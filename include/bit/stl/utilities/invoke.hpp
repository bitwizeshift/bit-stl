/*****************************************************************************
 * \file
 * \brief This header contains the definition for the INVOKE family of
 *        utilities, including type-traits
 *****************************************************************************/

/*
  The MIT License (MIT)

  Bit Standard Template Library.
  https://github.com/bitwizeshift/bit-stl

  Copyright (c) 2018 Matthew Rodusek

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#ifndef BIT_STL_UTILITIES_INVOKE_HPP
#define BIT_STL_UTILITIES_INVOKE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "detail/invoke.hpp"

#include "../traits/composition/identity.hpp"

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
