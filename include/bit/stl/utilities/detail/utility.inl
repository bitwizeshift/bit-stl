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

#endif /* BIT_STL_UTILITIES_DETAIL_UTILITY_INL */
