#ifndef BIT_STL_UTILITIES_DETAIL_TUPLE_UTILITIES_INL
#define BIT_STL_UTILITIES_DETAIL_TUPLE_UTILITIES_INL

namespace bit { namespace stl { namespace detail {
  template<typename T>
  struct adl_get_protector { static constexpr bool stop = false; };
} } } // namespace bit::stl::detail

template<typename T, typename Tuple>
inline void bit::stl::adl::get( Tuple&& )
{
  static_assert( detail::adl_get_protector<Tuple>::stop,
                 "adl::get must not be used" );
}

template<std::size_t, typename Tuple>
inline void bit::stl::adl::get( Tuple&& )
{
  static_assert( detail::adl_get_protector<Tuple>::stop,
                 "adl::get must not be used" );
}

template<std::size_t Idx, typename Tuple>
decltype(auto) bit::stl::adl_get( Tuple&& tuple )
{
  using ::bit::stl::adl::get;

  return get<Idx>( std::forward<Tuple>(tuple) );
}

template<typename T, typename Tuple>
decltype(auto) bit::stl::adl_get( Tuple&& tuple )
{
  using ::bit::stl::adl::get;

  return get<T>( std::forward<Tuple>(tuple) );
}

namespace bit { namespace stl { namespace detail {
  template<typename Func, typename Tuple, size_t...Idxs>
  constexpr decltype(auto) apply_impl( Func&& func, Tuple&& tuple, std::index_sequence<Idxs...> )
  {
    using ::bit::stl::adl::get;

    return invoke( std::forward<Func>(func), get<Idxs>(std::forward<Tuple>(tuple))... );
  }

  template<typename T, typename Tuple, size_t...Idxs>
  constexpr T make_from_tuple( Tuple&& tuple, std::index_sequence<Idxs...> )
  {
    using ::bit::stl::adl::get;

    return T( get<Idxs>(std::forward<Tuple>(tuple))...);
  }
} } } // namespace bit::stl::detail

template<typename Func, typename Tuple>
constexpr decltype(auto) bit::stl::apply( Func&& function, Tuple&& tuple )
{
  return detail::apply_impl( std::forward<Func>(function), std::forward<Tuple>(tuple), std::make_index_sequence<tuple_size<std::decay_t<Tuple>>::value>() );
}

template<typename T, typename Tuple>
constexpr T bit::stl::make_from_tuple( Tuple&& tuple )
{
  return detail::make_from_tuple<T>( std::forward<Tuple>(tuple), std::make_index_sequence<tuple_size<std::decay_t<Tuple>>::value>() );
}

#endif /* BIT_STL_UTILITIES_DETAIL_TUPLE_UTILITIES_INL */
