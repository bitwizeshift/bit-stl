#ifndef BFSTL_DETAIL_STRING_VIEW_INL
#define BFSTL_DETAIL_STRING_VIEW_INL

namespace bit {

  //--------------------------------------------------------------------------
  // Constructor
  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline constexpr basic_string_view<CharT,Traits>::basic_string_view()
    noexcept
    : m_str(nullptr),
      m_size(0)
  {

  }

  template<typename CharT, typename Traits>
  template<typename Allocator>
  inline constexpr basic_string_view<CharT,Traits>::basic_string_view( const std::basic_string<CharT,Traits,Allocator>& str )
    noexcept
    : m_str(str.c_str()),
      m_size(str.size())
  {

  }

  template<typename CharT, typename Traits>
  inline constexpr basic_string_view<CharT,Traits>::basic_string_view( const value_type* str )
    noexcept
    : m_str(str),
      m_size(traits_type::length(str))
  {

  }

  template<typename CharT, typename Traits>
  inline constexpr basic_string_view<CharT,Traits>::basic_string_view( const value_type* str, size_type count )
    noexcept
    : m_str(str),
      m_size(count)
  {

  }

  //--------------------------------------------------------------------------
  // Capacity
  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::size()
    const noexcept
  {
    return m_size;
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::length()
    const noexcept
  {
    return size();
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::max_size()
    const noexcept
  {
    return npos - 1;
  }

  template<typename CharT, typename Traits>
  inline constexpr bool basic_string_view<CharT,Traits>::empty()
    const noexcept
  {
    return m_size == 0;
  }

  //--------------------------------------------------------------------------
  // Element Access
  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline constexpr const typename basic_string_view<CharT,Traits>::value_type*
    basic_string_view<CharT,Traits>::c_str()
    const noexcept
  {
    return m_str;
  }

  template<typename CharT, typename Traits>
  inline constexpr const typename basic_string_view<CharT,Traits>::value_type*
    basic_string_view<CharT,Traits>::data()
    const noexcept
  {
    return m_str;
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::const_reference
    basic_string_view<CharT,Traits>::operator[]( size_t pos )
    const noexcept
  {
    return m_str[pos];
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::const_reference
    basic_string_view<CharT,Traits>::at( size_t pos )
    const
  {
#if BIT_COMPILER_EXCEPTIONS_ENABLED
    return pos < m_size ? m_str[pos] : throw std::out_of_range("Input out of range in basic_string_view::at"), m_str[pos];
#else
    return m_str[pos];
#endif
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::const_reference
    basic_string_view<CharT,Traits>::front( )
    const noexcept
  {
    return *m_str;
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::const_reference
    basic_string_view<CharT,Traits>::back( )
    const noexcept
  {
    return m_str[m_size-1];
  }

  //--------------------------------------------------------------------------
  // Modifiers
  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline void
    basic_string_view<CharT,Traits>::remove_prefix( size_type n )
    noexcept
  {
    m_str += n, m_size -= n;
  }

  template<typename CharT, typename Traits>
  inline void
    basic_string_view<CharT,Traits>::remove_suffix( size_type n )
    noexcept
  {
    m_size -= n;
  }

  template<typename CharT, typename Traits>
  inline void
    basic_string_view<CharT,Traits>::swap( basic_string_view& v )
    noexcept
  {
    using std::swap;
    swap(m_size,v.m_size);
    swap(m_str,v.m_str);
  }

  //--------------------------------------------------------------------------
  // Conversions
  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  template<class Allocator>
  inline constexpr basic_string_view<CharT,Traits>::operator
    std::basic_string<CharT, Traits, Allocator>()
    const
  {
    return std::basic_string<CharT,Traits,Allocator>( m_str, m_size );
  }

  //--------------------------------------------------------------------------
  // String Operations
  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::copy( value_type* dest,
                                           size_type count,
                                           size_type pos )
    const
  {
#if BIT_COMPILER_EXCEPTIONS_ENABLED
    if(pos >= m_size) throw std::out_of_range("Index out of range in basic_string_view::copy");
#endif
    const size_type rcount = std::min(m_size - pos,count+1);
    std::copy( m_str + pos, m_str + pos + rcount, dest);
    return rcount;
  }

  template<typename CharT, typename Traits>
  inline basic_string_view<CharT,Traits>
    basic_string_view<CharT,Traits>::substr( size_type pos,
                                             size_type len )
    const
  {
    const size_type max_length = pos > m_size ? 0 : m_size - pos;

#if BIT_COMPILER_EXCEPTIONS_ENABLED
    return pos < m_size ? basic_string_view<CharT,Traits>( m_str + pos, len > max_length ? max_length : len ) : throw std::out_of_range("Index out of range in basic_string_view::substr");
#else
    return basic_string_view<CharT,Traits>( m_str + pos, len > max_length ? max_length : len );
#endif
  }

  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline int basic_string_view<CharT,Traits>::compare( basic_string_view v )
    const noexcept
  {
    const size_type rlen = std::min(m_size,v.m_size);
    const int compare = Traits::compare(m_str,v.m_str,rlen);

    return (compare ? compare : (m_size < v.m_size ? -1 : (m_size > v.m_size ? 1 : 0)));
  }

  template<typename CharT, typename Traits>
  inline int basic_string_view<CharT,Traits>::compare( size_type pos,
                                                       size_type count,
                                                       basic_string_view v )
    const
  {
    return substr(pos,count).compare(v);
  }

  template<typename CharT, typename Traits>
  inline int basic_string_view<CharT,Traits>::compare( size_type pos1,
                                                       size_type count1,
                                                       basic_string_view v,
                                                       size_type pos2,
                                                       size_type count2 )
    const
  {
    return substr(pos1,count1).compare( v.substr(pos2,count2) );
  }

  template<typename CharT, typename Traits>
  inline int basic_string_view<CharT,Traits>::compare( const value_type* s )
    const
  {
    return compare(basic_string_view<CharT,Traits>(s));
  }

  template<typename CharT, typename Traits>
  inline int basic_string_view<CharT,Traits>::compare( size_type pos,
                                                       size_type count,
                                                       const value_type* s )
    const
  {
    return substr(pos, count).compare( basic_string_view<CharT,Traits>(s) );
  }

  template<typename CharT, typename Traits>
  inline int basic_string_view<CharT,Traits>::compare( size_type pos,
                                                       size_type count1,
                                                       const value_type* s,
                                                       size_type count2 )
    const
  {
    return substr(pos, count1).compare( basic_string_view<CharT,Traits>(s, count2) );
  }

  //--------------------------------------------------------------------------
  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find( basic_string_view v,
                                           size_type pos )
    const
  {
    if(v.size()==0 || size()==0)
    {
      return npos;
    }

    const size_type max_index = m_size - v.size() + 1;

    for( size_type i = pos; i < max_index; ++i )
    {
      size_type j = v.size();
      for( ; j > 0; --j )
      {
        if( v[j-1] != m_str[i+j-1] )
        {
          break;
        }
      }
      if(j==0) return i;
    }
    return npos;
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find( value_type c,
                                           size_type pos )
    const
  {
    return find(basic_string_view<CharT,Traits>(&c, 1), pos);
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find( value_type const* s,
                                           size_type pos,
                                           size_type count )
    const
  {
    return find(basic_string_view<CharT,Traits>(s, count), pos);
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find( value_type const* s,
                                          size_type pos )
    const
  {
    return find(basic_string_view<CharT,Traits>(s), pos);
  }

  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::rfind( basic_string_view v,
                                            size_type pos )
    const
  {
    if(v.size()==0 || size()==0)
    {
      return npos;
    }

    const size_type max_index = m_size - v.size()+1;

    for( size_type i = std::min(max_index,pos); i > 0; --i )
    {
      size_type j = 0;
      for( ; j < v.size(); ++j )
      {
        if( v[j] != m_str[i+j-1] )
        {
          break;
        }
      }
      if(j==v.size()) return i-1;
    }
    return npos;
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::rfind( value_type c,
                                            size_type pos )
    const
  {
    return rfind(basic_string_view<CharT,Traits>(&c, 1), pos);
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::rfind( value_type const* s,
                                            size_type pos,
                                            size_type count )
    const
  {
    return rfind(basic_string_view<CharT,Traits>(s, count), pos);
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::rfind( value_type const* s,
                                            size_type pos )
    const
  {
    return rfind(basic_string_view<CharT,Traits>(s), pos);
  }

  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find_first_of( basic_string_view v,
                                                    size_type pos )
    const
  {
    if(v.size()==0 || size()==0)
    {
      return npos;
    }

    for( size_type i = pos; i < m_size; ++i )
    {
      for( size_type j = 0; j < v.size(); ++j )
      {
        if( v[j] == m_str[i] )
        {
          return i;
        }
      }
    }
    return npos;
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find_first_of( value_type c,
                                                    size_type pos )
    const
  {
    return find_first_of(basic_string_view<CharT,Traits>(&c, 1), pos);
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find_first_of( value_type const* s,
                                                    size_type pos,
                                                    size_type count )
    const
  {
    return find_first_of(basic_string_view<CharT,Traits>(s, count), pos);
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find_first_of( value_type const* s,
                                                    size_type pos )
    const
  {
    return find_first_of( basic_string_view<CharT,Traits>(s), pos );
  }

  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find_last_of( basic_string_view v,
                                                   size_type pos )
    const
  {
    if(v.size()==0 || size()==0)
    {
      return npos;
    }

    for( size_type i = std::min(m_size,pos); i > 0; --i )
    {
      for( size_type j = 0; j < v.size(); ++j )
      {
        if( v[j] == m_str[i-1] )
        {
          return i-1;
        }
      }
    }
    return npos;
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find_last_of( value_type c,
                                                   size_type pos )
    const
  {
    return find_last_of( basic_string_view<CharT,Traits>(&c, 1), pos );
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find_last_of( value_type const* s,
                                                   size_type pos,
                                                   size_type count )
    const
  {
    return find_last_of( basic_string_view<CharT,Traits>(s, count), pos );
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find_last_of( value_type const* s,
                                                   size_type pos )
    const
  {
    return find_last_of( basic_string_view<CharT,Traits>(s), pos );
  }

  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find_first_not_of( basic_string_view v,
                                                        size_type pos )
    const
  {
    if(v.size()==0 || size()==0)
    {
      return npos;
    }

    for( size_type i = pos; i < m_size; ++i )
    {
      size_type j = 0;
      for( ; j < v.size(); ++j )
      {
        if( v[j] == m_str[i] )
        {
          break;
        }
      }
      if( j == v.size() )
      {
        return i;
      }
    }
    return npos;
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find_first_not_of( value_type c,
                                                        size_type pos )
    const
  {
    return find_first_not_of( basic_string_view<CharT,Traits>(&c, 1), pos );
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find_first_not_of( value_type const* s,
                                                        size_type pos,
                                                        size_type count )
    const
  {
    return find_first_not_of( basic_string_view<CharT,Traits>(s, count), pos );
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find_first_not_of( value_type const* s,
                                                        size_type pos )
    const
  {
    return find_first_not_of( basic_string_view<CharT,Traits>(s), pos );
  }

  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find_last_not_of( basic_string_view v,
                                                       size_type pos )
    const
  {
    if(v.size()==0 || size()==0)
    {
      return npos;
    }

    for( size_type i = std::min(m_size,pos); i > 0; --i )
    {
      size_type j = 0;
      for( ; j < v.size(); ++j )
      {
        if( v[j] == m_str[i-1] )
        {
          break;
        }
      }
      if( j == v.size() )
      {
        return i-1;
      }
    }
    return npos;
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find_last_not_of( value_type c,
                                                       size_type pos )
    const
  {
    return find_last_not_of( basic_string_view<CharT,Traits>(&c, 1), pos );
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find_last_not_of( value_type const* s,
                                                       size_type pos,
                                                       size_type count )
    const
  {
    return find_last_not_of( basic_string_view<CharT,Traits>(s, count), pos );
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::size_type
    basic_string_view<CharT,Traits>::find_last_not_of( value_type const* s,
                                                       size_type pos )
    const
  {
    return find_last_not_of( basic_string_view<CharT,Traits>(s), pos );
  }

  //--------------------------------------------------------------------------
  // Iterator
  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::const_iterator
    basic_string_view<CharT,Traits>::begin()
    const noexcept
  {
    return m_str;
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::const_iterator
    basic_string_view<CharT,Traits>::cbegin()
    const noexcept
  {
    return m_str;
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::const_iterator
    basic_string_view<CharT,Traits>::end()
    const noexcept
  {
    return m_str + m_size;
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::const_iterator
    basic_string_view<CharT,Traits>::cend()
    const noexcept
  {
    return m_str + m_size;
  }

  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::const_reverse_iterator
    basic_string_view<CharT,Traits>::rbegin()
    const noexcept
  {
    return const_reverse_iterator{m_str - 1};
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::const_reverse_iterator
    basic_string_view<CharT,Traits>::crbegin()
    const noexcept
  {
    return const_reverse_iterator{m_str - 1};
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::const_reverse_iterator
    basic_string_view<CharT,Traits>::rend()
    const noexcept
  {
    return const_reverse_iterator{m_str + (m_size - 1)};
  }

  template<typename CharT, typename Traits>
  inline constexpr typename basic_string_view<CharT,Traits>::const_reverse_iterator
    basic_string_view<CharT,Traits>::crend()
    const noexcept
  {
    return const_reverse_iterator{m_str + (m_size - 1)};
  }
  //--------------------------------------------------------------------------
  // Public Functions
  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  std::basic_ostream<CharT,Traits>& operator << ( std::basic_ostream<CharT,Traits>& o,
                                                  const basic_string_view<CharT,Traits>& str )
  {
    o.write(str.data(),str.size());
    return o;
  }

  template<typename CharT, typename Traits>
  inline void swap( basic_string_view<CharT,Traits>& lhs,
                    basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    lhs.swap(rhs);
  }

  //--------------------------------------------------------------------------
  // Comparison Functions
  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline bool operator == ( const basic_string_view<CharT,Traits>& lhs,
                            const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return lhs.compare(rhs) == 0;
  }

  template<typename CharT, typename Traits, std::size_t N>
  inline bool operator == ( const basic_string_view<CharT,Traits>& lhs,
                            CharT (&rhs)[N] )
    noexcept
  {
    return lhs == basic_string_view<CharT,Traits>(rhs);
  }

  template<typename CharT, typename Traits, std::size_t N>
  inline bool operator == ( CharT (&lhs)[N],
                            const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return basic_string_view<CharT,Traits>(lhs) == rhs;
  }

  template<typename CharT, typename Traits>
  inline bool operator == ( basic_string_view<CharT,Traits> lhs,
                            const CharT* rhs )
    noexcept
  {
    return lhs == basic_string_view<CharT,Traits>(rhs);
  }

  template<typename CharT, typename Traits>
  inline bool operator == ( const CharT* lhs,
                            const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return basic_string_view<CharT,Traits>(lhs) == rhs;
  }

  template<typename CharT, typename Traits, typename Allocator>
  inline bool operator == ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                            const basic_string_view<CharT,Traits>& rhs )
  {
    return basic_string_view<CharT,Traits>(lhs) == rhs;
  }

  template<typename CharT, typename Traits, typename Allocator>
  inline bool operator == ( const basic_string_view<CharT,Traits>& lhs,
                            const std::basic_string<CharT,Traits,Allocator>& rhs )
  {
    return lhs == basic_string_view<CharT,Traits>(rhs);
  }

  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline bool operator != ( const basic_string_view<CharT,Traits>& lhs,
                            const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return lhs.compare(rhs) != 0;
  }

  template<typename CharT, typename Traits, std::size_t N>
  inline bool operator != ( const basic_string_view<CharT,Traits>& lhs,
                            CharT (&rhs)[N] )
    noexcept
  {
    return lhs != basic_string_view<CharT,Traits>(rhs);
  }

  template<typename CharT, typename Traits, std::size_t N>
  inline bool operator != ( CharT (&lhs)[N],
                            const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return basic_string_view<CharT,Traits>(lhs) != rhs;
  }

  template<typename CharT, typename Traits>
  inline bool operator != ( const basic_string_view<CharT,Traits>& lhs,
                            const CharT* rhs )
    noexcept
  {
    return lhs != basic_string_view<CharT,Traits>(rhs);
  }

  template<typename CharT, typename Traits>
  inline bool operator != ( const CharT* lhs,
                            const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return basic_string_view<CharT,Traits>(lhs) != rhs;
  }

  template<typename CharT, typename Traits, typename Allocator>
  inline bool operator != ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                            const basic_string_view<CharT,Traits>& rhs )
  {
    return basic_string_view<CharT,Traits>(lhs) != rhs;
  }

  template<typename CharT, typename Traits, typename Allocator>
  inline bool operator != ( const basic_string_view<CharT,Traits>& lhs,
                            const std::basic_string<CharT,Traits,Allocator>& rhs )
  {
    return lhs != basic_string_view<CharT,Traits>(rhs);
  }
  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline bool operator < ( const basic_string_view<CharT,Traits>& lhs,
                           const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return lhs.compare(rhs) < 0;
  }

  template<typename CharT, typename Traits, std::size_t N>
  inline bool operator < ( const basic_string_view<CharT,Traits>& lhs,
                           CharT (&rhs)[N] )
    noexcept
  {
    return lhs < basic_string_view<CharT,Traits>(rhs);
  }

  template<typename CharT, typename Traits, std::size_t N>
  inline bool operator < ( CharT (&lhs)[N],
                           const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return basic_string_view<CharT,Traits>(lhs) < rhs;
  }

  template<typename CharT, typename Traits>
  inline bool operator < ( const basic_string_view<CharT,Traits>& lhs,
                           const CharT* rhs )
    noexcept
  {
    return lhs < basic_string_view<CharT,Traits>(rhs);
  }

  template<typename CharT, typename Traits>
  inline bool operator < ( const CharT* lhs,
                           const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return basic_string_view<CharT,Traits>(lhs) < rhs;
  }

  template<typename CharT, typename Traits, typename Allocator>
  inline bool operator < ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                           const basic_string_view<CharT,Traits>& rhs )
  {
    return basic_string_view<CharT,Traits>(lhs) < rhs;
  }

  template<typename CharT, typename Traits, typename Allocator>
  inline bool operator < ( const basic_string_view<CharT,Traits>& lhs,
                           const std::basic_string<CharT,Traits,Allocator>& rhs )
  {
    return lhs < basic_string_view<CharT,Traits>(rhs);
  }

  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline bool operator > ( const basic_string_view<CharT,Traits>& lhs,
                           const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return lhs.compare(rhs) > 0;
  }

  template<typename CharT, typename Traits, std::size_t N>
  inline bool operator > ( const basic_string_view<CharT,Traits>& lhs,
                           CharT (&rhs)[N] )
    noexcept
  {
    return lhs > basic_string_view<CharT,Traits>(rhs);
  }

  template<typename CharT, typename Traits, std::size_t N>
  inline bool operator > ( CharT (&lhs)[N],
                           const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return basic_string_view<CharT,Traits>(lhs) > rhs;
  }

  template<typename CharT, typename Traits>
  inline bool operator > ( const basic_string_view<CharT,Traits>& lhs,
                           const CharT* rhs )
    noexcept
  {
    return lhs > basic_string_view<CharT,Traits>(rhs);
  }

  template<typename CharT, typename Traits>
  inline bool operator > ( const CharT* lhs,
                           const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return basic_string_view<CharT,Traits>(lhs) > rhs;
  }

  template<typename CharT, typename Traits, typename Allocator>
  inline bool operator > ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                           const basic_string_view<CharT,Traits>& rhs )
  {
    return basic_string_view<CharT,Traits>(lhs) > rhs;
  }

  template<typename CharT, typename Traits, typename Allocator>
  inline bool operator > ( const basic_string_view<CharT,Traits>& lhs,
                           const std::basic_string<CharT,Traits,Allocator>& rhs )
  {
    return lhs > basic_string_view<CharT,Traits>(rhs);
  }

  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline bool operator <= ( const basic_string_view<CharT,Traits>& lhs,
                            const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return lhs.compare(rhs) <= 0;
  }

  template<typename CharT, typename Traits, std::size_t N>
  inline bool operator <= ( const basic_string_view<CharT,Traits>& lhs,
                            CharT (&rhs)[N] )
    noexcept
  {
    return lhs <= basic_string_view<CharT,Traits>(rhs);
  }

  template<typename CharT, typename Traits, std::size_t N>
  inline bool operator <= ( CharT (&lhs)[N],
                            const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return basic_string_view<CharT,Traits>(lhs) <= rhs;
  }

  template<typename CharT, typename Traits>
  inline bool operator <= ( const basic_string_view<CharT,Traits>& lhs,
                            const CharT* rhs )
    noexcept
  {
    return lhs <= basic_string_view<CharT,Traits>(rhs);
  }

  template<typename CharT, typename Traits>
  inline bool operator <= ( const CharT* lhs,
                            const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return basic_string_view<CharT,Traits>(lhs) <= rhs;
  }

  template<typename CharT, typename Traits, typename Allocator>
  inline bool operator <= ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                            const basic_string_view<CharT,Traits>& rhs )
  {
    return basic_string_view<CharT,Traits>(lhs) <= rhs;
  }

  template<typename CharT, typename Traits, typename Allocator>
  inline bool operator <= ( const basic_string_view<CharT,Traits>& lhs,
                            const std::basic_string<CharT,Traits,Allocator>& rhs )
  {
    return lhs <= basic_string_view<CharT,Traits>(rhs);
  }

  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  inline bool operator >= ( const basic_string_view<CharT,Traits>& lhs,
                            const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return lhs.compare(rhs) >= 0;
  }

  template<typename CharT, typename Traits, std::size_t N>
  inline bool operator >= ( const basic_string_view<CharT,Traits>& lhs,
                            CharT (&rhs)[N] )
    noexcept
  {
    return lhs >= basic_string_view<CharT,Traits>(rhs);
  }

  template<typename CharT, typename Traits, std::size_t N>
  inline bool operator >= ( CharT (&lhs)[N],
                            const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return basic_string_view<CharT,Traits>(lhs) >= rhs;
  }

  template<typename CharT, typename Traits>
  inline bool operator >= ( const basic_string_view<CharT,Traits>& lhs,
                            const CharT* rhs )
    noexcept
  {
    return lhs >= basic_string_view<CharT,Traits>(rhs);
  }

  template<typename CharT, typename Traits>
  inline bool operator >= ( const CharT* lhs,
                            const basic_string_view<CharT,Traits>& rhs )
    noexcept
  {
    return basic_string_view<CharT,Traits>(lhs) >= rhs;
  }

  template<typename CharT, typename Traits, typename Allocator>
  inline bool operator >= ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                            const basic_string_view<CharT,Traits>& rhs )
  {
    return basic_string_view<CharT,Traits>(lhs) >= rhs;
  }

  template<typename CharT, typename Traits, typename Allocator>
  inline bool operator >= ( const basic_string_view<CharT,Traits>& lhs,
                            const std::basic_string<CharT,Traits,Allocator>& rhs )
  {
    return lhs >= basic_string_view<CharT,Traits>(rhs);
  }

  //--------------------------------------------------------------------------
  // Hash Functions
  //--------------------------------------------------------------------------

  namespace detail {

    template<std::size_t> constexpr std::size_t fnv1_prime();
    template<std::size_t> constexpr std::size_t fnv1_offset();

    template<> constexpr std::size_t fnv1_prime<4>(){ return 16777619ul; }
    template<> constexpr std::size_t fnv1_prime<8>(){ return 1099511628211ull; }

    template<> constexpr std::size_t fnv1_offset<4>(){ return 2166136261ul; }
    template<> constexpr std::size_t fnv1_offset<8>(){ return 14695981039346656037ull; }

  }

  template<typename CharT, typename Traits>
  inline constexpr std::size_t hash_value( const basic_string_view<CharT,Traits>& str )
    noexcept
  {
    constexpr auto offset = detail::fnv1_offset<sizeof(std::size_t)>();
    constexpr auto prime  = detail::fnv1_prime<sizeof(std::size_t)>();

    auto count  = str.size();
    auto result = offset;
    auto ptr    = str.data();
    while (count--)
    {
      result ^= static_cast<std::size_t>(*(ptr++));
      result *= prime;
    }
    return result;
  }

} // namespace bit

#endif /* BFSTL_DETAIL_STRING_VIEW_INL */
