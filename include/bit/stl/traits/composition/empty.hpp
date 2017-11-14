/**
 * \file empty.hpp
 *
 * \brief This header defines an alias for an always empty type
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_COMPOSITION_EMPTY_HPP
#define BIT_STL_TRAITS_COMPOSITION_EMPTY_HPP

namespace bit {
  namespace stl {

    /// \brief Utility metafunction that always expands into an empty struct
    ///        with no members or type members
    template<typename T = void>
    struct empty{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_COMPOSITION_EMPTY_HPP */
