/**
 * \file delegate.hpp
 *
 * \brief This file contains the definition for delegates
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_UTILITIES_DELEGATE_HPP
#define BIT_STL_UTILITIES_DELEGATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

// bit::stl local libraries
#include "stddef.hpp" //
#include "assert.hpp" // BIT_ASSERT
#include "invoke.hpp" // is_invocable

#include <type_traits> // std::enable_if
#include <utility>     // std::forward, std::move

namespace bit {
  namespace stl {

    ////////////////////////////////////////////////////////////////////////////
    /// \brief This class is for a lightweight way of managing function callbacks
    ///        without requiring heap allocations.
    ///
    /// The syntax is a little off as a result, requiring a call to
    /// Delegate::bind.
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
    template<typename Fn> class delegate;

    template<typename R, typename...Types>
    class delegate<R(Types...)> final
    {
      //-----------------------------------------------------------------------------
      // Public Member Types
      //-----------------------------------------------------------------------------
    public:

      using return_type        = R;
      using free_function_type = return_type (*)(Types...);

      template<class C>
      using member_function_type = return_type (C::*)(Types...);

      template<class C>
      using const_member_function_type = return_type (C::*)(Types...) const;

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

      /// \{
      /// \brief Binds a member function to this delegate
      ///
      /// \tparam C The type of instance to bind
      /// \tparam member_function The pointer to member function to bind
      /// \param instance the instance to call the member function on
      template <class C, member_function_type<C> member_function>
      constexpr void bind( C* instance ) noexcept;

      template <class C, member_function_type<C> member_function>
      constexpr void bind( C& instance ) noexcept;
      /// \}

      /// \{
      /// \brief Binds a const member function to this delegate
      ///
      /// \tparam C the type of instance to bind
      /// \tparam member_function The pointer to member function to bind
      /// \param instance the instance to call the member function on
      template <class C, const_member_function_type<C> member_function>
      constexpr void bind( const C* instance ) noexcept;

      template <class C, const_member_function_type<C> member_function>
      constexpr void bind( const C& instance ) noexcept;

      template <class C, const_member_function_type<C> member_function>
      constexpr void cbind( const C* instance ) noexcept;

      template <class C, const_member_function_type<C> member_function>
      constexpr void cbind( const C& instance ) noexcept;
      /// \}

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
      template<typename...Args, typename = std::enable_if_t<is_invocable<R(Types...),Args...>::value>>
      constexpr return_type invoke( Args&&...args ) const;

      /// \copydoc delegate::invoke( Args&&... )
      template<typename...Args, typename = std::enable_if_t<is_invocable<R(Types...),Args...>::value>>
      constexpr return_type operator()( Args&&...args ) const;

      //-----------------------------------------------------------------------------
      // Private Member Types
      //-----------------------------------------------------------------------------
    private:

      using internal_function_type = return_type(*)(void*, Types...);
      using stub_type              = std::pair<void*, internal_function_type>;

      //-----------------------------------------------------------------------------
      // Private Members
      //-----------------------------------------------------------------------------
    private:

      stub_type m_delegate_stub; ///< The internal stub for this delegate

      template<typename Fn>
      friend bool operator==(const delegate<Fn>& lhs, const delegate<Fn>& rhs);

      template<typename Fn>
      friend bool operator<(const delegate& lhs, const delegate& rhs);
    };

    template<typename Fn>
    bool operator==(const delegate<Fn>& lhs, const delegate<Fn>& rhs);
    template<typename Fn>
    bool operator!=(const delegate<Fn>& lhs, const delegate<Fn>& rhs);
    template<typename Fn>
    bool operator<(const delegate<Fn>& lhs, const delegate<Fn>& rhs);
    template<typename Fn>
    bool operator>(const delegate<Fn>& lhs, const delegate<Fn>& rhs);
    template<typename Fn>
    bool operator<=(const delegate<Fn>& lhs, const delegate<Fn>& rhs);
    template<typename Fn>
    bool operator>=(const delegate<Fn>& lhs, const delegate<Fn>& rhs);

    //------------------------------------------------------------------------
    // Make Utilities
    //------------------------------------------------------------------------
//
//    template<typename Sig, function_t<Sig> function>
//    delegate<Sig> make_delegate() noexcept;
//
//    template<typename T, typename Sig, member_function_t<T,Sig> member_function>
//    delegate<Sig> make_delegate( T& instance ) noexcept;
//
//    template<typename T, typename Sig, member_function_t<T,Sig> member_function>
//    delegate<Sig> make_delegate( T* instance ) noexcept;

#if __cplusplus >= 201703L

      template<auto Fn>
      auto make_delegate();

      template<auto Fn, typename T>
      auto make_delegate( T* );

#endif

  } // namespace stl
}  // namespace bit

#include "detail/delegate.inl"

#endif /* BIT_STL_UTILITIES_DELEGATE_HPP */
