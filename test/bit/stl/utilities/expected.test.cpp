/**
 * \file expected.test.cpp
 *
 * \brief Test cases for the bit::stl::stl::expected type
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#include <bit/stl/utilities/expected.hpp>

#include <catch.hpp>

#include <string>

//----------------------------------------------------------------------------
// Helpers
//----------------------------------------------------------------------------

namespace {

  struct valueless_exception
  {
    valueless_exception(){}
    valueless_exception(int){ throw std::logic_error("logic error"); }
  };

  bit::stl::expected<int> get_exception()
  {
    try {
      throw std::logic_error("logic error");
    } catch (...) {
      return bit::stl::expected<int>( bit::stl::in_place_type<std::exception_ptr> );
    }
    return 42; // this case never gets hit
  }

  bit::stl::expected<valueless_exception> get_valueless_by_exception()
  {
    auto expect = bit::stl::expected<valueless_exception>();
    try {
      expect.emplace(0);
    } catch (...) {}
    return expect;
  }

}

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

TEST_CASE("expected::expected()", "[ctor]")
{
  auto expect = bit::stl::expected<std::string>();

  SECTION("Default constructs an expected")
  {
    SECTION("Constructs default constructed input")
    {
      REQUIRE( *expect == std::string() );
    }

    SECTION("Contains a value")
    {
      REQUIRE( expect.has_value() );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("expected::expected( in_place_type<std::exception_ptr> )", "[ctor]")
{
  auto expect = get_exception();

  SECTION("Constructs an expected with an exception")
  {
    SECTION("Constructs same exception as current exception")
    {
      REQUIRE( expect.has_exception<std::logic_error>() );
    }

    SECTION("Contains an exception")
    {
      REQUIRE( expect.has_exception() );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("expected::expected( in_place_type<Exception>, Args&&... )", "[ctor]")
{
  auto expect = bit::stl::expected<std::string>( bit::stl::in_place_type<std::logic_error>, "test" );

  SECTION("Constructs an expected with an exception")
  {
    SECTION("Constructs same exception as input")
    {
      REQUIRE( expect.has_exception<std::logic_error>() );
    }

    SECTION("Contains an exception")
    {
      REQUIRE( expect.has_exception() );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("expected::expected( in_place_type<Exception>, std::initialzier_list<U>, Args&&... )", "[ctor]")
{


  SECTION("Constructs an expected with an exception")
  {
    SECTION("Constructs same exception as input")
    {
      // REQUIRE( expect.has_exception<std::logic_error>() );
    }

    SECTION("Contains an exception")
    {
      // REQUIRE( expect.has_exception() );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("expected::expected( in_place_t, Args&&... )", "[ctor]")
{
  auto expect = bit::stl::expected<std::string>( bit::stl::in_place, "test test", 4 );

  SECTION("Constructs an expected from the supplied arguments")
  {
    SECTION("Constructs same value as direct constructor call")
    {
      REQUIRE( expect.value() == std::string("test test", 4) );
    }

    SECTION("Contains a value")
    {
      REQUIRE( expect.has_value() );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("expected::expected( in_place_t, std::initialzier_list<U>, Args&&... )", "[ctor]")
{


  SECTION("Constructs an expected from the supplied arguments")
  {
    SECTION("Constructs same value as direct constructor call")
    {
      // REQUIRE( expect.value() == std::string("test test", 4) );
    }

    SECTION("Contains a value")
    {
      // REQUIRE( expect.has_value() );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("expected::expected( const T& )", "[ctor]")
{
  auto value  = std::string("Hello World");
  auto expect = bit::stl::expected<std::string>(value);

  SECTION("Constructs an expected from the supplied arguments")
  {
    SECTION("Constructs same value as input")
    {
      REQUIRE( expect.value() == value );
    }

    SECTION("Contains a value")
    {
      REQUIRE( expect.has_value() );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("expected::expected( T&& )", "[ctor]")
{
  auto value  = std::string("Hello World");
  auto input  = value;
  auto expect = bit::stl::expected<std::string>( std::move(input) );

  SECTION("Constructs an expected from the supplied arguments")
  {
    SECTION("Constructs same value as input")
    {
      REQUIRE( expect.value() == value );
    }

    SECTION("Contains a value")
    {
      REQUIRE( expect.has_value() );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("expected::expected( const expected& )", "[ctor]")
{

  SECTION("Copy constructs an expected containing an exception")
  {
    auto except = get_exception();
    auto copy   = except;

    SECTION("Constructs same value as input")
    {
      REQUIRE( copy.has_exception<std::logic_error>() );
    }

    SECTION("Contains an exception")
    {
      REQUIRE( copy.has_exception() );
    }
  }

  SECTION("Copy constructs an expected containing a value")
  {
    auto except = bit::stl::expected<int>(5);
    auto copy   = except;

    SECTION("Constructs same value as input")
    {
      REQUIRE( copy.value() == except.value() );
    }

    SECTION("Contains an exception")
    {
      REQUIRE( copy.has_value() );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("expected::expected( expected&& )", "[ctor]")
{

  SECTION("Move constructs an expected containing an exception")
  {
    auto except = get_exception();
    auto input  = except;
    auto move   = std::move(input);

    SECTION("Constructs same value as input")
    {
      REQUIRE( move.has_exception<std::logic_error>() );
    }

    SECTION("Contains an exception")
    {
      REQUIRE( move.has_exception() );
    }
  }

  SECTION("Move constructs an expected containing a value")
  {
    auto except = bit::stl::expected<int>(5);
    auto input  = except;
    auto move   = std::move(input);

    SECTION("Constructs same value as input")
    {
      REQUIRE( move.value() == except.value() );
    }

    SECTION("Contains an exception")
    {
      REQUIRE( move.has_value() );
    }
  }
}

//----------------------------------------------------------------------------
// Assignment
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

TEST_CASE("expected::operator bool() const noexcept")
{
  SECTION("expected contains a value")
  {
    SECTION("returns true")
    {
      auto expect = bit::stl::expected<int>(5);

      REQUIRE( expect );
    }
  }

  SECTION("expected contains an exception")
  {
    SECTION("returns false")
    {
      auto expect = get_exception();

      REQUIRE_FALSE( expect );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("expected::has_value() const noexcept")
{
  SECTION("expected contains a value")
  {
    SECTION("returns true")
    {
      auto expect = bit::stl::expected<int>(5);

      REQUIRE( expect.has_value() );
    }
  }

  SECTION("expected contains an exception")
  {
    SECTION("returns false")
    {
      auto expect = get_exception();

      REQUIRE_FALSE( expect.has_value() );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("expected::has_exception() const noexcept")
{
  SECTION("expected contains a value")
  {
    SECTION("returns false")
    {
      auto expect = bit::stl::expected<int>(5);

      REQUIRE_FALSE( expect.has_exception() );
    }
  }

  SECTION("expected contains an exception")
  {
    SECTION("returns true")
    {
      auto expect = get_exception();

      REQUIRE( expect.has_exception() );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("expected::has_exception<Exception>() const noexcept")
{
  SECTION("expected contains a value")
  {
    SECTION("Returns false")
    {
      auto expect = bit::stl::expected<int>(5);

      REQUIRE_FALSE( expect.has_exception<std::exception>() );
    }
  }

  SECTION("expected contains an exception")
  {
    SECTION("is same exception returns true")
    {
      auto expect = get_exception();

      REQUIRE( expect.has_exception<std::logic_error>() );
    }

    SECTION("is hierarchal parent exception returns true")
    {
      auto expect = get_exception();

      REQUIRE( expect.has_exception<std::exception>() );
    }

    SECTION("is unrelated exception returns false")
    {
      auto expect = get_exception();

      REQUIRE_FALSE( expect.has_exception<std::runtime_error>() );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("expected::valueless_by_exception() const noexcept")
{
  SECTION("expected contains a value")
  {
    auto expect = bit::stl::expected<std::string>("hello world");

    SECTION("returns false")
    {
      REQUIRE_FALSE( expect.valueless_by_exception() );
    }
  }

  SECTION("expected contains an exception")
  {
    auto expect = get_exception();

    SECTION("returns false")
    {
      REQUIRE_FALSE( expect.valueless_by_exception() );
    }
  }

  SECTION("expected is valueluess")
  {
    auto expect = get_valueless_by_exception();

    SECTION("returns true")
    {
      REQUIRE( expect.valueless_by_exception() );
    }
  }

}

//----------------------------------------------------------------------------

TEST_CASE("expected::value() &")
{
  SECTION("expected contains value")
  {
    auto expect = bit::stl::expected<std::string>("Hello World");

    SECTION("returns value")
    {
      REQUIRE( expect.value() == std::string("Hello World") );
    }
  }

  SECTION("expected contains exception")
  {
    auto expect = get_exception();

    SECTION("throws stored exception")
    {
      REQUIRE_THROWS_AS( expect.value(), std::logic_error& );
    }
  }

  SECTION("expected is valueless_by_exception")
  {
    auto expect = get_valueless_by_exception();

    SECTION("throws bit::stl::bad_expected_access")
    {
      REQUIRE_THROWS_AS( expect.value(), bit::stl::bad_expected_access& );
    }
  }
}
