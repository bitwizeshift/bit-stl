/**
 * \file nonesuch.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_NONESUCH_HPP
#define BIT_STL_TRAITS_NONESUCH_HPP

namespace bit {
  namespace stl {

    struct nonesuch {
        nonesuch() = delete;
        ~nonesuch() = delete;
        nonesuch(nonesuch const&) = delete;
        void operator=(nonesuch const&) = delete;
    };

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_NONESUCH_HPP */
