/**
 * \file match_cv_qualifiers.hpp
 *
 * \brief This header contains a utility metafunction for matching CV-qualifiers
 *        of a given qualified type
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_TRANSFORMATIONS_MATCH_CV_QUALIFIERS_HPP
#define BIT_STL_TRAITS_TRANSFORMATIONS_MATCH_CV_QUALIFIERS_HPP

#include "../identity.hpp"

#include <type_traits> // std::add_const, std::add_volatile, std::is_const, etc

namespace bit {
  namespace stl {
    namespace detail{

      /// \brief Helper to select the proper cv-qualifiers
      template<
        typename Unqualified,
        bool is_const_type,
        bool is_volatile_type
      >
      struct cv_selector : identity<Unqualified>{};

      template<typename Unqualified>
      struct cv_selector<Unqualified, false, true>
        : std::add_volatile<Unqualified>{};

      template<typename Unqualified>
      struct cv_selector<Unqualified, true, false>
        : std::add_const<Unqualified>{};

      template<typename Unqualified>
      struct cv_selector<Unqualified, true, true>
        : std::add_cv<Unqualified>{};

    } // namespace detail

    /// \brief Type trait to match the cv qualifications of \p Qualified and apply
    ///        it to \p Unqualified
    ///
    /// The result is aliased as \c ::type
    template<typename Qualified,typename Unqualified>
    using match_cv_qualifiers = detail::cv_selector<
      Unqualified,
      std::is_const<Qualified>::value,
      std::is_volatile<Qualified>::value
    >;

    /// \brief Convenience alias for retrieving the \c ::type field of
    ///        match_cv_qualifiers
    template<typename Qualified, typename Unqualified>
    using match_cv_qualifiers_t =
      typename match_cv_qualifiers<Qualified, Unqualified>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_TRANSFORMATIONS_MATCH_CV_QUALIFIERS_HPP */
