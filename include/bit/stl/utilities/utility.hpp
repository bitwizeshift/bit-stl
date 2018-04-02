/*****************************************************************************
 * \file
 * \brief This header contains extensions to the standard 'utility' header
 *****************************************************************************/

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
#ifndef BIT_STL_UTILITIES_UTILITY_HPP
#define BIT_STL_UTILITIES_UTILITY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../traits/composition/identity.hpp"
#include "../traits/composition/void_t.hpp"

#include <type_traits> // std::remove_reference
#include <utility>     // std::forward
#include <stdexcept>   // std::out_of_range

namespace bit {
  namespace stl {

    //--------------------------------------------------------------------------
    // Indexing
    //--------------------------------------------------------------------------

    namespace detail {

      template<typename T, typename Key, typename = void>
      struct has_at : std::false_type{};

      template<typename T, typename Key>
      struct has_at<
        T,
        Key,
        void_t<decltype(std::declval<T>().at( std::declval<Key>() ))>
      > : std::true_type{};

    } // namespace detail

    /// \brief Safely retrieves the value at the given index, otherwise asserts
    ///
    /// \param array reference to the array to index into
    /// \param n     the index to retrieve
    /// \return reference to instance
    template<typename T, std::size_t N>
    constexpr T& at( T (&array)[N], std::size_t n );

    /// \brief Safely retrieves the value at the given index, otherwise asserts
    ///
    /// \param array reference to the array to index into
    /// \param n     the index to retrieve
    /// \return reference to instance
#ifndef BIT_DOXYGEN_BUILD
    template<typename Container, typename Key, typename = std::enable_if_t<detail::has_at<Container,Key>::value>>
#else
    template<typename Container, typename Key>
#endif
    constexpr decltype(auto) at( Container& container, Key&& key );

    //------------------------------------------------------------------------
    //
    //------------------------------------------------------------------------

    namespace detail {

      template<typename Ptr>
      struct type_of_member_ptr;

      template<typename T, typename U>
      struct type_of_member_ptr<U T::*> : identity<U>{};

      template<typename Ptr>
      using type_of_member_t = typename type_of_member_ptr<Ptr>::type;

    } // namespace detail

    template<typename T>
    class underlying_container_type
    {
    private:
      struct I : private T{
        using type = typename detail::type_of_member_ptr<decltype(&I::c)>::type;
      };
    public:
      using type = typename I::type;
    };

    template<typename T>
    using underlying_container_type_t = typename underlying_container_type<T>::type;

    /// \brief Gets the underlying container of a given container adapter
    ///
    /// \param container reference to the container adapter
    /// \return reference to the underlying container
    template<typename Container, underlying_container_type_t<Container>* = nullptr>
    underlying_container_type_t<Container>&
      get_underlying_container( Container& container );

  } // namespace stl
} // namespace bit

#include "detail/utility.inl"

#endif /* BIT_STL_UTILITIES_UTILITY_HPP */
