#ifndef BIT_STL_DETAIL_HASHED_STRING_VIEW_INL
#define BIT_STL_DETAIL_HASHED_STRING_VIEW_INL

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr bit::stl::basic_hashed_string_view<CharT,Traits>::
  basic_hashed_string_view()
  noexcept
  : m_view(),
    m_hash(hash_value(m_view))
{

}

template<typename CharT, typename Traits>
template<size_t N>
inline constexpr bit::stl::basic_hashed_string_view<CharT,Traits>::
  basic_hashed_string_view( const char_type(&str)[N] )
  noexcept
  : m_view(str,N-1),
    m_hash(hash_value(m_view))
{

}

template<typename CharT, typename Traits>
template<typename Allocator>
inline constexpr bit::stl::basic_hashed_string_view<CharT,Traits>::
  basic_hashed_string_view( const std::basic_string<CharT,Traits,Allocator>& str )
  noexcept
  : m_view(str.data(),str.size()),
    m_hash(hash_value(m_view))
{

}

template<typename CharT, typename Traits>
inline bit::stl::basic_hashed_string_view<CharT,Traits>::
  basic_hashed_string_view( const_char_wrapper str )
  noexcept
  : m_view(str.ptr),
    m_hash(hash_value(m_view))
{

}

template<typename CharT, typename Traits>
inline constexpr bit::stl::basic_hashed_string_view<CharT,Traits>::
  basic_hashed_string_view( const char_type* str, size_type count )
  noexcept
  : m_view(str,count),
    m_hash(hash_value(m_view))
{

}

//----------------------------------------------------------------------------
// Accessors
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr typename bit::stl::basic_hashed_string_view<CharT,Traits>::hash_type
  bit::stl::basic_hashed_string_view<CharT,Traits>::
  hash() const noexcept
{
  return m_hash;
}

template<typename CharT, typename Traits>
  inline constexpr typename bit::stl::basic_hashed_string_view<CharT,Traits>::string_view_type
  bit::stl::basic_hashed_string_view<CharT,Traits>::view()
  const noexcept
{
  return m_view;
}

template<typename CharT, typename Traits>
  inline constexpr const typename bit::stl::basic_hashed_string_view<CharT,Traits>::char_type*
  bit::stl::basic_hashed_string_view<CharT,Traits>::c_str()
  const noexcept
{
  return m_view.data();
}

template<typename CharT, typename Traits>
  inline constexpr const typename bit::stl::basic_hashed_string_view<CharT,Traits>::char_type*
  bit::stl::basic_hashed_string_view<CharT,Traits>::data()
  const noexcept
{
  return m_view.data();
}

template<typename CharT, typename Traits>
  inline constexpr typename bit::stl::basic_hashed_string_view<CharT,Traits>::size_type
  bit::stl::basic_hashed_string_view<CharT,Traits>::size()
  const noexcept
{
  return m_view.size();
}

template<typename CharT, typename Traits>
  inline void bit::stl::basic_hashed_string_view<CharT,Traits>::
  swap( basic_hashed_string_view& other )
  noexcept
{
  using std::swap; // for use with ADL
  swap(m_hash,other.m_hash);
  swap(m_view,other.m_view);
}

//----------------------------------------------------------------------------
// Equality Comparisons
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr bool
  bit::stl::operator == ( const basic_hashed_string_view<CharT,Traits>& lhs,
                          const basic_hashed_string_view<CharT,Traits>& rhs )
  noexcept
{
  return lhs.hash() == rhs.hash();
}

template<typename CharT, typename Traits>
inline constexpr bool
  bit::stl::operator != ( const basic_hashed_string_view<CharT,Traits>& lhs,
                          const basic_hashed_string_view<CharT,Traits>& rhs )
  noexcept
{
  return lhs.hash() != rhs.hash();
}

template<typename CharT, typename Traits>
inline constexpr bool
  bit::stl::operator < ( const basic_hashed_string_view<CharT,Traits>& lhs,
                         const basic_hashed_string_view<CharT,Traits>& rhs )
  noexcept
{
  return lhs.hash() < rhs.hash();
}

template<typename CharT, typename Traits>
inline constexpr bool
  bit::stl::operator > ( const basic_hashed_string_view<CharT,Traits>& lhs,
                         const basic_hashed_string_view<CharT,Traits>& rhs )
  noexcept
{
  return lhs.hash() > rhs.hash();
}

template<typename CharT, typename Traits>
inline constexpr bool
  bit::stl::operator <= ( const basic_hashed_string_view<CharT,Traits>& lhs,
                          const basic_hashed_string_view<CharT,Traits>& rhs )
  noexcept
{
  return lhs.hash() <= rhs.hash();
}

template<typename CharT, typename Traits>
inline constexpr bool
  bit::stl::operator >= ( const basic_hashed_string_view<CharT,Traits>& lhs,
                          const basic_hashed_string_view<CharT,Traits>& rhs )
  noexcept
{
  return lhs.hash() >= rhs.hash();
}

//----------------------------------------------------------------------------
// Mutators
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline void
  bit::stl::swap( basic_hashed_string_view<CharT,Traits>& lhs,
                  basic_hashed_string_view<CharT,Traits>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//----------------------------------------------------------------------------
// Hash Functions
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline constexpr std::size_t
  bit::stl::hash_value( const basic_hashed_string_view<CharT,Traits>& str )
  noexcept
{
  return str.hash();
}

#endif /* BIT_STL_DETAIL_HASHED_STRING_VIEW_INL */
