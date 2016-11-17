/**
 * \file suppress_warnings_header.hpp
 *
 * This header is used to disable and enabled specific
 * compiler warnings so that the system will not complain
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_SUPPRESS_WARNINGS_HEADER_HPP
#define BIT_SUPPRESS_WARNINGS_HEADER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

// If using clang
#if defined(__clang__)
#  pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunused-parameter"
# pragma clang diagnostic ignored "-Wunused-variable"
// If using gcc
#elif defined(__GNUC__)
#  if (__GNUC__ * 100 + __GNUC_MINOR__ >= 406)
#    pragma GCC diagnostic push
#    pragma GCC diagnostic "-Wunused-parameter"
#    pragma GCC diagnostic "-Wunused-variable"
#  endif
// If using MSVC
#elif defined(_MSC_VER)
#  pragma warning(push)
# pragma warning(disable: 4100) // unreferenced formal parameter
#endif

#endif /* BIT_SUPPRESS_WARNINGS_HEADER_HPP */
