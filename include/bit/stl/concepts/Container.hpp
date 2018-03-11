/**
 * \file Container.hpp
 *
 * \brief TODO: Add description
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
#ifndef BIT_STL_CONCEPTS_CONTAINER_HPP
#define BIT_STL_CONCEPTS_CONTAINER_HPP

#include "EqualityComparable.hpp"

#include "../traits/composition/void_t.hpp"
#include "../traits/composition/conjunction.hpp"
#include "../traits/composition/bool_constant.hpp"

#include <type_traits>

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T, typename = void>
      struct is_container_impl : false_type{};

      template<typename T>
      struct is_container_impl<T,
        void_t<
          typename T::value_type,
          typename T::reference,
          typename T::const_reference,
          typename T::iterator,
          typename T::const_iterator,
          typename T::difference_type,
          typename T::size_type,
          decltype(typename T::iterator(std::declval<T&>().begin())),
          decltype(typename T::iterator(std::declval<T&>().end())),
          decltype(typename T::const_iterator(std::declval<const T&>().cbegin())),
          decltype(typename T::const_iterator(std::declval<const T&>().cend())),
          decltype(bool(std::declval<const T&>() == std::declval<const T&>() )),
          decltype(bool(std::declval<const T&>() != std::declval<const T&>() )),
          decltype(std::declval<T&>().swap( std::declval<T&>() )),
          decltype(typename T::size_type( std::declval<const T&>().size() )),
          decltype(typename T::size_type( std::declval<const T&>().max_size() )),
          decltype(bool( std::declval<const T&>().empty() ))
        >
      > : conjunction<
        std::is_default_constructible<T>,
        std::is_copy_constructible<T>,
        is_equality_comparable<typename T::value_type>
      >{};

    } // namespace detail

    /// \brief Type trait to determine if a given type is a Container
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_container : detail::is_container_impl<std::decay_t<T>>{};

    /// \brief Type trait to determine if a series of \c Types are all Containers
    ///
    /// \The result is stored in \c ::value
    template<typename...Types>
    struct are_containers : conjunction<is_container<Types>...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONCEPTS_CONTAINER_HPP */
