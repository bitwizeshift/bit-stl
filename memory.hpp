/**
 * \file memory.hpp
 *
 * \brief This header contains custom and c++17 extensions to the memory library
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_MEMORY_HPP
#define BIT_STL_MEMORY_HPP

// bit::stl local libraries
#include "stddef.hpp"
#include "type_traits.hpp"

// std types
#include <limits>
#include <memory>

namespace bit {
  namespace stl {

    /// \brief A pointer that represents ownership
    template<typename T>
    using owner = T;

    //------------------------------------------------------------------------
    // Pointer Manipulation
    //------------------------------------------------------------------------

    /// \brief Obtains the actual address of the object referenced
    ///        through an iterator \p it
    ///
    /// \param it the iterator
    /// \return pointer to the value referenced from the iterator
    template<typename InputIterator>
    constexpr auto address_from( InputIterator& it ) noexcept
      -> typename std::iterator_traits<InputIterator>::value_type*;

    /// \brief Dereferences all levels of pointer indirection from the
    ///        supplied pointer
    ///
    /// \note This does not do any null-checking
    ///
    /// \param ptr the pointer to dereference
    /// \return reference to the dereferenced pointer
    template<typename T>
    constexpr decltype(auto) dereference(T& ptr);

    //------------------------------------------------------------------------

    /// \brief Converts a pointer \p ptr into an integral type representing
    ///        the address
    ///
    /// \param ptr the pointer to convert to an integral value
    /// \return the numeric address of the given pointer
    std::uintptr_t to_address( const void* ptr ) noexcept;

    /// \brief Converts a numeric address \p address into a pointer pointing
    ///        to the address location
    ///
    /// \param address the address value to convert to a pointer
    /// \return the pointer pointing to the given address
    void* from_address( std::uintptr_t address ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Retrieves the distance between two pointers
    ///
    /// \note The distance is the positive number of bytes separating
    ///       \p lhs from \p rhs
    ///
    /// \param lhs the left pointer
    /// \param rhs the right pointer
    /// \return the number of bytes between the two
    constexpr std::size_t pointer_distance( const void* lhs,
                                            const void* rhs ) noexcept;

    /// \brief Retrieve the difference between two pointers in bytes
    ///
    /// \param lhs the left pointer to get the difference from
    /// \param rhs the right pointer to get the difference from
    /// \return the difference in bytes between the two pointers
    constexpr std::ptrdiff_t pointer_difference( const void* lhs,
                                                 const void* rhs ) noexcept;

    //------------------------------------------------------------------------

    /// \brief Determines if the pointer \p ptr is within the pointer range
    ///        range [\p first,\p last)
    ///
    /// \param ptr the pointer to determine whether or not its in range
    /// \param first the first entry of the range
    /// \param last the last entry in the range (exclusive)
    /// \return \c true if \p ptr exists between [\p first, \p last)
    constexpr bool in_region( const void* ptr,
                              const void* first,
                              const void* last ) noexcept;

    //------------------------------------------------------------------------
    // Pointer Alignment
    //------------------------------------------------------------------------

    /// \brief Aligns a pointer forward to the given alignment boundary,
    ///        with a specified offset
    ///
    /// \param ptr    the pointer to align
    /// \param align  the alignment boundary to align to
    /// \param offset the amount to offset from the alignment
    /// \return a pair containing the address and the adjustment amount
    std::pair<void*,std::size_t> align_forward( void* ptr,
                                                std::size_t align,
                                                std::size_t offset = 0 ) noexcept;

    /// \brief Aligns a pointer backward to the given alignment boundary,
    ///        with a specified offset
    ///
    /// \param ptr    the pointer to align
    /// \param align  the alignment boundary to align to
    /// \param offset the amount to offset from the alignment
    /// \return a pair containing the address and the adjustment amount
    std::pair<void*,std::size_t> align_backward( void* ptr,
                                                 std::size_t align,
                                                 std::size_t offset = 0 ) noexcept;

    //------------------------------------------------------------------------
    // Alignment Detection
    //------------------------------------------------------------------------

    /// \brief Determines whether the given pointer is aligned to the
    ///        specified alignment
    ///
    /// \param ptr The pointer to determine the alignment of
    /// \param align the alignment to check
    bool is_aligned( const void* ptr, std::size_t align ) noexcept;

    /// \brief Determines the alignment of a given pointer
    ///
    /// \param ptr the pointer to determine the alignment of
    /// \return the alignment of the supplied pointer
    std::size_t align_of( const void* ptr ) noexcept;

    //------------------------------------------------------------------------
    // Uninitialized Construction
    //------------------------------------------------------------------------

    /// \brief Copy constructs an instance of type \p T in the given memory
    ///
    /// \param ptr   The memory location to construct into
    /// \param other The instance to copy
    /// \return Pointer to the initialized memory (cast of \p ptr)
    template<typename T>
    T* uninitialized_copy_at( void* ptr, const T& other );

    /// \brief Move constructs an instance of type \p T in the given memory
    ///
    /// \param ptr   The memory location to construct into
    /// \param other The instance to move
    /// \return Pointer to the initialized memory (cast of \p ptr)
    template<typename T>
    T* uninitialized_move_at( void* ptr, T&& other );

    /// \brief Constructs an instance of type \p T with the given \p args
    ///        at the memory location specified in \p ptr
    ///
    /// \param ptr     The memory location to construct into
    /// \param args... The arguments to supply to T's constructor
    /// \return Pointer to the initialized memory (cast of \p ptr)
    template<typename T, typename...Args>
    T* uninitialized_construct_at( void* ptr, Args&&...args );

    /// \brief Constructs an instance of type \p T with the given \p tuple
    ///        at the memory location specified in \p ptr.
    ///
    /// This forwards the arguments from the \p tuple to the constructor
    /// of T, as if by calling make_from_tuple
    ///
    /// \param ptr   The memory location to construct into
    /// \param tuple The tuple containing arguments to forward to T
    /// \return Pointer ot the initialzied memory (cast of \p ptr)
    template<typename T, typename Tuple>
    T* uninitialized_tuple_construct_at( void* ptr, Tuple&& tuple );

    /// \brief Constructs an instance of type \p T with the given \p args
    ///        at the memory addresses in the given range [\p first, \p last )
    ///
    /// \param first the start of the range of the elements to copy
    /// \param last  the end of the range of the elements to copy
    /// \param args... The arguments to supply to the
    template<typename ForwardIterator, typename...Args>
    void uninitialized_construct( ForwardIterator first, ForwardIterator last, Args&&...args );

    /// \brief Constructs an instance of type \p T with the given \p args
    ///        at the memory addresses in the given range [\p first, \p first + \p n )
    ///
    /// \param first the start of the range of the elements to copy
    /// \param n     the number of entries to construct
    /// \param args... The arguments to supply to the
    template<typename ForwardIterator, typename Size, typename...Args>
    ForwardIterator uninitialized_construct_n( ForwardIterator first, Size n, Args&&...args );

    /// \brief Creates a pointer in uninitialized memory that contains size
    ///        information about the number of entries it should hold
    ///
    /// \note This does not initialize the memory, it simply encodes the size
    ///       with the array in an implementation-defined way
    ///
    /// \param ptr   The memory location to construct into
    /// \param count The number of entries
    /// \return Pointer to the memory containing the array size
    template<typename Size>
    constexpr void* uninitialized_create_array_at( void* ptr, Size count );

    //------------------------------------------------------------------------
    // Destruction
    //------------------------------------------------------------------------

    /// \brief Calls the destructor of the object pointed to by p, as if by p->~T().
    ///
    /// \param p a pointer to the object to be destroyed
    template<typename T>
    void destroy_at( T* p );

    /// \brief Destroys the objects in the range \c [first, \c last)
    ///
    /// \param first the start of the range to destroy
    /// \param end   the end of the range to destroy
    template<typename ForwardIterator>
    void destroy( ForwardIterator first, ForwardIterator last );

    /// \brief Destroys the \p n objects in the range starting at \p first
    ///
    /// \param first the start of the range to destroy
    /// \param n     the number of entries to destroy
    template<typename ForwardIterator>
    ForwardIterator destroy_n( ForwardIterator first, std::size_t n );

    /// \brief Destroys an array of entries at the given \p ptr
    ///
    /// \note The pointer to the destroyed array must have been created with
    ///       A call to uninitialized_create_array_at
    ///
    /// \param ptr A pointer to an
    template<typename T>
    void destroy_array_at( T* ptr );

    //------------------------------------------------------------------------
    // Array Utilities
    //------------------------------------------------------------------------

    /// \brief Default constructs an instance of type \p T in the given memory
    ///
    /// \param ptr The memory location to construct into
    /// \return Pointer to the initialized memory (cast of \p ptr)
    template<typename T>
    T* uninitialized_default_construct_at( void* ptr );

    /// \brief Retrieves the size of any given array that was constructed with
    ///        one of the uninitialized array construct calls.
    constexpr std::size_t array_size( const void* ptr ) noexcept;

    /// \brief Retrieves the max size that an array created with
    ///        \c uninitialized_default_construct_at
    ///
    /// \return the max size the array can hold
    constexpr std::size_t array_max_size() noexcept;

    /// \brief Retrieves the implementation-defined array offset size used in
    ///        uninitialized_create_array_at
    ///
    /// This is used to ensure the appropriate offset when reserving raw-memory
    /// for use as an array, or for doing an aligned offset allocation
    ///
    /// e.g.:
    /// \code
    /// void* ptr       = aligned_offset_malloc( 10, alignof(int), array_offset() );
    /// int*  array_ptr = uninitialized_create_array_at( ptr, 10 );
    /// \endcode
    ///
    /// \return the offset size
    constexpr std::size_t array_offset() noexcept;

    //------------------------------------------------------------------------
    // Hashing
    //------------------------------------------------------------------------

    /// \brief Hashes a unique_ptr
    ///
    /// \param val the ptr to hash
    /// \return the hash of the unique_ptr
    template<typename T, typename Deleter>
    std::size_t hash_value( const std::unique_ptr<T,Deleter>& val ) noexcept;

    /// \brief Hashes a shared_ptr
    ///
    /// \param val the ptr to hash
    /// \return the hash of the unique_ptr
    template<typename T>
    std::size_t hash_value( const std::shared_ptr<T>& val ) noexcept;

  } // namespace stl
} // namespace bit

//#include "internal/memory/memory_pool.hpp"
//#include "internal/memory/aligned_memory_pool.hpp"
#include "internal/memory/indirect_ptr.hpp"
#include "internal/memory/smart_ptr.hpp"
#include "internal/memory/std_allocator.hpp"

#include "detail/memory.inl"

#endif /* BIT_STL_MEMORY_HPP */
