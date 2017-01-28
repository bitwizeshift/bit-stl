/**
 * \file delegate.test.cpp
 *
 * \brief Unit tests for #bit::stl::delegate
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#include <bit/stl/delegate.hpp>

#include "../../catch.hpp"

namespace {

  //----------------------------------------------------------------------------
  // Dummy Classes
  //----------------------------------------------------------------------------

  int dummy_function(int a)
  {
    return a + 1;
  }

  //----------------------------------------------------------------------------

  class DummyClass
  {
  public:
    DummyClass( int value ) : m_value(value){}

    int non_const_function( int a ) { return m_value + a; }
    int const_function( int a ) const { return m_value + a; }

    int m_value;
  };

} // anonymous namespace

//----------------------------------------------------------------------------
// Test Cases
//----------------------------------------------------------------------------

TEST_CASE("delegate()", "[ctor]")
{
  SECTION("delegate()")
  {
    SECTION("Constructs unbound delegate")
    {
      bit::stl::delegate<int(int)> delegate;

      REQUIRE_FALSE( delegate.is_bound() );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("delegate::bind()", "[member function]")
{
  SECTION("Binds free function")
  {
    bit::stl::delegate<int(int)> delegate;

    delegate.bind<dummy_function>();
    REQUIRE( delegate.is_bound() );
  }
}

TEST_CASE("delegate::bind( T* )", "[member function]")
{
  SECTION("Binds non-const member function")
  {
    bit::stl::delegate<int(int)> delegate;
    DummyClass              dummy(10);

    delegate.bind<DummyClass,&DummyClass::non_const_function>(&dummy);
    REQUIRE( delegate.is_bound() );
  }

  SECTION("Binds const member function")
  {
    bit::stl::delegate<int(int)> delegate;
    const DummyClass        dummy(10);

    delegate.bind<DummyClass,&DummyClass::const_function>(&dummy);
    REQUIRE( delegate.is_bound() );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("delegate::is_bound()", "[member function]")
{
  SECTION("Returns false when not bound")
  {
    bit::stl::delegate<int(int)> delegate;

    REQUIRE_FALSE( delegate.is_bound() );
  }

  SECTION("Returns true when bound")
  {
    bit::stl::delegate<int(int)> delegate;

    delegate.bind<dummy_function>();

    REQUIRE( delegate.is_bound() );
  }
}

TEST_CASE("delegate::operator bool", "[member function]")
{
  SECTION("Is explicitly convertible to false when not bound")
  {
    bit::stl::delegate<int(int)> delegate;

    REQUIRE_FALSE( static_cast<bool>(delegate) );
  }

  SECTION("Is explicitly convertible to true when bound")
  {
    bit::stl::delegate<int(int)> delegate;

    delegate.bind<dummy_function>();

    REQUIRE( static_cast<bool>(delegate) );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("delegate::invoke(Args&&...)", "[member function]")
{
  SECTION("Invokes bound free function")
  {
    bit::stl::delegate<int(int)> delegate;

    delegate.bind<dummy_function>();

    REQUIRE( delegate.invoke(5) == 6 );
  }

  SECTION("Invokes non-const member function")
  {
    bit::stl::delegate<int(int)> delegate;
    DummyClass              dummy(10);

    delegate.bind<DummyClass,&DummyClass::non_const_function>(&dummy);

    REQUIRE( delegate.invoke(5) == 15 );
  }

  SECTION("Invokes const member function")
  {
    bit::stl::delegate<int(int)> delegate;
    const DummyClass        dummy(10);

    delegate.bind<DummyClass,&DummyClass::const_function>(&dummy);

    REQUIRE( delegate.invoke(5) == 15 );
  }
}

