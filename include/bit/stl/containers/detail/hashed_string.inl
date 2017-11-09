#ifndef BIT_STL_CONTAINERS_DETAIL_HASHED_STRING_INL
#define BIT_STL_CONTAINERS_DETAIL_HASHED_STRING_INL

//----------------------------------------------------------------------------
// Constructor / Assignment
//----------------------------------------------------------------------------

template<typename CharT, typename Traits, typename Allocator>
inline bit::stl::basic_hashed_string<CharT,Traits,Allocator>
  ::basic_hashed_string()
  noexcept( std::is_nothrow_default_constructible<Allocator>::value )
  : m_string()
  , m_hash(hash_value(m_string))
{

}

template<typename CharT, typename Traits, typename Allocator>
inline bit::stl::basic_hashed_string<CharT,Traits,Allocator>
  ::basic_hashed_string( const Allocator& alloc )
  noexcept( std::is_nothrow_copy_constructible<Allocator>::value )
  : m_string( alloc )
  , m_hash(hash_value(m_string))
{

}

template<typename CharT, typename Traits, typename Allocator>
inline bit::stl::basic_hashed_string<CharT,Traits,Allocator>
  ::basic_hashed_string( size_type count,
                         CharT ch,
                         const Allocator& alloc )
  : m_string(count,ch,alloc)
  , m_hash(hash_value(m_string))
{

}

template<typename CharT, typename Traits, typename Allocator>
inline bit::stl::basic_hashed_string<CharT,Traits,Allocator>
  ::basic_hashed_string( const string_type& other,
                         size_type pos,
                         size_type count,
                         const Allocator& alloc )
  : m_string(other,pos,count,alloc)
  , m_hash(hash_value(m_string))
{

}

template<typename CharT, typename Traits, typename Allocator>
inline bit::stl::basic_hashed_string<CharT,Traits,Allocator>
  ::basic_hashed_string( const CharT* s,
                         size_type count,
                         const Allocator& alloc )
  : m_string(s, count, alloc)
  , m_hash(hash_value(m_string))
{

}

template<typename CharT, typename Traits, typename Allocator>
inline bit::stl::basic_hashed_string<CharT,Traits,Allocator>
  ::basic_hashed_string( const CharT* s,
                         const Allocator& alloc )
  : m_string(s,alloc)
  , m_hash(hash_value(m_string))
{

}

template<typename CharT, typename Traits, typename Allocator>
template<typename InputIt>
inline bit::stl::basic_hashed_string<CharT,Traits,Allocator>
  ::basic_hashed_string( InputIt first, InputIt last,
                         const Allocator& alloc )
  : m_string(first,last)
  , m_hash(hash_value(m_string))
{

}

template<typename CharT, typename Traits, typename Allocator>
inline bit::stl::basic_hashed_string<CharT,Traits,Allocator>
  ::basic_hashed_string( const basic_hashed_string& other )
  : m_string(other.m_string)
  , m_hash(hash_value(m_string))
{

}

template<typename CharT, typename Traits, typename Allocator>
inline bit::stl::basic_hashed_string<CharT,Traits,Allocator>
  ::basic_hashed_string( const basic_hashed_string& other,
                         const Allocator& alloc )
  : m_string(other.m_string, alloc)
  , m_hash(hash_value(m_string))
{

}

template<typename CharT, typename Traits, typename Allocator>
inline bit::stl::basic_hashed_string<CharT,Traits,Allocator>
  ::basic_hashed_string( basic_hashed_string&& other )
  noexcept
  : m_string(std::move(other.m_string))
  , m_hash(hash_value(m_string))
{

}

template<typename CharT, typename Traits, typename Allocator>
inline bit::stl::basic_hashed_string<CharT,Traits,Allocator>
  ::basic_hashed_string( basic_hashed_string&& other,
                         const Allocator& alloc )
  : m_string(std::move(other.m_string), alloc)
  , m_hash(hash_value(m_string))
{

}

template<typename CharT, typename Traits, typename Allocator>
inline bit::stl::basic_hashed_string<CharT,Traits,Allocator>
  ::basic_hashed_string( std::initializer_list<CharT> init,
                         const Allocator& alloc )
  : m_string(std::move(init), alloc)
  , m_hash(hash_value(m_string))
{

}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, typename Allocator>
inline bit::stl::basic_hashed_string<CharT,Traits,Allocator>&
  bit::stl::basic_hashed_string<CharT,Traits,Allocator>::operator=( string_view_type other )
{
  m_string = static_cast<string_type>(other);
  m_hash   = hash_value(m_string);

  return (*this);
}

//----------------------------------------------------------------------------
// Accessors
//----------------------------------------------------------------------------

template<typename CharT, typename Traits, typename Allocator>
inline typename bit::stl::basic_hashed_string<CharT,Traits,Allocator>::hash_type
  bit::stl::basic_hashed_string<CharT,Traits,Allocator>::hash()
  const noexcept
{
  return m_hash;
}

