/**
 * \file normalize_char.hpp
 *
 * \brief This header contains utility metafunctions for normalizing characters
 *        to just the 'char' type
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_TRANSFORMATIONS_NORMALIZE_CHAR_HPP
#define BIT_STL_TRAITS_TRANSFORMATIONS_NORMALIZE_CHAR_HPP

#include "../composition/identity.hpp"

namespace bit {
  namespace stl {

    /// \brief Normalizes character types T to non-signed/unsigned character
    ///        types
    ///
    /// The result is aliased as \t ::type
    ///
    /// \note The result is undefined for anything that is not a char-type
    template<typename T>
    struct normalize_char;

    template<>
    struct normalize_char<char> : identity<char>{};

    template<>
    struct normalize_char<signed char> : identity<char>{};

    template<>
    struct normalize_char<unsigned char> : identity<char>{};

    /// \brief Convenience alias for retrieving the \c ::type field of
    ///        normalize_char
    template<typename T>
    using normalize_char_t = typename normalize_char<T>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_TRANSFORMATIONS_NORMALIZE_CHAR_HPP */
