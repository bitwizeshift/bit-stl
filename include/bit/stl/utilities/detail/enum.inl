#ifndef BIT_STL_UTILITIES_DETAIL_ENUM_INL
#define BIT_STL_UTILITIES_DETAIL_ENUM_INL

//----------------------------------------------------------------------------
// Inline Definitions
//----------------------------------------------------------------------------

template<typename Enum>
inline bit::stl::string_view
  bit::stl::enum_traits<Enum>::to_string( Enum )
{
  BIT_ASSERT_OR_THROW(bad_enum_cast,false,"bad_enum_cast: to_string functionality not implemented for given enum");
  return "";
}

template<typename Enum>
inline Enum
  bit::stl::enum_traits<Enum>::from_string( string_view )
{
  BIT_ASSERT_OR_THROW(bad_enum_cast,false,"bad_enum_cast: from_string functionality not implemented for given enum");
  return Enum();
}

template<typename Enum>
inline const Enum*
  bit::stl::enum_traits<Enum>::begin()
{
  BIT_ASSERT_OR_THROW(bad_enum_cast,false,"bad_enum_cast: begin functionality not implemented for given enum");
  return nullptr;
}

template<typename Enum>
inline const Enum*
  bit::stl::enum_traits<Enum>::end()
{
  BIT_ASSERT_OR_THROW(bad_enum_cast,false,"bad_enum_cast: end functionality not implemented for given enum");
  return nullptr;
}

template<typename Enum>
inline constexpr typename bit::stl::enum_range<Enum>::iterator
  bit::stl::enum_range<Enum>::begin()
  const noexcept
{
  return iterator{ bit::stl::enum_traits<Enum>::begin() };
}

template<typename Enum>
inline constexpr typename bit::stl::enum_range<Enum>::sentinel
  bit::stl::enum_range<Enum>::end()
  const noexcept
{
  return sentinel{ bit::stl::enum_traits<Enum>::end() };
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

namespace bit { namespace stl { inline namespace casts { namespace detail {

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

}}}} // namespace bit::stl::casts::detail

template<typename To, typename From>
To bit::stl::casts::enum_cast( From from )
{
  return detail::enum_caster<To,From>::cast( from );
}


//============================================================================
// Enum Operators
//============================================================================

//----------------------------------------------------------------------------
// Unary Operators
//----------------------------------------------------------------------------

template<typename Enum, typename>
inline constexpr Enum operator ~( Enum e )
  noexcept
{
  using enum_type = std::underlying_type_t<Enum>;
  return static_cast<Enum>(~static_cast<enum_type>(e));
}

//----------------------------------------------------------------------------
// Binary Operators
//----------------------------------------------------------------------------

template<typename Enum, typename>
inline constexpr Enum bit::stl::enum_ops::operator|( Enum lhs, Enum rhs )
  noexcept
{
  using enum_type = std::underlying_type_t<Enum>;
  return static_cast<Enum>(static_cast<enum_type>(lhs) | static_cast<enum_type>(rhs));
}

template<typename Enum, typename>
inline constexpr Enum bit::stl::enum_ops::operator&( Enum lhs, Enum rhs )
  noexcept
{
  using enum_type = std::underlying_type_t<Enum>;
  return static_cast<Enum>(static_cast<enum_type>(lhs) & static_cast<enum_type>(rhs));
}

template<typename Enum, typename>
inline constexpr Enum bit::stl::enum_ops::operator^( Enum lhs, Enum rhs )
  noexcept
{
  using enum_type = std::underlying_type_t<Enum>;
  return static_cast<Enum>(static_cast<enum_type>(lhs) ^ static_cast<enum_type>(rhs));
}

template<typename Enum, typename Integer, typename>
inline constexpr Enum bit::stl::enum_ops::operator <<( Enum lhs, Integer rhs )
  noexcept
{
  using enum_type = std::underlying_type_t<Enum>;

  return static_cast<Enum>(static_cast<enum_type>(lhs) << rhs);
}

template<typename Enum, typename Integer, typename>
inline constexpr Enum bit::stl::enum_ops::operator >>( Enum lhs, Integer rhs )
  noexcept
{
  using enum_type = std::underlying_type_t<Enum>;

  return static_cast<Enum>(static_cast<enum_type>(lhs) >> rhs);
}

//----------------------------------------------------------------------------
// Compound Operators
//----------------------------------------------------------------------------

template<typename Enum, typename>
inline Enum& bit::stl::enum_ops::operator |=( Enum& lhs, Enum rhs )
  noexcept
{
  return lhs = (lhs | rhs);
}

template<typename Enum, typename>
inline Enum& bit::stl::enum_ops::operator &=( Enum& lhs, Enum rhs )
  noexcept
{
  return lhs = (lhs & rhs);
}

template<typename Enum, typename>
inline Enum& bit::stl::enum_ops::operator ^=( Enum& lhs, Enum rhs )
  noexcept
{
  return lhs = (lhs ^ rhs);
}

template<typename Enum, typename Integer, typename>
inline Enum& bit::stl::enum_ops::operator <<=( Enum& lhs, Integer rhs )
  noexcept
{
  return lhs = (lhs << rhs);
}

template<typename Enum, typename Integer, typename>
inline Enum& bit::stl::enum_ops::operator >>=( Enum& lhs, Integer rhs )
  noexcept
{
  return lhs = (lhs >> rhs);
}

#endif /* BIT_STL_UTILITIES_DETAIL_ENUM_INL */