template<typename CharT, typename Traits, typename Allocator>
inline typename bit::stl::basic_hashed_string<CharT,Traits,Allocator>::string_view_type
  bit::stl::basic_hashed_string<CharT,Traits,Allocator>::view()
  const noexcept
{
  return m_string;
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, typename Allocator>
inline const typename bit::stl::basic_hashed_string<CharT,Traits,Allocator>::char_type*
  bit::stl::basic_hashed_string<CharT,Traits,Allocator>::c_str()
  const noexcept
{
  return m_string.data();
}

template<typename CharT, typename Traits, typename Allocator>
inline const typename bit::stl::basic_hashed_string<CharT,Traits,Allocator>::char_type*
  bit::stl::basic_hashed_string<CharT,Traits,Allocator>::data()
  const noexcept
{
  return m_string.data();
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, typename Allocator>
inline typename bit::stl::basic_hashed_string<CharT,Traits,Allocator>::size_type
  bit::stl::basic_hashed_string<CharT,Traits,Allocator>::size()
  const noexcept
{
  return m_string.size();
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename CharT, typename Traits, typename Allocator>
inline void
  bit::stl::basic_hashed_string<CharT,Traits,Allocator>::swap( basic_hashed_string& other )
  noexcept
{
  using std::swap;

  swap(m_string,other.m_string);
  swap(m_hash,other.m_hash);
}

//============================================================================
// Free Functions
//============================================================================

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename CharT, typename Traits, typename Allocator>
inline void bit::stl::swap( basic_hashed_string<CharT,Traits,Allocator>& lhs,
                            basic_hashed_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//----------------------------------------------------------------------------
// Hash Functions
//----------------------------------------------------------------------------

template<typename CharT, typename Traits, typename Allocator>
inline std::size_t
  bit::stl::hash_value( const basic_hashed_string<CharT,Traits,Allocator>& str )
  noexcept
{
  return str.hash();
}

//----------------------------------------------------------------------------
// Comparison Operators
//----------------------------------------------------------------------------

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator == ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                          const basic_hashed_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return lhs.hash() == rhs.hash() && lhs.view() == rhs.view();
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator == ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                          const basic_hashed_string_view<CharT,Traits>& rhs )
  noexcept
{
  return lhs.hash() == rhs.hash() && lhs.view() == rhs.view();
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator == ( const basic_hashed_string_view<CharT,Traits>& lhs,
                          const basic_hashed_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return lhs.hash() == rhs.hash() && lhs.view() == rhs.view();
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator != ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                          const basic_hashed_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return !(lhs==rhs);
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator != ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                          const basic_hashed_string_view<CharT,Traits>& rhs )
  noexcept
{
  return !(lhs==rhs);
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator != ( const basic_hashed_string_view<CharT,Traits>& lhs,
                          const basic_hashed_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return !(lhs==rhs);
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator < ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                         const basic_hashed_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return lhs.hash() == rhs.hash() ? lhs.view() < rhs.view() : lhs.hash() < rhs.hash();
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator < ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                         const basic_hashed_string_view<CharT,Traits>& rhs )
  noexcept
{
  return lhs.hash() == rhs.hash() ? lhs.view() < rhs.view() : lhs.hash() < rhs.hash();
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator < ( const basic_hashed_string_view<CharT,Traits>& lhs,
                         const basic_hashed_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return lhs.hash() == rhs.hash() ? lhs.view() < rhs.view() : lhs.hash() < rhs.hash();
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator > ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                         const basic_hashed_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return rhs < lhs;
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator > ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                         const basic_hashed_string_view<CharT,Traits>& rhs )
  noexcept
{
  return rhs < lhs;
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator > ( const basic_hashed_string_view<CharT,Traits>& lhs,
                         const basic_hashed_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return rhs < lhs;
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator <= ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                          const basic_hashed_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return !(rhs < lhs);
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator <= ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                          const basic_hashed_string_view<CharT,Traits>& rhs )
  noexcept
{
  return !(rhs < lhs);
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator <= ( const basic_hashed_string_view<CharT,Traits>& lhs,
                          const basic_hashed_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return !(rhs < lhs);
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator >= ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                          const basic_hashed_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return !(lhs < rhs);
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator >= ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                          const basic_hashed_string_view<CharT,Traits>& rhs )
  noexcept
{
  return !(lhs < rhs);
}

template<typename CharT, typename Traits, typename Allocator>
inline bool
  bit::stl::operator >= ( const basic_hashed_string_view<CharT,Traits>& lhs,
                          const basic_hashed_string<CharT,Traits,Allocator>& rhs )
  noexcept
{
  return !(lhs < rhs);
}

#endif /* BIT_STL_CONTAINERS_DETAIL_HASHED_STRING_INL */
