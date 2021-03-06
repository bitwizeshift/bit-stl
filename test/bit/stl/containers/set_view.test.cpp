/*****************************************************************************
 * \file
 * \brief todo: fill in documentation
 *****************************************************************************/

#include <bit/stl/containers/set_view.hpp>

#include <set>

#include <catch.hpp>

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

TEST_CASE("set_view::set_view()", "[ctor]")
{
  auto view = bit::stl::set_view<int>();

  SECTION("Default constructs a set_view")
  {
    SECTION("Constructs an empty set view")
    {
      REQUIRE( view.empty() );
    }

    SECTION("Contains 0 elements")
    {
      REQUIRE( view.size() == 0 );
    }
  }
}

TEST_CASE("set_view::set_view( U&& )", "[ctor]")
{
  auto set  = std::set<int>{1,2,3,4,5};
  auto view = bit::stl::set_view<int>( set );

  SECTION("Constructs a set_view from a set")
  {
    SECTION("Constructs a non-empty view")
    {
      REQUIRE_FALSE( view.empty() );
    }

    SECTION("Contains set.size() elements")
    {
      REQUIRE( view.size() == set.size() );
    }
  }
}
