/**
 * \brief This header is mostly taken from Microsoft's implementation of
 *        the GSL byte-type.
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_INTERNAL_BYTE_HPP
#define BIT_INTERNAL_BYTE_HPP

#include <type_traits>

namespace bit {

  /// \brief Signed byte type
  enum class byte : unsigned char{};

  //------------------------------------------------------------------------
  // Byte Operators
  //------------------------------------------------------------------------

  template <typename IntT, typename = std::enable_if_t<std::is_integral<IntT>::value>>
  inline constexpr byte& operator<<=(byte& lhs, IntT shift)
    noexcept
  {
      return lhs = byte(static_cast<unsigned char>(lhs) << shift);
  }

  template <class IntT, typename = std::enable_if_t<std::is_integral<IntT>::value>>
  inline constexpr byte operator<<(byte lhs, IntT shift)
    noexcept
  {
      return byte(static_cast<unsigned char>(lhs) << shift);
  }

  template <class IntT, typename = std::enable_if_t<std::is_integral<IntT>::value>>
  inline constexpr byte& operator>>=(byte& lhs, IntT shift)
    noexcept
  {
      return lhs = byte(static_cast<unsigned char>(lhs) >> shift);
  }

  template <class IntT, typename = std::enable_if_t<std::is_integral<IntT>::value>>
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

} // namespace bit

#endif /* BIT_INTERNAL_BYTE_HPP */
