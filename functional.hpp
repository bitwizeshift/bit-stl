/**
 * \file functional.hpp
 *
 * \brief This header contains c++17 extensions of the functional library
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_FUNCTIONAL_HPP
#define BIT_STL_FUNCTIONAL_HPP

// std library
#include <type_traits> // for std::is_base_of
#include <utility>     // for std::forward
#include <functional>  // for std::function

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

    /// \brief Invoke the Callable object \p function with the parameters \p args.
    ///
    /// As by \c INVOKE(std::forward<F>(f), std::forward<Args>(args)...)
    ///
    /// \param function Callable object to be invoked
    /// \param args     arguments to pass to \p function
    template<typename Func, typename... Args>
    auto invoke(Func&& function, Args&&... args)
      noexcept( noexcept( detail::invoke_impl(std::forward<Func>(function), std::forward<Args>(args)...) ) )
      -> decltype( detail::invoke_impl(std::forward<Func>(function), std::forward<Args>(args)...) );

    namespace detail {
      template<typename T, typename Fn>
      class capture_impl
      {
      public:
          capture_impl( T&& capture, Fn&& func );

      public:

          template<typename...Args>
          typename std::result_of<Fn>::type operator()( Args&&...args );

          template<typename...Args>
          typename std::result_of<Fn>::type operator()( Args&&...args ) const;

      private:

          T  m_capture;
          Fn m_function;
      };

      template<typename T, typename Fn>
      capture_impl<T,Fn>::capture_impl( T&& capture, Fn&& func )
        : m_capture{ std::forward<T>(capture) },
          m_function{std::forward<Fn>(func)}
      {

      }

      template<typename T, typename Fn>
      template<typename...Args>
      typename std::result_of<Fn>::type capture_impl<T,Fn>::operator()( Args&&...args )
      {
          return m_function( m_capture, std::forward<Args>(args)... );
      }

      template<typename T, typename Fn>
      template<typename...Args>
      typename std::result_of<Fn>::type capture_impl<T,Fn>::operator()( Args&&...args )
        const
      {
          return m_function( m_capture, std::forward<Args>(args)... );
      }

    }

    template<typename T, typename Fn>
    detail::capture_impl<T,Fn> capture(T&& value, Fn&& function )
    {
        return detail::capture_impl<T,Fn>( std::forward<T>(value), std::forward<Fn>(function) );
    }
  } // namespace stl
} // namespace bit

#include "detail/functional.inl"

#endif /* BIT_STL_FUNCTIONAL_HPP */
