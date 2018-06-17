/*****************************************************************************
 * \file
 * \brief Unit tests for the circular_deque
 *****************************************************************************/

#include <bit/stl/containers/circular_deque.hpp>

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

  struct nothrow_moveable
  {
    nothrow_moveable( int i ) : value(i){}
    nothrow_moveable( nothrow_moveable&& other ) noexcept
    {
      value = other.value;
      ++move_calls;
    }
    nothrow_moveable( nothrow_moveable const& other )
    {
      value = other.value;
      ++copy_calls;
    }

    static int move_calls;
    static int copy_calls;
    int value;
  };

  bool operator==( const nothrow_moveable& lhs, const nothrow_moveable& rhs ) {
    return lhs.value == rhs.value;
  }

  int nothrow_moveable::move_calls = 0;
  int nothrow_moveable::copy_calls = 0;

}

//-----------------------------------------------------------------------------
// Constructors / Assignment
//-----------------------------------------------------------------------------

TEST_CASE("circular_deque::circular_deque()", "[ctor]")
{
  bit::stl::circular_deque<int> empty;

  SECTION("Constructs null circular deque")
  {
    SECTION("Deque is empty")
    {
      REQUIRE( empty.empty() );
    }
    SECTION("Deque is full")
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

TEST_CASE("circular_deque::circular_deque( const Allocator& )", "[ctor]")
{
  // TODO(bitwizeshift): Test copying an allocator. Requires custom allocator
}

TEST_CASE("circular_deque::circular_deque( size_type, const T&, const Allocator& )", "[ctor]")
{
  SECTION("Doesn't specify allocator")
  {

  }
  SECTION("Specifies allocator")
  {
    // TODO(bitwizeshift): Test copying an allocator. Requires custom allocator
  }
}

TEST_CASE("circular_deque::circular_deque( size_type, const Allocator& )", "[ctor]")
{
  SECTION("Doesn't specify allocator")
  {

  }
  SECTION("Specifies allocator")
  {
    // TODO(bitwizeshift): Test copying an allocator. Requires custom allocator
  }
}

TEST_CASE("circular_deque::circular_deque( const circular_deque& )", "[ctor]")
{
  bit::stl::circular_deque<int> original{5};
  for( auto i = 0; i < 5; ++i ) {
    original.emplace_back(i);
  }

  auto copy = original;

  SECTION("Contains the same entries")
  {
    REQUIRE( std::equal(original.begin(),original.end(),copy.begin(),copy.end()) );
  }
  SECTION("Has same size")
  {
    REQUIRE( copy.size() == original.size() );
  }
  SECTION("Has same capacity")
  {
    REQUIRE( copy.capacity() == original.capacity() );
  }
}

TEST_CASE("circular_deque::circular_deque( const circular_deque&, const Allocator& )", "[ctor]")
{
  // TODO(bitwizeshift): Test copying an allocator. Requires custom allocator
}

TEST_CASE("circular_deque::circular_deque( circular_deque&& )", "[ctor]")
{
  bit::stl::circular_deque<moveable> original{5};
  for( auto i = 0; i < 5; ++i ) {
    original.emplace_back(i);
  }

  const auto copy = original;
  moveable::copy_calls = 0;
  moveable::move_calls = 0;
  const auto moved = std::move(original);

  SECTION("Contains the same entries")
  {
    REQUIRE( std::equal(moved.begin(),moved.end(),copy.begin(),copy.end()) );
  }
  SECTION("Has same size")
  {
    REQUIRE( moved.size() == copy.size() );
  }
  SECTION("Has same capacity")
  {
    REQUIRE( moved.capacity() == copy.capacity() );
  }
  SECTION("Performs no moves/copies on the underlying elements")
  {
    REQUIRE( (moveable::copy_calls == 0 && moveable::move_calls == 0) );
  }
}

TEST_CASE("circular_deque::circular_deque( circular_deque&&, const Allocator& )", "[ctor]")
{
  // TODO(bitwizeshift): Test copying an allocator. Requires custom allocator
}

//-----------------------------------------------------------------------------

TEST_CASE("circular_deque::operator=( circular_deque )", "[assignment]")
{
  auto deque = bit::stl::circular_deque<nothrow_moveable>{10};

  for( auto i = 0; i < 10; ++i ) {
    deque.emplace_back(i);
  }

  SECTION("deque as lvalue")
  {
    auto copy = deque;

    SECTION("Has same size")
    {
      REQUIRE( copy.size() == deque.size() );
    }

    SECTION("Has same capacity")
    {
      REQUIRE( copy.capacity() == deque.capacity() );
    }

    SECTION("Has same entries")
    {
      REQUIRE( std::equal(copy.begin(),copy.end(),deque.begin(),deque.end()) );
    }
  }
  SECTION("deque as rvalue")
  {
    auto old = deque;
    auto move = std::move(deque);

    SECTION("Has same size")
    {
      REQUIRE( move.size() == old.size() );
    }

    SECTION("Has same capacity")
    {
      REQUIRE( move.capacity() == old.capacity() );
    }

    SECTION("Has same entries")
    {
      REQUIRE( std::equal(move.begin(),move.end(),old.begin(),old.end()) );
    }
  }
}

//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

TEST_CASE("circular_deque::push_back( const T& )","[modifier]")
{
  const auto size = 5u;
  const copyable entry{42};
  auto deque = bit::stl::circular_deque<copyable>{size};

  SECTION("Deque is empty")
  {
    copyable::copy_calls = 0;
    deque.push_back( entry );

    SECTION("Increases size of deque")
    {
      REQUIRE( deque.size() == 1 );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( copyable::copy_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( deque.front() == entry );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( deque.back() == entry );
    }
  }

  SECTION("Deque is non-empty")
  {
    deque.push_back( copyable{0} );
    deque.push_back( copyable{1} );

    const auto old_size = deque.size();

    copyable::copy_calls = 0;
    deque.push_back( entry );

    SECTION("Increases size of deque")
    {
      REQUIRE( deque.size() == old_size + 1 );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( copyable::copy_calls == 1 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( deque.back() == entry );
    }
  }

  SECTION("Deque is full")
  {
    for( auto i = 0u; i < size; ++i ) {
      deque.push_back( copyable{ static_cast<int>(i) } );
    }
    const auto old_size = deque.size();

    copyable::copy_calls = 0;
    deque.push_back( entry );

    SECTION("Size doesn't change")
    {
      REQUIRE( deque.size() == old_size );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( copyable::copy_calls == 1 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( deque.back() == entry );
    }
  }
}

TEST_CASE("circular_deque::push_back( T&& )","[modifier]")
{
  const auto size = 5u;
  moveable entry{42};
  auto deque = bit::stl::circular_deque<moveable>{size};

  SECTION("Deque is empty")
  {
    const auto value = entry;

    moveable::move_calls = 0;
    deque.push_back( std::move(entry) );

    SECTION("Increases size of deque")
    {
      REQUIRE( deque.size() == 1 );
    }

    SECTION("Calls move constructor")
    {
      REQUIRE( moveable::move_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( deque.front() == value );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( deque.back() == value );
    }
  }

  SECTION("Deque is non-empty")
  {
    deque.push_back( moveable{0} );
    deque.push_back( moveable{1} );

    const auto old_size = deque.size();
    const auto value = entry;

    moveable::move_calls = 0;
    deque.push_back( std::move(entry) );

    SECTION("Increases size of deque")
    {
      REQUIRE( deque.size() == old_size + 1 );
    }

    SECTION("Calls move constructor")
    {
      REQUIRE( moveable::move_calls == 1 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( deque.back() == value );
    }
  }

  SECTION("Deque is full")
  {
    for( auto i = 0u; i < size; ++i ) {
      deque.push_back( moveable{ static_cast<int>(i) } );
    }
    const auto old_size = deque.size();
    const auto value = entry;

    moveable::move_calls = 0;
    deque.push_back( std::move(entry) );

    SECTION("Size doesn't change")
    {
      REQUIRE( deque.size() == old_size );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( moveable::move_calls == 1 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( deque.back() == value );
    }
  }
}

//-----------------------------------------------------------------------------

TEST_CASE("circular_deque::push_front( const T& )","[modifier]")
{
  const auto size = 5u;
  const copyable entry{42};
  auto deque = bit::stl::circular_deque<copyable>{size};

  SECTION("Deque is empty")
  {
    copyable::copy_calls = 0;
    deque.push_front( entry );

    SECTION("Increases size of deque")
    {
      REQUIRE( deque.size() == 1 );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( copyable::copy_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( deque.front() == entry );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( deque.back() == entry );
    }
  }

  SECTION("Deque is non-empty")
  {
    deque.push_front( copyable{0} );
    deque.push_front( copyable{1} );

    const auto old_size = deque.size();

    copyable::copy_calls = 0;
    deque.push_front( entry );

    SECTION("Increases size of deque")
    {
      REQUIRE( deque.size() == old_size + 1 );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( copyable::copy_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( deque.front() == entry );
    }
  }

  SECTION("Deque is full")
  {
    for( auto i = 0u; i < size; ++i ) {
      deque.push_front( copyable{ static_cast<int>(i) } );
    }
    const auto old_size = deque.size();

    copyable::copy_calls = 0;
    deque.push_front( entry );

    SECTION("Size doesn't change")
    {
      REQUIRE( deque.size() == old_size );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( copyable::copy_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( deque.front() == entry );
    }
  }
}

TEST_CASE("circular_deque::push_front( T&& )","[modifier]")
{
  const auto size = 5u;
  moveable entry{42};
  auto deque = bit::stl::circular_deque<moveable>{size};

  SECTION("Deque is empty")
  {
    const auto value = entry;

    moveable::move_calls = 0;
    deque.push_front( std::move(entry) );

    SECTION("Increases size of deque")
    {
      REQUIRE( deque.size() == 1 );
    }

    SECTION("Calls move constructor")
    {
      REQUIRE( moveable::move_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( deque.front() == value );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( deque.back() == value );
    }
  }

  SECTION("Deque is non-empty")
  {
    deque.push_front( moveable{0} );
    deque.push_front( moveable{1} );

    const auto old_size = deque.size();
    const auto value = entry;

    moveable::move_calls = 0;
    deque.push_front( std::move(entry) );

    SECTION("Increases size of deque")
    {
      REQUIRE( deque.size() == old_size + 1 );
    }

    SECTION("Calls move constructor")
    {
      REQUIRE( moveable::move_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( deque.front() == value );
    }
  }

  SECTION("Deque is full")
  {
    for( auto i = 0u; i < size; ++i ) {
      deque.push_front( moveable{ static_cast<int>(i) } );
    }
    const auto old_size = deque.size();
    const auto value = entry;

    moveable::move_calls = 0;
    deque.push_front( std::move(entry) );

    SECTION("Size doesn't change")
    {
      REQUIRE( deque.size() == old_size );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( moveable::move_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( deque.front() == value );
    }
  }
}

//-----------------------------------------------------------------------------

TEST_CASE("circular_deque::emplace_back( Args&&... )", "[modifier]")
{
  const auto size = 5u;
  auto deque = bit::stl::circular_deque<copyable>{size};
  const auto value = 42;

  SECTION("Deque is empty")
  {
    copyable::copy_calls = 0;
    deque.emplace_back( value );

    SECTION("Increases size of deque")
    {
      REQUIRE( deque.size() == 1 );
    }

    SECTION("Does not call copy constructor")
    {
      REQUIRE( copyable::copy_calls == 0 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( deque.front() == copyable{value} );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( deque.back() == copyable{value} );
    }
  }

  SECTION("Deque is non-empty")
  {
    deque.push_back( copyable{0} );
    deque.push_back( copyable{1} );

    const auto old_size = deque.size();

    copyable::copy_calls = 0;
    deque.emplace_back( value );

    SECTION("Increases size of deque")
    {
      REQUIRE( deque.size() == old_size + 1 );
    }

    SECTION("Does not call copy constructor")
    {
      REQUIRE( copyable::copy_calls == 0 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( deque.back() == copyable{value} );
    }
  }

  SECTION("Deque is full")
  {
    for( auto i = 0u; i < size; ++i ) {
      deque.push_back( copyable{ static_cast<int>(i) } );
    }
    const auto old_size = deque.size();

    copyable::copy_calls = 0;
    deque.emplace_back( value );

    SECTION("Size doesn't change")
    {
      REQUIRE( deque.size() == old_size );
    }

    SECTION("Does not call copy constructor")
    {
      REQUIRE( copyable::copy_calls == 0 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( deque.back() == copyable{value} );
    }
  }
}

TEST_CASE("circular_deque::emplace_front( Args&&... )", "[modifier]")
{
  const auto size = 5u;
  auto deque = bit::stl::circular_deque<copyable>{size};
  const auto value = 42;

  SECTION("Deque is empty")
  {
    copyable::copy_calls = 0;
    deque.emplace_front( value );

    SECTION("Increases size of deque")
    {
      REQUIRE( deque.size() == 1 );
    }

    SECTION("Does not call copy constructor")
    {
      REQUIRE( copyable::copy_calls == 0 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( deque.front() == copyable{value} );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( deque.back() == copyable{value} );
    }
  }

  SECTION("Deque is non-empty")
  {
    deque.push_back( copyable{0} );
    deque.push_back( copyable{1} );

    const auto old_size = deque.size();

    copyable::copy_calls = 0;
    deque.emplace_front( value );

    SECTION("Increases size of deque")
    {
      REQUIRE( deque.size() == old_size + 1 );
    }

    SECTION("Does not call copy constructor")
    {
      REQUIRE( copyable::copy_calls == 0 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( deque.front() == copyable{value} );
    }
  }

  SECTION("Deque is full")
  {
    for( auto i = 0u; i < size; ++i ) {
      deque.push_back( copyable{ static_cast<int>(i) } );
    }
    const auto old_size = deque.size();

    copyable::copy_calls = 0;
    deque.emplace_front( value );

    SECTION("Size doesn't change")
    {
      REQUIRE( deque.size() == old_size );
    }

    SECTION("Does not call copy constructor")
    {
      REQUIRE( copyable::copy_calls == 0 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( deque.front() == copyable{value} );
    }
  }
}

//-----------------------------------------------------------------------------

TEST_CASE("circular_deque::pop_back()","[modifier]")
{
  const auto size = 5u;
  auto deque = bit::stl::circular_deque<int>{size};

  for( auto i = 0u; i < size; ++i ) {
    deque.emplace_front( static_cast<int>(i) );
  }

  SECTION("Reduces size by 1")
  {
    const auto old_size = deque.size();
    deque.pop_back();
    const auto new_size = deque.size();

    REQUIRE( old_size != new_size );
  }

  SECTION("Removes the front entry")
  {
    const auto old_value = deque.back();
    deque.pop_back();
    const auto new_value = deque.back();

    REQUIRE( old_value != new_value );
  }
}

TEST_CASE("circular_deque::pop_front()","[modifier]")
{
  const auto size = 5u;
  auto deque = bit::stl::circular_deque<int>{size};

  for( auto i = 0u; i < size; ++i ) {
    deque.emplace_back( static_cast<int>(i) );
  }

  SECTION("Reduces size by 1")
  {
    const auto old_size  = deque.size();
    deque.pop_front();
    const auto new_size  = deque.size();

    REQUIRE( old_size != new_size );
  }

  SECTION("Removes the front entry")
  {
    const auto old_value = deque.front();
    deque.pop_front();
    const auto new_value = deque.front();

    REQUIRE( old_value != new_value );
  }
}

//-----------------------------------------------------------------------------

TEST_CASE("circular_deque::swap( circular_deque& )","[modifier]")
{
  const auto size = 5u;
  auto right = bit::stl::circular_deque<moveable>{};
  auto left = bit::stl::circular_deque<moveable>{size};

  for( auto i = 0u; i < size; ++i ) {
    left.emplace_back( static_cast<int>(i) );
  }

  const auto copy_right = right;
  const auto copy_left  = left;

  moveable::copy_calls = 0;
  moveable::move_calls = 0;

  left.swap(right);

  SECTION("Doesn't call any constructors")
  {
    REQUIRE( (moveable::copy_calls == 0 && moveable::move_calls == 0) );
  }

  SECTION("Left contain's Right's old state")
  {
    SECTION("Swaps values")
    {
      REQUIRE( std::equal(left.begin(),left.end(),copy_right.begin(),copy_right.end()) );
    }
    SECTION("Swaps capacity")
    {
      REQUIRE( left.capacity() == copy_right.capacity() );
    }
    SECTION("Swaps size")
    {
      REQUIRE( left.size() == copy_right.size() );
    }
  }

  SECTION("Right contains Left's old state")
  {
    SECTION("Swaps values")
    {
      REQUIRE( std::equal(right.begin(),right.end(),copy_left.begin(),copy_left.end()) );
    }
    SECTION("Swaps capacity")
    {
      REQUIRE( right.capacity() == copy_left.capacity() );
    }
    SECTION("Swaps size")
    {
      REQUIRE( right.size() == copy_left.size() );
    }
  }

}

//-----------------------------------------------------------------------------

TEST_CASE("circular_deque::resize( size_type )", "[modifier]")
{
  SECTION("Deque is empty")
  {
    SECTION("New size smaller than current capacity")
    {
      static constexpr auto size = 10u;
      static constexpr auto new_size = 5u;
      auto deque = bit::stl::circular_deque<int>{size};

      deque.resize(new_size);

      SECTION("Max size is unchanged")
      {
        REQUIRE( deque.max_size() == size );
      }
      SECTION("Capacity is unchanged")
      {
        REQUIRE( deque.capacity() == size );
      }
    }

    SECTION("New size bigger than current capacity")
    {
      static constexpr auto new_size = 10u;
      auto deque = bit::stl::circular_deque<int>{};

      deque.resize(new_size);

      SECTION("Max size is new_size")
      {
        REQUIRE( deque.max_size() == new_size );
      }
      SECTION("Capacity is new_size")
      {
        REQUIRE( deque.capacity() == new_size );
      }
    }

  }

  SECTION("Deque is not empty")
  {
    SECTION("New size bigger than current capacity")
    {
      SECTION("T is nothrow move constructible")
      {
        static constexpr auto size = 5u;
        static constexpr auto new_size = 10u;

        auto deque = bit::stl::circular_deque<nothrow_moveable>{size};

        for( auto i = 0u; i < size; ++i ) {
          deque.emplace_back( static_cast<int>(i) );
        }
        auto old = deque;

        nothrow_moveable::move_calls = 0;
        nothrow_moveable::copy_calls = 0;

        deque.resize(new_size);

        SECTION("Resize calls move constructors")
        {
          REQUIRE( nothrow_moveable::move_calls == size );
        }
        SECTION("Resize does not call copy constructors")
        {
          REQUIRE( nothrow_moveable::copy_calls == 0 );
        }
        SECTION("Entries are the same after resizing")
        {
          REQUIRE( std::equal(old.begin(),old.end(),deque.begin(),deque.end()) );
        }
        SECTION("Capacity is new_size")
        {
          REQUIRE( deque.capacity() == new_size );
        }
      }

      SECTION("T is not nothrow move constructible")
      {
        static constexpr auto size = 5u;
        static constexpr auto new_size = 10u;

        auto deque = bit::stl::circular_deque<moveable>{size};

        for( auto i = 0u; i < size; ++i ) {
          deque.emplace_back( static_cast<int>(i) );
        }
        auto old = deque;

        moveable::move_calls = 0;
        moveable::copy_calls = 0;

        deque.resize(new_size);

        SECTION("Resize calls copy constructors")
        {
          REQUIRE( moveable::copy_calls == size );
        }
        SECTION("Resize does not call move constructors")
        {
          REQUIRE( moveable::move_calls == 0 );
        }
        SECTION("Entries are the same after resizing")
        {
          REQUIRE( std::equal(old.begin(),old.end(),deque.begin(),deque.end()) );
        }
        SECTION("Capacity is new_size")
        {
          REQUIRE( deque.capacity() == new_size );
        }
      }
    }
  }
}


