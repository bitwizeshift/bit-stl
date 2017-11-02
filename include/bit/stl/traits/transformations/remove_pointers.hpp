/**
 * \file remove_pointers.hpp
 *
 * \brief This header defines a utility metafunction for removing all pointers
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_TRANSFORMATIONS_REMOVE_POINTERS_HPP
#define BIT_STL_TRAITS_TRANSFORMATIONS_REMOVE_POINTERS_HPP

#include "../identity.hpp"

namespace bit {
  namespace stl {

    /// \brief Removes all pointers from a given type
    ///
    /// The result is aliased as \c ::type
    template<typename T>
    struct remove_pointers : identity<T>{};

    template<typename T>
    struct remove_pointers<T*> : remove_pointers<T>{};

    template<typename T>
    struct remove_pointers<T* const> : remove_pointers<T>{};

    template<typename T>
    struct remove_pointers<T* volatile> : remove_pointers<T>{};

    template<typename T>
    struct remove_pointers<T* const volatile> : remove_pointers<T>{};

    /// \brief Convenience template to retrieve the \c ::type of
    ///        remove_pointers
    template<typename T>
    using remove_pointers_t = typename remove_pointers<T>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_TRANSFORMATIONS_REMOVE_POINTERS_HPP */
