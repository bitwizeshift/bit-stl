#ifndef BIT_STL_DETAIL_SPAN_INL
#define BIT_STL_DETAIL_SPAN_INL

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename T, std::ptrdiff_t Extent>
inline constexpr bit::stl::span<T,Extent>::span()
  noexcept
  : m_storage(nullptr,0)
{

}

template<typename T, std::ptrdiff_t Extent>
inline constexpr bit::stl::span<T,Extent>::span( std::nullptr_t )
  noexcept
  : span()
{

}

template<typename T, std::ptrdiff_t Extent>
inline constexpr bit::stl::span<T,Extent>::span( pointer first, pointer last )
  noexcept
  : m_storage(first, std::distance(first,last))
{

}

template<typename T, std::ptrdiff_t Extent>
template<typename U, std::ptrdiff_t OtherExtent, typename>
inline constexpr bit::stl::span<T,Extent>::
  span( const span<U,OtherExtent>& other )
  : m_storage(other.data(), bit::stl::detail::span_extent_type<OtherExtent>(other.size()))
{

}

template<typename T, std::ptrdiff_t Extent>
template<typename U, std::ptrdiff_t OtherExtent, typename>
inline constexpr bit::stl::span<T,Extent>::span( span<U,OtherExtent>&& other )
  : m_storage(other.data(), bit::stl::detail::span_extent_type<OtherExtent>(other.size()))
{

}

template<typename T, std::ptrdiff_t Extent>
template<typename U>
inline constexpr bit::stl::span<T,Extent>::span( U* ptr, size_type count )
  noexcept
  : m_storage(ptr, count)
{

}

template<typename T, std::ptrdiff_t Extent>
template<typename U, std::size_t N>
inline constexpr bit::stl::span<T,Extent>::span( U (&array)[N] )
  noexcept
  : m_storage( &array[0], bit::stl::detail::span_extent_type<N>() )
{
  static_assert( std::is_convertible<U*,T*>::value, "Type U being assigned is not convertible to T" );
}

template<typename T, std::ptrdiff_t Extent>
template<typename Container, typename>
inline constexpr bit::stl::span<T,Extent>::span( Container&& container )
  noexcept
  : m_storage( container.data(), static_cast<size_type>(container.size()) )
{

}

