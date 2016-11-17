/**
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */

/*
 * Symbols Defined:
 *
 * BIT_STRINGIZE(a)      : Converts symbol 'a' to string at compile time.
 * BIT_JOIN(lhs,rhs)     : concatenates lhs to rhs at compile time, producing symbol lhsrhs.
 * BIT_TO_BOOL(x)        : Converts integer x to a boolean value
 * BIT_BOOL_NOT(x)       : Inverts the boolean value (1 to 0 or 0 to 1)
 * BIT_BOOL_OR(x,y)      : Performs bitwise or, returning the result of x||y
 * BIT_BOOL_AND(x,y)     : Performs bitwise and, returning the result of x&&y
 * BIT_BOOL_XOR(x,y)     : Performs bitwise xor, returning the result of x^y
 * BIT_BOOL_NAND(x,y)    : Performs bitwise nand, returning the result of !(x&&y)
 * BIT_BOOL_NOR(x,y)     : Performs bitwise nor, returning the result of !(x||y)
 * BIT_BOOL_XNOR(x,y)    : Performs bitwise xnor, returning the result of !(x^y)
 * BIT_IF(cond,x)        : If condition is true, perform x
 * BIT_IF_ELSE(cond,x,y) : If condition is true, perform x, otherwise y
 * BIT_COMMA_IF(cond)    : If condition, create comma
 * BIT_LIST(c,p)         : Creates an increasing list of c elements, prefixed by 'p'
 * BIT_REVERSE_LIST(c,p) : Creates a decreasing list of c elements, prefixed by 'p'
 * BIT_SELECT(n,...)     : Selects the n'th argument of the supplied variadic list
 * BIT_VA_ARGS(...)      : Portable way of passing variadic arguments without a trailing comma on empty input
 * BIT_EMPTY             : Empty symbol for passing to macro parameters to avoid warnings
 */
#ifndef BIT_INTERNAL_CONFIG_MACROS_HPP
#define BIT_INTERNAL_CONFIG_MACROS_HPP

//! \def BIT_STRINGIZE(a)
//!
//! \brief Converts arguments to a string representation at compile time.
//!
//! This uses 2 levels of indirection to guarantee macro expansion
#define BIT_STRINGIZE(a)           BIT_STRINGIZE_H1(a)
#define BIT_STRINGIZE_H1(a)        BIT_STRINGIZE_H2(a)
#define BIT_STRINGIZE_H2(a)        # a

//! \def BIT_JOIN(lhs,rhs)
//!
//! \brief Concatenates \p lhs to \p rhs at compile time, producing
//!        symbol \a lhsrhs.
//!
//! Concatenates two macro arguments into one. This uses 2 levels of
//! indirection to guarantee macro expansion.
#define BIT_JOIN(lhs,rhs)          BIT_JOIN_H1(lhs, rhs)
#define BIT_JOIN_H1(lhs,rhs)       BIT_JOIN_H2(lhs, rhs)
#define BIT_JOIN_H2(lhs,rhs)       lhs ## rhs

//----------------------------------------------------------------------------

//! \def BIT_UNIQUE_NAME(name)
//!
//! \brief Constructs an unique name by concatenating \p name with
//!        either a unique counter or the line number (if the counter is
//!        not otherwise available)
#ifdef __COUNTER__
# define BIT_UNIQUE_NAME(name) BIT_JOIN(name,BIT_STRINGIZE(__COUNTER__))
#else
# define BIT_UNIQUE_NAME(name) BIT_JOIN(name,BIT_STRINGIZE(__LINE__))
#endif

//! \def BIT_EMPTY
//!
//! \brief ANSI-C (C90 standard) does not permit a macro to be invoked with
//!        an empty argument, so this exists to satisfy that requirement.
#define BIT_EMPTY /* empty list */

//! \def __WFILE__
//!
//! \brief Filename of the current translation unit in wide-format
#define BIT_WIDEN(x)         BIT_JOIN(L,x)
#ifndef __WFILE__
# define __WFILE__           BIT_WIDEN(__FILE__)
#endif

