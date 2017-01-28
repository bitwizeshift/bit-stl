#ifndef BFSTL_DETAIL_TUPLE_INL
#define BFSTL_DETAIL_TUPLE_INL

namespace bit {

  namespace detail {

    template<typename Func, typename Tuple, std::size_t...Idxs>
    constexpr decltype(auto) apply_impl( Func&& func, Tuple&& tuple, std::index_sequence<Idxs...> )
    {
      return invoke( std::forward<Func>(func), std::get<Idxs>(std::forward<Tuple>(tuple))... );
    }

    template<typename T, typename Tuple, std::size_t...Idxs>
    constexpr T make_from_tuple( Tuple&& tuple, std::index_sequence<Idxs...> )
    {
      return T( std::get<Idxs>(std::forward<Tuple>(tuple))...);
    }

  } // namespace detail

  ///
  template<typename Func, typename Tuple>
  constexpr decltype(auto) apply( Func&& function, Tuple&& tuple )
  {
    return detail::apply_impl( std::forward<Func>(function), std::forward<Tuple>(tuple), std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>() );
  }

  template<typename T, typename Tuple>
  constexpr T make_from_tuple( Tuple&& tuple )
  {
    return detail::make_from_tuple<T>( std::forward<Tuple>(tuple), std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>() );
  }
}

#endif /* BFSTL_DETAIL_TUPLE_INL */