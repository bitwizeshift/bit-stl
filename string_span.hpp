/**
 * \file string_span.hpp
 *
 * \brief Thie file contains a mutable view of a string
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STRING_SPAN_HPP
#define BIT_STRING_SPAN_HPP

#include "span.hpp"

namespace bit {

  template<typename CharT, std::ptrdiff_t Extent>
  class basic_string_span : span<CharT,Extent>
  {
  public:

    using span<CharT,Extent>::span;

  private:

  };

  template<std::ptrdiff_t Extent>
  using string_span = basic_string_span<char,Extent>;

  template<std::ptrdiff_t Extent>
  using wstring_span = basic_string_span<wchar_t,Extent>;

  template<std::ptrdiff_t Extent>
  using u16string_span = basic_string_span<char16_t,Extent>;

  template<std::ptrdiff_t Extent>
  using u32string_span = basic_string_span<char32_t,Extent>;

} // namespace bit

#endif /* BIT_STRING_SPAN_HPP */