//! \def __UTF16FILE__
//! \brief Filename of the current translation unit in UTF16-format
//!
//! \def __UTF32FILE__
//! \brief Filename of the current translation unit in UTF32-format
#if __cplusplus >= 201103L
# define BIT_ENCODE_UTF16(x) BIT_JOIN(u,x)
# ifndef __UTF16FILE__
#   define __UTF16FILE__      BIT_ENCODE_UTF16(__FILE__)
# endif
# ifndef __UTF32FILE__
#   define BIT_ENCODE_UTF32(x) BIT_JOIN(U,x)
#   define __UTF32FILE__        BIT_ENCODE_UTF16(__FILE__)
# endif
#endif

// todo: Update when C++17's __cplusplus identifier is standardized
#if __cplusplus >= 201700L
# define BIT_ENCODE_UTF8(x) BIT_JOIN(u8,x)
# ifndef __UTF8FILE__
#   define __UTF8FILE__ BIT_ENCODE_UTF8(__FILE__)
# endif
#endif

//----------------------------------------------------------------------------
// Boolean Operations
//----------------------------------------------------------------------------

//! \def BIT_TO_BOOL(x)
//!
//! \brief Converts integer x to a boolean value at compile time
//!
//! Converts integer values to bool (0 or 1) for macro expansion.
//! This is necessary to do macro conditionals
#define BIT_TO_BOOL(x) BIT_JOIN(BIT_TO_BOOL_, x)
#define BIT_TO_BOOL_true  1 // true and false shouldn't be used in macros
#define BIT_TO_BOOL_false 0 // but are added here anyway just in case
#define BIT_TO_BOOL_0     0
#define BIT_TO_BOOL_1     1
#define BIT_TO_BOOL_2     1
#define BIT_TO_BOOL_3     1
#define BIT_TO_BOOL_4     1
#define BIT_TO_BOOL_5     1
#define BIT_TO_BOOL_6     1
#define BIT_TO_BOOL_7     1
#define BIT_TO_BOOL_8     1
#define BIT_TO_BOOL_9     1
#define BIT_TO_BOOL_10    1

//! \def BIT_BOOL_NOT(x)
//!
//! \brief Inverts the boolean value (1 to 0 or 0 to 1)
#define BIT_BOOL_NOT(x)    BIT_JOIN(BIT_BOOL_NOT_, BIT_TO_BOOL(x))
#define BIT_BOOL_NOT_0   1
#define BIT_BOOL_NOT_1   0

//! \def BIT_BOOL_OR(x,y)
//!
//! \brief Performs bitwise or, returning the result of x||y
#define BIT_BOOL_OR(x,y)   BIT_JOIN(BIT_JOIN(BIT_BOOL_OR_, BIT_TO_BOOL(x)),BIT_TO_BOOL(y))
#define BIT_BOOL_OR_00   0
#define BIT_BOOL_OR_10   1
#define BIT_BOOL_OR_11   1
#define BIT_BOOL_OR_01   1

//! \def BIT_BOOL_AND(x,y)
//!
//! \brief Performs bitwise and, returning the result of x&&y
#define BIT_BOOL_AND(x,y)  BIT_JOIN(BIT_JOIN(BIT_BOOL_AND_, BIT_TO_BOOL(x)),BIT_TO_BOOL(y))
#define BIT_BOOL_AND_00  0
#define BIT_BOOL_AND_10  0
#define BIT_BOOL_AND_11  1
#define BIT_BOOL_AND_01  0

//! \def BIT_BOOL_XOR(x,y)
//!
//! \brief Performs bitwise xor, returning the result of x^y
#define BIT_BOOL_XOR(x,y)  BIT_JOIN(BIT_JOIN(BIT_BOOL_XOR_, BIT_TO_BOOL(x)),BIT_TO_BOOL(y))
#define BIT_BOOL_XOR_00  0
#define BIT_BOOL_XOR_10  1
#define BIT_BOOL_XOR_01  1
#define BIT_BOOL_XOR_11  0

//! \def BIT_BOOL_NAND(x,y)
//!
//! \brief Performs bitwise nand, returning the result of !(x&&y)
#define BIT_BOOL_NAND(x,y) BIT_BOOL_NOT(BIT_BOOL_AND(x,y))

