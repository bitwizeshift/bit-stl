#ifndef BIT_STL_UTILITIES_DETAIL_HASH_INL
#define BIT_STL_UTILITIES_DETAIL_HASH_INL

//-----------------------------------------------------------------------------
// Hashing Calculations
//-----------------------------------------------------------------------------

template<typename T>
inline constexpr void
  bit::stl::hash_combine( std::size_t& seed, const T& v )
{
  seed ^= hash_value(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename InputIterator>
inline constexpr std::size_t
  bit::stl::hash_range( InputIterator first, InputIterator last )
{
  auto hash = std::size_t{0};
  hash_range( hash, first, last );
  return hash;
}

template<typename InputIterator>
inline constexpr void
  bit::stl::hash_range( std::size_t& seed,
                        InputIterator first,
                        InputIterator last )
{
  if(first==last) return;

  for(; first != last; ++first )
  {
    hash_combine(seed,*first);
  }
}

//-----------------------------------------------------------------------------

inline constexpr std::size_t  bit::stl::hash_value( std::nullptr_t )
  noexcept
{
  return std::size_t{0};
}

inline constexpr std::size_t bit::stl::hash_value( bool val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

inline constexpr std::size_t bit::stl::hash_value( char val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

inline constexpr std::size_t bit::stl::hash_value( signed char val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

inline constexpr std::size_t bit::stl::hash_value( unsigned char val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

inline constexpr std::size_t bit::stl::hash_value( wchar_t val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

inline constexpr std::size_t bit::stl::hash_value( char16_t val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

inline constexpr std::size_t bit::stl::hash_value( char32_t val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

inline constexpr std::size_t bit::stl::hash_value( short val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

inline constexpr std::size_t bit::stl::hash_value( unsigned short val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

inline constexpr std::size_t bit::stl::hash_value( int val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

inline constexpr std::size_t bit::stl::hash_value( unsigned int val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

inline constexpr std::size_t bit::stl::hash_value( long val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

inline constexpr std::size_t bit::stl::hash_value( unsigned long val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

inline constexpr std::size_t bit::stl::hash_value( long long val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

inline constexpr std::size_t bit::stl::hash_value( unsigned long long val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

inline std::size_t bit::stl::hash_value( float val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

inline std::size_t bit::stl::hash_value( double val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

inline std::size_t bit::stl::hash_value( long double val )
  noexcept
{
  return static_cast<std::size_t>(val);
}

template<typename T>
inline std::size_t bit::stl::hash_value( T* const& val )
  noexcept
{
  return reinterpret_cast<std::size_t>(val);
}

template<typename T, unsigned N>
inline constexpr std::size_t bit::stl::hash_value( T (&val)[N] )
{
  return hash_range( std::begin(val), std::end(val) );
}

template<typename T, unsigned N>
inline constexpr std::size_t bit::stl::hash_value( const T (&val)[N] )
{
  return hash_range( std::begin(val), std::end(val) );
}

template<typename Enum, typename>
inline constexpr std::size_t bit::stl::hash_value( Enum val )
  noexcept
{
  return hash_value( static_cast<std::underlying_type_t<Enum>>(val) );
}

template<typename Container, typename>
inline constexpr std::size_t
  bit::stl::hash_value( const Container& container )
  noexcept
{
  return hash_range( container.begin(), container.end() );
}

template<typename T, typename U>
inline constexpr std::size_t
  bit::stl::hash_value( const std::pair<T,U>& pair )
{
  auto seed = hash_value( pair.first );
  hash_combine( seed, pair.second );

  return seed;
}

namespace bit { namespace stl { namespace detail {

  template<typename...Args, std::size_t...Idxs>
  inline constexpr void hash_tuple_combine( std::size_t& seed,
                                            const std::tuple<Args...>& tuple,
                                            std::index_sequence<Idxs...> )
  {
    hash_tuple_combine( seed, std::get<Idxs>(tuple)... );
  }

  template<typename Arg0, typename...Args>
  inline constexpr void hash_tuple_combine( std::size_t& seed,
                                            const Arg0& arg0,
                                            const Args&...args )
  {
    hash_combine( seed, arg0 );
    hash_tuple_combine( seed, args... );
  }

  template<typename Arg0>
  inline constexpr void hash_tuple_combine( std::size_t& seed,
                                            const Arg0& arg0 )
  {
    hash_combine( seed, arg0 );
  }

} } } // namespace bit::stl::detail


template<typename...Args>
inline constexpr std::size_t
  bit::stl::hash_value( const std::tuple<Args...>& tuple )
{
  auto seed = std::size_t{0};
  detail::hash_tuple_combine( seed, tuple, std::index_sequence_for<Args...>() );

  return seed;
}

template<typename T>
inline constexpr std::size_t
  bit::stl::hash_value( const std::initializer_list<T>& il )
{
  return hash_range( il.begin(), il.end() );
}

//-----------------------------------------------------------------------------

template<typename Key>
inline constexpr std::size_t
  bit::stl::hash<Key>::operator()( const Key& val )
{
  return hash_value( val );
}

#endif /* BIT_STL_UTILITIES_DETAIL_HASH_INL */
