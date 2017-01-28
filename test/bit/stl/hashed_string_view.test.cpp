/**
 * \file hashed_string_view.cpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#include <bit/stl/hashed_string_view.hpp>
#include <iostream>
#include "../../catch.hpp"

// hashes from https://www.tools4noobs.com/online_tools/hash/

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

TEST_CASE("hashed_string_view::hashed_string_view()")
{
  constexpr bit::stl::hashed_string_view view; // default-initialized view
  constexpr std::size_t hash = 0xcbf29ce484222325;

  SECTION("Returns 64-bit fnv1 offset")
  {
    REQUIRE( view.hash() == hash );
  }

  SECTION("Constructs empty string view")
  {
    REQUIRE( view.view() == "" );
  }
}

TEST_CASE("hashed_string_view::hashed_string_view( const char_type (&)[N] )")
{
  constexpr bit::stl::hashed_string_view view = "hello world";
  constexpr std::size_t hash = 0x779a65e7023cd2e7;

  SECTION("Returns 64-bit fnv1 hash")
  {
    REQUIRE( view.hash() == hash );
  }

  SECTION("Constructs string view containing string")
  {
    REQUIRE( view.view() == "hello world" );
  }
}

TEST_CASE("hashed_string_view::hashed_string_view( const std::string& )")
{
  std::string str = "hello world";
  bit::stl::hashed_string_view view = str;
  std::size_t hash = 0x779a65e7023cd2e7;

  SECTION("Returns 64-bit fnv1 hash")
  {
    REQUIRE( view.hash() == hash );
  }

  SECTION("Constructs string view containing string")
  {
    REQUIRE( view.view() == "hello world" );
  }
}

TEST_CASE("hashed_string_view::hashed_string_view( const_type_wrapper<char_type> )")
{
//  const char* str = "hello world";
//  bit::stl::hashed_string_view view = str;
//  bit::stl::hash_t hash = 0x779a65e7023cd2e7;
//
//  SECTION("Returns 64-bit fnv1 hash")
//  {
//    REQUIRE( view.hash() == hash );
//  }
//
//  SECTION("Constructs string view containing string")
//  {
//    REQUIRE( view.view() == "hello world" );
//  }
}


TEST_CASE("hashed_string_view::hashed_string_view( const char_type*, size_t )")
{
  constexpr auto view = bit::stl::hashed_string_view("hello world",5);

  SECTION("Hashes only first 5 characters")
  {
    REQUIRE( view.hash() == 0xa430d84680aabd0b );
  }

  SECTION("Constructs string view containing string")
  {
    REQUIRE( view.view() == "hello" );
  }
}

//----------------------------------------------------------------------------
// Accessors
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Comparisons
//----------------------------------------------------------------------------
