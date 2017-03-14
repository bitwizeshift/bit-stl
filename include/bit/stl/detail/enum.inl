#ifndef BIT_STL_DETAIL_ENUM_INL
#define BIT_STL_DETAIL_ENUM_INL

//----------------------------------------------------------------------------
// Inline Definitions
//----------------------------------------------------------------------------

template<typename Enum>
inline bit::stl::string_view
  bit::stl::enum_traits<Enum>::to_string( Enum e )
{
//  BIT_ASSERT_OR_THROW(bad_enum_cast,false,"bad_enum_cast: to_string functionality not implemented for given enum");
  return "";
}

template<typename Enum>
inline Enum
  bit::stl::enum_traits<Enum>::from_string( string_view s )
{
//  BIT_ASSERT_OR_THROW(bad_enum_cast,false,"bad_enum_cast: from_string functionality not implemented for given enum");
  return Enum();
}

template<typename Enum>
inline constexpr typename bit::stl::enum_range<Enum>::iterator
  bit::stl::enum_range<Enum>::begin()
  const noexcept
{
  return iterator{ bit::stl::enum_sequence<Enum>::begin };
}

template<typename Enum>
inline constexpr typename bit::stl::enum_range<Enum>::sentinel
  bit::stl::enum_range<Enum>::end()
  const noexcept
{
  return sentinel{ bit::stl::enum_sequence<Enum>::end };
}

template<typename Enum>
inline constexpr bit::stl::enum_range<Enum>
  bit::stl::make_enum_range()
{
  return enum_range<Enum>();
}

//----------------------------------------------------------------------------
// Enum Casts
//----------------------------------------------------------------------------

namespace bit {
namespace stl {
inline namespace casts {
namespace detail {

  template<typename To, typename From>
  struct enum_caster;

  template<typename Enum>
  struct enum_caster<string_view,Enum>
  {
    static string_view cast( Enum e )
    {
      return enum_traits<Enum>::to_string( e );
    }
  };

  template<typename Enum>
  struct enum_caster<std::string,Enum>
  {
    static std::string cast( Enum e )
    {
      return enum_traits<Enum>::to_string( e );
    }
  };

  template<typename Enum>
  struct enum_caster<Enum,string_view>
  {
    static Enum cast( string_view s )
    {
      return enum_traits<Enum>::from_string( s );
    }
  };

  template<typename Enum>
  struct enum_caster<Enum,const char*>
  {
    static Enum cast( string_view s )
    {
      return enum_traits<Enum>::from_string( s );
    }
  };

  template<typename Enum>
  struct enum_caster<Enum,std::string>
  {
    static Enum cast( string_view s )
    {
      return enum_traits<Enum>::from_string( s );
    }
  };

} // namespace detail
} // inline namespace casts
} // namespace stl
} // namespace bit

template<typename To, typename From>
To bit::stl::casts::enum_cast( From from )
{
  return detail::enum_caster<To,From>::cast( from );
}

#endif /* BIT_STL_DETAIL_ENUM_INL */
