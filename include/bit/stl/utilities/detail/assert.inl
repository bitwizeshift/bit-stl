#ifndef BIT_STL_UTILITIES_DETAIL_ASSERT_INL
#define BIT_STL_UTILITIES_DETAIL_ASSERT_INL

namespace bit { namespace stl { namespace detail {
  inline void assert_internal( const char* message, source_location source )
  {
    std::fprintf(stderr, "[assertion] %s (%zu)::%s\n"
                         "            %s\n", source.file_name(),
                                             source.line(),
                                             source.function_name(),
                                             message );

    BIT_BREAKPOINT();
  }

} } } // namespace bit::stl::detail

#endif /* BIT_STL_UTILITIES_DETAIL_ASSERT_INL */
