/*****************************************************************************
 * \file
 * \brief This provides the definition for the standards meta-function INVOKE
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 *****************************************************************************/
#ifndef BIT_STL_UTILITIES_DETAIL_INVOKE_HPP
#define BIT_STL_UTILITIES_DETAIL_INVOKE_HPP

#include <type_traits> // for std::is_base_of
#include <utility>     // for std::forward
#include <functional>  // std::reference_wrapper

#include <type_traits> // std::true_type, std::false_type

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T>
      struct is_reference_wrapper : std::false_type {};

      template<typename U>
      struct is_reference_wrapper<std::reference_wrapper<U>> : std::true_type {};

      template<typename T>
      constexpr bool is_reference_wrapper_v = is_reference_wrapper<T>::value;

      template<typename Base, typename T, typename Derived, typename... Args>
      inline constexpr auto invoke_impl(T Base::*pmf, Derived&& ref, Args&&... args)
        noexcept(noexcept((std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...)))
        -> std::enable_if_t<std::is_function<T>::value &&
                            std::is_base_of<Base, std::decay_t<Derived>>::value,
           decltype((std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...))>
      {
        return (std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...);
      }

      template<typename Base, typename T, typename RefWrap, typename... Args>
      inline constexpr auto invoke_impl(T Base::*pmf, RefWrap&& ref, Args&&... args)
        noexcept(noexcept((ref.get().*pmf)(std::forward<Args>(args)...)))
        -> std::enable_if_t<std::is_function<T>::value &&
                            is_reference_wrapper<std::decay_t<RefWrap>>::value,
           decltype((ref.get().*pmf)(std::forward<Args>(args)...))>

      {
        return (ref.get().*pmf)(std::forward<Args>(args)...);
      }

      template<typename Base, typename T, typename Pointer, typename... Args>
      inline constexpr auto invoke_impl(T Base::*pmf, Pointer&& ptr, Args&&... args)
        noexcept(noexcept(((*std::forward<Pointer>(ptr)).*pmf)(std::forward<Args>(args)...)))
        -> std::enable_if_t<std::is_function<T>::value &&
                            !is_reference_wrapper<std::decay_t<Pointer>>::value &&
                            !std::is_base_of<Base, std::decay_t<Pointer>>::value,
           decltype(((*std::forward<Pointer>(ptr)).*pmf)(std::forward<Args>(args)...))>
      {
        return ((*std::forward<Pointer>(ptr)).*pmf)(std::forward<Args>(args)...);
      }

      template<typename Base, typename T, typename Derived>
      inline constexpr auto invoke_impl(T Base::*pmd, Derived&& ref)
        noexcept(noexcept(std::forward<Derived>(ref).*pmd))
        -> std::enable_if_t<!std::is_function<T>::value &&
                            std::is_base_of<Base, std::decay_t<Derived>>::value,
           decltype(std::forward<Derived>(ref).*pmd)>
      {
        return std::forward<Derived>(ref).*pmd;
      }

      template<typename Base, typename T, typename RefWrap>
      inline constexpr auto invoke_impl(T Base::*pmd, RefWrap&& ref)
        noexcept(noexcept(ref.get().*pmd))
        -> std::enable_if_t<!std::is_function<T>::value &&
                            is_reference_wrapper<std::decay_t<RefWrap>>::value,
           decltype(ref.get().*pmd)>
      {
        return ref.get().*pmd;
      }

      template<typename Base, typename T, typename Pointer>
      inline constexpr auto invoke_impl(T Base::*pmd, Pointer&& ptr)
        noexcept(noexcept((*std::forward<Pointer>(ptr)).*pmd))
        -> std::enable_if_t<!std::is_function<T>::value &&
                            !is_reference_wrapper<std::decay_t<Pointer>>::value &&
                            !std::is_base_of<Base, std::decay_t<Pointer>>::value,
           decltype((*std::forward<Pointer>(ptr)).*pmd)>
      {
        return (*std::forward<Pointer>(ptr)).*pmd;
      }

      template<typename F, typename... Args>
      inline constexpr auto invoke_impl(F&& f, Args&&... args)
          noexcept(noexcept(std::forward<F>(f)(std::forward<Args>(args)...)))
       -> std::enable_if_t<!std::is_member_pointer<std::decay_t<F>>::value,
          decltype(std::forward<F>(f)(std::forward<Args>(args)...))>
      {
        return std::forward<F>(f)(std::forward<Args>(args)...);
      }

      //=======================================================================
      // is_invokable
      //=======================================================================

      template<typename Fn, typename...Args>
      struct is_invocable
      {
        template<typename Fn2, typename...Args2>
        static auto test( Fn2&&, Args2&&... )
          -> decltype(invoke_impl(std::declval<Fn2>(), std::declval<Args2>()...), std::true_type{});

        static auto test(...)
          -> std::false_type;

        static constexpr bool value =
          decltype(test(std::declval<Fn>(), std::declval<Args>()...))::value;
      };

      //=======================================================================
      // is_nothrow_invokable
      //=======================================================================

      template<typename Fn, typename...Args>
      struct is_nothrow_invocable
      {
        template<typename Fn2, typename...Args2>
        static auto test( Fn2&&, Args2&&... )
          -> decltype(invoke_impl(std::declval<Fn2>(), std::declval<Args2>()...),
                      std::integral_constant<bool,noexcept(invoke_impl(std::declval<Fn2>(), std::declval<Args2>()...))>{});

        static auto test(...)
          -> std::false_type;

        static constexpr bool value =
          decltype(test(std::declval<Fn>(), std::declval<Args>()...))::value;
      };

    } // namespace detail
  } // namespace stl
} // namespace bit

#endif /* BIT_STL_UTILITIES_DETAIL_INVOKE_HPP */
