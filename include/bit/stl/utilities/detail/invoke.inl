#ifndef BIT_STL_UTILITIES_DETAIL_INVOKE_INL
#define BIT_STL_UTILITIES_DETAIL_INVOKE_INL

namespace bit {
  namespace stl {
    template<typename Func, typename... Args>
    inline constexpr auto invoke(Func&& func, Args&&... args)
#ifndef _MSC_VER
      noexcept( noexcept( bit::stl::detail::invoke_impl(std::forward<Func>(func), std::forward<Args>(args)...) ) )
#endif
      -> decltype( detail::invoke_impl(std::forward<Func>(func), std::forward<Args>(args)...) )
    {
      return detail::invoke_impl(std::forward<Func>(func), std::forward<Args>(args)...);
    }
  } // namespace stl
} // namespace bit

#endif /* BIT_STL_UTILITIES_DETAIL_INVOKE_INL */
