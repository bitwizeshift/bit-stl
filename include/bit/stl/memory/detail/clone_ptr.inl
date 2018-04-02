#ifndef BIT_STL_MEMORY_DETAIL_CLONE_PTR_INL
#define BIT_STL_MEMORY_DETAIL_CLONE_PTR_INL


//============================================================================
// detail::clone_ptr_pointer
//============================================================================

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------

template<typename T, typename Deleter, typename Allocator>
bit::stl::detail::clone_ptr_pointer<T,Deleter,Allocator>
  ::clone_ptr_pointer( T* pointer, const Deleter& deleter, const Allocator& allocator )
  : m_storage( pointer, deleter, allocator )
{

}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------

template<typename T, typename Deleter, typename Allocator>
void* bit::stl::detail::clone_ptr_pointer<T,Deleter,Allocator>
  ::get_deleter( const std::type_info& info )
  noexcept
{
  if( typeid(Deleter) == info ) {
    return std::addressof(m_storage.second().second());
  }
  return nullptr;
}

template<typename T, typename Deleter, typename Allocator>
bit::stl::detail::clone_ptr_base*
  bit::stl::detail::clone_ptr_pointer<T,Deleter,Allocator>::clone()
{
  using control_block = detail::clone_ptr_emplace<T,Allocator>;
  using alloc_traits  = typename std::allocator_traits<Allocator>::template rebind_traits<control_block>;
  using allocator     = typename alloc_traits::allocator_type;
  using destructor    = allocator_deleter<allocator>;

  auto& alloc  = m_storage.second().first();
  auto  alloc2 = allocator();
  auto  d      = destructor{alloc2,1};

  std::unique_ptr<control_block,destructor> hold( alloc2.allocate(1), d );
  alloc_traits::construct( alloc, hold.get(), alloc, *m_storage.first() );

  return hold.release();
}

template<typename T, typename Deleter, typename Allocator>
void bit::stl::detail::clone_ptr_pointer<T,Deleter,Allocator>::destroy()
{
  using control_block = clone_ptr_pointer<T,Deleter,Allocator>;
  using atraits   = typename std::allocator_traits<Allocator>::template rebind_traits<control_block>;
  using ptraits   = std::pointer_traits<typename atraits::pointer>;
  using allocator = typename atraits::allocator_type;

  // Delete the underlying type, the allocator, and this control block

  allocator alloc(m_storage.second());

  m_storage.first().second()(m_storage.first().first());
  m_storage.first().second().~Deleter();
  m_storage.second().~Allocator();
  alloc.deallocate( ptraits::pointer_to(*this), 1);
}

//============================================================================
// detail::clone_ptr_emplace
//============================================================================

//----------------------------------------------------------------------------
// Contructor
//----------------------------------------------------------------------------

template<typename T, typename Allocator>
template<typename...Args>
bit::stl::detail::clone_ptr_emplace<T,Allocator>
  ::clone_ptr_emplace( Allocator alloc, Args&&...args )
  : m_storage( std::piecewise_construct,
               std::forward_as_tuple(alloc),
               std::forward_as_tuple(std::forward<Args>(args)...) )
{

}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------

template<typename T, typename Allocator>
void* bit::stl::detail::clone_ptr_emplace<T,Allocator>
  ::get_deleter( const std::type_info& info )
  noexcept
{
  return nullptr;
}

template<typename T, typename Allocator>
bit::stl::detail::clone_ptr_base*
  bit::stl::detail::clone_ptr_emplace<T,Allocator>::clone()
{
  using control_block = detail::clone_ptr_emplace<T,Allocator>;
  using alloc_traits  = typename std::allocator_traits<Allocator>::template rebind_traits<control_block>;
  using allocator     = typename alloc_traits::allocator_type;
  using destructor    = allocator_deleter<allocator>;

  auto& alloc  = m_storage.first();
  auto  alloc2 = allocator();
  auto  d      = destructor{alloc2,1};

  std::unique_ptr<control_block,destructor> hold( alloc2.allocate(1), d );
  alloc_traits::construct( alloc2, hold.get(), alloc2, m_storage.second() );

  return hold.release();
}

