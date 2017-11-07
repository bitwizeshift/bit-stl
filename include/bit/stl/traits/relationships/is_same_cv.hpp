/**
 * \file is_same_cv.hpp
 *
 * \brief This header defines a type-trait for detecting if a type has the same
 *        cv qualifications
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_CV_HPP
#define BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_CV_HPP

#include "../composition/bool_constant.hpp"

#include <type_traits> // std::is_const std::is_volatile

namespace bit {
  namespace stl {

    /// \brief Type-trait to determine if \c T and \c U have the same cv-
    ///        qualification
    ///
    /// The result is aliased as \c ::value
    template<typename T, typename U>
    struct is_same_cv : bool_constant<
      (std::is_const<T>::value == std::is_const<U>::value) &&
      (std::is_volatile<T>::value == std::is_volatile<U>::value)
    >{};

    /// \brief Helper utility to extract is_same_cv::value
    template<typename T, typename U>
    constexpr bool is_same_cv_v = is_same_cv<T,U>::value;

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_TRAITS_RELATIONSHIPS_IS_SAME_CV_HPP */
