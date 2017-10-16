#ifndef BIT_STL_UTILITIES_DETAIL_UTILITY_INL
#define BIT_STL_UTILITIES_DETAIL_UTILITY_INL

template<typename T>
inline constexpr decltype(auto) bit::stl::fwd(T&& x)
  noexcept
{
  return std::forward<typename std::remove_reference<T>::type>( x );
}

template<typename T>
inline constexpr decltype(auto) bit::stl::decay_forward(T&& x) noexcept
{
  using type = match_ref_qualifiers_t<match_cv_qualifiers_t<std::decay_t<T>,T>,T>;
  return static_cast<type>(x);
}

//----------------------------------------------------------------------------
// Final Act
//----------------------------------------------------------------------------

template<typename Func>
inline constexpr bit::stl::final_act<Func>::final_act( Func&& function )
  : m_action( std::forward<Func>(function) ),
    m_will_invoke(true)
{

}

template<typename Func>
inline constexpr bit::stl::final_act<Func>::final_act( final_act&& other )
  : m_action( std::move(other.m_action) ),
    m_will_invoke(other.m_will_invoke)
{
  other.m_will_invoke = false;
}

template<typename Func>
inline bit::stl::final_act<Func>&
  bit::stl::final_act<Func>::operator = ( final_act&& other )
{
  m_action      = std::move(other.m_action);
  m_will_invoke = other.m_will_invoke;

  other.m_will_invoke = false;
}

template<typename Func>
inline bit::stl::final_act<Func>::~final_act()
{
  if(m_will_invoke)
  {
    m_action();
  }
}

template<typename Func>
void bit::stl::final_act<Func>::cancel() noexcept
{
  m_will_invoke = false;
}

//----------------------------------------------------------------------------

template<typename Func>
inline constexpr bit::stl::final_act<Func>
  bit::stl::finally( Func&& function )
  noexcept
{
  return final_act<Func>( std::forward<Func>(function) );
}

//----------------------------------------------------------------------------
// Indexing
//----------------------------------------------------------------------------

template<typename T, std::size_t N>
constexpr T& bit::stl::at( T (&array)[N], std::size_t n )
{
  if(n >= N) throw std::out_of_range("at: index out of range");
  return array[n];
}

template<typename Container, typename Key, typename>
constexpr decltype(auto) bit::stl::at( Container& container, Key&& key )
{
  return container.at( std::forward<Key>(key) );
}

//----------------------------------------------------------------------------
// Hashing Utilities
//----------------------------------------------------------------------------

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

//----------------------------------------------------------------------------
// Hashing Calculations
//----------------------------------------------------------------------------

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

namespace bit {
  namespace stl {
    namespace detail {

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

    } // namespace detail
  } // namespace stl
} // namespace bit


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

//----------------------------------------------------------------------------

template<typename Key>
inline constexpr std::size_t
  bit::stl::hash<Key>::operator()( const Key& val )
{
  return hash_value( val );
}

//----------------------------------------------------------------------------
// Tuple Applications
//----------------------------------------------------------------------------

namespace bit {
  namespace stl {
    namespace detail {

      template <typename T, typename Tuple, std::size_t... I>
      constexpr T make_from_tuple_impl( Tuple&& t, std::index_sequence<I...> )
      {
        return T(std::get<I>(std::forward<Tuple>(t))...);
      }

      template <typename F, typename Tuple, std::size_t... I>
      constexpr decltype(auto) apply_impl( F&& f, Tuple&& t, std::index_sequence<I...> )
      {
        return invoke(std::forward<F>(f), std::get<I>(std::forward<Tuple>(t))...);
      }

    } // namespace detail
  } // namespace stl
} // namespace bit


template <typename T, typename Tuple>
inline constexpr T bit::stl::make_from_tuple( Tuple&& t )
{
    return detail::make_from_tuple_impl<T>(
        std::forward<Tuple>(t),
        std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{}
    );
}

template <typename F, typename Tuple>
inline constexpr decltype(auto) bit::stl::apply( F&& f, Tuple&& t )
{
    return detail::apply_impl(
        std::forward<F>(f),
        std::forward<Tuple>(t),
        std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{}
    );
}

template<typename Container, bit::stl::underlying_container_type_t<Container>*>
bit::stl::underlying_container_type_t<Container>&
  bit::stl::get_underlying_container( Container& container )
{
  struct I : private Container {
    static decltype(auto) get( Container& container )
    {
      return (container.*&I::c);
    }
  };

  return I::get( container );
}

//template<typename T0, typename...Tn>
//struct bit::stl::detail::for_each_type_impl<bit::stl::type_list<T0,Tn...>>
//{
//    template<typename Functor, typename...Args>
//    static void invoke( Functor&& functor, Args&&...args )
//    {
//      std::forward<Functor>(functor).template operator()<T0>( std::forward<Args>(args)... );
//
//      for_each_type_impl<type_list<Tn...>>::invoke( std::forward<Functor>(functor), std::forward<Args>(args)... );
//    }
//};
//
//template<typename...Ts, typename...Tn>
//struct bit::stl::detail::for_each_type_impl<bit::stl::type_list<bit::stl::type_list<Ts...>,Tn...>>
//{
//  template<typename Functor, typename...Args>
//  static void invoke( Functor&& functor, Args&&...args )
//  {
//    std::forward<Functor>(functor).template operator()<Ts...>( std::forward<Args>(args)... );
//
//    for_each_type_impl<type_list<Tn...>>::invoke( std::forward<Functor>(functor), std::forward<Args>(args)... );
//  }
//};
//
//template<typename T0>
//struct bit::stl::detail::for_each_type_impl<bit::stl::type_list<T0>>
//{
//  template<typename Functor, typename...Args>
//  static void invoke( Functor&& functor, Args&&...args )
//  {
//    std::forward<Functor>(functor).template operator()<T0>( std::forward<Args>(args)... );
//  }
//};
//
//template<typename...Ts>
//struct bit::stl::detail::for_each_type_impl<bit::stl::type_list<Ts...>>
//{
//  template<typename Functor, typename...Args>
//  static void invoke( Functor&& functor, Args&&...args )
//  {
//    std::forward<Functor>(functor).template operator()<Ts...>( std::forward<Args>(args)... );
//  }
//};
//
//template<typename TypeList, typename Functor, typename...Args>
//void bit::stl::for_each_type( Functor&& functor, Args&&...args )
//{
//  detail::for_each_type_impl<TypeList>::invoke( std::forward<Functor>(functor), std::forward<Args>(args)... );
//}

#endif /* BIT_STL_UTILITIES_DETAIL_UTILITY_INL */