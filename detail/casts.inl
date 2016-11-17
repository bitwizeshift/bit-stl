#ifndef BIT_STL_DETAIL_CASTS_INL
#define BIT_STL_DETAIL_CASTS_INL

namespace bit {
  inline namespace stl {

    //------------------------------------------------------------------------
    // Casts
    //------------------------------------------------------------------------

    template<typename To, typename From>
    inline constexpr To narrow_cast( From from ) noexcept
    {
      static_assert( std::is_integral<To>::value, "Type casted to must be integral" );
      static_assert( std::is_integral<From>::value, "Type casted from must be integral" );

#ifdef BIT_DEBUG
      To to = static_cast<To>(from);
      if(static_cast<From>(to) != from) throw bad_narrow_cast();
      if(!is_same_sign<To, From>::value && ((to < To{}) != (from < From{})))
          throw bad_narrow_cast("narrowing_error");

      return to;
#else // If compiling in non-debug, then assume static cast
      return static_cast<To>(from);
#endif
    }

    // -----------------------------------------------------------------------

    template<typename To, typename From>
    inline To pointer_cast( From ptr ) noexcept
    {
      if( static_cast<To>(ptr) == dynamic_cast<To>(ptr) )
        throw bad_pointer_cast("bad_pointer_cast: destination type is not dynamically castable");

      return static_cast<To>(ptr);
    }

    // -----------------------------------------------------------------------

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
  } // inline namespace stl
} // namespace bit

#endif /* BIT_STL_DETAIL_CASTS_INL */
