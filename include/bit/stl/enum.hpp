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
#include "string_view.hpp"
#include "pointer_iterator.hpp"
#include "assert.hpp"

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief An exception of this type is thrown when an enum_cast to a
    ///        string fails with an invalid serialization, or when an enum
    ///        value is outside of range of a string.
    ///
    /// The latter case can only occur for bitfields or manual static_casts
    //////////////////////////////////////////////////////////////////////////
    class bad_enum_cast : public std::exception
    {
    public:

      bad_enum_cast() = default;
    };

    /// \brief A type used to indicate the sequence for a given enum.
    ///
    /// This type should be specialized for any enum that requires an
    /// iterable interface. The only 2 members required are \c ::begin
    /// and \c ::end, which must be \c enum* .
    ///
    /// \c ::begin
    /// \c ::end
    template<typename Enum>
    struct enum_sequence;

    /// \brief Type trait to determine whether a specialization exists for
    ///
    template<typename Enum, typename = void>
    struct has_enum_sequence : std::false_type{};

    template<typename Enum>
    struct has_enum_sequence<Enum,
      void_t<decltype(static_cast<const Enum*>(enum_sequence<Enum>::begin)),
             decltype(static_cast<const Enum*>(enum_sequence<Enum>::end))>>
      : std::true_type{};

    /// Type used for iterating an enum_range
    template<typename Enum>
    using enum_iterator = pointer_iterator<const Enum*,Enum>;

    //////////////////////////////////////////////////////////////////////////
    /// \brief Traits for an enum.
    ///
    /// Implementations should provide specialiations of this type to enable
    /// to_string and from_string functionality with \c enum_cast
    //////////////////////////////////////////////////////////////////////////
    template<typename Enum>
    struct enum_traits
    {
      /// \brief Converts the enum to a given string
      ///
      /// This function only asserts or throws without a specialization
      static string_view to_string( Enum e );

      /// \brief Converts the string to an enum
      ///
      /// This function only asserts or throws without a specialization
      static Enum from_string( string_view s );
    };

    //////////////////////////////////////////////////////////////////////////
    /// \brief A range for enumerable values
    ///
    //////////////////////////////////////////////////////////////////////////
    template<typename Enum>
    class enum_range
    {
      static_assert( has_enum_sequence<Enum>::value, "Enum type doesn't have a specialization of enum_sequence" );

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
  } // namespace stl
} // namespace bit

#include "detail/enum.inl"

#endif /* BIT_STL_ENUM_HPP */
