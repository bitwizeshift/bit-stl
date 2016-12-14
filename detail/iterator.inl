#ifndef BIT_STL_DETAIL_ITERATOR_INL
#define BIT_STL_DETAIL_ITERATOR_INL

namespace bit {
  namespace stl {

    //------------------------------------------------------------------------
    // Constructor
    //------------------------------------------------------------------------

    template<typename Container>
    constexpr range<Container>::range( Container& container )
      noexcept
      : m_container(container)
    {

    }

    //------------------------------------------------------------------------
    // Iterators
    //------------------------------------------------------------------------

    template<typename Container>
    constexpr typename range<Container>::iterator
      range<Container>::begin()
    {
      return m_container.begin();
    }

    template<typename Container>
    constexpr typename range<Container>::sentinel
      range<Container>::end()
    {
      return m_container.end();
    }

    //------------------------------------------------------------------------

    template<typename Container>
    constexpr typename range<Container>::const_iterator
      range<Container>::begin() const
    {
      return m_container.begin();
    }

    template<typename Container>
    constexpr typename range<Container>::const_sentinel
      range<Container>::end() const
    {
      return m_container.end();
    }

    //------------------------------------------------------------------------

    template<typename Container>
    constexpr typename range<Container>::const_iterator
      range<Container>::cbegin() const
    {
      return m_container.begin();
    }

    template<typename Container>
    constexpr typename range<Container>::const_sentinel
      range<Container>::cend() const
    {
      return m_container.end();
    }

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_DETAIL_ITERATOR_INL */
