/**
 * \file in_place.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_UTILITIES_IN_PLACE_HPP
#define BIT_STL_UTILITIES_IN_PLACE_HPP

#include <type_traits> // std::true_type, std::false_type

namespace bit {
  namespace stl {

    /// \brief This function is a special disambiguation tag for variadic
    ///        functions, used in any and optional
    ///
    /// \note Calling this function results in undefined behaviour.
    struct in_place_t
    {
      explicit in_place_t() = default;
    };
    constexpr in_place_t in_place{};

    /// \brief This function is a special disambiguation tag for variadic
    ///        functions, used in any and optional
    ///
    /// \note Calling this function results in undefined behaviour.
    template<typename T>
    struct in_place_type_t
    {
        explicit in_place_type_t() = default;
    };
    template<typename T>
    constexpr in_place_type_t<T> in_place_type{};


    /// \brief This function is a special disambiguation tag for variadic
    ///        functions, used in any and optional
    ///
    /// \note Calling this function results in undefined behaviour.
    template<std::size_t I> struct in_place_index_t
    {
      explicit in_place_index_t() = default;
    };

    template<std::size_t I>
    constexpr in_place_index_t<I> in_place_index{};

    //-------------------------------------------------------------------------

    /// \brief Type-trait to determine if the type is an in_place type
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_in_place : std::false_type{};

    template<>
    struct is_in_place<in_place_t> : std::true_type{};

    template<typename T>
    struct is_in_place<in_place_type_t<T>> : std::true_type{};

    template<std::size_t I>
    struct is_in_place<in_place_index_t<I>> : std::true_type{};

    template<typename T>
    constexpr bool is_in_place_v = is_in_place<T>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_UTILITIES_IN_PLACE_HPP */
