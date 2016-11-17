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
#ifndef BIT_STL_INTERNAL_FLOAT_TYPES_HPP
#define BIT_STL_INTERNAL_FLOAT_TYPES_HPP

namespace bit {
  inline namespace stl {

//! \addtogroup bit
//! \{

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

#if defined(BIT_DOUBLE_PRECISION)
    using precision = f64; ///< Precision type
#else
# ifndef BIT_SINGLE_PRECISION
#   define BIT_SINGLE_PRECISION // defined for consistency
# endif
    using precision = f32; ///< Precision type
#endif

    //////////////////////////////////////////////////////////////////////////
    /// \brief A type used for clamping floating-point values to values
    ///        between [0,1]
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class clamp
    {
      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      /// \brief Clamps a value to between 0 and 1
      ///
      /// \tparam value the value to clamp
      constexpr clamp( T value )
        noexcept
        : m_value( value > T(1) ? T(1) : value < T(0) ? T(0) : value )
      {

      }

      /// \brief Converts this value to the underlying clamp type
      constexpr operator T()
        const noexcept
      {
        return m_value;
      }

    private:

      T m_value;
    };

//! \}
  } // inline namespace stl
} // namespace bit

#endif /* BIT_STL_INTERNAL_FLOAT_TYPES_HPP */
