#ifndef BIT_STL_MEMORY_DETAIL_EXCLUSIVE_PTR_INL
#define BIT_STL_MEMORY_DETAIL_EXCLUSIVE_PTR_INL


//=============================================================================
// exclusive_ptr_control_block
//=============================================================================

class bit::stl::detail::exclusive_ptr_control_block
{
public:

  virtual void destroy() = 0;

  virtual void* get_deleter( const std::type_info& ) noexcept = 0;
};

//=============================================================================
// exclusive_ptr_emplace
//=============================================================================

template<typename T, typename Allocator>
class bit::stl::detail::exclusive_ptr_emplace
  : public bit::stl::detail::exclusive_ptr_control_block
{
public:

  template<typename...Args>
  exclusive_ptr_emplace( Allocator alloc, Args&&...args );

  void destroy() override;

  void* get_deleter( const std::type_info& info ) noexcept override;

  T* get() noexcept;

private:

  ::bit::stl::compressed_tuple<T, Allocator> m_storage;
};

template<typename T, typename Allocator>
template<typename...Args>
inline bit::stl::detail::exclusive_ptr_emplace<T,Allocator>
  ::exclusive_ptr_emplace( Allocator alloc, Args&&...args )
  : m_storage( std::piecewise_construct,
               std::forward_as_tuple(std::forward<Args>(args)...),
               std::forward_as_tuple(alloc) )
{

}

template<typename T, typename Allocator>
inline void bit::stl::detail::exclusive_ptr_emplace<T,Allocator>::destroy()
{
  using control_block = exclusive_ptr_emplace<T,Allocator>;
  using atraits   = typename std::allocator_traits<Allocator>::template rebind_traits<control_block>;
  using ptraits   = std::pointer_traits<typename atraits::pointer>;
  using allocator = typename atraits::allocator_type;

  using bit::stl::get;

  auto& value = get<0>(m_storage);
  auto& alloc = get<1>(m_storage);

  // Create allocator to deallocate this control block
  allocator control_block_allocator(alloc);

  // Destroy the allocator and the underlying type
  alloc.~Allocator();
  value.~T();

  // deallocate the memory
  control_block_allocator.deallocate( ptraits::pointer_to(*this), 1);
}

template<typename T, typename Allocator>
inline void* bit::stl::detail::exclusive_ptr_emplace<T,Allocator>
  ::get_deleter( const std::type_info& info )
  noexcept
{
  return nullptr;
}

template<typename T, typename Allocator>
inline T* bit::stl::detail::exclusive_ptr_emplace<T,Allocator>::get()
  noexcept
{
  using bit::stl::get;

  return std::addressof(bit::stl::get<0>(m_storage));
}

//=============================================================================
// exclusive_ptr_pointer
//=============================================================================

template<typename T, typename Deleter, typename Allocator>
class bit::stl::detail::exclusive_ptr_pointer
  : public bit::stl::detail::exclusive_ptr_control_block
{
public:

  exclusive_ptr_pointer( T* pointer,
                         const Deleter& deleter,
                         const Allocator& allocator );

  void destroy() override;

  void* get_deleter( const std::type_info& ) noexcept override;

  T* get() noexcept;

private:

  ::bit::stl::compressed_tuple<T, Deleter, Allocator> m_storage;
};

template<typename T, typename Deleter, typename Allocator>
inline bit::stl::detail::exclusive_ptr_pointer<T,Deleter,Allocator>
  ::exclusive_ptr_pointer( T* pointer,
                           const Deleter& deleter,
                           const Allocator& allocator )
  : m_storage( std::piecewise_construct,
               std::forward_as_tuple(pointer),
               std::forward_as_tuple(deleter),
               std::forward_as_tuple(allocator) )
{

}

