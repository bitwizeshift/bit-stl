/**
 * \file invoke.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_UTILITIES_INVOKE_HPP
#define BIT_STL_UTILITIES_INVOKE_HPP

#include "detail/invoke.hpp"

#include "../traits/identity.hpp"

#include <utility>     // std::forward
#include <type_traits> // std::declval

namespace bit {
  namespace stl {

    /// \brief Invoke the Callable object \p function with the parameters \p args.
    ///
    /// As by \c INVOKE(std::forward<F>(f), std::forward<Args>(args)...)
    ///
    /// \param function Callable object to be invoked
    /// \param args     arguments to pass to \p function
    template<typename Func, typename... Args>
    constexpr auto invoke(Func&& function, Args&&... args)
#ifndef _MSC_VER
      noexcept( noexcept( detail::invoke_impl(std::forward<Func>(function), std::forward<Args>(args)...) ) )
#endif
      -> decltype( detail::invoke_impl(std::forward<Func>(function), std::forward<Args>(args)...) );


    template<typename F, typename...Types>
    struct invoke_result : identity<decltype(invoke( std::declval<F>(), std::declval<Types>()... ))>{};

    template<typename F, typename...Types>
    using invoke_result_t = typename invoke_result<F,Types...>::type;


    /// \brief Type trait to determine whether \p Fn is invokable with
    ///        \p Args...
    ///
    /// Formally, the expression:
    /// \code
    /// INVOKE( std::declval<Fn>(), std::declval<Args>()... )
    /// \endcode
    /// is well formed
    ///
    /// The result is aliased as \c ::value
    template<typename Fn, typename...Args>
    using is_invocable = detail::is_invocable<Fn,Args...>;

    /// \brief Type-trait helper to retrieve the \c ::value of is_invokable
    template<typename Fn, typename...Args>
    constexpr bool is_invocable_v = is_invocable<Fn,Args...>::value;


//    template<typename R, typename Fn, typename... Types>
//    using is_invocable_r = is_detected_convertible<R,invoke_result_t,Fn,Types...>;
//
//    template<typename R, typename Fn, typename... Types>
//    constexpr bool is_invocable_r_v = is_invocable_r<R,Fn,Types...>::value;

    //------------------------------------------------------------------------

    /// \brief Type trait to determine whether \p Fn is nothrow invokable with
    ///        \p Args...
    ///
    /// Formally, the expression:
    /// \code
    /// INVOKE( std::declval<Fn>(), std::declval<Args>()... )
    /// \endcode
    /// is well formed and is known not to throw
    ///
    /// The result is aliased as \c ::value
    template<typename Fn, typename...Args>
    using is_nothrow_invocable = detail::is_nothrow_invocable<Fn,Args...>;

    /// \brief Type-trait helper to retrieve the \c ::value of is_nothrow_invokable
    template<typename Fn, typename...Args>
    constexpr bool is_nothrow_invocable_v = is_nothrow_invocable<Fn,Args...>::value;

//    template<typename R, typename Fn, typename... Types>
//    using is_nothrow_invocable_r = conjunction<bool_constant<noexcept( detail::INVOKE( std::declval<Fn>(), std::declval<Types>()... ) )>,
//                                               is_invocable_r<R,Fn,Types...>>;
//
//    template<typename R, typename Fn, typename... Types>
//    constexpr bool is_nothrow_invocable_r_v = is_nothrow_invocable_r<R,Fn,Types...>::value;

  } // namespace stl
} // namespace bit

#include "detail/invoke.inl"

#endif /* BIT_STL_UTILITIES_INVOKE_HPP */
