#ifndef BIT_DETAIL_ARRAY_VIEW_INL
#define BIT_DETAIL_ARRAY_VIEW_INL

namespace bit {

//--------------------------------------------------------------------------
  // Constructor
  //--------------------------------------------------------------------------

  template<typename T>
  constexpr array_view<T>::array_view()
    noexcept
    : m_ptr(nullptr),
      m_size(0)
  {

  }

  template<typename T>
  constexpr array_view<T>::array_view( std::nullptr_t )
    noexcept
    : array_view()
  {

  }

  template<typename T>
  constexpr array_view<T>::array_view( const array_view& other )
    noexcept
    : m_ptr(other.m_ptr),
      m_size(other.m_size)
  {

  }

  template<typename T>
  constexpr array_view<T>::array_view( array_view&& other )
    noexcept
    : m_ptr(other.m_ptr),
      m_size(other.m_size)
  {
    other.m_ptr  = nullptr;
    other.m_size = 0;
  }

  template<typename T>
  template<std::size_t N>
  constexpr array_view<T>::array_view(T (&array)[N])
    noexcept
    : m_ptr(array),
      m_size(N)
  {

  }

  template<typename T>
  template<std::size_t N>
  constexpr array_view<T>::array_view(const T (&array)[N])
    noexcept
    : m_ptr(array),
      m_size(N)
  {

  }

} // namespace bit

#endif /* BIT_DETAIL_ARRAY_VIEW_INL */
