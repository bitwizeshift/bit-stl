/**
 * \file array_view.test.cpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#include <bit/stl/containers/array_view.hpp>

#include <vector>

#include <catch.hpp>

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

TEST_CASE("array_view::array_view()")
{
  auto view = bit::stl::array_view<int>();

  SECTION("Default constructs a span")
  {
    SECTION("Constructs an empty array view")
    {
      REQUIRE( view.empty() );
    }

    SECTION("Contains 0 elements")
    {
      REQUIRE( view.size() == 0 );
    }

    SECTION("Data points to null")
    {
      REQUIRE( view.data() == nullptr );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("array_view::array_view( value_type (&)[N] ) ")
{
  int array[] = {1,2,3,4,5};
  auto view = bit::stl::array_view<int>(array);

  SECTION("Constructs a view out of raw C-style array")
  {
    SECTION("Constructs a non-empty view")
    {
      REQUIRE_FALSE( view.empty() );
    }

    SECTION("Contains 5 elements")
    {
      REQUIRE( view.size() == 5 );
    }

    SECTION("Data points to original array")
    {
      REQUIRE( view.data() == array );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("array_view::array_view( const value_type (&)[N] ) ")
{
  const int array[] = {1,2,3,4,5};
  auto view = bit::stl::array_view<int>(array);

  SECTION("Constructs a view out of raw C-style array")
  {
    SECTION("Constructs a non-empty view")
    {
      REQUIRE_FALSE( view.empty() );
    }

    SECTION("Contains 5 elements")
    {
      REQUIRE( view.size() == 5 );
    }

    SECTION("Data points to original array")
    {
      REQUIRE( view.data() == array );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("array_view::array_view( const Container& )")
{
  std::vector<int> vec = {1,2,3,4,5};
  auto view = bit::stl::array_view<int>(vec);

  SECTION("Constructs a view out of vector")
  {
    SECTION("Constructs a non-empty view")
    {
      REQUIRE_FALSE( view.empty() );
    }

    SECTION("Contains 5 elements")
    {
      REQUIRE( view.size() == 5 );
    }

    SECTION("Data points to original array")
    {
      REQUIRE( view.data() == std::addressof(vec[0]) );
    }
  }
}
