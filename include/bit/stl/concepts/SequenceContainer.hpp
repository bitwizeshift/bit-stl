/*****************************************************************************
 * \file
 * \brief TODO: Add description
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
#ifndef BIT_STL_CONCEPTS_SEQUENCECONTAINER_HPP
#define BIT_STL_CONCEPTS_SEQUENCECONTAINER_HPP

#include "Container.hpp"
#include "BidirectionalIterator.hpp"

#include "../traits/composition/conjunction.hpp"

#include <type_traits>

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T, typename = void>
      struct is_sequence_container_impl : false_type{};

      template<typename T>
      struct is_sequence_container_impl<T,
        void_t<
          // emplacing (iterator)
          // ...
          // insertions (iterator)
          decltype(std::declval<T&>().insert( std::declval<typename T::const_iterator>(), std::declval<const typename T::value_type&>() )),
          decltype(std::declval<T&>().insert( std::declval<typename T::const_iterator>(), std::declval<typename T::value_type&&>() )),
          decltype(std::declval<T&>().insert( std::declval<typename T::const_iterator>(), std::declval<typename T::size_type>(), std::declval<const typename T::value_type&>() )),
          decltype(std::declval<T&>().insert( std::declval<typename T::const_iterator>(), std::declval<const T*>(), std::declval<const T*>() )),
          decltype(std::declval<T&>().insert( std::declval<typename T::const_iterator>(), std::declval<std::initializer_list<typename T::value_type>>() )),
          // erasing
          decltype(std::declval<T&>().erase( std::declval<typename T::const_iterator>() )),
          decltype(std::declval<T&>().erase( std::declval<typename T::const_iterator>(), std::declval<typename T::const_iterator>() )),
          decltype(std::declval<T&>().clear()),
          // assigning
          decltype(std::declval<T&>().assign( std::declval<typename T::iterator>(), std::declval<typename T::iterator>() )),
          decltype(std::declval<T&>().assign( std::declval<std::initializer_list<typename T::value_type>>() )),
          decltype(std::declval<T&>().assign( std::declval<typename T::size_type>(), std::declval<typename T::value_type>() )),
          // observers
          decltype(typename T::reference( std::declval<T&>().front() )),
          decltype(typename T::const_reference( std::declval<const T&>().front() )),
          decltype(typename T::reference( std::declval<T&>().back() )),
          decltype(typename T::const_reference( std::declval<const T&>().back() )),
          // emplacing
          // ...
          // insertions
          decltype(std::declval<T&>().push_front( std::declval<const typename T::value_type&>() )),
          decltype(std::declval<T&>().push_front( std::declval<typename T::value_type&&>() )),
          decltype(std::declval<T&>().push_back( std::declval<const typename T::value_type&>() )),
          decltype(std::declval<T&>().push_back( std::declval<typename T::value_type&&>() )),
          // removals
          decltype(std::declval<T&>().pop_front()),
          decltype(std::declval<T&>().pop_back()),
          // member access
          decltype(typename T::reference(std::declval<T&>()[std::declval<typename T::size_type>()])),
          decltype(typename T::const_reference(std::declval<const T&>()[std::declval<typename T::size_type>()])),
          decltype(typename T::reference(std::declval<T&>().at(std::declval<typename T::size_type>()))),
          decltype(typename T::const_reference(std::declval<const T&>().at(std::declval<typename T::size_type>())))
        >
      > : conjunction<
            is_container<T>,
            std::is_constructible<T,typename T::size_type,typename T::value_type>,
            std::is_constructible<T,typename T::iterator,typename T::iterator>,
            std::is_constructible<T,const T*,const T*>,
            std::is_constructible<T,std::initializer_list<typename T::value_type>>
            // braced-init support
          >{};
    } // namespace detail

  /// \brief Type trait to determine if a given type is a SequenceContainer
  ///
  /// The result is aliased as \c ::value
  template<typename T>
  struct is_sequence_container : detail::is_sequence_container_impl<std::decay_t<T>>{};

  /// \brief Type trait to determine if a series of \c Types are all
  ///        SequenceContainers
  ///
  /// \The result is stored in \c ::value
  template<typename...Types>
  struct are_sequence_containers : conjunction<is_sequence_container<Types>...>{};


  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONCEPTS_SEQUENCECONTAINER_HPP */
