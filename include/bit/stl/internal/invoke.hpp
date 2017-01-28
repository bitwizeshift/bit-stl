/**
 * \file invoke.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_INTERNAL_INVOKE_HPP
#define BIT_STL_INTERNAL_INVOKE_HPP

#include <type_traits> // for std::is_base_of
#include <utility>     // for std::forward

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
      auto invoke_impl(T Base::*pmf, Derived&& ref, Args&&... args)
        noexcept(noexcept((std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...)))
        -> std::enable_if_t<std::is_function<T>::value &&
                           std::is_base_of<Base, std::decay_t<Derived>>::value,
           decltype((std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...))>
      {
        return (std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...);
      }

      template<typename Base, typename T, typename RefWrap, typename... Args>
      auto invoke_impl(T Base::*pmf, RefWrap&& ref, Args&&... args)
        noexcept(noexcept((ref.get().*pmf)(std::forward<Args>(args)...)))
        -> std::enable_if_t<std::is_function<T>::value &&
                            is_reference_wrapper<std::decay_t<RefWrap>>::value,
           decltype((ref.get().*pmf)(std::forward<Args>(args)...))>

      {
        return (ref.get().*pmf)(std::forward<Args>(args)...);
      }

      template<typename Base, typename T, typename Pointer, typename... Args>
      auto invoke_impl(T Base::*pmf, Pointer&& ptr, Args&&... args)
        noexcept(noexcept(((*std::forward<Pointer>(ptr)).*pmf)(std::forward<Args>(args)...)))
        -> std::enable_if_t<std::is_function<T>::value &&
                            !is_reference_wrapper<std::decay_t<Pointer>>::value &&
                            !std::is_base_of<Base, std::decay_t<Pointer>>::value,
           decltype(((*std::forward<Pointer>(ptr)).*pmf)(std::forward<Args>(args)...))>
      {
        return ((*std::forward<Pointer>(ptr)).*pmf)(std::forward<Args>(args)...);
      }

      template<typename Base, typename T, typename Derived>
      auto invoke_impl(T Base::*pmd, Derived&& ref)
        noexcept(noexcept(std::forward<Derived>(ref).*pmd))
        -> std::enable_if_t<!std::is_function<T>::value &&
                            std::is_base_of<Base, std::decay_t<Derived>>::value,
           decltype(std::forward<Derived>(ref).*pmd)>
      {
        return std::forward<Derived>(ref).*pmd;
      }

      template<typename Base, typename T, typename RefWrap>
      auto invoke_impl(T Base::*pmd, RefWrap&& ref)
        noexcept(noexcept(ref.get().*pmd))
        -> std::enable_if_t<!std::is_function<T>::value &&
                            is_reference_wrapper<std::decay_t<RefWrap>>::value,
           decltype(ref.get().*pmd)>
      {
        return ref.get().*pmd;
      }

      template<typename Base, typename T, typename Pointer>
      auto invoke_impl(T Base::*pmd, Pointer&& ptr)
        noexcept(noexcept((*std::forward<Pointer>(ptr)).*pmd))
        -> std::enable_if_t<!std::is_function<T>::value &&
                            !is_reference_wrapper<std::decay_t<Pointer>>::value &&
                            !std::is_base_of<Base, std::decay_t<Pointer>>::value,
           decltype((*std::forward<Pointer>(ptr)).*pmd)>
      {
        return (*std::forward<Pointer>(ptr)).*pmd;
      }

      template<typename F, typename... Args>
      auto invoke_impl(F&& f, Args&&... args)
          noexcept(noexcept(std::forward<F>(f)(std::forward<Args>(args)...)))
       -> std::enable_if_t<!std::is_member_pointer<std::decay_t<F>>::value,
          decltype(std::forward<F>(f)(std::forward<Args>(args)...))>
      {
        return std::forward<F>(f)(std::forward<Args>(args)...);
      }

    } // namespace detail
  } // namespace stl
} // namespace bit

#endif /* BIT_STL_INTERNAL_INVOKE_HPP */