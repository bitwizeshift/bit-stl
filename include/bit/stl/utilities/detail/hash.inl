#ifndef BIT_STL_UTILITIES_DETAIL_HASH_INL
#define BIT_STL_UTILITIES_DETAIL_HASH_INL

//=============================================================================
// hash_t
//=============================================================================

//-----------------------------------------------------------------------------
// Compound Operators
//-----------------------------------------------------------------------------

inline bit::stl::hash_t& bit::stl::operator+=( hash_t& lhs, hash_t rhs )
  noexcept
{
  return lhs = static_cast<hash_t>(static_cast<std::size_t>(lhs) + static_cast<std::size_t>(rhs));
}

inline bit::stl::hash_t& bit::stl::operator-=( hash_t& lhs, hash_t rhs )
  noexcept
{
  return lhs = static_cast<hash_t>(static_cast<std::size_t>(lhs) - static_cast<std::size_t>(rhs));
}

inline bit::stl::hash_t& bit::stl::operator*=( hash_t& lhs, hash_t rhs )
  noexcept
{
  return lhs = static_cast<hash_t>(static_cast<std::size_t>(lhs) * static_cast<std::size_t>(rhs));
}

inline bit::stl::hash_t& bit::stl::operator/=( hash_t& lhs, hash_t rhs )
  noexcept
{
  return lhs = static_cast<hash_t>(static_cast<std::size_t>(lhs) / static_cast<std::size_t>(rhs));
}

inline bit::stl::hash_t& bit::stl::operator%=( hash_t& lhs, hash_t rhs )
  noexcept
{
  return lhs = static_cast<hash_t>(static_cast<std::size_t>(lhs) % static_cast<std::size_t>(rhs));
}

//-----------------------------------------------------------------------------

inline bit::stl::hash_t& bit::stl::operator&=( hash_t& lhs, hash_t rhs )
  noexcept
{
  return lhs = static_cast<hash_t>(static_cast<std::size_t>(lhs) & static_cast<std::size_t>(rhs));
}

inline bit::stl::hash_t& bit::stl::operator|=( hash_t& lhs, hash_t rhs )
  noexcept
{
  return lhs = static_cast<hash_t>(static_cast<std::size_t>(lhs) | static_cast<std::size_t>(rhs));
}

inline bit::stl::hash_t& bit::stl::operator^=( hash_t& lhs, hash_t rhs )
  noexcept
{
  return lhs = static_cast<hash_t>(static_cast<std::size_t>(lhs) ^ static_cast<std::size_t>(rhs));
}

//-----------------------------------------------------------------------------

template<typename IntT, typename>
inline bit::stl::hash_t& bit::stl::operator<<=( hash_t& lhs, IntT rhs )
  noexcept
{
  return lhs = static_cast<hash_t>( static_cast<std::size_t>(lhs) << rhs );
}

template<typename IntT, typename>
inline bit::stl::hash_t& bit::stl::operator>>=( hash_t& lhs, IntT rhs )
  noexcept
{
  return lhs = static_cast<hash_t>( static_cast<std::size_t>(lhs) >> rhs );
}

//-----------------------------------------------------------------------------
// Binary Operators
//-----------------------------------------------------------------------------

inline constexpr bit::stl::hash_t bit::stl::operator+( hash_t lhs, hash_t rhs )
  noexcept
{
  return static_cast<hash_t>( static_cast<std::size_t>(lhs) + static_cast<std::size_t>(rhs) );
}

inline constexpr bit::stl::hash_t bit::stl::operator-( hash_t lhs, hash_t rhs )
  noexcept
{
  return static_cast<hash_t>( static_cast<std::size_t>(lhs) - static_cast<std::size_t>(rhs) );
}

inline constexpr bit::stl::hash_t bit::stl::operator*( hash_t lhs, hash_t rhs )
  noexcept
{
  return static_cast<hash_t>( static_cast<std::size_t>(lhs) * static_cast<std::size_t>(rhs) );
}

inline constexpr bit::stl::hash_t bit::stl::operator/( hash_t lhs, hash_t rhs )
  noexcept
{
  return static_cast<hash_t>( static_cast<std::size_t>(lhs) / static_cast<std::size_t>(rhs) );
}

inline constexpr bit::stl::hash_t bit::stl::operator%( hash_t lhs, hash_t rhs )
  noexcept
{
  return static_cast<hash_t>( static_cast<std::size_t>(lhs) % static_cast<std::size_t>(rhs) );
}

