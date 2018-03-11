/**
 * \file memory.hpp
 *
 * \brief This header contains custom and c++17 extensions to the memory library
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

/*
  The MIT License (MIT)

  Bit Standard Template Library.
  https://github.com/bitwizeshift/bit-stl

  Copyright (c) 2018 Matthew Rodusek

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#ifndef BIT_STL_MEMORY_MEMORY_HPP
#define BIT_STL_MEMORY_MEMORY_HPP

#include "../traits/composition/conjunction.hpp"
#include "../traits/composition/disjunction.hpp"
#include "../traits/composition/negation.hpp"

#include <cstddef>  // std::size_t
#include <cstdint>  // std::uintptr_t
#include <memory>   // std::addressof
#include <iterator> // std::iterator_traits

namespace bit {
  namespace stl {

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