//! \def BIT_BOOL_NOR(x,y)
//!
//! \brief Performs bitwise nor, returning the result of !(x||y)
#define BIT_BOOL_NOR(x,y)  BIT_BOOL_NOT(BIT_BOOL_OR(x,y))

//! \def BIT_BOOL_XNOR(x,y)
//!
//! \brief Performs bitwise xnor, returning the result of !(x^y)
#define BIT_BOOL_XNOR(x,y) BIT_BOOL_NOT(BIT_BOOL_XOR(x,y))

//----------------------------------------------------------------------------
// Conditionals
//----------------------------------------------------------------------------

//! \def BIT_IF(cond,x)
//!
//! \brief If condition is true, perform x
#define BIT_IF(cond,x) BIT_JOIN(BIT_IF_, BIT_TO_BOOL(cond))(x)
#define BIT_IF_0(x)
#define BIT_IF_1(x)    x

//! \def BIT_IF_ELSE(cond,x,y)
//!
//! \brief If condition is true, perform x, otherwise y
#define BIT_IF_ELSE(cond,x,y) BIT_JOIN(BIT_IF_ELSE_, BIT_TO_BOOL(cond))(x,y)
#define BIT_IF_ELSE_0(x,y) y
#define BIT_IF_ELSE_1(x,y) x

//! \def BIT_COMMA_IF(cond)
//!
//! \brief If condition, create comma
#define BIT_COMMA_IF(cond) BIT_JOIN(BIT_COMMA_IF_, BIT_TO_BOOL(cond))
#define BIT_COMMA_IF_0
#define BIT_COMMA_IF_1 ,

//----------------------------------------------------------------------------
// List Generation
//----------------------------------------------------------------------------

//! \def BIT_LIST(count,prefix)
//!
//! \brief Creates an increasing list of \p count elements, prefixed by \p prefix
//!
//! Example Use:
//! \code
//!    BIT_LIST(5,var)   => var1, var2, var3, var4, var5
//!    BIT_LIST(3,int x) => int x1, int x2, int x3
//!    BIT_LIST(3)       => 1, 2, 3
//! \endcode
#define BIT_LIST(count,prefix)         BIT_JOIN(BIT_LIST_,count)(prefix)
#define BIT_LIST_0(x)
#define BIT_LIST_1(x)  x##1
#define BIT_LIST_2(x)  BIT_LIST_1(x), x##2
#define BIT_LIST_3(x)  BIT_LIST_2(x), x##3
#define BIT_LIST_4(x)  BIT_LIST_3(x), x##4
#define BIT_LIST_5(x)  BIT_LIST_4(x), x##5
#define BIT_LIST_6(x)  BIT_LIST_5(x), x##6
#define BIT_LIST_7(x)  BIT_LIST_6(x), x##7
#define BIT_LIST_8(x)  BIT_LIST_7(x), x##8
#define BIT_LIST_9(x)  BIT_LIST_8(x), x##9
#define BIT_LIST_10(x) BIT_LIST_10(x), x##10

//! \def BIT_REVERSE_LIST(count,prefix)
//!
//! \brief Creates an decreasing list of \p count elements, prefixed by \p prefix
//!
//! Example Use:
//! \code
//!    BIT_REVERSE_LIST(5,var)   => var5, var4, var3, var2, var1
//!    BIT_REVERSE_LIST(3,int x) => int x3, int x2, int x1
//!    BIT_REVERSE_LIST(3,)      => 3, 2, 1
//! \endcode
#define BIT_REVERSE_LIST(count,prefix) BIT_JOIN(BIT_REVERSE_LIST_,count)(prefix)
#define BIT_REVERSE_LIST_0(x)
#define BIT_REVERSE_LIST_1(x)  x##1
#define BIT_REVERSE_LIST_2(x)  x##2, BIT_REVERSE_LIST_1(x)
#define BIT_REVERSE_LIST_3(x)  x##3, BIT_REVERSE_LIST_2(x)
#define BIT_REVERSE_LIST_4(x)  x##4, BIT_REVERSE_LIST_3(x)
#define BIT_REVERSE_LIST_5(x)  x##5, BIT_REVERSE_LIST_4(x)
#define BIT_REVERSE_LIST_6(x)  x##6, BIT_REVERSE_LIST_5(x)
#define BIT_REVERSE_LIST_7(x)  x##7, BIT_REVERSE_LIST_6(x)
#define BIT_REVERSE_LIST_8(x)  x##8, BIT_REVERSE_LIST_7(x)
#define BIT_REVERSE_LIST_9(x)  x##9, BIT_REVERSE_LIST_8(x)
#define BIT_REVERSE_LIST_10(x) x##10, BIT_REVERSE_LIST_9(x)

