/**
 * \brief This internal header attempts to prevent authors from using
 *        potentially dangerous functions or methods by redefining them.
 *
 * The following compile-time options are available to protect
 * sets of functions:
 *
 * <ul>
 *   <li>DISABLE_BUFFER_IO_FUNCTIONS : Disables all buffered IO Functions</li>
 *   <li>DISABLE_STRING_FUNCTIONS    : Disables all C string functions</li>
 *   <li>DISABLE_FILE_IO_FUNCTIONS   : Disables all C file IO functions</li>
 * </ul>
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */

#ifndef BIT_STL_INTERNAL_CONFIG_PROTECT_FUNCTIONS_HPP
#define BIT_STL_INTERNAL_CONFIG_PROTECT_FUNCTIONS_HPP

//-----------------------------------------------------------------------------
// I/O protections
//-----------------------------------------------------------------------------

#if defined( DISABLE_BUFFER_IO_FUNCTIONS )
# ifdef printf
#   undef printf
# endif
# define printf      printf__ERROR_USE_OUTPUT_STREAM_INSTEAD

# ifdef wprintf
#   undef wprintf
# endif
# define wprintf     wprintf__ERROR_USE_OUTPUT_STREAM_INSTEAD
#endif

//-----------------------------------------------------------------------------
// String protection
//-----------------------------------------------------------------------------

#if defined( DISABLE_STRING_FUNCTIONS )
# if strcmp
#   undef strcmp
# endif
# define strcmp      strcmp__ERROR_USE_STRING_METHODS_INSTEAD

# ifdef wcscmp
#   undef wcscmp
# endif
# define wcscmp      wcscmp__ERROR_USE_STRING_METHODS_INSTEAD

# ifdef strncpy
#   undef strncpy
# endif
# define strncpy     strncpy__ERROR_USE_STRING_METHODS_INSTEAD

# ifdef wcsncpy
#   undef wcsncpy
# endif
# define wcsncpy     wcsncpy__ERROR_USE_STRING_METHODS_INSTEAD

# ifdef strlen
#   undef strlen
# endif
# define strlen      strlen__ERROR_USE_STRING_METHODS_INSTEAD

# ifdef wcslen
#   undef wcslen
# endif
# define wcslen      wcslen__ERROR_USE_STRING_METHODS_INSTEAD

# ifdef _snprintf
#   undef _snprintf
# endif
# define _snprintf   snprintf__ERROR_USE_STRING_METHODS_INSTEAD

# ifdef _snwprintf
#   undef _snwprintf
# endif
# define _snwprintf  snwprintf__ERROR_USE_STRING_METHODS_INSTEAD

# ifdef sprintf
#   undef sprintf
# endif
# define sprintf     sprintf__ERROR_USE_STRING_METHODS_INSTEAD

# ifdef swprintf
#   undef swprintf
# endif
# define swprintf    swprintf__ERROR_USE_STRING_METHODS_INSTEAD

# ifdef vsprintf
#   undef vsprintf
# endif
# define vsprintf    vsprintf__ERROR_USE_STRING_METHODS_INSTEAD

# ifdef vswprintf
#   undef vswprintf
# endif
# define vswprintf   vswprintf__ERROR_USE_STRING_METHODS_INSTEAD

# ifdef _vsnprintf
#   undef _vsnprintf
# endif
# define _vsnprintf  vsnprintf__ERROR_USE_STRING_METHODS_INSTEAD

# ifdef _vsnwprintf
#   undef _vsnwprintf
# endif
# define _vsnwprintf vsnwprintf__ERROR_USE_STRING_METHODS_INSTEAD

# ifdef strcat
#   undef strcat
# endif
# define strcat      strcat__ERROR_USE_STRING_METHODS_INSTEAD

# ifdef wcscat
#   undef wcscat
# endif
# define wcscat      wcscat__ERROR_USE_STRING_METHODS_INSTEAD

# ifdef strncat
#   undef strncat
# endif
# define strncat     strncat__ERROR_USE_STRING_METHODS_INSTEAD

# ifdef wcsncat
#   undef wcsncat
# endif
# define wcsncat     wcsncat__ERROR_USE_STRING_METHODS_INSTEAD
#endif

//-----------------------------------------------------------------------------
// File I/O protection
//-----------------------------------------------------------------------------

#if defined( DISABLE_FILE_IO_FUNCTIONS )
# ifdef fopen
#   undef fopen
# endif
# define fopen    fopen_ERROR_USE_FILESYSTEM_INSTEAD

# ifdef _wfopen
#   undef _wfopen
# endif
# define _wfopen   _wfopen_ERROR_USE_FILESYSTEM_INSTEAD
#endif

#endif /* BIT_STL_INTERNAL_CONFIG_PROTECT_FUNCTIONS_HPP */
