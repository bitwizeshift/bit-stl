/**
 * \file Destructible.hpp
 *
 * \brief This header defines the concept for Desructible
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_CONCEPTS_DESTRUCTIBLE_HPP
#define BIT_STL_CONCEPTS_DESTRUCTIBLE_HPP

#include "../traits/void_t.hpp"
#include "../traits/bool_constant.hpp"
#include "../traits/conjunction.hpp"

#include <type_traits> // std::declval

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T, typename = void>
      struct is_destructible_impl : false_type{};

      template<typename T>
      struct is_destructible_impl<T,
        void_t<
          decltype( std::declval<T&>().~T() )
        >
      > : true_type{};

    } // namespace detail

    /// \brief Type trait to determine if a given type is Destructible
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_destructible : detail::is_destructible_impl<std::decay_t<T>>{};

    /// \brief Type trait to determine if a series of \c Types are all
    ///        Destructibles
    ///
    /// \The result is stored in \c ::value
    template<typename...Types>
    struct are_destructible : conjunction<is_destructible<Types>...>{};

  } // namespace stl
} // namespace bit

///////////////////////////////////////////////////////////////////////////////
/// \concept{Destructible}
///
/// \brief Specifies that an instance of the type can be destructed.
///
/// ## Requirements
///
/// The type \c T satisfies \ref Destructible if
///
/// Given
///
/// - \c u, a expression of type \c T
///
/// The following expressions must be valid and have their specified effects
///
/// \code
/// u.~T()
/// \endcode
///
/// All resources owned by u are reclaimed, no exceptions are thrown
///////////////////////////////////////////////////////////////////////////////

#endif /* BIT_STL_CONCEPTS_DESTRUCTIBLE_HPP */
