/*****************************************************************************
 * \file
 * \brief Unit tests for circular_buffer
 *****************************************************************************/

#include <bit/stl/containers/circular_buffer.hpp>

#include <bit/stl/utilities/aligned_storage.hpp> // aligned_storage_for

#include <algorithm> // std::equal
#include <utility>   // std::move

#include <catch.hpp>

namespace {
  struct copyable
  {
    copyable( int i ) : value(i){}
    copyable( copyable const& other )
    {
      value = other.value;
      ++copy_calls;
    }
    copyable( copyable&& ) = delete;

    static int copy_calls;
    int value;
  };

  bool operator==( const copyable& lhs, const copyable& rhs ) {
    return lhs.value == rhs.value;
  }

  int copyable::copy_calls = 0;

  struct moveable
  {
    moveable( int i ) : value(i){}
    moveable( moveable&& other ) noexcept(false)
    {
      value = other.value;
      ++move_calls;
    }
    moveable( moveable const& other )
    {
      value = other.value;
      ++copy_calls;
    }

    static int move_calls;
    static int copy_calls;
    int value;
  };

  bool operator==( const moveable& lhs, const moveable& rhs ) {
    return lhs.value == rhs.value;
  }


  int moveable::move_calls = 0;
  int moveable::copy_calls = 0;
}

//-----------------------------------------------------------------------------
// Constructors / Assignment
//-----------------------------------------------------------------------------

TEST_CASE("circular_buffer::circular_buffer()", "[ctor]")
{
  auto empty = bit::stl::circular_buffer<int>{};

  SECTION("Constructs null circular buffer")
  {
    SECTION("Buffer is empty")
    {
      REQUIRE( empty.empty() );
    }
    SECTION("Buffer is full")
    {
      REQUIRE( empty.full() );
    }
    SECTION("Max size is 0")
    {
      REQUIRE( empty.max_size() == 0 );
    }
    SECTION("Capacity is 0")
    {
      REQUIRE( empty.capacity() == 0 );
    }
  }
}

//-----------------------------------------------------------------------------

TEST_CASE("circular_buffer::circular_buffer( std::nullptr_t )", "[ctor]")
{
  auto empty = bit::stl::circular_buffer<int>{nullptr};

  SECTION("Constructs null circular buffer")
  {
    SECTION("Buffer is empty")
    {
      REQUIRE( empty.empty() );
    }
    SECTION("Buffer is full")
    {
      REQUIRE( empty.full() );
    }
    SECTION("Max size is 0")
    {
      REQUIRE( empty.max_size() == 0 );
    }
    SECTION("Capacity is 0")
    {
      REQUIRE( empty.capacity() == 0 );
    }
  }
}

//-----------------------------------------------------------------------------

TEST_CASE("circular_buffer::circular_buffer( void*, size_type )", "[ctor]")
{
  using storage_type = bit::stl::aligned_storage_for<int[5]>;

  const auto size = 5u;
  auto storage = storage_type{};
  auto data = reinterpret_cast<char*>(&storage);
  auto buffer = bit::stl::circular_buffer<int>(data,size);

  SECTION("Data points to original storage")
  {
    REQUIRE( buffer.data() == (void*) &storage );
  }
  SECTION("Capacity is equal to specified size")
  {
    REQUIRE( buffer.capacity() == size );
  }
  SECTION("Buffer is not full")
  {
    REQUIRE( !buffer.full() );
  }
}

//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

