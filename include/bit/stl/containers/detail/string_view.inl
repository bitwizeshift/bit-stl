#ifndef BIT_STL_CONTAINERS_DETAIL_STRING_VIEW_INL
#define BIT_STL_CONTAINERS_DETAIL_STRING_VIEW_INL

//============================================================================
// basic_string_view
//============================================================================

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr bit::stl::basic_string_view<CharT,Traits>::
  basic_string_view()
  noexcept
  : m_str(nullptr),
    m_size(0)
{

}

template<typename CharT, typename Traits>
template<typename Allocator>
inline constexpr bit::stl::basic_string_view<CharT,Traits>::
  basic_string_view( const std::basic_string<CharT,Traits,Allocator>& str )
  noexcept
  : m_str(str.c_str()),
    m_size(str.size())
{

}

template<typename CharT, typename Traits>
inline constexpr bit::stl::basic_string_view<CharT,Traits>::
  basic_string_view( const value_type* str )
  noexcept
  : m_str(str),
    m_size(traits_type::length(str))
{

}

template<typename CharT, typename Traits>
inline constexpr bit::stl::basic_string_view<CharT,Traits>::
  basic_string_view( const value_type* str, size_type count )
  noexcept
  : m_str(str),
    m_size(count)
{

}

//----------------------------------------------------------------------------
// Capacity
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::size()
  const noexcept
{
  return m_size;
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::length()
  const noexcept
{
  return size();
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::max_size()
  const noexcept
{
  return npos - 1;
}

template<typename CharT, typename Traits>
inline constexpr bool bit::stl::basic_string_view<CharT,Traits>::empty()
  const noexcept
{
  return m_size == 0;
}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr const typename bit::stl::basic_string_view<CharT,Traits>::value_type*
  bit::stl::basic_string_view<CharT,Traits>::data()
  const noexcept
{
  return m_str;
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::const_reference
  bit::stl::basic_string_view<CharT,Traits>::operator[]( size_t pos )
  const noexcept
{
  return m_str[pos];
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::const_reference
  bit::stl::basic_string_view<CharT,Traits>::at( size_t pos )
  const
{
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  if( pos >= m_size ) throw std::out_of_range("basic_string_view::at: index out of range");
#endif

  return m_str[pos];
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::const_reference
  bit::stl::basic_string_view<CharT,Traits>::front( )
  const noexcept
{
  return *m_str;
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::const_reference
  bit::stl::basic_string_view<CharT,Traits>::back( )
  const noexcept
{
  return m_str[m_size-1];
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr void
  bit::stl::basic_string_view<CharT,Traits>::remove_prefix( size_type n )
  noexcept
{
  m_str += n, m_size -= n;
}

template<typename CharT, typename Traits>
inline constexpr void
  bit::stl::basic_string_view<CharT,Traits>::remove_suffix( size_type n )
  noexcept
{
  m_size -= n;
}

template<typename CharT, typename Traits>
inline constexpr void
  bit::stl::basic_string_view<CharT,Traits>::swap( basic_string_view& v )
  noexcept
{
  using std::swap;
  swap(m_size,v.m_size);
  swap(m_str,v.m_str);
}

//----------------------------------------------------------------------------
// Conversions
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
template<class Allocator>
inline bit::stl::basic_string_view<CharT,Traits>::operator
  std::basic_string<CharT, Traits, Allocator>()
  const
{
  return std::basic_string<CharT,Traits,Allocator>( m_str, m_size );
}

//----------------------------------------------------------------------------
// String Operations
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::copy( value_type* dest,
                                                   size_type count,
                                                   size_type pos )
  const
{
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  if( pos >= m_size ) throw std::out_of_range("basic_string_view::copy: index out of range");
#endif

  const size_type rcount = std::min(m_size - pos,count+1);
  std::copy( m_str + pos, m_str + pos + rcount, dest);
  return rcount;
}

template<typename CharT, typename Traits>
inline constexpr bit::stl::basic_string_view<CharT,Traits>
  bit::stl::basic_string_view<CharT,Traits>::substr( size_type pos,
                                                     size_type len )
  const
{
#if BIT_COMPILER_EXCEPTIONS_ENABLED
  if( pos >= m_size ) throw std::out_of_range("basic_string_view::substr: index out of range");
#endif

  const size_type max_length = pos > m_size ? 0 : m_size - pos;

  return basic_string_view<CharT,Traits>( m_str + pos, len > max_length ? max_length : len );
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr int
  bit::stl::basic_string_view<CharT,Traits>::compare( basic_string_view v )
  const noexcept
{
  const size_type rlen = std::min(m_size,v.m_size);
  const int compare    = Traits::compare(m_str,v.m_str,rlen);

  return (compare ? compare : (m_size < v.m_size ? -1 : (m_size > v.m_size ? 1 : 0)));
}

template<typename CharT, typename Traits>
inline constexpr int
  bit::stl::basic_string_view<CharT,Traits>::compare( size_type pos,
                                                      size_type count,
                                                      basic_string_view v )
  const
{
  return substr(pos,count).compare(v);
}

template<typename CharT, typename Traits>
inline constexpr int
  bit::stl::basic_string_view<CharT,Traits>::compare( size_type pos1,
                                                      size_type count1,
                                                      basic_string_view v,
                                                      size_type pos2,
                                                      size_type count2 )
  const
{
  return substr(pos1,count1).compare( v.substr(pos2,count2) );
}

template<typename CharT, typename Traits>
inline constexpr int
  bit::stl::basic_string_view<CharT,Traits>::compare( const value_type* s )
  const
{
  return compare(basic_string_view<CharT,Traits>(s));
}

template<typename CharT, typename Traits>
inline constexpr int
  bit::stl::basic_string_view<CharT,Traits>::compare( size_type pos,
                                                      size_type count,
                                                      const value_type* s )
  const
{
  return substr(pos, count).compare( basic_string_view<CharT,Traits>(s) );
}

template<typename CharT, typename Traits>
inline constexpr int
  bit::stl::basic_string_view<CharT,Traits>::compare( size_type pos,
                                                      size_type count1,
                                                      const value_type* s,
                                                      size_type count2 )
  const
{
  return substr(pos, count1).compare( basic_string_view<CharT,Traits>(s, count2) );
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find( basic_string_view v,
                                                   size_type pos )
  const
{
  if(v.size()==0 || size()==0) {
    return npos;
  }

  const size_type max_index = m_size - v.size() + 1;

  for( size_type i = pos; i < max_index; ++i ) {
    size_type j = v.size();
    for( ; j > 0; --j ) {
      if( v[j-1] != m_str[i+j-1] ) {
        break;
      }
    }
    if(j==0) return i;
  }
  return npos;
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find( value_type c,
                                                   size_type pos )
  const
{
  return find(basic_string_view<CharT,Traits>(&c, 1), pos);
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find( const value_type* s,
                                                   size_type pos,
                                                   size_type count )
  const
{
  return find(basic_string_view<CharT,Traits>(s, count), pos);
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find( const value_type* s,
                                                   size_type pos )
  const
{
  return find(basic_string_view<CharT,Traits>(s), pos);
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::rfind( basic_string_view v,
                                                    size_type pos )
  const
{
  if(v.size()==0 || size()==0) {
    return npos;
  }

  const size_type max_index = m_size - v.size()+1;

  for( size_type i = std::min(max_index,pos); i > 0; --i ) {
    size_type j = 0;
    for( ; j < v.size(); ++j ) {
      if( v[j] != m_str[i+j-1] ) {
        break;
      }
    }
    if(j==v.size()) return i-1;
  }
  return npos;
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::rfind( value_type c,
                                                    size_type pos )
  const
{
  return rfind(basic_string_view<CharT,Traits>(&c, 1), pos);
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::rfind( const value_type* s,
                                                    size_type pos,
                                                    size_type count )
  const
{
  return rfind(basic_string_view<CharT,Traits>(s, count), pos);
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::rfind( const value_type* s,
                                                    size_type pos )
  const
{
  return rfind(basic_string_view<CharT,Traits>(s), pos);
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find_first_of( basic_string_view v,
                                                            size_type pos )
  const
{
  if(v.size()==0 || size()==0)
  {
    return npos;
  }

  for( size_type i = pos; i < m_size; ++i ) {
    for( size_type j = 0; j < v.size(); ++j ) {
      if( v[j] == m_str[i] ) {
        return i;
      }
    }
  }
  return npos;
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find_first_of( value_type c,
                                                            size_type pos )
  const
{
  return find_first_of(basic_string_view<CharT,Traits>(&c, 1), pos);
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find_first_of( const value_type* s,
                                                            size_type pos,
                                                            size_type count )
  const
{
  return find_first_of(basic_string_view<CharT,Traits>(s, count), pos);
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find_first_of( const value_type* s,
                                                            size_type pos )
  const
{
  return find_first_of( basic_string_view<CharT,Traits>(s), pos );
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find_last_of( basic_string_view v,
                                                           size_type pos )
  const
{
  if(v.size()==0 || size()==0) {
    return npos;
  }

  for( size_type i = std::min(m_size,pos); i > 0; --i ) {
    for( size_type j = 0; j < v.size(); ++j ) {
      if( v[j] == m_str[i-1] ) {
        return i-1;
      }
    }
  }
  return npos;
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find_last_of( value_type c,
                                                           size_type pos )
  const
{
  return find_last_of( basic_string_view<CharT,Traits>(&c, 1), pos );
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find_last_of( const value_type* s,
                                                           size_type pos,
                                                           size_type count )
  const
{
  return find_last_of( basic_string_view<CharT,Traits>(s, count), pos );
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find_last_of( const value_type* s,
                                                           size_type pos )
  const
{
  return find_last_of( basic_string_view<CharT,Traits>(s), pos );
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find_first_not_of( basic_string_view v,
                                                                size_type pos )
  const
{
  if(v.size()==0 || size()==0) {
    return npos;
  }

  for( size_type i = pos; i < m_size; ++i ) {
    size_type j = 0;
    for( ; j < v.size(); ++j ) {
      if( v[j] == m_str[i] ) {
        break;
      }
    }
    if( j == v.size() ) {
      return i;
    }
  }
  return npos;
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find_first_not_of( value_type c,
                                                                size_type pos )
  const
{
  return find_first_not_of( basic_string_view<CharT,Traits>(&c, 1), pos );
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find_first_not_of( const value_type* s,
                                                                size_type pos,
                                                                size_type count )
  const
{
  return find_first_not_of( basic_string_view<CharT,Traits>(s, count), pos );
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find_first_not_of( const value_type* s,
                                                                size_type pos )
  const
{
  return find_first_not_of( basic_string_view<CharT,Traits>(s), pos );
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find_last_not_of( basic_string_view v,
                                                               size_type pos )
  const
{
  if(v.size()==0 || size()==0) {
    return npos;
  }

  for( size_type i = std::min(m_size,pos); i > 0; --i ) {
    size_type j = 0;
    for( ; j < v.size(); ++j ) {
      if( v[j] == m_str[i-1] ) {
        break;
      }
    }
    if( j == v.size() ) {
      return i-1;
    }
  }
  return npos;
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find_last_not_of( value_type c,
                                                               size_type pos )
  const
{
  return find_last_not_of( basic_string_view<CharT,Traits>(&c, 1), pos );
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find_last_not_of( const value_type* s,
                                                               size_type pos,
                                                               size_type count )
  const
{
  return find_last_not_of( basic_string_view<CharT,Traits>(s, count), pos );
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::size_type
  bit::stl::basic_string_view<CharT,Traits>::find_last_not_of( const value_type* s,
                                                               size_type pos )
  const
{
  return find_last_not_of( basic_string_view<CharT,Traits>(s), pos );
}

//----------------------------------------------------------------------------
// Iterator
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::const_iterator
  bit::stl::basic_string_view<CharT,Traits>::begin()
  const noexcept
{
  return const_iterator{m_str};
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::const_iterator
  bit::stl::basic_string_view<CharT,Traits>::cbegin()
  const noexcept
{
  return const_iterator{m_str};
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::const_iterator
  bit::stl::basic_string_view<CharT,Traits>::end()
  const noexcept
{
  return const_iterator{m_str + m_size};
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::const_iterator
  bit::stl::basic_string_view<CharT,Traits>::cend()
  const noexcept
{
  return const_iterator{m_str + m_size};
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::const_reverse_iterator
  bit::stl::basic_string_view<CharT,Traits>::rbegin()
  const noexcept
{
  return const_reverse_iterator{m_str - 1};
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::const_reverse_iterator
  bit::stl::basic_string_view<CharT,Traits>::crbegin()
  const noexcept
{
  return const_reverse_iterator{m_str - 1};
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::const_reverse_iterator
  bit::stl::basic_string_view<CharT,Traits>::rend()
  const noexcept
{
  return const_reverse_iterator{m_str + (m_size - 1)};
}

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_string_view<CharT,Traits>::const_reverse_iterator
  bit::stl::basic_string_view<CharT,Traits>::crend()
  const noexcept
{
  return const_reverse_iterator{m_str + (m_size - 1)};
}

//============================================================================
// basic_zstring_view
//============================================================================

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
constexpr bit::stl::basic_zstring_view<CharT,Traits>::
  basic_zstring_view( const value_type* str )
  noexcept
  : basic_string_view<CharT,Traits>(str,Traits::length(str))
{

}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
constexpr const typename bit::stl::basic_zstring_view<CharT,Traits>::value_type*
  bit::stl::basic_zstring_view<CharT,Traits>::c_str()
  const noexcept
{
  return basic_zstring_view<CharT,Traits>::data();
}

//============================================================================
// Free Functions
//============================================================================

//----------------------------------------------------------------------------
// Hash Functions
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr bit::stl::hash_t
  bit::stl::hash_value( const basic_string_view<CharT,Traits>& str )
  noexcept
{
  return hash_string_segment( str.data(), str.size() );
}

//----------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
std::basic_ostream<CharT,Traits>&
  bit::stl::operator << ( std::basic_ostream<CharT,Traits>& o,
                          const basic_string_view<CharT,Traits>& str )
{
  o.write(str.data(),str.size());
  return o;
}

template<typename CharT, typename Traits>
inline void
  bit::stl::swap( basic_string_view<CharT,Traits>& lhs,
                  basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//----------------------------------------------------------------------------
// Literals
//----------------------------------------------------------------------------

inline constexpr bit::stl::string_view
  bit::stl::literals::string_view_literals::operator "" _sv( const char* str,
                                                             std::size_t len )
  noexcept
{
  return {str,len};
}

inline constexpr bit::stl::wstring_view
  bit::stl::literals::string_view_literals::operator "" _sv( const wchar_t* str,
                                                             std::size_t len )
  noexcept
{
  return {str,len};
}

inline constexpr bit::stl::u16string_view
  bit::stl::literals::string_view_literals::operator "" _sv( const char16_t* str,
                                                             std::size_t len )
  noexcept
{
  return {str,len};
}

inline constexpr bit::stl::u32string_view
  bit::stl::literals::string_view_literals::operator "" _sv( const char32_t* str,
                                                             std::size_t len )
  noexcept
{
  return {str,len};
}

//----------------------------------------------------------------------------
// Comparison Functions
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator == ( const basic_string_view<CharT,Traits>& lhs,
                          const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return lhs.compare(rhs) == 0;
}

template<typename CharT, typename Traits, std::size_t N>
inline bool
  bit::stl::operator == ( const basic_string_view<CharT,Traits>& lhs,
                          CharT (&rhs)[N] )
  noexcept
{
  return lhs == basic_string_view<CharT,Traits>(rhs);
}

template<typename CharT, typename Traits, std::size_t N>
inline bool
  bit::stl::operator == ( CharT (&lhs)[N],
                          const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) == rhs;
}

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator == ( basic_string_view<CharT,Traits> lhs,
                          const CharT* rhs )
  noexcept
{
  return lhs == basic_string_view<CharT,Traits>(rhs);
}

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator == ( const CharT* lhs,
                          const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) == rhs;
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator == ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                          const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) == rhs;
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator == ( const basic_string_view<CharT,Traits>& lhs,
                          const std::basic_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return lhs == basic_string_view<CharT,Traits>(rhs);
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator != ( const basic_string_view<CharT,Traits>& lhs,
                          const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return lhs.compare(rhs) != 0;
}

template<typename CharT, typename Traits, std::size_t N>
inline bool
  bit::stl::operator != ( const basic_string_view<CharT,Traits>& lhs,
                          CharT (&rhs)[N] )
  noexcept
{
  return lhs != basic_string_view<CharT,Traits>(rhs);
}

template<typename CharT, typename Traits, std::size_t N>
inline bool
  bit::stl::operator != ( CharT (&lhs)[N],
                          const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) != rhs;
}

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator != ( const basic_string_view<CharT,Traits>& lhs,
                          const CharT* rhs )
  noexcept
{
  return lhs != basic_string_view<CharT,Traits>(rhs);
}

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator != ( const CharT* lhs,
                          const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) != rhs;
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator != ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                          const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) != rhs;
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator != ( const basic_string_view<CharT,Traits>& lhs,
                          const std::basic_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return lhs != basic_string_view<CharT,Traits>(rhs);
}
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator < ( const basic_string_view<CharT,Traits>& lhs,
                         const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return lhs.compare(rhs) < 0;
}

template<typename CharT, typename Traits, std::size_t N>
inline bool
  bit::stl::operator < ( const basic_string_view<CharT,Traits>& lhs,
                         CharT (&rhs)[N] )
  noexcept
{
  return lhs < basic_string_view<CharT,Traits>(rhs);
}

template<typename CharT, typename Traits, std::size_t N>
inline bool
  bit::stl::operator < ( CharT (&lhs)[N],
                         const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) < rhs;
}

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator < ( const basic_string_view<CharT,Traits>& lhs,
                         const CharT* rhs )
  noexcept
{
  return lhs < basic_string_view<CharT,Traits>(rhs);
}

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator < ( const CharT* lhs,
                         const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) < rhs;
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator < ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                         const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) < rhs;
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator < ( const basic_string_view<CharT,Traits>& lhs,
                         const std::basic_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return lhs < basic_string_view<CharT,Traits>(rhs);
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator > ( const basic_string_view<CharT,Traits>& lhs,
                         const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return lhs.compare(rhs) > 0;
}

template<typename CharT, typename Traits, std::size_t N>
inline bool
  bit::stl::operator > ( const basic_string_view<CharT,Traits>& lhs,
                         CharT (&rhs)[N] )
  noexcept
{
  return lhs > basic_string_view<CharT,Traits>(rhs);
}

template<typename CharT, typename Traits, std::size_t N>
inline bool
  bit::stl::operator > ( CharT (&lhs)[N],
                         const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) > rhs;
}

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator > ( const basic_string_view<CharT,Traits>& lhs,
                         const CharT* rhs )
  noexcept
{
  return lhs > basic_string_view<CharT,Traits>(rhs);
}

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator > ( const CharT* lhs,
                         const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) > rhs;
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator > ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                         const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) > rhs;
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator > ( const basic_string_view<CharT,Traits>& lhs,
                         const std::basic_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return lhs > basic_string_view<CharT,Traits>(rhs);
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator <= ( const basic_string_view<CharT,Traits>& lhs,
                          const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return lhs.compare(rhs) <= 0;
}

template<typename CharT, typename Traits, std::size_t N>
inline bool
  bit::stl::operator <= ( const basic_string_view<CharT,Traits>& lhs,
                          CharT (&rhs)[N] )
  noexcept
{
  return lhs <= basic_string_view<CharT,Traits>(rhs);
}

template<typename CharT, typename Traits, std::size_t N>
inline bool
  bit::stl::operator <= ( CharT (&lhs)[N],
                          const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) <= rhs;
}

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator <= ( const basic_string_view<CharT,Traits>& lhs,
                          const CharT* rhs )
  noexcept
{
  return lhs <= basic_string_view<CharT,Traits>(rhs);
}

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator <= ( const CharT* lhs,
                          const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) <= rhs;
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator <= ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                          const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) <= rhs;
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator <= ( const basic_string_view<CharT,Traits>& lhs,
                          const std::basic_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return lhs <= basic_string_view<CharT,Traits>(rhs);
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator >= ( const basic_string_view<CharT,Traits>& lhs,
                          const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return lhs.compare(rhs) >= 0;
}

template<typename CharT, typename Traits, std::size_t N>
inline bool
  bit::stl::operator >= ( const basic_string_view<CharT,Traits>& lhs,
                          CharT (&rhs)[N] )
  noexcept
{
  return lhs >= basic_string_view<CharT,Traits>(rhs);
}

template<typename CharT, typename Traits, std::size_t N>
inline bool
  bit::stl::operator >= ( CharT (&lhs)[N],
                          const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) >= rhs;
}

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator >= ( const basic_string_view<CharT,Traits>& lhs,
                          const CharT* rhs )
  noexcept
{
  return lhs >= basic_string_view<CharT,Traits>(rhs);
}

template<typename CharT, typename Traits>
inline bool
  bit::stl::operator >= ( const CharT* lhs,
                          const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) >= rhs;
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator >= ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                          const basic_string_view<CharT,Traits>& rhs )
  noexcept
{
  return basic_string_view<CharT,Traits>(lhs) >= rhs;
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator >= ( const basic_string_view<CharT,Traits>& lhs,
                          const std::basic_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return lhs >= basic_string_view<CharT,Traits>(rhs);
}

//----------------------------------------------------------------------------
// String Concatenation
//----------------------------------------------------------------------------

template<typename CharT, typename Traits, typename Allocator>
inline std::basic_string<CharT,Traits,Allocator>
  bit::stl::operator + ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                         const basic_string_view<CharT,Traits>& rhs )
{
  return std::basic_string<CharT,Traits>(lhs).append(rhs.data(),rhs.size());
}

template<typename CharT, typename Traits, typename Allocator>
inline std::basic_string<CharT,Traits,Allocator>
  bit::stl::operator + ( const basic_string_view<CharT,Traits>& lhs,
                         const std::basic_string<CharT,Traits,Allocator>& rhs )
{
  return std::basic_string<CharT,Traits>(lhs).append(rhs.data(),rhs.size());
}

template<typename CharT, typename Traits, typename Allocator>
inline std::basic_string<CharT,Traits,Allocator>&
  bit::stl::operator += ( std::basic_string<CharT,Traits,Allocator>& lhs,
                          const basic_string_view<CharT,Traits>& rhs )
{
  return lhs.append(rhs.data(),rhs.size());
}

#endif /* BIT_STL_CONTAINERS_DETAIL_STRING_VIEW_INL */
