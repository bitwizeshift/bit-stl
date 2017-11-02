/**
 * \file allocator_destructor.hpp
 *
 * \brief This header contains the definition of a deleter for allocators
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_MEMORY_ALLOCATOR_DESTRUCTOR_HPP
#define BIT_STL_MEMORY_ALLOCATOR_DESTRUCTOR_HPP

#include <memory> // std::allocator_traits

namespace bit {
  namespace stl {

    ///////////////////////////////////////////////////////////////////////////
    /// \brief A deleter for use with standard allocators
    ///
    /// This holds onto the allocator by reference
    ///
    /// \tparam Allocator the allocator to delete
    ///////////////////////////////////////////////////////////////////////////
    template<typename Allocator>
    class allocator_deleter
    {
      //-----------------------------------------------------------------------
      // Public Member Types
      //-----------------------------------------------------------------------
    public:

      using alloc_traits = std::allocator_traits<Allocator>;
      using pointer   = typename alloc_traits::pointer;
      using size_type = typename alloc_traits::size_type;

      //-----------------------------------------------------------------------
      // Constructor
      //-----------------------------------------------------------------------
    public:

      allocator_deleter( Allocator& alloc, size_type size ) noexcept;

      //-----------------------------------------------------------------------
      // Modifiers
      //-----------------------------------------------------------------------
    public:

      void operator()( pointer p ) noexcept;

      //-----------------------------------------------------------------------
      // Private Members
      //-----------------------------------------------------------------------
    private:

      Allocator& m_allocator;
      size_type  m_size;
    };

  } // namespace stl
} // namespace bit

#include "detail/allocator_deleter.inl"

#endif /* BIT_STL_MEMORY_ALLOCATOR_DESTRUCTOR_HPP */
