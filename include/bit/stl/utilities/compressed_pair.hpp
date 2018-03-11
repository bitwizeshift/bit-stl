/**
 * \file compressed_pair.hpp
 *
 * \brief This header contains a utility for compressing pairs that leverages
 *        EBO
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

/*
  The MIT License (MIT)

  Bit Standard Template Library.
  https://github.com/bitwizeshift/bit-stl

  Copyright (c) 2018 Matthew Rodusek

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#ifndef BIT_STL_UTILITIES_COMPRESSED_PAIR_HPP
#define BIT_STL_UTILITIES_COMPRESSED_PAIR_HPP

#include "hash.hpp"

#include "detail/tuple_size.hpp"
#include "detail/tuple_element.hpp"

#include "../traits/composition/identity.hpp"
#include "../traits/composition/conjunction.hpp"
#include "../traits/composition/disjunction.hpp"
#include "../traits/composition/negation.hpp"
#include "../traits/composition/size_constant.hpp"

#include <type_traits> // std::is_constructible, std::decay_t, etc...
#include <tuple>       // std::get
#include <utility>     // std::forward

namespace bit {
  namespace stl {
    namespace detail {
      template<typename T1,
               typename T2,
               bool = std::is_empty<T1>::value && !std::is_final<T1>::value,
               bool = std::is_empty<T2>::value && !std::is_final<T2>::value>
      class compressed_pair_impl;

      //-----------------------------------------------------------------------

      template<typename T1>
      class compressed_pair_impl<T1,T1,true,true> : T1
      {
      public:
        template<typename U1, typename U2>
        constexpr compressed_pair_impl( U1&& u1, U2&& u2 ) : T1(std::forward<U1>(u1)), m_second(std::forward<U2>(u2)){}

        template<typename Tuple1, typename Tuple2, std::size_t...Idxs1, std::size_t...Idxs2>
        constexpr compressed_pair_impl( Tuple1&& tuple1, Tuple2&& tuple2, std::index_sequence<Idxs1...>, std::index_sequence<Idxs2...> )
          : T1( std::get<Idxs1>( std::forward<Tuple1>(tuple1) )... ),
            m_second( std::get<Idxs2>( std::forward<Tuple2>(tuple2) )... )
        {

        }

        constexpr T1& first(){ return static_cast<T1&>(*this); }
        constexpr const T1& first() const{ return static_cast<const T1&>(*this); }

        constexpr T1& second(){ return m_second; }
        constexpr const T1& second() const{ return m_second; }
      private:
        T1 m_second;
      };

      //-----------------------------------------------------------------------

      template<typename T1, typename T2>
      class compressed_pair_impl<T1,T2,true,true> : T1, T2
      {
      public:
        template<typename U1, typename U2>
        constexpr compressed_pair_impl( U1&& u1, U2&& u2 ) : T1(std::forward<U1>(u1)), T2(std::forward<U2>(u2)){}

        template<typename Tuple1, typename Tuple2, std::size_t...Idxs1, std::size_t...Idxs2>
        constexpr compressed_pair_impl( Tuple1&& tuple1, Tuple2&& tuple2, std::index_sequence<Idxs1...>, std::index_sequence<Idxs2...> )
          : T1( std::get<Idxs1>( std::forward<Tuple1>(tuple1) )... ),
            T2( std::get<Idxs2>( std::forward<Tuple2>(tuple2) )... )
        {

        }

        constexpr T1& first(){ return static_cast<T1&>(*this); }
        constexpr const T1& first() const{ return static_cast<const T1&>(*this); }

        constexpr T2& second(){ return static_cast<T2&>(*this); }
        constexpr const T2& second() const{ return static_cast<const T2&>(*this); }
      };

      //-----------------------------------------------------------------------

      template<typename T1, typename T2>
      class compressed_pair_impl<T1,T2,true,false> : T1
      {
      public:
        template<typename U1, typename U2>
        constexpr compressed_pair_impl( U1&& u1, U2&& u2 ) : T1(std::forward<U1>(u1)), m_second(std::forward<U2>(u2)){}

        template<typename Tuple1, typename Tuple2, std::size_t...Idxs1, std::size_t...Idxs2>
        constexpr compressed_pair_impl( Tuple1&& tuple1, Tuple2&& tuple2, std::index_sequence<Idxs1...>, std::index_sequence<Idxs2...> )
          : T1( std::get<Idxs1>( std::forward<Tuple1>(tuple1) )... ),
            m_second( std::get<Idxs2>( std::forward<Tuple2>(tuple2) )... )
        {

        }

        constexpr T1& first(){ return static_cast<T1&>(*this); }
        constexpr const T1& first() const{ return static_cast<const T1&>(*this); }

        constexpr T2& second(){ return m_second; }
        constexpr const T2& second() const{ return m_second; }

        //---------------------------------------------------------------------
        // Private Members
        //---------------------------------------------------------------------
      private:

        T2 m_second;
      };

      //-----------------------------------------------------------------------

      template<typename T1, typename T2>
      class compressed_pair_impl<T1,T2,false,true> : T2
      {
      public:
        template<typename U1, typename U2>
        constexpr compressed_pair_impl( U1&& u1, U2&& u2 ) : T2(std::forward<U2>(u2)), m_first(std::forward<U1>(u1)){}

        template<typename Tuple1, typename Tuple2, std::size_t...Idxs1, std::size_t...Idxs2>
        constexpr compressed_pair_impl( Tuple1&& tuple1, Tuple2&& tuple2, std::index_sequence<Idxs1...>, std::index_sequence<Idxs2...> )
          : T2( std::get<Idxs2>( std::forward<Tuple2>(tuple2) )... ),
            m_first( std::get<Idxs1>( std::forward<Tuple1>(tuple1) )... )
        {

        }

        constexpr T1& first(){ return m_first; }
        constexpr const T1& first() const{ return m_first; }

        constexpr T2& second(){ return static_cast<T2&>(*this); }
        constexpr const T2& second() const{ return static_cast<const T2&>(*this); }

        //---------------------------------------------------------------------
        // Private Members
        //---------------------------------------------------------------------
      private:

        T1 m_first;
      };

      //-----------------------------------------------------------------------

      template<typename T1, typename T2>
      class compressed_pair_impl<T1,T2,false,false>
      {
      public:
        template<typename U1, typename U2>
        constexpr compressed_pair_impl( U1&& u1, U2&& u2 ) : m_first(std::forward<U1>(u1)), m_second(std::forward<U2>(u2)){}

        template<typename Tuple1, typename Tuple2, std::size_t...Idxs1, std::size_t...Idxs2>
        constexpr compressed_pair_impl( Tuple1 tuple1, Tuple2 tuple2, std::index_sequence<Idxs1...>, std::index_sequence<Idxs2...> )
          : m_first( std::get<Idxs1>(tuple1)... ),
            m_second( std::get<Idxs2>(tuple2)... )
        {

        }

        constexpr T1& first(){ return m_first; }
        constexpr const T1& first() const{ return m_first; }

        constexpr T2& second(){ return m_second; }
        constexpr const T2& second() const{ return m_second; }

        //---------------------------------------------------------------------
        // Private Members
        //---------------------------------------------------------------------
      private:

        T1 m_first;
        T2 m_second;
      };

      template<typename T1, typename T2, typename U1, typename U2>
      struct is_constructible : conjunction<
        std::is_constructible<T1,U1>,
        std::is_constructible<T1,U1>
      >{};

      template<typename T1, typename T2, typename U1, typename U2>
      struct is_explicit_constructible : conjunction<
        std::is_constructible<T1,U1>,
        std::is_constructible<T1,U1>,
        disjunction<
          negation<std::is_convertible<U1,T1>>,
          negation<std::is_convertible<U2,T2>>
        >
      >{};
    } // namespace detail

    template<typename T1, typename T2>
    class compressed_pair;

    template<typename T, typename U>
    struct tuple_element<0,compressed_pair<T,U>> : identity<T>{};

    template<typename T, typename U>
    struct tuple_element<1,compressed_pair<T,U>> : identity<U>{};

    template<typename T, typename U>
    struct tuple_size<compressed_pair<T,U>> : public size_constant<2>{};

    ///////////////////////////////////////////////////////////////////////////
    /// \brief \c compressed_pair is a \c struct template that provides a way
    ///        to store two heterogeneous objects as a single unit that
    ///        leverages empty-base-optimization
    ///
    /// A compressed pair is a special case of a compressed_tuple with only two
    /// elements.
    ///
    /// \tparam T1 the first type
    /// \tparam T2 the second type
    ///////////////////////////////////////////////////////////////////////////
    template<typename T1, typename T2>
    class compressed_pair
      : public detail::compressed_pair_impl<T1,T2>
    {
      using base_type = detail::compressed_pair_impl<T1,T2>;

      //-----------------------------------------------------------------------
      // Public Member Types
      //-----------------------------------------------------------------------
    public:

      using first_type  = T1;
      using second_type = T2;

      //-----------------------------------------------------------------------
      // Constructors / Assignment
      //-----------------------------------------------------------------------
    public:

      // (1)

      /// \brief Default constructor. Value-initializes both elements of the
      ///        pair, first and second
      constexpr compressed_pair() = default;

      // (2)

      /// \{
      /// \brief Initializes first with \p x and second with \p y
      ///
      /// \param x the value to assign to first
      /// \param y the value to assign to second
      template<typename U1=T1, typename U2=T2, std::enable_if_t<detail::is_constructible<U1,U2,const U1&,const U2&>::value>* = nullptr>
      constexpr compressed_pair( const T1& x, const T2& y );

      template<typename U1=T1, typename U2=T2, std::enable_if_t<detail::is_explicit_constructible<U1,U2,const U1&,const U2&>::value>* = nullptr>
      explicit constexpr compressed_pair( const T1& x, const T2& y );
      /// \}

      // (3)

      /// \{
      /// \brief Initializes first with \c std::forward<U1>(x) and second
      ///        with \c std::forward<U2>(y)
      ///
      /// \param x the value to assign to first
      /// \param y the value to assign to second
      template<typename U1, typename U2, std::enable_if_t<detail::is_constructible<T1,T2,U1&&,U2&&>::value>* = nullptr>
      constexpr compressed_pair( U1&& x, U2&& y );

      template<typename U1, typename U2, std::enable_if_t<detail::is_explicit_constructible<T1,T2,U1&&,U2&&>::value>* = nullptr>
      constexpr explicit compressed_pair( U1&& x, U2&& y );
      /// \}

      // (4)

      /// \{
      /// \brief Initializes \c first with \c other.first and \c second
      ///        with \c p.second
      ///
      /// \param other the pair to copy
      template<typename U1, typename U2, std::enable_if_t<detail::is_constructible<T1,T2,const U1&,const U2&>::value>* = nullptr>
      constexpr compressed_pair( const compressed_pair<U1,U2>& other );

      template<typename U1, typename U2, std::enable_if_t<detail::is_explicit_constructible<T1,T2,const U1&,const U2&>::value>* = nullptr>
      constexpr explicit compressed_pair( const compressed_pair<U1,U2>& other );
      /// \}

      // (5)

      /// \{
      /// \brief Initializes \c first with \c std::forward<U1>(other.first)
      ///        and \c second with \c std::forward<U2>(other.second)
      ///
      /// \param other the pair to move
      template<typename U1, typename U2, std::enable_if_t<detail::is_constructible<T1,T2,U1&&,U2&&>::value>* = nullptr>
      constexpr compressed_pair( compressed_pair<U1,U2>&& other );

      template<typename U1, typename U2, std::enable_if_t<detail::is_explicit_constructible<T1,T2,U1&&,U2&&>::value>* = nullptr>
      constexpr explicit compressed_pair( compressed_pair<U1,U2>&& other );
      /// \}

      // (6)

      /// \brief Forwards the elements of first_args to the constructor of
      ///         first and forwards the elements of second_args to the
      ///         constructor of second.
      ///
      /// This is the only non-default constructor that can be used to create
      /// a pair of non-copyable non-movable types.
      ///
      /// \param first_args a tuple containing args to forward to \c first
      /// \param second_args a tuple containing args to forward to \c second
      template<typename Tuple1, typename Tuple2>
      constexpr compressed_pair( std::piecewise_construct_t,
                                 Tuple1&& first_args,
                                 Tuple2&& second_args );

      // (7)

      /// \brief Copy constructor is defaulted, and is constexpr if copying
      ///        of both elements satisfies the requirements on constexpr
      ///        functions
      ///
      /// \param other the other pair to copy
      constexpr compressed_pair( const compressed_pair& other ) = default;

      // (8)

      /// \brief Move constructor is defaulted, and is constexpr if moving
      ///        of both elements satisfies the requirements on constexpr
      ///        functions
      ///
      /// \param other the other pair to move
      constexpr compressed_pair( compressed_pair&& other ) = default;

      //-----------------------------------------------------------------------

      compressed_pair& operator=( const compressed_pair& other );

      template<typename U1, typename U2>
      compressed_pair& operator=( const compressed_pair<U1,U2>& other );

      compressed_pair& operator=( compressed_pair&& other );

      template<typename U1, typename U2>
      compressed_pair& operator=( compressed_pair<U1,U2>&& other );

      //-----------------------------------------------------------------------
      // Member Access
      //-----------------------------------------------------------------------
    public:

      /// \{
      /// \brief Accesses the first element of this compressed pair
      ///
      /// \return a reference to the first element
      constexpr first_type& first() noexcept;
      constexpr const first_type& first() const noexcept;
      /// \}

      /// \{
      /// \brief Accesses the second element of this compressed pair
      ///
      /// \return a reference to the second element
      constexpr second_type& second() noexcept;
      constexpr const second_type& second() const noexcept;
      ///\}

      //-----------------------------------------------------------------------
      // Modifiers
      //-----------------------------------------------------------------------
    public:

      /// \brief Swaps \c first with \c other.first and \c second with
      ///        \c other.second.
      ///
      /// \param other pair of values to swap
      void swap( compressed_pair& other );

      //-----------------------------------------------------------------------
      // Private Members
      //-----------------------------------------------------------------------
    private:

      /// \{
      /// \brief Getter methods for accessing the first and second element
      ///        from get overloads
      ///
      /// \return the retrieved entry
      T1& get( size_constant<0> ) &;
      const T1& get( size_constant<0> ) const &;
      T1&& get( size_constant<0> ) &&;
      const T1&& get( size_constant<0> ) const &&;
      T1& get( size_constant<1> ) &;
      const T1& get( size_constant<1> ) const &;
      T1&& get( size_constant<1> ) &&;
      const T1&& get( size_constant<1> ) const &&;
      /// \}

      //-----------------------------------------------------------------------
      // Friends
      //-----------------------------------------------------------------------
    private:

      template<std::size_t Idx, typename U1, typename U2>
      friend constexpr tuple_element_t<Idx,compressed_pair<U1,U2>>&
        get( compressed_pair<U1,U2>& p ) noexcept;

      template<std::size_t Idx, typename U1, typename U2>
      friend constexpr const tuple_element_t<Idx,compressed_pair<U1,U2>>&
        get( const compressed_pair<U1,U2>& p ) noexcept;

      template<std::size_t Idx, typename U1, typename U2>
      friend constexpr tuple_element_t<Idx,compressed_pair<U1,U2>>&&
        get( compressed_pair<U1,U2>&& p ) noexcept;

      template<std::size_t Idx, typename U1, typename U2>
      friend constexpr const tuple_element_t<Idx,compressed_pair<U1,U2>>&&
        get( const compressed_pair<U1,U2>&& p ) noexcept;
    };

    //-------------------------------------------------------------------------
    // Utilities
    //-------------------------------------------------------------------------

    /// \brief Hashes a std::pair
    ///
    /// \param pair the pair to hash
    template<typename T, typename U>
    constexpr std::size_t hash_value( const compressed_pair<T,U>& pair );

    //-------------------------------------------------------------------------

    /// \brief Swaps the contents of two compressed_pairs
    ///
    /// \param lhs the left compressed_pair to swap
    /// \param rhs the right compressed pair to swap
    template<typename T1, typename T2>
    void swap( compressed_pair<T1,T2>& lhs, compressed_pair<T1,T2>& rhs );

    //-------------------------------------------------------------------------

    /// \brief Make utility to create a type-deduced compressed pair
    ///
    /// \param x the value to assign to \c first
    /// \param y the value to assign to \c second
    template<typename T1, typename T2>
    constexpr compressed_pair<std::decay_t<T1>,std::decay_t<T2>>
      make_compressed_pair( T1&& x, T2&& y );

    //-------------------------------------------------------------------------

    template<std::size_t Idx, typename U1, typename U2>
    constexpr tuple_element_t<Idx,compressed_pair<U1,U2>>&
      get( compressed_pair<U1,U2>& p ) noexcept;

    template<std::size_t Idx, typename U1, typename U2>
    constexpr const tuple_element_t<Idx,compressed_pair<U1,U2>>&
      get( const compressed_pair<U1,U2>& p ) noexcept;

    template<std::size_t Idx, typename U1, typename U2>
    constexpr tuple_element_t<Idx,compressed_pair<U1,U2>>&&
      get( compressed_pair<U1,U2>&& p ) noexcept;

    template<std::size_t Idx, typename U1, typename U2>
    constexpr const tuple_element_t<Idx,compressed_pair<U1,U2>>&&
      get( const compressed_pair<U1,U2>&& p ) noexcept;

    //-------------------------------------------------------------------------
    // Comparisons
    //-------------------------------------------------------------------------

    template<typename T1, typename T2>
    constexpr bool operator==( const compressed_pair<T1,T2>& lhs,
                               const compressed_pair<T1,T2>& rhs );

    template<typename T1, typename T2>
    constexpr bool operator!=( const compressed_pair<T1,T2>& lhs,
                               const compressed_pair<T1,T2>& rhs );

    template<typename T1, typename T2>
    constexpr bool operator<( const compressed_pair<T1,T2>& lhs,
                              const compressed_pair<T1,T2>& rhs );

    template<typename T1, typename T2>
    constexpr bool operator<=( const compressed_pair<T1,T2>& lhs,
                               const compressed_pair<T1,T2>& rhs );

    template<typename T1, typename T2>
    constexpr bool operator>( const compressed_pair<T1,T2>& lhs,
                              const compressed_pair<T1,T2>& rhs );

    template<typename T1, typename T2>
    constexpr bool operator>=( const compressed_pair<T1,T2>& lhs,
                               const compressed_pair<T1,T2>& rhs );

  } // namespace stl
} // namespace bit

#include "detail/compressed_pair.inl"

#endif /* BIT_STL_UTILITIES_COMPRESSED_PAIR_HPP */
