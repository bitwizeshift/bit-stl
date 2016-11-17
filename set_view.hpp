/**
 * \file set_view.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_SET_VIEW_HPP
#define BIT_SET_VIEW_HPP

#include <type_traits>

namespace bit {

  namespace detail {

    template<typename T>
    class set_vtable
    {
    public:
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------

      template<typename Key, class Value>
      using get_function_t    = Value(*)(void*, Key const&);
      template<typename Key>
      using exists_function_t = bool(*)(void*, const Key&);
      using size_function_t   = std::size_t(*)(void*);

      //----------------------------------------------------------------------
      // Public Members
      //----------------------------------------------------------------------
    public:

      exists_function_t<T> count_ptr = nullptr;
      size_function_t      size_ptr   = nullptr;

      template<typename S>
      static void build_vtable( set_vtable* table )
      {
        auto const container_function = [](void* ptr, T const& k) -> bool
        {
          S* ps = static_cast<S*>(ptr);
          return ps->count( k );
        };

        auto const size_function = [](void* ptr) -> std::size_t
        {
          S* ps = static_cast<S*>(ptr);

          return ps->size();
        };

        table->count_ptr = +container_function;
        table->size_ptr   = +size_function;
      }

      template<typename S>
      static const set_vtable* get_vtable()
      {
        static const set_vtable retval = []
        {
          set_vtable retval;
          build_vtable<S>(&retval);
          return retval;
        }();

        return &retval;
      }
    };
  }

  ////////////////////////////////////////////////////////////////////////////
  /// \brief A lightweight, non-owning wrapper around set operations
  ///
  ////////////////////////////////////////////////////////////////////////////
  template<typename T>
  class set_view final
  {
    //------------------------------------------------------------------------
    // Public Member Types
    //------------------------------------------------------------------------
  public:

    using value_type      = std::decay_t<T>;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using reference       = value_type&;
    using const_reference = const value_type&;

    using size_type       = std::size_t;

    //------------------------------------------------------------------------
    // Constructor / Destructor / Assignment
    //------------------------------------------------------------------------
  public:

    /// \brief Constructs an empty set_view
    constexpr set_view();

    /// \brief Constructs a set_view from a given set
    ///
    /// \note This constructor does not participate in overload resolution
    ///       if U is a set_view
    ///
    /// \param other the set-like type to view
#ifndef BFG_DOXYGEN_BUILD
    template<typename U,
             typename = std::enable_if_t<!std::is_same<set_view,std::decay_t<U>>::value> >
#else
    template<typename U>
#endif
    constexpr set_view( U&& other );

    /// \brief Constructs a set_view by copying another set_view
    ///
    /// \param other the set view to copy
    constexpr set_view( const set_view& other );

    /// \brief Constructs a set_view by moving another set_view
    ///
    /// \param other the set_view to move
    constexpr set_view( set_view&& other );

    /// \brief Destructs the set_view
    ~set_view() = default;

    //------------------------------------------------------------------------
    // Assignment Operators
    //------------------------------------------------------------------------
  public:

    set_view& operator=( set_view other );

    //------------------------------------------------------------------------
    // Capacity
    //------------------------------------------------------------------------
  public:

    /// \brief Checks if this set_view is empty
    bool empty() const noexcept;

    size_type size() const noexcept;

    //------------------------------------------------------------------------
    // Lookup
    //------------------------------------------------------------------------
  public:

    size_type count( const value_type& t ) const noexcept;

    bool contains( const value_type& t ) const noexcept;

    explicit operator bool() const noexcept;

    //------------------------------------------------------------------------
    // Private Member Types
    //------------------------------------------------------------------------
  private:

    using vtable_type = detail::set_vtable<T>;


    //------------------------------------------------------------------------
    // Private Members
    //------------------------------------------------------------------------
  private:

    const vtable_type* m_vtable;
    const void*        m_instance;

    friend std::size_t hash_value( const set_view<T>& );

  };

  /// \brief Hashes a given set_view
  ///
  /// \param val the set_view to hash
  /// \return the hash of the set_view
  template<typename T>
  std::size_t hash_value( const set_view<T>& val ) noexcept;


  template<typename T>
  inline std::size_t hash_value( const set_view<T>& val )
    noexcept
  {
    return reinterpret_cast<std::size_t>(val.m_instance);
  }


  template<typename T>
  bool set_view<T>::empty() const noexcept
  {
    return size() == 0;
  }

  template<typename T>
  typename set_view<T>::size_type set_view<T>::size() const noexcept
  {
    if( m_vtable ) return m_vtable->size_ptr( m_instance );
    return 0;
  }

  template<typename T>
  typename set_view<T>::size_type set_view<T>::count( const value_type& key ) const noexcept
  {
    if( m_vtable ) return m_vtable->count_ptr( m_instance );
    return 0;
  }

  template<typename T>
  bool set_view<T>::contains( const value_type& key ) const noexcept
  {
    return count( key ) != 0;
  }

  template<typename T>
  set_view<T>::operator bool() const noexcept
  {
    return m_vtable;
  }

} // namespace bit

#endif /* BIT_SET_VIEW_HPP */
