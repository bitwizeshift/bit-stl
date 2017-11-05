/**
 * \file propagate_const.hpp
 *
 * \brief This header contains a utility for propagating const to pointer
 *        types
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_UTILITIES_PROPAGATE_CONST_HPP
#define BIT_STL_UTILITIES_PROPAGATE_CONST_HPP

#include "../traits/properties/is_explicitly_convertible.hpp"
#include "../traits/bool_constant.hpp"

#include <type_traits> // std::remove_reference_t, etc
#include <utility>     // std::forward, std::move

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief A wrapper to propagate the const qualifier
    ///
    /// \tparam T the underlying type that has pointer-semantics to propagate
    ///           constness to
    //////////////////////////////////////////////////////////////////////////
    template<typename T>
    class propagate_const
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using element_type = std::remove_reference_t<decltype(*std::declval<T&>())>;

      //----------------------------------------------------------------------
      // Constructors / Assignment
      //----------------------------------------------------------------------
    public:

      // (1)
      /// \brief Default-constructs the underlying type
      constexpr propagate_const() = default;

      // (2)
      /// \brief Move-constructs this propagate_const from an existing one
      ///
      /// \param other the propagate_const to move
      constexpr propagate_const( propagate_const&& other ) = default;

      // (3)
      /// \brief Initializes the underlying type by direct-non-list-initialization
      ///
      /// \note This constructor does not participate in overload resolution
      ///       unless std::is_constructible<T, U&&>::value is true, and is
      ///       explicit if and only if std::is_convertible<U&&, T>::value is
      ///       false
      ///
      /// \param pu the propagate_const to move
#ifdef BIT_DOXYGEN_BUILD
      template<typename U>
      constexpr propagate_const( propagate_const<U>&& pu );
#else
      template<typename U, std::enable_if_t<is_explicitly_convertible<U&&,T>::value>* = nullptr>
      constexpr propagate_const( propagate_const<U>&& pu );

      template<typename U, std::enable_if_t<!is_explicitly_convertible<U&&,T>::value>* = nullptr>
      explicit constexpr propagate_const( propagate_const<U>&& pu );
#endif

      // (4)
      /// \brief Initializes the underlying type by direct-non-list-initializatio
      ///
      /// \note This constructor does not participate in overload resolution
      ///       unless std::is_constructible<T, U&&>::value is true and
      ///       std::decay_t<U> is not a specialization of propagate_const. This
      ///       constructor is explicit if and only if
      ///       std::is_convertible<U&&, T>::value is false
      ///
      /// \param u the entry to forward to the underlying type
#ifdef BIT_DOXYGEN_BUILD
      template<typename U>
      constexpr propagate_const( U&& u );
#else
      template<typename U, std::enable_if_t<is_explicitly_convertible<U&&,T>::value && !std::is_same<std::decay_t<U>,propagate_const>::value>* = nullptr>
      constexpr propagate_const( U&& u );

      template<typename U, std::enable_if_t<!is_explicitly_convertible<U&&,T>::value && !std::is_same<std::decay_t<U>,propagate_const>::value>* = nullptr>
      explicit constexpr propagate_const( U&& u );
#endif

      // (5)
      // Explicitly deleted copy constructor
      propagate_const( const propagate_const& other ) = delete;

      //----------------------------------------------------------------------

      /// \brief Move-assigns this propagate_const from an existing one
      ///
      /// \param p the other propagate_const to move
      /// \return reference to \c (*this)
      propagate_const& operator=( propagate_const&& p ) = default;

      /// \brief Move-assigns the underlying type from the propagate_const to
      ///        this one
      ///
      /// \param pu the propagate_const to move
      /// \return reference to \c (*this)
#ifdef BIT_DOXYGEN_BUILD
      template<typename U>
      propagate_const& operator=( propagate_const<U>&& pu );
#else
      template<typename U, typename = std::enable_if_t<std::is_convertible<U&&,T>::value>>
      propagate_const& operator=( propagate_const<U>&& pu );
#endif

      /// \brief Forwards the entry to the underlying propagate_const
      ///
      /// \param u the value to forward
      /// \return reference to \c (*this)
#ifdef BIT_DOXYGEN_BUILD
      template<typename U>
      propagate_const& operator=( U&& u );
#else
      template<typename U, typename = std::enable_if_t<std::is_convertible<U&&,T>::value && !std::is_same<std::decay_t<U>,propagate_const>::value>>
      propagate_const& operator=( U&& u );
#endif

      // (5)
      // Deleted copy constructor
      propagate_const& operator=( const propagate_const& ) = delete;

      //-----------------------------------------------------------------------
      // Modifiers
      //-----------------------------------------------------------------------
    public:

      /// \brief Swaps this propagate_const with \p other
      ///
      /// \param other the otehr propagate_const to swap
      constexpr void swap( propagate_const& other ) noexcept;

      //-----------------------------------------------------------------------
      // Observers
      //-----------------------------------------------------------------------
    public:

      /// \{
      /// \brief Gets the underlying pointer type
      ///
      /// \return If T is an object pointer type, then m_t. Otherwise, m_t.get()
      constexpr element_type* get();
      constexpr const element_type* get() const;
      /// \}

      //-----------------------------------------------------------------------

      /// \brief Implicitly convertible to \c true if the underlying type has
      ///        a value
      ///
      /// \return \c true if the underlying type is not nullptr
      constexpr explicit operator bool() const;

      //-----------------------------------------------------------------------

      /// \{
      constexpr element_type& operator*();
      constexpr const element_type& operator*() const;
      /// \}

      /// \{
      constexpr element_type* operator->();
      constexpr const element_type* operator->() const;
      /// \}

      //-----------------------------------------------------------------------

      /// \{
      /// \brief Provides implicit conversions to element_type* and
      ///        const element_type*
#ifdef BIT_DOXYGEN_BUILD
      constexpr operator element_type*();
      constexpr operator const element_type*() const;
#else
      template<typename U=T, typename = std::enable_if_t<std::is_pointer<U>::value || std::is_convertible<U,element_type*>::value>>
      constexpr operator element_type*()
      {
        return m_pointer;
      }

      template<typename U=T, typename = std::enable_if_t<std::is_pointer<U>::value || std::is_convertible<U,const element_type*>::value>>
      constexpr operator const element_type*() const
      {
        return m_pointer;
      }
#endif
      /// \}

      //-----------------------------------------------------------------------
      // Private Implementation
      //-----------------------------------------------------------------------
    private:

      /// \{
      /// \brief Gets the underlying pointer type, either by returning the type
      ///        itself if it is a pointer, or by calling \c T::get()
      ///
      /// \return the underlying pointer
      constexpr element_type* get_impl( std::true_type );
      constexpr const element_type* get_impl( std::true_type ) const;
      constexpr element_type* get_impl( std::false_type );
      constexpr const element_type* get_impl( std::false_type ) const;
      /// \}

      //-----------------------------------------------------------------------
      // Private Members
      //-----------------------------------------------------------------------
    private:

      T m_pointer;

      template<typename U>
      friend constexpr std::size_t hash_value( const propagate_const<U>& v ) noexcept;
    };

    //=========================================================================
    // Free Functions
    //=========================================================================

    //-------------------------------------------------------------------------
    // Utilities
    //-------------------------------------------------------------------------

    /// \brief Swaps the two propagate_consts
    ///
    /// \param lhs the left entry to swap
    /// \param rhs the right entry to swap
    template<typename T>
    constexpr void swap( propagate_const<T>& lhs,
                         propagate_const<T>& rhs ) noexcept;

    /// \brief Hashes the value of the underlying type of the propagate_const
    ///
    /// \param v the value to hash
    /// \return the hashed value
    template<typename T>
    constexpr std::size_t hash_value( const propagate_const<T>& v ) noexcept;
  } // namespace stl
} // namespace bit

#include "detail/propagate_const.inl"

#endif /* BIT_STL_UTILITIES_PROPAGATE_CONST_HPP */
