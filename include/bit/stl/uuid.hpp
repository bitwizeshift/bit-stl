/**
 * \file uuid.hpp
 *
 * \brief This header contains an implementation of a universal identifier
 *        structure
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_UUID_HPP
#define BIT_STL_UUID_HPP

#include "stddef.hpp"
#include "pointer_iterator.hpp"

#include <algorithm>

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \class uuid
    /// \brief A wrapper type to represent universally unique identifiers
    ///
    //////////////////////////////////////////////////////////////////////////
    class uuid
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using value_type      = byte;
      using reference       = value_type&;
      using pointer         = value_type*;
      using const_reference = const value_type&;
      using const_pointer   = const value_type*;

      using iterator        = pointer_iterator<const byte*,uuid>;
      using const_iterator  = pointer_iterator<const byte*,uuid>;

      using size_type = std::size_t;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a uuid without initializing any entries
      uuid() noexcept;

      /// \brief Constructs a uuid from an array of 16 bytes
      ///
      /// \param array a reference to an array containing 16 bytes
      constexpr uuid( const value_type(&array)[16] ) noexcept;

      /// \brief Copy-constructs a uuid from another uuid
      ///
      /// \param other the other uuid to copy
      constexpr uuid( const uuid& other ) noexcept = default;

      /// \brief Move-constructs a uuid from another uuid
      ///
      /// \param other the other uuid to move
      constexpr uuid( uuid& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Assigns a uuid from an array of 16 bytes
      ///
      /// \param array a reference to an array containing 16 bytes
      /// \return a reference to \c (*this)
      uuid& operator=( const value_type(&)[16] ) noexcept;

      /// \brief Copy-assigns this uuid from another uuid
      ///
      /// \param other the other uuid to copy
      /// \return a reference to \c (*this)
      uuid& operator=( const uuid& other ) noexcept = default;

      /// \brief Move-assigns this uuid from another uuid
      ///
      /// \param other the other uuid to move
      /// \return a reference to \c (*this)
      uuid& operator=( uuid&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Capacity
      //----------------------------------------------------------------------
    public:

      /// \brief Returns the size of this uuid
      ///
      /// \return 16
      constexpr size_type size() const noexcept;

      //----------------------------------------------------------------------
      // Iterators
      //----------------------------------------------------------------------
    public:

      /// \brief Returns an iterator to the beginning of the uuid sequence
      ///
      /// \return iterator to the beginning
      constexpr iterator begin() const noexcept;

      /// \brief Returns an iterator to the end of the uuid sequence
      ///
      /// \return iterator to the end
      constexpr iterator end() const noexcept;

      /// \copydoc uuid::begin() const noexcept
      constexpr iterator cbegin() const noexcept;

      /// \copydoc uuid::end() const noexcept
      constexpr iterator cend() const noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      value_type m_storage[16]; ///< the storage of the uuid bytes
    };

    //------------------------------------------------------------------------
    // Comparison Operators
    //------------------------------------------------------------------------

    bool operator==(const uuid& lhs, const uuid& rhs) noexcept;
    bool operator!=(const uuid& lhs, const uuid& rhs) noexcept;
    bool operator<(const uuid& lhs, const uuid& rhs) noexcept;
    bool operator>(const uuid& lhs, const uuid& rhs) noexcept;
    bool operator<=(const uuid& lhs, const uuid& rhs) noexcept;
    bool operator>=(const uuid& lhs, const uuid& rhs) noexcept;

  } // namespace stl
} // namespace bit

#include "detail/uuid.inl"

#endif /* BIT_STL_UUID_HPP */
