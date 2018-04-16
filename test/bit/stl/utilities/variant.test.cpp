/**
 * \file variant.test.cpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#include <bit/stl/utilities/variant.hpp>

#include <string> // std::string
#include <memory> // std::unique_ptr

#include <catch.hpp>

static_assert( std::is_trivially_destructible<bit::stl::variant<int,bool>>::value,
               "Variant containing trivially destructible types must be trivially destructible" );
static_assert( !std::is_trivially_destructible<bit::stl::variant<std::string,bool>>::value,
               "Variant containing non-trivially destructible types must not be trivially destructible" );

namespace {
  struct throw_on_move
  {
    throw_on_move() = default;
    throw_on_move( const throw_on_move& ) = default;
    throw_on_move( throw_on_move&& ) { throw 42; };
    throw_on_move& operator=( const throw_on_move& ) = default;
    throw_on_move& operator=( throw_on_move&& ) = default;
  };
  struct throw_on_copy
  {
    throw_on_copy() = default;
    throw_on_copy( const throw_on_copy& ) { throw 42; }
    throw_on_copy( throw_on_copy&& ) noexcept = default;
    throw_on_copy& operator=( const throw_on_copy& ) = default;
    throw_on_copy& operator=( throw_on_copy&& ) = default;
  };

}

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

// (1)
TEST_CASE("variant::variant()", "[ctor]")
{
  using variant_type = bit::stl::variant<std::string,int>;

  auto variant = variant_type{};

  SECTION("Default-constructs first alternative")
  {
    SECTION("Index is 0")
    {
      REQUIRE( variant.index() == 0 );
    }
    SECTION("First type is default-constructed")
    {
      REQUIRE( bit::stl::get<0>( variant ) == std::string() );
    }
  }
}

//-----------------------------------------------------------------------------

// (2)
TEST_CASE("variant::variant( const variant& )", "[ctor]")
{
  using variant_type = bit::stl::variant<int,std::string>;
  using namespace std::string_literals;

  auto original = variant_type{"hello world"s};
  auto copy     = original;

  SECTION("Copies the currently active element")
  {
    SECTION("Index is the same")
    {
      REQUIRE( original.index() == copy.index() );
    }
    SECTION("Content is the same")
    {
      REQUIRE( bit::stl::get<1>( original ) == bit::stl::get<1>( copy ) );
    }
  }
}

//-----------------------------------------------------------------------------

// (3)
TEST_CASE("variant::variant( variant&& )", "[ctor]")
{
  using variant_type = bit::stl::variant<int,std::unique_ptr<int>>;
  using namespace std::string_literals;

  auto original = variant_type{std::make_unique<int>(5)};
  auto pointer  = bit::stl::get<1>( original ).get();
  auto moved    = std::move(original);

  SECTION("Copies the currently active element")
  {
    SECTION("Index is the same")
    {
      REQUIRE( original.index() == moved.index() );
    }
    SECTION("Moved variant owns the original memory")
    {
      REQUIRE( bit::stl::get<1>( moved ).get() == pointer );
    }
    SECTION("Original content is moved")
    {
      REQUIRE( bit::stl::get<1>( original ) == nullptr );
    }
  }

}

//-----------------------------------------------------------------------------

// (4)
TEST_CASE("variant::variant( T&& )", "[ctor]")
{
  using namespace std::string_literals;
  using variant_type = bit::stl::variant<bool,std::string>;

  SECTION("Constructs based on function-overload resolution disambiguation")
  {
    SECTION("Resolves 'bool'-overload with C-string literal")
    {
      auto variant = variant_type{"hello world"};

      SECTION("Index is 0")
      {
        REQUIRE( variant.index() == 0 );
      }
      SECTION("Value is true")
      {
        REQUIRE( bit::stl::get<0>( variant ) == true );
      }
    }
    SECTION("Resolves 'bool'-overload with boolean literal")
    {
      auto variant = variant_type{false};

      SECTION("Index is 0")
      {
        REQUIRE( variant.index() == 0 );
      }
      SECTION("Value is false")
      {
        REQUIRE( bit::stl::get<0>( variant ) == false );
      }
    }
    SECTION("Resolves 'string'-overload with string literal")
    {
      auto expected = "hello world"s;
      auto variant = variant_type{expected};

      SECTION("Index is 1")
      {
        REQUIRE( variant.index() == 1 );
      }
      SECTION("Value is \"hello world\"")
      {
        REQUIRE( bit::stl::get<1>( variant ) == expected );
      }
    }
  }
}

//-----------------------------------------------------------------------------

// (5)
TEST_CASE("variant::variant( in_place_type_t<T>, Args&&... )", "[ctor]")
{
  using namespace std::string_literals;
  using variant_type = bit::stl::variant<bool,std::string>;

  SECTION("Selects the overload based on type T")
  {
    auto variant = variant_type{ bit::stl::in_place_type<std::string>, "hello world" };

    SECTION("Index is string's index")
    {
      REQUIRE( variant.index() == 1 );
    }
    SECTION("Value is constructed from input")
    {
      REQUIRE( bit::stl::get<1>( variant ) == "hello world"s );
    }
  }
}

//-----------------------------------------------------------------------------

// (6)
TEST_CASE("variant::variant( in_place_type_t<T>, std::initializer_list<U>, Args&&...", "[ctor]")
{
  using namespace std::string_literals;
  using variant_type = bit::stl::variant<bool,std::string>;

  SECTION("Selects the overload based on type T")
  {
    auto variant = variant_type{ bit::stl::in_place_type<std::string>,
                                 {'h','e','l','l','o',' ','w','o','r','l','d'},
                                 std::allocator<char>{} };

    SECTION("Index is string's index")
    {
      REQUIRE( variant.index() == 1 );
    }
    SECTION("Value is constructed from input")
    {
      REQUIRE( bit::stl::get<1>( variant ) == "hello world"s );
    }
  }
}

//-----------------------------------------------------------------------------

// (7)
TEST_CASE("variant::variant( in_place_index_t<T>, Args&&... )", "[ctor]")
{
  using namespace std::string_literals;
  using variant_type = bit::stl::variant<bool,std::string>;

  SECTION("Selects the overload based on type T")
  {
    auto variant = variant_type{ bit::stl::in_place_index<1>, "hello world" };

    SECTION("Index is string's index")
    {
      REQUIRE( variant.index() == 1 );
    }
    SECTION("Value is constructed from input")
    {
      REQUIRE( bit::stl::get<1>( variant ) == "hello world"s );
    }
  }
}

// (8)
TEST_CASE("variant::variant( in_place_index_t<I>, std::initializer_list<U>, Args&&...", "[ctor]")
{
  using namespace std::string_literals;
  using variant_type = bit::stl::variant<bool,std::string>;

  SECTION("Selects the overload based on type T")
  {
    auto variant = variant_type{ bit::stl::in_place_index<1>,
                                 {'h','e','l','l','o',' ','w','o','r','l','d'},
                                 std::allocator<char>{} };

    SECTION("Index is string's index")
    {
      REQUIRE( variant.index() == 1 );
    }
    SECTION("Value is constructed from input")
    {
      REQUIRE( bit::stl::get<1>( variant ) == "hello world"s );
    }
  }
}

//-----------------------------------------------------------------------------
// Assignment
//-----------------------------------------------------------------------------

TEST_CASE("variant::operator=( const variant& )", "[assignment]")
{
  using namespace std::string_literals;
  using variant_type = bit::stl::variant<bool,std::string,::throw_on_copy>;

  auto old_value = "hello world"s;
  auto variant   = variant_type{old_value};
  auto old_index = variant.index();

  SECTION("Calls constructor if assigning type that is not active index")
  {
    auto to_copy = variant_type{false};
    variant = to_copy;

    SECTION("Changes active index")
    {
      REQUIRE( old_index != variant.index() );
    }
    SECTION("Changes value")
    {
      REQUIRE( bit::stl::get<0>( variant ) == false );
    }
  }
  SECTION("Calls assignment operator if assigning active index")
  {
    auto new_value = "goodbye world"s;
    auto to_copy = variant_type{new_value};
    variant = to_copy;

    SECTION("Does not change index")
    {
      REQUIRE( old_index == variant.index() );
    }
    SECTION("Changes value")
    {
      REQUIRE( bit::stl::get<1>( variant ) == new_value );
    }
  }
  SECTION("Holds old value if copy throws")
  {
    try {
      auto to_copy = variant_type{::throw_on_copy{}};
      variant = to_copy;
    } catch (...) {
      // ignore
    }

    SECTION("Does not change index")
    {
      REQUIRE( old_index == variant.index() );
    }
    SECTION("Value remains unchanged")
    {
      REQUIRE( bit::stl::get<1>( variant ) == old_value );
    }
  }
}

TEST_CASE("variant::operator=( variant&& )", "[assignment]")
{
  using namespace std::string_literals;
  using variant_type = bit::stl::variant<bool,std::string,::throw_on_move>;

  auto old_value = "hello world"s;
  auto variant   = variant_type{old_value};
  auto old_index = variant.index();

  SECTION("Calls constructor if assigning type that is not active index")
  {
    variant = variant_type{false};

    SECTION("Changes active index")
    {
      REQUIRE( old_index != variant.index() );
    }
    SECTION("Changes value")
    {
      REQUIRE( bit::stl::get<0>( variant ) == false );
    }
  }
  SECTION("Calls assignment operator if assigning active index")
  {
    auto new_value = "goodbye world"s;
    variant = variant_type{new_value};

    SECTION("Does not change index")
    {
      REQUIRE( old_index == variant.index() );
    }
    SECTION("Changes value")
    {
      REQUIRE( bit::stl::get<1>( variant ) == new_value );
    }
  }
  SECTION("Becomes valueless by exception if move throws")
  {
    try {
      const ::throw_on_move value;
      variant = variant_type{value};
    } catch (...) {
      // ignore
    }

    SECTION("Index becomes variant_npos")
    {
      REQUIRE( bit::stl::variant_npos == variant.index() );
    }
    SECTION("Is valueless_by_exception")
    {
      REQUIRE( variant.valueless_by_exception() );
    }
  }
}

TEST_CASE("variant::operator=( T&& )", "[assignment]")
{
  using namespace std::string_literals;
  using variant_type = bit::stl::variant<bool,std::string,::throw_on_move>;

  auto old_value = "hello world"s;
  auto variant   = variant_type{old_value};
  auto old_index = variant.index();

  SECTION("Calls constructor if assigning type that is not active index")
  {
    variant = false;

    SECTION("Changes active index")
    {
      REQUIRE( old_index != variant.index() );
    }
    SECTION("Changes value")
    {
      REQUIRE( bit::stl::get<0>( variant ) == false );
    }
  }
  SECTION("Calls assignment operator if assigning active index")
  {
    auto new_value = "goodbye world"s;
    auto expected = new_value;
    variant = std::move(new_value);

    SECTION("Does not change index")
    {
      REQUIRE( old_index == variant.index() );
    }
    SECTION("Changes value")
    {
      REQUIRE( bit::stl::get<1>( variant ) == expected );
    }
  }
  SECTION("Becomes valueless by exception if type change throws")
  {
    try {
      variant = ::throw_on_move{};
    } catch (...) {
      // ignore
    }

    SECTION("Index becomes variant_npos")
    {
      REQUIRE( bit::stl::variant_npos == variant.index() );
    }
    SECTION("Is valueless_by_exception")
    {
      REQUIRE( variant.valueless_by_exception() );
    }
  }
}

//-----------------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------------

TEST_CASE("variant::emplace<T>( Args&&... )", "[modifiers]")
{
  using namespace std::string_literals;
  using variant_type = bit::stl::variant<bool,std::string,::throw_on_move>;

  auto variant = variant_type{false};
  auto old_index = variant.index();

  SECTION("Emplaces the new variant element")
  {
    variant.emplace<std::string>( "hello world" );

    SECTION("Variant index changess")
    {
      REQUIRE( variant.index() != old_index );
    }
    SECTION("Value is constructed from input")
    {
      REQUIRE( bit::stl::get<1>( variant ) == "hello world"s );
    }
  }
  SECTION("Becomes valueless by exception if exception is thrown")
  {
    try {
      variant.emplace<::throw_on_move>( ::throw_on_move{} );
    } catch ( ... ) {
      // ignore
    }

    SECTION("Index is variant_npos")
    {
      REQUIRE( variant.index() == bit::stl::variant_npos );
    }
    SECTION("Variant is valueless_by_exception")
    {
      REQUIRE( variant.valueless_by_exception() );
    }
  }
}

TEST_CASE("variant::emplace<T>( std::initializer_list<U>, Args&&... )", "[modifiers]")
{
  using namespace std::string_literals;
  using variant_type = bit::stl::variant<bool,std::string,::throw_on_move>;

  auto variant = variant_type{false};
  auto old_index = variant.index();

  SECTION("Emplaces the new variant element")
  {
    variant.emplace<std::string>( {'h','e','l','l','o',' ','w','o','r','l','d'} );

    SECTION("Variant index changess")
    {
      REQUIRE( variant.index() != old_index );
    }
    SECTION("Value is constructed from input")
    {
      REQUIRE( bit::stl::get<1>( variant ) == "hello world"s );
    }
  }
}

TEST_CASE("variant::emplace<I>( Args&&... )", "[modifiers]")
{
  using namespace std::string_literals;
  using variant_type = bit::stl::variant<bool,std::string,::throw_on_move>;

  auto variant = variant_type{false};
  auto old_index = variant.index();

  SECTION("Emplaces the new variant element")
  {
    variant.emplace<1>( "hello world" );

    SECTION("Variant index changess")
    {
      REQUIRE( variant.index() != old_index );
    }
    SECTION("Value is constructed from input")
    {
      REQUIRE( bit::stl::get<1>( variant ) == "hello world"s );
    }
  }
  SECTION("Becomes valueless by exception if exception is thrown")
  {
    try {
      variant.emplace<2>( ::throw_on_move{} );
    } catch ( ... ) {
      // ignore
    }

    SECTION("Index is variant_npos")
    {
      REQUIRE( variant.index() == bit::stl::variant_npos );
    }
    SECTION("Variant is valueless_by_exception")
    {
      REQUIRE( variant.valueless_by_exception() );
    }
  }
}

TEST_CASE("variant::emplace<I>( std::initializer_list<U>, Args&&... )", "[modifiers]")
{
  using namespace std::string_literals;
  using variant_type = bit::stl::variant<bool,std::string,::throw_on_move>;

  auto variant = variant_type{false};
  auto old_index = variant.index();

  SECTION("Emplaces the new variant element")
  {
    variant.emplace<1>( {'h','e','l','l','o',' ','w','o','r','l','d'} );

    SECTION("Variant index changess")
    {
      REQUIRE( variant.index() != old_index );
    }
    SECTION("Value is constructed from input")
    {
      REQUIRE( bit::stl::get<1>( variant ) == "hello world"s );
    }
  }
}

//-----------------------------------------------------------------------------

TEST_CASE("variant::swap( variant& )", "[modifiers]")
{
  using namespace std::string_literals;
  using variant_type = bit::stl::variant<std::string,bool,::throw_on_move>;

  SECTION("Swapping two variants with same alternative")
  {
    SECTION("Both variants are valueless_by_exception")
    {
      auto lhs = variant_type{};
      auto rhs = variant_type{};
      try {
        lhs = ::throw_on_move{};
      } catch (...) {}
      try {
        rhs = ::throw_on_move{};
      } catch (...) {}

      lhs.swap(rhs);

      SECTION("Left remains valueless_by_exception")
      {
        REQUIRE( lhs.valueless_by_exception() );
      }
      SECTION("Right remains valueless_by_exception")
      {
        REQUIRE( rhs.valueless_by_exception() );
      }
    }
    SECTION("Both variants hold types")
    {
      auto lexpected = "hello world"s;
      auto rexpected = "goodbye world"s;

      auto lhs = variant_type{lexpected};
      auto rhs = variant_type{rexpected};

      lhs.swap(rhs);

      SECTION("Left contains right's old value")
      {
        REQUIRE( bit::stl::get<0>(lhs) == rexpected );
      }
      SECTION("Right contains left's old value")
      {
        REQUIRE( bit::stl::get<0>(rhs) == lexpected );
      }
    }
  }
  SECTION("Swapping two variants with different alternatives")
  {
    SECTION("One variant is valueless_by_exception")
    {
      auto lexpected = "hello world"s;

      auto lhs = variant_type{lexpected};
      auto rhs = variant_type{};
      try {
        rhs = ::throw_on_move{};
      } catch (...) {}

      lhs.swap(rhs);

      SECTION("Left is valueless")
      {
        REQUIRE( lhs.valueless_by_exception() );
      }
      SECTION("Right contains left's old value")
      {
        REQUIRE( bit::stl::get<0>(rhs) == lexpected );
      }
    }
    SECTION("Both variants hold types")
    {
      auto lexpected = false;
      auto rexpected = "goodbye world"s;

      auto lhs = variant_type{lexpected};
      auto rhs = variant_type{rexpected};

      lhs.swap(rhs);

      SECTION("Left contains right's old value")
      {
        REQUIRE( bit::stl::get<0>(lhs) == rexpected );
      }
      SECTION("Right contains left's old value")
      {
        REQUIRE( bit::stl::get<1>(rhs) == lexpected );
      }

    }
  }
}
