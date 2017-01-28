/**
 * \file span.test.cpp
 *
 * \brief Unit tests for the span
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#include <bit/stl/span.hpp>
#include <bit/stl/string_view.hpp>

#include <vector>
#include <array>

#include "../../catch.hpp"

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

TEST_CASE("span::span()", "[ctor]")
{
  auto view = bit::stl::span<int>();
  SECTION("Default constructs an span")
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

TEST_CASE("span::span( const value_type*, size_type )", "[ctor]")
{
  int array[] = {1,2,3,4,5};
  auto view   = bit::stl::span<int>(array,5);

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

TEST_CASE("span::span( const value_type (&)[N] )", "[ctor]")
{
  int array[] = {1,2,3,4,5};
  auto view   = bit::stl::span<int>(array);

  SECTION("Constructs a view out of reference to array")
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

TEST_CASE("span::span( const span<T,M>& )", "[ctor]")
{
  int array[] = {1,2,3,4,5};
  auto view = bit::stl::span<int>(array);

  SECTION("Constructs an unbounded view from another view")
  {
    auto view2 = bit::stl::span<int>(view);

    SECTION("Constructs a non-empty view")
    {
      REQUIRE_FALSE( view2.empty() );
    }

    SECTION("Contains 5 elements")
    {
      REQUIRE( view2.size() == view.size() );
    }

    SECTION("Data points to original array")
    {
      REQUIRE( view2.data() == array );
    }
  }

  SECTION("Constructs a bounded view from another view")
  {
    auto view2 = bit::stl::span<int,5>(view);

    SECTION("Constructs a non-empty view")
    {
      REQUIRE_FALSE( view2.empty() );
    }

    SECTION("Contains 5 elements")
    {
      REQUIRE( view2.size() == 5 );
    }

    SECTION("Data points to original array")
    {
      REQUIRE( view2.data() == array );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("span::span( span<T,M>&& )", "[ctor]")
{
  int array[] = {1,2,3,4,5};
  auto view = bit::stl::span<int>(array);

  SECTION("Constructs an unbounded view from another view")
  {
    auto view2 = bit::stl::span<int>(std::move(view));

    SECTION("Constructs a non-empty view")
    {
      REQUIRE_FALSE( view2.empty() );
    }

    SECTION("Contains 5 elements")
    {
      REQUIRE( view2.size() == view.size() );
    }

    SECTION("Data points to original array")
    {
      REQUIRE( view2.data() == array );
    }
  }

  SECTION("Constructs a bounded view from another view")
  {
    auto view2 = bit::stl::span<int,5>(std::move(view));

    SECTION("Constructs a non-empty view")
    {
      REQUIRE_FALSE( view2.empty() );
    }

    SECTION("Contains 3 elements")
    {
      REQUIRE( view2.size() == 5 );
    }

    SECTION("Data points to original array")
    {
      REQUIRE( view2.data() == array );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("span::span( const std::array& )", "[ctor]")
{
  auto array = std::array<int,5>{{1,2,3,4,5}};
  auto view  = bit::stl::span<int>(array);

  SECTION("Constructs a view out of a std::array")
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
      REQUIRE( view.data() == &array[0] );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("span::span( const std::vector& )", "[ctor]")
{
  auto vector = std::vector<int>{1,2,3,4,5};
  auto view   = bit::stl::span<int>(vector);

  SECTION("Constructs a view out of a std::vector")
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
      REQUIRE( view.data() == &vector[0] );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("span::span( const std::string& )", "[ctor]")
{
  auto vector = std::vector<int>{1,2,3,4,5};
  auto view   = bit::stl::span<int>(vector);

  SECTION("Constructs a view out of a std::vector")
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
      REQUIRE( view.data() == &vector[0] );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("span::span( const basic_string_view<char>& )", "[ctor]")
{
  auto string = bit::stl::string_view("Hello");
  auto view   = bit::stl::span<const char>(string);

  SECTION("Constructs a view out of a basic_string_view")
  {
    SECTION("Constructs a non-empty view")
    {
      REQUIRE_FALSE( view.empty() );
    }

    SECTION("Contains 5 elements")
    {
      REQUIRE( view.size() == 5 );
    }

    SECTION("Data points to original string")
    {
      REQUIRE( view.data() == string.data() );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("span::span( const std::basic_string<char>& )", "[ctor]")
{
  auto string = std::string("Hello");
  auto view   = bit::stl::span<const char>(string);

  SECTION("Constructs a view out of a std::basic_string")
  {
    SECTION("Constructs a non-empty view")
    {
      REQUIRE_FALSE( view.empty() );
    }

    SECTION("Contains 5 elements")
    {
      REQUIRE( view.size() == 5 );
    }

    SECTION("Data points to original string")
    {
      REQUIRE( view.data() == string.data() );
    }
  }
}


//----------------------------------------------------------------------------
// Capacity
//----------------------------------------------------------------------------

TEST_CASE("span::size()", "[capacity]")
{
  SECTION("Returns size of view")
  {
    int array[] = {1,2,3,4,5};
    auto view   = bit::stl::span<int>(array);

    REQUIRE( view.size() == 5 );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("span::empty()", "[capacity]")
{
  SECTION("Determines empty view")
  {
    auto view = bit::stl::span<int>();

    REQUIRE( view.empty() );
  }

  SECTION("Determines non-empty view")
  {
    int array[] = {1,2,3,4,5};
    auto view = bit::stl::span<int>(array);

    REQUIRE_FALSE( view.empty() );
  }
}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

TEST_CASE("span::data()", "[accessor]")
{
  int array[] = {1,2,3,4,5};

  SECTION("Retrieves data to original array")
  {
    auto view = bit::stl::span<int>(array);

    REQUIRE( view.data() == array );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("span::operator[]( size_type )", "[accessor]")
{
  int array[] = {1,2,3,4,5};
  auto view = bit::stl::span<int>(array);

  SECTION("Returns reference to entry at position")
  {
    REQUIRE( &view[0] == array );
  }

  SECTION("Retrieves data value correctly")
  {
    REQUIRE( view[1] == 2 );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("span::at( size_type )", "[accessor]")
{

  int array[] = {1,2,3,4,5};
  auto view = bit::stl::span<int>(array);

  SECTION("Returns reference to entry at position")
  {
    REQUIRE( &view.at(0) == array );
  }

  SECTION("Retrieves data value correctly")
  {
    REQUIRE( view.at(1) == 2 );
  }

#if BIT_COMPILER_EXCEPTIONS_ENABLED
  SECTION("Throws when out of range")
  {
    REQUIRE_THROWS_AS(view.at(11),std::out_of_range&);
  }
#endif

}

//----------------------------------------------------------------------------

TEST_CASE("span::front()", "[accessor]")
{
  int array[] = {1,2,3,4,5};
  auto view = bit::stl::span<int>(array);

  SECTION("Returns reference to first entry")
  {
    REQUIRE( view.front() == 1 );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("span::back()", "[accessor]")
{
  int array[] = {1,2,3,4,5};
  auto view = bit::stl::span<int>(array);

  SECTION("Returns reference to last entry")
  {
    REQUIRE( view.back() == 5 );
  }
}

//----------------------------------------------------------------------------
// Operations
//----------------------------------------------------------------------------

TEST_CASE("span::copy( value_type*, size_type, size_type )","[operation]")
{
  int array[] = {1,2,3,4,5};
  auto view = bit::stl::span<int>(array);

#if BIT_COMPILER_EXCEPTIONS_ENABLED
  SECTION("Throws std::out_of_range if pos >= view.size()")
  {
    int result[5];

    REQUIRE_THROWS_AS( view.copy(result,11,11), std::out_of_range& );
  }
#endif

  SECTION("Returns number of entries copied")
  {
    int result[5];

    REQUIRE( view.copy(result,20)==5 );
  }

  SECTION("Copies entire array")
  {
    int result[5];
    view.copy(result,5);

    // todo: REQUIRE
  }

  SECTION("Copies remaining entries if count > size")
  {
    int result[11];
    view.copy(result,20);

    // todo: REQUIRE
  }

  SECTION("Copies part of the array")
  {
    int result[5];
    view.copy(result,5);

    // todo: REQUIRE
  }

  SECTION("Copies part of the array, offset from the beginning")
  {
    int result[5];
    view.copy(result,2,3);

    // todo: REQUIRE
  }
}

//----------------------------------------------------------------------------

TEST_CASE("span::subspan( size_type, size_type )","[operation]")
{
  int array[] = {1,2,3,4,5};
  bit::stl::span<int> view = array;

  SECTION("Returns the full string when given no args")
  {
    auto sublist = view.subspan(0);

    REQUIRE( view.data() == sublist.data() );
  }

#if BIT_COMPILER_EXCEPTIONS_ENABLED
  SECTION("Throws std::out_of_range if pos > size")
  {
    REQUIRE_THROWS_AS( view.subspan(12), std::out_of_range& );
  }
#endif

  SECTION("Returns last part of list")
  {
    // auto sublist = view.sublist(4);

    // todo: REQUIRE( sublist );
  }

  SECTION("Sublist returns at most count entries")
  {
    // auto sublist = view.sublist(4,5);

    // todo: REQUIRE( sublist );
  }

  SECTION("Returns up to end of array if length > size")
  {
    // auto sublist = view.sublist(4,10);

    // todo: REQUIRE( sublist );
  }
}
