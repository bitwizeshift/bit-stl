/*****************************************************************************
 * \file
 * \brief Unit tests for the circular_queue
 *****************************************************************************/

#include <bit/stl/containers/circular_queue.hpp>

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

TEST_CASE("circular_queue::circular_queue()", "[ctor]")
{
  bit::stl::circular_queue<int> empty;

  SECTION("Constructs null circular queue")
  {
    SECTION("Queue is empty")
    {
      REQUIRE( empty.empty() );
    }
    SECTION("Queue is full")
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

TEST_CASE("circular_queue::circular_queue( const Allocator& )", "[ctor]")
{
  // TODO(bitwizeshift): Test copying an allocator. Requires custom allocator
}

TEST_CASE("circular_queue::circular_queue( size_type, const T&, const Allocator& )", "[ctor]")
{
  SECTION("Doesn't specify allocator")
  {

  }
  SECTION("Specifies allocator")
  {
    // TODO(bitwizeshift): Test copying an allocator. Requires custom allocator
  }
}

TEST_CASE("circular_queue::circular_queue( size_type, const Allocator& )", "[ctor]")
{
  SECTION("Doesn't specify allocator")
  {

  }
  SECTION("Specifies allocator")
  {
    // TODO(bitwizeshift): Test copying an allocator. Requires custom allocator
  }
}

TEST_CASE("circular_queue::circular_queue( const circular_queue& )", "[ctor]")
{
  bit::stl::circular_queue<int> original{5};
  for( auto i = 0; i < 5; ++i ) {
    original.emplace(i);
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

TEST_CASE("circular_queue::circular_queue( const circular_queue&, const Allocator& )", "[ctor]")
{
  // TODO(bitwizeshift): Test copying an allocator. Requires custom allocator
}

TEST_CASE("circular_queue::circular_queue( circular_queue&& )", "[ctor]")
{
  bit::stl::circular_queue<moveable> original{5};
  for( auto i = 0; i < 5; ++i ) {
    original.emplace(i);
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

TEST_CASE("circular_queue::circular_queue( circular_queue&&, const Allocator& )", "[ctor]")
{
  // TODO(bitwizeshift): Test copying an allocator. Requires custom allocator
}

//-----------------------------------------------------------------------------

TEST_CASE("circular_queue::operator=( circular_queue )", "[assignment]")
{
  auto queue = bit::stl::circular_queue<nothrow_moveable>{10};

  for( auto i = 0; i < 10; ++i ) {
    queue.emplace(i);
  }

  SECTION("queue as lvalue")
  {
    auto copy = queue;

    SECTION("Has same size")
    {
      REQUIRE( copy.size() == queue.size() );
    }

    SECTION("Has same capacity")
    {
      REQUIRE( copy.capacity() == queue.capacity() );
    }

    SECTION("Has same entries")
    {
      REQUIRE( std::equal(copy.begin(),copy.end(),queue.begin(),queue.end()) );
    }
  }
  SECTION("queue as rvalue")
  {
    auto old = queue;
    auto move = std::move(queue);

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

TEST_CASE("circular_queue::push( const T& )","[modifier]")
{
  const auto size = 5u;
  const copyable entry{42};
  auto queue = bit::stl::circular_queue<copyable>{size};

  SECTION("Queue is empty")
  {
    copyable::copy_calls = 0;
    queue.push( entry );

    SECTION("Increases size of queue")
    {
      REQUIRE( queue.size() == 1 );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( copyable::copy_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( queue.front() == entry );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( queue.back() == entry );
    }
  }

  SECTION("Queue is non-empty")
  {
    queue.push( copyable{0} );
    queue.push( copyable{1} );

    const auto old_size = queue.size();

    copyable::copy_calls = 0;
    queue.push( entry );

    SECTION("Increases size of queue")
    {
      REQUIRE( queue.size() == old_size + 1 );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( copyable::copy_calls == 1 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( queue.back() == entry );
    }
  }

  SECTION("Queue is full")
  {
    for( auto i = 0u; i < size; ++i ) {
      queue.push( copyable{ static_cast<int>(i) } );
    }
    const auto old_size = queue.size();

    copyable::copy_calls = 0;
    queue.push( entry );

    SECTION("Size doesn't change")
    {
      REQUIRE( queue.size() == old_size );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( copyable::copy_calls == 1 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( queue.back() == entry );
    }
  }
}

TEST_CASE("circular_queue::push( T&& )","[modifier]")
{
  const auto size = 5u;
  moveable entry{42};
  auto queue = bit::stl::circular_queue<moveable>{size};

  SECTION("Queue is empty")
  {
    const auto value = entry;

    moveable::move_calls = 0;
    queue.push( std::move(entry) );

    SECTION("Increases size of queue")
    {
      REQUIRE( queue.size() == 1 );
    }

    SECTION("Calls move constructor")
    {
      REQUIRE( moveable::move_calls == 1 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( queue.front() == value );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( queue.back() == value );
    }
  }

  SECTION("Queue is non-empty")
  {
    queue.push( moveable{0} );
    queue.push( moveable{1} );

    const auto old_size = queue.size();
    const auto value = entry;

    moveable::move_calls = 0;
    queue.push( std::move(entry) );

    SECTION("Increases size of queue")
    {
      REQUIRE( queue.size() == old_size + 1 );
    }

    SECTION("Calls move constructor")
    {
      REQUIRE( moveable::move_calls == 1 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( queue.back() == value );
    }
  }

  SECTION("Queue is full")
  {
    for( auto i = 0u; i < size; ++i ) {
      queue.push( moveable{ static_cast<int>(i) } );
    }
    const auto old_size = queue.size();
    const auto value = entry;

    moveable::move_calls = 0;
    queue.push( std::move(entry) );

    SECTION("Size doesn't change")
    {
      REQUIRE( queue.size() == old_size );
    }

    SECTION("Calls copy constructor")
    {
      REQUIRE( moveable::move_calls == 1 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( queue.back() == value );
    }
  }
}

//-----------------------------------------------------------------------------

TEST_CASE("circular_queue::emplace( Args&&... )", "[modifier]")
{
  const auto size = 5u;
  auto queue = bit::stl::circular_queue<copyable>{size};
  const auto value = 42;

  SECTION("Queue is empty")
  {
    copyable::copy_calls = 0;
    queue.emplace( value );

    SECTION("Increases size of queue")
    {
      REQUIRE( queue.size() == 1 );
    }

    SECTION("Does not call copy constructor")
    {
      REQUIRE( copyable::copy_calls == 0 );
    }

    SECTION("Becomes the front value")
    {
      REQUIRE( queue.front() == copyable{value} );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( queue.back() == copyable{value} );
    }
  }

  SECTION("Queue is non-empty")
  {
    queue.push( copyable{0} );
    queue.push( copyable{1} );

    const auto old_size = queue.size();

    copyable::copy_calls = 0;
    queue.emplace( value );

    SECTION("Increases size of queue")
    {
      REQUIRE( queue.size() == old_size + 1 );
    }

    SECTION("Does not call copy constructor")
    {
      REQUIRE( copyable::copy_calls == 0 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( queue.back() == copyable{value} );
    }
  }

  SECTION("Queue is full")
  {
    for( auto i = 0u; i < size; ++i ) {
      queue.push( copyable{ static_cast<int>(i) } );
    }
    const auto old_size = queue.size();

    copyable::copy_calls = 0;
    queue.emplace( value );

    SECTION("Size doesn't change")
    {
      REQUIRE( queue.size() == old_size );
    }

    SECTION("Does not call copy constructor")
    {
      REQUIRE( copyable::copy_calls == 0 );
    }

    SECTION("Becomes the back value")
    {
      REQUIRE( queue.back() == copyable{value} );
    }
  }
}

//-----------------------------------------------------------------------------

TEST_CASE("circular_queue::pop()","[modifier]")
{
  const auto size = 5u;
  auto queue = bit::stl::circular_queue<int>{size};

  for( auto i = 0u; i < size; ++i ) {
    queue.emplace(i);
  }

  SECTION("Reduces size by 1")
  {
    const auto old_size  = queue.size();
    queue.pop();
    const auto new_size  = queue.size();

    REQUIRE( old_size != new_size );
  }

  SECTION("Removes the front entry")
  {
    const auto old_value = queue.front();
    queue.pop();
    const auto new_value = queue.front();

    REQUIRE( old_value != new_value );
  }
}

//-----------------------------------------------------------------------------

TEST_CASE("circular_queue::swap( circular_queue& )","[modifier]")
{
  const auto size = 5u;
  auto right = bit::stl::circular_queue<moveable>{};
  auto left = bit::stl::circular_queue<moveable>{size};

  for( auto i = 0u; i < size; ++i ) {
    left.emplace(i);
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

TEST_CASE("circular_queue::resize( size_type )", "[modifier]")
{
  SECTION("Queue is empty")
  {
    SECTION("New size smaller than current capacity")
    {
      static constexpr auto size = 10u;
      static constexpr auto new_size = 5u;
      auto queue = bit::stl::circular_queue<int>{size};

      queue.resize(new_size);

      SECTION("Max size is unchanged")
      {
        REQUIRE( queue.max_size() == size );
      }
      SECTION("Capacity is unchanged")
      {
        REQUIRE( queue.capacity() == size );
      }
    }

    SECTION("New size bigger than current capacity")
    {
      static constexpr auto new_size = 10u;
      auto queue = bit::stl::circular_queue<int>{};

      queue.resize(new_size);

      SECTION("Max size is new_size")
      {
        REQUIRE( queue.max_size() == new_size );
      }
      SECTION("Capacity is new_size")
      {
        REQUIRE( queue.capacity() == new_size );
      }
    }

  }

  SECTION("Queue is not empty")
  {
    SECTION("New size bigger than current capacity")
    {
      SECTION("T is nothrow move constructible")
      {
        static constexpr auto size = 5u;
        static constexpr auto new_size = 10u;

        auto queue = bit::stl::circular_queue<nothrow_moveable>{size};

        for( auto i = 0u; i < size; ++i ) {
          queue.emplace(i);
        }
        auto old = queue;

        nothrow_moveable::move_calls = 0;
        nothrow_moveable::copy_calls = 0;

        queue.resize(new_size);

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
          REQUIRE( std::equal(old.begin(),old.end(),queue.begin(),queue.end()) );
        }
        SECTION("Capacity is new_size")
        {
          REQUIRE( queue.capacity() == new_size );
        }
      }

      SECTION("T is not nothrow move constructible")
      {
        static constexpr auto size = 5u;
        static constexpr auto new_size = 10u;

        auto queue = bit::stl::circular_queue<moveable>{size};

        for( auto i = 0u; i < size; ++i ) {
          queue.emplace(i);
        }
        auto old = queue;

        moveable::move_calls = 0;
        moveable::copy_calls = 0;

        queue.resize(new_size);

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
          REQUIRE( std::equal(old.begin(),old.end(),queue.begin(),queue.end()) );
        }
        SECTION("Capacity is new_size")
        {
          REQUIRE( queue.capacity() == new_size );
        }
      }
    }
  }
}
