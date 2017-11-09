/**
 * \file sfinae.hpp
 *
 * \brief This header contains useful SFINAE utilities for selectively enabling
 *        or disabling functionality
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_COMPOSITION_SFINAE_HPP
#define BIT_STL_TRAITS_COMPOSITION_SFINAE_HPP

#include "identity.hpp"

namespace bit {
  namespace stl {

    /// \brief Base class for sfinae types
    struct sfinae_base
    {
      /// \brief Type corresponding to yes (is) instances using SFINAE.
      /// \note bit::yes_type is guaranteed to be a different size than bit::no_type
      using yes_type = char(&)[1];

      /// \brief Type corresponding to no (is not) instances using SFINAE.
      /// \note bit::no_type is guaranteed to be a different size than bit::yes_type
      using no_type = char(&)[4];
    };

    //-------------------------------------------------------------------------

    template<bool B, typename T = void>
    struct enable_if : identity<T>{};

    template<typename T>
    struct enable_if<false,T>{};

    template<bool B, typename T>
    using enable_if_t = typename enable_if<B,T>::type;

    //-------------------------------------------------------------------------

    template<bool B, typename T = void>
    struct disable_if : identity<T>{};

    template<typename T>
    struct disable_if<true,T>{};

    /// \brief Convenience alias to retrieve the \c ::type member of
    ///        \c block_if
    template<bool B, typename T>
    using disable_if_t = typename enable_if<B,T>::type;

    //---------------------------------------------------------------------------

    /// \brief Similar to enable_if, but doesn't sfinae-away a type; instead
    ///        produces an uninstantiable unique type when true
    ///
    /// This is used to selectively disable constructors, since sfinae doesn't
    /// work for copy/move constructors
    template<bool b, typename T>
    struct enable_overload_if : identity<T>{};

    template<typename T>
    struct enable_overload_if<false,T>
    {
      class type{ type() = delete; ~type() = delete; };
    };

    /// \brief Convenience alias to retrieve the \c ::type member of
    ///        \c block_if
    template<bool B, typename T>
    using enable_overload_if_t = typename enable_overload_if<B,T>::type;

    //---------------------------------------------------------------------------

    /// \brief Inverse of \c block_if
    template<bool B, typename T>
    using disable_overload_if = enable_overload_if<!B,T>;

    /// \brief Convenience alias to retrieve the \c ::type member of
    ///        \c block_unless
    template<bool B, typename T>
    using disable_overload_if_t = typename disable_overload_if<B,T>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_COMPOSITION_SFINAE_HPP */