//----------------------------------------------------------------------------

///! \def BIT_SELECT(n,...)
///
///! \brief Selects the n'th argument of the supplied variadic list
#define BIT_SELECT_1(a1, ...) a1
#define BIT_SELECT_2(a1, a2, ...) a2
#define BIT_SELECT_3(a1, a2, a3, ...) a3
#define BIT_SELECT_4(a1, a2, a3, a4, ...) a4
#define BIT_SELECT_5(a1, a2, a3, a4, a5, ...) a5
#define BIT_SELECT_6(a1, a2, a3, a4, a5, a6, ...) a6
#define BIT_SELECT_7(a1, a2, a3, a4, a5, a6, a7, ...) a7
#define BIT_SELECT_8(a1, a2, a3, a4, a5, a6, a7, a8, ...) a8
#define BIT_SELECT_9(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) a9
#define BIT_SELECT_10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) a10

#define BIT_SELECT(n,...) BIT_JOIN(BIT_SELECT_,n)(__VA_ARGS__, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) // random elements added to prevent compiler warnings

//----------------------------------------------------------------------------
// ARGUMENT RANGE SELECTION
//   Selects a range of arguments from a specified argument list
//----------------------------------------------------------------------------

//! \def BIT_RANGE(low,high,...)
//!
//! \brief Selects the elements in the variadic macro between [low,high]
//!
//! Example Use: \code BIT_RANGE(2,3,a,b,c,d,e,f,g) => b,c \endcode
#define BIT_RANGE(low,high,...) BIT_JOIN(BIT_JOIN(BIT_JOIN(BIT_RANGE_,low),_TO_),high)(__VA_ARGS__)

#define BIT_RANGE_1_TO_2(a1, a2, ...) a1, a2
#define BIT_RANGE_1_TO_3(a1, a2, a3, ...) a1, a2, a3
#define BIT_RANGE_1_TO_4(a1, a2, a3, a4, ...) a1, a2, a3, a4
#define BIT_RANGE_1_TO_5(a1, a2, a3, a4, a5, ...) a1, a2, a3, a4, a5
#define BIT_RANGE_1_TO_6(a1, a2, a3, a4, a5, a6, ...) a1, a2, a3, a4, a5, a6
#define BIT_RANGE_1_TO_7(a1, a2, a3, a4, a5, a6, a7, ...) a1, a2, a3, a4, a5, a6, a7
#define BIT_RANGE_1_TO_8(a1, a2, a3, a4, a5, a6, a7, a8, ...) a1, a2, a3, a4, a5, a6, a7, a8
#define BIT_RANGE_1_TO_9(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) a1, a2, a3, a4, a5, a6, a7, a8, a9
#define BIT_RANGE_1_TO_10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) a1, a2, a3, a4, a5, a6, a7, a8, a9, a10

#define BIT_RANGE_2_TO_3(a1, a2, a3, ...) a2, a3
#define BIT_RANGE_2_TO_4(a1, a2, a3, a4, ...) a2, a3, a4
#define BIT_RANGE_2_TO_5(a1, a2, a3, a4, a5, ...) a2, a3, a4, a5
#define BIT_RANGE_2_TO_6(a1, a2, a3, a4, a5, a6, ...) a2, a3, a4, a5, a6
#define BIT_RANGE_2_TO_7(a1, a2, a3, a4, a5, a6, a7, ...) a2, a3, a4, a5, a6, a7
#define BIT_RANGE_2_TO_8(a1, a2, a3, a4, a5, a6, a7, a8, ...) a2, a3, a4, a5, a6, a7, a8
#define BIT_RANGE_2_TO_9(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) a2, a3, a4, a5, a6, a7, a8, a9
#define BIT_RANGE_2_TO_10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) a2, a3, a4, a5, a6, a7, a8, a9, a10