//----------------------------------------------------------------------------
// Capacity
//----------------------------------------------------------------------------

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::size_type
  bit::stl::span<T,Extent>::length()
  const noexcept
{
  return size();
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::size_type
  bit::stl::span<T,Extent>::size()
  const noexcept
{
  return m_storage.size();
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::size_type
  bit::stl::span<T,Extent>::length_bytes()
  const noexcept
{
  return size_bytes();
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::size_type
  bit::stl::span<T,Extent>::size_bytes()
  const noexcept
{
  return size() * sizeof(T);
}


template<typename T, std::ptrdiff_t Extent>
inline constexpr bool bit::stl::span<T,Extent>::empty()
  const noexcept
{
  return m_storage.size() == 0;
}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::pointer
  bit::stl::span<T,Extent>::data()
  noexcept
{
  return m_storage.data();
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::const_pointer
  bit::stl::span<T,Extent>::data()
  const noexcept
{
  return m_storage.data();
}

//----------------------------------------------------------------------------

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::reference
  bit::stl::span<T,Extent>::operator[] ( index_type pos )
  noexcept
{
  return m_storage.data()[pos];
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::const_reference
  bit::stl::span<T,Extent>::operator[] ( index_type pos )
  const noexcept
{
  return m_storage.data()[pos];
}

//----------------------------------------------------------------------------

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::reference
  bit::stl::span<T,Extent>::at( index_type pos )
{
  BIT_ASSERT_OR_THROW(std::out_of_range, pos >= 0, "span::at: position out of range");
  BIT_ASSERT_OR_THROW(std::out_of_range, static_cast<size_type>(pos) < size(), "span::at: position out of range");

  return *(data() + pos);
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::const_reference
  bit::stl::span<T,Extent>::at( index_type pos )
  const
{
  BIT_ASSERT_OR_THROW(std::out_of_range, pos >= 0, "span::at: position out of range");
  BIT_ASSERT_OR_THROW(std::out_of_range, static_cast<size_type>(pos) < size(), "span::at: position out of range");

  return *(data() + pos);
}

//----------------------------------------------------------------------------

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::reference
  bit::stl::span<T,Extent>::front()
  noexcept
{
  return *data();
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::const_reference
  bit::stl::span<T,Extent>::front()
  const noexcept
{
  return *data();
}

//----------------------------------------------------------------------------

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::reference
  bit::stl::span<T,Extent>::back()
  noexcept
{
  return *(data() + (size() - 1));
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::const_reference
  bit::stl::span<T,Extent>::back()
  const noexcept
{
  return *(data() + (size() - 1));
}

//----------------------------------------------------------------------------
// Operations
//----------------------------------------------------------------------------

template<typename T, std::ptrdiff_t Extent>
inline typename bit::stl::span<T,Extent>::size_type
  bit::stl::span<T,Extent>::copy( value_type* dest,
                                  size_type count,
                                  size_type pos )
  const
{
  BIT_ASSERT_OR_THROW(std::out_of_range, pos < size(), "span::copy: Index out of range");

  const size_type rcount = std::min(size() - pos,count+1);
  std::copy( data() + pos, data() + pos + rcount, dest);
  return rcount;
}


template<typename T, std::ptrdiff_t Extent>
inline constexpr bit::stl::span<T,bit::stl::dynamic_extent>
  bit::stl::span<T,Extent>::subspan( size_type offset, size_type count )
  const
{
  BIT_ASSERT_OR_THROW(std::out_of_range, offset < size(), "span::at: Index out of range");

  const size_type max_length = offset > size() ? 0 : size() - offset;
  const size_type length     = count == dynamic_extent ? max_length : std::min(count,max_length);

  return span<T,dynamic_extent>( m_storage.data() + offset, length );
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr bit::stl::span<T,bit::stl::dynamic_extent>
  bit::stl::span<T,Extent>::first( size_type n )
  const
{
  return subspan( 0, n );
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr bit::stl::span<T,bit::stl::dynamic_extent>
  bit::stl::span<T,Extent>::last( size_type n )
  const
{
  return (n > size())
         ? *this
         : subspan( size() - n );
}

//----------------------------------------------------------------------------
// Iterators
//----------------------------------------------------------------------------

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::iterator
  bit::stl::span<T,Extent>::begin()
  const noexcept
{
  return iterator( data() ? data() : nullptr );
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::iterator
  bit::stl::span<T,Extent>::end()
  const noexcept
{
  return iterator( data() ? (data() + size()) : nullptr );
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::const_iterator
  bit::stl::span<T,Extent>::cbegin()
  const noexcept
{
  return const_iterator( data() ? data() : nullptr );
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::const_iterator
  bit::stl::span<T,Extent>::cend()
  const noexcept
{
  return const_iterator( data() ? data() + size() : nullptr );
}

//----------------------------------------------------------------------------

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::reverse_iterator
  bit::stl::span<T,Extent>::rbegin()
  const noexcept
{
  return reverse_iterator( m_storage.data() ? (m_storage.data() + (m_storage.size() - 1)) : nullptr );
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::reverse_iterator
  bit::stl::span<T,Extent>::rend()
  const noexcept
{
  return reverse_iterator( m_storage.data() ? (m_storage.data() - 1) : nullptr );
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::const_reverse_iterator
  bit::stl::span<T,Extent>::crbegin()
  const noexcept
{
  return const_reverse_iteartor( m_storage.data() ? (m_storage.data() + (m_storage.size() - 1)) : nullptr );
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::span<T,Extent>::const_reverse_iterator
  bit::stl::span<T,Extent>::crend()
  const noexcept
{
  return const_reverse_iterator( m_storage.data() ? (m_storage.data() - 1) : nullptr );
}

//----------------------------------------------------------------------------
// Comparison Operators
//----------------------------------------------------------------------------

template<typename T, std::ptrdiff_t Extent>
inline constexpr bool
  bit::stl::operator == ( const span<T,Extent>& lhs,
                          const span<T,Extent>& rhs )
  noexcept
{
  return std::equal(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr bool
  bit::stl::operator != ( const span<T,Extent>& lhs,
                          const span<T,Extent>& rhs )
  noexcept
{
  return !(lhs==rhs);
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr bool
  bit::stl::operator < ( const span<T,Extent>& lhs,
                         const span<T,Extent>& rhs )
  noexcept
{
  return std::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr bool
  bit::stl::operator <= ( const span<T,Extent>& lhs,
                          const span<T,Extent>& rhs )
  noexcept
{
  return !(lhs > rhs);
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr bool
  bit::stl::operator > ( const span<T,Extent>& lhs,
                         const span<T,Extent>& rhs )
  noexcept
{
  return (rhs < lhs);
}

template<typename T, std::ptrdiff_t Extent>
inline constexpr bool
  bit::stl::operator >= ( const span<T,Extent>& lhs,
                          const span<T,Extent>& rhs )
  noexcept
{
  return !(lhs < rhs);
}

//============================================================================
// Free Functions
//============================================================================

//----------------------------------------------------------------------------
// to_bytes
//----------------------------------------------------------------------------

template<typename T, std::ptrdiff_t Extent>
inline constexpr bit::stl::span<bit::stl::byte>
  bit::stl::casts::to_bytes( span<T,Extent> span )
{
  return bit::stl::span<byte>(
    static_cast<byte*>(static_cast<void*>(span.data())),
    span.size_bytes()
  );
}

template<typename T>
inline constexpr bit::stl::span<bit::stl::byte>
  bit::stl::casts::to_bytes( span<T> span )
{
  return bit::stl::span<byte>(
    static_cast<byte*>(static_cast<void*>(span.data())),
    span.size_bytes()
  );
}

//----------------------------------------------------------------------------

template<typename T, std::ptrdiff_t Extent>
constexpr bit::stl::span<const bit::stl::byte>
  bit::stl::casts::to_bytes( span<const T,Extent> span )
{
  return bit::stl::span<const byte>(
    static_cast<const byte*>(static_cast<const void*>(span.data())),
    span.size_bytes()
  );
}

template<typename T>
constexpr bit::stl::span<const bit::stl::byte>
  bit::stl::casts::to_bytes( span<const T> span )
{
  return bit::stl::span<const byte>(
    static_cast<const byte*>(static_cast<const void*>(span.data())),
    span.size_bytes()
  );
}

//----------------------------------------------------------------------------
// from_bytes
//----------------------------------------------------------------------------

template<typename T, std::ptrdiff_t Extent>
constexpr bit::stl::span<T>
  bit::stl::casts::from_bytes( span<byte,Extent> span )
{
  BIT_ASSERT( span.size_bytes() % sizeof(T) == 0, "from_bytes: Span does not contain enough bytes to convert to T");

  return bit::stl::span<T>(
    static_cast<T*>(static_cast<void*>(span.data())),
    span.size_bytes() / sizeof(T)
  );
}

template<typename T>
constexpr bit::stl::span<T>
  bit::stl::casts::from_bytes( span<byte> span )
{
  BIT_ASSERT( span.size_bytes() % sizeof(T) == 0, "from_bytes: Span does not contain enough bytes to convert to T");

  return bit::stl::span<T>(
    static_cast<T*>(static_cast<void*>(span.data())),
    span.size_bytes() / sizeof(T)
  );
}

//----------------------------------------------------------------------------

template<typename T, std::ptrdiff_t Extent>
constexpr bit::stl::span<const T>
  bit::stl::casts::from_bytes( span<const byte,Extent> span )
{
  BIT_ASSERT( span.size_bytes() % sizeof(T) == 0, "from_bytes: Span does not contain enough bytes to convert to T");

  return bit::stl::span<const T>(
    static_cast<const T*>(static_cast<const void*>(span.data())),
    span.size_bytes() / sizeof(const T)
  );
}

template<typename T>
constexpr bit::stl::span<const T>
  bit::stl::casts::from_bytes( span<const byte> span )
{
  BIT_ASSERT( span.size_bytes() % sizeof(T) == 0, "from_bytes: Span does not contain enough bytes to convert to T");

  return bit::stl::span<const T>(
    static_cast<const T*>(static_cast<const void*>(span.data())),
    span.size_bytes() / sizeof(const T)
  );
}

#endif /* BIT_STL_DETAIL_SPAN_INL */
