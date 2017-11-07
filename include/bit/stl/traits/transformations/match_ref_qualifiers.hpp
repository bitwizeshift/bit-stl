/**
 * \file match_ref_qualifiers.hpp
 *
 * \brief This header contains a utility metafunction for matching
 *        ref-qualifiers of a given qualified type
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_TRANSFORMATIONS_MATCH_REF_QUALIFIERS_HPP
#define BIT_STL_TRAITS_TRANSFORMATIONS_MATCH_REF_QUALIFIERS_HPP

#include "../composition/identity.hpp"

#include <type_traits> // std::is_lvalue_reference, std::is_rvalue_reference, etc

namespace bit {
  namespace stl {
    namespace detail {

      template<typename Unqualified,
               bool IsLValue,
               bool IsRValue>
      struct ref_selector : identity<Unqualified>{};

      template<typename Unqualified>
      struct ref_selector<Unqualified, true, false>
        : std::add_lvalue_reference<Unqualified>{};

      template<typename Unqualified>
      struct ref_selector<Unqualified, false, true>
        : std::add_rvalue_reference<Unqualified>{};

    } // namespace detail

    /// \brief Type trait to match the ref qualifications of \p Qualified and apply
    ///        it to \p Unqualified
    ///
    /// The result is aliased as \c ::type
    template<typename Qualified, typename Unqualified>
    using match_ref_qualifiers = detail::ref_selector<
      Unqualified,
      std::is_lvalue_reference<Qualified>::value,
      std::is_rvalue_reference<Qualified>::value
    >;

    /// \brief Convenience alias for retrieving the \c ::type field of
    ///        match_ref_qualifiers
    template<typename Qualified, typename Unqualified>
    using match_ref_qualifiers_t =
      typename match_ref_qualifiers<Qualified, Unqualified>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_TRANSFORMATIONS_MATCH_REF_QUALIFIERS_HPP */