#define BIT_RANGE_3_TO_4(a1, a2, a3, a4, ...) a3, a4
#define BIT_RANGE_3_TO_5(a1, a2, a3, a4, a5, ...) a3, a4, a5
#define BIT_RANGE_3_TO_6(a1, a2, a3, a4, a5, a6, ...) a3, a4, a5, a6
#define BIT_RANGE_3_TO_7(a1, a2, a3, a4, a5, a6, a7, ...) a3, a4, a5, a6, a7
#define BIT_RANGE_3_TO_8(a1, a2, a3, a4, a5, a6, a7, a8, ...) a3, a4, a5, a6, a7, a8
#define BIT_RANGE_3_TO_9(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) a3, a4, a5, a6, a7, a8, a9
#define BIT_RANGE_3_TO_10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) a3, a4, a5, a6, a7, a8, a9, a10

#define BIT_RANGE_4_TO_5(a1, a2, a3, a4, a5, ...) a4, a5
#define BIT_RANGE_4_TO_6(a1, a2, a3, a4, a5, a6, ...) a4, a5, a6
#define BIT_RANGE_4_TO_7(a1, a2, a3, a4, a5, a6, a7, ...) a4, a5, a6, a7
#define BIT_RANGE_4_TO_8(a1, a2, a3, a4, a5, a6, a7, a8, ...) a4, a5, a6, a7, a8
#define BIT_RANGE_4_TO_9(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) a4, a5, a6, a7, a8, a9
#define BIT_RANGE_4_TO_10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) a4, a5, a6, a7, a8, a9, a10

#define BIT_RANGE_5_TO_6(a1, a2, a3, a4, a5, a6, ...) a5, a6
#define BIT_RANGE_5_TO_7(a1, a2, a3, a4, a5, a6, a7, ...) a5, a6, a7
#define BIT_RANGE_5_TO_8(a1, a2, a3, a4, a5, a6, a7, a8, ...) a5, a6, a7, a8
#define BIT_RANGE_5_TO_9(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) a5, a6, a7, a8, a9
#define BIT_RANGE_5_TO_10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) a5, a6, a7, a8, a9, a10

#define BIT_RANGE_6_TO_7(a1, a2, a3, a4, a5, a6, a7, ...) a6, a7
#define BIT_RANGE_6_TO_8(a1, a2, a3, a4, a5, a6, a7, a8, ...) a6, a7, a8
#define BIT_RANGE_6_TO_9(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) a6, a7, a8, a9
#define BIT_RANGE_6_TO_10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) a6, a7, a8, a9, a10

#define BIT_RANGE_7_TO_8(a1, a2, a3, a4, a5, a6, a7, a8, ...) a7, a8
#define BIT_RANGE_7_TO_9(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) a7, a8, a9
#define BIT_RANGE_7_TO_10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) a7, a8, a9, a10

#define BIT_RANGE_8_TO_9(a1, a2, a3, a4, a5, a6, a7, a8, a9, ...) a8, a9
#define BIT_RANGE_8_TO_10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) a8, a9, a10

#define BIT_RANGE_9_TO_10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) a9, a10


//----------------------------------------------------------------------------
// VARIADIC MACROS
//----------------------------------------------------------------------------

// Counting variadic arguments
#if (_MSC_VER >= 1400)
# define BIT_NUM_ARGS_REVERSE_SEQUENCE 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
# define BIT_COUNT_VA_ARGS_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
# define BIT_LEFT_PARENTHESIS    (
# define BIT_RIGHT_PARENTHESIS   )
# define BIT_COUNT_VA_ARGS(...)    BIT_COUNT_VA_ARGS_HELPER BIT_LEFT_PARENTHESIS __VA_ARGS__, BIT_NUM_ARGS_REVERSE_SEQUENCE BIT_RIGHT_PARENTHESIS
#else
# define BIT_COUNT_VA_ARGS_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...)    N
# define BIT_COUNT_VA_ARGS(...)    BIT_COUNT_VA_ARGS_HELPER(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#endif

