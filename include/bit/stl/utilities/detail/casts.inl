#ifndef BIT_STL_UTILITIES_DETAIL_CASTS_INL
#define BIT_STL_UTILITIES_DETAIL_CASTS_INL

//-----------------------------------------------------------------------------
// Casts
//-----------------------------------------------------------------------------

template<typename To, typename From, typename>
inline constexpr To bit::stl::casts::narrow_cast( From from ) noexcept
{
  To to = static_cast<To>(from);

  BIT_ASSERT( static_cast<From>(to) == from, "narrow_cast: narrowing error" );
  BIT_ASSERT( (is_same_sign<To, From>::value || (to < To{}) == (from < From{})),
              "narrow_cast: narrowing error" );

  return to;
}

//-----------------------------------------------------------------------------

template<typename To, typename From, typename>
inline To bit::stl::casts::pointer_cast( From ptr ) noexcept
{
  BIT_ASSERT( static_cast<To>(ptr) == dynamic_cast<To>(ptr),
              "pointer_cast: destination type is not dynamically castable" );

  return static_cast<To>(ptr);
}

//-----------------------------------------------------------------------------

template<typename To, typename From, typename>
inline To bit::stl::casts::copy_cast( const From& from )
  noexcept
{
  struct Unnamed{
    To   to;
  } value = {};

  std::memcpy(
    static_cast<void*>(&value.to),
    static_cast<const void*>(&from),
    (sizeof(From) < sizeof(To) ? sizeof(From) : sizeof(To))
  );
  return value.to;
}

//-----------------------------------------------------------------------------

template<typename To, typename From, typename>
inline To bit::stl::casts::implicit_cast( From&& from )
{
  return std::forward<From>(from);
}

#endif /* BIT_STL_UTILITIES_DETAIL_CASTS_INL */
