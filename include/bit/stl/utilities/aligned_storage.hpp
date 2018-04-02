/*****************************************************************************
 * \file
 * \brief This header defines a utility type for aligned storage
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
#ifndef BIT_STL_UTILITIES_ALIGNED_STORAGE_HPP
#define BIT_STL_UTILITIES_ALIGNED_STORAGE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "../traits/composition/conjunction.hpp"
#include "../traits/composition/size_constant.hpp"

#include <cstddef> // std::size_t, std::max_align_t

namespace bit {
  namespace stl {
    namespace detail {
      template<std::size_t Max, std::size_t...Sizes>
      struct aligned_storage_max;

      template<std::size_t Max, std::size_t Size0, std::size_t...Sizes>
      struct aligned_storage_max<Max,Size0,Sizes...>
        : aligned_storage_max<(Max > Size0 ? Max : Size0),Sizes...>{};

      template<std::size_t Max>
      struct aligned_storage_max<Max> : size_constant<Max>{};
    } // namespace detail

    constexpr auto max_align = alignof(std::max_align_t);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Provides the nested type type, which is a PODType suitable for
    ///        use as uninitialized storage for any object whose size is at
    ///        most Len and whose alignment requirement is a divisor of Align.
    ///
    /// The default value of Align is the most stringent (the largest)
    /// alignment requirement for any object whose size is at most Len.
    /// If the default value is not used, Align must be the value of
    ///  alignof(T) for some type T, or the behavior is undefined.
    ///
    /// The behavior is undefined if Len == 0.
    ///
    /// \tparam Len the length of the storage
    /// \tparam Align the alignment of the storage
    //////////////////////////////////////////////////////////////////////////
    template<std::size_t Len, std::size_t Align = max_align>
    struct aligned_storage
    {
      union type
      {
        char data[Len];
        alignas(Align) struct dummy{} dummy;
      };
    };

    /// \brief Type-alias for extracting aligned_storage::type
    template<std::size_t Len, std::size_t Align = max_align>
    using aligned_storage_t = typename aligned_storage<Len,Align>::type;

    /// \brief Type-alias for creating aligned_storage large enough and suitably
    ///        aligned for all specified Types...
    ///
    /// \tparam Types the types to ensure alignment and size of
    template<typename...Types>
    using aligned_storage_for = aligned_storage_t<detail::aligned_storage_max<sizeof(Types)...>::value,
                                                  detail::aligned_storage_max<alignof(Types)...>::value>;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_UTILITIES_ALIGNED_STORAGE_HPP */
