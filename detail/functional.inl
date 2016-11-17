#ifndef BFSTL_DETAIL_FUNCTIONAL_INL
#define BFSTL_DETAIL_FUNCTIONAL_INL

namespace bit {

  template<typename Func, typename... Args>
  auto invoke(Func&& func, Args&&... args)
    noexcept( noexcept( detail::invoke_impl(std::forward<Func>(func), std::forward<Args>(args)...) ) )
    -> decltype( detail::invoke_impl(std::forward<Func>(func), std::forward<Args>(args)...) )
  {
    return detail::invoke_impl(std::forward<Func>(func), std::forward<Args>(args)...);
  }

} // namespace bit

#endif /* BFSTL_DETAIL_FUNCTIONAL_INL */
