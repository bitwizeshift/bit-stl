/**
 * \brief This internal header declares fixed size floating types
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */

/*
 * Symbols Defined:
 *
 * BIT_SINGLE_PRECISION : Defined if BIT_DOUBLE_PRECISION and
 *                         BIT_SINGLE_PRECISION are not defined.
 */
#ifndef BIT_INTERNAL_FLOAT_TYPES_HPP
#define BIT_INTERNAL_FLOAT_TYPES_HPP

namespace bit {

//! \addtogroup bit
//! \{

  //--------------------------------------------------------------------------
  // Floating point types
  //
  // It is worth noting that float and double may not always be
  // IEEE-754 floats/doubles in which they are 32/64 bits respectively.
  //
  // However, there is rarely a case in which float will be practically less
  // than 32 bits, and having it larger than 32 bits should not pose a problem.
  //--------------------------------------------------------------------------

  typedef float       f32;        ///< 32-bit floating point (single precision)
  typedef double      f64;        ///< 64-bit floating point (double precision)
  typedef long double highp;      ///< High-precision floating point

  #if defined(BIT_DOUBLE_PRECISION)
    typedef f64   precision;      ///< Precision type
  #else
    #ifndef BIT_SINGLE_PRECISION
      #define BIT_SINGLE_PRECISION // defined for consistency
    #endif
    typedef f32   precision;      ///< Precision type
  #endif

  //--------------------------------------------------------------------------
  // Clamped floating point types
  //
  // These typedefs exist for semantic purposes only; a clamped float value is
  // expected to be between 0 and 1
  //--------------------------------------------------------------------------

  typedef float       f32_clamp;     ///< 32-bit float clamped between 0 and 1
  typedef double      f64_clamp;     ///< 64-bit float clamped between 0 and 1
  typedef long double highp_clamp;   ///< High-precision float clamped between 0 and 1
  typedef precision precision_clamp; ///< Precision value clamped between 0 and 1

//! \}

} // namespace bit

#endif /* BIT_INTERNAL_FLOAT_TYPES_HPP */