//-----------------------------------------------------------------------------

inline constexpr bit::stl::hash_t bit::stl::operator&( hash_t lhs, hash_t rhs )
  noexcept
{
  return static_cast<hash_t>( static_cast<std::size_t>(lhs) & static_cast<std::size_t>(rhs) );
}

inline constexpr bit::stl::hash_t bit::stl::operator|( hash_t lhs, hash_t rhs )
  noexcept
{
  return static_cast<hash_t>( static_cast<std::size_t>(lhs) | static_cast<std::size_t>(rhs) );
}

inline constexpr bit::stl::hash_t bit::stl::operator^( hash_t lhs, hash_t rhs )
  noexcept
{
  return static_cast<hash_t>( static_cast<std::size_t>(lhs) ^ static_cast<std::size_t>(rhs) );
}

//-----------------------------------------------------------------------------

template<typename IntT, typename>
inline constexpr bit::stl::hash_t bit::stl::operator<<( hash_t lhs, IntT rhs )
  noexcept
{
  return static_cast<hash_t>( static_cast<std::size_t>(lhs) << rhs );
}

template<typename IntT, typename>
inline constexpr bit::stl::hash_t bit::stl::operator>>( hash_t lhs, IntT rhs )
  noexcept
{
  return static_cast<hash_t>( static_cast<std::size_t>(lhs) >> rhs );
}

//-----------------------------------------------------------------------------
// Hashing Functions
//-----------------------------------------------------------------------------

inline constexpr bit::stl::hash_t bit::stl::hash_value( std::nullptr_t )
  noexcept
{
  return static_cast<hash_t>(0);
}