template<typename T, typename Deleter, typename Allocator>
inline void bit::stl::detail::exclusive_ptr_pointer<T,Deleter,Allocator>
  ::destroy()
{
  using control_block = exclusive_ptr_pointer<T,Deleter,Allocator>;
  using atraits   = typename std::allocator_traits<Allocator>::template rebind_traits<control_block>;
  using ptraits   = std::pointer_traits<typename atraits::pointer>;
  using allocator = typename atraits::allocator_type;

  // Delete the underlying type, the allocator, and this control block

  using bit::stl::get;

  auto& pointer = get<0>(m_storage);
  auto& deleter = get<1>(m_storage);
  auto& alloc   = get<2>(m_storage);

  allocator control_block_allocator(alloc);

  // Call the deleter with the specified pointer
  deleter(pointer);

  // Delete the deleter and allocator
  deleter.~Deleter();
  alloc.~Allocator();

  // Deallocate the entire block
  control_block_allocator.deallocate( ptraits::pointer_to(*this), 1);
}

template<typename T, typename Deleter, typename Allocator>
inline void* bit::stl::detail::exclusive_ptr_pointer<T,Deleter,Allocator>
  ::get_deleter( const std::type_info& info )
  noexcept
{
  using bit::stl::get;

  if( typeid(Deleter) == info ) {
    return std::addressof( get<1>(m_storage) );
  }
  return nullptr;
}

template<typename T, typename Deleter, typename Allocator>
inline T* bit::stl::detail::exclusive_ptr_pointer<T,Deleter,Allocator>::get()
  noexcept
{
  using bit::stl::get;

  return std::addressof( get<0>(m_storage) );
}

//=============================================================================
// casts
//=============================================================================

template<typename T, typename U>
inline bit::stl::exclusive_ptr<T>
  bit::stl::detail::static_pointer_cast( exclusive_ptr<U>&& other )
{
  auto p = static_cast<T*>(other.m_ptr);
  auto c = other.m_control_block;

  other.m_ptr           = nullptr;
  other.m_control_block = nullptr;

  return { typename exclusive_ptr<T>::ctor_tag{}, c, p };
}

template<typename T, typename U>
inline bit::stl::exclusive_ptr<T>
  bit::stl::detail::dynamic_pointer_cast( exclusive_ptr<U>&& other )
{
  if( auto p = dynamic_cast<T*>(other.m_ptr) )
  {
    auto c = other.m_control_block;

    other.m_ptr           = nullptr;
    other.m_control_block = nullptr;

    return { typename exclusive_ptr<T>::ctor_tag{}, c, p };
  }
  return nullptr;
}

template<typename T, typename U>
inline bit::stl::exclusive_ptr<T>
  bit::stl::detail::const_pointer_cast( exclusive_ptr<U>&& other )
{
  auto p = const_cast<T*>(other.m_ptr);
  auto c = other.m_control_block;

  other.m_ptr           = nullptr;
  other.m_control_block = nullptr;

  return { typename exclusive_ptr<T>::ctor_tag{}, c, p };
}

template<typename T, typename U>
inline bit::stl::exclusive_ptr<T>
  bit::stl::detail::reinterpret_pointer_cast( exclusive_ptr<U>&& other )
{
  auto p = reinterpret_cast<T*>(other.m_ptr);
  auto c = other.m_control_block;

  other.m_ptr           = nullptr;
  other.m_control_block = nullptr;

  return { typename exclusive_ptr<T>::ctor_tag{}, c, p };
}


//=============================================================================
// exclusive_ptr
//=============================================================================

//-----------------------------------------------------------------------------
// Constructors / Destructor / Assignment
//-----------------------------------------------------------------------------

template<typename T>
inline constexpr bit::stl::exclusive_ptr<T>::exclusive_ptr()
  noexcept
  : exclusive_ptr( nullptr )
{

}

template<typename T>
inline constexpr bit::stl::exclusive_ptr<T>::exclusive_ptr( std::nullptr_t )
  noexcept
  : m_control_block(nullptr),
    m_ptr(nullptr)
{

}

template<typename T>
template<typename Y, typename>
inline bit::stl::exclusive_ptr<T>::exclusive_ptr( Y* ptr )
  : exclusive_ptr( ptr, std::default_delete<Y>{} )
{

}

template<typename T>
template<typename Y, typename Deleter, typename>
inline bit::stl::exclusive_ptr<T>::exclusive_ptr( Y* ptr, Deleter deleter )
  : exclusive_ptr( ptr, deleter, std::allocator<void>{} )
{

}

