/**
 * \file ForwardIterator.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_CONCEPTS_FORWARDITERATOR_HPP
#define BIT_STL_CONCEPTS_FORWARDITERATOR_HPP

#include "InputIterator.hpp"

#include "../traits/composition/conjunction.hpp"

namespace bit {
  namespace stl {

    template<typename T>
    struct is_forward_iterator : is_input_iterator<T>{};

    /// \brief Type trait to determine if a series of \c Types are all ForwardIterators
    ///
    /// \The result is stored in \c ::value
    template<typename...Types>
    struct are_forward_iterators : conjunction<is_forward_iterator<Types>...>{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONCEPTS_FORWARDITERATOR_HPP */
