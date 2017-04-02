#ifndef BIT_STL_DETAIL_ARRAY_INL
#define BIT_STL_DETAIL_ARRAY_INL

template<typename T, typename...Args>
inline constexpr bit::stl::detail::array_return_type_t<T,Args...>
  bit::stl::make_array( Args&&...args )
  noexcept
{
  return { std::forward<Args>(args)... };
}

#endif /* BIT_STL_DETAIL_ARRAY_INL */