template<typename T, typename Allocator>
void bit::stl::detail::clone_ptr_emplace<T,Allocator>::destroy()
{
  using control_block = clone_ptr_emplace<T,Allocator>;
  using atraits   = typename std::allocator_traits<Allocator>::template rebind_traits<control_block>;
  using ptraits   = std::pointer_traits<typename atraits::pointer>;
  using allocator = typename atraits::allocator_type;

  // Destruct the underlying type, the allocator, and this control block

  auto alloc = allocator(m_storage.first());

  m_storage.first().~Allocator();
  m_storage.second().~T();
  alloc.deallocate( ptraits::pointer_to(*this), 1);
}

template<typename T, typename Allocator>
T* bit::stl::detail::clone_ptr_emplace<T,Allocator>::get()
  noexcept
{
  return std::addressof(m_storage.second());
}

//============================================================================
// clone_ptr<T>
//============================================================================

//----------------------------------------------------------------------------
// Constructors / Destructor / Assignment
//----------------------------------------------------------------------------

template<typename T>
bit::stl::clone_ptr<T>::clone_ptr()
  noexcept
  : m_control_block( nullptr ),
    m_ptr( nullptr )
{

}

template<typename T>
bit::stl::clone_ptr<T>::clone_ptr( std::nullptr_t )
  noexcept
  : clone_ptr()
{

}


template<typename T>
template<typename U, typename>
bit::stl::clone_ptr<T>::clone_ptr( U* ptr )
  noexcept
  : clone_ptr( ptr, std::default_delete<U>{} )
{

}

template<typename T>
template<typename U, typename Deleter, typename>
bit::stl::clone_ptr<T>::clone_ptr( U* ptr, Deleter deleter )
  : clone_ptr( ptr, deleter, std::allocator<void>{} )
{

}

template<typename T>
template<typename Deleter, typename Allocator>
bit::stl::clone_ptr<T>::clone_ptr( std::nullptr_t, Deleter deleter )
  : clone_ptr( nullptr, deleter, std::allocator<void>{} )
{

}

template<typename T>
template<typename U, typename Deleter, typename Allocator, typename>
bit::stl::clone_ptr<T>::clone_ptr( U* ptr, Deleter deleter, Allocator alloc )
  : m_control_block(nullptr),
    m_ptr(ptr)
{
  reset( ptr, deleter, alloc );
}

template<typename T>
template<typename Deleter, typename Allocator>
bit::stl::clone_ptr<T>::clone_ptr( std::nullptr_t, Deleter, Allocator )
  : m_control_block(nullptr),
    m_ptr(nullptr)
{

}

template<typename T>
bit::stl::clone_ptr<T>::clone_ptr( const clone_ptr& other )
  : m_control_block( other.m_control_block->clone() ),
    m_ptr(nullptr)
{
  // TODO: Adjust m_ptr
}

template<typename T>
template<typename U, typename>
bit::stl::clone_ptr<T>::clone_ptr( const clone_ptr<U>& other )
  : m_control_block( other.m_control_block->clone() ),
    m_ptr(nullptr)
{
  // TODO: Adjust m_ptr
}

template<typename T>
bit::stl::clone_ptr<T>::clone_ptr( clone_ptr&& other )
  noexcept
  : m_control_block( other.m_control_block ),
    m_ptr( other.m_ptr )
{
  // TODO: Adjust m_ptr
  other.m_control_block = nullptr;
  other.m_ptr = nullptr;
}

template<typename T>
template<typename U, typename>
bit::stl::clone_ptr<T>::clone_ptr( clone_ptr<U>&& other )
  noexcept
  : m_control_block( other.m_control_block ),
    m_ptr( other.m_ptr )
{
  // TODO: Adjust m_ptr
  other.m_control_block = nullptr;
  other.m_ptr = nullptr;
}

template<typename T>
template<typename U, typename Deleter, typename>
bit::stl::clone_ptr<T>::clone_ptr( std::unique_ptr<U,Deleter>&& other )
  noexcept
  : clone_ptr( other.release(), other.get_deleter() )
{

}

//----------------------------------------------------------------------------

template<typename T>
bit::stl::clone_ptr<T>::~clone_ptr()
{
  destroy();
}

//----------------------------------------------------------------------------

template<typename T>
bit::stl::clone_ptr<T>&
  bit::stl::clone_ptr<T>::operator=( const clone_ptr& other )
{
  destroy();

  return (*this);
}

