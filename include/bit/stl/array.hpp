/**
 * \file array.hpp
 *
 * \brief This header defines a utility for constructing arbitrary sized
 *        std::array types, with optional type-deduction
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_ARRAY_HPP
#define BIT_STL_ARRAY_HPP

#include <array>   // std::array
#include <utility> // std::forward

namespace bit {
  namespace stl {
    namespace detail {
      struct array_autodeduce{};

      template<typename T, typename...>
      struct array_return_type_helper { using type = T; };

      template<typename... Types>
      struct array_return_type_helper<array_autodeduce, Types...>
        : std::common_type<Types...> {};

      template<typename T, typename...Ts>
      using array_return_type_helper_t
        = typename array_return_type_helper<T,Ts...>::type;

      template<typename T, typename... Types>
      using array_return_type_t
        = std::array<array_return_type_helper_t<T, Types...>,sizeof...(Types)>;

    } // namespace details

    /// \brief Make utility for creating a std::array
    ///
    /// If the return type is explicitly specified, no deduction take place;
    /// if the type is ommitted, the return type is the common type of all
    /// inputs.
    ///
    /// \tparam T the return type of the array.
    /// \param args the arguments for the array
    /// \return an array containing the arguments
    template<typename T = detail::array_autodeduce, typename...Args>
    constexpr auto make_array(Args&&... args) noexcept
      -> detail::array_return_type_t<T, Args...>;

  } // namespace stl
} // namespace bit

#include "detail/array.inl"

#endif /* BIT_STL_ARRAY_HPP */
