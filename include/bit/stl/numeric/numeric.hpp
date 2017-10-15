/**
 * \file numeric.hpp
 *
 * \brief
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_NUMERIC_HPP
#define BIT_STL_NUMERIC_HPP

#include <cstdint>
#include <type_traits>
#include <cmath>

namespace bit {
  namespace stl {

    //------------------------------------------------------------------------
    // Runtime Mathematics
    //------------------------------------------------------------------------

    /// \brief Computes the greatest common divisor of the integers \p m and \p n
    ///
    /// \param a the first integer value
    /// \param b the second integer value
    /// \return The greatest common divisor
    template<typename T, typename U>
    constexpr std::common_type_t<T,U> gcd( const T& a, const U& b ) noexcept;

    /// \brief Computes the least common multiple of the integers \p m and \p n
    ///
    /// \param a the first integer value
    /// \param b the second integer value
    /// \return The least-common multiple of \p a and \p b
    template<typename T, typename U>
    constexpr std::common_type_t<T,U> lcm( const T& a, const U& b ) noexcept;

    //------------------------------------------------------------------------
    // Static Mathematics
    //------------------------------------------------------------------------

    /// \brief Calculates the greatest common denominator of \p a and \p b
    ///        The result is aliased as \a static_gcd::value
    template<std::intmax_t a, std::intmax_t b>
    struct static_gcd : std::integral_constant<std::intmax_t, static_gcd<b%a,a>::value>{};

    template<std::intmax_t b>
    struct static_gcd<0,b> : std::integral_constant<std::intmax_t,b>{};

    //---------------------------------------------------------------------------

    template<std::intmax_t a, std::intmax_t b>
    struct static_lcm : std::integral_constant<std::intmax_t, ( (a > b ? b : a) / static_gcd<a,b>::value) * (a > b ? a : b)>{};

    //---------------------------------------------------------------------------

    template<std::uintmax_t v, std::uintmax_t a, std::uintmax_t b>
    struct static_divisible_by_range : std::integral_constant<bool,!(v%a) || static_divisible_by_range<v, a+1,b>::value>{};

    template<std::uintmax_t v, std::uintmax_t b>
    struct static_divisible_by_range<v,b,b> : std::integral_constant<bool,!(v%b)>{};

    //---------------------------------------------------------------------------

    template<std::uintmax_t p>
    struct static_is_prime : static_divisible_by_range<p,2,p/2+p%2>{};

    template<>
    struct static_is_prime<0> : std::false_type{};

    template<>
    struct static_is_prime<1> : std::false_type{};

    template<>
    struct static_is_prime<2> : std::true_type{};

    //---------------------------------------------------------------------------

    /// Calculate the sum of the values between a and b
    /// The result is aliased as static_sum_of_range::value
    template<std::uintmax_t a, std::uintmax_t b>
    struct static_sum_of_range : std::integral_constant<std::uintmax_t, ((b)*(b+1) - (a)*(a+1))/2>{};

    /// Calculate the square sum of the values between a and b
    /// The result is aliased as static_square_sum_of_range::value
    template<std::uintmax_t a, std::uintmax_t b>
    struct static_square_sum_of_range : std::integral_constant<std::uintmax_t, ((b*b*b)/3 + b*b/2 + b/6) - ((a*a*a)/3 + a*a/2 + a/6)>{};

  } // namespace stl
} // namespace bit

#include "detail/numeric.inl"

#endif /* BIT_STL_NUMERIC_HPP */
