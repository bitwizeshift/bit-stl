/*****************************************************************************
 * \file
 * \brief This file unit tests the compressed_pair from utility.hpp
 *****************************************************************************/

#include <bit/stl/utilities/compressed_pair.hpp>

#include <catch.hpp>

namespace
{
  template<std::size_t>
  struct empty_final final
  {

  };

  template<std::size_t>
  struct non_empty_final final
  {
    int i = 42;
  };

  template<std::size_t>
  struct empty_non_final
  {

  };

  template<std::size_t>
  struct non_empty_non_final
  {
    int i = 42;
  };

} // anonymous namespace

TEST_CASE("compressed_pair( T1&&, T2&& )")
{
  SECTION("T1 and T2 are the same classification")
  {
    SECTION("T1 & T2 are empty, non-final")
    {
      auto pair = bit::stl::make_compressed_pair(empty_non_final<0>{},empty_non_final<1>{});

      REQUIRE( sizeof(pair) == sizeof(empty_non_final<0>) );
    }
    SECTION("T1 & T2 are non-empty, non-final")
    {
      auto pair = bit::stl::make_compressed_pair(non_empty_non_final<0>{},non_empty_non_final<1>{});

      REQUIRE( sizeof(pair) >= sizeof(non_empty_non_final<0>)*2 );
    }
    SECTION("T1 & T2 are empty, final")
    {
      auto pair = bit::stl::make_compressed_pair(empty_final<0>{},empty_final<1>{});

      REQUIRE( sizeof(pair) >= sizeof(empty_final<0>)*2 );
    }
    SECTION("T1 & T2 are non-empty, final")
    {
      auto pair = bit::stl::make_compressed_pair(non_empty_final<0>{},non_empty_final<1>{});

      REQUIRE( sizeof(pair) >= sizeof(non_empty_final<1>)*2 );
    }
  }

  SECTION("T1 and T2 are different classifications")
  {
    SECTION("T1 is empty, non-final & T2 is non-empty, non-final")
    {
      auto pair = bit::stl::make_compressed_pair(empty_non_final<0>{},non_empty_non_final<0>{});

      REQUIRE( sizeof(pair) == sizeof(non_empty_non_final<0>) );
    }
    SECTION("T1 is non-empty, non-final & T2 is empty, non-final")
    {
      auto pair = bit::stl::make_compressed_pair(non_empty_non_final<0>{},empty_non_final<0>{});

      REQUIRE( sizeof(pair) == sizeof(non_empty_non_final<0>) );
    }

    //------------------------------------------------------------------------

    SECTION("T1 is empty, final & T2 is non-empty, non-final")
    {
      auto pair = bit::stl::make_compressed_pair(empty_final<0>{},non_empty_non_final<0>{});

      REQUIRE( sizeof(pair) >= sizeof(non_empty_non_final<0>) );
    }
    SECTION("T1 is non-empty, non-final & T2 is empty, final")
    {
      auto pair = bit::stl::make_compressed_pair(non_empty_non_final<0>{},empty_final<0>{});

      REQUIRE( sizeof(pair) >= sizeof(non_empty_non_final<0>) );
    }

    //------------------------------------------------------------------------

    SECTION("T1 is empty, non-final & T2 is non-empty, final")
    {
      auto pair = bit::stl::make_compressed_pair(empty_non_final<0>{},non_empty_final<0>{});

      REQUIRE( sizeof(pair) == sizeof(non_empty_final<0>) );
    }
    SECTION("T1 is non-empty, final & T2 is empty, non-final")
    {
      auto pair = bit::stl::make_compressed_pair(non_empty_final<0>{},empty_non_final<0>{});

      REQUIRE( sizeof(pair) == sizeof(non_empty_final<0>) );
    }
  }
}
