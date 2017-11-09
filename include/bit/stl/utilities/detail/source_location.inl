#ifndef BIT_STL_UTILITIES_DETAIL_SOURCE_LOCATION_INL
#define BIT_STL_UTILITIES_DETAIL_SOURCE_LOCATION_INL

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

inline constexpr bit::stl::source_location::
  source_location( const char* file_name,
                   const char* function_name,
                   std::size_t line )
  : m_file(file_name),
    m_function(function_name),
    m_line(line)
{

}

//-----------------------------------------------------------------------------
// Access
//-----------------------------------------------------------------------------

inline constexpr std::size_t bit::stl::source_location::line()
  const noexcept
{
  return m_line;
}

inline constexpr const char* bit::stl::source_location::function_name()
  const noexcept
{
  return m_function;
}

inline constexpr const char* bit::stl::source_location::file_name()
  const noexcept
{
  return m_file;
}


//-----------------------------------------------------------------------------
// Comparisons
//-----------------------------------------------------------------------------

inline bool bit::stl::operator==( const source_location& lhs,
                                  const source_location& rhs )
  noexcept
{
  return lhs.file_name() == rhs.file_name() &&
         lhs.function_name() == rhs.function_name() &&
         lhs.line() == rhs.line();
}

inline bool bit::stl::operator!=( const source_location& lhs,
                                  const source_location& rhs )
  noexcept
{
  return !(lhs==rhs);
}

#endif /* BIT_STL_UTILITIES_DETAIL_SOURCE_LOCATION_INL */
