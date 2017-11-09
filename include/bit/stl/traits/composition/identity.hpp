/**
 * \file identity.hpp
 *
 * \brief This header contains the trait helper for identity types
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_COMPOSITION_IDENTITY_HPP
#define BIT_STL_TRAITS_COMPOSITION_IDENTITY_HPP

namespace bit {
  namespace stl {

    /// \brief This simple type is used to add '::type' to any transformation
    ///        type-traits
    ///
    /// The result is aliased as \c ::type
    template<typename T>
    struct identity{ using type = T; };

    /// \brief Namespace alias used to extract identity<T>::type
    ///
    /// \note This alias is mostly useful for preventing template deduction
    template<typename T>
    using identity_t = typename identity<T>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_COMPOSITION_IDENTITY_HPP */
