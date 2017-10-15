/**
 * \file integral_types.hpp
 *
 * \brief This internal header declares fixed size integral types
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_DETAIL_STDDEF_TYPES_INTEGRAL_TYPES_HPP
#define BIT_STL_DETAIL_STDDEF_TYPES_INTEGRAL_TYPES_HPP

// Prevent pedantic errors for __int128
#if defined(__GNUC__) && (__GNUC__ >= 4)
#  pragma GCC system_header
#endif

#include <cstdint>
#include <cstddef> // for std::size_t and std::ptrdiff_t

namespace bit {
  namespace stl {

    //------------------------------------------------------------------------
    // Integer Types
    //------------------------------------------------------------------------

    // Basic signed
    using s8  = std::int8_t;    ///< Signed 8-bit integer
    using s16 = std::int16_t;   ///< Signed 16-bit integer
    using s32 = std::int32_t;   ///< Signed 32-bit integer
    using s64 = std::int64_t;   ///< Signed 64-bit integer

    // Basic unsigned
    using u8  = std::uint8_t;    ///< Unsigned 8-bit integer
    using u16 = std::uint16_t;   ///< Unsigned 16-bit integer
    using u32 = std::uint32_t;   ///< Unsigned 32-bit integer
    using u64 = std::uint64_t;   ///< Unsigned 64-bit integer

    // Fast signed
    using s8f  = std::int_fast8_t;  ///< Fastest signed 8-bit integer
    using s16f = std::int_fast16_t; ///< Fastest signed 16-bit integer
    using s32f = std::int_fast32_t; ///< Fastest signed 32-bit integer
    using s64f = std::int_fast64_t; ///< Fastest signed 64-bit integer

    // Fast unsigned
    using u8f  = std::uint_fast8_t;  ///< Fastest unsigned 8-bit integer
    using u16f = std::uint_fast16_t; ///< Fastest unsigned 16-bit integer
    using u32f = std::uint_fast32_t; ///< Fastest unsigned 32-bit integer
    using u64f = std::uint_fast64_t; ///< Fastest unsigned 64-bit integer

    // Least signed
    using s8l  = std::int_least8_t;  ///< Least signed 8-bit integer
    using s16l = std::int_least16_t; ///< Least signed 16-bit integer
    using s32l = std::int_least32_t; ///< Least signed 32-bit integer
    using s64l = std::int_least64_t; ///< Least signed 64-bit integer

    // Least unsigned
    using u8l  = std::uint_least8_t;  ///< Least unsigned 8-bit integer
    using u16l = std::uint_least16_t; ///< Least unsigned 16-bit integer
    using u32l = std::uint_least32_t; ///< Least unsigned 32-bit integer
    using u64l = std::uint_least64_t; ///< Least unsigned 64-bit integer

    // Max size int
    using smaxint = std::intmax_t;  ///< Maximum signed integer type
    using umaxint = std::uintmax_t; ///< Maximum unsigned integer type

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_DETAIL_STDDEF_TYPES_INTEGRAL_TYPES_HPP */
