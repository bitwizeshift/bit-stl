#ifndef BIT_STL_DETAIL_DELEGATE_INL
#define BIT_STL_DETAIL_DELEGATE_INL

namespace bit {
  namespace stl {

    //--------------------------------------------------------------------------
    // Constructor
    //--------------------------------------------------------------------------

    template<typename R, typename ... Args>
    constexpr delegate<R(Args...)>::delegate() noexcept
      :  m_delegate_stub(nullptr,nullptr)
    {

    }

    //--------------------------------------------------------------------------
    // Function Binding
    //--------------------------------------------------------------------------

    template<typename R, typename ... Args>
    template<R (*function)(Args...)>
    inline constexpr void delegate<R(Args...)>::bind()
      noexcept
    {
      const auto callback = [](void*, Args...args )
      {
        return function(std::forward<Args>(args)...);
      };
      m_delegate_stub.first  = nullptr;
      m_delegate_stub.second = +callback;
    }

    template<typename R, typename ... Args>
    template<typename C, R (C::*member_function)(Args...)>
    inline constexpr void delegate<R(Args...)>::bind( C* instance )
      noexcept
    {
      const auto callback = [](void* ptr, Args...args )
      {
        return (static_cast<C*>(ptr)->*member_function)(std::forward<Args>(args)...);
      };
      m_delegate_stub.first  = instance;
      m_delegate_stub.second = +callback;
    }

    template<typename R, typename ... Args>
    template<typename C, R (C::*member_function)(Args...) const>
    inline constexpr void delegate<R(Args...)>::bind( const C* instance )
      noexcept
    {
       const auto callback = [](void* ptr, Args...args )
      {
        return (static_cast<const C*>(ptr)->*member_function)(std::forward<Args>(args)...);
      };
      m_delegate_stub.first  = const_cast<C*>(instance); // needed for const
      m_delegate_stub.second = +callback;
    }

    //--------------------------------------------------------------------------
    // Queries
    //--------------------------------------------------------------------------

    template<typename R, typename ... Args>
    inline constexpr bool delegate<R(Args...)>::is_bound()
      const noexcept
    {
      return m_delegate_stub.second != nullptr;
    }

    template<typename R, typename...Args>
    inline constexpr delegate<R(Args...)>::operator bool()
      const noexcept
    {
      return m_delegate_stub.second != nullptr;
    }

    //--------------------------------------------------------------------------
    // Invocation
    //--------------------------------------------------------------------------

    template<typename R, typename ... Args>
    inline constexpr typename delegate<R(Args...)>::return_type
      delegate<R(Args...)>::invoke( Args&&... args )
      const
    {
      BIT_ASSERT( m_delegate_stub.second != nullptr, "Cannot invoke unbound delegate");
      return m_delegate_stub.second( m_delegate_stub.first, std::forward<Args>(args)... );
    }

  } // namespace stl
}  // namespace bit

#endif /* BIT_STL_DETAIL_DELEGATE_INL */
