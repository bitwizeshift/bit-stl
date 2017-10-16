#ifndef BIT_STL_CONTAINERS_DETAIL_STRING_SPAN_INL
#define BIT_STL_CONTAINERS_DETAIL_STRING_SPAN_INL

//============================================================================
// basic_string_span
//============================================================================

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr bit::stl::basic_string_span<CharT,Traits,Extent>::
  basic_string_span( std::nullptr_t )
  noexcept
  : basic_string_span()
{

}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr bit::stl::basic_string_span<CharT,Traits,Extent>::
  basic_string_span( pointer ptr, size_type length )
  noexcept
  : m_span( ptr, length )
{

}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr bit::stl::basic_string_span<CharT,Traits,Extent>::
  basic_string_span( pointer first, pointer last )
  noexcept
  : m_span( first, last - first )
{

}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
template<std::size_t N>
inline constexpr bit::stl::basic_string_span<CharT,Traits,Extent>::
  basic_string_span( value_type (&arr)[N] )
  noexcept
  : m_span( arr, traits_type::length(arr) )
{

}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
template<typename Container, typename>
inline constexpr bit::stl::basic_string_span<CharT,Traits,Extent>::
  basic_string_span( Container& container )
  : m_span( container )
{

}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
template<typename Container, typename>
inline constexpr bit::stl::basic_string_span<CharT,Traits,Extent>::
  basic_string_span( const Container& container )
  : m_span( container )
{

}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
template<typename OtherTraits, typename Allocator>
inline constexpr bit::stl::basic_string_span<CharT,Traits,Extent>::
  basic_string_span( const std::basic_string<value_type, OtherTraits, Allocator>& str )
  noexcept
  : m_span( &str[0], str.size() )
{

}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
template<typename OtherCharT, std::ptrdiff_t OtherExtent, typename>
inline constexpr bit::stl::basic_string_span<CharT,Traits,Extent>::
  basic_string_span( basic_string_span<OtherCharT,Traits,OtherExtent> span )
  noexcept
  : m_span( span.data(), span.size() )
{

}

