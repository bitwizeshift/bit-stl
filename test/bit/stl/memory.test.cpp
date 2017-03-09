/**
 * \file memory.test.cpp
 *
 * \brief Tests cases for the memory module
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#include <bit/stl/memory.hpp>

#include <catch.hpp>

//----------------------------------------------------------------------------
// Pointer Manipulation
//----------------------------------------------------------------------------

TEST_CASE("bit::stl::dereference( T* )")
{
  static const auto deref_value = 42;

  SECTION("Dereferences single-indirection pointer")
  {
    auto value = deref_value;
    auto p1    = &value;

    REQUIRE( bit::stl::dereference( p1 ) == deref_value );
  }

  SECTION("Dereferences double-indirection pointer")
  {
    auto value = deref_value;
    auto p1    = &value;
    auto p2    = &p1;

    REQUIRE( bit::stl::dereference( p2 ) == deref_value );
  }

  SECTION("Dereferences triple-indirection pointer")
  {
    auto value = deref_value;
    auto p1    = &value;
    auto p2    = &p1;
    auto p3    = &p2;

    REQUIRE( bit::stl::dereference( p3 ) == deref_value );
  }

  SECTION("Dereferences quadruple-indirection pointer")
  {
    auto value = deref_value;
    auto p1    = &value;
    auto p2    = &p1;
    auto p3    = &p2;
    auto p4    = &p3;

    REQUIRE( bit::stl::dereference( p4 ) == deref_value );
  }
}

//------------------------------------------------------------------------

TEST_CASE("bit::stl::to_address( const void* ptr )")
{
  SECTION("Converts raw pointers into an integral address")
  {
    auto address = static_cast<std::uintptr_t>(0xdeadbeef);
    auto ptr     = reinterpret_cast<void*>(address);

    REQUIRE( bit::stl::to_address(ptr) == address );
  }

}

//------------------------------------------------------------------------

TEST_CASE("bit::stl::from_address( std::uintptr_t address )")
{
  SECTION("Converts integral address to raw pointers")
  {
    auto address = static_cast<std::uintptr_t>(0xdeadbeef);
    auto ptr     = reinterpret_cast<void*>(address);

    REQUIRE( bit::stl::from_address(address) == ptr );
  }
}

//------------------------------------------------------------------------

TEST_CASE("bit::stl::pointer_distance( const void*, const void* )")
{
  auto a_ptr = bit::stl::from_address(0x1000);
  auto b_ptr = bit::stl::from_address(0x2000);

  SECTION("Retrieves the distance between two pointers")
  {
    REQUIRE( bit::stl::pointer_distance(a_ptr,b_ptr) == 0x1000 );
  }

  SECTION("Retrieves absolute distance between two pointers")
  {
    REQUIRE( bit::stl::pointer_distance(b_ptr,a_ptr) == 0x1000 );
  }
}

//------------------------------------------------------------------------

TEST_CASE("bit::stl::pointer_difference( const void*, const void* )")
{
  auto a_ptr = bit::stl::from_address(0x1000);
  auto b_ptr = bit::stl::from_address(0x2000);

  SECTION("Retrieves positive difference between two pointers")
  {
    REQUIRE( bit::stl::pointer_difference(b_ptr,a_ptr) == 0x1000 );
  }
  SECTION("Retrieves negative difference between two pointers")
  {
    REQUIRE( bit::stl::pointer_difference(a_ptr,b_ptr) == -0x1000 );
  }
}

//------------------------------------------------------------------------

TEST_CASE("bit::stl::in_region( const void*, const void*, const void* )")
{
  auto first = bit::stl::from_address(0x1000);
  auto last  = bit::stl::from_address(0x2000);

  SECTION("Address in range")
  {
    SECTION("Pointer in range returns true")
    {
      auto ptr = bit::stl::from_address(0x1500);

      REQUIRE( bit::stl::in_region( ptr, first, last ) );
    }
  }

  SECTION("Address out of range")
  {
    SECTION("Pointer below pointer range returns false")
    {
      auto ptr = bit::stl::from_address(0x0500);

      REQUIRE_FALSE( bit::stl::in_region( ptr, first, last ) );
    }

    SECTION("Pointer above pointer range returns false")
    {
      auto ptr = bit::stl::from_address(0x2500);

      REQUIRE_FALSE( bit::stl::in_region( ptr, first, last ) );
    }
  }

  SECTION("Address on boundary")
  {
    SECTION("Pointer on start boundary returns true")
    {
      auto ptr = first;

      REQUIRE( bit::stl::in_region( ptr, first, last ) );
    }

    SECTION("Pointer on end boundary returns false")
    {
      auto ptr = last;

      REQUIRE_FALSE( bit::stl::in_region( ptr, first, last ) );
    }
  }
}

//------------------------------------------------------------------------
// Pointer Alignment
//------------------------------------------------------------------------

TEST_CASE("bit::stl::align_forward( void*, std::size_t, std::size_t )")
{
  SECTION("Doesn't align on 1 alignment")
  {
    auto ptr = bit::stl::from_address(0x1001);
    auto adjust = std::size_t{};

    std::tie(ptr,adjust) = bit::stl::align_forward(ptr,1);

    REQUIRE( ptr == bit::stl::from_address(0x1001) );
  }

  SECTION("Doesn't align aligned pointer")
  {
    auto original_ptr = bit::stl::from_address(0x1000);
    auto ptr          = original_ptr;
    auto adjust       = std::size_t{};

    std::tie(ptr,adjust) = bit::stl::align_forward(ptr,8);

    SECTION("Pointer doesn't change")
    {
      REQUIRE( ptr == original_ptr );
    }

    SECTION("Number of bytes offset is 0")
    {
      REQUIRE( adjust == 0 );
    }
  }

  SECTION("Aligns unaligned pointer")
  {
    auto original_ptr = bit::stl::from_address(0x1001);
    auto ptr          = original_ptr;
    auto adjust       = std::size_t{};

    std::tie(ptr,adjust) = bit::stl::align_forward(ptr,8);

    SECTION("Aligns to the specified byte-boundary")
    {
      REQUIRE( ptr == bit::stl::from_address(0x1008) );
    }

    SECTION("Aligns the pointer forward")
    {
      REQUIRE( ptr > original_ptr );
    }

    SECTION("Returns number of bytes offset")
    {
      REQUIRE( adjust == 7 );
    }
  }

  SECTION("Aligns unaligned pointer with an offset")
  {
    auto original_ptr = bit::stl::from_address(0x1000);
    auto ptr          = original_ptr;
    auto adjust       = std::size_t{};

    std::tie(ptr,adjust) = bit::stl::align_forward(ptr,8,1);

    SECTION("Aligns to the specified byte-boundary")
    {
      REQUIRE( ptr == bit::stl::from_address(0x1007) );
    }

    SECTION("Aligns the pointer forward")
    {
      REQUIRE( ptr > original_ptr );
    }

    SECTION("Returns the number of bytes offset")
    {
      REQUIRE( adjust == 7 );
    }
  }

  SECTION("Doesn't align aligned pointer with an offset")
  {
    auto original_ptr = bit::stl::from_address(0x1007);
    auto ptr          = original_ptr;
    auto adjust       = std::size_t{};

    std::tie(ptr,adjust) = bit::stl::align_forward(ptr,8,1);

    SECTION("Aligns to the specified byte-boundary")
    {
      REQUIRE( ptr == original_ptr );
    }

    SECTION("Pointer doesn't change")
    {
      REQUIRE( ptr == original_ptr );
    }

    SECTION("Returns the number of bytes offset")
    {
      REQUIRE( adjust == 0 );
    }
  }
}

//------------------------------------------------------------------------

TEST_CASE("bit::stl::align_backward( void*, std::size_t, std::size_t )")
{
  SECTION("Doesn't align on 1 alignment")
   {
    auto ptr = bit::stl::from_address(0x1001);
    auto adjust = std::size_t{};

    std::tie(ptr,adjust) = bit::stl::align_backward(ptr,1);

     REQUIRE( ptr == bit::stl::from_address(0x1001) );
   }

   SECTION("Doesn't align aligned pointer")
   {
     auto original_ptr = bit::stl::from_address(0x1000);
     auto ptr          = original_ptr;
     auto adjust       = std::size_t{};

     std::tie(ptr,adjust) = bit::stl::align_backward(ptr,8);

     SECTION("Pointer doesn't change")
     {
       REQUIRE( ptr == original_ptr );
     }

     SECTION("Number of bytes offset is 0")
     {
       REQUIRE( adjust == 0 );
     }
   }

   SECTION("Aligns unaligned pointer")
   {
     auto original_ptr = bit::stl::from_address(0x1007);
     auto ptr          = original_ptr;
     auto adjust       = std::size_t{};

     std::tie(ptr,adjust) = bit::stl::align_backward(ptr,8);

     SECTION("Aligns to the specified byte-boundary")
     {
       REQUIRE( ptr == bit::stl::from_address(0x1000) );
     }

     SECTION("Aligns the pointer backward")
     {
       REQUIRE( ptr < original_ptr );
     }

     SECTION("Returns number of bytes offset")
     {
       REQUIRE( adjust == 7 );
     }
   }

   SECTION("Aligns unaligned pointer with an offset")
   {
     auto original_ptr = bit::stl::from_address(0x1007);
     auto ptr          = original_ptr;
     auto adjust       = std::size_t{};

     std::tie(ptr,adjust) = bit::stl::align_backward(ptr,8,1);

     SECTION("Aligns to the specified byte-boundary")
     {
       REQUIRE( ptr == bit::stl::from_address(0x1001) );
     }

     SECTION("Aligns the pointer backward")
     {
       REQUIRE( ptr < original_ptr );
     }

     SECTION("Returns the number of bytes offset")
     {
       REQUIRE( adjust == 6 );
     }
   }

   SECTION("Doesn't align aligned pointer with an offset")
   {
     auto original_ptr = bit::stl::from_address(0x1001);
     auto ptr          = original_ptr;
     auto adjust       = std::size_t{};

     std::tie(ptr,adjust) = bit::stl::align_backward(ptr,8,1);

     SECTION("Pointer doesn't change")
     {
       REQUIRE( ptr == original_ptr );
     }

     SECTION("Returns the number of bytes offset")
     {
       REQUIRE( adjust == 0 );
     }
   }
}

//----------------------------------------------------------------------------
// Alignment Detection
//----------------------------------------------------------------------------

TEST_CASE("bit::stl::is_aligned( const void*, std::size_t )")
{
  SECTION("Returns true if aligned")
  {
    auto ptr = bit::stl::from_address(0xdeadb8);

    REQUIRE( bit::stl::is_aligned(ptr,4) );
  }

  SECTION("Returns true if alignment is higher than tested")
  {
    auto ptr = bit::stl::from_address(0xdead20);

    REQUIRE( bit::stl::is_aligned(ptr,4) );
  }

  SECTION("Returns false if not aligned")
  {
    auto ptr = bit::stl::from_address(0xdeadb7);

    REQUIRE_FALSE( bit::stl::is_aligned(ptr,4) );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::align_of( const void* )")
{
  SECTION("Determines 1-byte alignment")
  {
    auto ptr = bit::stl::from_address(0xdeadb7);

    REQUIRE( bit::stl::align_of(ptr) == 1 );
  }

  SECTION("Determines 2-byte alignment")
  {
    auto ptr = bit::stl::from_address(0xdead02);

    REQUIRE( bit::stl::align_of(ptr) == 2 );
  }

  SECTION("Determines 4-byte alignment")
  {
    auto ptr = bit::stl::from_address(0xdead04);

    REQUIRE( bit::stl::align_of(ptr) == 4 );
  }

  SECTION("Determines 8-byte alignment")
  {
    auto ptr = bit::stl::from_address(0xdead08);

    REQUIRE( bit::stl::align_of(ptr) == 8 );
  }

  SECTION("Determines 16-byte alignment")
  {
    auto ptr = bit::stl::from_address(0xdead10);

    REQUIRE( bit::stl::align_of(ptr) == 16 );
  }
}

//----------------------------------------------------------------------------
// Uninitialized Construction
//----------------------------------------------------------------------------

// todo: test uninitialized construction functions

TEST_CASE("bit::stl::uninitialized_copy_at( void*, const T& )")
{

}

TEST_CASE("bit::stl::uninitialized_move_at( void*, T&& )")
{

}

TEST_CASE("bit::stl::uninitialized_construct_at( void*, Args&&... )")
{

}

TEST_CASE("bit::stl::uninitialized_tuple_construct_at( void*, Tuple&&... )")
{

}

TEST_CASE("bit::stl::uninitialized_construct( ForwardIterator, ForwardIterator, Args&&... )")
{

}

TEST_CASE("bit::stl::uninitialized_construct_n( ForwardIterator, Size, Args&&... )")
{

}

//------------------------------------------------------------------------
// Destruction
//------------------------------------------------------------------------

// todo Test destruction functions

TEST_CASE("bit::stl::destroy_at( T* )")
{

}

TEST_CASE("bit::stl::destroy( ForwardIterator, ForwardIterator )")
{

}

TEST_CASE("bit::stl::destroy_n( ForwardIterator, Size )")
{

}
