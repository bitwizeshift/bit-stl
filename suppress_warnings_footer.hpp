/**
 * \file suppress_warnings_footer.hpp
 *
 * This header disables the warning suppressions enabled with
 * 'suppress_warnings_header.hpp'
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_SUPPRESS_WARNINGS_FOOTER_HPP
#define BIT_SUPPRESS_WARNINGS_FOOTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#if defined(__clang__)
#  pragma clang diagnostic pop
#elif defined(__GNUC__)
#  if (__GNUC__ * 100 + __GNUC_MINOR__ >= 406)
#    pragma GCC diagnostic pop
#  endif
#elif defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif /* BIT_SUPPRESS_WARNINGS_FOOTER_HPP */
