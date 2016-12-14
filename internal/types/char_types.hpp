/**
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_INTERNAL_CHAR_TYPES_HPP
#define BIT_STL_INTERNAL_CHAR_TYPES_HPP

namespace bit {
  namespace stl {

//! \addtogroup stl
//! \{

    // Decide tchar type; implementation specific character type
    // that supports multiple character encodings
#if defined(BIT_UTF32) && !defined(BIT_TCHAR_DEFINED)

    #define BIT_CHAR32_IS_TCHAR 1
    #define BIT_TCHAR_DEFINED   1

    using tchar = char32_t;

#elif defined(BIT_UTF16) && !defined(BIT_TCHAR_DEFINED)

    #define BIT_CHAR16_IS_TCHAR 1
    #define BIT_TCHAR_DEFINED   1

    using tchar = char16_t;

#elif defined(BIT_UNICODE) && !defined(BIT_TCHAR_DEFINED)

    #define BIT_WCHAR_IS_TCHAR  1
    #define BIT_TCHAR_DEFINED   1

    using tchar = wchar_t;

#elif !defined(BIT_TCHAR_DEFINED)

    #define BIT_CHAR_IS_TCHAR   1
    #define BIT_TCHAR_DEFINED   1

    using tchar = char;

    #ifndef BIT_ANSI
      #define BIT_ANSI          1
    #endif

#endif

//! \}
  } // namespace stl
} // namespace bit

#endif /* BIT_STL_INTERNAL_CHAR_TYPES_HPP */