template<typename T>
template<typename U, typename>
bit::stl::clone_ptr<T>&
  bit::stl::clone_ptr<T>::operator=( const clone_ptr<U>& other )
{
  destroy();

  return (*this);
}

template<typename T>
bit::stl::clone_ptr<T>&
  bit::stl::clone_ptr<T>::operator=( clone_ptr&& other )
  noexcept
{
  destroy();

  m_control_block = other.m_control_block;
  m_ptr           = other.m_ptr;

  other.m_control_block = nullptr;
  other.m_ptr           = nullptr;

  return (*this);
}

template<typename T>
template<typename U, typename>
bit::stl::clone_ptr<T>&
  bit::stl::clone_ptr<T>::operator=( clone_ptr<U>&& other )
  noexcept
{
  destroy();

  m_control_block = other.m_control_block;
  m_ptr           = other.m_ptr;

  other.m_control_block = nullptr;
  other.m_ptr           = nullptr;

  return (*this);
}

template<typename T>
template<typename U, typename Deleter, typename>
bit::stl::clone_ptr<T>&
  bit::stl::clone_ptr<T>::operator=( std::unique_ptr<U,Deleter>&& other )
{
  reset( other.release(), other.get_deleter() );

  return (*this);
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

template<typename T>
void bit::stl::clone_ptr<T>::reset()
  noexcept
{
  if( m_control_block ) {
    m_control_block->destroy();
  }
  m_control_block = nullptr;
  m_ptr           = nullptr;
}

template<typename T>
template<typename U, typename>
void bit::stl::clone_ptr<T>::reset( U* ptr )
{
  reset( ptr, std::default_delete<T>{} );
}

template<typename T>
template<typename U, typename Deleter, typename>
void bit::stl::clone_ptr<T>::reset( U* ptr, Deleter deleter )
{
  reset( ptr, deleter, std::allocator<T>{} );
}

template<typename T>
template<typename U, typename Deleter, typename Allocator, typename>
void bit::stl::clone_ptr<T>::reset( U* ptr, Deleter deleter, Allocator alloc )
{
  reset();
  if(ptr) {
    using control_block = detail::clone_ptr_pointer<T,Deleter,Allocator>;
    using alloc_traits  = typename std::allocator_traits<Allocator>::template rebind_traits<control_block>;
    using allocator     = typename alloc_traits::allocator_type;
    using destructor    = allocator_deleter<allocator>;

    allocator alloc2(alloc);
    destructor d{alloc2,1};
    std::unique_ptr<control_block,destructor> hold( alloc2.allocate(1), d );

    alloc_traits::construct( alloc2, hold.get(), ptr, deleter, alloc );

    m_ptr = ptr;
    m_control_block = hold.release();
  }
}

//----------------------------------------------------------------------------

template<typename T>
void bit::stl::clone_ptr<T>::swap( clone_ptr<T>& other ) noexcept
{
  using std::swap;

  swap( m_ptr, other.m_ptr );
  swap( m_control_block, other.m_control_block );
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename T>
typename bit::stl::clone_ptr<T>::element_type*
  bit::stl::clone_ptr<T>::get()
  const noexcept
{
  return m_ptr;
}

template<typename T>
bit::stl::clone_ptr<T>::operator bool()
  const noexcept
{
  return static_cast<bool>(m_ptr);
}

template<typename T>
std::add_lvalue_reference_t<T> bit::stl::clone_ptr<T>::operator*()
  const noexcept
{
  return *m_ptr;
}

template<typename T>
T* bit::stl::clone_ptr<T>::operator->()
  const noexcept
{
  return m_ptr;
}

//----------------------------------------------------------------------------
// Private Constructor
//----------------------------------------------------------------------------

template<typename T>
bit::stl::clone_ptr<T>::clone_ptr( ctor_tag,
                                   detail::clone_ptr_base* control_block,
                                   T* ptr )
  noexcept
  : m_control_block(control_block),
    m_ptr(ptr)
{

}

//----------------------------------------------------------------------------
// Private Utilities
//----------------------------------------------------------------------------

template<typename T>
void* bit::stl::clone_ptr<T>::get_deleter( const std::type_info& info )
  const noexcept
{
  return m_control_block->get_deleter( info );
}

template<typename T>
void bit::stl::clone_ptr<T>::destroy()
{
  if( m_control_block ) {
    m_control_block->destroy();
  }
}

//
//
//

template<typename T>
void bit::stl::swap( clone_ptr<T>& lhs, clone_ptr<T>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

template<typename T, typename...Args>
bit::stl::clone_ptr<T> bit::stl::make_clone( Args&&...args )
{
  using tag_type      = typename clone_ptr<T>::ctor_tag;
  using control_block = detail::clone_ptr_emplace<T,std::allocator<T>>;
  using allocator     = std::allocator<control_block>;
  using alloc_traits  = std::allocator_traits<allocator>;
  using destructor    = allocator_deleter<allocator>;

  allocator alloc;
  destructor d{alloc,1};
  std::unique_ptr<control_block,destructor> hold( alloc.allocate(1), d );
  alloc_traits::construct( alloc, hold.get(), alloc, std::forward<Args>(args)... );

  auto* ptr   = hold.get()->get();
  auto* block = hold.release();
  return { tag_type{}, block, ptr };
}

template<typename T, typename Allocator, typename...Args>
bit::stl::clone_ptr<T>
  bit::stl::allocate_clone( const Allocator& alloc, Args&&...args )
{
  using tag_type      = typename clone_ptr<T>::ctor_tag;
  using control_block = detail::clone_ptr_emplace<T,Allocator>;
  using alloc_traits  = typename std::allocator_traits<Allocator>::template rebind_traits<control_block>;
  using allocator     = typename alloc_traits::allocator_type;
  using destructor    = allocator_deleter<allocator>;

  allocator alloc2(alloc);
  destructor d{alloc2,1};
  std::unique_ptr<control_block,destructor> hold( alloc2.allocate(1), d );
  alloc_traits::construct( alloc, hold.get(), alloc, std::forward<Args>(args)... );

  auto* ptr   = hold.get()->get();
  auto* block = hold.release();
  return { tag_type{}, block, ptr };
}

template<typename Deleter, typename T>
Deleter* bit::stl::get_deleter( const clone_ptr<T>& p )
  noexcept
{
  return static_cast<Deleter*>( p.get_deleter( typeid(Deleter) ) );
}

//----------------------------------------------------------------------------
// Casts
//----------------------------------------------------------------------------

template<typename To, typename From>
bit::stl::clone_ptr<To>
  bit::stl::casts::static_pointer_cast( clone_ptr<From>&& other )
{
  using tag_type = typename clone_ptr<To>::ctor_tag;

  auto* ptr   = static_cast<To*>(other.get());
  auto* block = other.m_control_block;

  other.m_ptr = nullptr;
  other.m_control_block = nullptr;

  return { tag_type{}, block, ptr };
}

template<typename To, typename From>
bit::stl::clone_ptr<To>
  bit::stl::casts::dynamic_pointer_cast( clone_ptr<From>&& other )
{
  using tag_type = typename clone_ptr<To>::ctor_tag;

  auto* ptr = dynamic_cast<To*>(other.get());

  if( ptr ) {
    auto* block = other.m_control_block;

    other.m_ptr = nullptr;
    other.m_control_block = nullptr;

    return { tag_type{}, block, ptr };
  }
  return {};
}

template<typename To, typename From>
bit::stl::clone_ptr<To>
  bit::stl::casts::const_pointer_cast( clone_ptr<From>&& other )
{
  using tag_type = typename clone_ptr<To>::ctor_tag;

  auto* ptr   = const_cast<To*>(other.get());
  auto* block = other.m_control_block;

  other.m_ptr = nullptr;
  other.m_control_block = nullptr;

  return { tag_type{}, block, ptr };
}

template<typename To, typename From>
bit::stl::clone_ptr<To>
  bit::stl::casts::reinterpret_pointer_cast( clone_ptr<From>&& other )
{
  using tag_type = typename clone_ptr<To>::ctor_tag;

  auto* ptr   = reinterpret_cast<To*>(other.get());
  auto* block = other.m_control_block;

  other.m_ptr = nullptr;
  other.m_control_block = nullptr;

  return { tag_type{}, block, ptr };
}

#endif /* BIT_STL_MEMORY_DETAIL_CLONE_PTR_INL */
