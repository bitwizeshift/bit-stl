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
#include <functional>  // for std::function

#include "detail/invoke.hpp"

namespace bit {
  namespace stl {

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

  } // namespace stl
} // namespace bit

#include "detail/functional.inl"

#endif /* BIT_STL_FUNCTIONAL_HPP */
