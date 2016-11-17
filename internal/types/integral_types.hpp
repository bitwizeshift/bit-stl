/**
 * \brief This internal header declares fixed size integral types
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_INTERNAL_INTEGRAL_TYPES_HPP
#define BIT_INTERNAL_INTEGRAL_TYPES_HPP

// Prevent pedantic errors for __int128
#if defined(__GNUC__) && (__GNUC__ >= 4)
#  pragma GCC system_header
#endif

#include <cstdint>
#include <cstddef> // for std::size_t and std::ptrdiff_t

namespace bit {

  //--------------------------------------------------------------------------
  // Integer Types
  //--------------------------------------------------------------------------

  //! \addtogroup bit
  //! \{

  // Basic signed
  typedef std::int8_t   s8;    ///< Signed 8-bit integer
  typedef std::int16_t  s16;   ///< Signed 16-bit integer
  typedef std::int32_t  s32;   ///< Signed 32-bit integer
  typedef std::int64_t  s64;   ///< Signed 64-bit integer

  // Basic unsigned
  typedef std::uint8_t  u8;    ///< Unsigned 8-bit integer
  typedef std::uint16_t u16;   ///< Unsigned 16-bit integer
  typedef std::uint32_t u32;   ///< Unsigned 32-bit integer
  typedef std::uint64_t u64;   ///< Unsigned 64-bit integer

  // Fast signed
  typedef std::int_fast8_t   s8f;  ///< Fastest signed 8-bit integer
  typedef std::int_fast16_t  s16f; ///< Fastest signed 16-bit integer
  typedef std::int_fast32_t  s32f; ///< Fastest signed 32-bit integer
  typedef std::int_fast64_t  s64f; ///< Fastest signed 64-bit integer

  // Fast unsigned
  typedef std::uint_fast8_t  u8f;  ///< Fastest unsigned 8-bit integer
  typedef std::uint_fast16_t u16f; ///< Fastest unsigned 16-bit integer
  typedef std::uint_fast32_t u32f; ///< Fastest unsigned 32-bit integer
  typedef std::uint_fast64_t u64f; ///< Fastest unsigned 64-bit integer

  // Least signed
  typedef std::int_least8_t  s8l;  ///< Least signed 8-bit integer
  typedef std::int_least16_t s16l; ///< Least signed 16-bit integer
  typedef std::int_least32_t s32l; ///< Least signed 32-bit integer
  typedef std::int_least64_t s64l; ///< Least signed 64-bit integer

  // Least unsigned
  typedef std::uint_least8_t  u8l;  ///< Least unsigned 8-bit integer
  typedef std::uint_least16_t u16l; ///< Least unsigned 16-bit integer
  typedef std::uint_least32_t u32l; ///< Least unsigned 32-bit integer
  typedef std::uint_least64_t u64l; ///< Least unsigned 64-bit integer

  // Max size int
  typedef std::intmax_t  smaxint; ///< Maximum signed integer type
  typedef std::uintmax_t umaxint; ///< Maximum unsigned integer type

  // Pointer size
  typedef std::uintptr_t uptr;    ///< Integer large enough for pointer address
  typedef std::ptrdiff_t ptrdiff; ///< Type representing difference between pointers

  //! \}

} // namespace bit

#endif /* BIT_INTERNAL_INTEGRAL_TYPES_HPP */
