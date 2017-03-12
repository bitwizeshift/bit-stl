#ifndef BIT_STL_DETAIL_CASTS_INL
#define BIT_STL_DETAIL_CASTS_INL

//----------------------------------------------------------------------------
// Casts
//----------------------------------------------------------------------------

template<typename To, typename From>
inline constexpr To bit::stl::narrow_cast( From from ) noexcept
{
  static_assert( std::is_integral<To>::value, "Type casted to must be integral" );
  static_assert( std::is_integral<From>::value, "Type casted from must be integral" );

#ifdef BIT_DEBUG
  To to = static_cast<To>(from);
  BIT_ASSERT_OR_THROW(bad_narrow_cast, static_cast<From>(to) != from, "narrow_cast: unable to perform narrowing");
  BIT_ASSERT_OR_THROW(bad_narrow_cast, (!is_same_sign<To, From>::value && ((to < To{}) != (from < From{}))), "narrow_cast: unable to perform narrowing");

  return to;
#else // If compiling in non-debug, then assume static cast
  return static_cast<To>(from);
#endif
}

//----------------------------------------------------------------------------

template<typename To, typename From>
inline To bit::stl::pointer_cast( From ptr ) noexcept
{
  BIT_ASSERT_OR_THROW(bad_pointer_cast, static_cast<To>(ptr) == dynamic_cast<To>(ptr), "pointer_cast: destination type is not dynamically castable");

  return static_cast<To>(ptr);
}

//----------------------------------------------------------------------------

template<typename To, typename From>
inline To bit::stl::copy_cast(const From& from)
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

#endif /* BIT_STL_DETAIL_CASTS_INL */
