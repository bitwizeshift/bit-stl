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
