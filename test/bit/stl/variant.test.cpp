/**
 * \file variant.test.cpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#include <bit/stl/variant.hpp>

#include <string>
#include <iostream>

#include <catch.hpp>

class squawker1
{
public:
  squawker1()
  {
    std::cout << "squawker1()\n";
  }

  squawker1( const squawker1& )
  {
    std::cout << "squawker1( const squawker1& )\n";
  }

  squawker1( squawker1&& )
  {
    std::cout << "squawker1( squawker1&& )\n";
  }

  squawker1( int v )
  {
    std::cout << "squawker1( " << v << " )\n";
  }

  ~squawker1()
  {
    std::cout << "~squawker1()\n";
  }

  squawker1& operator=( const squawker1& other ){ return (*this); };
  squawker1& operator=( squawker1&& other ){ return (*this); };
};

class squawker2
{
public:
  squawker2()
  {
    std::cout << "squawker2()\n";
  }

  squawker2( const squawker2& )
  {
    std::cout << "squawker2( const squawker2& )\n";
  }

  squawker2( squawker2&& )
  {
    std::cout << "squawker2( squawker2&& )\n";
  }

  squawker2( float v )
  {
    std::cout << "squawker2( " << v << " )\n";
  }

  ~squawker2()
  {
    std::cout << "~squawker2()\n";
  }

  squawker2& operator=( const squawker2& other ){ return (*this); };
  squawker2& operator=( squawker2&& other ){ return (*this); };
};

class squawker3
{
public:
  squawker3()
  {
    std::cout << "squawker3()\n";
  }

  squawker3( const squawker3& )
  {
    std::cout << "squawker3( const squawker3& )\n";
  }

  squawker3( squawker3&& )
  {
    std::cout << "squawker3( squawker3&& )\n";
  }

  template<std::size_t N>
  squawker3( char(&v)[N] )
  {
    std::cout << "squawker3( " << v << " )\n";
  }

  template<std::size_t N>
  squawker3( const char(&v)[N] )
  {
    std::cout << "squawker3( " << v << " )\n";
  }

  ~squawker3()
  {
    std::cout << "~squawker3()\n";
  }

  squawker3& operator=( const squawker3& other ){ return (*this); };
  squawker3& operator=( squawker3&& other ){ return (*this); };
};

void f(int){ std::cout << "f(int)\n"; }
void f(float){ std::cout << "f(float)\n"; }
void f(std::string){ std::cout << "f(std::string)\n"; }

TEST_CASE("variant::variant()")
{
  using variant_type = bit::stl::variant<squawker1,squawker3>;

  std::cout << bit::stl::detail::conversion_index<int,variant_type>::value << std::endl;
  std::cout << bit::stl::detail::conversion_index<double,variant_type>::value << std::endl;
  std::cout << bit::stl::detail::conversion_index<char(&)[18],variant_type>::value << std::endl;
  std::cout << bit::stl::detail::conversion_index<bool,variant_type>::value << std::endl;

  variant_type v0;
  variant_type v1 = 42;
  variant_type v2 = "hello world";

  variant_type v3 = v1;
  variant_type v4 = v2;

  variant_type v5 = std::move(v3);
  variant_type v6 = std::move(v4);

  v3 = std::move(v2);
  v4 = std::move(v1);

  v3 = v6;
  v4 = v5;

}
