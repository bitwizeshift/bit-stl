/**
 * \file clone_ptr.hpp
 *
 * \brief This header contains an implementation of a smart pointers that
 *        clones pointers on copy.
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_MEMORY_DETAIL_CLONE_PTR_HPP
#define BIT_STL_MEMORY_DETAIL_CLONE_PTR_HPP

#include "../../utilities/utility.hpp"

#include <memory>

namespace bit {
  namespace stl {
    namespace detail {

      ////////////////////////////////////////////////////////////////////////
      /// \brief
      ///
      ////////////////////////////////////////////////////////////////////////
      class clone_ptr_base
      {
        //--------------------------------------------------------------------
        // Destructor
        //--------------------------------------------------------------------
      public:

        virtual ~clone_ptr_base() = default;

        //--------------------------------------------------------------------
        //
        //--------------------------------------------------------------------
      public:

        virtual void* get_deleter( const std::type_info& info ) noexcept = 0;

        virtual clone_ptr_base* clone() = 0;

        virtual void destroy() = 0;
      };

      ////////////////////////////////////////////////////////////////////////
      /// \brief
      ///
      ////////////////////////////////////////////////////////////////////////
      template<typename T, typename Deleter, typename Allocator>
      class clone_ptr_pointer : public clone_ptr_base
      {
        //--------------------------------------------------------------------
        // Constructor
        //--------------------------------------------------------------------
      public:

        clone_ptr_pointer( T* pointer, const Deleter& deleter, const Allocator& allocator );

        //--------------------------------------------------------------------
        //
        //--------------------------------------------------------------------
      public:

        void* get_deleter( const std::type_info& info ) noexcept override;

        clone_ptr_base* clone() override;

        void destroy() override;

        //--------------------------------------------------------------------
        // Private Member Types
        //--------------------------------------------------------------------
      private:

        using compressed_storage = compressed_pair<compressed_pair<T*,Allocator>,Deleter>;

        //--------------------------------------------------------------------
        // Private Members
        //--------------------------------------------------------------------
      private:

        compressed_storage m_storage;

      };

      ////////////////////////////////////////////////////////////////////////
      /// \brief
      ///
      ////////////////////////////////////////////////////////////////////////
      template<typename T, typename Allocator>
      class clone_ptr_emplace : public clone_ptr_base
      {
        //--------------------------------------------------------------------
        // Constructor
        //--------------------------------------------------------------------
      public:

        template<typename...Args>
        clone_ptr_emplace( Allocator alloc, Args&&...args );

        //--------------------------------------------------------------------
        //
        //--------------------------------------------------------------------
      public:

        void* get_deleter( const std::type_info& info ) noexcept override;

        clone_ptr_base* clone() override;

        void destroy() override;

        T* get() noexcept;

        //--------------------------------------------------------------------
        // Private Member Types
        //--------------------------------------------------------------------
      private:

        using compressed_storage = compressed_pair<Allocator,T>;

        //--------------------------------------------------------------------
        // Private Members
        //--------------------------------------------------------------------
      private:

        compressed_storage m_storage;
      };

    } // namespace detail

    ////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ////////////////////////////////////////////////////////////////////////
    template<typename Allocator>
    class allocator_destructor
    {
      //--------------------------------------------------------------------
      // Public Member Types
      //--------------------------------------------------------------------
    public:

      using alloc_traits = std::allocator_traits<Allocator>;
      using pointer   = typename alloc_traits::pointer;
      using size_type = typename alloc_traits::size_type;

      //--------------------------------------------------------------------
      // Constructor
      //--------------------------------------------------------------------
    public:

      allocator_destructor( Allocator& alloc, size_type size );

      //--------------------------------------------------------------------
      //
      //--------------------------------------------------------------------
    public:

      void operator()( pointer p ) noexcept;

      //--------------------------------------------------------------------
      // Private Members
      //--------------------------------------------------------------------
    private:

      Allocator& m_allocator;
      size_type  m_size;
    };

    //////////////////////////////////////////////////////////////////////////
    /// \brief clone_ptr is a smart pointer that owns and manages another
    ///        object through a pointer and disposes of that object when the
    ///        clone_ptr goes out of scope
    ///
    /// Like unique_ptr, clone_ptr owns unique instances of objects; no two
    /// clone_ptrs should ever point to the same instance. Unlike unique_ptr,
    /// clone_ptr is copyable -- wherein the underlying type's copy-constructor
    /// is invoked, and the new object is allocated.
    ///
    /// Instead of requiring the Deleter type, this class requires knowledge
    /// of both the allocation *and* deallocation scheme -- and thus requires
    /// the Allocator itself.
    ///
    /// \note No attempt has been made for this class to support the T[]
    ///       specialization, since the \c Allocator concept requires the
    ///       size of the originally allocated array to perform deallocations.
    ///       This would require carrying along an extra size argument to
    ///       properly deallocate, and provides more complications than
    ///       benefits
    ///
    /// \bug Currently this marks functions as 'noexcept', when they should be
    ///      marked 'noexcept(std::is_nothrow_copyable<Allocator>::value)' and
    ///      'noexcept(std::is_nothrow_default_constructible<Allocator>::value)'
    ///
    /// \tparam T the type this clone_ptr manages
     //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class clone_ptr
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using element_type   = T;
      using pointer        = T*;

      //----------------------------------------------------------------------
      // Constructor / Assignment
      //----------------------------------------------------------------------
    public:

      /// \{
      /// \brief Constructs a clone_ptr with no managed object
      clone_ptr() noexcept;
      clone_ptr( std::nullptr_t ) noexcept;
      /// \}

      /// \brief Constructs a clone_ptr that manages \p ptr
      ///
      /// \param ptr the pointer to manage
      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      explicit clone_ptr( U* ptr ) noexcept;

      template<typename U, typename Deleter, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      clone_ptr( U* ptr, Deleter deleter );

      template<typename Deleter, typename Allocator>
      clone_ptr( std::nullptr_t, Deleter deleter );

      template<typename U, typename Deleter, typename Allocator, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      clone_ptr( U* ptr, Deleter deleter, Allocator alloc );

      template<typename Deleter, typename Allocator>
      clone_ptr( std::nullptr_t, Deleter deleter, Allocator allocator );

      /// \brief Constructs a clone_ptr from an existing clone_ptr
      ///
      /// \param other the other clone_ptr to copy
      clone_ptr( const clone_ptr& other );

      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      clone_ptr( const clone_ptr<U>& other );

      /// \brief Constructs a clone_ptr from an existing cone_ptr
      ///
      /// \param other the other clone_ptry to copy
      clone_ptr( clone_ptr&& other ) noexcept;

      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      clone_ptr( clone_ptr<U>&& other ) noexcept;

      template<typename U, typename Deleter, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      clone_ptr( std::unique_ptr<U,Deleter>&& other ) noexcept;


      //----------------------------------------------------------------------

      ~clone_ptr();

      //----------------------------------------------------------------------

      clone_ptr& operator=( const clone_ptr& other );

      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      clone_ptr& operator=( const clone_ptr<U>& other );

      clone_ptr& operator=( clone_ptr&& other ) noexcept;

      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      clone_ptr& operator=( clone_ptr<U>&& other ) noexcept;

      template<typename U, typename Deleter, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      clone_ptr& operator=( std::unique_ptr<U,Deleter>&& other );

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      void reset() noexcept;

      template<typename U, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      void reset( U* ptr );

      template<typename U, typename Deleter, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      void reset( U* ptr, Deleter deleter );

      template<typename U, typename Deleter, typename Allocator, typename = std::enable_if_t<std::is_convertible<U*,T*>::value>>
      void reset( U* ptr, Deleter deleter, Allocator alloc );

      void swap( clone_ptr& other ) noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      pointer get() const noexcept;

      explicit operator bool() const noexcept;

      std::add_lvalue_reference_t<T> operator*() const noexcept;

      pointer operator->() const noexcept;

      //----------------------------------------------------------------------
      // Private Constructors
      //----------------------------------------------------------------------
    private:

      struct ctor_tag{};

      clone_ptr( ctor_tag, detail::clone_ptr_base* control_block, T* ptr ) noexcept;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      detail::clone_ptr_base* m_control_block;
      T*                      m_ptr;

      //----------------------------------------------------------------------
      // Private Utilities
      //----------------------------------------------------------------------
    private:

      void* get_deleter( const std::type_info& info ) const noexcept;

      void destroy();

      //----------------------------------------------------------------------
      // Friends
      //----------------------------------------------------------------------
    private:

      template<typename U, typename...Args>
      friend clone_ptr<U> make_clone( Args&&...args );

      template<typename U, typename Allocator, typename...Args>
      friend clone_ptr<U> allocate_clone( const Allocator&, Args&&...args );

      template<typename Deleter, typename U>
      friend Deleter* get_deleter( clone_ptr<U>& p ) noexcept;

      template<typename To, typename From>
      friend clone_ptr<To> static_pointer_cast( clone_ptr<From>&& other );

      template<typename To, typename From>
      friend clone_ptr<To> dynamic_pointer_cast( clone_ptr<From>&& other );

      template<typename To, typename From>
      friend clone_ptr<To> const_pointer_cast( clone_ptr<From>&& other );

      template<typename To, typename From>
      friend clone_ptr<To> reinterpret_pointer_cast( clone_ptr<From>&& other );

      template<typename U>
      friend class clone_ptr;
    };

    //------------------------------------------------------------------------
    // Utilities
    //------------------------------------------------------------------------

    /// \brief Swaps the contents of two clone_ptrs
    ///
    /// \param lhs the left clone_ptr
    /// \param rhs the right clone_ptr
    template<typename T>
    void swap( clone_ptr<T>& lhs, clone_ptr<T>& rhs ) noexcept;

    //------------------------------------------------------------------------


    template<typename T, typename...Args>
    clone_ptr<T> make_clone( Args&&...args );

    template<typename T, typename Allocator, typename...Args>
    clone_ptr<T> allocate_clone( const Allocator&, Args&&...args );

    /// \brief Access to the \c p's deleter.
    ///
    /// If the clone pointer \p p owns a deleter of type cv-unqualified
    /// \p Deleter (e.g. if it was created with one of the constructors that
    /// take a deleter as a parameter), then returns a pointer to the deleter.
    ///
    /// Otherwise, returns a null pointer.
    ///
    /// \param p the pointer
    /// \return the deleter
    template<typename Deleter, typename T>
    Deleter* get_deleter( const clone_ptr<T>& p ) noexcept;

    //------------------------------------------------------------------------
    // Casts
    //------------------------------------------------------------------------

    inline namespace casts {

      template<typename To, typename From>
      clone_ptr<To> static_pointer_cast( clone_ptr<From>&& other );

      template<typename To, typename From>
      clone_ptr<To> dynamic_pointer_cast( clone_ptr<From>&& other );

      template<typename To, typename From>
      clone_ptr<To> const_pointer_cast( clone_ptr<From>&& other );

      template<typename To, typename From>
      clone_ptr<To> reinterpret_pointer_cast( clone_ptr<From>&& other );

    } // inline namespace casts

  } // namespace stl
} // namespace bit


//============================================================================
// allocator_destructor
//============================================================================

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------

template<typename Allocator>
bit::stl::allocator_destructor<Allocator>
  ::allocator_destructor( Allocator& alloc, size_type size )
  : m_allocator(alloc),
    m_size(size)
{

}

//----------------------------------------------------------------------------
// Observer
//----------------------------------------------------------------------------

template<typename Allocator>
void bit::stl::allocator_destructor<Allocator>::operator()( pointer p )
  noexcept
{
  alloc_traits::deallocate( m_allocator, p, m_size );
}

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
  using destructor    = allocator_destructor<allocator>;

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
  using destructor    = allocator_destructor<allocator>;

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
  if(ptr) {
    using control_block = detail::clone_ptr_pointer<T,Deleter,Allocator>;
    using alloc_traits  = typename std::allocator_traits<Allocator>::template rebind_traits<control_block>;
    using allocator     = typename alloc_traits::allocator_type;
    using destructor    = allocator_destructor<allocator>;

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
  using destructor    = allocator_destructor<allocator>;

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
  using destructor    = allocator_destructor<allocator>;

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

#endif /* BIT_STL_MEMORY_DETAIL_CLONE_PTR_HPP */
