/**
 * \file compressed_pair.hpp
 *
 * \brief This header contains a utility for compressing pairs that leverages
 *        EBO
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */

#ifndef BIT_STL_DETAIL_UTILITY_COMPRESSED_PAIR_HPP
#define BIT_STL_DETAIL_UTILITY_COMPRESSED_PAIR_HPP

#include <type_traits>

namespace bit {
  namespace stl {
    namespace detail {
      template<typename T1, typename T2, bool = std::is_final<T1>::value, bool = std::is_final<T2>::value>
      class compressed_pair_impl;

      template<typename T1>
      class compressed_pair_impl<T1,T1,false,false> : T1
      {
      public:
        template<typename U1, typename U2>
        constexpr compressed_pair_impl( U1&& u1, U2&& u2 ) : T1(std::forward<U1>(u1)), m_second(std::forward<U2>(u2)){}
        constexpr T1& first(){ return (*this); }
        constexpr T1& second(){ return m_second; }
      private:
        T1 m_second;
      };

      template<typename T1, typename T2>
      class compressed_pair_impl<T1,T2,false,false> : T1, T2
      {
      public:
        template<typename U1, typename U2>
        constexpr compressed_pair_impl( U1&& u1, U2&& u2 ) : T1(std::forward<U1>(u1)), T2(std::forward<U2>(u2)){}
        constexpr T1& first(){ return (*this); }
        constexpr T2& second(){ return (*this); }
      };

      template<typename T1, typename T2>
      class compressed_pair_impl<T1,T2,false,true> : T1
      {
      public:
        template<typename U1, typename U2>
        constexpr compressed_pair_impl( U1&& u1, U2&& u2 ) : T1(std::forward<U1>(u1)), m_second(std::forward<U2>(u2)){}
        constexpr T1& first(){ return (*this); }
        constexpr T2& second(){ return m_second; }
      private:
        T2 m_second;
      };

      template<typename T1, typename T2>
      class compressed_pair_impl<T1,T2,true,false> : T2
      {
      public:
        template<typename U1, typename U2>
        constexpr compressed_pair_impl( U1&& u1, U2&& u2 ) : T2(std::forward<U2>(u2)), m_first(std::forward<U1>(u1)){}
        constexpr T1& first(){ return m_first; }
        constexpr T2& second(){ return (*this); }
      private:
        T1 m_first;
      };

      template<typename T1, typename T2>
      class compressed_pair_impl<T1,T2,true,true>
      {
      public:
        template<typename U1, typename U2>
        constexpr compressed_pair_impl( U1&& u1, U2&& u2 ) : m_first(std::forward<U1>(u1)), m_second(std::forward<U2>(u2)){}
        constexpr T1& first(){ return m_first; }
        constexpr T2& second(){ return (*this); }
      private:
        T1 m_first;
        T2 m_second;
      };

    } // namespace detail

    template<typename T1, typename T2>
    class compressed_pair : public detail::compressed_pair_impl<T1,T2>
    {
    public:

      constexpr compressed_pair() = default;

      constexpr compressed_pair( const compressed_pair& other ) = default;

      constexpr compressed_pair( compressed_pair&& other ) = default;

      template<typename U1, typename U2>
      constexpr compressed_pair( U1&& u1, U2&& u2 ) : detail::compressed_pair_impl<T1,T2>( std::forward<U1>(u1), std::forward<U2>(u2) ){}
    };

    template<typename T1, typename T2>
    constexpr compressed_pair<std::decay_t<T1>,std::decay_t<T2>>
      make_compressed_pair( T1&& t1, T2&& t2 )
    {
      return {std::forward<T1>(t1),std::forward<T2>(t2)};
    }

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_DETAIL_UTILITY_COMPRESSED_PAIR_HPP */
