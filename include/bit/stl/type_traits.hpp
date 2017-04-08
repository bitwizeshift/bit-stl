
/**
 * \file type_traits.hpp
 *
 * \brief This header defines a series of classes to obtain type information
 *        at compile-time.
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TYPE_TRAITS_HPP
#define BIT_STL_TYPE_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

// bit::stl libraries
#include "stddef.hpp"

// std:: libraries
#include <type_traits>

#include "detail/invoke.hpp"
#include "detail/type_traits/type_composite.hpp"
#include "detail/type_traits/type_function.hpp"
#include "detail/type_traits/type_container.hpp"
#include "detail/type_traits/type_transformations.hpp"
#include "detail/type_traits/type_relationships.hpp"

#endif /* BIT_STL_TYPE_TRAITS_HPP */
