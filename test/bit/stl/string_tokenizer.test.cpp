/**
 * \file string_tokenizer.test.cpp
 *
 * \brief Test cases for the bit::stl::basic_string_tokenizer
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#include <bit/stl/string_tokenizer.hpp>

#include <catch.hpp>

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

TEST_CASE("string_tokenizer::string_tokenizer( string_type, string_type, bool )", "[ctor]")
{
  SECTION("string_tokenizer( string_type )")
  {
    auto tokenizer = bit::stl::string_tokenizer("Hello World", " ");

    SECTION("Has non-empty buffer")
    {
      REQUIRE( tokenizer.buffer() != "" );
    }

    SECTION("Has default delimiters")
    {
      REQUIRE( tokenizer.delimiters() == " " );
    }

    SECTION("Does not keep delimiters")
    {
      REQUIRE_FALSE( tokenizer.keeps_delimiter() );
    }
  }

  //--------------------------------------------------------------------------

  SECTION("string_tokenizer( string_type, string_type )")
  {
    auto tokenizer = bit::stl::string_tokenizer("Hello World",";,");

    SECTION("Has non-empty buffer")
    {
      REQUIRE( tokenizer.buffer() != "" );
    }

    SECTION("Has default delimiters")
    {
      REQUIRE( tokenizer.delimiters() == ";," );
    }

    SECTION("Does not keep delimiters")
    {
      REQUIRE_FALSE( tokenizer.keeps_delimiter() );
    }
  }

  //--------------------------------------------------------------------------

  SECTION("string_tokenizer( string_type, string_type, bool )")
  {
    auto tokenizer = bit::stl::string_tokenizer("Hello World",";,", true);

    SECTION("Has non-empty buffer")
    {
      REQUIRE( tokenizer.buffer() != "" );
    }

    SECTION("Has default delimiters")
    {
      REQUIRE( tokenizer.delimiters() == ";," );
    }

    SECTION("Keeps delimiters")
    {
      REQUIRE( tokenizer.keeps_delimiter() );
    }
  }
}

//----------------------------------------------------------------------------
// Accessors
//----------------------------------------------------------------------------

TEST_CASE("string_tokenizer::buffer()")
{
  auto tokenizer = bit::stl::string_tokenizer("Hello World", " ");

  SECTION("Returns the buffer")
  {
    REQUIRE( tokenizer.buffer() == "Hello World" );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_tokenizer::delimiters()")
{
  auto tokenizer = bit::stl::string_tokenizer("","\n\r\t");

  SECTION("Returns the delimiter")
  {
    REQUIRE( tokenizer.delimiters() == "\n\r\t" );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_tokenizer::keep_delimiter()")
{
  SECTION("Has return delimiter flag when set")
  {
    auto tokenizer = bit::stl::string_tokenizer("","\n\r\t",true);
    REQUIRE( tokenizer.keeps_delimiter() );
  }

  SECTION("Doesn't have delimiter flag when set")
  {
    auto tokenizer = bit::stl::string_tokenizer("","\n\r\t",false);
    REQUIRE_FALSE( tokenizer.keeps_delimiter() );
  }
}

//----------------------------------------------------------------------------
// Tokenizing
//----------------------------------------------------------------------------

TEST_CASE("string_tokenizer::has_more()")
{
  SECTION("Doesn't have more tokens with empty string")
  {
    auto tokenizer = bit::stl::string_tokenizer("", " ");

    REQUIRE_FALSE( tokenizer.has_more() );
  }

  SECTION("Has more before tokenizing")
  {
    auto tokenizer = bit::stl::string_tokenizer("Hello World", " ");

    REQUIRE( tokenizer.has_more() );
  }

  SECTION("Doesn't have more after tokenizing")
  {
    auto tokenizer = bit::stl::string_tokenizer("Hello World", " ");

    tokenizer.next();
    tokenizer.next();

    REQUIRE_FALSE( tokenizer.has_more() );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_tokenizer::next()")
{
  SECTION("Tokenize empty string")
  {
    auto tokenizer = bit::stl::string_tokenizer("", " ");

    SECTION("Retrieves empty string token")
    {
      REQUIRE( tokenizer.next() == "" );
    }
  }

  SECTION("Tokenize without delimiters")
  {
    auto tokenizer = bit::stl::string_tokenizer("Hello World", " ");

    SECTION("Retrieves first token")
    {
      REQUIRE( tokenizer.next() == "Hello" );
    }

    SECTION("Retrieves second token")
    {
      tokenizer.next();

      REQUIRE( tokenizer.next() == "World" );
    }

    SECTION("Retrieves empty string token")
    {
      tokenizer.next();
      tokenizer.next();

      REQUIRE( tokenizer.next() == "" );
    }
  }

  SECTION("Tokenize with delimiters as token (single delimiter)")
  {
    auto tokenizer = bit::stl::string_tokenizer("Hello World", " ", true);

    auto t1 = tokenizer.next();
    auto t2 = tokenizer.next();
    auto t3 = tokenizer.next();
    auto t4 = tokenizer.next();

    SECTION("Retrieves first token")
    {
      REQUIRE( t1 == "Hello" );
    }

    SECTION("Retrieves the delimiter")
    {
      REQUIRE( t2 == " " );
    }

    SECTION("Retrieves the second token")
    {
      REQUIRE( t3 == "World" );
    }

    SECTION("Retrieves empty string (end of tokenizing)")
    {
      REQUIRE( t4 == "" );
    }
  }

  SECTION("Tokenize with delimiters as token (multiple delimiters)")
  {
    auto tokenizer = bit::stl::string_tokenizer("apples;bananas,oranges:", ";,:", true);

    auto t1 = tokenizer.next(); // apples
    auto t2 = tokenizer.next(); // ;
    auto t3 = tokenizer.next(); // bananas
    auto t4 = tokenizer.next(); // ,
    auto t5 = tokenizer.next(); // oranges
    auto t6 = tokenizer.next(); // :
    auto t7 = tokenizer.next(); // ""

    SECTION("Retrieves first word")
    {
      REQUIRE( t1 == "apples" );
    }

    SECTION("Retrieves first delimiter")
    {
      REQUIRE( t2 == ";");
    }

    SECTION("Retrieves second word")
    {
      REQUIRE( t3 == "bananas" );
    }

    SECTION("Retrieves second delimiter")
    {
      REQUIRE( t4 == "," );
    }

    SECTION("Retrieves third word")
    {
      REQUIRE( t5 == "oranges");
    }

    SECTION("Retrieves third delimiter")
    {
      REQUIRE( t6 == ":" );
    }

    SECTION("Retrieves empty string (end of tokenizing)")
    {
      REQUIRE( t7 == "" );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_tokenizer::next( const string_type& )")
{
  SECTION("Tokenize empty string")
  {
    auto tokenizer = bit::stl::string_tokenizer("", " ");

    SECTION("Retrieves empty string token")
    {
      REQUIRE( tokenizer.next(";") == "" );
    }
  }

  SECTION("Tokenize with empty delimiters")
  {
    auto tokenizer = bit::stl::string_tokenizer("Hello World", " ");

    SECTION("Retrieves entire string")
    {
      REQUIRE( tokenizer.next("") == "Hello World" );
    }
  }

  SECTION("Tokenize with multiple delimiters")
  {
    auto tokenizer = bit::stl::string_tokenizer("apples;bananas,oranges:","",true);

    auto t1 = tokenizer.next(";,:"); // apples
    auto t2 = tokenizer.next(";,:"); // ;
    auto t3 = tokenizer.next(";,:"); // bananas
    auto t4 = tokenizer.next(";,:"); // ,
    auto t5 = tokenizer.next(";,:"); // oranges
    auto t6 = tokenizer.next(";,:"); // :
    auto t7 = tokenizer.next(";,:"); // ""

    SECTION("Retrieves first word")
    {
      REQUIRE( t1 == "apples" );
    }

    SECTION("Retrieves first delimiter")
    {
      REQUIRE( t2 == ";");
    }

    SECTION("Retrieves second word")
    {
      REQUIRE( t3 == "bananas" );
    }

    SECTION("Retrieves second delimiter")
    {
      REQUIRE( t4 == "," );
    }

    SECTION("Retrieves third word")
    {
      REQUIRE( t5 == "oranges");
    }

    SECTION("Retrieves third delimiter")
    {
      REQUIRE( t6 == ":" );
    }

    SECTION("Retrieves empty string (end of tokenizing)")
    {
      REQUIRE( t7 == "" );
    }
  }
}
