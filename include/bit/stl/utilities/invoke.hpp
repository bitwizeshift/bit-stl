/**
 * \file invoke.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_UTILITIES_INVOKE_HPP
#define BIT_STL_UTILITIES_INVOKE_HPP

#include <utility> // std::forward

#include "detail/invoke.hpp" // detail::INVOKE

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
      noexcept( noexcept( detail::INVOKE(std::forward<Func>(function), std::forward<Args>(args)...) ) )
      -> decltype( detail::INVOKE(std::forward<Func>(function), std::forward<Args>(args)...) );

  } // namespace stl
} // namespace bit

#include "detail/invoke.inl"

#endif /* BIT_STL_UTILITIES_INVOKE_HPP */
