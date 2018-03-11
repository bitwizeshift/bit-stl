/**
 * \file NullablePointer.hpp
 *
 * \brief This header defines the concept NullablePointer
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

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
#ifndef BIT_STL_CONCEPTS_NULLABLEPOINTER_HPP
#define BIT_STL_CONCEPTS_NULLABLEPOINTER_HPP

#include "EqualityComparable.hpp"
#include "Destructible.hpp"

#include "../traits/composition/void_t.hpp"
#include "../traits/composition/conjunction.hpp"
#include "../traits/composition/bool_constant.hpp"

#include <type_traits> // std::declval, std::decay_t

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T, typename = void>
      struct is_nullable_pointer_impl : false_type{};

      template<typename T>
      struct is_nullable_pointer_impl<T,
        void_t<
          decltype( T(nullptr) ),
          decltype( std::declval<T&>() = nullptr ),
          decltype( std::declval<T&>() != std::declval<T&>() ),
          decltype( std::declval<T&>() == nullptr ),
          decltype( nullptr == std::declval<T&>() ),
          decltype( std::declval<T&>() != nullptr ),
          decltype( nullptr != std::declval<T&>() )
        >
      > : conjunction<
        std::is_default_constructible<T>,
        std::is_copy_constructible<T>,
        std::is_copy_assignable<T>,
        is_destructible<T>,
        is_equality_comparable<T>
      >{};

    } // namespace detail

    /// \brief Type trait to determine if a given type is a Container
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    struct is_nullable_pointer : detail::is_nullable_pointer_impl<std::decay_t<T>>{};

    /// \brief Type trait to determine if a series of \c Types are all Containers
    ///
    /// \The result is stored in \c ::value
    template<typename...Types>
    struct are_nullable_pointers : conjunction<is_nullable_pointer<Types>...>{};

  } // namespace stl
} // namespace bit

///////////////////////////////////////////////////////////////////////////////
/// \concept{NullablePointer}
///
/// \brief Specifies that the type is a pointer-like object which can be
///        compared to std::nullptr_t objects.
///
/// ## Requirements
///
/// The type \c T satisfies \ref NullablePointer if it satisfies the
/// concept requirements:
///
/// - \ref EqualityComparable
/// - \ref DefaultConstructible
/// - \ref CopyConstructible
/// - \ref CopyAssignable
/// - \ref Destructible
///
/// In addition, a value-initialized object of the type must produce a null
/// value of that type. This null value shall only be equivalent to itself.
/// Default initialization of the type may have an indeterminate value.
///
/// An object of the type must be contextually convertible to bool. The effect
/// of this conversion returns false if the value is equivalent to its null
/// value and true otherwise.
///
/// None of the operations that this type performs may throw exceptions.
///
/// The type must satisfy the following additional expressions, given:
///
/// - \c p an instance of type \c T
/// - \c q an instance of type \c T
/// - \c np an instance of (possibly const qualified) \c std::nullptr_t
///
/// \code
/// T(nullptr)
/// \endcode
///
/// a temporary object that is equivalent to nullptr
///
/// \code
/// p = np
/// \endcode
///
/// Must return a Type&, and afterwards, p is equivalent to nullptr
///
/// \code
/// p != q
/// \endcode
///
/// Must return a value that is contextually convertible to bool.
///
/// The effect is !(p == q)
///
/// \code
/// p == np
/// np == p
/// \endcode
///
/// Must return a value that is contextually convertible to bool.
///
/// The effect is (p == Type())
///
/// \code
/// p != np
/// np != p
/// \endcode
///
/// Must return a value that is contextually convertible to bool.
///
/// The effect is !(p == np)
///////////////////////////////////////////////////////////////////////////////

#endif /* BIT_STL_CONCEPTS_NULLABLEPOINTER_HPP */
