/**
 * \file type_list.hpp
 *
 * \brief This header contains a generic metaprogramming utility for storing a
 *        sequence of types in a single type.
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_COMPOSITION_TYPE_LIST_HPP
#define BIT_STL_TRAITS_COMPOSITION_TYPE_LIST_HPP

namespace bit {
  namespace stl {

    /// \brief A utility metafunction for encoding a sequence of types into a
    ///        single unique type.
    ///
    /// This is used for packing multiple types into one as a template argument,
    /// for expansion later. This can be used to support multiple variadic sets
    /// in a single template.
    template<typename...Types>
    struct type_list{};

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_COMPOSITION_TYPE_LIST_HPP */
