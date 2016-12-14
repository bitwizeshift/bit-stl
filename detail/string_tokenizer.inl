#ifndef BFSTL_DETAIL_STRING_TOKENIZER_INL
#define BFSTL_DETAIL_STRING_TOKENIZER_INL

namespace bit {
  namespace stl {

    //--------------------------------------------------------------------------
    // Constructor
    //--------------------------------------------------------------------------

    template<typename CharT, typename Traits>
    inline constexpr basic_string_tokenizer<CharT,Traits>::
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

    template<typename CharT, typename Traits>
    inline constexpr typename basic_string_tokenizer<CharT,Traits>::string_type
      basic_string_tokenizer<CharT,Traits>::delimiters()
      const noexcept
    {
      return m_delimiter;
    }

    template<typename CharT, typename Traits>
    inline constexpr typename basic_string_tokenizer<CharT,Traits>::string_type
      basic_string_tokenizer<CharT,Traits>::buffer()
      const noexcept
    {
      return m_buffer;
    }

    template<typename CharT, typename Traits>
    inline constexpr bool basic_string_tokenizer<CharT,Traits>::keeps_delimiter()
      const noexcept
    {
      return m_return_delims;
    }

    //--------------------------------------------------------------------------
    // Tokenizing
    //--------------------------------------------------------------------------

    template<typename CharT, typename Traits>
    inline constexpr bool
      basic_string_tokenizer<CharT,Traits>::has_more()
      const noexcept
    {
      return m_current != m_buffer.size();
    }

    template<typename CharT, typename Traits>
    inline typename basic_string_tokenizer<CharT,Traits>::string_type
      basic_string_tokenizer<CharT,Traits>::next()
      noexcept
    {
      return next_token( m_delimiter );
    }

    template<typename CharT, typename Traits>
    inline typename basic_string_tokenizer<CharT,Traits>::string_type
      basic_string_tokenizer<CharT,Traits>::next( const string_type& delim )
      noexcept
    {
      return next_token( delim );
    }

    template<typename CharT, typename Traits>
    inline void
      basic_string_tokenizer<CharT,Traits>::reset()
      noexcept
    {
      m_current = 0;
    }

    //-------------------------------------------------------------------------
    // Private Member Functions
    //-------------------------------------------------------------------------

    template<typename CharT, typename Traits>
    inline void basic_string_tokenizer<CharT,Traits>::
      skip_delimiter()
      noexcept
    {
      if(!m_return_delims && (m_current < m_buffer.size())) ++m_current;
    }

    //-------------------------------------------------------------------------

    template<typename CharT, typename Traits>
    inline typename basic_string_tokenizer<CharT,Traits>::string_type
      basic_string_tokenizer<CharT,Traits>::
      next_token( const string_type& delim )
      noexcept
    {
      if(!has_more()) return "";

      auto delim_found = false;
      auto start       = m_current;

      while( m_current < m_buffer.size() && !delim_found )
      {
        auto character = m_buffer[m_current];
        if( is_delimiter( character, delim ) )
        {
          delim_found = true;
        } else {
          ++m_current;
        }
      }
      if(m_current==start && m_return_delims) ++m_current;

      auto end = m_current - start;
      skip_delimiter();

      return m_buffer.substr( start, end );
    }

    //-------------------------------------------------------------------------

    template<typename CharT, typename Traits>
    inline bool basic_string_tokenizer<CharT,Traits>::
      is_delimiter( value_type c, const string_type& delim )
      const noexcept
    {
      for( const value_type& d : delim )
      {
        if( d == c ) return true;
      }
      return false;
    }
  } // namespace stl
} // namespace bit

#endif /* BFSTL_DETAIL_STRING_TOKENIZER_INL */
