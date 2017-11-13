/**
 * \file expected.test.cpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#include <bit/stl/utilities/expected.hpp>

#include <catch.hpp>

#include <system_error>

//=============================================================================
// expected<T,E>
//=============================================================================

//-----------------------------------------------------------------------------
// Constructors / Assignment
//-----------------------------------------------------------------------------

TEST_CASE("expected::expected()")
{
  auto expect = bit::stl::expected<int>();

  SECTION("Default-constructs underlying type T")
  {
    REQUIRE( expect.has_value() );
  }
}

//-----------------------------------------------------------------------------

TEST_CASE("expected::expected( const expected& )")
{
  SECTION("Contains Value")
  {
    auto expect = bit::stl::expected<int>(5);
    auto copy = expect;

    SECTION("Copy contains same value")
    {
      REQUIRE( *copy == *expect );
    }
    SECTION("Calls underlying value's copy constructor")
    {
      // TODO: Check that the copy constructor is called
    }
    SECTION("Copied expected contains a value")
    {
      REQUIRE( copy.has_value() );
    }
  }

  SECTION("Contains Error")
  {
    auto unexpect = bit::stl::make_unexpected<std::error_condition>( std::errc::address_family_not_supported );
    auto expect = bit::stl::expected<int>( unexpect );
    auto copy = expect;

    SECTION("Copy contains same error")
    {
      REQUIRE( copy.error() == expect.error() );
    }
    SECTION("Calls underlying error's copy constructor")
    {
      // TODO: Check that the copy constructor is called
    }
    SECTION("Copied expected contains an error")
    {
      REQUIRE( copy.has_error() );
    }
  }

  SECTION("Contains Nothing")
  {
    // TODO: Trigger valueless_by_exception and ensure state copies over
  }
}

//-----------------------------------------------------------------------------

TEST_CASE("expected::expected( expected&& )")
{
  SECTION("Contains Value")
  {
    auto expect = bit::stl::expected<int>(5);
    auto copy = expect;
    auto move = std::move(expect);

    SECTION("Copy contains same value")
    {
      REQUIRE( *copy == *move );
    }
    SECTION("Calls underlying value's move constructor")
    {
      // TODO: Check that the move constructor is called
    }
    SECTION("Moved expected contains a value")
    {
      REQUIRE( move.has_value() );
    }
  }

  SECTION("Contains Error")
  {
    auto unexpect = bit::stl::make_unexpected<std::error_condition>( std::errc::address_family_not_supported );
    auto expect = bit::stl::expected<int>( unexpect );
    auto copy = expect;
    auto move = std::move(expect);

    SECTION("Copy contains same error")
    {
      REQUIRE( copy.error() == move.error() );
    }
    SECTION("Calls underlying error's move constructor")
    {
      // TODO Check that the move constructor is called
    }
    SECTION("Moved expected contains an error")
    {
      REQUIRE( move.has_error() );
    }
  }

  SECTION("Contains Nothing")
  {
    // TODO: Trigger valueless_by_exception and ensure state copies over
  }
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
