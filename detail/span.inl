#ifndef BFSTL_DETAIL_ARRAY_VIEW_INL
#define BFSTL_DETAIL_ARRAY_VIEW_INL

namespace bit {

  //--------------------------------------------------------------------------
  // Constructors
  //--------------------------------------------------------------------------

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr span<T,Extent>::span()
    noexcept
    : m_storage(nullptr,0)
  {

  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr span<T,Extent>::span( std::nullptr_t )
    noexcept
    : span()
  {

  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr span<T,Extent>::span( pointer first, pointer last )
    noexcept
    : m_storage(first, std::distance(first,last))
  {

  }

  template<typename T, std::ptrdiff_t Extent>
  template<typename U, std::ptrdiff_t OtherExtent, typename>
  inline constexpr span<T,Extent>::span( const span<U,OtherExtent>& other )
    : m_storage(other.data(), detail::span_extent_type<OtherExtent>(other.size()))
  {

  }

  template<typename T, std::ptrdiff_t Extent>
  template<typename U, std::ptrdiff_t OtherExtent, typename>
  inline constexpr span<T,Extent>::span( span<U,OtherExtent>&& other )
    : m_storage(other.data(), detail::span_extent_type<OtherExtent>(other.size()))
  {

  }

  template<typename T, std::ptrdiff_t Extent>
  template<typename U>
  inline constexpr span<T,Extent>::span( U* ptr, size_type count )
    noexcept
    : m_storage(ptr, count)
  {

  }

  template<typename T, std::ptrdiff_t Extent>
  template<typename U, std::size_t N>
  inline constexpr span<T,Extent>::span( U (&array)[N] )
    noexcept
    : m_storage( &array[0], detail::span_extent_type<N>() )
  {
    static_assert( std::is_convertible<U*,T*>::value, "Type U being assigned is not convertible to T" );
  }

  template<typename T, std::ptrdiff_t Extent>
  template<typename Container, typename>
  inline constexpr span<T,Extent>::span( Container&& container )
    noexcept
    : m_storage( container.data(), container.size() )
  {

  }

  //--------------------------------------------------------------------------
  // Capacity
  //--------------------------------------------------------------------------

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr typename span<T,Extent>::size_type
    span<T,Extent>::length()
    const noexcept
  {
    return size();
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr typename span<T,Extent>::size_type
    span<T,Extent>::size()
    const noexcept
  {
    return m_storage.size();
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr typename span<T,Extent>::size_type
    span<T,Extent>::length_bytes()
    const noexcept
  {
    return size_bytes();
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr typename span<T,Extent>::size_type
    span<T,Extent>::size_bytes()
    const noexcept
  {
    return size() * sizeof(T);
  }


  template<typename T, std::ptrdiff_t Extent>
  inline constexpr bool span<T,Extent>::empty()
    const noexcept
  {
    return m_storage.size() == 0;
  }

  //--------------------------------------------------------------------------
  // Element Access
  //--------------------------------------------------------------------------

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr typename span<T,Extent>::value_type*
    span<T,Extent>::data()
    const noexcept
  {
    return m_storage.data();
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr typename span<T,Extent>::reference
    span<T,Extent>::operator[] ( index_type pos )
    const noexcept
  {
    return m_storage.data()[pos];
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr typename span<T,Extent>::reference
    span<T,Extent>::at( index_type pos )
    const
  {
    BIT_ASSERT( pos >= 0, "Input out of range", pos, size() );
    BIT_ASSERT( static_cast<size_type>(pos) < size(), "Input out of range", pos, size() );

    return *(data() + pos);
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr typename span<T,Extent>::reference
    span<T,Extent>::front()
    const noexcept
  {
    BIT_ASSERT( data(), "View must not be null", data() );
    return *data();
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr typename span<T,Extent>::reference
    span<T,Extent>::back()
    const noexcept
  {
    BIT_ASSERT( data(), "View must not be null", data() );
    return *(data() + (size() - 1));
  }

  //--------------------------------------------------------------------------
  // Operations
  //--------------------------------------------------------------------------

  template<typename T, std::ptrdiff_t Extent>
  inline typename span<T,Extent>::size_type
    span<T,Extent>::copy( value_type* dest,
                           size_type count,
                           size_type pos )
    const
  {
    BIT_ASSERT( pos < size(), "Index out of range", pos, size() );

    const size_type rcount = std::min(size() - pos,count+1);
    std::copy( data() + pos, data() + pos + rcount, dest);
    return rcount;
  }


  template<typename T, std::ptrdiff_t Extent>
  inline constexpr span<T,dynamic_extent>
    span<T,Extent>::subspan( size_type offset, size_type count )
    const
  {
    BIT_ASSERT( offset < size(), "Index out of range", offset, size() );

    const size_type max_length = offset > size() ? 0 : size() - offset;
    const size_type length     = count == dynamic_extent ? max_length : std::min(count,max_length);

    return span<T,dynamic_extent>( data() + offset, length );
  }

  template<typename T, std::ptrdiff_t Extent>
  template<std::ptrdiff_t Offset, std::ptrdiff_t Count>
  inline constexpr span<T,Count>
    span<T,Extent>::subspan()
    const noexcept
  {
    static_assert( Offset < Count || Count == dynamic_extent, "Index out of range" );

    constexpr size_type max_length = Offset > size() ? 0 : size() - Offset;
    constexpr size_type length     = Count == dynamic_extent ? max_length : std::min(Count,max_length);

    return span<T,Count>( data() + offset, length );
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr span<T,dynamic_extent> span<T,Extent>::first( size_type n )
    const
  {
    return subspan( 0, n );
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr span<T,dynamic_extent> span<T,Extent>::last( size_type n )
    const
  {
    return (n > size())
           ? subspan()
           : subspan( size() - n );
  }

  //--------------------------------------------------------------------------
  // Iterators
  //--------------------------------------------------------------------------

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr typename span<T,Extent>::iterator
    span<T,Extent>::begin()
    const noexcept
  {
    return data() ? data() : nullptr;
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr typename span<T,Extent>::iterator
    span<T,Extent>::end()
    const noexcept
  {
    return data() ? (data() + size()) : nullptr;
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr typename span<T,Extent>::const_iterator
    span<T,Extent>::cbegin()
    const noexcept
  {
    return data() ? data() : nullptr;
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr typename span<T,Extent>::const_iterator
    span<T,Extent>::cend()
    const noexcept
  {
    return data() ? data() + size() : nullptr;
  }

  //--------------------------------------------------------------------------

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr typename span<T,Extent>::reverse_iterator
    span<T,Extent>::rbegin()
    const noexcept
  {
    return reverse_iterator( m_storage.data() ? (m_storage.data() + (m_storage.size() - 1)) : nullptr );
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr typename span<T,Extent>::reverse_iterator
    span<T,Extent>::rend()
    const noexcept
  {
    return reverse_iterator( m_storage.data() ? (m_storage.data() - 1) : nullptr );
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr typename span<T,Extent>::const_reverse_iterator
    span<T,Extent>::crbegin()
    const noexcept
  {
    return const_reverse_iteartor( m_storage.data() ? (m_storage.data() + (m_storage.size() - 1)) : nullptr );
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr typename span<T,Extent>::const_reverse_iterator
    span<T,Extent>::crend()
    const noexcept
  {
    return const_reverse_iterator( m_storage.data() ? (m_storage.data() - 1) : nullptr );
  }

  //--------------------------------------------------------------------------
  // Comparison Operators
  //--------------------------------------------------------------------------

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr bool operator == ( const span<T,Extent>& lhs,
                                      const span<T,Extent>& rhs )
    noexcept
  {
    return std::equal(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr bool operator != ( const span<T,Extent>& lhs,
                                      const span<T,Extent>& rhs )
    noexcept
  {
    return !(lhs==rhs);
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr bool operator < ( const span<T,Extent>& lhs,
                                     const span<T,Extent>& rhs )
    noexcept
  {
    return std::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr bool operator <= ( const span<T>& lhs, const span<T>& rhs )
    noexcept
  {
    return !(lhs > rhs);
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr bool operator > ( const span<T,Extent>& lhs,
                                     const span<T,Extent>& rhs )
    noexcept
  {
    return (rhs < lhs);
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr bool operator >= ( const span<T,Extent>& lhs,
                                      const span<T,Extent>& rhs )
    noexcept
  {
    return !(lhs < rhs);
  }

  //==========================================================================
  // span_iterator
  //==========================================================================

  //--------------------------------------------------------------------------
  // span_iterator: Constructors
  //--------------------------------------------------------------------------

  template<typename T>
  inline constexpr span_iterator<T>::span_iterator()
    noexcept
    : m_ptr(nullptr)
  {

  }

  template<typename T>
  inline constexpr span_iterator<T>::span_iterator( const T* ptr )
    noexcept
    : m_ptr( ptr )
  {

  }

  //--------------------------------------------------------------------------
  // span_iterator: Operators
  //--------------------------------------------------------------------------

  template<typename T>
  inline constexpr span_iterator<T>& span_iterator<T>::operator++()
    noexcept
  {
    ++m_ptr;
    return (*this);
  }

  template<typename T>
  inline constexpr span_iterator<T> span_iterator<T>::operator++(int)
    noexcept
  {
    auto result = span_iterator<T>(m_ptr);
    ++m_ptr;
    return result;
  }

  template<typename T>
  inline constexpr span_iterator<T>& span_iterator<T>::operator--()
    noexcept
  {
    --m_ptr;
    return (*this);
  }

  template<typename T>
  inline constexpr span_iterator<T> span_iterator<T>::operator--(int)
    noexcept
  {
    auto result = span_iterator<T>(m_ptr);
    --m_ptr;
    return result;
  }

  template<typename T>
  inline constexpr span_iterator<T>& span_iterator<T>::operator+=( difference_type n )
    noexcept
  {
    m_ptr += n;
    return (*this);
  }

  template<typename T>
  inline constexpr span_iterator<T>& span_iterator<T>::operator-=( difference_type n )
    noexcept
  {
    m_ptr -= n;
    return (*this);
  }

  template<typename T>
  inline constexpr span_iterator<T> span_iterator<T>::operator+( difference_type n )
    const noexcept
  {
    auto result = span_iterator<T>(m_ptr);
    m_ptr += n;
    return result;
  }

  template<typename T>
  inline constexpr span_iterator<T> span_iterator<T>::operator-( difference_type n )
    const noexcept
  {
    auto result = span_iterator<T>(m_ptr);
    m_ptr -= n;
    return result;
  }

  template<typename T>
  inline constexpr typename span_iterator<T>::pointer
    span_iterator<T>::operator->()
    const noexcept
  {
    return m_ptr;
  }

  template<typename T>
  inline constexpr typename span_iterator<T>::reference
    span_iterator<T>::operator*()
    const noexcept
  {
    return *m_ptr;
  }

  //--------------------------------------------------------------------------
  // span_iterator: Comparison Operators
  //--------------------------------------------------------------------------

  template<typename T>
  inline constexpr bool span_iterator<T>::operator==( const span_iterator<T>& rhs )
    noexcept
  {
    return m_ptr == rhs.m_ptr;
  }

  template<typename T>
  inline constexpr bool span_iterator<T>::operator!=( const span_iterator<T>& rhs )
    noexcept
  {
    return m_ptr != rhs.m_ptr;
  }

  template<typename T>
  inline constexpr bool span_iterator<T>::operator<( const span_iterator<T>& rhs )
    noexcept
  {
    return m_ptr < rhs.m_ptr;
  }

  template<typename T>
  inline constexpr bool span_iterator<T>::operator<=( const span_iterator<T>& rhs )
    noexcept
  {
    return m_ptr <= rhs.m_ptr;
  }

  template<typename T>
  inline constexpr bool span_iterator<T>::operator>( const span_iterator<T>& rhs )
    noexcept
  {
    return m_ptr > rhs.m_ptr;
  }

  template<typename T>
  inline constexpr bool span_iterator<T>::operator>=( const span_iterator<T>& rhs )
    noexcept
  {
    return m_ptr >= rhs.m_ptr;
  }

  //==========================================================================
  // Free Functions
  //==========================================================================

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr span<byte> byte_cast( const span<T,Extent>& view )
  {
    return span<byte>( static_cast<byte*>(static_cast<void*>(view.data())), view.size_bytes() );
  }

  template<typename T, std::ptrdiff_t Extent>
  inline constexpr span<const byte> byte_cast( const span<const T,Extent>& view )
  {
    return span<const byte>( static_cast<const byte*>(static_cast<const void*>(view.data())), view.size_bytes() );
  }

} // namespace bfg

#endif /* BFSTL_DETAIL_ARRAY_VIEW_INL */
