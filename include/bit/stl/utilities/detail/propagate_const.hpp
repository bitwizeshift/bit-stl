/**
 * \file propagate_const.hpp
 *
 * \brief This header contains a utility for propagating const to pointer
 *        types
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_UTILITIES_DETAIL_UTILITY_PROPAGATE_CONST_HPP
#define BIT_STL_UTILITIES_DETAIL_UTILITY_PROPAGATE_CONST_HPP

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief A wrapper to propagate the const qualifier
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class propagate_const
    {

      template<typename U>
      using is_enabled_and_explicit = conjunction<
        std::is_constructible<T, U&&>,
        negation<std::is_convertible<U&&, T>>
      >;

      template<typename U>
      using is_enabled_and_implicit = conjunction<
        std::is_constructible<T, U&&>,
        std::is_convertible<U&&, T>
      >;

      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using element_type = std::remove_reference_t<decltype(*std::declval<T&>())>;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      constexpr propagate_const() = default;

      constexpr propagate_const( propagate_const&& p ) = default;

#ifndef BIT_DOXYGEN_BUILD
      template<typename U, std::enable_if_t<is_enabled_and_explicit<U>::value>* = nullptr>
#else
      template<typename U>
#endif
      constexpr propagate_const( propagate_const<U>&& pu );

#ifndef BIT_DOXYGEN_BUILD
      template<typename U, std::enable_if_t<is_enabled_and_implicit<U>::value>* = nullptr>
#else
      template<typename U>
#endif
      explicit constexpr propagate_const( propagate_const<U>&& pu );

#ifndef BIT_DOXYGEN_BUILD
      template<typename U, std::enable_if_t<is_enabled_and_explicit<U>::value>* = nullptr>
#else
      template<typename U>
#endif
      constexpr propagate_const( U&& u );

#ifndef BIT_DOXYGEN_BUILD
      template<typename U, std::enable_if_t<is_enabled_and_implicit<U>::value>* = nullptr>
#else
      template<typename U>
#endif
      explicit constexpr propagate_const( U&& u );

      propagate_const( const propagate_const& ) = delete;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      constexpr propagate_const& operator=( propagate_const&& p ) = default;

      template<typename U>
      constexpr propagate_const& operator=( propagate_const<U>&& pu );

      template<typename U>
      constexpr propagate_const& operator=( U&& u );

      propagate_const& operator=( const propagate_const& ) = delete;

      //----------------------------------------------------------------------
      // Member Functions
      //----------------------------------------------------------------------
    public:

      constexpr void swap( propagate_const& pt );

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      constexpr element_type* get();

      constexpr const element_type* get() const;

      constexpr explicit operator bool() const;

      constexpr element_type& operator*();

      constexpr const element_type& operator*() const;

      constexpr element_type* operator->();

      constexpr const element_type* operator->() const;

      constexpr operator element_type*();

      constexpr operator const element_type*() const;

    };
  } // namespace stl
} // namespace bit

#endif /* BIT_STL_UTILITIES_DETAIL_UTILITY_PROPAGATE_CONST_HPP */
