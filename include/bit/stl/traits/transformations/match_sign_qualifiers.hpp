/**
 * \file match_sign_qualifiers.hpp
 *
 * \brief This header contains a utility metafunction for matching
 *        sign-qualifiers of a given qualified type
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_TRANSFORMATIONS_MATCH_SIGN_QUALIFIERS_HPP
#define BIT_STL_TRAITS_TRANSFORMATIONS_MATCH_SIGN_QUALIFIERS_HPP

#include "../identity.hpp"

#include <type_traits> // std::make_signed, std::make_unsigneds

namespace bit {
  namespace stl {
    namespace detail {

      template<typename Unqualified,
               bool IsSigned,
               bool IsUnsigned>
      struct sign_selector : identity<Unqualified>{};

      template<typename Unqualified>
      struct sign_selector<Unqualified, true, false>
        : std::make_signed<Unqualified>{};

      template<typename Unqualified>
      struct sign_selector<Unqualified, false, true>
        : std::make_unsigned<Unqualified>{};
    } // namespace detail

    /// \brief Type trait to match the sign qualifications of \p Qualified and apply
    ///        it to \p Unqualified
    ///
    /// The result is aliased as \c ::type
    template<typename Qualified, typename Unqualified>
    using match_sign_qualifiers = detail::sign_selector<
      Unqualified,
      std::is_signed<Qualified>::value,
      std::is_unsigned<Qualified>::value
    >;

    /// \brief Convenience alias for retrieving the \c ::type field of
    ///        match_sign_qualifiers
    template<typename Qualified, typename Unqualified>
    using match_sign_qualifiers_t =
      typename match_sign_qualifiers<Qualified, Unqualified>::type;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_TRANSFORMATIONS_MATCH_SIGN_QUALIFIERS_HPP */