template<typename T>
template<typename Deleter>
inline bit::stl::exclusive_ptr<T>::exclusive_ptr( std::nullptr_t,
                                                  Deleter deleter )
  : exclusive_ptr( static_cast<T*>(nullptr), deleter )
{

}

template<typename T>
template<typename Y, typename Deleter, typename Allocator, typename>
inline bit::stl::exclusive_ptr<T>::exclusive_ptr( Y* ptr,
                                                  Deleter deleter,
                                                  Allocator alloc )
{
  reset( ptr, deleter, alloc );
}

template<typename T>
template<typename Deleter, typename Allocator>
inline bit::stl::exclusive_ptr<T>::exclusive_ptr( std::nullptr_t,
                                                  Deleter deleter,
                                                  Allocator alloc )
  : exclusive_ptr( static_cast<T*>(nullptr), deleter, alloc )
{

}

template<typename T>
inline bit::stl::exclusive_ptr<T>::exclusive_ptr( exclusive_ptr&& other )
  noexcept
  : m_control_block( other.m_control_block ),
    m_ptr( other.m_ptr )
{
  other.m_control_block = nullptr;
  other.m_ptr = nullptr;
}

template<typename T>
template<typename Y, typename>
inline bit::stl::exclusive_ptr<T>::exclusive_ptr( exclusive_ptr<Y>&& other )
  noexcept
  : m_control_block( other.m_control_block ),
    m_ptr( other.m_ptr )
{
  other.m_control_block = nullptr;
  other.m_ptr = nullptr;
}

//-----------------------------------------------------------------------

template<typename T>
inline bit::stl::exclusive_ptr<T>::~exclusive_ptr()
{
  reset();
}

//-----------------------------------------------------------------------

template<typename T>
bit::stl::exclusive_ptr<T>&
  bit::stl::exclusive_ptr<T>::operator=( exclusive_ptr&& other )
  noexcept
{
  if( m_control_block ) m_control_block->destroy();

  m_control_block = other.m_control_block;
  m_ptr           = other.m_ptr;

  other.m_control_block = nullptr;
  other.m_ptr           = nullptr;

  return (*this);
}

template<typename T>
template<typename Y, typename>
bit::stl::exclusive_ptr<T>&
  bit::stl::exclusive_ptr<T>::operator=( exclusive_ptr<Y>&& other )
  noexcept
{
  if( m_control_block ) m_control_block->destroy();

  m_control_block = other.m_control_block;
  m_ptr           = other.m_ptr;

  other.m_control_block = nullptr;
  other.m_ptr           = nullptr;

  return (*this);
}

template<typename T>
bit::stl::exclusive_ptr<T>&
  bit::stl::exclusive_ptr<T>::operator=( std::nullptr_t other )
  noexcept
{
  reset();

  return (*this);
}

//-----------------------------------------------------------------------
// Modifiers
//-----------------------------------------------------------------------

template<typename T>
inline void bit::stl::exclusive_ptr<T>::reset()
  noexcept
{
  if( m_control_block ) {
    m_control_block->destroy();
    m_control_block = nullptr;
    m_ptr           = nullptr;
  }
}

template<typename T>
template<typename Y, typename>
inline void bit::stl::exclusive_ptr<T>::reset( Y* ptr )
{
  reset( ptr, std::default_delete<Y>{} );
}

template<typename T>
template<typename Y, typename Deleter, typename>
inline void bit::stl::exclusive_ptr<T>::reset( Y* ptr, Deleter deleter )
{
  reset( ptr, deleter, std::allocator<void>{} );
}

