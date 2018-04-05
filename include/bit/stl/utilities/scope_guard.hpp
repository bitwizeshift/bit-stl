/*****************************************************************************
 * \file
 * \brief This header contains RAII guards for executing functions at scope
 *        exit.
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

#ifndef BIT_STL_UTILITIES_SCOPE_GUARD_HPP
#define BIT_STL_UTILITIES_SCOPE_GUARD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "macros.hpp" // BIT_JOIN

#include <type_traits> // std::decay_t, std::is_nothrow_move_constructible
#include <utility>     // std::move
#include <exception>   // std::uncaught_exception/std::uncaught_exceptions

namespace bit {
  namespace stl {

    //=========================================================================
    // scope_guard
    //=========================================================================

    ///////////////////////////////////////////////////////////////////////////
    /// \brief This class leverages RAII to perform cleanup actions at the end
    ///        of a scope
    ///
    /// This is guaranteed to run the action, even if an exception is thrown
    ///////////////////////////////////////////////////////////////////////////
    template<typename Fn>
    class scope_guard
    {
      //-----------------------------------------------------------------------
      // Public Member Types
      //-----------------------------------------------------------------------
    public:

      enum class scope : char
      {
        cancelled     = 0x0, ///< Don't execute
        on_clean_exit = 0x1, ///< Execute on clean
        on_error_exit = 0x2, ///< Execute on error
        on_exit       = 0x4, ///< Execute on either clean or error
      };

      //-----------------------------------------------------------------------
      // Constructors / Destructor / Assignment
      //-----------------------------------------------------------------------
    public:

      /// \brief Constructs an action to perform on end-of-scope
      ///
      /// \param scope the time to execute the scope_guard
      /// \param function The function to call at the end
      constexpr scope_guard( scope scope, Fn function )
        noexcept(std::is_nothrow_move_constructible<Fn>::value);

      /// \brief Move-constructs a final act to perform on end-of-scope
      ///
      /// \param other the other act to move
      constexpr scope_guard( scope_guard&& other )
        noexcept(std::is_nothrow_move_constructible<Fn>::value);

      // Disallow copy-construction
      scope_guard( const scope_guard& ) = delete;

      //-----------------------------------------------------------------------

      /// \brief Destroys the final act, invoking the action
      ~scope_guard();

      //-----------------------------------------------------------------------

      /// \brief Move-assigns a final act to perform an end-of-scope
      ///
      /// \param other the other act to move
      scope_guard& operator=( scope_guard&& other )
        noexcept(std::is_nothrow_move_assignable<Fn>::value);

      // Disallow copy-assignment
      scope_guard& operator=( const scope_guard& ) = delete;

      //-----------------------------------------------------------------------
      // Modifiers
      //-----------------------------------------------------------------------
    public:

      /// \brief Cancels the final act from occurring
      void cancel() noexcept;


      //-----------------------------------------------------------------------
      // Private Member Function
      //-----------------------------------------------------------------------
    private:

        Fn    m_action; ///< The action to perform
        scope m_scope;  ///< When to invoke the scope guard
    };

    //=========================================================================
    // Free Functions
    //=========================================================================

    //-------------------------------------------------------------------------
    // Utilities
    //-------------------------------------------------------------------------

    /// \brief Creates a scope guard that executes at the end of the scope
    ///
    /// \param fn the function to execute when a scope is exited
    template<typename Fn>
    constexpr scope_guard<std::decay_t<Fn>> on_scope_exit( Fn&& fn );

    /// \brief Creates a scope guard that executes at the end of the scope only
    ///        if an exception has been thrown
    ///
    /// \param fn the function to execute when a scope is exited by error
    template<typename Fn>
    constexpr scope_guard<std::decay_t<Fn>> on_scope_error_exit( Fn&& fn );

    /// \brief Creates a scope guard that executes at the end of the scope only
    ///        if no exception has propagated
    ///
    /// \param fn the function to execute when a scope is without error
    template<typename Fn>
    constexpr scope_guard<std::decay_t<Fn>> on_scope_clean_exit( Fn&& fn );

  } // namespace stl
} // namespace bit

#ifdef __COUNTER__
# define BIT_ON_SCOPE_EXIT(fn) auto BIT_JOIN(BIT_JOIN(scope_guard__on_exit__,__COUNTER__),__) = ::bit::stl::on_scope_exit(fn);
#else
# define BIT_ON_SCOPE_EXIT(fn) auto BIT_JOIN(BIT_JOIN(scope_guard__on_exit__,__COUNTER__),__) = ::bit::stl::on_scope_exit(fn);
#endif

#ifdef __COUNTER__
# define BIT_ON_SCOPE_ERROR_EXIT(fn) auto BIT_JOIN(BIT_JOIN(scope_guard__on_error_exit__,__COUNTER__),__) = ::bit::stl::on_scope_error_exit(fn);
#else
# define BIT_ON_SCOPE_ERROR_EXIT(fn) auto BIT_JOIN(BIT_JOIN(scope_guard__on_error_exit__,__COUNTER__),__) = ::bit::stl::on_scope_error_exit(fn);
#endif

#ifdef __COUNTER__
# define BIT_ON_SCOPE_CLEAN_EXIT(fn) auto BIT_JOIN(BIT_JOIN(scope_guard__on_clean_exit__,__COUNTER__),__) = ::bit::stl::on_scope_clean_exit(fn);
#else
# define BIT_ON_SCOPE_CLEAN_EXIT(fn) auto BIT_JOIN(BIT_JOIN(scope_guard__on_clean_exit__,__COUNTER__),__) = ::bit::stl::on_scope_clean_exit(fn);
#endif

#include "detail/scope_guard.inl"

#endif /* BIT_STL_UTILITIES_SCOPE_GUARD_HPP */
