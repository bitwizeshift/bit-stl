/*****************************************************************************
 * \file
 * \brief This header contains an implementation of c++17's \c std::optional
 *****************************************************************************/

/*
  The MIT License (MIT)

  Bit Standard Template Library.
  https://github.com/bitwizeshift/bit-stl

  Copyright (c) 2018 Matthew Rodusek

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#ifndef BIT_STL_UTILITIES_OPTIONAL_HPP
#define BIT_STL_UTILITIES_OPTIONAL_HPP

#include "utility.hpp"
#include "in_place.hpp" // in_place_t

#include "../traits/composition/conjunction.hpp"
#include "../traits/composition/disjunction.hpp"
#include "../traits/composition/negation.hpp"

#include <initializer_list>
#include <type_traits>
#include <memory>

namespace bit {
  namespace stl {

    template<typename> class optional;

    //------------------------------------------------------------------------
    // Optional SFINAE type traits
    //------------------------------------------------------------------------

    namespace detail {

      template<typename T, typename U>
      struct optional_is_enabled_ctor_base : negation<
        disjunction<
          std::is_constructible<T, optional<U>&>,
          std::is_constructible<T, const optional<U>&>,
          std::is_constructible<T, optional<U>&&>,
          std::is_constructible<T, const optional<U>&&>,

          std::is_convertible<optional<U>&, T>,
          std::is_convertible<const optional<U>&, T>,
          std::is_convertible<optional<U>&&, T>,
          std::is_convertible<const optional<U>&&, T>
        >
      >{};

      template<typename T, typename U>
      struct optional_is_enabled_copy_ctor : conjunction<
      optional_is_enabled_ctor_base<T,U>,
        std::is_constructible<T,const U&>
      >{};

      template<typename T, typename U>
      struct optional_is_enabled_move_ctor : conjunction<
      optional_is_enabled_ctor_base<T,U>,
        std::is_constructible<T, U&&>
      >{};

      template<typename T, typename U>
      struct optional_is_enabled_assignment_base : negation<
        disjunction<
          std::is_constructible<T, optional<U>&>,
          std::is_constructible<T, const optional<U>&>,
          std::is_constructible<T, optional<U>&&>,
          std::is_constructible<T, const optional<U>&&>,

          std::is_convertible<optional<U>&, T>,
          std::is_convertible<const optional<U>&, T>,
          std::is_convertible<optional<U>&&, T>,
          std::is_convertible<const optional<U>&&, T>,

          std::is_assignable<T&, optional<U>&>,
          std::is_assignable<T&, const optional<U>&>,
          std::is_assignable<T&, optional<U>&&>,
          std::is_assignable<T&, const optional<U>&&>
        >
      >{};

      template<typename T, typename U>
      struct optional_is_enabled_copy_assignment : conjunction<
        optional_is_enabled_assignment_base<T,U>,
        std::is_assignable<T&, const U&>,
        std::is_constructible<T, const U&>
      >{};

      template<typename T, typename U>
      struct optional_is_enabled_move_assignment : conjunction<
        optional_is_enabled_assignment_base<T,U>,
        std::is_assignable<T&, U&&>,
        std::is_constructible<T, U&&>
      >{};

      template<typename T, typename U>
      struct optional_is_direct_initializable : conjunction<
        std::is_constructible<T, U&&>,
        negation<std::is_same<std::decay_t<U>,in_place_t>>,
        negation<std::is_same<std::decay_t<U>,optional<T>>>
      >{};

      template<typename T, typename U>
      struct optional_is_direct_init_assignable : conjunction<
        negation<std::is_same<std::decay_t<U>,optional<T>>>,
        std::is_constructible<T,U>,
        std::is_assignable<T,U>,
        disjunction<
          negation<std::is_scalar<U>>,
          negation<std::is_same<std::decay_t<U>,T>>
        >
      >{};

    } // namespace detail

    ////////////////////////////////////////////////////////////////////////////
    /// \brief An exception thrown when an optional is attempted to be accessed
    ///        while not containing a value
    ////////////////////////////////////////////////////////////////////////////
    class bad_optional_access : public std::logic_error
    {
    public:
      bad_optional_access() : std::logic_error("bad_optional_access"){}

    };

    /// \brief This type represents null optional value
    struct nullopt_t
    {
      nullopt_t() = delete;
      constexpr nullopt_t(int){}
    };

    /// \brief Instance of a nullopt type
    constexpr nullopt_t nullopt = nullopt_t(0);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The class template optional manages an optional contained value,
    ///        i.e. a value that may or may not be present.
    ///
    /// A common use case for optional is the return value of a function that
    /// may fail. As opposed to other approaches, such as std::pair<T,bool>,
    /// optional handles expensive to construct objects well and is more
    /// readable, as the intent is expressed explicitly.
    ///
    /// Any instance of optional<T> at any given point in time either contains a
    /// value or does not contain a value.
    ///
    /// If an optional<T> contains a value, the value is guaranteed to be
    /// allocated as part of the optional object footprint, i.e. no dynamic
    /// memory allocation ever takes place. Thus, an optional object models an
    /// object, not a pointer, even though the operator*() and operator->()
    /// are defined.
    ///
    /// When an object of type optional<T> is contextually converted to bool,
    /// the conversion returns true if the object contains a value and false if
    /// it does not contain a value.
    ///
    /// The optional object contains a value in the following conditions:
    /// - The object is initialized with a value of type T
    /// - The object is assigned from another optional that contains a value.
    /// - The object does not contain a value in the following conditions:
    /// - The object is default-initialized.
    /// - The object is initialized with a value of nullopt_t or an optional
    ///   object that does not contain a value.
    /// - The object is assigned from a value of nullopt_t or from an optional
    ///   that does not contain a value
    ///
    /// \tparam T the underlying type
    ////////////////////////////////////////////////////////////////////////////
    template<typename T>
    class optional
    {
      //------------------------------------------------------------------------
      // Public Member Types
      //------------------------------------------------------------------------
    public:

      using value_type = T;

      //------------------------------------------------------------------------
      // Constructor / Destructor
      //------------------------------------------------------------------------
    public:

      /// \brief Constructs an optional that does not contain a value
      constexpr optional() noexcept;

      /// \brief Constructs an optional that does not contain a value
      constexpr optional( nullopt_t );

      /// \brief Copy constructs an optional
      ///
      /// If \p other contains a value, initializes the contained value as if
      /// direct-initializing (but not direct-list-initializing) an object of
      /// type T with the expression *other.
      ///
      /// If other does not contain a value, constructs an object that does
      /// not contain a value.
      ///
      /// \param other the optional to copy
      optional( const optional& other );

      /// \brief Copy constructs an optional of type U
      ///
      /// \param other the optional to copy
      template<typename U, std::enable_if_t<detail::optional_is_enabled_copy_ctor<T,U>::value>* = nullptr>
      optional( const optional<U>& other );

      /// \brief Move constructs an optional of type U
      ///
      /// \param other the optional to move
      template<typename U, std::enable_if_t<detail::optional_is_enabled_move_ctor<T,U>::value>* = nullptr>
      optional( optional<U>&& other );

      /// \brief Move constructs an optional
      ///
      /// If other contains a value, initializes the contained value as if
      /// direct-initializing (but not direct-list-initializing) an object
      /// of type T with the expression std::move(*other) and does not make
      /// other empty: a moved-from optional still contains a value, but the
      /// value itself is moved from.
      ///
      /// If other does not contain a value, constructs an object that does
      /// not contain a value.
      ///
      /// \param other the optional to move
      optional( optional&& other );

      /// \brief Constructs an optional object that contains a value
      ///
      /// The value is initialized as if direct-initializing (but not
      /// direct-list-initializing) an object of type T with the expression
      /// value.
      ///
      /// \note This constructor is constexpr if the constructor of T
      ///       selected by direct-initialization is constexpr
      ///
      /// \param value the value to copy
      constexpr optional( const value_type& value );

      /// \brief Constructs an optional object that contains a value
      ///
      /// The value is initialized as if direct-initializing (but not
      /// direct-list-initializing) an object of type T with the expression
      /// std::move(value).
      ///
      /// \note This constructor is constexpr if the constructor of T selected
      ///       by direct-initialization is constexpr
      ///
      /// \param value the value to move
      constexpr optional( value_type&& value );

      /// \brief Constructs an optional object that contains a value
      ///
      /// the value is initialized as if direct-initializing (but not
      /// direct-list-initializing) an object of type T from the arguments
      /// std::forward<Args>(args)...
      ///
      /// \param tag     The in_place tag
      /// \param args... the arguments to pass to T's constructor
      template<typename...Args>
      constexpr explicit optional( in_place_t tag, Args&&... args );

      /// \brief Constructs an optional object that contains a value
      ///
      /// the value is initialized as if direct-initializing (but not
      /// direct-list-initializing) an object of type T from the arguments
      /// std::forward<std::initializer_list<U>>(ilist), std::forward<Args>(args)...
      ///
      /// \param tag     The in_place tag
      /// \param ilist   An initializer list of entries to forward
      /// \param args... the arguments to pass to T's constructor
  #ifndef BIT_DOXYGEN_BUILD
      template<typename U, typename...Args,
               typename = std::enable_if_t<std::is_constructible<T, std::initializer_list<U>&, Args&&...>::value>>
  #else
      template<typename U, typename...Args>
  #endif
      constexpr explicit optional( in_place_t,
                                   std::initializer_list<U> ilist,
                                   Args&&...args );

      ~optional();


      //------------------------------------------------------------------------
      // Assignment
      //------------------------------------------------------------------------
    public:

      optional& operator=( nullopt_t );
      optional& operator=( const optional& other );
      optional& operator=( optional&& other );
      template<typename U, typename = typename std::is_same<typename std::decay<U>::type, T>::value>
      optional& operator=( U&& value );

      template<typename U, std::enable_if_t<detail::optional_is_enabled_copy_assignment<T,U>::value>* = nullptr>
      optional& operator=( const optional<U>& other );

      template<typename U, std::enable_if_t<detail::optional_is_enabled_move_assignment<T,U>::value>* = nullptr>
      optional& operator=( optional<U>&& other );

      //------------------------------------------------------------------------
      // Observers
      //------------------------------------------------------------------------
    public:

      constexpr value_type* operator->() noexcept;

      constexpr const value_type* operator->() const noexcept;

      constexpr value_type& operator*() & noexcept;

      constexpr value_type&& operator*() && noexcept;

      constexpr const value_type& operator*() const& noexcept;

      constexpr const value_type&& operator*() const&& noexcept;

      /// \brief Checks whether \c *this contains a value
      ///
      /// \return \c true if \c *this contains a value, \c false if \c *this
      ///         does not contain a value
      constexpr explicit operator bool() const noexcept;

      /// \brief Checks whether \c *this contains a value
      ///
      /// \return \c true if \c *this contains a value, \c false if \c *this
      ///         does not contain a value
      constexpr bool has_value() const noexcept;

      //------------------------------------------------------------------------

      /// \brief Returns the contained value.
      ///
      /// Equivalent to
      /// \code
      /// return bool(*this) ? *val : throw bad_optional_access();
      /// \endcode
      ///
      /// \throws bad_optional_access if \c *this does not contain a value.
      ///
      /// \return the value of \c *this
      constexpr value_type& value() &;

      /// \copydoc value() &
      constexpr const value_type& value() const &;

      /// \brief Returns the contained value.
      ///
      /// Equivalent to
      /// \code
      /// return bool(*this) ? std::move(*val) : throw bad_optional_access();
      /// \endcode
      ///
      /// \throws bad_optional_access if \c *this does not contain a value.
      ///
      /// \return the value of \c *this
      constexpr value_type&& value() &&;

      /// \copydoc value() &&
      constexpr const value_type&& value() const &&;

      //------------------------------------------------------------------------

      /// \brief Returns the contained value if \c *this has a value,
      ///        otherwise returns \p default_value.
      ///
      /// \param default_value the value to use in case \c *this is empty
      /// \return the value to use in case \c *this is empty
      template<typename U>
      constexpr value_type value_or( U&& default_value ) const &;

      /// \copydoc value_or( U&& )
      template<typename U>
      constexpr value_type value_or( U&& default_value ) &&;

      //------------------------------------------------------------------------
      // Modifiers
      //------------------------------------------------------------------------
    public:

      /// \brief Swaps the contents with those of other.
      ///
      /// \param other the optional object to exchange the contents with
      void swap( optional& other );

      /// \brief If \c *this contains a value, destroy that value as if by
      ///        \c value().T::~T().
      ///
      /// Otherwise, there are no effects. \c *this does not contain a value
      /// after this call.
      void reset() noexcept(std::is_nothrow_destructible<T>::value);

      /// \brief Constructs the contained value in-place.
      ///
      /// If \c *this already contains a value before the call, the contained
      /// value is destroyed by calling its destructor.
      ///
      /// \param args... the arguments to pass to the constructor
      template<typename...Args>
      void emplace( Args&&...args );

      /// \brief Constructs the contained value in-place.
      ///
      /// If \c *this already contains a value before the call, the contained
      /// value is destroyed by calling its destructor.
      ///
      /// \param ilist   the initializer list to pass to the constructor
      /// \param args... the arguments to pass to the constructor
      template<typename U,typename...Args >
      void emplace( std::initializer_list<U> ilist, Args&&...args );

      //------------------------------------------------------------------------
      // Private Member Types
      //------------------------------------------------------------------------
    private:

      using storage_type = typename std::aligned_storage<sizeof(T),alignof(T)>::type;

      //------------------------------------------------------------------------
      // Private Members
      //------------------------------------------------------------------------
    private:

      storage_type m_value;      ///< The value of this optional
      mutable bool m_has_value;  ///< Whether or not the optional has a value

      //------------------------------------------------------------------------
      // Private Member Functions
      //------------------------------------------------------------------------
    private:

      /// \brief Gets a pointer to the value type
      ///
      /// \return the pointer
      constexpr T* val() const noexcept;

      /// \brief Destructs the value of the optional if it is not trivially destructible
      void destruct() const;

    };

    //==========================================================================
    // Equality Operators
    //==========================================================================

    //--------------------------------------------------------------------------
    // Compare two optional objects
    //--------------------------------------------------------------------------

    /// \brief Performs equality operation on two optionals
    ///
    /// \param lhs an optional object on the left side to compare
    /// \param rhs an optional object on the right side to compare
    /// \return If bool(lhs) != bool(rhs), returns false
    ///         Otherwise, if bool(lhs) == false, returns true
    ///         Otherwise, returns *lhs == *rhs
    template<typename T>
    constexpr bool operator==( const optional<T>& lhs, const optional<T>& rhs );

    /// \brief Performs inequality operation on two optionals
    ///
    /// \param lhs an optional object on the left side to compare
    /// \param rhs an optional object on the right side to compare
    /// \return If bool(lhs) != bool(rhs), returns true
    ///         Otherwise, if bool(lhs) == false, returns false
    ///         Otherwise, returns *lhs == *rhs
    template<typename T>
    constexpr bool operator!=( const optional<T>& lhs, const optional<T>& rhs );

    /// \brief Performs less-than operation on two optionals
    ///
    /// \param lhs an optional object on the left side to compare
    /// \param rhs an optional object on the right side to compare
    /// \return If bool(rhs) == false, returns false
    ///         Otherwise, if bool(lhs) == false, returns true
    ///         Otherwise, returns *lhs < *rhs
    template<typename T>
    constexpr bool operator<( const optional<T>& lhs, const optional<T>& rhs );

    /// \brief Performs greater-than operation on two optionals
    ///
    /// \param lhs an optional object on the left side to compare
    /// \param rhs an optional object on the right side to compare
    /// \return If bool(lhs) == false, returns false
    ///         Otherwise, if bool(rhs) == false, returns true
    ///         Otherwise, returns *lhs > *rhs
    template<typename T>
    constexpr bool operator>( const optional<T>& lhs, const optional<T>& rhs );

    /// \brief Performs less-than or equal operation on two optionals
    ///
    /// \param lhs an optional object on the left side to compare
    /// \param rhs an optional object on the right side to compare
    /// \return If bool(lhs) == false, returns true
    ///         Otherwise, if bool(rhs) == false, returns false
    ///         Otherwise, returns *lhs <= *rhs
    template<typename T>
    constexpr bool operator<=( const optional<T>& lhs, const optional<T>& rhs );

    /// \brief Performs greater-than or equal operation on two optionals
    ///
    /// \param lhs an optional object on the left side to compare
    /// \param rhs an optional object on the right side to compare
    /// \return If bool(rhs) == false, returns true
    ///         Otherwise, if bool(lhs) == false, returns false
    ///         Otherwise, returns *lhs <= *rhs
    template<typename T>
    constexpr bool operator>=( const optional<T>& lhs, const optional<T>& rhs );

    //--------------------------------------------------------------------------
    // Compare an optional object with a nullopt
    //--------------------------------------------------------------------------

    template<typename T>
    constexpr bool operator==( const optional<T>& opt, nullopt_t ) noexcept;

    template<typename T>
    constexpr bool operator==( nullopt_t, const optional<T>& opt ) noexcept;

    template<typename T>
    constexpr bool operator!=( const optional<T>& opt, nullopt_t ) noexcept;

    template<typename T>
    constexpr bool operator!=( nullopt_t, const optional<T>& opt ) noexcept;

    template<typename T>
    constexpr bool operator<( const optional<T>& opt, nullopt_t ) noexcept;

    template<typename T>
    constexpr bool operator<( nullopt_t, const optional<T>& opt ) noexcept;

    template<typename T>
    constexpr bool operator>( const optional<T>& opt, nullopt_t ) noexcept;

    template<typename T>
    constexpr bool operator>( nullopt_t, const optional<T>& opt ) noexcept;

    template<typename T>
    constexpr bool operator<=( const optional<T>& opt, nullopt_t ) noexcept;

    template<typename T>
    constexpr bool operator<=( nullopt_t, const optional<T>& opt ) noexcept;

    template<typename T>
    constexpr bool operator>=( const optional<T>& opt, nullopt_t ) noexcept;

    template<typename T>
    constexpr bool operator>=( nullopt_t, const optional<T>& opt ) noexcept;

    //--------------------------------------------------------------------------
    // Compare an optional object with a T
    //--------------------------------------------------------------------------

    template<typename T>
    constexpr bool operator==( const optional<T>& opt, const T& value );

    template<typename T>
    constexpr bool operator==( const T& value, const optional<T>& opt );

    template<typename T>
    constexpr bool operator!=( const optional<T>& opt, const T& value );

    template<typename T>
    constexpr bool operator!=( const T& value, const optional<T>& opt );

    template<typename T>
    constexpr bool operator<( const optional<T>& opt, const T& value );

    template<typename T>
    constexpr bool operator<( const T& value, const optional<T>& opt );

    template<typename T>
    constexpr bool operator>( const optional<T>& opt, const T& value );

    template<typename T>
    constexpr bool operator>( const T& value, const optional<T>& opt );

    template<typename T>
    constexpr bool operator<=( const optional<T>& opt, const T& value );

    template<typename T>
    constexpr bool operator<=( const T& value, const optional<T>& opt );

    template<typename T>
    constexpr bool operator>=( const optional<T>& opt, const T& value );

    template<typename T>
    constexpr bool operator>=( const T& value, const optional<T>& opt );

    //--------------------------------------------------------------------------
    // Non-member functions
    //--------------------------------------------------------------------------

    /// \brief Creates an optional object from \p value
    ///
    /// \param value the value to construct the optional from
    template<typename T>
    constexpr optional<std::decay_t<T>> make_optional( T&& value );

    /// \brief Creates an optional object of type \p T from the given \p args
    ///
    /// \tparam T the type to construct
    /// \param args... the arguments to pass to \p T's constructor
    template<typename T, typename... Args >
    constexpr optional<T> make_optional( Args&&... args );

    /// \brief Creates an optional object of type \p T from the given
    ///        \p il \p args
    ///
    /// \tparam T the type to construct
    /// \param il      the initializer list to pass
    /// \param args... the arguments to pass to \p T's constructor
    template<typename T, typename U, typename... Args >
    constexpr optional<T> make_optional( std::initializer_list<U> il, Args&&... args );

    /// \brief Swaps \p lhs and \p rhs
    ///
    /// \param lhs the left optional to swap
    /// \param rhs the right optional to swap
    template<typename T>
    void swap( optional<T>& lhs, optional<T>& rhs );

    /// \brief Retrieves the hash from a given optional
    ///
    /// \param str the optional to retrieve the hash from
    /// \return the hash of the string
    template<typename T>
    constexpr std::size_t hash_value( const optional<T>& s ) noexcept;
  } // namespace stl
} // namespace bit

#include "detail/optional.inl"

#endif /* BIT_STL_UTILITIES_OPTIONAL_HPP */