// BIT_PASS_VA_ARGS passes __VA_ARGS__ as multiple parameters to another macro
#if (_MSC_VER >= 1400)
# define BIT_PASS_VA_ARGS(op, ...) op BIT_LEFT_PARENTHESIS __VA_ARGS__ BIT_RIGHT_PARENTHESIS
#else
# define BIT_PASS_VA_ARGS(op, ...) op(__VA_ARGS__)
#endif

// Variadic macro expansion
#define BIT_EXPAND_VA_ARGS_0(op)
#define BIT_EXPAND_VA_ARGS_1(op, a1) \
  op(a1)
#define BIT_EXPAND_VA_ARGS_2(op, a1, a2) \
  op(a1) op(a2)
#define BIT_EXPAND_VA_ARGS_3(op, a1, a2, a3) \
  op(a1) op(a2) op(a3)
#define BIT_EXPAND_VA_ARGS_4(op, a1, a2, a3, a4) \
  op(a1) op(a2) op(a3) op(a4)
#define BIT_EXPAND_VA_ARGS_5(op, a1, a2, a3, a4, a5) \
  op(a1) op(a2) op(a3) op(a4) op(a5)
#define BIT_EXPAND_VA_ARGS_6(op, a1, a2, a3, a4, a5, a6) \
  op(a1) op(a2) op(a3) op(a4) op(a5) op(a6)
#define BIT_EXPAND_VA_ARGS_7(op, a1, a2, a3, a4, a5, a6, a7) \
  op(a1) op(a2) op(a3) op(a4) op(a5) op(a6) op(a7)
#define BIT_EXPAND_VA_ARGS_8(op, a1, a2, a3, a4, a5, a6, a7, a8) \
  op(a1) op(a2) op(a3) op(a4) op(a5) op(a6) op(a7) op(a8)
#define BIT_EXPAND_VA_ARGS_9(op, a1, a2, a3, a4, a5, a6, a7, a8, a9) \
  op(a1) op(a2) op(a3) op(a4) op(a5) op(a6) op(a7) op(a8) op(a9)
#define BIT_EXPAND_VA_ARGS_10(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) \
  op(a1) op(a2) op(a3) op(a4) op(a5) op(a6) op(a7) op(a8) op(a9) op(a10)

#define BIT_EXPAND_ARGS(n,op,...) BIT_JOIN(BIT_EXPAND_VA_ARGS_,n)(op,__VA_ARGS__)

// Variadic macro dispatching the arguments to the correct macro.
// The number of arguments is found by using BIT_VA_NUM_ARGS(__VA_ARGS__)
#define BIT_EXPAND_VA_ARGS(op, ...) BIT_JOIN(BIT_EXPAND_VA_ARGS_, BIT_COUNT_VA_ARGS(__VA_ARGS__))(op, __VA_ARGS__)

//----------------------------------------------------------------------------
// VA ARGUMENT PASSING
//   This passes variadic arguments without resulting in a trailing comma
//   for an empty argument
//----------------------------------------------------------------------------

// Get the first argument of a VA argument list
#define BIT_VA_FIRST_HELPER(first,...) first
#define BIT_VA_FIRST(...)              BIT_VA_FIRST_HELPER(__VA_ARGS__,throwaway)

// Get the rest of the arguments of a VA argument list
#define BIT_VA_REST_HELPER(qty, ...)  BIT_VA_REST_HELPER2(qty, __VA_ARGS__)
#define BIT_VA_REST_HELPER2(qty, ...) BIT_VA_REST_HELPER_##qty(__VA_ARGS__)
#define BIT_VA_REST_HELPER_FIRST(first)
#define BIT_VA_REST_HELPER_REST(first, ...) __VA_ARGS__
#define BIT_VA_REST(...) BIT_VA_REST_HELPER(BIT_VA_REST_NUM(__VA_ARGS__), __VA_ARGS__)

