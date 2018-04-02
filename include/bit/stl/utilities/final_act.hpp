/*****************************************************************************
 * \file
 * \brief This header contains the utility function and type, finally/final_act
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
#ifndef BIT_STL_UTILITIES_FINAL_ACT_HPP
#define BIT_STL_UTILITIES_FINAL_ACT_HPP

#include <utility> // std::forward

namespace bit {
  namespace stl {

    ///////////////////////////////////////////////////////////////////////////
    /// \brief This class leverages RAII to perform cleanup actions at the end
    ///        of a scope
    ///
    /// This is guaranteed to run the action, even if an exception is thrown
    ///////////////////////////////////////////////////////////////////////////
    template<typename Func>
    class final_act final
    {
      //-----------------------------------------------------------------------
      // Constructors
      //-----------------------------------------------------------------------
    public:
      /// \brief Constructs an action to perform on end-of-scope
      ///
      /// \param function The function to call at the end
      constexpr explicit final_act( Func&& function );

      /// \brief Move-constructs a final act to perform on end-of-scope
      ///
      /// \param other the other act to move
      constexpr final_act(final_act&& other);

      /// \brief Disallow copy-construction
      final_act(const final_act&) = delete;

      /// \brief Move-assigns a final act to perform an end-of-scope
      ///
      /// \param other the other act to move
      final_act& operator=(final_act&& other);

      /// \brief Disallow copy-assignment
      final_act& operator=(const final_act&) = delete;

      /// \brief Destroys the final act, invoking the action
      ~final_act();

      //-----------------------------------------------------------------------
      // API
      //-----------------------------------------------------------------------
    public:

      /// \brief Cancels the final act from occurring
      void cancel() noexcept;

      //-----------------------------------------------------------------------
      // Private Member Function
      //-----------------------------------------------------------------------
    private:

        Func m_action;      ///< The action to perform
        bool m_will_invoke; ///< Whether or not this will invoke
    };

    /// \brief Convenience function to generate a final_act
    ///
    /// \param function the function to perform on the final act
    template<typename Func>
    inline constexpr final_act<Func> finally( Func&& function ) noexcept;

  } // namespace stl
} // namespace bit

#include "detail/final_act.inl"

#endif /* BIT_STL_UTILITIES_FINAL_ACT_HPP */
