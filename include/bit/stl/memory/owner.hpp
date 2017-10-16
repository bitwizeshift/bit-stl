/**
 * \file owner.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_MEMORY_OWNER_HPP
#define BIT_STL_MEMORY_OWNER_HPP

namespace bit {
  namespace stl {

    /// \brief A pointer that represents ownership
    template<typename T>
    using owner = T;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_MEMORY_OWNER_HPP */
