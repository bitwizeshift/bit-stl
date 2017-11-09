/**
 * \file dynamic_index_constant.hpp
 *
 * \brief This header contains the definition for a constant type that can be
 *        specified either at runtime or compile time
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_UTILITIES_DYNAMIC_INDEX_CONSTANT_HPP
#define BIT_STL_UTILITIES_DYNAMIC_INDEX_CONSTANT_HPP

#include <cstddef> // std::size_t, std::ptrdiff_t
#include <limits>  // std::numeric_limits

namespace bit {
  namespace stl {

    constexpr auto dynamic_index = std::numeric_limits<std::ptrdiff_t>::min();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief A index-constant that can be specified etiher at runtime or
    ///        compile time
    ///
    /// \tparam Value the fixed value for this constant
    /// \tparam Idx an index to allow unique EBO inheritance
    ///////////////////////////////////////////////////////////////////////////
    template<std::ptrdiff_t Value, std::size_t Idx = 0>
    class dynamic_index_constant
    {
      //-----------------------------------------------------------------------
      // Constructors
      //-----------------------------------------------------------------------
    public:

      /// \brief Default-constructs this dynamic_index_constant
      constexpr dynamic_index_constant() = default;

      //-----------------------------------------------------------------------
      // Observers
      //-----------------------------------------------------------------------
    public:

      /// \brief Returns the value of this constant
      ///
      /// \return the value of this constant
      constexpr std::ptrdiff_t value() const noexcept;

    };

    template<std::size_t Idx>
    class dynamic_index_constant<dynamic_index,Idx>
    {
      //-----------------------------------------------------------------------
      // Constructors
      //-----------------------------------------------------------------------
    public:

      /// \brief Constructs a dynamic_index_constant from the given \p value
      ///
      /// \param value the value to assign to this constant
      explicit constexpr dynamic_index_constant( std::ptrdiff_t value );

      //-----------------------------------------------------------------------
      // Observers
      //-----------------------------------------------------------------------
    public:

      /// \brief Returns the value of this constant
      ///
      /// \return the value of this constant
      constexpr std::ptrdiff_t value() const noexcept;

      //-----------------------------------------------------------------------
      // Private Members
      //-----------------------------------------------------------------------
    private:

      std::ptrdiff_t m_value;
    };
  } // namespace stl
} // namespace bit

#include "detail/dynamic_index_constant.inl"

#endif /* BIT_STL_UTILITIES_DYNAMIC_INDEX_CONSTANT_HPP */
