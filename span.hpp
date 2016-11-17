/**
 * \file span.hpp
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_SPAN_HPP
#define BIT_SPAN_HPP

// local bit libraries
#include "type_traits.hpp"
#include "assert.hpp"

#include <iterator>
#include <limits>

namespace bit {

  // Private Type Traits

  constexpr auto dynamic_extent = std::ptrdiff_t{-1};

  namespace detail {

    //////////////////////////////////////////////////////////////////////////
    /// \brief A type used to manage the extent.
    ///
    /// This is used in conjunction with storage_type to leverage
    /// empty base-class optimization.
    //////////////////////////////////////////////////////////////////////////
    template <std::ptrdiff_t Extent>
    class span_extent_type
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using index_type = std::ptrdiff_t;

      static_assert(Extent >= 0, "A fixed-size span must be >= 0 in size.");

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs an extent
      constexpr span_extent_type() noexcept {}

      /// \brief Constructs an extent from another extent
      ///
      /// \tparam Other the other extent value
      /// \param extent the other extent entry
      template <index_type Other>
      constexpr span_extent_type(span_extent_type<Other> extent)
      {
        static_assert( Other == Extent || Other == dynamic_extent,
                      "Mismatch between fixed-size extent and size of initializing data.");

        BIT_ASSERT(extent.size() == Extent,"Extent size must match for fixed size types");
      }

      constexpr span_extent_type( index_type size )
      {
        BIT_ASSERT( size == Extent,"Extent size must match for fixed size types");
      }

      //----------------------------------------------------------------------
      // Capacity
      //----------------------------------------------------------------------
    public:

      constexpr inline index_type size()
        const noexcept
      {
        return Extent;
      }
    };

    template <>
    class span_extent_type<dynamic_extent>
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using index_type = std::ptrdiff_t;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      template <index_type Other>
      explicit constexpr span_extent_type(span_extent_type<Other> extent)
        : m_size(extent.size())
      {

      }

      explicit constexpr span_extent_type(index_type size)
        : m_size(size)
      {
        BIT_ASSERT( size >= 0, "Span size must be greater than 0" );
      }

      //----------------------------------------------------------------------
      // Capacity
      //----------------------------------------------------------------------
    public:

      constexpr inline index_type size()
        const noexcept
      {
        return m_size;
      }

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      index_type m_size;
    };

    //========================================================================
    // Type-Traits
    //========================================================================

    template<std::ptrdiff_t To, std::ptrdiff_t From>
    struct is_allowed_extent_conversion
      : std::integral_constant<bool, From == To ||
                                     From == dynamic_extent ||
                                     To   == dynamic_extent>{};

    template <typename From, typename To>
    struct is_allowed_element_type_conversion
      : std::is_convertible<From (*)[], To (*)[]>{};


    template<typename T, typename = void>
    struct has_data_member_function : std::false_type{};

    template<typename T>
    struct has_data_member_function<T,void_t<decltype(std::declval<T>().data())>> : std::true_type{};

    template<typename T, typename = void>
    struct has_size_member_function : std::false_type{};

    template<typename T>
    struct has_size_member_function<T,void_t<decltype(std::declval<T>().size())>> : std::true_type{};

  }

  template<typename T>
  class span_iterator;

  ////////////////////////////////////////////////////////////////////////////
  /// \brief A light-weight non-owning wrapper around contiguous memory.
  ///
  /// Overloads are provided for easy conversion from std::vector,
  /// std::array, references-to-arrays, strings, and simple pointer/size pairs.
  ///
  /// This helps to effectively reduce the number of available operations,
  /// while still exposing contiguous data to the client.
  ///
  /// This is based on Microsoft's implementation of the gsl::span
  ///
  /// \tparam T The type of this array view
  /// \tparam N The maximum size of this array view (default: unbounded)
  ///
  /// \ingroup core
  ////////////////////////////////////////////////////////////////////////////
  template<typename T, std::ptrdiff_t Extent = dynamic_extent>
  class span final
  {
    //------------------------------------------------------------------------
    // Public Member Types
    //------------------------------------------------------------------------
  public:

    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T*;

    using size_type  = std::ptrdiff_t;
    using index_type = std::ptrdiff_t;

    using iterator               = span_iterator<T>;
    using const_iterator         = span_iterator<const T>;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    //------------------------------------------------------------------------
    // Public Static Members
    //------------------------------------------------------------------------
  public:

    static constexpr size_type extent = Extent; ///< The extent of this view

    //------------------------------------------------------------------------
    // Constructors
    //------------------------------------------------------------------------
  public:

    template<typename U, std::ptrdiff_t OtherExtent>
    using enable_if_allowed_t = std::enable_if_t<
      detail::is_allowed_extent_conversion<OtherExtent, Extent>::value &&
      detail::is_allowed_element_type_conversion<U, value_type>::value
    >;

    /// \brief Constructs an span containing 0 entries
    constexpr span() noexcept;

    /// \brief Constructs an span containing 0 entries
    constexpr span( std::nullptr_t ) noexcept;

    /// \brief Constructs an span
    constexpr span( pointer first, pointer last ) noexcept;

    /// \brief Constructs an span by copying another span
    ///
    /// \param other the other span
#ifndef BIT_DOXYGEN
    template<typename U, std::ptrdiff_t OtherExtent, typename = enable_if_allowed_t<U,OtherExtent>>
#else
    template<typename U, std::ptrdiff_t OtherExtent>
#endif
    constexpr span( const span<U,OtherExtent>& other );

    /// \brief Constructs an span by moving another span
    ///
    /// \param other the other span
#ifndef BIT_DOXYGEN
    template<typename U, std::ptrdiff_t OtherExtent, typename = enable_if_allowed_t<U,OtherExtent>>
#else
    template<typename U, std::ptrdiff_t OtherExtent>
#endif
    constexpr span( span<U,OtherExtent>&& other );

    /// \brief Constructs an span from the specified \p ptr with
    ///        size \p count
    ///
    /// \param ptr   pointer to the data
    /// \param count the number of entries
    template<typename U>
    constexpr span( U* ptr, size_type count ) noexcept;

    /// \brief Constructs an span from a given array reference
    ///
    /// \param array a reference to a const T array of size N
    template<typename U, std::size_t N>
    constexpr span( U (&array)[N] ) noexcept;

    /// \brief Constructs an span from a given contiguous container
    ///        that contains a data() member function and a size() member
    ///        function
    ///
    /// \param container the container to construct an span out of
#ifndef BFG_DOXYGEN_BUILD
    template<typename Container,
             typename = std::enable_if_t<is_contiguous_container<Container>::value>>
#else
    template<typename Container>
#endif
    constexpr span( Container&& container ) noexcept;

    //------------------------------------------------------------------------
    // Assignment
    //------------------------------------------------------------------------
  public:

    /// \brief Assigns an span
    ///
    /// This will automatically resize the span to refer to at most N
    /// bytes of the supplied view
    ///
    /// \param other the span to copy
    /// \return reference to \c (*this)
    span& operator=( const span& other ) noexcept = default;

    /// \brief Assigns a span
    ///
    /// \param other the span to move
    /// \return reference to \c (*this)
    span& operator=( span&& other ) noexcept = default;

    //------------------------------------------------------------------------
    // Capacity
    //------------------------------------------------------------------------
  public:

    /// \brief Returns the size of the span
    ///
    /// \return the number of entries in the span
    constexpr size_type length() const noexcept;

    /// \brief Returns the size of the span
    ///
    /// \return the number of entries in the span
    constexpr size_type size() const noexcept;

    /// \brief Returns the size of the span in bytes
    ///
    /// \return the number of bytes in the span
    constexpr size_type length_bytes() const noexcept;

    /// \brief Returns the size of the span in bytes
    ///
    /// \return the number of bytes in the span
    constexpr size_type size_bytes() const noexcept;

    /// \brief Returns whether the span is empty
    ///        (i.e. whether its size is 0).
    ///
    /// \return \c true if the span is empty
    constexpr bool empty() const noexcept;

    //------------------------------------------------------------------------
    // Element Access
    //------------------------------------------------------------------------
  public:

    /// \brief Gets the data of the current span
    ///
    /// \return the data this non-const span contains
    constexpr value_type* data() const noexcept;

    /// \brief Accesses the element at index \p pos
    ///
    /// \param pos the index to access
    /// \return const reference to the entry
    constexpr reference operator[]( index_type pos ) const noexcept;

    /// \brief Accesses the element at index \p pos
    ///
    /// \param pos the index to access
    /// \return const reference to the entry
    constexpr reference at( index_type pos ) const;

    /// \brief Access the first entry of the span
    ///
    /// \note Undefined behavior if span is empty
    ///
    /// \return reference to the first entry of the span
    constexpr reference front() const noexcept;

    /// \brief References the last entry of the span
    ///
    /// \note Undefined behavior if span is empty
    ///
    /// \return reference to the last entry of the span
    constexpr reference back() const noexcept;

    //------------------------------------------------------------------------
    // Operations
    //------------------------------------------------------------------------
  public:

    /// \brief Copies the sublist [pos, pos + rcount) to the data pointed
    ///        to by dest, where rcount is the smaller of count and size() - pos.
    ///
    /// \param dest pointer to the destination data
    /// \param count requested sublist length
    /// \param pos position of the first entry
    size_type copy( value_type* dest,
                    size_type count = dynamic_extent,
                    size_type pos = 0 ) const;

    /// \brief Returns a subview of this span
    ///
    /// \param offset the position of the first entry in the subview
    /// \param count  the length of the subview
    /// \return the created span subview
    constexpr span<T,dynamic_extent> subspan( size_type offset, size_type count = dynamic_extent ) const;

    /// \brief Returns a subview of this span
    ///
    /// \tparam Offset the position of the first entry in the subview
    /// \tparam Count  the length of the subview
    /// \return the created span subview
    template<std::ptrdiff_t Offset, std::ptrdiff_t Count = dynamic_extent>
    constexpr span<T,Count> subspan() const noexcept;

    /// \brief Returns a subview consisting of the first \p n entries
    ///        of the span
    ///
    /// \param n the number of entries from the beginning of the span
    /// \return the created span subview
    constexpr span<T,dynamic_extent> first( size_type n ) const;

    /// \brief Returns a subview consisting of the last \p n entries
    ///        of the span
    ///
    /// \param n the number of entries from the end of the span
    /// \return the created span subview
    constexpr span<T,dynamic_extent> last( size_type n ) const;

    //------------------------------------------------------------------------
    // Iterators
    //------------------------------------------------------------------------
  public:

    /// \brief Retrieves the begin iterator for this span
    ///
    /// \return the begin iterator
    constexpr iterator begin() const noexcept;

    /// \brief Retrieves the end iterator for this span
    ///
    /// \return the end iterator
    constexpr iterator end() const noexcept;

    /// \copydoc span::begin()
    constexpr const_iterator cbegin() const noexcept;

    /// \copydoc span::end()
    constexpr const_iterator cend() const noexcept;

    //------------------------------------------------------------------------

    /// \brief Retrieves the reverse begin iterator for this array_View
    ///
    /// \return the reverse begin iterator
    constexpr reverse_iterator rbegin() const noexcept;

    /// \brief Retrieves the reverse end iterator for this array_View
    ///
    /// \return the reverse end iterator
    constexpr reverse_iterator rend() const noexcept;

    /// \copydoc span::rbegin()
    constexpr const_reverse_iterator crbegin() const noexcept;

    /// \brief span::rend()
    constexpr const_reverse_iterator crend() const noexcept;

    //------------------------------------------------------------------------
    // Private Members
    //------------------------------------------------------------------------
  private:

    /// \brief Internal class to use for storage of data
    template<typename ExtentType>
    class storage_type : public ExtentType
    {
    public:
      template <class OtherExtentType>
      constexpr storage_type(pointer data, OtherExtentType ext)
        : ExtentType(ext), m_data(data)
      {
        // Expects((!data && ExtentType::size() == 0) || (data && ExtentType::size() >= 0));
      }

      constexpr inline pointer data()
        const noexcept
      {
        return m_data;
      }

    private:

      pointer m_data;
    };

    using extent_storage = storage_type<detail::span_extent_type<Extent>>;

    extent_storage m_storage;
  };

  //--------------------------------------------------------------------------
  // Comparison Operators
  //--------------------------------------------------------------------------

  /// \brief Performs equality comparison between all entries in the span
  ///
  /// \param lhs the left span to compare
  /// \param rhs the right span to compare
  /// \return \c true if the spans contain the same elements in the same order
  template<typename T, std::ptrdiff_t Extent>
  constexpr bool operator == ( const span<T,Extent>& lhs,
                               const span<T,Extent>& rhs ) noexcept;

  /// \brief Performs inequality comparison between all entries in the span
  ///
  /// \param lhs the left span to compare
  /// \param rhs the right span to compare
  /// \return \c false if the spans contain the same elements in the same order
  template<typename T, std::ptrdiff_t Extent>
  constexpr bool operator != ( const span<T,Extent>& lhs,
                               const span<T,Extent>& rhs ) noexcept;

  /// \brief Lexographically compares all entries in the span
  ///
  /// \param lhs the left span to compare
  /// \param rhs the right span to compare
  /// \return \c true if the left span is lexographically less than the right
  template<typename T, std::ptrdiff_t Extent>
  constexpr bool operator < ( const span<T,Extent>& lhs,
                              const span<T,Extent>& rhs ) noexcept;

  /// \brief Lexographically compares all entries in the span
  ///
  /// \param lhs the left span to compare
  /// \param rhs the right span to compare
  /// \return \c true if the left span is lexographically less than or equal
  ///         to the right entry
  template<typename T, std::ptrdiff_t Extent>
  constexpr bool operator <= ( const span<T,Extent>& lhs,
                               const span<T,Extent>& rhs ) noexcept;

  /// \brief Lexographically compares all entries in the span
  ///
  /// \param lhs the left span to compare
  /// \param rhs the right span to compare
  /// \return \c true if the left span is lexographically greater than the
  ///         right entry
  template<typename T, std::ptrdiff_t Extent>
  constexpr bool operator > ( const span<T,Extent>& lhs,
                              const span<T,Extent>& rhs ) noexcept;

  /// \brief Lexographically compares all entries in the span
  ///
  /// \param lhs the left span to compare
  /// \param rhs the right span to compare
  /// \return \c true if the left span is lexographically greater than
  ///         or equal to the right entry
  template<typename T, std::ptrdiff_t Extent>
  constexpr bool operator >= ( const span<T,Extent>& lhs,
                               const span<T,Extent>& rhs ) noexcept;

  ////////////////////////////////////////////////////////////////////////////
  /// \brief An iterator for span type
  ////////////////////////////////////////////////////////////////////////////
  template<typename T>
  class span_iterator
  {
    //------------------------------------------------------------------------
    // Public Member Types
    //------------------------------------------------------------------------
  public:

    using value_type        = T;
    using pointer           = const T*;
    using reference         = const T&;
    using difference_type   = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    //------------------------------------------------------------------------
    // Constructors
    //------------------------------------------------------------------------
  public:

    /// \brief Default constructs a span_iterator
    constexpr span_iterator() noexcept;

    /// \brief Constructs a span_iterator from a pointer
    ///
    /// \param ptr the pointer to copy
    constexpr span_iterator(const T* ptr) noexcept;
    constexpr span_iterator(const span_iterator&) noexcept = default;
    constexpr span_iterator(span_iterator&&) noexcept = default;

    //------------------------------------------------------------------------
    // Operators
    //------------------------------------------------------------------------
  public:

    constexpr span_iterator& operator++() noexcept;
    constexpr span_iterator  operator++(int) noexcept;

    constexpr span_iterator& operator--() noexcept;
    constexpr span_iterator  operator--(int) noexcept;

    constexpr span_iterator& operator+=( difference_type n ) noexcept;
    constexpr span_iterator& operator-=( difference_type n ) noexcept;

    constexpr span_iterator operator+ ( difference_type n ) const noexcept;
    constexpr span_iterator operator- ( difference_type n ) const noexcept;

    constexpr pointer operator->() const noexcept;
    constexpr reference operator*() const noexcept;

    //------------------------------------------------------------------------
    // Comparison Operators
    //------------------------------------------------------------------------
  public:

    constexpr bool operator == ( const span_iterator& rhs ) noexcept;
    constexpr bool operator != ( const span_iterator& rhs ) noexcept;
    constexpr bool operator <  ( const span_iterator& rhs ) noexcept;
    constexpr bool operator <= ( const span_iterator& rhs ) noexcept;
    constexpr bool operator >  ( const span_iterator& rhs ) noexcept;
    constexpr bool operator >= ( const span_iterator& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Private Member Types
    //------------------------------------------------------------------------
  private:

    const T* m_ptr;
  };

  //--------------------------------------------------------------------------
  // Type Traits
  //--------------------------------------------------------------------------

  /// \brief Is the given type an span ?
  ///
  /// \tparam T the type to check
  ///
  /// The result is aliased as \c ::value
  template<typename T>
  struct is_span : std::false_type{};

  template<typename T, std::ptrdiff_t N>
  struct is_span< span<T,N> > :  std::true_type{};

  /// \brief Is the given type a dynamic span?
  ///
  /// \tparam T the type to check
  ///
  /// The result is aliased as \c ::value
  template<typename T>
  struct is_dynamic_span : std::false_type{};

  template<typename T>
  struct is_dynamic_span< span<T,dynamic_extent> > : std::true_type{};

  namespace detail {

    template<typename T, std::ptrdiff_t Extent>
    struct calculate_extent_as_bytes
      : std::integral_constant<std::ptrdiff_t,Extent * sizeof(T)>{};

    template<typename T>
    struct calculate_extent_as_bytes<T,dynamic_extent>
      : std::integral_constant<std::ptrdiff_t,dynamic_extent>{};

  } // namespace detail

  /// \brief Casts an span viewing a non-const object into a byte view
  ///
  /// \param view the view to cast
  /// \return the view as a stream of bytes
  template<typename T, std::ptrdiff_t Extent>
  constexpr span<byte> byte_cast( const span<T,Extent>& view );

  /// \brief Casts an span viewing a const object into a const byte view
  ///
  /// \param view the view to cast
  /// \return the view as a stream of const bytes
  template<typename T, std::ptrdiff_t Extent>
  constexpr span<const byte> byte_cast( const span<const T,Extent>& view );

} // namespace bfg

#include "detail/span.inl"

#endif /* BIT_SPAN_HPP */
