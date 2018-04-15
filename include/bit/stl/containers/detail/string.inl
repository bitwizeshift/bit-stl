#ifndef BIT_STL_CONTAINERS_DETAIL_STRING_INL
#define BIT_STL_CONTAINERS_DETAIL_STRING_INL

//----------------------------------------------------------------------------
// Char Traits
//----------------------------------------------------------------------------

template<typename CharT>
inline constexpr CharT
  bit::stl::insensitive_char_traits<CharT>::to_upper( CharT ch )
  noexcept
{
  return std::toupper( ch, std::locale() );
}

//----------------------------------------------------------------------------

template<typename CharT>
inline constexpr bool
  bit::stl::insensitive_char_traits<CharT>::eq( CharT lhs, CharT rhs )
  noexcept
{
  return to_upper(lhs) == to_upper(rhs);
}

template<typename CharT>
inline constexpr bool
  bit::stl::insensitive_char_traits<CharT>::lt( CharT lhs, CharT rhs )
  noexcept
{
  return to_upper(lhs) < to_upper(rhs);
}

//----------------------------------------------------------------------------

template<typename CharT>
inline constexpr int
  bit::stl::insensitive_char_traits<CharT>::compare( const CharT* s1,
                                                     const CharT* s2,
                                                     std::size_t count )
  noexcept
{
  while( count-- != 0 ) {
    if( to_upper(*s1) < to_upper(*s2) ) return -1;
    if( to_upper(*s1) > to_upper(*s2) ) return 1;
    ++s1; ++s2;
  }
  return 0;
}

//----------------------------------------------------------------------------

template<typename CharT>
inline constexpr const CharT*
  bit::stl::insensitive_char_traits<CharT>::find( const CharT* s,
                                                  int n, CharT a )
  noexcept
{
  auto const ua = to_upper(a);

  while( n-- != 0 ) {
    if( to_upper(*s) == ua ) return s;
    ++s;
  }
  return nullptr;
}

//----------------------------------------------------------------------------
// Utilities
//----------------------------------------------------------------------------

template<typename CharT, typename Traits, typename Allocator>
bit::stl::hash_t
  bit::stl::hash_value( const std::basic_string<CharT,Traits,Allocator>& str )
  noexcept
{
  return hash_string_segment( str.data(), str.size() );
}

#endif /* BIT_STL_CONTAINERS_DETAIL_STRING_INL */
