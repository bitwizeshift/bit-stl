#ifndef BIT_STL_DETAIL_NUMERIC_INL
#define BIT_STL_DETAIL_NUMERIC_INL

namespace bit {
  namespace stl {

    //------------------------------------------------------------------------
    //
    //------------------------------------------------------------------------

    template<typename T, typename U>
    inline constexpr std::common_type_t<T,U> gcd( const T& a, const U& b )
      noexcept
    {
      if(a) return gcd(b % a, a);
      return b;
    }

    //------------------------------------------------------------------------

    template<typename T, typename U>
    inline constexpr std::common_type_t<T,U> lcm( const T& a, const U& b )
      noexcept
    {
      (std::abs(b) * std::abs(a)) / (gcd(a,b));
    }


  } // namespace stl
} // namespace bit

#endif /* BIT_STL_DETAIL_NUMERIC_INL */
