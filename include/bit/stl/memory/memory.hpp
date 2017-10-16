/**
 * \file memory.hpp
 *
 * \brief This header contains custom and c++17 extensions to the memory library
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_MEMORY_MEMORY_HPP
#define BIT_STL_MEMORY_MEMORY_HPP

// bit::stl local libraries
#include "../utilities/stddef.hpp"
#include "../utilities/type_traits.hpp"

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
    std::uintptr_t to_address( void* ptr ) noexcept;

    /// \brief Converts a numeric address \p address into a pointer pointing
    ///        to the address location
    ///
    /// \param address the address value to convert to a pointer
    /// \return the pointer pointing to the given address
    void* from_address( std::uintptr_t address ) noexcept;

    //------------------------------------------------------------------------
    // Uninitialized Construction
    //------------------------------------------------------------------------

    /// \brief Default constructs an instance of type \p T in the given memory
    ///
    /// \param ptr The memory location to construct into
    /// \return Pointer to the initialized memory (cast of \p ptr)
    template<typename T>
    T* uninitialized_default_construct_at( void* ptr );

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

    //------------------------------------------------------------------------
    // Comparisons
    //------------------------------------------------------------------------

    /// \brief Performs a deep comparison of two pointer-like objects
    ///
    /// \param lhs the left pointer
    /// \param rhs the right pointer
    /// \return \c true if \p lhs is the same as \p rhs
    /// \{
    template<typename T, typename U>
    constexpr bool deep_compare( const T& lhs, const U& rhs ) noexcept;
    template<typename T>
    constexpr bool deep_compare( std::nullptr_t, const T& rhs ) noexcept;
    template<typename T>
    constexpr bool deep_compare( const T& lhs, std::nullptr_t ) noexcept;
    constexpr bool deep_compare( std::nullptr_t, std::nullptr_t ) noexcept;
    /// \}
  } // namespace stl
} // namespace bit

#include "detail/memory.inl"

#endif /* BIT_STL_MEMORY_MEMORY_HPP */
