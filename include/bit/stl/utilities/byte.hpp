/**
 * \file byte.hpp
 *
 * \brief This header is mostly taken from Microsoft's implementation of
 *        the GSL byte-type.
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_UTILITIES_BYTE_HPP
#define BIT_STL_UTILITIES_BYTE_HPP

#include <type_traits> // std::is_integral, std::enable_if_t, etc

namespace bit {
  namespace stl {

    /// \brief Unsigned byte type
    ///
    /// \note Due to a restriction in pre-C++-17, a conversion to a pointer of
    ///       byte types results in undefined behavior due to a violation of
    ///       strict-aliasing.
    enum class byte : unsigned char{};

    //-------------------------------------------------------------------------
    // Byte Operators
    //-------------------------------------------------------------------------

#ifndef BIT_DOXYGEN_BUILD
    template<typename IntT, typename = std::enable_if_t<std::is_integral<IntT>::value>>
#else
    template<typename IntT>
#endif
    inline constexpr byte& operator<<=(byte& lhs, IntT shift)
      noexcept
    {
        return lhs = byte(static_cast<unsigned char>(lhs) << shift);
    }

#ifndef BIT_DOXYGEN_BUILD
    template<typename IntT, typename = std::enable_if_t<std::is_integral<IntT>::value>>
#else
    template<typename IntT>
#endif
    inline constexpr byte operator<<(byte lhs, IntT shift)
      noexcept
    {
        return byte(static_cast<unsigned char>(lhs) << shift);
    }

#ifndef BIT_DOXYGEN_BUILD
    template<typename IntT, typename = std::enable_if_t<std::is_integral<IntT>::value>>
#else
    template<typename IntT>
#endif
    inline constexpr byte& operator>>=(byte& lhs, IntT shift)
      noexcept
    {
        return lhs = byte(static_cast<unsigned char>(lhs) >> shift);
    }

#ifndef BIT_DOXYGEN_BUILD
    template<typename IntT, typename = std::enable_if_t<std::is_integral<IntT>::value>>
#else
    template<typename IntT>
#endif
    inline constexpr byte operator>>(byte lhs, IntT shift)
      noexcept
    {
        return byte(static_cast<unsigned char>(lhs) >> shift);
    }

    inline byte& operator|=(byte& lhs, byte rhs)
      noexcept
    {
        return lhs = byte(static_cast<unsigned char>(lhs) | static_cast<unsigned char>(rhs));
    }

    inline constexpr byte operator|(byte lhs, byte rhs)
      noexcept
    {
        return byte(static_cast<unsigned char>(lhs) | static_cast<unsigned char>(rhs));
    }

    inline byte& operator&=(byte& lhs, byte rhs)
      noexcept
    {
        return lhs = byte(static_cast<unsigned char>(lhs) & static_cast<unsigned char>(rhs));
    }

    inline constexpr byte operator&(byte lhs, byte rhs)
      noexcept
    {
        return byte(static_cast<unsigned char>(lhs) & static_cast<unsigned char>(rhs));
    }

    inline byte& operator^=(byte& lhs, byte rhs)
      noexcept
    {
        return lhs = byte(static_cast<unsigned char>(lhs) ^ static_cast<unsigned char>(rhs));
    }

    inline constexpr byte operator^(byte lhs, byte rhs)
      noexcept
    {
        return byte(static_cast<unsigned char>(lhs) ^ static_cast<unsigned char>(rhs));
    }

    inline constexpr byte operator~(byte lhs)
      noexcept
    {
      return byte(~static_cast<unsigned char>(lhs));
    }
  } // namespace stl
} // namespace bit

#endif /* BIT_STL_UTILITIES_BYTE_HPP */
