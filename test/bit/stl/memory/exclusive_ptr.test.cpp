/*****************************************************************************
 * \file
 * \brief Tests cases for the exclusive_ptr header
 *****************************************************************************/

#include <bit/stl/memory/exclusive_ptr.hpp>

#include <catch.hpp>

namespace
{
  class base
  {
  public:
    virtual ~base() = default;
  };

  class derived : public base{};
}

//=============================================================================
// exclusive_ptr
//=============================================================================

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

TEST_CASE("exclusive_ptr<T>::exclusive_ptr()")
{
  auto ptr = bit::stl::exclusive_ptr<::base>{};

  SECTION("points to null")
  {
    REQUIRE( ptr == nullptr );
  }
}

TEST_CASE("exclusive_ptr<T>::exclusive_ptr( std::nullptr_t )")
{
  bit::stl::exclusive_ptr<::base> ptr = nullptr;

  SECTION("points to null")
  {
    REQUIRE( ptr == nullptr );
  }
}

TEST_CASE("exclusive_ptr<T>::exclusive_ptr( exclusive_ptr&& )")
{
  auto p1 = bit::stl::make_exclusive<::derived>();
  auto p1_old = p1.get();
  auto p2 = std::move(p1);

  SECTION("owns p1's old memory")
  {
    REQUIRE( p2.get() == p1_old );
  }
  SECTION("p1 is null after move")
  {
    REQUIRE( p1 == nullptr );
  }
}

TEST_CASE("exclusive_ptr<T>::exclusive_ptr( exclusive_ptr<U>&& )")
{
  auto p1 = bit::stl::make_exclusive<::derived>();
  auto p1_old = p1.get();
  auto p2 = bit::stl::exclusive_ptr<::base>(std::move(p1));

  SECTION("owns p1's old memory")
  {
    REQUIRE( p2.get() == p1_old );
  }
  SECTION("p1 is null after move")
  {
    REQUIRE( p1 == nullptr );
  }
}

//-----------------------------------------------------------------------------

TEST_CASE("exclusive_ptr<T>::operator=( exclusive_ptr&& )")
{
  auto p = bit::stl::make_exclusive<::derived>();
  auto p_old = p.get();

  p = bit::stl::make_exclusive<::derived>();

  SECTION("no longer refers to p1's old memory")
  {
    REQUIRE( p.get() != p_old );
  }
}

TEST_CASE("exclusive_ptr<T>::operator=( exclusive_ptr<U>&& )")
{
  auto p = bit::stl::make_exclusive<::base>();
  auto p_old = p.get();

  p = bit::stl::make_exclusive<::derived>();

  SECTION("no longer refers to p1's old memory")
  {
    REQUIRE( p.get() != p_old );
  }
}

//=============================================================================
// casts
//=============================================================================

TEST_CASE("casts::dynamic_pointer_cast<T>( exclusive_ptr<U>&& )")
{
  using namespace bit::stl::casts;

  auto p1 = bit::stl::make_exclusive<::derived>();
  auto p1_old = p1.get();
  auto p2 = bit::stl::exclusive_ptr<::base>(std::move(p1));

  SECTION("Casted type is unrelated")
  {
    struct unrelated{};

    auto p3 = dynamic_pointer_cast<unrelated>(std::move(p2));

    SECTION("Result is null")
    {
      REQUIRE( p3 == nullptr );
    }

    SECTION("p2 remains unchanged")
    {
      REQUIRE( p2.get() == p1_old );
    }
  }

  SECTION("Casted type is related")
  {
    auto p3 = dynamic_pointer_cast<::base>(std::move(p2));

    SECTION("Result points to original instance")
    {
      REQUIRE( p3.get() == p1_old );
    }
  }
}

TEST_CASE("casts::const_pointer_cast<T>( exclusive_ptr<U>&& )")
{
  using namespace bit::stl::casts;

  auto p1 = bit::stl::make_exclusive<::derived>();
  auto p1_old = p1.get();
  auto p2 = bit::stl::exclusive_ptr<const ::derived>(std::move(p1));
  auto p3 = const_pointer_cast<::derived>(std::move(p2));

  SECTION("Is const casted back to original pointer")
  {
    REQUIRE( p3.get() == p1_old );
  }
}

TEST_CASE("casts::reinterpret_pointer_cast<T>( exclusive_ptr<U>&& )")
{
  using namespace bit::stl::casts;

  auto p1 = bit::stl::make_exclusive<::derived>();
  auto p1_old = p1.get();
  auto p2 = bit::stl::exclusive_ptr<void>(std::move(p1));
  auto p3 = reinterpret_pointer_cast<::derived>(std::move(p2));

  SECTION("Is reinterpret casted back to original pointer")
  {
    REQUIRE( p3.get() == p1_old );
  }
}

//-----------------------------------------------------------------------------
