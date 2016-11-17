/**
 * \file type_traits.hpp
 *
 * \brief This header defines a series of classes to obtain type information
 *        at compile-time.
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_TYPE_TRAITS_HPP
#define BIT_TYPE_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

// bit::stl libraries
#include "stddef.hpp"

// std:: libraries
#include <type_traits>

#include "internal/traits/type_composite.hpp"
#include "internal/traits/type_function.hpp"
#include "internal/traits/type_container.hpp"
#include "internal/traits/type_transformations.hpp"
#include "internal/traits/type_relationships.hpp"

#endif /* BIT_TYPE_TRAITS_HPP */
