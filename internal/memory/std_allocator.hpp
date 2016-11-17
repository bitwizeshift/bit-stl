/**
 * \file std_allocator.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_INTERNAL_MEMORY_STD_ALLOCATOR_HPP
#define BIT_INTERNAL_MEMORY_STD_ALLOCATOR_HPP

namespace bit {
  inline namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief This class serves as a wrapper around the base Allocator
    ///        object, so that the STL library will be able to use all the
    ///        abilities.
    ///
    /// Using this wrapper requires a slightly different way to allocate STL
    /// objects. Below is the basic way of constructing some std class of
    /// type T
    ///
    /// \code
    ///
    /// using Allocator_t    = Allocator< ... >;
    /// using STDAllocator_t = bit::std_allocator<T,Allocator_t>;
    ///
    /// Allocator_t    alloc(memory, memsize);
    /// STLAllocator_t std_alloc(alloc)
    ///
    /// std::some_class<T,STLAllocator_t> instance{stl_alloc}
    ///
    /// // continue normally
    ///
    /// \endcode
    ///
    /// \tparam T         the type of this allocator
    /// \tparam Allocator the bit::Allocator this STLAllocator wraps around
    //////////////////////////////////////////////////////////////////////////
    template<typename T, typename Allocator>
    class std_allocator final
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      // ISO C++ Required and Optional Types

      using value_type     = typename std::remove_cv<T>::type; ///< The value type being allocated
      using allocator_type = Allocator;                        ///< The type of this allocator

      using pointer       = value_type*;         ///< The type of pointer
      using const_pointer = const value_type*;   ///< Constant version of pointer

      using reference       = value_type&;       ///< The type of reference
      using const_reference = const value_type&; ///< constant version of reference

      using void_pointer       = void*;          ///< The type of void pointer
      using const_void_pointer = const void*;    ///< constant version of void pointer

      using size_type       = std::size_t;       ///< The type used for size
      using difference_type = std::ptrdiff_t;    ///< The type used for pointer differences

      /// \struct internal struct for rebinding this allocator to a new type
      template<typename U>
      struct rebind
      {
        typedef std_allocator<U, Allocator> other;  ///< Rebinding this allocator
      };

      //----------------------------------------------------------------------
      // Constructors / Assignment / Destructor
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs this std_allocator wrapper given the supplied
      ///        Allocator.
      ///
      /// \param alloc the allocator to use in this policy
      explicit std_allocator( Allocator& alloc ) noexcept;

      std_allocator( const std_allocator& other ) noexcept;

      /// \brief Constructs this STLAllocator wrapper given another
      ///        std_allocator
      ///
      /// \param other the other STLAllocator to convert to this
      template <typename U, typename Allocator2>
      std_allocator( const std_allocator<U,Allocator2>& other ) noexcept;

      //----------------------------------------------------------------------
      // Allocation / Deallocation
      //----------------------------------------------------------------------
    public:

      /// \brief Allocates n * sizeof(T) bytes of uninitialized storage
      ///
      /// \param n the number of objects to allocate storage for
      /// \return Pointer to the first byte of a memory block suitably aligned
      /// and sufficient to hold an array of n objects of type T
      pointer allocate( size_type n );

      /// \brief Deallocates the storage referenced by the pointer p, which must
      /// be a pointer obtained by an earlier call to allocate(). The argument n
      /// must be equal to the first argument of the call to allocate() that
      /// originally produced p.
      ///
      /// \param p pointer obtained from allocate()
      /// \param n number of objects earlier passed to allocate()
      void deallocate( pointer p, size_type n );

      //----------------------------------------------------------------------
      // Construction / Destruction
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs an object of type T in allocated uninitialized storage
      /// pointed to by p
      ///
      /// \param p   pointer to allocated uninitialized storage
      /// \param val the value to use as the copy constructor argument
      void construct( pointer p, const_reference val );

      /// \brief Constructs an object of type T in allocated uninitialized storage
      /// pointed to by p
      ///
      /// \param p   pointer to allocated uninitialized storage
      /// \param val the constructor arguments to use
      template<typename U, typename... Args >
      void construct( U* p, Args&&... args );

      //----------------------------------------------------------------------

      /// \brief Calls the destructor of the object pointed to by p
      ///
      /// \param p pointer to the object that is going to be destroyed
      void destroy( pointer p );

      /// \brief Calls the destructor of the object pointed to by p
      ///
      /// \param p pointer to the object that is going to be destroyed
      template<typename U>
      void destroy( U* p );

      //----------------------------------------------------------------------

      /// \brief Returns the maximum theoretically possible value of n, for
      ///        which the call \c allocate(n) could succeed
      ///
      /// \return
      size_type max_size() const noexcept;

      /// \brief Returns the actual address of x even in presence of overloaded
      ///
      /// \param x the object to acquire address of
      /// \return The actual address of x.
      pointer address( reference x ) const;

      /// \brief Returns the actual address of x even in presence of overloaded
      ///
      /// \param x the object to acquire address of
      /// \return The actual address of x.
      const_pointer address( const_reference x ) const;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      Allocator& m_allocator; ///< The allocation policy to use

      //----------------------------------------------------------------------
      // Friend classes
      //----------------------------------------------------------------------
    private:

      template<typename, typename> friend class std_allocator;

    };

    //------------------------------------------------------------------------
    // Global Operators
    //------------------------------------------------------------------------

    /// \brief Compares two allocators. This checks for whether or not both
    /// allocators would be able to allocate and free from the same location
    ///
    /// \return true
    template <class T, class U, class Allocator>
    bool operator==(const std_allocator<T,Allocator>&, const std_allocator<U,Allocator>&);

    /// \brief Compares two allocators to see if they are identical
    ///
    /// \return false
    template <class T, class U, class Allocator>
    bool operator!=(const std_allocator<T,Allocator>&, const std_allocator<U,Allocator>&);

  } // inline namespace stl
} // namespace bit

#include "std_allocator.inl"

#endif /* BIT_INTERNAL_MEMORY_STD_ALLOCATOR_HPP */
