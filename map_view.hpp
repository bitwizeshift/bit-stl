/**
 * \file map_view.hpp
 *
 * \brief This header contains a type-erased view of a map
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_MAP_VIEW_HPP
#define BIT_STL_MAP_VIEW_HPP

// local bit
#include "set_view.hpp"

namespace bit {

  ////////////////////////////////////////////////////////////////////////////
  ///
  ///
  ////////////////////////////////////////////////////////////////////////////
  template<typename Key, typename T>
  class map_view final
  {
    //------------------------------------------------------------------------
    // Public Member Types
    //------------------------------------------------------------------------
  public:

    using key_type        = Key;
    using mapped_type     = T;
    using value_type      = std::pair<const key_type,mapped_type>;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using reference       = value_type&;
    using const_reference = const value_type&;

    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

    //------------------------------------------------------------------------
    // Constructor / Destructor / Assignment
    //------------------------------------------------------------------------
  public:

    /// \brief Constructs an empty map_view
    constexpr map_view();

    /// \brief Constructs a map_view from a given set
    ///
    /// \note This constructor does not participate in overload resolution
    ///       if U is a set_view
    ///
    /// \param other the map-like type to view
#ifndef BIT_DOXYGEN_BUILD
    template<typename U,
             typename = std::enable_if_t<!std::is_same<std::decay_t<U>, map_view>::value> >
#else
    template<typename U>
#endif
    constexpr map_view( U&& u );

    /// \brief Constructs a map_view by copying another map_view
    ///
    /// \param other the map_view to copy
    constexpr map_view( const map_view& );

    /// \brief Constructs a map_view by moving another map_view
    ///
    /// \param other the map_view to move
    constexpr map_view( map_view&& );

    /// \brief Destructs the map_view
    ~map_view() = default;

    //------------------------------------------------------------------------
    // Assignment Operators
    //------------------------------------------------------------------------
  public:

    /// \brief Assigns a new map_view
    map_view& operator=(map_view other);

    //------------------------------------------------------------------------
    // Elemental Access
    //------------------------------------------------------------------------
  public:

    /// \brief Retrieves the mapped type for the given \p key
    ///
    /// \param key the key for the mapped type
    /// \return the mapped type to retrieve
    const mapped_type& at( const key_type& key ) const;

    //------------------------------------------------------------------------
    // Capacity
    //------------------------------------------------------------------------
  public:

    /// \brief Checks if this set_view is empty
    ///
    /// \return \c true if the map_view is empty
    bool empty() const noexcept;

    /// \brief Checks the size of this map_view
    ///
    /// \return the number of entries in this map_view
    size_type size() const noexcept;

    //------------------------------------------------------------------------
    // Lookup
    //------------------------------------------------------------------------
  public:

    /// \brief Counts the number if instances of the given mapped_type
    ///
    /// \param key to count from this map
    /// \return the number of entries of a given key
    size_type count( const key_type& key ) const noexcept;

    /// \brief Determines whether this map_view contains the given \p key
    ///
    /// \param key the key to query
    /// \return \c true if the key exists within the map_view
    bool contains( const key_type& key ) const noexcept;

    /// \brief Returns \c true if this map_view is currently referencing a map
    explicit operator bool() const noexcept;

    //------------------------------------------------------------------------
    // Private Member Types
    //------------------------------------------------------------------------
  private:

    using vtable_type = Key;

    //------------------------------------------------------------------------
    // Private Members
    //------------------------------------------------------------------------
  private:

    const vtable_type* m_vtable;
    void*              m_instance;
  };

} // namespace bit

#endif /* BIT_STL_MAP_VIEW_HPP */
