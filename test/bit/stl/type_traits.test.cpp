/**
 * \file type_traits.cpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#include <bit/stl/type_traits.hpp>

#include <vector>
#include <map>
#include <array>

#include <catch.hpp>

namespace {

  struct input_iterator
  {
    using value_type        = int;
    using pointer           = int*;
    using reference         = int&;
    using iterator_category = std::input_iterator_tag;
    using difference_type   = std::ptrdiff_t;

    input_iterator& operator++();
    input_iterator operator++(int);
    int& operator*();
    int* operator->();

    bool operator==(input_iterator const&);
    bool operator!=(input_iterator const&);
  };

  using forward_iterator = input_iterator;
}

//============================================================================
// Type Composite
//============================================================================

//============================================================================
// Type Function
//============================================================================

//============================================================================
// Type Container
//============================================================================

TEST_CASE("bit::stl::is_iterator<T>")
{
  SECTION("Non-iterator T resolves false")
  {
    REQUIRE_FALSE( (bit::stl::is_iterator<int>::value) );
  }

  SECTION("Input Iterator T resolves true")
  {
    using iterator = input_iterator;

    REQUIRE( (bit::stl::is_iterator<iterator>::value) );
  }

  SECTION("Forward Iterator T resolves true")
  {
    using iterator = forward_iterator;

    REQUIRE( (bit::stl::is_iterator<iterator>::value) );
  }

  SECTION("Bidirectional Iterator T resolves true")
  {
    using iterator = typename std::map<int,int>::iterator;

    REQUIRE( (bit::stl::is_iterator<iterator>::value) );
  }

  SECTION("Random-access Iterator T resolves true")
  {
    using iterator = typename std::array<int,5>::iterator;

    REQUIRE( (bit::stl::is_iterator<iterator>::value) );
  }

  SECTION("Output Iterator T resolves true")
  {
    using iterator = std::back_insert_iterator<std::vector<int>>;

    REQUIRE( (bit::stl::is_iterator<iterator>::value) );
  }

  SECTION("Pointer resolves true")
  {
    using iterator = int*;

    REQUIRE( (bit::stl::is_iterator<iterator>::value) );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::is_input_iterator<T>")
{
  SECTION("Non-iterator T resolves false")
  {
    REQUIRE_FALSE( (bit::stl::is_input_iterator<int>::value) );
  }

  SECTION("Input Iterator T resolves true")
  {
    using iterator = input_iterator;

    REQUIRE( (bit::stl::is_input_iterator<iterator>::value) );
  }

  SECTION("Forward Iterator T resolves true")
  {
    using iterator = forward_iterator;

    REQUIRE( (bit::stl::is_input_iterator<iterator>::value) );
  }

  SECTION("Bidirectional Iterator T resolves true")
  {
    using iterator = typename std::map<int,int>::iterator;

    REQUIRE( (bit::stl::is_input_iterator<iterator>::value) );
  }

  SECTION("Random-access Iterator T resolves true")
  {
    using iterator = typename std::array<int,5>::iterator;

    REQUIRE( (bit::stl::is_input_iterator<iterator>::value) );
  }

  SECTION("Output Iterator T resolves false")
  {
    using iterator = std::back_insert_iterator<std::vector<int>>;

    REQUIRE_FALSE( (bit::stl::is_input_iterator<iterator>::value) );
  }

  SECTION("Pointer resolves true")
  {
    using iterator = int*;

    REQUIRE( (bit::stl::is_input_iterator<iterator>::value) );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::is_forward_iterator")
{
  SECTION("Non-iterator T resolves false")
  {
    REQUIRE_FALSE( (bit::stl::is_forward_iterator<int>::value) );
  }

  SECTION("Input Iterator T resolves true")
  {
    using iterator = input_iterator;

    // The only difference between InputIterator and ForwardIterator, is semantics

    REQUIRE( (bit::stl::is_forward_iterator<iterator>::value) );
  }

  SECTION("Forward Iterator T resolves true")
  {
    using iterator = forward_iterator;

    REQUIRE( (bit::stl::is_forward_iterator<iterator>::value) );
  }

  SECTION("Bidirectional Iterator T resolves true")
  {
    using iterator = typename std::map<int,int>::iterator;

    REQUIRE( (bit::stl::is_forward_iterator<iterator>::value) );
  }

  SECTION("Random-access Iterator T resolves true")
  {
    using iterator = typename std::array<int,5>::iterator;

    REQUIRE( (bit::stl::is_forward_iterator<iterator>::value) );
  }

  SECTION("Output Iterator T resolves false")
  {
    using iterator = std::back_insert_iterator<std::vector<int>>;

    REQUIRE_FALSE( (bit::stl::is_forward_iterator<iterator>::value) );
  }

  SECTION("Pointer resolves true")
  {
    using iterator = int*;

    REQUIRE( (bit::stl::is_forward_iterator<iterator>::value) );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::is_bidirectional_iterator")
{
  SECTION("Non-iterator T resolves false")
  {
    REQUIRE_FALSE( (bit::stl::is_bidirectional_iterator<int>::value) );
  }

  SECTION("Input Iterator T resolves false")
  {
    using iterator = input_iterator;

    REQUIRE_FALSE( (bit::stl::is_bidirectional_iterator<iterator>::value) );
  }

  SECTION("Forward Iterator T resolves false")
  {
    using iterator = forward_iterator;

    REQUIRE_FALSE( (bit::stl::is_bidirectional_iterator<iterator>::value) );
  }

  SECTION("Bidirectional Iterator T resolves true")
  {
    using iterator = typename std::map<int,int>::iterator;

    REQUIRE( (bit::stl::is_bidirectional_iterator<iterator>::value) );
  }

  SECTION("Random-access Iterator T resolves true")
  {
    using iterator = typename std::array<int,5>::iterator;

    REQUIRE( (bit::stl::is_bidirectional_iterator<iterator>::value) );
  }

  SECTION("Output Iterator T resolves false")
  {
    using iterator = std::back_insert_iterator<std::vector<int>>;

    REQUIRE_FALSE( (bit::stl::is_bidirectional_iterator<iterator>::value) );
  }

  SECTION("Pointer resolves true")
  {
    using iterator = int*;

    REQUIRE( (bit::stl::is_bidirectional_iterator<iterator>::value) );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::is_random_access_iterator")
{
  SECTION("Non-iterator T resolves false")
  {
    REQUIRE_FALSE( (bit::stl::is_random_access_iterator<int>::value) );
  }

  SECTION("Input Iterator T resolves false")
  {
    using iterator = input_iterator;

    REQUIRE_FALSE( (bit::stl::is_random_access_iterator<iterator>::value) );
  }

  SECTION("Forward Iterator T resolves false")
  {
    using iterator = forward_iterator;

    REQUIRE_FALSE( (bit::stl::is_random_access_iterator<iterator>::value) );
  }

  SECTION("Bidirectional Iterator T resolves false")
  {
    using iterator = typename std::map<int,int>::iterator;

    REQUIRE_FALSE( (bit::stl::is_random_access_iterator<iterator>::value) );
  }

  SECTION("Random-access Iterator T resolves true")
  {
    using iterator = typename std::array<int,5>::iterator;

    REQUIRE( (bit::stl::is_random_access_iterator<iterator>::value) );
  }

  SECTION("Output Iterator T resolves false")
  {
    using iterator = std::back_insert_iterator<std::vector<int>>;

    REQUIRE_FALSE( (bit::stl::is_random_access_iterator<iterator>::value) );
  }

  SECTION("Pointer resolves true")
  {
    using iterator = int*;

    REQUIRE( (bit::stl::is_random_access_iterator<iterator>::value) );
  }
}

//============================================================================
// Type Transformations
//============================================================================

TEST_CASE("bit::stl::unqualified<T>")
{
  SECTION("Unqualified T")
  {
    SECTION("Resolves T")
    {
      REQUIRE( (std::is_same<bit::stl::unqualified_t<int>,int>::value) );
    }
  }

  SECTION("CV-qualified")
  {
    SECTION("Const-qualified T resolves")
    {
      REQUIRE( (std::is_same<bit::stl::unqualified_t<const int>,int>::value) );
    }

    SECTION("Volatile-qualified T resolves")
    {
      REQUIRE( (std::is_same<bit::stl::unqualified_t<volatile int>,int>::value) );
    }

    SECTION("CV-qualified T resolves")
    {
      REQUIRE( (std::is_same<bit::stl::unqualified_t<const volatile int>,int>::value) );
    }
  }

  SECTION("Pointer-qualified")
  {
    SECTION("T* resolves T")
    {
      REQUIRE( (std::is_same<bit::stl::unqualified_t<int*>,int>::value) );
    }

    SECTION("T** resolves T")
    {
      REQUIRE( (std::is_same<bit::stl::unqualified_t<int**>,int>::value) );
    }
  }

  SECTION("Reference-qualified")
  {
    SECTION("T& resolves T")
    {
      REQUIRE( (std::is_same<bit::stl::unqualified_t<int&>,int>::value) );
    }

    SECTION("T&& resolves T")
    {
      REQUIRE( (std::is_same<bit::stl::unqualified_t<int&&>,int>::value) );
    }
  }

  SECTION("Compound-qualified")
  {
    SECTION("Compound-qualified type resolves T")
    {
      REQUIRE( (std::is_same<bit::stl::unqualified_t<const int* const**volatile&>,int>::value) );
    }
  }
}

//============================================================================
// Type Relationship
//============================================================================
