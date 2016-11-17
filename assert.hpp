/**
 * \file assert.hpp
 *
 * \brief This header contains the definitions for both static and
 *        runtime assertions.
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_ASSERT_HPP
#define BIT_ASSERT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

// bit::core local libraries
#include "config.hpp"

// Runtime assertion (Only available when in debug)
#if defined(BIT_DEBUG)
#  include <iostream>

// Define an assert overload of type 'type' and display it to the user
#  define BIT_RUNTIME_ASSERT_DEFINE_VARIABLE(type)                      \
      inline RuntimeAssert& variable( const char* name, type value )       \
      {                                                                    \
        std::cerr << m_message << "   o Variable " << name << ": "         \
                  << value << " (" BIT_STRINGIZE(type) ")\n";           \
        return (*this);                                                    \
      }

// Define an assert overload of pointer-to-type 'type' and display it to the user
#  define BIT_RUNTIME_ASSERT_DEFINE_POINTER(type)                              \
      inline RuntimeAssert& variable( const char* name, type* value )             \
      {                                                                           \
        std::cerr << m_message << "   o Pointer " << name << ": "                 \
                  << ((void*) value) << " -> " << *value                          \
                  << " (" BIT_STRINGIZE(type) "*)\n";                          \
        return (*this);                                                           \
      }                                                                           \
      inline RuntimeAssert& variable( const char* name, const type* value )       \
      {                                                                           \
        std::cerr << m_message << "   o Pointer " << name << ": "                 \
                  << ((void*) value) << " -> " << *value                          \
                  << " (const " BIT_STRINGIZE(type) "*)\n";                    \
        return (*this);                                                           \
      }


namespace bit {

#ifdef BIT_COMPILER_EXCEPTIONS_ENABLED
  class assertion_failure final : public std::runtime_error
  {
  public:

    assertion_failure(const char* message, source_location source );

    source_location source() const noexcept;

  };
#endif

  namespace detail {

    //////////////////////////////////////////////////////////////////////////
    /// \class bit::detail::RuntimeAssert
    ///
    /// \brief Implementation of a runtime assertion that accepts variable
    ///        names and values to be displayed to the user.
    //////////////////////////////////////////////////////////////////////////
    class RuntimeAssert {

      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      /// Initializes a RuntimeAssert
      inline RuntimeAssert(const char* format)
        : m_message(format)
      {
        std::cerr << m_message << "\n";
      }

      /// Initializes a RuntimeAssert with a message
      inline RuntimeAssert(const char* format, const char* message)
        :  m_message(format)
      {
        std::cerr << m_message << " " << message << "\n";
      }

      //----------------------------------------------------------------------
      // Primitive Types
      //----------------------------------------------------------------------
    public:

      /// Prints a boolean variable type
      inline RuntimeAssert& variable( const char* name, bool value ){
        std::cerr << m_message << "   o Variable " << name << ": "
                  << (value ? "true" : "false") << " (bool)\n";
        return (*this);
      }

      BIT_RUNTIME_ASSERT_DEFINE_VARIABLE(float)
      BIT_RUNTIME_ASSERT_DEFINE_VARIABLE(double)
      BIT_RUNTIME_ASSERT_DEFINE_VARIABLE(long double)

      BIT_RUNTIME_ASSERT_DEFINE_VARIABLE(char)
      BIT_RUNTIME_ASSERT_DEFINE_VARIABLE(signed char)
      BIT_RUNTIME_ASSERT_DEFINE_VARIABLE(unsigned char)
      BIT_RUNTIME_ASSERT_DEFINE_VARIABLE(signed short)
      BIT_RUNTIME_ASSERT_DEFINE_VARIABLE(unsigned short)
      BIT_RUNTIME_ASSERT_DEFINE_VARIABLE(signed int)
      BIT_RUNTIME_ASSERT_DEFINE_VARIABLE(unsigned int)
      BIT_RUNTIME_ASSERT_DEFINE_VARIABLE(signed long)
      BIT_RUNTIME_ASSERT_DEFINE_VARIABLE(unsigned long)

      // Long Long (only when supported)
#      if defined(BIT_COMPILER_HAS_LONG_LONG)
        BIT_RUNTIME_ASSERT_DEFINE_VARIABLE(signed long long)
        BIT_RUNTIME_ASSERT_DEFINE_VARIABLE(unsigned long long)
#      endif

      //----------------------------------------------------------------------
      // Pointer Types
      //----------------------------------------------------------------------
    public:

      BIT_RUNTIME_ASSERT_DEFINE_POINTER(float)
      BIT_RUNTIME_ASSERT_DEFINE_POINTER(double)
      BIT_RUNTIME_ASSERT_DEFINE_POINTER(long double)

      BIT_RUNTIME_ASSERT_DEFINE_POINTER(char)
      BIT_RUNTIME_ASSERT_DEFINE_POINTER(signed char)
      BIT_RUNTIME_ASSERT_DEFINE_POINTER(unsigned char)
      BIT_RUNTIME_ASSERT_DEFINE_POINTER(signed short)
      BIT_RUNTIME_ASSERT_DEFINE_POINTER(unsigned short)
      BIT_RUNTIME_ASSERT_DEFINE_POINTER(signed int)
      BIT_RUNTIME_ASSERT_DEFINE_POINTER(unsigned int)
      BIT_RUNTIME_ASSERT_DEFINE_POINTER(signed long)
      BIT_RUNTIME_ASSERT_DEFINE_POINTER(unsigned long)

      // Long Long (only when supported)
      BIT_RUNTIME_ASSERT_DEFINE_POINTER(signed long long)
      BIT_RUNTIME_ASSERT_DEFINE_POINTER(unsigned long long)

      //----------------------------------------------------------------------
      // Generic Variable Types
      //----------------------------------------------------------------------
    public:

      /// Prints a void pointer. This overload will not dereference the pointer
      inline RuntimeAssert& variable( const char* name, const void* value )
      {
        std::cerr << m_message << "   o Variable " << name << ": "
                  << ((void*) value) << " (void*)\n";
        return (*this);
      }

      /// Prints a nullptr
      inline RuntimeAssert& variable( const char* name, const ::std::nullptr_t )
      {
        std::cerr << m_message << "   o Variable " << name
                  << ": nullptr (nullptr_t)\n";
        return (*this);
      }

      //-----------------------------------------------------------------------

      /// Triggers a compiler breakpoint, flushing std::err to the screen
      inline void breakpoint()
      {
        std::flush(std::cerr); // Make sure it prints before the end
        BIT_BREAKPOINT();
      }

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      const char* m_message; /// The message to show to the user
    };


  } // namespace detail
} // namespace bit

#  define BIT_ASSERT_IMPL_VAR(x)    .variable( BIT_STRINGIZE(x), x )
#  define BIT_ASSERT_IMPL_VARS(...) BIT_EXPAND_VA_ARGS(BIT_ASSERT_IMPL_VAR, __VA_ARGS__)

#  define BIT_ASSERT_IMPL_FIRST(...)
#  define BIT_ASSERT_IMPL_REST(throwaway,...)  BIT_ASSERT_IMPL_VARS(__VA_ARGS__)

#  define BIT_ASSERT_VARS(...) BIT_JOIN(BIT_ASSERT_IMPL_,BIT_VA_REST_NUM(__VA_ARGS__))(__VA_ARGS__)

//-----------------------------------------------------------------------------

# ifndef BIT_COMPILER_EXCEPTIONS_ENABLED

//! \def BIT_ASSERT(condition, message, ...)
//!
//! \brief A runtime assertion when \a condition fails, displaying \a message
//!        to the user.
//!
//! Optionally the name and values can be displayed if entered in the list of
//! comma separated variables
#   define BIT_ASSERT(condition, ...) \
      do{                                                                                           \
        if(!(condition)){                                                                           \
          ::bit::detail::RuntimeAssert(                                                          \
            __FILE__ "(" BIT_STRINGIZE(__LINE__) "): [Assert]",                                  \
            "Assertion \"" #condition "\" failed with message \"" BIT_VA_FIRST(__VA_ARGS__) "\"" \
            ) BIT_ASSERT_VARS( __VA_ARGS__ )                                                     \
            .breakpoint();                                                                          \
        }                                                                                           \
      } while(0)

# else

#   define BIT_ASSERT(conditiong, ...) \
      do{
        if(!(condition)){
          throw ::bit::assertion_failure("Assertion \"" #condition "\" failed with message \"" BIT_VA_FIRST(__VA_ARGS__) "\"")
        }
      }while(0)

# endif

#else
#  define BIT_WARNING( condition, ... )
#endif

//! \def BIT_ASSERT_NULL(var)
//!
//! \brief Asserts that \a var should be null
#define BIT_ASSERT_NULL(var) BIT_ASSERT((var==nullptr), BIT_STRINGIZE(var) " should be null!", var)

//! \def BIT_ASSERT_NOT_NULL(var)
//!
//! \brief Asserts that \a var should not be null
#define BIT_ASSERT_NOT_NULL(var) BIT_ASSERT((var!=nullptr),  BIT_STRINGIZE(var) " should not be null!", var)

//! \def BIT_SANITY_CHECK(a,b)
//!
//! Performs a sanity check on a condition. This is used as a way to
//! assert that the condition will never be both simultaneously true and false
//!
//! \note this is primarily used as a utility to check user-built class
//!       operations, such as a class's "operator ==", to ensure that
//!       operator == and operator != don't always return the same value
#if defined(BIT_DEBUG)
#  define BIT_SANITY_CHECK(a,b) BIT_ASSERT(                      \
    !((a)&&(b)),                                                \
    "Sanity check failed: "                                     \
    "Conditions " #a " and " #b " cannot both be true.", a, b )
#else
#  define BIT_SANITY_CHECK(a,b) BIT_NOOP()
#endif

#undef BIT_RUNTIME_ASSERT_DEFINE_VARIABLE
#undef BIT_RUNTIME_ASSERT_DEFINE_POINTER

#endif /* BIT_ASSERT_HPP */
