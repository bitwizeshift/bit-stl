#ifndef BIT_STL_DETAIL_STRING_TOKENIZER_INL
#define BIT_STL_DETAIL_STRING_TOKENIZER_INL

//--------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------

template<typename CharT, typename Traits, bool Owning>
inline constexpr bit::stl::basic_string_tokenizer<CharT,Traits,Owning>::
  basic_string_tokenizer( string_type str,
                          string_type delim,
                          bool return_delims )
  : m_buffer(std::move(str)),
    m_delimiter(std::move(delim)),
    m_current(0),
    m_return_delims(return_delims)
{

}

//-------------------------------------------------------------------------
// Accessors
//-------------------------------------------------------------------------

template<typename CharT, typename Traits, bool Owning>
inline constexpr typename bit::stl::basic_string_tokenizer<CharT,Traits,Owning>::string_view_type
  bit::stl::basic_string_tokenizer<CharT,Traits,Owning>::delimiters()
  const noexcept
{
  return m_delimiter;
}

template<typename CharT, typename Traits,bool Owning>
inline constexpr typename bit::stl::basic_string_tokenizer<CharT,Traits,Owning>::string_view_type
  bit::stl::basic_string_tokenizer<CharT,Traits,Owning>::buffer()
  const noexcept
{
  return m_buffer;
}

template<typename CharT, typename Traits, bool Owning>
inline constexpr bool
  bit::stl::basic_string_tokenizer<CharT,Traits,Owning>::keeps_delimiter()
  const noexcept
{
  return m_return_delims;
}

//--------------------------------------------------------------------------
// Tokenizing
//--------------------------------------------------------------------------

template<typename CharT, typename Traits, bool Owning>
inline constexpr bool
  bit::stl::basic_string_tokenizer<CharT,Traits,Owning>::has_more()
  const noexcept
{
  return m_current != m_buffer.size();
}

template<typename CharT, typename Traits, bool Owning>
inline typename bit::stl::basic_string_tokenizer<CharT,Traits,Owning>::string_view_type
  bit::stl::basic_string_tokenizer<CharT,Traits,Owning>::next()
  noexcept
{
  return next_token( m_delimiter );
}

template<typename CharT, typename Traits, bool Owning>
inline typename bit::stl::basic_string_tokenizer<CharT,Traits,Owning>::string_view_type
  bit::stl::basic_string_tokenizer<CharT,Traits,Owning>::
  next( const string_view_type& delim )
  noexcept
{
  return next_token( delim );
}

template<typename CharT, typename Traits, bool Owning>
inline void
bit::stl::basic_string_tokenizer<CharT,Traits,Owning>::reset()
  noexcept
{
  m_current = 0;
}

//-------------------------------------------------------------------------
// Private Member Functions
//-------------------------------------------------------------------------

template<typename CharT, typename Traits, bool Owning>
inline void
  bit::stl::basic_string_tokenizer<CharT,Traits,Owning>::skip_delimiter()
  noexcept
{
  if(!m_return_delims && (m_current < m_buffer.size())) ++m_current;
}

//-------------------------------------------------------------------------

template<typename CharT, typename Traits, bool Owning>
inline typename bit::stl::basic_string_tokenizer<CharT,Traits,Owning>::string_view_type
  bit::stl::basic_string_tokenizer<CharT,Traits,Owning>::
  next_token( const string_view_type& delim )
  noexcept
{
  if(!has_more()) return "";

  auto delim_found = false;
  auto start       = m_current;

  while( m_current < m_buffer.size() && !delim_found ) {
    if( is_delimiter( m_buffer[m_current], delim ) ) {
      delim_found = true;
    } else {
      ++m_current;
    }
  }
  if(m_current==start && m_return_delims) ++m_current;

  auto end = m_current - start;
  skip_delimiter();

  return string_view_type(m_buffer).substr( start, end );
}

//-------------------------------------------------------------------------

template<typename CharT, typename Traits, bool Owning>
inline bool bit::stl::basic_string_tokenizer<CharT,Traits,Owning>::
  is_delimiter( value_type c, const string_view_type& delim )
  const noexcept
{
  for( const value_type& d : delim )
  {
    if( traits_type::eq(d,c) ) return true;
  }
  return false;
}

#endif /* BIT_STL_DETAIL_STRING_TOKENIZER_INL */
