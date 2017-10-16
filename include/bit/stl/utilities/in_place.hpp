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

    namespace detail {

      /// \brief Used to disambiguate unspecialized in_place
      struct in_place_ctor_tag{};

      /// \brief Used to disambiguate typed in-place
      template<typename T>
      struct in_place_ctor_type_tag{};

      /// \brief Used to disambiguate indexed in-place
      template<std::size_t I>
      struct in_place_ctor_index_tag{};

    } // namespace detail

    //-------------------------------------------------------------------------
    // In Place Tags / Types
    //-------------------------------------------------------------------------

    /// \brief in_place_tag is an empty struct type used as the return types
    ///        of the in_place functions for disambiguation.
    struct in_place_tag
    {
      in_place_tag() = delete;
      in_place_tag(int){}
    };

    /// \brief This function is a special disambiguation tag for variadic
    ///        functions, used in any and optional
    ///
    /// \note Calling this function results in undefined behaviour.
#ifndef BIT_DOXYGEN_BUILD
    inline in_place_tag in_place( detail::in_place_ctor_tag = detail::in_place_ctor_tag() ){ return {0}; }
#else
    in_place_tag in_place();
#endif

    /// \brief This function is a special disambiguation tag for variadic
    ///        functions, used in any and optional
    ///
    /// \note Calling this function results in undefined behaviour.
    template<typename T>
#ifndef BIT_DOXYGEN_BUILD
    inline in_place_tag in_place( detail::in_place_ctor_type_tag<T> = detail::in_place_ctor_type_tag<T>() ){ return {0}; }
#else
    in_place_tag in_place();
#endif

    /// \brief This function is a special disambiguation tag for variadic
    ///        functions, used in any and optional
    ///
    /// \note Calling this function results in undefined behaviour.
    template<std::size_t I>
#ifndef BIT_DOXYGEN_BUILD
    inline in_place_tag in_place( detail::in_place_ctor_index_tag<I> = detail::in_place_ctor_index_tag<I>() ){ return {0}; }
#else
    in_place_tag in_place();
#endif

    /// \brief A tag type used for dispatching in_place calls
#ifndef BIT_DOXYGEN_BUILD
    using in_place_t = in_place_tag(&)( detail::in_place_ctor_tag );
#else
    using in_place_t = in_place_tag(&)( /* implementation defined */ );
#endif

    /// \brief A tag type used for type-based dispatching in_place calls
#ifndef BIT_DOXYGEN_BUILD
    template<typename T>
    using in_place_type_t = in_place_tag(&)( detail::in_place_ctor_type_tag<T> );
#else
    template<typename T>
    using in_place_type_t = in_place_tag(&)( /* implementation defined */ );
#endif

    /// \brief A tag type used for type-based dispatching in_place calls
#ifndef BIT_DOXYGEN_BUILD
    template <std::size_t I>
    using in_place_index_t = in_place_tag(&)( detail::in_place_ctor_index_tag<I> );
#else
    template <std::size_t I>
    using in_place_index_t = in_place_tag(&)( /* implementation defined */ );
#endif

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