#define BIT_VA_REST_NUM(...) \
    BIT_SELECT_10(__VA_ARGS__, REST, REST, REST, REST,\
    REST, REST, REST, REST, FIRST, throwaway)

#define BIT_VA_ARGS(...) BIT_VA_FIRST(__VA_ARGS__) BIT_VA_REST(__VA_ARGS__)

//----------------------------------------------------------------------------
// Nested Namespace Generation
//----------------------------------------------------------------------------

//! \def BIT_NAMESPACE_BEGIN(...)
//!
//! \brief Generates a series of namespace opening statements.
//!
//! This serves a utility macro in order to easily create nested namespaces
//! without requiring a lot of indentation.
//!
//! \note A call to BIT_NAMESPACE_BEGIN must have a matching call to
//!       BIT_NAMESPACE_END somewhere.
#define BIT_NAMESPACE_BEGIN_1(n1) namespace n1{
#define BIT_NAMESPACE_BEGIN_2(n1,n2) namespace n1{ namespace n2{
#define BIT_NAMESPACE_BEGIN_3(n1,n2,n3) namespace n1{ namespace n2{ namespace n3{
#define BIT_NAMESPACE_BEGIN_4(n1,n2,n3,n4) namespace n1{ namespace n2{ namespace n3{ namespace n4{
#define BIT_NAMESPACE_BEGIN_5(n1,n2,n3,n4,n5) namespace n1{ namespace n2{ namespace n3{ namespace n4{ namespace n5{
#define BIT_NAMESPACE_BEGIN_6(n1,n2,n3,n4,n5,n6) namespace n1{ namespace n2{ namespace n3{ namespace n4{ namespace n5{ namespace n6{
#define BIT_NAMESPACE_BEGIN_7(n1,n2,n3,n4,n5,n6,n7) namespace n1{ namespace n2{ namespace n3{ namespace n4{ namespace n5{ namespace n6{ namespace n7{
#define BIT_NAMESPACE_BEGIN_8(n1,n2,n3,n4,n5,n6,n7,n8) namespace n1{ namespace n2{ namespace n3{ namespace n4{ namespace n5{ namespace n6{ namespace n7{ namespace n8{
#define BIT_NAMESPACE_BEGIN_9(n1,n2,n3,n4,n5,n6,n7,n8,n9) namespace n1{ namespace n2{ namespace n3{ namespace n4{ namespace n5{ namespace n6{ namespace n7{ namespace n8{ namespace n9{

#define BIT_NAMESPACE_BEGIN(...) BIT_JOIN(BIT_NAMESPACE_BEGIN_,BIT_COUNT_VA_ARGS(__VA_ARGS__))(__VA_ARGS__)

//! \def BIT_NAMESPACE_END(...)
//!
//! \brief Generates a series of namespace closing statements.
//!
//! This serves a utility macro in order to easily create nested namespaces
//! without requiring a lot of indentation.
#define BIT_NAMESPACE_END_1(n1) }
#define BIT_NAMESPACE_END_2(n1,n2) } }
#define BIT_NAMESPACE_END_3(n1,n2,n3) } } }
#define BIT_NAMESPACE_END_4(n1,n2,n3,n4) } } } }
#define BIT_NAMESPACE_END_5(n1,n2,n3,n4,n5) } } } } }
#define BIT_NAMESPACE_END_6(n1,n2,n3,n4,n5,n6) } } } } } }
#define BIT_NAMESPACE_END_7(n1,n2,n3,n4,n5,n6,n7) } } } } } } }
#define BIT_NAMESPACE_END_8(n1,n2,n3,n4,n5,n6,n7,n8) } } } } } } } }
#define BIT_NAMESPACE_END_9(n1,n2,n3,n4,n5,n6,n7,n8,n9) } } } } } } } }

#define BIT_NAMESPACE_END(...) BIT_JOIN(BIT_NAMESPACE_END_, BIT_COUNT_VA_ARGS(__VA_ARGS__))(__VA_ARGS__)

#endif /* BIT_INTERNAL_CONFIG_MACROS_HPP */
