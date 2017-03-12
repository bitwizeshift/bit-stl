#ifndef BIT_STL_DETAIL_DELEGATE_INL
#define BIT_STL_DETAIL_DELEGATE_INL

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------

template<typename R, typename ... Args>
constexpr bit::stl::delegate<R(Args...)>::delegate()
  noexcept
  : m_delegate_stub(nullptr,nullptr)
{

}

//----------------------------------------------------------------------------
// Function Binding
//----------------------------------------------------------------------------

template<typename R, typename ... Args>
template<R (*function)(Args...)>
inline constexpr void
  bit::stl::delegate<R(Args...)>::bind()
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
inline constexpr void
  bit::stl::delegate<R(Args...)>::bind( C* instance )
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
inline constexpr void
  bit::stl::delegate<R(Args...)>::bind( const C* instance )
  noexcept
{
   const auto callback = [](void* ptr, Args...args )
  {
    return (static_cast<const C*>(ptr)->*member_function)(std::forward<Args>(args)...);
  };
  m_delegate_stub.first  = const_cast<C*>(instance); // needed for const
  m_delegate_stub.second = +callback;
}

//----------------------------------------------------------------------------
// Queries
//----------------------------------------------------------------------------

template<typename R, typename ... Args>
inline constexpr bool
  bit::stl::delegate<R(Args...)>::is_bound()
  const noexcept
{
  return m_delegate_stub.second != nullptr;
}

template<typename R, typename...Args>
inline constexpr bit::stl::delegate<R(Args...)>::operator bool()
  const noexcept
{
  return m_delegate_stub.second != nullptr;
}

//----------------------------------------------------------------------------
// Invocation
//----------------------------------------------------------------------------

template<typename R, typename ... Args>
template<typename...Arguments,typename>
inline constexpr typename bit::stl::delegate<R(Args...)>::return_type
  bit::stl::delegate<R(Args...)>::invoke( Arguments&&... args )
  const
{
  BIT_ASSERT( m_delegate_stub.second != nullptr, "delegate::invoke: cannot invoke unbound delegate");

  return m_delegate_stub.second( m_delegate_stub.first, std::forward<Arguments>(args)... );
}

template<typename R, typename ... Args>
template<typename...Arguments,typename>
inline constexpr typename bit::stl::delegate<R(Args...)>::return_type
  bit::stl::delegate<R(Args...)>::operator()( Arguments&&... args )
  const
{
  BIT_ASSERT( m_delegate_stub.second != nullptr, "delegate::operator(): cannot invoke unbound delegate");

  return m_delegate_stub.second( m_delegate_stub.first, std::forward<Arguments>(args)... );
}

#endif /* BIT_STL_DETAIL_DELEGATE_INL */