template<typename T>
template<typename Y, typename Deleter, typename Allocator, typename>
inline void bit::stl::exclusive_ptr<T>::reset( Y* ptr,
                                               Deleter deleter,
                                               Allocator alloc )
{
  reset();

  if(ptr) {
    using control_block = detail::exclusive_ptr_pointer<T,Deleter,Allocator>;
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

//-----------------------------------------------------------------------

template<typename T>
inline void bit::stl::exclusive_ptr<T>::swap( exclusive_ptr& other )
  noexcept
{
  using std::swap;

  swap(m_control_block, other.m_control_block);
  swap(m_ptr, other.m_ptr);
}

//-----------------------------------------------------------------------
// Observers
//-----------------------------------------------------------------------

template<typename T>
inline typename bit::stl::exclusive_ptr<T>::element_type*
  bit::stl::exclusive_ptr<T>::get()
  const noexcept
{
  return m_ptr;
}

template<typename T>
template<typename U, typename>
inline std::add_lvalue_reference_t<typename bit::stl::exclusive_ptr<T>::element_type>
  bit::stl::exclusive_ptr<T>::operator[]( std::ptrdiff_t i )
  noexcept
{
  return m_ptr[i];
}

template<typename T>
inline std::add_lvalue_reference_t<typename bit::stl::exclusive_ptr<T>::element_type>
  bit::stl::exclusive_ptr<T>::operator*()
  const noexcept
{
  return (*m_ptr);
}

template<typename T>
inline typename bit::stl::exclusive_ptr<T>::element_type*
  bit::stl::exclusive_ptr<T>::operator->()
  const noexcept
{
  return m_ptr;
}

template<typename T>
inline bit::stl::exclusive_ptr<T>::operator bool()
  const noexcept
{
  return m_ptr != nullptr;
}

template<typename T>
inline bit::stl::exclusive_ptr<T>::exclusive_ptr( ctor_tag,
                                                  control_block_type* block,
                                                  T* ptr )
  noexcept
  : m_control_block(block),
    m_ptr(ptr)
{

}

//=============================================================================
// Free Functions
//=============================================================================

//-----------------------------------------------------------------------------
// Comparisons
//-----------------------------------------------------------------------------

template<typename T>
inline bool bit::stl::operator==( const exclusive_ptr<T>& lhs,
                                  const exclusive_ptr<T>& rhs )
  noexcept
{
  return lhs.get() == rhs.get();
}

template<typename T>
inline bool bit::stl::operator!=( const exclusive_ptr<T>& lhs,
                                  const exclusive_ptr<T>& rhs )
  noexcept
{
  return lhs.get() != rhs.get();
}

template<typename T>
inline bool bit::stl::operator<( const exclusive_ptr<T>& lhs,
                                 const exclusive_ptr<T>& rhs )
  noexcept
{
  return lhs.get() < rhs.get();
}

template<typename T>
inline bool bit::stl::operator>( const exclusive_ptr<T>& lhs,
                                 const exclusive_ptr<T>& rhs )
  noexcept
{
  return lhs.get() > rhs.get();
}

template<typename T>
inline bool bit::stl::operator<=( const exclusive_ptr<T>& lhs,
                                  const exclusive_ptr<T>& rhs )
  noexcept
{
  return lhs.get() <= rhs.get();
}

template<typename T>
inline bool bit::stl::operator>=( const exclusive_ptr<T>& lhs,
                                  const exclusive_ptr<T>& rhs )
  noexcept
{
  return lhs.get() >= rhs.get();
}

template<typename T>
inline bool bit::stl::operator==( const exclusive_ptr<T>& lhs,
                                  std::nullptr_t ) noexcept
{
  return lhs.get() == nullptr;
}

template<typename T>
inline bool bit::stl::operator==( std::nullptr_t,
                                  const exclusive_ptr<T>& rhs )
  noexcept
{
  return nullptr == rhs.get();
}

template<typename T>
inline bool bit::stl::operator!=( const exclusive_ptr<T>& lhs,
                                  std::nullptr_t )
  noexcept
{
  return lhs.get() != nullptr;
}

template<typename T>
inline bool bit::stl::operator!=( std::nullptr_t,
                                  const exclusive_ptr<T>& rhs )
  noexcept
{
  return nullptr != rhs.get();
}

template<typename T>
inline bool bit::stl::operator<( const exclusive_ptr<T>& lhs,
                                 std::nullptr_t )
  noexcept
{
  return false;
}

template<typename T>
inline bool bit::stl::operator<( std::nullptr_t,
                                 const exclusive_ptr<T>& rhs )
  noexcept
{
  return rhs.get() != nullptr;
}

template<typename T>
inline bool bit::stl::operator>( const exclusive_ptr<T>& lhs,
                                 std::nullptr_t )
  noexcept
{
  return lhs.get() != nullptr;
}

template<typename T>
inline bool bit::stl::operator>( std::nullptr_t,
                                 const exclusive_ptr<T>& rhs )
  noexcept
{
  return false;
}

template<typename T>
inline bool bit::stl::operator<=( const exclusive_ptr<T>& lhs,
                                  std::nullptr_t )
  noexcept
{
  return lhs.get() == nullptr;
}

template<typename T>
inline bool bit::stl::operator<=( std::nullptr_t,
                                  const exclusive_ptr<T>& rhs )
  noexcept
{
  return true;
}

template<typename T>
inline bool bit::stl::operator>=( const exclusive_ptr<T>& lhs,
                                  std::nullptr_t )
  noexcept
{
  return true;
}

template<typename T>
inline bool bit::stl::operator>=( std::nullptr_t,
                                  const exclusive_ptr<T>& rhs )
  noexcept
{
  return rhs.get() == nullptr;
}

//=============================================================================
// X.Y.2 : exclusive_ptr utilities
//=============================================================================

//-----------------------------------------------------------------------------
// Utilities
//-----------------------------------------------------------------------------

template<typename T>
inline void bit::stl::swap( exclusive_ptr<T>& lhs, exclusive_ptr<T>& rhs )
  noexcept
{
  lhs.swap(rhs);
}

//-----------------------------------------------------------------------------

template<typename T>
inline bit::stl::hash_t bit::stl::hash_value( const exclusive_ptr<T>& val )
  noexcept
{
  return static_cast<hash_t>(reinterpret_cast<std::uintptr_t>( val.get() ));
}

//-----------------------------------------------------------------------------

template<typename Deleter, typename T>
inline Deleter* bit::stl::get_deleter( const exclusive_ptr<T>& ptr )
{
  return static_cast<Deleter*>( ptr.m_control_block->get_deleter( typeid(T) ) );
}

//-------------------------------------------------------------------------

template<typename T, typename...Args>
inline bit::stl::exclusive_ptr<T> bit::stl::make_exclusive( Args&&...args )
{
  return allocate_exclusive<T>( std::allocator<void>{},
                                std::forward<Args>(args)... );
}

template<typename T, typename Allocator, typename...Args>
inline bit::stl::exclusive_ptr<T>
  bit::stl::allocate_exclusive( const Allocator& alloc,
                                Args&&...args )
{
  using tag_type      = typename exclusive_ptr<T>::ctor_tag;
  using control_block = detail::exclusive_ptr_emplace<T,Allocator>;
  using alloc_traits  = typename std::allocator_traits<Allocator>::template rebind_traits<control_block>;
  using allocator     = typename alloc_traits::allocator_type;
  using destructor    = allocator_deleter<allocator>;

  allocator alloc2(alloc);
  destructor d{alloc2,1};
  std::unique_ptr<control_block,destructor> hold( alloc2.allocate(1), d );
  alloc_traits::construct( alloc2, hold.get(), alloc, std::forward<Args>(args)... );

  auto* ptr   = hold.get()->get();
  auto* block = hold.release();
  return { tag_type{}, block, ptr };
}

//-----------------------------------------------------------------------------
// Casts
//-----------------------------------------------------------------------------

template<typename T, typename U>
inline bit::stl::exclusive_ptr<T>
  bit::stl::casts::static_pointer_cast( exclusive_ptr<U>&& other )
{
  return detail::static_pointer_cast<T>( std::move(other) );
}

template<typename T, typename U>
inline bit::stl::exclusive_ptr<T>
  bit::stl::casts::dynamic_pointer_cast( exclusive_ptr<U>&& other )
{
  return detail::dynamic_pointer_cast<T>( std::move(other) );
}

template<typename T, typename U>
inline bit::stl::exclusive_ptr<T>
  bit::stl::casts::const_pointer_cast( exclusive_ptr<U>&& other )
{
  return detail::const_pointer_cast<T>( std::move(other) );
}

template<typename T, typename U>
inline bit::stl::exclusive_ptr<T>
  bit::stl::casts::reinterpret_pointer_cast( exclusive_ptr<U>&& other )
{
  return detail::reinterpret_pointer_cast<T>( std::move(other) );
}

#endif //BIT_STL_MEMORY_DETAIL_EXCLUSIVE_PTR_INL
