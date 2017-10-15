/**
 * \file enum.hpp
 *
 * \brief This header contains various helpers for managing enum and enum class types
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_ENUM_HPP
#define BIT_STL_ENUM_HPP

#include "type_traits.hpp"
#include "../containers/string_view.hpp"
#include "assert.hpp"
#include "../iterators/iterator.hpp" // pointer_iterator

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief An exception of this type is thrown when an enum_cast to a
    ///        string fails with an invalid serialization, or when an enum
    ///        value is outside of range of a string.
    ///
    /// The latter case can only occur for bitfields or manual static_casts
    //////////////////////////////////////////////////////////////////////////
    class bad_enum_cast : public std::runtime_error
    {
    public:

      using std::runtime_error::runtime_error;
    };

    /// Type used for iterating an enum_range
    template<typename Enum>
    using enum_iterator = pointer_iterator<const Enum*,Enum>;

    /// \brief Type-trait to determine whether a type is an enum_bitmask
    ///
    /// The result is aliased as \c ::value
    template<typename Enum> struct is_enum_bitmask : std::false_type{};

    //////////////////////////////////////////////////////////////////////////
    /// \brief Traits for an enum.
    ///
    /// Implementations should provide specialiations of this type to enable
    /// to_string and from_string functionality with \c enum_cast
    ///
    /// This struct also must specialize a begin() and end() function that
    /// returns type const Enum*, if an enum is to be used for iteration
    ///
    /// \tparam Enum the enum type
    //////////////////////////////////////////////////////////////////////////
    template<typename Enum>
    struct enum_traits
    {

      /// \brief Is this enum a bitmask enum
      static constexpr bool is_bitmask = is_enum_bitmask<Enum>::value;

      /// \brief Converts the enum to a given string
      ///
      /// This function only asserts or throws without a specialization
      static string_view to_string( Enum e );

      /// \brief Converts the string to an enum
      ///
      /// This function only asserts or throws without a specialization
      static Enum from_string( string_view s );

      /// \brief Gets the start iterator for an enum range
      ///
      /// \return the start iterator
      static const Enum* begin();

      /// \brief Gets the end iterator for an enum range
      ///
      /// \return the end iterator
      static const Enum* end();
    };

    //////////////////////////////////////////////////////////////////////////
    /// \brief A range for enumerable values
    ///
    /// \tparam Enum The enum type for this range
    //////////////////////////////////////////////////////////////////////////
    template<typename Enum>
    class enum_range
    {
      static_assert( std::is_enum<Enum>::value, "Enum must be an enum type");

      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using iterator = enum_iterator<Enum>;
      using sentinel = enum_iterator<Enum>;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default-constructs this \c enum_range
      constexpr enum_range() noexcept = default;

      //----------------------------------------------------------------------
      // Iterators
      //----------------------------------------------------------------------
    public:

      /// \brief Accesses the begin iterator of this enum_range
      ///
      /// \return the beginning iterator
      constexpr iterator begin() const noexcept;

      /// \brief Accesses the end iterator of this enum_range
      ///
      /// \return the end iterator
      constexpr sentinel end() const noexcept;
    };

    /// \brief Makes an enum range from a given
    ///
    /// \return an enum range
    template<typename Enum>
    constexpr enum_range<Enum> make_enum_range();

    //----------------------------------------------------------------------------
    // Enum Casts
    //----------------------------------------------------------------------------

    inline namespace casts {

      /// \brief Casts an enum to a string, or a string to an enum
      ///
      /// \param from the entry to cast from
      /// \return the casted type
      template<typename To, typename From>
      To enum_cast( From from );

    } // inline namespace casts

    /// \brief This namespace introduces bitwise operations to any enums that
    ///        specialize \c is_enum_bitmask
    ///
    /// This namespace behaves a lot like std::rel_ops. To make use of this,
    /// use this namespace either from within another namespace, or from the
    /// top level. These overloads will only selectively enable if
    /// \c bit::stl::is_enum_bitmask has been specialized to be true for that
    /// enum.
    namespace enum_ops {

      namespace detail {
        template<typename T>
        struct is_enum_and_bitmask : std::integral_constant<bool,std::is_enum<T>::value && is_enum_bitmask<T>::value>{};

      } // namespace detail

      //======================================================================
      // Enum Operators
      //======================================================================

      //----------------------------------------------------------------------
      // Unary Operators
      //----------------------------------------------------------------------

      template<typename Enum, typename = std::enable_if_t<detail::is_enum_and_bitmask<Enum>::value>>
      constexpr Enum operator ~( Enum e ) noexcept;

      //----------------------------------------------------------------------
      // Binary Operators
      //----------------------------------------------------------------------

      template<typename Enum, typename = std::enable_if_t<detail::is_enum_and_bitmask<Enum>::value>>
      constexpr Enum operator |( Enum lhs, Enum rhs ) noexcept;

      template<typename Enum, typename = std::enable_if_t<detail::is_enum_and_bitmask<Enum>::value>>
      constexpr Enum operator &( Enum lhs, Enum rhs ) noexcept;

      template<typename Enum, typename = std::enable_if_t<detail::is_enum_and_bitmask<Enum>::value>>
      constexpr Enum operator ^( Enum lhs, Enum rhs ) noexcept;

      template<typename Enum, typename Integer, typename = std::enable_if_t<detail::is_enum_and_bitmask<Enum>::value && std::is_integral<Integer>::value>>
      constexpr Enum operator <<( Enum lhs, Integer rhs ) noexcept;

      template<typename Enum, typename Integer, typename = std::enable_if_t<detail::is_enum_and_bitmask<Enum>::value && std::is_integral<Integer>::value>>
      constexpr Enum operator >>( Enum lhs, Integer rhs ) noexcept;

      //----------------------------------------------------------------------
      // Compound Operators
      //----------------------------------------------------------------------

      template<typename Enum, typename = std::enable_if_t<detail::is_enum_and_bitmask<Enum>::value>>
      Enum& operator |=( Enum& lhs, Enum rhs ) noexcept;

      template<typename Enum, typename = std::enable_if_t<detail::is_enum_and_bitmask<Enum>::value>>
      Enum& operator &=( Enum& lhs, Enum rhs ) noexcept;

      template<typename Enum, typename = std::enable_if_t<detail::is_enum_and_bitmask<Enum>::value>>
      Enum& operator^=( Enum& lhs, Enum rhs ) noexcept;

      template<typename Enum, typename Integer, typename = std::enable_if_t<detail::is_enum_and_bitmask<Enum>::value && std::is_integral<Integer>::value>>
      Enum& operator<<=( Enum& lhs, Integer rhs ) noexcept;

      template<typename Enum, typename Integer, typename = std::enable_if_t<detail::is_enum_and_bitmask<Enum>::value && std::is_integral<Integer>::value>>
      Enum& operator>>=( Enum& lhs, Integer rhs ) noexcept;

    } // namespace enum_ops
  } // namespace stl

  inline namespace casts {
    using namespace stl::casts;
  } // inline namespace casts
} // namespace bit

#include "detail/enum.inl"

#endif /* BIT_STL_ENUM_HPP */
