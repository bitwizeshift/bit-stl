/**
 * \file string_hash.hpp
 *
 * \brief This header contains the implementation for string hashing
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */

#ifndef BIT_STL_CONTAINERS_DETAIL_STRING_HASH_HPP
#define BIT_STL_CONTAINERS_DETAIL_STRING_HASH_HPP

#include <cstdlib> // std::size_t

namespace bit {
  namespace stl {
    namespace detail {

      template<std::size_t> constexpr std::size_t fnv1_prime();
      template<std::size_t> constexpr std::size_t fnv1_offset();

      template<> constexpr std::size_t fnv1_prime<4>(){ return 16777619ul; }
      template<> constexpr std::size_t fnv1_prime<8>(){ return 1099511628211ull; }

      template<> constexpr std::size_t fnv1_offset<4>(){ return 2166136261ul; }
      template<> constexpr std::size_t fnv1_offset<8>(){ return 14695981039346656037ull; }

      template<typename CharT>
      constexpr std::size_t string_hash( const CharT* str, std::size_t count ) noexcept;

    } // namespace detail

    inline namespace literals {
      inline namespace hash_literals {

        constexpr std::size_t operator "" _hash( const char* str, std::size_t n ) noexcept;
        constexpr std::size_t operator "" _hash( const wchar_t* str , std::size_t n ) noexcept;
        constexpr std::size_t operator "" _hash( const char16_t* str , std::size_t n ) noexcept;
        constexpr std::size_t operator "" _hash( const char32_t* str , std::size_t n ) noexcept;

      } // inline namespace hash_literals
    } // inline namespace literals
  } // namespace stl
} // namespace bit

template<typename CharT>
inline constexpr std::size_t
  bit::stl::detail::string_hash( const CharT* str, std::size_t count )
  noexcept
{
  constexpr auto offset = detail::fnv1_offset<sizeof(std::size_t)>();
  constexpr auto prime  = detail::fnv1_prime<sizeof(std::size_t)>();

  auto result = offset;
  auto ptr    = str;
  while (count--)
  {
    result ^= static_cast<std::size_t>(*(ptr++));
    result *= prime;
  }
  return result;
}

inline constexpr std::size_t
  bit::stl::literals::hash_literals
  ::operator "" _hash( const char* str, std::size_t n )
  noexcept
{
  return detail::string_hash( str, n );
}

inline constexpr std::size_t
  bit::stl::literals::hash_literals
  ::operator "" _hash( const wchar_t* str, std::size_t n )
  noexcept
{
  return detail::string_hash( str, n );
}

inline constexpr std::size_t
  bit::stl::literals::hash_literals
  ::operator "" _hash( const char16_t* str, std::size_t n )
  noexcept
{
  return detail::string_hash( str, n );
}

inline constexpr std::size_t
  bit::stl::literals::hash_literals
  ::operator "" _hash( const char32_t* str, std::size_t n )
  noexcept
{
  return detail::string_hash( str, n );
}

#endif /* BIT_STL_CONTAINERS_DETAIL_STRING_HASH_HPP */
