/**
 * \file base_type.hpp
 *
 * \brief This header contains the definition of a metafunction for extracting
 *        the base of a type without any qualifiers
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_TRANSFORMATIONS_BASE_TYPE_HPP
#define BIT_STL_TRAITS_TRANSFORMATIONS_BASE_TYPE_HPP

#include "../identity.hpp"

#include <type_traits> // std::decay_t

namespace bit {
  namespace stl {

    /// \brief Obtains the base type of T without modifiers
    ///
    /// The result is aliased as \c ::type
    template<typename T>
    struct base_type : identity<std::decay_t<T>>{};

    template<typename T>
    struct base_type<T*> : base_type<std::decay_t<T>>{};

    template<typename T>
    struct base_type<T&> : base_type<std::decay_t<T>>{};

    template<typename T>
    struct base_type<T&&> : base_type<std::decay_t<T>>{};

    /// \brief Convenience alias for retrieving the \c ::type field of
    ///        base_type
    template<typename T>
    using base_type_t = typename base_type<T>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_TRANSFORMATIONS_BASE_TYPE_HPP */