TEST_CASE("circular_buffer::push_back( const T& )","[modifier]")
{
  using storage_type = bit::stl::aligned_storage_for<copyable[5]>;

  const auto size = 5u;
  const copyable entry{42};

  auto storage = storage_type{};
  auto data = reinterpret_cast<char*>(&storage);
  auto buffer = bit::stl::circular_buffer<copyable>(data,size);

  SECTION("Buffer is empty")
  {
    copyable::copy_calls = 0;
    buffer.push_back( entry );

    SECTION("Increases size of buffer")
    {
      REQUIRE( buffer.size() == 1 );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( copyable::copy_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( buffer.front() == entry );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( buffer.back() == entry );
    }
  }

  SECTION("Buffer is non-empty")
  {
    buffer.push_back( copyable{0} );
    buffer.push_back( copyable{1} );

    const auto old_size = buffer.size();

    copyable::copy_calls = 0;
    buffer.push_back( entry );

    SECTION("Increases size of buffer")
    {
      REQUIRE( buffer.size() == old_size + 1 );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( copyable::copy_calls == 1 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( buffer.back() == entry );
    }
  }

  SECTION("Buffer is full")
  {
    for( auto i = 0; i < size; ++i ) {
      buffer.push_back( copyable{i} );
    }
    const auto old_size = buffer.size();

    copyable::copy_calls = 0;
    buffer.push_back( entry );

    SECTION("Size doesn't change")
    {
      REQUIRE( buffer.size() == old_size );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( copyable::copy_calls == 1 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( buffer.back() == entry );
    }
  }
}

TEST_CASE("circular_buffer::push_back( T&& )","[modifier]")
{
  using storage_type = bit::stl::aligned_storage_for<moveable[5]>;

  const auto size = 5u;
  moveable entry{42};

  auto storage = storage_type{};
  auto data = reinterpret_cast<char*>(&storage);
  auto buffer = bit::stl::circular_buffer<moveable>(data,size);

  SECTION("Buffer is empty")
  {
    const auto value = entry;

    moveable::move_calls = 0;
    buffer.push_back( std::move(entry) );

    SECTION("Increases size of buffer")
    {
      REQUIRE( buffer.size() == 1 );
    }

    SECTION("Calls move constructor")
    {
      REQUIRE( moveable::move_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( buffer.front() == value );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( buffer.back() == value );
    }
  }

  SECTION("Buffer is non-empty")
  {
    buffer.push_back( moveable{0} );
    buffer.push_back( moveable{1} );

    const auto old_size = buffer.size();
    const auto value = entry;

    moveable::move_calls = 0;
    buffer.push_back( std::move(entry) );

    SECTION("Increases size of buffer")
    {
      REQUIRE( buffer.size() == old_size + 1 );
    }

    SECTION("Calls move constructor")
    {
      REQUIRE( moveable::move_calls == 1 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( buffer.back() == value );
    }
  }

  SECTION("Buffer is full")
  {
    for( auto i = 0; i < size; ++i ) {
      buffer.push_back( moveable{i} );
    }
    const auto old_size = buffer.size();
    const auto value = entry;

    moveable::move_calls = 0;
    buffer.push_back( std::move(entry) );

    SECTION("Size doesn't change")
    {
      REQUIRE( buffer.size() == old_size );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( moveable::move_calls == 1 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( buffer.back() == value );
    }
  }
}

//-----------------------------------------------------------------------------

TEST_CASE("circular_buffer::push_front( const T& )","[modifier]")
{
  using storage_type = bit::stl::aligned_storage_for<copyable[5]>;

  const auto size = 5u;
  const copyable entry{42};

  auto storage = storage_type{};
  auto data = reinterpret_cast<char*>(&storage);
  auto buffer = bit::stl::circular_buffer<copyable>(data,size);

  SECTION("Buffer is empty")
  {
    copyable::copy_calls = 0;
    buffer.push_front( entry );

    SECTION("Increases size of buffer")
    {
      REQUIRE( buffer.size() == 1 );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( copyable::copy_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( buffer.front() == entry );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( buffer.back() == entry );
    }
  }

  SECTION("Buffer is non-empty")
  {
    buffer.push_front( copyable{0} );
    buffer.push_front( copyable{1} );

    const auto old_size = buffer.size();

    copyable::copy_calls = 0;
    buffer.push_front( entry );

    SECTION("Increases size of buffer")
    {
      REQUIRE( buffer.size() == old_size + 1 );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( copyable::copy_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( buffer.front() == entry );
    }
  }

  SECTION("Buffer is full")
  {
    for( auto i = 0; i < size; ++i ) {
      buffer.push_front( copyable{i} );
    }
    const auto old_size = buffer.size();

    copyable::copy_calls = 0;
    buffer.push_front( entry );

    SECTION("Size doesn't change")
    {
      REQUIRE( buffer.size() == old_size );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( copyable::copy_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( buffer.front() == entry );
    }
  }
}

TEST_CASE("circular_buffer::push_front( T&& )","[modifier]")
{
  using storage_type = bit::stl::aligned_storage_for<moveable[5]>;

  const auto size = 5u;
  moveable entry{42};

  auto storage = storage_type{};
  auto data = reinterpret_cast<char*>(&storage);
  auto buffer = bit::stl::circular_buffer<moveable>(data,size);

  SECTION("Buffer is empty")
  {
    const auto value = entry;

    moveable::move_calls = 0;
    buffer.push_front( std::move(entry) );

    SECTION("Increases size of buffer")
    {
      REQUIRE( buffer.size() == 1 );
    }

    SECTION("Calls move constructor")
    {
      REQUIRE( moveable::move_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( buffer.front() == value );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( buffer.back() == value );
    }
  }

  SECTION("Buffer is non-empty")
  {
    buffer.push_front( moveable{0} );
    buffer.push_front( moveable{1} );

    const auto old_size = buffer.size();
    const auto value = entry;

    moveable::move_calls = 0;
    buffer.push_front( std::move(entry) );

    SECTION("Increases size of buffer")
    {
      REQUIRE( buffer.size() == old_size + 1 );
    }

    SECTION("Calls move constructor")
    {
      REQUIRE( moveable::move_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( buffer.front() == value );
    }
  }

  SECTION("Buffer is full")
  {
    for( auto i = 0; i < size; ++i ) {
      buffer.push_front( moveable{i} );
    }
    const auto old_size = buffer.size();
    const auto value = entry;

    moveable::move_calls = 0;
    buffer.push_front( std::move(entry) );

    SECTION("Size doesn't change")
    {
      REQUIRE( buffer.size() == old_size );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( moveable::move_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( buffer.front() == value );
    }
  }
}

//-----------------------------------------------------------------------------

TEST_CASE("circular_buffer::emplace_back( Args&&... )", "[modifier]")
{
  using storage_type = bit::stl::aligned_storage_for<copyable[5]>;

  const auto size = 5u;
  const auto value = 42;

  auto storage = storage_type{};
  auto data = reinterpret_cast<char*>(&storage);
  auto buffer = bit::stl::circular_buffer<copyable>(data,size);


  SECTION("Buffer is empty")
  {
    copyable::copy_calls = 0;
    buffer.emplace_back( value );

    SECTION("Increases size of buffer")
    {
      REQUIRE( buffer.size() == 1 );
    }

    SECTION("Does not call copy constructor")
    {
      REQUIRE( copyable::copy_calls == 0 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( buffer.front() == copyable{value} );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( buffer.back() == copyable{value} );
    }
  }

  SECTION("Buffer is non-empty")
  {
    buffer.push_back( copyable{0} );
    buffer.push_back( copyable{1} );

    const auto old_size = buffer.size();

    copyable::copy_calls = 0;
    buffer.emplace_back( value );

    SECTION("Increases size of buffer")
    {
      REQUIRE( buffer.size() == old_size + 1 );
    }

    SECTION("Does not call copy constructor")
    {
      REQUIRE( copyable::copy_calls == 0 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( buffer.back() == copyable{value} );
    }
  }

  SECTION("Buffer is full")
  {
    for( auto i = 0; i < size; ++i ) {
      buffer.push_back( copyable{i} );
    }
    const auto old_size = buffer.size();

    copyable::copy_calls = 0;
    buffer.emplace_back( value );

    SECTION("Size doesn't change")
    {
      REQUIRE( buffer.size() == old_size );
    }

    SECTION("Does not call copy constructor")
    {
      REQUIRE( copyable::copy_calls == 0 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( buffer.back() == copyable{value} );
    }
  }
}

TEST_CASE("circular_buffer::emplace_front( Args&&... )", "[modifier]")
{
  using storage_type = bit::stl::aligned_storage_for<copyable[5]>;

  const auto size = 5u;
  const auto value = 42;

  auto storage = storage_type{};
  auto data = reinterpret_cast<char*>(&storage);
  auto buffer = bit::stl::circular_buffer<copyable>(data,size);

  SECTION("Buffer is empty")
  {
    copyable::copy_calls = 0;
    buffer.emplace_front( value );

    SECTION("Increases size of buffer")
    {
      REQUIRE( buffer.size() == 1 );
    }

    SECTION("Does not call copy constructor")
    {
      REQUIRE( copyable::copy_calls == 0 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( buffer.front() == copyable{value} );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( buffer.back() == copyable{value} );
    }
  }

  SECTION("Buffer is non-empty")
  {
    buffer.push_back( copyable{0} );
    buffer.push_back( copyable{1} );

    const auto old_size = buffer.size();

    copyable::copy_calls = 0;
    buffer.emplace_front( value );

    SECTION("Increases size of buffer")
    {
      REQUIRE( buffer.size() == old_size + 1 );
    }

    SECTION("Does not call copy constructor")
    {
      REQUIRE( copyable::copy_calls == 0 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( buffer.front() == copyable{value} );
    }
  }

  SECTION("Buffer is full")
  {
    for( auto i = 0; i < size; ++i ) {
      buffer.push_back( copyable{i} );
    }
    const auto old_size = buffer.size();

    copyable::copy_calls = 0;
    buffer.emplace_front( value );

    SECTION("Size doesn't change")
    {
      REQUIRE( buffer.size() == old_size );
    }

    SECTION("Does not call copy constructor")
    {
      REQUIRE( copyable::copy_calls == 0 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( buffer.front() == copyable{value} );
    }
  }
}

//-----------------------------------------------------------------------------

TEST_CASE("circular_buffer::pop_back()","[modifier]")
{
  using storage_type = bit::stl::aligned_storage_for<int[5]>;

  const auto size = 5u;

  auto storage = storage_type{};
  auto data = reinterpret_cast<char*>(&storage);
  auto buffer = bit::stl::circular_buffer<int>(data,size);

  for( auto i = 0; i < size; ++i ) {
    buffer.emplace_front(i);
  }

  SECTION("Reduces size by 1")
  {
    const auto old_size = buffer.size();
    buffer.pop_back();
    const auto new_size = buffer.size();

    REQUIRE( old_size != new_size );
  }

  SECTION("Removes the front entry")
  {
    const auto old_value = buffer.back();
    buffer.pop_back();
    const auto new_value = buffer.back();

    REQUIRE( old_value != new_value );
  }
}

TEST_CASE("circular_buffer::pop_front()","[modifier]")
{
  using storage_type = bit::stl::aligned_storage_for<int[5]>;

  const auto size = 5u;

  auto storage = storage_type{};
  auto data = reinterpret_cast<char*>(&storage);
  auto buffer = bit::stl::circular_buffer<int>(data,size);

  for( auto i = 0; i < size; ++i ) {
    buffer.emplace_back(i);
  }

  SECTION("Reduces size by 1")
  {
    const auto old_size  = buffer.size();
    buffer.pop_front();
    const auto new_size  = buffer.size();

    REQUIRE( old_size != new_size );
  }

  SECTION("Removes the front entry")
  {
    const auto old_value = buffer.front();
    buffer.pop_front();
    const auto new_value = buffer.front();

    REQUIRE( old_value != new_value );
  }
}
