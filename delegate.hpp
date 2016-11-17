/**
 * \file delegate.hpp
 *
 * \brief This file contains the definition for delegates
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_DELEGATE_HPP
#define BIT_DELEGATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

// bit::core libraries
#include "config.hpp"
#include "assert.hpp"
#include "functional.hpp"

#include <utility>

namespace bit {

  ////////////////////////////////////////////////////////////////////////////
  /// \class bit::delegate
  ///
  /// \brief This class is for a lightweight way of managing function callbacks
  ///        without requiring heap allocations.
  ///
  /// The syntax is a little off as a result, requiring a call to
  /// #Delegate::bind.
  ///
  /// Example
  /// \code
  /// Delegate<void()> delegate;
  /// T       t;
  /// const T ct;
  ///
  /// delegate.bind<&foo>();           // bind free function
  /// delegate.bind<T,&T::foo>( &t );  // bind member functions
  /// delegate.bind<T,&T::foo>( &ct ); // bind const member function
  /// \endcode
  ///
  /// \tparam Function signature and return type
  ////////////////////////////////////////////////////////////////////////////
  template<typename Function> class delegate;

  template<typename R, typename...Args>
  class delegate<R(Args...)> final
  {
    //-----------------------------------------------------------------------------
    // Public Member Types
    //-----------------------------------------------------------------------------
  public:

    using return_type        = R;
    using free_function_type = return_type (*)(Args...);

    template<class C>
    using member_function_type = return_type (C::*)(Args...);

    template<class C>
    using const_member_function_type = return_type (C::*)(Args...) const;

    //-----------------------------------------------------------------------------
    // Constructor / Destructor
    //-----------------------------------------------------------------------------
  public:

    /// \brief Constructs an unbound delegate
    constexpr delegate() noexcept;

    //-----------------------------------------------------------------------------
    // Function Binding
    //-----------------------------------------------------------------------------
  public:

    /// \brief Binds a free function to this delegate
    ///
    /// \tparam function the free-function type to bind
    /// \tparam function the function pointer for the delegate
    template<free_function_type function>
    constexpr void bind() noexcept;

    /// \brief Binds a member function to this delegate
    ///
    /// \tparam C The type of instance to bind
    /// \tparam member_function The pointer to member function to bind
    /// \param instance the instance to call the member function on
    template <class C, member_function_type<C> member_function>
    constexpr void bind( C* instance ) noexcept;

    /// \brief Binds a const member function to this delegate
    ///
    /// \tparam C the type of instance to bind
    /// \tparam member_function The pointer to member function to bind
    /// \param instance the instance to call the member function on
    template <class C, const_member_function_type<C> member_function>
    constexpr void bind( const C* instance ) noexcept;

    //-----------------------------------------------------------------------------
    // Queries
    //-----------------------------------------------------------------------------
  public:

    /// \brief Is this Delegate bound?
    ///
    /// \return \c true if the delegate is bound
    constexpr bool is_bound() const noexcept;

    /// \brief Returns true if this delegate is bound
    constexpr explicit operator bool() const noexcept;

    //-----------------------------------------------------------------------------
    // Invocation
    //-----------------------------------------------------------------------------
  public:

    /// \brief Invokes the bound function
    ///
    /// \param args the arguments for the invokation
    /// \return the return value for the invoked delegate
    constexpr return_type invoke( Args&&...args ) const;

    //-----------------------------------------------------------------------------
    // Private Member Types
    //-----------------------------------------------------------------------------
  private:

    using internal_function_type = return_type (*)(void*, Args...);
    using stub_type              = std::pair<void*, internal_function_type>;

    //-----------------------------------------------------------------------------
    // Private Members
    //-----------------------------------------------------------------------------
  private:

    stub_type m_delegate_stub; ///< The internal stub for this delegate

  };

}  // namespace bit

#include "detail/delegate.inl"

#endif /* BIT_DELEGATE_HPP */