inline constexpr bit::stl::hash_t bit::stl::hash_value( bool val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

inline constexpr bit::stl::hash_t bit::stl::hash_value( char val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

inline constexpr bit::stl::hash_t bit::stl::hash_value( signed char val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

inline constexpr bit::stl::hash_t bit::stl::hash_value( unsigned char val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

inline constexpr bit::stl::hash_t bit::stl::hash_value( wchar_t val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

inline constexpr bit::stl::hash_t bit::stl::hash_value( char16_t val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

inline constexpr bit::stl::hash_t bit::stl::hash_value( char32_t val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

inline constexpr bit::stl::hash_t bit::stl::hash_value( short val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

inline constexpr bit::stl::hash_t bit::stl::hash_value( unsigned short val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

inline constexpr bit::stl::hash_t bit::stl::hash_value( int val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

inline constexpr bit::stl::hash_t bit::stl::hash_value( unsigned int val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

inline constexpr bit::stl::hash_t bit::stl::hash_value( long val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

inline constexpr bit::stl::hash_t bit::stl::hash_value( unsigned long val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

inline constexpr bit::stl::hash_t bit::stl::hash_value( long long val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

inline constexpr bit::stl::hash_t bit::stl::hash_value( unsigned long long val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

inline bit::stl::hash_t bit::stl::hash_value( float val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

inline bit::stl::hash_t bit::stl::hash_value( double val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

inline bit::stl::hash_t bit::stl::hash_value( long double val )
  noexcept
{
  return static_cast<hash_t>(static_cast<std::size_t>(val));
}

template<typename T>
inline bit::stl::hash_t bit::stl::hash_value( T* val )
  noexcept
{
  return static_cast<hash_t>(reinterpret_cast<std::size_t>(val));
}

template<typename R, typename...Args>
inline bit::stl::hash_t bit::stl::hash_value( R(*val)(Args...) )
  noexcept
{
  return hash_raw( val );
}

template<typename R, typename C, typename...Args>
bit::stl::hash_t bit::stl::hash_value( R(C::*val)(Args...) )
  noexcept
{
  return hash_raw( val );
}

template<typename R, typename C, typename...Args>
bit::stl::hash_t bit::stl::hash_value( R(C::*val)(Args...) const )
  noexcept
{
  return hash_raw( val );
}

template<typename R, typename C>
inline bit::stl::hash_t bit::stl::hash_value( R C::* val )
  noexcept
{
  return hash_raw( val );
}

template<typename T, std::size_t N>
inline constexpr bit::stl::hash_t bit::stl::hash_value( T (&val)[N] )
{
  return hash_range( std::begin(val), std::end(val) );
}

template<typename T, std::size_t N>
inline constexpr bit::stl::hash_t bit::stl::hash_value( const T (&val)[N] )
{
  return hash_range( std::begin(val), std::end(val) );
}

template<typename Enum, typename>
inline constexpr bit::stl::hash_t bit::stl::hash_value( Enum val )
  noexcept
{
  return hash_value( static_cast<std::underlying_type_t<Enum>>(val) );
}

//-----------------------------------------------------------------------------
// Composite Hashing Functions
//-----------------------------------------------------------------------------

inline constexpr bit::stl::hash_t bit::stl::hash_combine( hash_t seed,
                                                          hash_t hash )
  noexcept
{
  return (seed ^ hash) + static_cast<hash_t>(0x9e3779b9) + (seed << 6) + (seed >> 2);
}

template<typename...Hashes, typename>
inline constexpr bit::stl::hash_t bit::stl::hash_combine( hash_t seed,
                                                          hash_t hash0,
                                                          Hashes...hashes )
  noexcept
{
  return hash_combine( hash_combine(seed,hash0), hashes... );
}

//-----------------------------------------------------------------------------

template<typename InputIterator>
inline constexpr bit::stl::hash_t bit::stl::hash_range( InputIterator first,
                                                        InputIterator last )
  noexcept( is_nothrow_hashable<typename std::iterator_traits<InputIterator>::value_type>::value )
{
  auto seed = static_cast<hash_t>(0);
  for(; first != last; ++first ) {
    seed = hash_combine( seed, hash_value(*first) );
  }
  return seed;
}

//-----------------------------------------------------------------------------

namespace bit { namespace stl { namespace detail {

  template<typename Arg0, typename Arg1, typename...Args>
  ::bit::stl::hash_t hash_values_impl( Arg0&& arg0, Arg1&& arg1, Args&&...args )
  {
    using ::bit::stl::hash_value;

    return hash_combine( hash_value( std::forward<Arg0>(arg0) ),
                         hash_value( std::forward<Arg1>(arg1) ),
                         hash_value( std::forward<Args>(args) )... );
  }

  template<typename Arg0>
  ::bit::stl::hash_t hash_values_impl( Arg0&& arg0 )
  {
    using ::bit::stl::hash_value;

    return hash_value( std::forward<Arg0>(arg0) );
  }

} } } // namespace bit::stl::detail

template<typename...Args>
inline constexpr bit::stl::hash_t bit::stl::hash_values( Args&&...args )
{
  return detail::hash_values_impl( std::forward<Args>(args)... );
}

//-----------------------------------------------------------------------------

namespace bit { namespace stl { namespace detail {

      template<std::size_t> constexpr std::size_t fnv1_prime();
      template<std::size_t> constexpr std::size_t fnv1_offset();

      template<> constexpr std::size_t fnv1_prime<4>(){ return 16777619ul; }
      template<> constexpr std::size_t fnv1_prime<8>(){ return 1099511628211ull; }

      template<> constexpr std::size_t fnv1_offset<4>(){ return 2166136261ul; }
      template<> constexpr std::size_t fnv1_offset<8>(){ return 14695981039346656037ull; }

      template<typename CharT>
      constexpr hash_t string_hash( const CharT* str, std::size_t count ) noexcept;

} } } // namespace bit::stl::detail

template<typename CharT>
inline constexpr bit::stl::hash_t
  bit::stl::hash_string_segment( const CharT* str, std::size_t count )
  noexcept
{
  constexpr auto offset = detail::fnv1_offset<sizeof(std::size_t)>();
  constexpr auto prime  = detail::fnv1_prime<sizeof(std::size_t)>();

  auto result = offset;

  while (count--) {
    result ^= static_cast<std::size_t>(*(str++));
    result *= prime;
  }

  return static_cast<hash_t>(result);
}

template<typename T>
inline bit::stl::hash_t bit::stl::hash_raw( const T& data )
  noexcept
{
  using byte_t = unsigned char;
  auto ptr = reinterpret_cast<const byte_t*>(data);

  return hash_string_segment( ptr, sizeof(T) );
}

//=============================================================================
// class hash
//=============================================================================

template<typename Key>
inline constexpr bit::stl::hash_t
  bit::stl::hash<Key>::operator()( const Key& val )
{
  return hash_value( val );
}

#endif /* BIT_STL_UTILITIES_DETAIL_HASH_INL */
