/**
 * \file final_act.hpp
 *
 * \brief TODO: Add description
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
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
