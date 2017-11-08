/**
 * \file dynamic_constant.hpp
 *
 * \brief This header contains the definition for a constant type that can be
 *        specified either at runtime or compile time
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_UTILITIES_DYNAMIC_CONSTANT_HPP
#define BIT_STL_UTILITIES_DYNAMIC_CONSTANT_HPP

#include <cstddef> // std::size_t, std::ptrdiff_t

namespace bit {
  namespace stl {

    constexpr auto dynamic_size = std::size_t(-1);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief A size-constant that can be specified etiher at runtime or
    ///        compile time
    ///
    /// \tparam Value the fixed value for this constant
    /// \tparam Idx an index to allow unique EBO inheritance
    ///////////////////////////////////////////////////////////////////////////
    template<std::size_t Value, std::size_t Idx = 0>
    class dynamic_size_constant
    {
      //-----------------------------------------------------------------------
      // Constructors
      //-----------------------------------------------------------------------
    public:

      /// \brief Default-constructs this dynamic_size_constant
      constexpr dynamic_size_constant() = default;

      //-----------------------------------------------------------------------
      // Observers
      //-----------------------------------------------------------------------
    public:

      /// \brief Returns the value of this constant
      ///
      /// \return the value of this constant
      constexpr std::size_t value() const noexcept;
    };

    template<std::size_t Idx>
    class dynamic_size_constant<dynamic_size,Idx>
    {
      //-----------------------------------------------------------------------
      // Constructors
      //-----------------------------------------------------------------------
    public:

      /// \brief Constructs a dynamic_size_constant from the given \p value
      ///
      /// \param value the value to assign to this constant
      explicit constexpr dynamic_size_constant( std::size_t value );

      //-----------------------------------------------------------------------
      // Observers
      //-----------------------------------------------------------------------
    public:

      /// \brief Returns the value of this constant
      ///
      /// \return the value of this constant
      constexpr std::size_t value() const noexcept;

      //-----------------------------------------------------------------------
      // Private Members
      //-----------------------------------------------------------------------
    private:

      std::size_t m_value;
    };

  } // namespace stl
} // namespace bit

#include "detail/dynamic_size_constant.inl"

#endif /* BIT_STL_UTILITIES_DYNAMIC_CONSTANT_HPP */
