#ifndef BIT_DETAIL_BIMAP_INL
#define BIT_DETAIL_BIMAP_INL

namespace bit {

  //==========================================================================
  // Inline Definitions
  //==========================================================================

  //--------------------------------------------------------------------------
  // Constructors
  //--------------------------------------------------------------------------

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline bimap<X,Y,XComp,YComp,Alloc>::bimap()
    : m_map_x(),
      m_map_y()
  {

  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline bimap<X,Y,XComp,YComp,Alloc>::bimap( const XComp& xcomp,
                                              const YComp& ycomp,
                                              const Alloc& alloc )
     : m_map_x( xcomp, x_allocator(alloc) ),
       m_map_y( ycomp, y_allocator(alloc) )
  {

  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline bimap<X,Y,XComp,YComp,Alloc>::bimap( const Alloc& alloc )
     : m_map_x( x_allocator(alloc) ),
       m_map_y( y_allocator(alloc) )
  {

  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  template<typename InputIterator>
  inline bimap<X,Y,XComp,YComp,Alloc>::bimap( InputIterator first,
                                              InputIterator last,
                                              const XComp& xcomp,
                                              const YComp& ycomp,
                                              const Alloc& alloc )
    : m_map_x( xcomp, x_allocator(alloc) ),
      m_map_y( ycomp, y_allocator(alloc) )
  {
    for( ; first != last ; ++first )
    {
      auto  x_result = m_map_x.insert( std::make_pair( first.first, nullptr ) );
      auto& x_it     = x_result;

      auto  y_result = m_map_y.insert( std::make_pair( first.second, std::addressof(*x_it) ) );
      auto& y_it     = y_result;

      x_it->second = std::addressof(*y_it);
    }
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  template<typename InputIterator>
  inline bimap<X,Y,XComp,YComp,Alloc>::bimap( InputIterator first,
                                              InputIterator last,
                                              const Alloc& alloc )
    : bimap( first, last, XComp(), YComp(), alloc )
  {

  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline bimap<X,Y,XComp,YComp,Alloc>::bimap( const bimap& other )
    : m_map_x( other.m_map_x ),
      m_map_y( other.m_map_y )
  {

  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline bimap<X,Y,XComp,YComp,Alloc>::bimap( const bimap& other, const Alloc& alloc )
    : m_map_x( other.m_map_x, x_allocator(alloc) ),
      m_map_y( other.m_map_y, y_allocator(alloc) )
  {

  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline bimap<X,Y,XComp,YComp,Alloc>::bimap( bimap&& other )
    : m_map_x( std::move(other.m_map_x) ),
      m_map_y( std::move(other.m_map_y) )
  {

  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline bimap<X,Y,XComp,YComp,Alloc>::bimap( bimap&& other, const Alloc& alloc )
    : m_map_x( std::move(other.m_map_x), x_allocator(alloc) ),
      m_map_y( std::move(other.m_map_y), y_allocator(alloc) )
  {

  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline bimap<X,Y,XComp,YComp,Alloc>::bimap( std::initializer_list<value_type> init,
                                              const XComp& xcomp,
                                              const YComp& ycomp,
                                              const Alloc& alloc )
    : bimap( init.begin(), init.end(), xcomp, ycomp, alloc )
  {

  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline bimap<X,Y,XComp,YComp,Alloc>::bimap( std::initializer_list<value_type> init,
                                              const Alloc& alloc )
    : bimap( init.begin(), init.end(), XComp(), YComp(), alloc )
  {

  }

  //--------------------------------------------------------------------------
  // Assignment
  //--------------------------------------------------------------------------

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>&
    bimap<X,Y,XComp,YComp,Alloc>::operator = ( const bimap& other )
  {
    m_map_x = other.m_map_x;
    m_map_y = other.m_map_y;
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>&
    bimap<X,Y,XComp,YComp,Alloc>::operator = ( bimap&& other )
  {
    m_map_x = std::move(other.m_map_x);
    m_map_y = std::move(other.m_map_y);
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>&
    bimap<X,Y,XComp,YComp,Alloc>::operator = ( std::initializer_list<value_type> ilist )
  {
    (*this) = bimap(ilist);
  }

  //--------------------------------------------------------------------------
  // Accessors
  //--------------------------------------------------------------------------

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::allocator_type
    bimap<X,Y,XComp,YComp,Alloc>::get_allocator()
    const
  {
    return m_alloc;
  }

  //--------------------------------------------------------------------------
  // Capacity
  //--------------------------------------------------------------------------

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline bool bimap<X,Y,XComp,YComp,Alloc>::empty()
    const noexcept
  {
    return m_map_x.empty();
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::size_type
    bimap<X,Y,XComp,YComp,Alloc>::size()
    const noexcept
  {
    return m_map_x.size();
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::size_type
    bimap<X,Y,XComp,YComp,Alloc>::max_size()
    const noexcept
  {
    return m_map_x.max_size();
  }

  //--------------------------------------------------------------------------
  // Insertions
  //--------------------------------------------------------------------------

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::insert_return_type
    bimap<X,Y,XComp,YComp,Alloc>::insert( const x_type& x, const y_type& y )
  {
    auto  x_result = m_map_x.insert( std::make_pair( x, nullptr ) );
    auto& x_it     = x_result;

    auto  y_result = m_map_y.insert( std::make_pair( y, std::addressof(*x_it) ) );
    auto& y_it     = y_result;

    x_it->second = std::addressof(*y_it);

    return std::make_pair(it, false);
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::insert_return_type
    bimap<X,Y,XComp,YComp,Alloc>::insert( x_type&& x, y_type&& y )
  {
    auto  x_result = m_map_x.insert( std::make_pair( std::move(x), nullptr ) );
    auto& x_it     = x_result;

    auto  y_result = m_map_y.insert( std::make_pair( std::move(y), std::addressof(*x_it) ) );
    auto& y_it     = y_result;

    x_it->second = std::addressof(*y_it);

    return std::make_pair(it, false);
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::insert_return_type
    bimap<X,Y,XComp,YComp,Alloc>::insert( const value_type& value )
  {
    auto  x_result = m_map_x.insert( std::make_pair( value.first, nullptr ) );
    auto& x_it     = x_result;

    auto  y_result = m_map_y.insert( std::make_pair( value.second, std::addressof(*x_it) ) );
    auto& y_it     = y_result;

    x_it->second = std::addressof(*y_it);

    return std::make_pair(it, false);
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::insert_return_type
    bimap<X,Y,XComp,YComp,Alloc>::insert( value_type&& value )
  {
    auto  x_result = m_map_x.insert( std::make_pair( std::move(value.first), nullptr ) );
    auto& x_it     = x_result;

    auto  y_result = m_map_y.insert( std::make_pair( std::move(value.second), std::addressof(*x_it) ) );
    auto& y_it     = y_result;

    x_it->second = std::addressof(*y_it);

    return std::make_pair(it, false);
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  template<typename InputIterator>
  void bimap<X,Y,XComp,YComp,Alloc>::insert( InputIterator first, InputIterator last )
  {
    for( ; first != last; ++first )
    {
      insert( *first );
    }
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  void bimap<X,Y,XComp,YComp,Alloc>::insert( std::initializer_list<value_type> ilist )
  {
    insert( ilist.begin(), ilist.end() );
  }

  //--------------------------------------------------------------------------
  // Erasing
  //--------------------------------------------------------------------------

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  typename bimap<X,Y,XComp,YComp,Alloc>::iterator
    bimap<X,Y,XComp,YComp,Alloc>::erase( const_iterator pos )
  {
    return m_data.erase( pos );
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  typename bimap<X,Y,XComp,YComp,Alloc>::iterator
    bimap<X,Y,XComp,YComp,Alloc>::erase( const_iterator first, const_iterator last )
  {
    return m_data.erase( first, last );
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  typename bimap<X,Y,XComp,YComp,Alloc>::size_type
    bimap<X,Y,XComp,YComp,Alloc>::erase( const key_type& key )
  {
    return m_data.erase( key );
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  typename bimap<X,Y,XComp,YComp,Alloc>::size_type
    bimap<X,Y,XComp,YComp,Alloc>::erase_x( const x_type& key )
  {
    auto before = m_data.size();
    auto it = find_x( key );
    m_data.erase( it );

    return before - m_data.size();
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  typename bimap<X,Y,XComp,YComp,Alloc>::size_type
    bimap<X,Y,XComp,YComp,Alloc>::erase_y( const y_type& key )
  {
    auto before = m_data.size();
    auto it = find_y( key );
    m_data.erase( it );

    return before - m_data.size();
  }

  //--------------------------------------------------------------------------
  // Mutators
  //--------------------------------------------------------------------------

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline void bimap<X,Y,XComp,YComp,Alloc>::clear()
  {
    m_data.clear();
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline void bimap<X,Y,XComp,YComp,Alloc>::swap( bimap& other )
  {
    using namespace std;
    swap(m_data, other.m_data);
    swap(m_y_compare, other.m_y_compare);
  }

  //--------------------------------------------------------------------------
  // Lookout
  //--------------------------------------------------------------------------

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::size_type
    bimap<X,Y,XComp,YComp,Alloc>::count( const key_type& key )
    const noexcept
  {
    return m_data.count(key);
  }

  //--------------------------------------------------------------------------

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::size_type
    bimap<X,Y,XComp,YComp,Alloc>::count_x( const x_type& key )
    const noexcept
  {
    auto it = m_data.find( std::pair<const X, const Y>{ key, Y() } );
    if( it != m_data.end() )
    {
      return 1;
    }
    return 0;
  }

  //--------------------------------------------------------------------------

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::size_type
    bimap<X,Y,XComp,YComp,Alloc>::count_y( const y_type& key )
    const noexcept
  {
    for( auto& entry : m_data )
    {
      if( entry.second == key )
      {
        return 1;
      }
    }
    return 0;
  }


  //--------------------------------------------------------------------------
  // Iterators
  //--------------------------------------------------------------------------

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::iterator
    bimap<X,Y,XComp,YComp,Alloc>::begin()
    noexcept
  {
    return m_data.begin();
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::const_iterator
    bimap<X,Y,XComp,YComp,Alloc>::begin()
    const noexcept
  {
    return m_data.begin();
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::const_iterator
    bimap<X,Y,XComp,YComp,Alloc>::cbegin()
    const noexcept
  {
    return m_data.cbegin();
  }

  //--------------------------------------------------------------------------

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::iterator
    bimap<X,Y,XComp,YComp,Alloc>::end()
    noexcept
  {
    return m_data.end();
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::const_iterator
    bimap<X,Y,XComp,YComp,Alloc>::end()
    const noexcept
  {
    return m_data.end();
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::const_iterator
    bimap<X,Y,XComp,YComp,Alloc>::cend()
    const noexcept
  {
    return m_data.cend();
  }

  //--------------------------------------------------------------------------

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::reverse_iterator
    bimap<X,Y,XComp,YComp,Alloc>::rbegin()
    noexcept
  {
    return m_data.rbegin();
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::const_reverse_iterator
    bimap<X,Y,XComp,YComp,Alloc>::rbegin()
    const noexcept
  {
    return m_data.rbegin();
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::const_reverse_iterator
    bimap<X,Y,XComp,YComp,Alloc>::crbegin()
    const noexcept
  {
    return m_data.crbegin();
  }

  //--------------------------------------------------------------------------

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::reverse_iterator
    bimap<X,Y,XComp,YComp,Alloc>::rend()
    noexcept
  {
    return m_data.rend();
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::const_reverse_iterator
    bimap<X,Y,XComp,YComp,Alloc>::rend()
    const noexcept
  {
    return m_data.rend();
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::const_reverse_iterator
    bimap<X,Y,XComp,YComp,Alloc>::crend()
    const noexcept
  {
    return m_data.crend();
  }

  //--------------------------------------------------------------------------
  // Observers
  //--------------------------------------------------------------------------

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::x_compare
    bimap<X,Y,XComp,YComp,Alloc>::x_comp()
    const noexcept
  {
    return m_data.value_comp().x_compare;
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::y_compare
    bimap<X,Y,XComp,YComp,Alloc>::y_comp()
    const noexcept
  {
    return m_y_compare;
  }

  template<typename X, typename Y, typename XComp, typename YComp, typename Alloc>
  inline typename bimap<X,Y,XComp,YComp,Alloc>::value_compare
    bimap<X,Y,XComp,YComp,Alloc>::value_comp()
    const noexcept
  {
    return value_compare{x_compare(),y_compare()};
  }

  //--------------------------------------------------------------------------
  // Free Functions
  //--------------------------------------------------------------------------

  template<typename X, typename Y>
  void swap( bimap<X,Y>& lhs, bimap<X,Y>& rhs ) noexcept
  {
    lhs.swap(rhs);
  }

} // namespace bit

#endif /* BIT_DETAIL_BIMAP_INL */
