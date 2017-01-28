/**
 * \file tribool.test.cpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#include "../../catch.hpp"

#include <bit/stl/tribool.hpp>

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------

TEST_CASE("tribool::tribool()")
{
  auto t = bit::stl::tribool();

  SECTION("Constructor creates indeterminate tribool")
  {
    REQUIRE( bit::stl::indeterminate( t ) );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("tribool::tribool( bool t )")
{
  SECTION("Constructor accepting true constructs true tribool")
  {
    bit::stl::tribool t = true;

    REQUIRE( t == true );
  }

  SECTION("Constructor accepting false constructs false tribool")
  {
    bit::stl::tribool t = false;

    REQUIRE( t == false );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("tribool::tribool( indeterminate_t )")
{
  SECTION("Constructor accepting indeterminate constructs indeterminate tribool")
  {
    bit::stl::tribool t = bit::stl::indeterminate;

    REQUIRE( (t == bit::stl::indeterminate) );
  }
}

//----------------------------------------------------------------------------
// Boolean Operators
//----------------------------------------------------------------------------

TEST_CASE("tribool::operator bool()")
{
  SECTION("false returns false")
  {
    auto result = bit::stl::tribool(false);

    REQUIRE_FALSE( bool(result) );
  }

  SECTION("indeterminate returns false")
  {
    auto result = bit::stl::tribool(bit::stl::indeterminate);

    REQUIRE_FALSE( bool(result) );
  }

  SECTION("true returns true")
  {
    auto result = bit::stl::tribool(true);

    REQUIRE( bool(result) );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("tribool::operator !()")
{
  SECTION("false returns true")
  {
    auto result = bit::stl::tribool(false);

    REQUIRE( !result );
  }

  SECTION("indeterminate returns false")
  {
    auto result = bit::stl::tribool(bit::stl::indeterminate);

    REQUIRE_FALSE( !result );
  }

  SECTION("true returns false")
  {
    auto result = bit::stl::tribool(true);

    REQUIRE_FALSE( !result );
  }
}

//----------------------------------------------------------------------------
// Binary Boolean Operators
//----------------------------------------------------------------------------

TEST_CASE("tribool operator && ( const tribool&, const tribool& )")
{
  SECTION("false && false returns false")
  {
    auto result = bit::stl::tribool(false) && bit::stl::tribool(false);

    REQUIRE( result == false );
  }

  SECTION("false && true returns false")
  {
    auto result = bit::stl::tribool(false) && bit::stl::tribool(true);

    REQUIRE( result == false );
  }

  SECTION("true && true returns true")
  {
    auto result = bit::stl::tribool(true) && bit::stl::tribool(true);

    REQUIRE( result == true );
  }

  SECTION("false && indeterminate returns indeterminate")
  {
    auto result = bit::stl::tribool(false) && bit::stl::tribool(bit::stl::indeterminate);

    REQUIRE( (result == bit::stl::indeterminate) );
  }

  SECTION("true && indeterminate returns indeterminate")
  {
    auto result = bit::stl::tribool(true) && bit::stl::tribool(bit::stl::indeterminate);

    REQUIRE( (result == bit::stl::indeterminate) );
  }

  SECTION("indeterminate && indeterminate returns indeterminate")
  {
    auto result = bit::stl::tribool(bit::stl::indeterminate) && bit::stl::tribool(bit::stl::indeterminate);

    REQUIRE( (result == bit::stl::indeterminate) );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("tribool operator || ( const tribool&, const tribool& )")
{
  SECTION("false || false returns false")
  {
    auto result = bit::stl::tribool(false) || bit::stl::tribool(false);

    REQUIRE( result == false );
  }

  SECTION("false || true returns true")
  {
    auto result = bit::stl::tribool(false) || bit::stl::tribool(true);

    REQUIRE( result == true );
  }

  SECTION("true || true returns true")
  {
    auto result = bit::stl::tribool(true) || bit::stl::tribool(true);

    REQUIRE( result == true );
  }

  SECTION("false || indeterminate returns indeterminate")
  {
    auto result = bit::stl::tribool(false) || bit::stl::tribool(bit::stl::indeterminate);

    REQUIRE( (result == bit::stl::indeterminate) );
  }

  SECTION("true || indeterminate returns true")
  {
    auto result = bit::stl::tribool(true) || bit::stl::tribool(bit::stl::indeterminate);

    REQUIRE( (result == true) );
  }

  SECTION("indeterminate || indeterminate returns indeterminate")
  {
    auto result = bit::stl::tribool(bit::stl::indeterminate) || bit::stl::tribool(bit::stl::indeterminate);

    REQUIRE( (result == bit::stl::indeterminate) );
  }
}
