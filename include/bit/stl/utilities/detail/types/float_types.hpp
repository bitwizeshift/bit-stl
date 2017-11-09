/**
 * \file float_types.hpp
 *
 * \brief This internal header declares fixed size floating types
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_UTILITIES_DETAIL_TYPES_FLOAT_TYPES_HPP
#define BIT_STL_UTILITIES_DETAIL_TYPES_FLOAT_TYPES_HPP

namespace bit {
  namespace stl {

    //------------------------------------------------------------------------
    // Floating point types
    //
    // It is worth noting that float and double may not always be
    // IEEE-754 floats/doubles in which they are 32/64 bits respectively.
    //
    // However, there is rarely a case in which float will be practically less
    // than 32 bits, and having it larger than 32 bits should not pose a
    // problem.
    //------------------------------------------------------------------------

    using f32   = float;       ///< 32-bit floating point (single precision)
    using f64   = double;      ///< 64-bit floating point (double precision)
    using highp = long double; ///< High-precision floating point

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_UTILITIES_DETAIL_TYPES_FLOAT_TYPES_HPP */
