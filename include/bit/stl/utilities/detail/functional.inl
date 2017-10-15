#ifndef BIT_STL_DETAIL_FUNCTIONAL_INL
#define BIT_STL_DETAIL_FUNCTIONAL_INL

namespace bit {
  namespace stl {
    template<typename Func, typename... Args>
    auto invoke(Func&& func, Args&&... args)
      noexcept( noexcept( detail::INVOKE(std::forward<Func>(func), std::forward<Args>(args)...) ) )
      -> decltype( detail::INVOKE(std::forward<Func>(func), std::forward<Args>(args)...) )
    {
      return detail::INVOKE(std::forward<Func>(func), std::forward<Args>(args)...);
    }
  } // namespace stl
} // namespace bit

#endif /* BIT_STL_DETAIL_FUNCTIONAL_INL */
