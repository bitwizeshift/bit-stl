/**
 * \file nonesuch.hpp
 *
 * \brief This header contains the utility type nonesuch
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_NONESUCH_HPP
#define BIT_STL_TRAITS_NONESUCH_HPP

namespace bit {
  namespace stl {

    /// \brief A utility type for the detected_t idiom
    struct nonesuch {
        nonesuch() = delete;
        ~nonesuch() = delete;
        nonesuch(nonesuch const&) = delete;
        void operator=(nonesuch const&) = delete;
    };

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_NONESUCH_HPP */
