#ifndef BIT_STL_UTILITIES_DETAIL_ASSERT_INL
#define BIT_STL_UTILITIES_DETAIL_ASSERT_INL

//=============================================================================
// X.Y.1, assertion_failure
//=============================================================================

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

inline bit::stl::assertion_failure
  ::assertion_failure( const char* message, source_location source )
  : std::runtime_error(message),
    m_location( std::move(source) )
{

}

//-----------------------------------------------------------------------------
// Accessors
//-----------------------------------------------------------------------------

inline bit::stl::source_location bit::stl::assertion_failure::source()
  const noexcept
{
  return m_location;
}

//=============================================================================
// X.Y.2, Assertion handlers
//=============================================================================

inline void bit::stl::default_assert( const char* message,
                                      source_location source )
{
  std::fprintf(stderr, "[assertion] %s (%zu)::%s\n"
                       "            %s\n", source.file_name(),
                                           source.line(),
                                           source.function_name(),
                                           message );

  BIT_BREAKPOINT();
}

inline void bit::stl::throwing_assert( const char* message,
                                       source_location source )
{
  throw assertion_failure(message,source);
}

namespace bit { namespace stl { namespace detail {

  inline std::atomic<assert_handler_t>& assert_handler()
  {
    static std::atomic<assert_handler_t> handler(&default_assert);

    return handler;
  }

  inline void assert_internal( const char* message, source_location source )
  {
    (*get_assert_handler())(message,source);
  }

} } } // namespace bit::stl::detail

inline bit::stl::assert_handler_t bit::stl::set_assert_handler( assert_handler_t f )
{
  return detail::assert_handler().exchange( f ? f : &default_assert );
}

inline bit::stl::assert_handler_t bit::stl::get_assert_handler()
{
  return detail::assert_handler();
}

#endif /* BIT_STL_UTILITIES_DETAIL_ASSERT_INL */
