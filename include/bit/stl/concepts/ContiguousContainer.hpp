/**
 * \file ContiguousContainer.hpp
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
#ifndef BIT_STL_CONCEPTS_CONTIGUOUS_CONTAINER_HPP
#define BIT_STL_CONCEPTS_CONTIGUOUS_CONTAINER_HPP

#include "Container.hpp"
#include "RandomAccessIterator.hpp"

#include "../traits/composition/conjunction.hpp"
#include "../traits/composition/bool_constant.hpp"

#include <type_traits>

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T, typename = void>
      struct is_contiguous_container_impl : false_type{};

      template<typename T>
      struct is_contiguous_container_impl<T,
        void_t<
          decltype(std::declval<const typename T::value_type*&>() = std::declval<const T&>().data())
        >
      > : conjunction<
        is_container<T>,
        is_random_access_iterator<typename T::iterator>,
        is_random_access_iterator<typename T::const_iterator>
      >{};
    } // namespace detail

    /// \brief Type trait to determine if a given type is a ContiguousContainer
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_contiguous_container : detail::is_contiguous_container_impl<std::decay_t<T>>{};

    /// \brief Type trait to determine if a series of \c Types are all
    ///        ContiguousContainers
    ///
    /// \The result is stored in \c ::value
    template<typename...Types>
    struct are_contiguous_containers : conjunction<is_contiguous_container<Types>...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONCEPTS_CONTIGUOUS_CONTAINER_HPP */
