/**
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */

//
// WARNING:
//  This is an internal header file, included by other library headers.
//  Do not attempt to use it directly.
//
#ifndef BIT_INTERNAL_CHAR_TYPES_HPP
#define BIT_INTERNAL_CHAR_TYPES_HPP

#include <string>

namespace bit {

//! \addtogroup bit
//! \{

  // Decide tchar type; implementation specific character type
  // that supports multiple character encodings
  #if defined(BIT_UTF32) && !defined(BIT_TCHAR_DEFINED)

    typedef char32_t tchar;
    #define BIT_CHAR32_IS_TCHAR 1
    #define BIT_TCHAR_DEFINED   1

  #elif defined(BIT_UTF16) && !defined(BIT_TCHAR_DEFINED)

    typedef char16_t tchar;
    #define BIT_CHAR16_IS_TCHAR 1
    #define BIT_TCHAR_DEFINED   1

  #elif defined(BIT_UNICODE) && !defined(BIT_TCHAR_DEFINED)

    typedef wchar_t tchar;
    #define BIT_WCHAR_IS_TCHAR  1
    #define BIT_TCHAR_DEFINED   1

  #elif !defined(BIT_TCHAR_DEFINED)

    typedef char tchar;
    #define BIT_CHAR_IS_TCHAR   1
    #define BIT_TCHAR_DEFINED   1

    #ifndef BIT_ANSI
      #define BIT_ANSI          1
    #endif

  #endif

//! \}

} // namespace bit

#endif /* BIT_INTERNAL_CHAR_TYPES_HPP */
