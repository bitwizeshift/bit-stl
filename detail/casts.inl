#ifndef BIT_CORE_DETAIL_CASTS_INL
#define BIT_CORE_DETAIL_CASTS_INL

namespace bit {

  namespace detail {

    /// Casting between types of the same signs
    template<bool from_is_signed, bool to_is_signed>
    struct narrow_cast_helper{
      template<typename To, typename From>
      static inline To cast( From from )
      {
        BIT_ASSERT( from > std::numeric_limits<To>::min(), "Number to cast exceeds numeric limits.", from, std::numeric_limits<To>::min() );
        BIT_ASSERT( from < std::numeric_limits<To>::max(), "Number to cast exceeds numeric limits.", from, std::numeric_limits<To>::max() );
        return static_cast<To>(from);
      }
    };

    // -------------------------------------------------------------------------

    /// Cast unsigned-to-signed
    template<>
    struct narrow_cast_helper<false,true>
    {
      template<typename To, typename From>
      static inline To cast( From from )
      {
        typedef typename std::make_signed<From>::type signed_type;
        BIT_ASSERT( static_cast<signed_type>(from) > std::numeric_limits<To>::min(), "Number to cast exceeds numeric limits.", from, std::numeric_limits<To>::min() );
        BIT_ASSERT( from < std::numeric_limits<To>::max(), "Number to cast exceeds numeric limits.", from, std::numeric_limits<To>::max() );
        return static_cast<To>(from);
      }
    };

    // -------------------------------------------------------------------------

    /// Cast signed-to-unsigned
    template<>
    struct narrow_cast_helper<true,false>
    {
      // Cast signed-to-unsigned
      template<typename To, typename From>
      static inline To cast( From from )
      {
        typedef typename std::make_unsigned<From>::type unsigned_type;
        BIT_ASSERT( from >= std::numeric_limits<To>::min(), "Number to cast exceeds numeric limits.", from, std::numeric_limits<To>::min() );
        BIT_ASSERT( static_cast<unsigned_type>(from) <= std::numeric_limits<To>::max(), "Number to cast exceeds numeric limits.", from, std::numeric_limits<To>::max() );
        return static_cast<To>(from);
      }
    };

  } // namespace detail

  //--------------------------------------------------------------------------
  // Casts
  //--------------------------------------------------------------------------

  template<typename To, typename From>
  inline To narrow_cast( From from ) noexcept
  {
    static_assert( std::is_integral<To>::value, "Type casted to must be integral" );
    static_assert( std::is_integral<From>::value, "Type casted from must be integral" );

#ifdef BIT_DEBUG
    constexpr bool is_arithmetic = std::is_arithmetic<To>::value && std::is_arithmetic<From>::value;
    static_assert(is_arithmetic,"Values to cast must be numeric.");

    using cast_type = detail::narrow_cast_helper<(std::is_signed<From>::value),(std::is_signed<To>::value)>;
    return cast_type::template cast<To,From>(from);
#else // If compiling in non-debug, then assume static cast
    return static_cast<To>(from);
#endif
  }

  // -------------------------------------------------------------------------

  template<typename To, typename From>
  inline To pointer_cast( From ptr ) noexcept
  {
    BIT_ASSERT( static_cast<To>(ptr) == dynamic_cast<To>(ptr), "Destination type is not dynamically castable.", ptr );

    return static_cast<To>(ptr);
  }

  // -------------------------------------------------------------------------

  template<typename To, typename From>
  inline To copy_cast(const From& from)
    noexcept
  {
    struct Unnamed{
      To   to;
    } value = {};

    std::memcpy(
      static_cast<byte*>( static_cast<void*>(&value.to) ),
      static_cast<const byte*>( static_cast<const void*>(&from) ),
      ((sizeof(From) < sizeof(To)) ? sizeof(From) : sizeof(To))
    );
    return value.to;
  }

  template<typename To, typename From>
  inline To byte_cast( const From& from )
    noexcept
  {
    static_assert( sizeof(To) >= sizeof(From), "Size of 'To' is less than 'From' bytes");
    static_assert( alignof(To) <= alignof(From), "Alignment of 'From' is insufficient for alignment of 'To'");

    const To* ptr = reinterpret_cast<const To*>(&from);
    return *ptr;
  }

  template<typename To, typename From>
  inline To byte_cast( const From* from )
    noexcept
  {
    static_assert( sizeof(To) >= sizeof(From), "Size of 'To' is less than 'From' bytes");
    static_assert( alignof(To) <= alignof(From), "Alignment of 'From' is insufficient for alignment of 'To'");

    const To* ptr = reinterpret_cast<const To*>(from);
    return *ptr;
  }

} // namespace bit

#endif /* BIT_CORE_DETAIL_CASTS_INL */
