/**
 * \file utility.hpp
 *
 * \brief This header contains extensions to the standard 'utility' header
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_UTILITIES_UTILITY_HPP
#define BIT_STL_UTILITIES_UTILITY_HPP

// bit::stl libraries

#include "../traits/identity.hpp"
#include "../traits/void_t.hpp"

// std libraries
#include <type_traits> // for std::remove_reference
#include <utility>     // for std::forward
#include <stdexcept>   // for std::out_of_range

namespace bit {
  namespace stl {

    /// \brief A wrapper around std::forward that removes the need for
    ///        specifying the type T.
    ///
    /// \param x the value to forward
    template<typename T>
    constexpr decltype(auto) fwd(T&& x) noexcept;

    //--------------------------------------------------------------------------
    // Indexing
    //--------------------------------------------------------------------------

    namespace detail {

      template<typename T, typename Key, typename = void>
      struct has_at : std::false_type{};

      template<typename T, typename Key>
      struct has_at<
        T,
        Key,
        void_t<decltype(std::declval<T>().at( std::declval<Key>() ))>
      > : std::true_type{};

    } // namespace detail

    /// \brief Safely retrieves the value at the given index, otherwise asserts
    ///
    /// \param array reference to the array to index into
    /// \param n     the index to retrieve
    /// \return reference to instance
    template<typename T, std::size_t N>
    constexpr T& at( T (&array)[N], std::size_t n );

    /// \brief Safely retrieves the value at the given index, otherwise asserts
    ///
    /// \param array reference to the array to index into
    /// \param n     the index to retrieve
    /// \return reference to instance
#ifndef BIT_DOXYGEN_BUILD
    template<typename Container, typename Key, typename = std::enable_if_t<detail::has_at<Container,Key>::value>>
#else
    template<typename Container, typename Key>
#endif
    constexpr decltype(auto) at( Container& container, Key&& key );

    //--------------------------------------------------------------------------
    // Tuple Applications
    //--------------------------------------------------------------------------

    /// \brief Construct an object of type T, using the elements of the tuple t as
    ///        the arguments to the constructor
    ///
    /// \tparam T the type to construct
    /// \param t tuple whose elements to be used as arguments to the constructor of T
    /// \return The constructed T object
    template <typename T, typename Tuple>
    constexpr T make_from_tuple( Tuple&& t );

    /// \brief Invoke the Callable object f with a tuple of arguments
    ///
    /// \param f Callable object to be invoked
    /// \param t tuple whose elements to be used as arguments to \p f
    /// \return The value returned from invoking \p f with \p t's elements
    template <typename F, typename Tuple>
    constexpr decltype(auto) apply( F&& f, Tuple&& t );

    //------------------------------------------------------------------------
    //
    //------------------------------------------------------------------------

    namespace detail {

      template<typename Ptr>
      struct type_of_member_ptr;

      template<typename T, typename U>
      struct type_of_member_ptr<U T::*> : identity<U>{};

      template<typename Ptr>
      using type_of_member_t = typename type_of_member_ptr<Ptr>::type;

    } // namespace detail

    template<typename T>
    class underlying_container_type
    {
    private:
      struct I : private T{
        using type = typename detail::type_of_member_ptr<decltype(&I::c)>::type;
      };
    public:
      using type = typename I::type;
    };

    template<typename T>
    using underlying_container_type_t = typename underlying_container_type<T>::type;

    /// \brief Gets the underlying container of a given container adapter
    ///
    /// \param container reference to the container adapter
    /// \return reference to the underlying container
    template<typename Container, underlying_container_type_t<Container>* = nullptr>
    underlying_container_type_t<Container>&
      get_underlying_container( Container& container );

  } // namespace stl
} // namespace bit

#include "detail/utility.inl"

#endif /* BIT_STL_UTILITIES_UTILITY_HPP */
