/**
 * \file is_implicitly_convertible.hpp
 *
 * \brief This header defines a type-trait for determining whether a type is
 *        implicitly convertible to another type
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_PROPERTIES_IS_IMPLICITLY_CONVERTIBLE_HPP
#define BIT_STL_TRAITS_PROPERTIES_IS_IMPLICITLY_CONVERTIBLE_HPP

#include "../composition/bool_constant.hpp"
#include "../composition/void_t.hpp"

#include <type_traits> // std::declval

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T>
      struct is_implicitly_convertible_dummy
      {
        static void test( T );
      };

      template<typename From, typename To, typename = void>
      struct is_implicitly_convertible_impl : false_type{};

      template<typename From, typename To>
      struct is_implicitly_convertible_impl<From,To,void_t<
        decltype( is_implicitly_convertible_dummy<To>::test( std::declval<From>() ) )
      >> : true_type{};
    } // namespace detail

    /// \brief Type trait to determine if From is implicitly convertible to
    ///        To
    ///
    /// A type is considered implicitly convertible if the following expression
    /// is well-formed:
    ///
    /// \code
    /// To test(){ return std::declval<From>(); }
    /// \endcode
    ///
    /// For the purpose of the above illustration, std::declval is not
    /// considered ODR-used.
    ///
    /// The result is aliased as \c ::value
    template<typename From, typename To>
    struct is_implicitly_convertible
      : detail::is_implicitly_convertible_impl<From,To>{};

    /// \brief Helper utility to extract is_implicitly_convertible::type
    template<typename From, typename To>
    constexpr bool is_implicitly_convertible_v = is_implicitly_convertible<From,To>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_PROPERTIES_IS_IMPLICITLY_CONVERTIBLE_HPP */