//----------------------------------------------------------------------------
// Capacity
//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::size_type
  bit::stl::basic_string_span<CharT,Traits,Extent>::length()
  const noexcept
{
  return m_span.length();
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::size_type
  bit::stl::basic_string_span<CharT,Traits,Extent>::size()
  const noexcept
{
  return m_span.size();
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::size_type
  bit::stl::basic_string_span<CharT,Traits,Extent>::length_bytes()
  const noexcept
{
  return m_span.length_bytes();
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::size_type
  bit::stl::basic_string_span<CharT,Traits,Extent>::size_bytes()
  const noexcept
{
  return m_span.size_bytes();
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr bool
  bit::stl::basic_string_span<CharT,Traits,Extent>::empty()
  const noexcept
{
  return m_span.empty();
}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::pointer
  bit::stl::basic_string_span<CharT,Traits,Extent>::data()
  noexcept
{
  return m_span.data();
}

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::const_pointer
  bit::stl::basic_string_span<CharT,Traits,Extent>::data()
  const noexcept
{
  return m_span.data();
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::reference
  bit::stl::basic_string_span<CharT,Traits,Extent>::operator[]( index_type pos )
  noexcept
{
  return m_span[pos];
}

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::const_reference
  bit::stl::basic_string_span<CharT,Traits,Extent>::operator[]( index_type pos )
  const noexcept
{
  return m_span[pos];
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::reference
  bit::stl::basic_string_span<CharT,Traits,Extent>::at( index_type pos )
{
  return m_span.at(pos);
}

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::const_reference
  bit::stl::basic_string_span<CharT,Traits,Extent>::at( index_type pos )
  const
{
  return m_span.at(pos);
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::reference
  bit::stl::basic_string_span<CharT,Traits,Extent>::front()
  noexcept
{
  return m_span.front();
}

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::const_reference
  bit::stl::basic_string_span<CharT,Traits,Extent>::front()
  const noexcept
{
  return m_span.front();
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::reference
  bit::stl::basic_string_span<CharT,Traits,Extent>::back()
  noexcept
{
  return m_span.back();
}

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::const_reference
  bit::stl::basic_string_span<CharT,Traits,Extent>::back()
  const noexcept
{
  return m_span.back();
}

//----------------------------------------------------------------------------
// Operations
//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr bit::stl::basic_string_span<CharT,Traits,bit::stl::dynamic_extent>
  bit::stl::basic_string_span<CharT,Traits,Extent>::substr( size_type offset,
                                                            size_type count )
  const
{
  return m_span.subspan( offset, count );
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
constexpr bit::stl::basic_string_span<CharT,Traits,bit::stl::dynamic_extent>
  bit::stl::basic_string_span<CharT,Traits,Extent>::first( size_type n )
  const
{
  return m_span.first( n );
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
constexpr bit::stl::basic_string_span<CharT,Traits,bit::stl::dynamic_extent>
  bit::stl::basic_string_span<CharT,Traits,Extent>::last( size_type n )
  const
{
  return m_span.last( n );
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
constexpr bit::stl::basic_string_span<CharT,Traits,bit::stl::dynamic_extent>
  bit::stl::basic_string_span<CharT,Traits,Extent>::remove_prefix( size_type n )
  const
{
  return m_span.last( size() - n );
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
constexpr bit::stl::basic_string_span<CharT,Traits,bit::stl::dynamic_extent>
  bit::stl::basic_string_span<CharT,Traits,Extent>::remove_suffix( size_type n )
  const
{
  return m_span.first( size() - n );
}

//----------------------------------------------------------------------------
// Iterators
//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::iterator
  bit::stl::basic_string_span<CharT,Traits,Extent>::begin()
  const noexcept
{
  return iterator( m_span.data() ? m_span.data() : nullptr );
}

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::iterator
  bit::stl::basic_string_span<CharT,Traits,Extent>::end()
  const noexcept
{
  return iterator( m_span.data() ? (m_span.data() + m_span.size()) : nullptr );
}

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::const_iterator
  bit::stl::basic_string_span<CharT,Traits,Extent>::cbegin()
  const noexcept
{
  return const_iterator( m_span.data() ? m_span.data() : nullptr );
}

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::const_iterator
  bit::stl::basic_string_span<CharT,Traits,Extent>::cend()
  const noexcept
{
  return const_iterator( m_span.data() ? m_span.data() + m_span.size() : nullptr );
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::reverse_iterator
  bit::stl::basic_string_span<CharT,Traits,Extent>::rbegin()
  const noexcept
{
  return reverse_iterator( m_span.data() ? (m_span.data() + (m_span.size() - 1)) : nullptr );
}

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::reverse_iterator
  bit::stl::basic_string_span<CharT,Traits,Extent>::rend()
  const noexcept
{
  return reverse_iterator( m_span.data() ? (m_span.data() - 1) : nullptr );
}

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::const_reverse_iterator
  bit::stl::basic_string_span<CharT,Traits,Extent>::crbegin()
  const noexcept
{
  return const_reverse_iteartor( m_span.data() ? (m_span.data() + (m_span.size() - 1)) : nullptr );
}

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_string_span<CharT,Traits,Extent>::const_reverse_iterator
  bit::stl::basic_string_span<CharT,Traits,Extent>::crend()
  const noexcept
{
  return const_reverse_iterator( m_span.data() ? (m_span.data() - 1) : nullptr );
}

//============================================================================
// basic_zstring_span
//============================================================================

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr bit::stl::basic_zstring_span<CharT,Traits,Extent>::
  basic_zstring_span( value_type* str )
  noexcept
  : basic_string_span<CharT,Traits,Extent>( str )
{

}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

template<typename CharT, typename Traits, std::ptrdiff_t Extent>
inline constexpr typename bit::stl::basic_zstring_span<CharT,Traits,Extent>::const_pointer
  bit::stl::basic_zstring_span<CharT,Traits,Extent>::c_str()
  const noexcept
{
  return this->data();
}

#endif /* BIT_STL_CONTAINERS_DETAIL_STRING_SPAN_INL */
