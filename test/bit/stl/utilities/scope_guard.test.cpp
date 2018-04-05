/*****************************************************************************
 * \file
 * \brief TODO: Add description
 *****************************************************************************/

#include <bit/stl/utilities/scope_guard.hpp>

#include <catch.hpp>

TEST_CASE("bit::stl::on_scope_exit( Fn&& fn )", "[raii]")
{
  bool flag = false;

  SECTION("Executes on clean scope exit")
  {
    {
      auto scope = bit::stl::on_scope_exit([&]()
      {
        flag = true;
      });
    }

    REQUIRE( flag == true );
  }

  SECTION("Executes on exception scope exit")
  {
    try {
      auto scope = bit::stl::on_scope_exit([&]()
      {
        flag = true;
      });
      throw std::exception();
    } catch (...) {}

    REQUIRE( flag == true );
  }
}

TEST_CASE("bit::stl::on_scope_error_exit( Fn&& fn )", "[raii]")
{
  bool flag = false;

  SECTION("Does not execute on clean scope exit")
  {
    {
      auto scope = bit::stl::on_scope_error_exit([&]()
      {
        flag = true;
      });
    }

    REQUIRE( flag == false );
  }

  SECTION("Executes on exception scope exit")
  {
    try {
      auto scope = bit::stl::on_scope_error_exit([&]()
      {
        flag = true;
      });
      throw std::exception();
    } catch (...) {}

    REQUIRE( flag == true );
  }
}

TEST_CASE("bit::stl::on_scope_clean_exit( Fn&& fn )", "[raii]")
{
  bool flag = false;

  SECTION("Executes on clean scope exit")
  {
    {
      auto scope = bit::stl::on_scope_clean_exit([&]()
      {
        flag = true;
      });
    }

    REQUIRE( flag == true );
  }

  SECTION("Does not execute on exception scope exit")
  {
    try {
      auto scope = bit::stl::on_scope_clean_exit([&]()
      {
        flag = true;
      });
      throw std::exception();
    } catch (...) {}

    REQUIRE( flag == false );
  }
}
