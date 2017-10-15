/**
 * \file lazy.test.cpp
 *
 * \brief Test cases for bit::stl::lazy
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#include <bit/stl/utilities/lazy.hpp>

#include <string>

#include <catch.hpp>

//----------------------------------------------------------------------------
// Constructor / Destructor
//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy()", "[ctor]")
{
  bit::stl::lazy<std::string> lazy;

  SECTION("Default constructs a lazy")
  {
    SECTION("Is uninitialized")
    {
      REQUIRE_FALSE( lazy.has_value() );
    }

    SECTION("Default constructs on initialization")
    {
      REQUIRE( lazy.value() == std::string() );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy( const lazy& )", "[ctor]")
{
  bit::stl::lazy<std::string> lazy( bit::stl::in_place, "Hello World" );

  SECTION("Copy constructs an uninitialized lazy")
  {
    auto copy = lazy;

    SECTION("Is uninitialized")
    {
      REQUIRE_FALSE( copy.has_value() );
    }

    SECTION("Copy constructs on initialization")
    {
      REQUIRE( copy.value() == "Hello World" );
    }
  }

  SECTION("Copy constructs an initialized lazy")
  {
    lazy.initialize();
    auto copy = lazy;

    SECTION("Is initialized")
    {
      REQUIRE( copy.has_value() );
    }

    SECTION("Contains the copied value")
    {
      REQUIRE( *copy == "Hello World" );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy( lazy&& )", "[ctor]")
{
  bit::stl::lazy<std::string> lazy = "Hello World";

  SECTION("Copy constructs an uninitialized lazy")
  {
    auto move = std::move(lazy);

    SECTION("Is uninitialized")
    {
      REQUIRE_FALSE( move.has_value() );
    }

    SECTION("Copy constructs on initialization")
    {
      REQUIRE( move.value() == "Hello World" );
    }
  }

  SECTION("Copy constructs an initialized lazy")
  {
    lazy.initialize();
    auto move = std::move(lazy);

    SECTION("Is initialized")
    {
      REQUIRE( move.has_value() );
    }

    SECTION("Contains the moved value")
    {
      REQUIRE( *move == "Hello World" );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy( const lazy<U>& )", "[ctor]")
{
  bit::stl::lazy<const char*> lazy = "Hello World";

  SECTION("Copy constructs an uninitialized lazy")
  {
    bit::stl::lazy<std::string> copy(lazy);

    SECTION("Is uninitialized")
    {
      REQUIRE_FALSE( copy.has_value() );
    }

    SECTION("Copy constructs on initialization")
    {
      REQUIRE( copy.value() == "Hello World" );
    }
  }

  SECTION("Copy constructs an initialized lazy")
  {
    lazy.initialize();
    bit::stl::lazy<std::string> copy(lazy);

    SECTION("Is initialized")
    {
      REQUIRE( copy.has_value() );
    }

    SECTION("Contains the moved value")
    {
      REQUIRE( *copy == "Hello World" );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy( lazy<U>&& )", "[ctor]")
{
  bit::stl::lazy<const char*> lazy = "Hello World";

  SECTION("Move constructs an uninitialized lazy")
  {
    bit::stl::lazy<std::string> move(std::move(lazy));

    SECTION("Is uninitialized")
    {
      REQUIRE_FALSE( move.has_value() );
    }

    SECTION("Copy constructs on initialization")
    {
      REQUIRE( move.value() == "Hello World" );
    }
  }

  SECTION("Move constructs an initialized lazy")
  {
    lazy.initialize();
    bit::stl::lazy<std::string> move(std::move(lazy));

    SECTION("Is initialized")
    {
      REQUIRE( move.has_value() );
    }

    SECTION("Contains the moved value")
    {
      REQUIRE( *move == "Hello World" );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy( U&& )", "[ctor]")
{
  bit::stl::lazy<int> lazy = 3.5;

  SECTION("Value constructs the lazy")
  {
    SECTION("Is uninitialized")
    {
      REQUIRE_FALSE( lazy.has_value() );
    }

    SECTION("Default constructs on initialization")
    {
      REQUIRE( lazy.value() == int(3.5) );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy( in_place_t, Args&&...args )", "[ctor]")
{
  bit::stl::lazy<std::string> lazy( bit::stl::in_place, "Hello World", 5 );

  SECTION("Variadic contructs an uninitialized lazy")
  {
    SECTION("Is uninitialized")
    {
      REQUIRE_FALSE( lazy.has_value() );
    }

    SECTION("Constructs on initialization")
    {
      REQUIRE( lazy.value() == "Hello" );
    }
  }
}

//----------------------------------------------------------------------------
// Assignment
//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy::operator=( const lazy& )", "[assignment]")
{
  bit::stl::lazy<std::string> source = "Hello World";
  bit::stl::lazy<std::string> destination = "Goodbye World";

  SECTION("Copy assigns uninitialized destination with uninitialized source")
  {
    bool before = destination.has_value();
    destination = source;
    bool after  = destination.has_value();

    SECTION("destination is uninitialized")
    {
      REQUIRE_FALSE( destination.has_value() );
    }

    SECTION("source is uninitialized")
    {
      REQUIRE_FALSE( source.has_value() );
    }

    SECTION("destination state is unchanged")
    {
      REQUIRE( before == after );
    }

    SECTION("Initializes destination with value of source")
    {
      REQUIRE( destination.value() == source.value() );
    }
  }

  //--------------------------------------------------------------------------

  SECTION("Copy assigns uninitialized destination with initialized source")
  {
    source.initialize();
    bool before = destination.has_value();
    destination = source;
    bool after  = destination.has_value();

    SECTION("destination is initialized")
    {
      REQUIRE( destination.has_value() );
    }

    SECTION("source is initialized")
    {
      REQUIRE( source.has_value() );
    }

    SECTION("destination state is changed")
    {
      REQUIRE( before != after );
    }

    SECTION("Initializes destination with value of source")
    {
      REQUIRE( destination.value() == source.value() );
    }
  }

  //--------------------------------------------------------------------------

  SECTION("Copy assigns initialized copy with uninitialized source")
  {
    destination.initialize();
    bool before = source.has_value();
    destination = source;
    bool after  = source.has_value();

    SECTION("destination is initialized")
    {
      REQUIRE( destination.has_value() );
    }

    SECTION("source is initialized")
    {
      REQUIRE( source.has_value() );
    }

    SECTION("source state is changed")
    {
      REQUIRE( before != after );
    }

    SECTION("Initializes destination with value of source")
    {
      REQUIRE( destination.value() == source.value() );
    }
  }

  //--------------------------------------------------------------------------

  SECTION("Copy assigns initialized copy with initialized source")
  {
    destination.initialize();
    source.initialize();
    destination = source;

    SECTION("destination is initialized")
    {
      REQUIRE( destination.has_value() );
    }

    SECTION("source is initialized")
    {
      REQUIRE( source.has_value() );
    }

    SECTION("Initializes destination with value of source")
    {
      REQUIRE( destination.value() == source.value() );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy::operator=( lazy&& )", "[assignment]")
{
  const char* string = "Hello World";
  bit::stl::lazy<std::string> source = string;
  bit::stl::lazy<std::string> destination = "Goodbye World";

  SECTION("Move assigns uninitialized destination with uninitialized source")
  {
    bool before = destination.has_value();
    destination = std::move(source);
    bool after  = destination.has_value();

    SECTION("destination is uninitialized")
    {
      REQUIRE_FALSE( destination.has_value() );
    }

    SECTION("source is uninitialized")
    {
      REQUIRE_FALSE( source.has_value() );
    }

    SECTION("destination state is unchanged")
    {
      REQUIRE( before == after );
    }

    SECTION("Initializes destination with value of source")
    {
      REQUIRE( destination.value() == string );
    }
  }

  //--------------------------------------------------------------------------

  SECTION("Move assigns uninitialized destination with initialized source")
  {
    source.initialize();
    bool before = destination.has_value();
    destination = std::move(source);
    bool after  = destination.has_value();

    SECTION("destination is initialized")
    {
      REQUIRE( destination.has_value() );
    }

    SECTION("source is initialized")
    {
      REQUIRE( source.has_value() );
    }

    SECTION("destination state is changed")
    {
      REQUIRE( before != after );
    }

    SECTION("Initializes destination with value of source")
    {
      REQUIRE( destination.value() == string );
    }
  }

  //--------------------------------------------------------------------------

  SECTION("Move assigns initialized copy with uninitialized source")
  {
    destination.initialize();
    bool before = source.has_value();
    destination = std::move(source);
    bool after  = source.has_value();

    SECTION("destination is initialized")
    {
      REQUIRE( destination.has_value() );
    }

    SECTION("source is initialized")
    {
      REQUIRE( source.has_value() );
    }

    SECTION("source state is changed")
    {
      REQUIRE( before != after );
    }

    SECTION("Initializes destination with value of source")
    {
      REQUIRE( destination.value() == string );
    }
  }

  //--------------------------------------------------------------------------

  SECTION("Move assigns initialized copy with initialized source")
  {
    destination.initialize();
    source.initialize();
    destination = std::move(source);

    SECTION("destination is initialized")
    {
      REQUIRE( destination.has_value() );
    }

    SECTION("source is initialized")
    {
      REQUIRE( source.has_value() );
    }

    SECTION("Initializes destination with value of source")
    {
      REQUIRE( destination.value() == string );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy::operator=( const lazy<U>& )", "[assignment]")
{
  bit::stl::lazy<const char*> source = "Hello World";
  bit::stl::lazy<std::string> destination = "Goodbye World";

  SECTION("Copy assigns uninitialized destination with uninitialized source")
  {
    bool before = destination.has_value();
    destination = source;
    bool after  = destination.has_value();

    SECTION("destination is uninitialized")
    {
      REQUIRE_FALSE( destination.has_value() );
    }

    SECTION("source gets initialized")
    {
      REQUIRE( source.has_value() );
    }

    SECTION("destination state is unchanged")
    {
      REQUIRE( before == after );
    }

    SECTION("Initializes destination with value of source")
    {
      REQUIRE( destination.value() == source.value() );
    }
  }

  //--------------------------------------------------------------------------

  SECTION("Copy assigns uninitialized destination with initialized source")
  {
    source.initialize();
    bool before = destination.has_value();
    destination = source;
    bool after  = destination.has_value();

    SECTION("destination is initialized")
    {
      REQUIRE( destination.has_value() );
    }

    SECTION("source is initialized")
    {
      REQUIRE( source.has_value() );
    }

    SECTION("destination state is changed")
    {
      REQUIRE( before != after );
    }

    SECTION("Initializes destination with value of source")
    {
      REQUIRE( destination.value() == source.value() );
    }
  }

  //--------------------------------------------------------------------------

  SECTION("Copy assigns initialized copy with uninitialized source")
  {
    destination.initialize();
    bool before = source.has_value();
    destination = source;
    bool after  = source.has_value();

    SECTION("destination is initialized")
    {
      REQUIRE( destination.has_value() );
    }

    SECTION("source is initialized")
    {
      REQUIRE( source.has_value() );
    }

    SECTION("source state is changed")
    {
      REQUIRE( before != after );
    }

    SECTION("Initializes destination with value of source")
    {
      REQUIRE( destination.value() == source.value() );
    }
  }

  //--------------------------------------------------------------------------

  SECTION("Copy assigns initialized copy with initialized source")
  {
    destination.initialize();
    source.initialize();
    destination = source;

    SECTION("destination is initialized")
    {
      REQUIRE( destination.has_value() );
    }

    SECTION("source is initialized")
    {
      REQUIRE( source.has_value() );
    }

    SECTION("Initializes destination with value of source")
    {
      REQUIRE( destination.value() == source.value() );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy::operator=( lazy<U>&& )", "[assignment]")
{
  const char* string = "Hello World";
  bit::stl::lazy<const char*> source = string;
  bit::stl::lazy<std::string> destination = "Goodbye World";

  SECTION("Move assigns uninitialized destination with uninitialized source")
  {
    bool before = destination.has_value();
    destination = std::move(source);
    bool after  = destination.has_value();

    SECTION("destination is uninitialized")
    {
      REQUIRE_FALSE( destination.has_value() );
    }

    SECTION("source is initialized")
    {
      REQUIRE( source.has_value() );
    }

    SECTION("destination state is unchanged")
    {
      REQUIRE( before == after );
    }

    SECTION("Initializes destination with value of source")
    {
      REQUIRE( destination.value() == string );
    }
  }

  //--------------------------------------------------------------------------

  SECTION("Move assigns uninitialized destination with initialized source")
  {
    source.initialize();
    bool before = destination.has_value();
    destination = std::move(source);
    bool after  = destination.has_value();

    SECTION("destination is initialized")
    {
      REQUIRE( destination.has_value() );
    }

    SECTION("source is initialized")
    {
      REQUIRE( source.has_value() );
    }

    SECTION("destination state is changed")
    {
      REQUIRE( before != after );
    }

    SECTION("Initializes destination with value of source")
    {
      REQUIRE( destination.value() == string );
    }
  }

  //--------------------------------------------------------------------------

  SECTION("Move assigns initialized copy with uninitialized source")
  {
    destination.initialize();
    bool before = source.has_value();
    destination = std::move(source);
    bool after  = source.has_value();

    SECTION("destination is initialized")
    {
      REQUIRE( destination.has_value() );
    }

    SECTION("source is initialized")
    {
      REQUIRE( source.has_value() );
    }

    SECTION("source state is changed")
    {
      REQUIRE( before != after );
    }

    SECTION("Initializes destination with value of source")
    {
      REQUIRE( destination.value() == string );
    }
  }

  //--------------------------------------------------------------------------

  SECTION("Move assigns initialized copy with initialized source")
  {
    destination.initialize();
    source.initialize();
    destination = std::move(source);

    SECTION("destination is initialized")
    {
      REQUIRE( destination.has_value() );
    }

    SECTION("source is initialized")
    {
      REQUIRE( source.has_value() );
    }

    SECTION("Initializes destination with value of source")
    {
      REQUIRE( destination.value() == string );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy::operator=( U&& )", "[assignment]")
{
  const char* string = "Hello World";
  bit::stl::lazy<std::string> lazy;

  SECTION("Assigning to uninitialized lazy")
  {
    SECTION("Copy-assigns lvalue references")
    {
      bool before = lazy.has_value();
      lazy = string;
      bool after  = lazy.has_value();

      SECTION("Initializes lazy")
      {
        REQUIRE( before != after );
      }

      SECTION("Lazy contains new value")
      {
        REQUIRE( *lazy == string );
      }
    }

    SECTION("Move-assigns rvalue references")
    {
      auto copy = string;
      bool before = lazy.has_value();
      lazy = std::move(string);
      bool after  = lazy.has_value();

      SECTION("Initializes lazy")
      {
        REQUIRE( before != after );
      }

      SECTION("Lazy contains new value")
      {
        REQUIRE( *lazy == copy );
      }
    }
  }

  //--------------------------------------------------------------------------

  SECTION("Assigning to initialized lazy")
  {
    lazy.initialize();

    SECTION("Copy-assigns lvalue references")
    {
      bool before = lazy.has_value();
      lazy = string;
      bool after  = lazy.has_value();

      SECTION("Lazy is already initialized")
      {
        REQUIRE( before == after );
      }

      SECTION("Lazy contains new value")
      {
        REQUIRE( *lazy == string );
      }
    }

    //--------------------------------------------------------------------------

    SECTION("Move-assigns rvalue references")
    {
      lazy = std::move(string);

      auto copy = string;
      bool before = lazy.has_value();
      lazy = std::move(string);
      bool after  = lazy.has_value();

      SECTION("Lazy is already initialized")
      {
        REQUIRE( before == after );
      }

      SECTION("Lazy contains new value")
      {
        REQUIRE( *lazy == copy );
      }
    }
  }
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy::initialize()", "[modifiers]")
{
  bit::stl::lazy<int> lazy = 42;

  SECTION("Initializes uninitialized lazy")
  {
    bool before = lazy.has_value();
    lazy.initialize();
    bool after = lazy.has_value();

    SECTION("Lazy changes state")
    {
      REQUIRE( before != after );
    }

    SECTION("Lazy contains value")
    {
      REQUIRE( *lazy == 42 );
    }
  }

  SECTION("Doesn't modify initialized lazy")
  {
    lazy.initialize();
    bool before = lazy.has_value();
    lazy.initialize();
    bool after = lazy.has_value();

    SECTION("Lazy state doesn't change")
    {
      REQUIRE( before == after );
    }

    SECTION("Lazy contains value")
    {
      REQUIRE( *lazy == 42 );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy::reset()", "[modifiers]")
{
   bit::stl::lazy<int> lazy = 42;

   SECTION("Does nothing to uninitialized lazies")
   {
     bool before = lazy.has_value();
     lazy.reset();
     bool after = lazy.has_value();

     REQUIRE( before == after );
   }

   SECTION("Does nothing to uninitialized lazies")
   {
     lazy.initialize();
     bool before = lazy.has_value();
     lazy.reset();
     bool after = lazy.has_value();

     REQUIRE( before != after );
   }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy::swap( lazy& )", "[modifiers]")
{
  int left_value  = 0xdead;
  int right_value = 0xbeef;
  bit::stl::lazy<int> left  = left_value;
  bit::stl::lazy<int> right = right_value;

  SECTION("Swapping uninitialized lazy with uninitialized lazy")
  {
    left.swap(right);

    SECTION("Left is still uninitialized")
    {
      REQUIRE_FALSE( left.has_value() );
    }

    SECTION("Right is still uninitialized")
    {
      REQUIRE_FALSE( right.has_value() );
    }

    SECTION("Left initializes with right's value")
    {
      REQUIRE( left.value() == right_value );
    }

    SECTION("Right initializes with left's value")
    {
      REQUIRE( right.value() == left_value );
    }
  }

  SECTION("Swapping initialized lazy with uninitialized lazy")
  {
    left.initialize();
    left.swap(right);

    SECTION("Left is initialized")
    {
      REQUIRE( left.has_value() );
    }

    SECTION("Right is ninitialized")
    {
      REQUIRE( right.has_value() );
    }

    SECTION("Left initializes with right's value")
    {
      REQUIRE( left.value() == right_value );
    }

    SECTION("Right initializes with left's value")
    {
      REQUIRE( right.value() == left_value );
    }
  }

  SECTION("Swapping uninitialized lazy with initialized lazy")
  {
    right.initialize();
    left.swap(right);

    SECTION("Left is initialized")
    {
      REQUIRE( left.has_value() );
    }

    SECTION("Right is ninitialized")
    {
      REQUIRE( right.has_value() );
    }

    SECTION("Left initializes with right's value")
    {
      REQUIRE( left.value() == right_value );
    }

    SECTION("Right initializes with left's value")
    {
      REQUIRE( right.value() == left_value );
    }
  }

  SECTION("Swapping initialized lazy with initialized lazy")
  {
    left.initialize();
    right.initialize();
    left.swap(right);

    SECTION("Left is initialized")
    {
      REQUIRE( left.has_value() );
    }

    SECTION("Right is ninitialized")
    {
      REQUIRE( right.has_value() );
    }

    SECTION("Left initializes with right's value")
    {
      REQUIRE( left.value() == right_value );
    }

    SECTION("Right initializes with left's value")
    {
      REQUIRE( right.value() == left_value );
    }
  }
}

//---------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy::operator bool")
{
  bit::stl::lazy<int> lazy;

  SECTION("Returns true when initialized")
  {
    lazy.initialize();

    REQUIRE( lazy );
  }

  SECTION("Returns false when uninitialized")
  {
    REQUIRE_FALSE( lazy );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy::has_value")
{
  bit::stl::lazy<int> lazy;

  SECTION("Returns true when initialized")
  {
    lazy.initialize();

    REQUIRE( lazy.has_value() );
  }

  SECTION("Returns false when uninitialized")
  {
    REQUIRE_FALSE( lazy.has_value() );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy::value() &")
{
  int value = 42;
  bit::stl::lazy<int> lazy = value;

  SECTION("Initializes uninitialized lazy")
  {
    bool before = lazy.has_value();
    lazy.value();
    bool after = lazy.has_value();

    REQUIRE( before != after );
  }

  SECTION("Returns the deferred value")
  {
    REQUIRE( lazy.value() == value );
  }

  SECTION("Returns non-const lvalue reference")
  {
    bool result = std::is_same<decltype(lazy.value()),int&>::value;

    REQUIRE( result );
  }
}

TEST_CASE("bit::stl::lazy::value() const &")
{
  int value = 42;
  const bit::stl::lazy<int> lazy = value;

  SECTION("Initializes uninitialized lazy")
  {
    bool before = lazy.has_value();
    lazy.value();
    bool after = lazy.has_value();

    REQUIRE( before != after );
  }

  SECTION("Returns the deferred value")
  {
    REQUIRE( lazy.value() == value );
  }

  SECTION("Returns const lvalue reference")
  {
    bool result = std::is_same<decltype(lazy.value()),const int&>::value;

    REQUIRE( result );
  }

}

TEST_CASE("bit::stl::lazy::value() &&")
{
  int value = 42;
  bit::stl::lazy<int> lazy = value;

  SECTION("Initializes uninitialized lazy")
  {
    bool before = lazy.has_value();
    std::move(lazy).value();
    bool after = lazy.has_value();

    REQUIRE( before != after );
  }

  SECTION("Returns the deferred value")
  {
    REQUIRE( std::move(lazy).value() == value );
  }

  SECTION("Returns non-const rvalue reference")
  {
    bool result = std::is_same<decltype(std::move(lazy).value()),int&&>::value;

    REQUIRE( result );
  }

}

TEST_CASE("bit::stl::lazy::value() const &&")
{
  int value = 42;
  const bit::stl::lazy<int> lazy = value;

  SECTION("Initializes uninitialized lazy")
  {
    bool before = lazy.has_value();
    std::move(lazy).value();
    bool after = lazy.has_value();

    REQUIRE( before != after );
  }

  SECTION("Returns the deferred value")
  {
    REQUIRE( std::move(lazy).value() == value );
  }

  SECTION("Returns const rvalue reference")
  {
    bool result = std::is_same<decltype(std::move(lazy).value()),const int&&>::value;

    REQUIRE( result );
  }

}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::lazy::value_or( U&& ) const &")
{
  const bit::stl::lazy<int> lazy = 42;

  SECTION("Returns underlying value when initialized")
  {
    lazy.initialize();

    REQUIRE( lazy.value_or(24) == 42 );
  }

  SECTION("Returns default_value when initialized")
  {
    REQUIRE( lazy.value_or(24) == 24 );
  }
}

TEST_CASE("bit::stl::lazy::value_or( U&& ) &&")
{
  bit::stl::lazy<int> lazy = 42;

  SECTION("Returns underlying value when initialized")
  {
    std::move(lazy).initialize();

    REQUIRE( std::move(lazy).value_or(24) == 42 );
  }

  SECTION("Returns default_value when initialized")
  {
    REQUIRE( std::move(lazy).value_or(24) == 24 );
  }
}

//----------------------------------------------------------------------------
// Utility Generators
//----------------------------------------------------------------------------

TEST_CASE("bit::stl::make_lazy<T>( Args&&... )", "[utility]")
{
  auto lazy = bit::stl::make_lazy<std::string>("Hello World", 5);

  SECTION("Creates uninitialized lazy")
  {
    REQUIRE_FALSE( lazy.has_value() );
  }

  SECTION("Initializes by calling underlying constructor")
  {
    REQUIRE( lazy.value() == std::string("Hello World", 5) );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("bit::stl::make_lazy_generator<T>( Ctor&& )", "[utility]")
{
  auto lazy = bit::stl::make_lazy_generator<int>([](){ return std::make_tuple( 42 ); });

  SECTION("Creates uninitialized lazy")
  {
    REQUIRE_FALSE( lazy.has_value() );
  }

  SECTION("Initializes with value stored in generator")
  {
    REQUIRE( lazy.value() == 42 );
  }
}
