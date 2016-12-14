/**
 * \file string_tokenizer.hpp
 *
 * \brief This header contains a utility for tokenizing strings
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STRING_TOKENIZER_HPP
#define BIT_STRING_TOKENIZER_HPP

#include "string_view.hpp"

namespace bit {
  namespace stl {

    /////////////////////////////////////////////////////////////////////////////
    /// \class bit::basic_string_tokenizer
    ///
    /// \brief A tokenizer class for strings.
    ///
    /// This class performs simple tokenization of strings in a lightweight
    /// manner, by making heavy-use of basic_string_view types.
    ///
    /////////////////////////////////////////////////////////////////////////////
    template<typename CharT, typename Traits = std::char_traits<CharT>>
    class basic_string_tokenizer final
    {
      //-------------------------------------------------------------------------
      // Public Types
      //-------------------------------------------------------------------------
    public:

      using value_type  = CharT;
      using traits_type = Traits;
      using string_type = basic_string_view<CharT,Traits>;

      using size_type = typename basic_string_view<CharT,Traits>::size_type;

      //-------------------------------------------------------------------------
      // Construction
      //-------------------------------------------------------------------------
    public:

      /// \brief Tokenizes a given string with the specified delimiter, with a
      ///        given option to return delimiters are part of the token
      ///
      /// \param str the string to tokenize
      /// \param delim the delimiter to use for tokenization
      /// \param return_delims Flag indicating whether to return delimiters
      constexpr explicit basic_string_tokenizer( string_type str,
                                                 string_type delim,
                                                 bool return_delims = false );

      /// \brief Copies a string tokenizer
      ///
      /// \param other the other tokenizer to copy
      constexpr basic_string_tokenizer( const basic_string_tokenizer& other ) = default;

      /// \brief Moves a string tokenizer
      ///
      /// \param other the other tokenizer to move
      constexpr basic_string_tokenizer( basic_string_tokenizer&& other ) = default;

      //-------------------------------------------------------------------------
      // Accessors
      //-------------------------------------------------------------------------
    public:

      /// \brief Retrieves the delimiters for this tokenizer
      ///
      /// \return the delimiters
      constexpr string_type delimiters() const noexcept;

      /// \brief Retrieves the string used in this tokenizer
      ///
      /// \return the string
      constexpr string_type buffer() const noexcept;

      /// \brief Returns whether this tokenizer includes the delimiters
      ///
      /// \return \c true if this tokenizer returns the delimiters
      constexpr bool keeps_delimiter() const noexcept;

      //-------------------------------------------------------------------------
      // Tokenizing
      //-------------------------------------------------------------------------
    public:

      /// \brief Returns true if the tokenizer has more tokens available
      ///
      /// \return true if the tokenizer has more tokens
      constexpr bool has_more() const noexcept;

      /// \brief Gets the next token in this string tokenizer's string.
      ///
      /// \return the next token
      string_type next() noexcept;

      /// \brief Gets the next token in this string tokenizer's string.
      ///
      /// First, the set of characters considered to be delimiters by this
      /// basic_string_tokenizer object is changed to be the characters in
      /// the string \p delim.
      ///
      /// Then the next token in the string after the current position is
      /// returned. The current position is advanced beyond the recognized
      /// token. The new delimiter set remains the default after this call
      ///
      /// \param delim the delimiter to match
      /// \return the next token
      string_type next( const string_type& delim ) noexcept;

      /// \brief Resets the current position within this string tokenizer
      ///        to the beginning of the buffer
      ///
      /// This call allows for the basic_string_tokenizer to be re-used as if
      /// reconstructed.
      void reset() noexcept;

      //-------------------------------------------------------------------------
      // Private Member Functions
      //-------------------------------------------------------------------------
    private:

      /// \brief Skips the delimiter, if \c return_delims was false
      void skip_delimiter() noexcept;

      /// \brief Retrieves the next token in the series
      ///
      /// \param delim the delimiters to check
      string_type next_token( const string_type& delim ) noexcept;

      /// Returns whether or not the supplied argument is a delimiter
      ///
      /// \param c value to check if delimiter
      /// \param delim the delimiters to check
      /// \return true if argument is a delimiter
      bool is_delimiter( value_type c, const string_type& delim ) const noexcept;

      //-------------------------------------------------------------------------
      // Private Members
      //-------------------------------------------------------------------------
    private:

      string_type m_buffer;        /// The buffer to tokenize
      string_type m_delimiter;     /// The delimiter used
      size_type   m_current;       /// Current character being read
      bool        m_return_delims; /// Are delimiters returned as tokens?

    };

    using string_tokenizer    = basic_string_tokenizer<char>;
    using wstring_tokenizer   = basic_string_tokenizer<wchar_t>;
    using u16string_tokenizer = basic_string_tokenizer<char16_t>;
    using u32string_tokenizer = basic_string_tokenizer<char32_t>;

  } // namespace stl
} // namespace bit

#include "detail/string_tokenizer.inl"

#endif /* BIT_STRING_TOKENIZER_HPP */
