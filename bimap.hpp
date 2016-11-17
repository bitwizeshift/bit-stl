/**
 * \file bimap.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_BIMAP_HPP
#define BIT_BIMAP_HPP

#include <map>
#include <iterator>

namespace bit {

  template<typename X, typename Y, typename XIterator, typename YIterator>
  class bimap_iterator
  {
  public:

    bimap_iterator( XIterator x, YIterator y );
    bimap_iterator( const bimap_iterator& other ) = default;
    bimap_iterator( bimap_iterator&& other ) = default;

  private:

    XIterator m_iterator_x;
    YIterator m_iterator_y;

  };

  ////////////////////////////////////////////////////////////////////////////
  /// \brief A bimap is a bidirectional associative container wherein each
  ///        \c <X,Y> pair creates a unique entry.
  ///
  /// All X lookup operations perform in \c O(log(N)), whereas Y lookup
  /// operations perform in \c O(N).
  ///
  /// \tparam X The first key in the bimap
  /// \tparam Y The second key in the bimap
  /// \tparam XCompare The comparison operator type for the first key
  /// \tparam YCompare The comparison operator type for the second key
  /// \tparam Allocator The type of the memory allocator for the bimap
  ////////////////////////////////////////////////////////////////////////////
  template<
    typename X,
    typename Y,
    typename XCompare = std::less<X>,
    typename YCompare = std::less<Y>,
    typename Allocator = std::allocator<std::pair<const X, const Y>>
  >
  class bimap
  {
    //------------------------------------------------------------------------
    // Private Member Types
    //------------------------------------------------------------------------
  public:

    using x_pair_type = std::pair<const X, const Y*>;
    using y_pair_type = std::pair<const Y, const X*>;

    using x_allocator = std::allocator_traits<Allocator>::template rebind_alloc<x_pair_type>;
    using y_allocator = std::allocator_traits<Allocator>::template rebind_alloc<y_pair_type>;

    using x_map = std::map<X,const Y*,XCompare,x_allocator>;
    using y_map = std::map<Y,const X*,YCompare,y_allocator>;

    //------------------------------------------------------------------------
    // Public Member Types
    //------------------------------------------------------------------------
  public:

      using x_type     = X;
      using y_type     = Y;
      using key_type   = std::pair<X, Y>;
      using map_type   = std::pair<X, Y>;
      using value_type = std::pair<const X, const Y>;
      using allocator_type = Allocator;

      using reference       = value_type&;
      using const_reference = const value_type&;
      using pointer         = value_type*;
      using const_pointer   = const value_type*;

      using size_type       = std::size_t;
      using difference_type = std::ptrdiff_t;

      using x_compare = XCompare;
      using y_compare = YCompare;

      using iterator
        = bimap_iterator<X, Y, typename x_map::iterator,
                               typename y_map::iterator>;
      using const_iterator
        = bimap_iterator<X, Y, typename x_map::const_iterator,
                               typename y_map::const_iterator>;
      using reverse_iterator
        = bimap_iterator<X, Y, typename x_map::reverse_iterator,
                               typename y_map::reverse_iterator>;
      using const_reverse_iterator
        = bimap_iterator<X, Y, typename x_map::const_reverse_iterator,
                               typename y_map::const_reverse_iterator>;

      using insert_return_type = std::pair<iterator,bool>;

      //------------------------------------------------------------------------
      // Constructors / Destructor
      //------------------------------------------------------------------------
  public:

      /// \brief Default constructs an empty bimap.
      bimap();

      /// \brief Constructs a bimap given an x-key and y-key comparator
      ///
      /// \param xcomp comparison function object to use for all comparisons of x-entries
      /// \param ycomp comparison function object to use for all comparisons of Y-entries
      /// \param alloc allocator to use for all memory allocations of this container
      explicit bimap( const XCompare& xcomp,
                      const YCompare& ycomp,
                      const Allocator& alloc = Allocator() );

      /// \brief Constructs an empty bimap with the given allocator
      ///
      /// \param alloc the allocator to use for bimap
      explicit bimap( const Allocator& alloc );

      /// \brief Range-constructs the bimap
      ///
      /// \param first the start range to copy the elements from
      /// \param last  the last range to copy the elements from
      /// \param xcomp comparison function object to use for all comparisons of x-entries
      /// \param ycomp comparison function object to use for all comparisons of Y-entries
      /// \param alloc allocator to use for all memory allocations of this container
      template<typename InputIterator>
      bimap( InputIterator first,
             InputIterator last,
             const XCompare& xcomp = XCompare(),
             const YCompare& ycomp = YCompare(),
             const Allocator& alloc = Allocator() );

      /// \brief Range-constructs the bimap
      ///
      /// \param first the start range to copy the elements from
      /// \param last  the last range to copy the elements from
      /// \param alloc allocator to use for all memory allocations of this container
      template<typename InputIterator>
      bimap( InputIterator first, InputIterator last, const Allocator& alloc );

      /// \brief Copy constructs a bimap from another bimap
      ///
      /// \param other the other bimap to copy
      bimap( const bimap& other );

      /// \brief Copy constructs a bimap from another bimap with an allocator
      ///
      /// \param other the other bimap to copy
      /// \param alloc allocator to use for all memory allocations of this container
      bimap( const bimap& other, const Allocator& alloc );

      /// \brief Move constructs a bimap from another bimap with an allocator
      ///
      /// \param other the other bimap to move
      bimap( bimap&& other );

      /// \brief Move constructs a bimap from another bimap with an allocator
      ///
      /// \param other the other bimap to move
      /// \param alloc allocator to use for all memory allocations of this container
      bimap( bimap&& other, const Allocator& alloc );

      /// \brief Constructs the bimap with the contents of the initializer list \p init
      ///
      /// \param init  initializer list to initialize the elements of the container with
      /// \param xcomp comparison function object to use for all comparisons of x-entries
      /// \param ycomp comparison function object to use for all comparisons of Y-entries
      /// \param alloc allocator to use for all memory allocations of this container
      bimap( std::initializer_list<value_type> init,
             const XCompare& xcomp = XCompare(),
             const YCompare& ycomp = YCompare(),
             const Allocator& alloc = Allocator() );

      /// \brief Constructs the bimap with the contents of the initializer list \p init
      ///
      /// \param init  initializer list to initialize the elements of the container with
      /// \param alloc allocator to use for all memory allocations of this container
      bimap( std::initializer_list<value_type> init, const Allocator& alloc );

      //------------------------------------------------------------------------
      // Assignment
      //------------------------------------------------------------------------
  public:

      /// \brief Copy-assigns the contents of the container
      ///
      /// \param other the other bimap to copy
      bimap& operator=( const bimap& other );

      /// \brief Move-assigns the contents of the container
      ///
      /// \param other the other bimap to move
      bimap& operator=( bimap&& other );

      /// \brief Replaces the contents with those identified by initializer list
      ///        \p ilist
      ///
      /// \param ilist the initializer list of entries
      bimap& operator=( std::initializer_list<value_type> ilist );

      //------------------------------------------------------------------------
      // Accessor
      //------------------------------------------------------------------------
  public:

      /// \brief Gets the allocator from the bimap
      allocator_type get_allocator() const;

      //------------------------------------------------------------------------
      // Capacity
      //------------------------------------------------------------------------
  public:

      /// \brief Checks if the container has no elements
      ///
      /// \return \c true if the container is empty, \c false otherwise
      bool empty() const noexcept;

      /// \brief Returns the number of elements in the container
      ///
      /// \return The number of elements in the container
      size_type size() const noexcept;

      /// \brief Returns the maximum number of elements the container is able
      ///        to hold due to system or library implementation limitations
      ///
      /// \return Maximum number of elements
      size_type max_size() const noexcept;

      //------------------------------------------------------------------------
      // Insertions
      //------------------------------------------------------------------------
  public:

      /// \brief Inserts an element into the container, if the container doesn't
      ///        already contain an element with an equivalent key
      ///
      /// \param x The x element to insert
      /// \param y The y element to insert
      /// \return a pair containing the iterator and location it was inserted
      insert_return_type insert( const x_type& x, const y_type& y );

      /// \brief Inserts an element into the container, if the container doesn't
      ///        already contain an element with an equivalent key
      ///
      /// \param x The x element to insert
      /// \param y The y element to insert
      /// \return a pair containing the iterator and location it was inserted
      insert_return_type insert( x_type&& x, y_type&& y );

      /// \brief Inserts an element into the container, if the container doesn't
      ///        already contain an element with an equivalent key
      ///
      /// \param value the value to insert
      /// \return a pair containing the iterator and location it was inserted
      insert_return_type insert( const value_type& value );

      /// \brief Inserts an element into the container, if the container doesn't
      ///        already contain an element with an equivalent key
      ///
      /// \param value the value to insert
      /// \return a pair containing the iterator and location it was inserted
      insert_return_type insert( value_type&& value );

      template< class InputIt >
      void insert( InputIt first, InputIt last );

      void insert( std::initializer_list<value_type> ilist );

      //------------------------------------------------------------------------
      // Erasing
      //------------------------------------------------------------------------
  public:

      iterator erase( const_iterator pos );

      iterator erase( const_iterator first, const_iterator last );

      size_type erase( const key_type& key );

      size_type erase_x( const x_type& key );

      size_type erase_y( const y_type& key );

      //------------------------------------------------------------------------
      // Mutators
      //------------------------------------------------------------------------
  public:

      /// \brief Removes all elements from the container.
      ///
      /// Invalidates any references, pointers, or iterators referring to
      /// contained elements. Any past-the-end iterator remains valid
      void clear();

      /// \brief Exchanges the contents of the container with those of other
      ///
      /// Does not invoke any move, copy, or swap operations on individual
      /// elements.
      ///
      /// All iterators and references remain valid. The past-the-end iterator
      /// is invalidated.
      ///
      /// \param other the other bimap to swap
      void swap( bimap& other );

      //------------------------------------------------------------------------
      // Lookup
      //------------------------------------------------------------------------
  public:

      size_type count( const key_type& key ) const noexcept;

      template<typename K>
      size_type count( const K& key ) const noexcept;

      //------------------------------------------------------------------------

      size_type count_x( const x_type& x ) const noexcept;

      template<typename K>
      size_type count_x( const K& x ) const noexcept;

      //------------------------------------------------------------------------

      size_type count_y( const y_type& y ) const noexcept;

      template<typename K>
      size_type count_y( const K& y ) const;

      //------------------------------------------------------------------------

      iterator find( const key_type& key );

      const_iterator find( const key_type& key ) const;

      template<typename K>
      iterator find( const K& key );

      template<typename K>
      const_iterator find( const K& key ) const;

      //------------------------------------------------------------------------

      iterator find_x( const x_type& key );

      const_iterator find_x( const x_type& key ) const;

      template<typename K>
      iterator find_x( const K& key );

      template<typename K>
      const_iterator find_x( const K& key ) const;

      //------------------------------------------------------------------------

      iterator find_y( const y_type& key );

      const_iterator find_y( const y_type& key ) const;

      template<typename K>
      iterator find_y( const K& key );

      template<typename K>
      const_iterator find_y( const K& key ) const;

      //------------------------------------------------------------------------
      // Iterators
      //------------------------------------------------------------------------
  public:

      iterator begin() noexcept;
      const_iterator begin() const noexcept;
      const_iterator cbegin() const noexcept;

      iterator end() noexcept;
      const_iterator end() const noexcept;
      const_iterator cend() const noexcept;

      reverse_iterator rbegin() noexcept;
      const_reverse_iterator rbegin() const noexcept;
      const_reverse_iterator crbegin() const noexcept;

      reverse_iterator rend() noexcept;
      const_reverse_iterator rend() const noexcept;
      const_reverse_iterator crend() const noexcept;

      //------------------------------------------------------------------------
      // Observers
      //------------------------------------------------------------------------
  public:

      x_compare x_comp() const noexcept;

      y_compare y_comp() const noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
  private:

      x_map          m_map_x; ///< The map containing the X-key entry
      y_map          m_map_y; ///< The map containing the Y-key entry
      allocator_type m_alloc; ///< The allocator for this bimap

  };

  /// \param Swaps the \p lhs entry with the \p rhs entry
  ///
  /// \param lhs the left bimap to swap
  /// \param rhs the right bimap to swap
  template<typename X, typename Y>
  void swap( bimap<X,Y>& lhs, bimap<X,Y>& rhs ) noexcept;

}

#include "detail/bimap.inl"

#endif /* BIT_BIMAP_HPP */
