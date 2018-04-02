/*****************************************************************************
 * \file
 * \brief Unit tests for #bit::stl::delegate
 *****************************************************************************/

#include <bit/stl/utilities/delegate.hpp>

#include <catch.hpp>

namespace {

  //----------------------------------------------------------------------------
  // Dummy Classes
  //----------------------------------------------------------------------------

  int plus_one(int a)
  {
    return a + 1;
  }

  //----------------------------------------------------------------------------

  class plus_n
  {
  public:
    plus_n( int value ) : m_value(value){}

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

    delegate.bind<&::plus_one>();
    REQUIRE( delegate.is_bound() );
  }
}

TEST_CASE("delegate::bind( T& )", "[member function]")
{
  SECTION("Binds non-const member function")
  {
    auto delegate = bit::stl::delegate<int(int)>{};
    auto dummy    = ::plus_n{10};

    delegate.bind<plus_n,&plus_n::non_const_function>(dummy);
    REQUIRE( delegate.is_bound() );
  }

  SECTION("Binds const member function")
  {
    auto delegate = bit::stl::delegate<int(int)>{};
    const auto dummy = ::plus_n{10};

    delegate.bind<plus_n,&plus_n::const_function>(dummy);
    REQUIRE( delegate.is_bound() );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("delegate::is_bound()", "[member function]")
{
  SECTION("Returns false when not bound")
  {
    auto delegate = bit::stl::delegate<int(int)>{};

    REQUIRE_FALSE( delegate.is_bound() );
  }

  SECTION("Returns true when bound")
  {
    auto delegate = bit::stl::delegate<int(int)>{};

    delegate.bind<&::plus_one>();

    REQUIRE( delegate.is_bound() );
  }
}

TEST_CASE("delegate::operator bool", "[member function]")
{
  SECTION("Is explicitly convertible to false when not bound")
  {
    auto delegate = bit::stl::delegate<int(int)>{};

    REQUIRE_FALSE( static_cast<bool>(delegate) );
  }

  SECTION("Is explicitly convertible to true when bound")
  {
    auto delegate = bit::stl::delegate<int(int)>{};

    delegate.bind<&::plus_one>();

    REQUIRE( static_cast<bool>(delegate) );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("delegate::operator()(Args&&...)", "[member function]")
{
  SECTION("Invokes bound free function")
  {
    auto delegate = bit::stl::delegate<int(int)>{};

    delegate.bind<&::plus_one>();

    REQUIRE( delegate(5) == 6 );
  }

  SECTION("Invokes non-const member function")
  {
    auto delegate = bit::stl::delegate<int(int)>{};
    auto dummy    = ::plus_n{10};

    delegate.bind<plus_n,&plus_n::non_const_function>(dummy);

    REQUIRE( delegate(5) == 15 );
  }

  SECTION("Invokes const member function")
  {
    auto delegate    = bit::stl::delegate<int(int)>{};
    const auto dummy = ::plus_n{10};

    delegate.bind<plus_n,&plus_n::const_function>(dummy);

    REQUIRE( delegate(5) == 15 );
  }
}

