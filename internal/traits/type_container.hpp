/**
 * \file type_container.hpp
 *
 * \brief This internal library provides type traits for determining containers
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_INTERNAL_TRAITS_TYPE_CONTAINER_HPP
#define BIT_INTERNAL_TRAITS_TYPE_CONTAINER_HPP

#if defined(__GNUC__) && (__GNUC__ >= 4)
#  pragma GCC system_header
#endif

#include <iterator>

namespace bit {

  //------------------------------------------------------------------------
  // Iterator Type Checking
  //------------------------------------------------------------------------

  namespace detail {

    template<typename T, typename = void>
    struct is_iterator : std::false_type{};

    template<typename T>
    struct is_iterator<T,
      void_t<
        typename std::iterator_traits<T>::value_type,
        typename std::iterator_traits<T>::difference_type,
        typename std::iterator_traits<T>::pointer,
        typename std::iterator_traits<T>::reference,
        typename std::iterator_traits<T>::iterator_category,
        decltype( *std::declval<T>() ),
        decltype( ++std::declval<T>() )
      >
    > : std::true_type{};

    template<typename T, bool = is_iterator<T>::value, typename = void>
    struct is_input_iterator : std::false_type{};

    template<typename T>
    struct is_input_iterator<
      T,
      true,
      void_t<
        decltype( std::declval<T>() != std::declval<T>() ),
        decltype( std::declval<T>() == std::declval<T>() ),
        decltype( std::declval<T>()++ ),
        decltype( *std::declval<T>()++ )
      >
    > : std::true_type{};

    template<typename T, bool = is_input_iterator<T>::value, typename = void>
    struct is_bidirectional_iterator : std::false_type{};

    template<typename T>
    struct is_bidirectional_iterator<
      T,
      true,
      void_t<
        decltype( --std::declval<T>() ),
        decltype( std::declval<T>()-- ),
        decltype( *std::declval<T>()-- )
      >
    > : std::true_type{};

    template<typename T, bool = is_bidirectional_iterator<T>::value, typename = void>
    struct is_random_access_iterator : std::false_type{};

    template<typename T>
    struct is_random_access_iterator<
      T,
      true,
      void_t<
        // it += n, it + n, it - n
        decltype( std::declval<T&>() += std::declval<typename std::iterator_traits<T>::difference_type>() ),
        decltype( std::declval<T>() + std::declval<typename std::iterator_traits<T>::difference_type>() ),
        decltype( std::declval<typename std::iterator_traits<T>::difference>() + std::declval<T>() ),
        // it -= n, it - n, b - a
        decltype( std::declval<T&>() -= std::declval<typename std::iterator_traits<T>::difference_type>() ),
        decltype( std::declval<T>() - std::declval<typename std::iterator_traits<T>::difference_type>() ),
        decltype( std::declval<T>() - std::declval<T>() ),
        // it[n]
        decltype( std::declval<T>()[ std::declval<typename std::iterator_traits<T>::difference_Type>()] ),
        // comparison
        decltype( static_cast<bool>(std::declval<T>() <  std::declval<T>()) ),
        decltype( static_cast<bool>(std::declval<T>() >  std::declval<T>()) ),
        decltype( static_cast<bool>(std::declval<T>() <= std::declval<T>()) ),
        decltype( static_cast<bool>(std::declval<T>() >= std::declval<T>()) )
      >
    > : std::true_type{};
  }

  /// \brief Type trait to determine if a given type is an Iterator
  ///
  /// The result is aliased as \c ::value
  template<typename T>
  using is_iterator = detail::is_iterator<T>;

  /// \brief Type trait to determine if a given type is an InputIterator
  ///
  /// The result is aliased as \c ::value
  template<typename T>
  using is_input_iterator = detail::is_input_iterator<T>;

  /// \brief Type trait to determine if a given type is a ForwardIterator
  ///
  /// The result is aliased as \c ::value
  template<typename T>
  using is_forward_iterator = detail::is_input_iterator<T>;

  /// \brief Type trait to determine if a given type is a BidirectionalIterator
  ///
  /// A type is considered an iterator if all \c iterator_traits are supplied
  ///
  /// The result is aliased as \c ::value
  template<typename T>
  using is_bidirectional_iterator = detail::is_bidirectional_iterator<T>;

  /// \brief Type trait to determine if a given type is a RandomAccessIterator
  ///
  /// A type is considered an iterator if all \c iterator_traits are supplied
  ///
  /// The result is aliased as \c ::value
  template<typename T>
  using is_random_access_iterator = detail::is_random_access_iterator<T>;

  //------------------------------------------------------------------------
  // Plural Iterator Types
  //------------------------------------------------------------------------

  /// \brief Type trait to determine if a series of \c Types are all Iterators
  ///
  /// \The result is stored in \c ::value
  template<typename...Types>
  struct are_iterators : conjunction<is_iterator<Types>...>{};

  /// \brief Type trait to determine if a series of \c Types are all InputIterators
  ///
  /// \The result is stored in \c ::value
  template<typename...Types>
  struct are_input_iterators : conjunction<is_input_iterator<Types>...>{};

  /// \brief Type trait to determine if a series of \c Types are all ForwardIterators
  ///
  /// \The result is stored in \c ::value
  template<typename...Types>
  struct are_forward_iterators : conjunction<is_forward_iterator<Types>...>{};

  /// \brief Type trait to determine if a series of \c Types are all BidirectionalIterators
  ///
  /// \The result is stored in \c ::value
  template<typename...Types>
  struct are_bidirectional_iterators : conjunction<is_bidirectional_iterator<Types>...>{};

  /// \brief Type trait to determine if a series of \c Types are all RandomAccessIterators
  ///
  /// \The result is stored in \c ::value
  template<typename...Types>
  struct are_random_access_iterators : conjunction<is_random_access_iterator<Types>...>{};

  //--------------------------------------------------------------------------
  // Has Iterators
  //--------------------------------------------------------------------------

  namespace detail {

    template<typename T, typename = void>
    struct has_iterators : std::false_type{};

    template<typename T>
    struct has_iterators<
      T,
      void_t<
        decltype( std::declval<T>().begin() == std::declval<T>().end() ),
        decltype( std::declval<T>().begin() != std::declval<T>().end() ),
        std::enable_if_t<is_iterator<decltype( std::declval<T>().begin() )>::value>
      >
    > : std::true_type{};

    //------------------------------------------------------------------------

    template<typename T, typename = void>
    struct has_reverse_iterators : std::false_type{};

    template<typename T>
    struct has_reverse_iterators<
      T,
      void_t<
        decltype( std::declval<T>().rbegin() == std::declval<T>().rend() ),
        decltype( std::declval<T>().rbegin() != std::declval<T>().rend() )
      >
    > : std::true_type{};

  } // namespace detail

  /// \brief Type trait to determine whether \p T has iterators
  ///
  /// The result is aliased as \c ::value
  template<typename T>
  struct has_iterators
    : detail::has_iterators<std::remove_const_t<std::decay_t<T>>>{};

  /// \brief Type trait to determine whether \p T has constant iterators
  ///
  /// The result is aliased as \c ::value
  template<typename T>
  struct has_const_iterators
    : detail::has_iterators<std::add_const_t<std::decay_t<T>>>{};

  /// \brief Type trait to determine whether \p T has reverse iterators
  ///
  /// The result is aliased as \c ::value
  template<typename T>
  struct has_reverse_iterators
    : detail::has_reverse_iterators<std::remove_const_t<std::decay_t<T>>>{};

  /// \brief Type trait to determine whether \p T has const reverse iterators
  ///
  /// The result is aliased as \c ::value
  template<typename T>
  struct has_const_reverse_iterators
    : detail::has_reverse_iterators<std::add_const_t<std::decay_t<T>>>{};

  //------------------------------------------------------------------------

  namespace detail {

    /// \brief Implementation of Type trait \c is_iterator_convertible by accepting
    ///        a boolean to determine whether the type is a given iterator
    ///
    /// The result is aliased as \c ::value
    template<typename InputIterator, typename T, bool>
    struct is_iterator_convertible : std::false_type{};

    template<typename InputIterator, typename T>
    struct is_iterator_convertible<InputIterator,T,true>
      : std::is_convertible<typename std::iterator_traits<InputIterator>::value_type,T>{};

  } // namespace detail

  /// \brief Type trait to determine whether the given \p InputIterator
  ///        is convertible to \p T.
  ///
  /// The result is aliased as \c ::value
  template<typename InputIterator, typename T>
  using is_iterator_convertible
    = detail::is_iterator_convertible<InputIterator,T,is_iterator<InputIterator>::value>;

  //------------------------------------------------------------------------

  /// \brief Type trait to determine whether the given \p InputIterators
  ///        are convertible to \p T.
  ///
  /// The result is aliased as \c ::value
  template<typename T, typename...InputIterators>
  using are_iterators_convertible = type_and<is_iterator_convertible<InputIterators,T>::value...>;

  //------------------------------------------------------------------------

  /// \brief Type trait to determine if a given \c type has a member type
  ///        \c ::key_type
  ///
  /// The result is aliased as ::value
  template<typename T, typename = void>
  struct has_key_type : std::false_type{};

  template<typename T>
  struct has_key_type<T,void_t<typename T::key_type>> : std::true_type{};

  //------------------------------------------------------------------------

  /// \brief Type trait to determine if a given \c type has a member type
  ///        \c ::mapped_type
  ///
  /// The result is aliased as ::value
  template<typename T, typename = void>
  struct has_mapped_type : std::false_type{};

  template<typename T>
  struct has_mapped_type<T,void_t<typename T::mapped_type>> : std::true_type{};

  //------------------------------------------------------------------------

  /// \brief Type trait to determine if a given \c type has a member type
  ///        \c ::value_type
  ///
  /// The result is aliased as ::value
  template<typename T, typename = void>
  struct has_value_type : std::false_type{};

  template<typename T>
  struct has_value_type<T,void_t<typename T::value_type>> : std::true_type{};

  //------------------------------------------------------------------------

  namespace detail {

    /// \brief Implementation of type trait \c get_value_member
    template<typename T, typename Default, bool = has_value_type<T>::value>
    struct get_value_type : identity<typename T::value_type>{};

    template<typename T, typename Default>
    struct get_value_type<T,Default, false> : identity<Default>{};

  }

  /// \brief Type trait to retrieve the data member \c ::value_type, if it
  ///        exists. Otherwise the type defaults to \p Default
  ///
  /// The result is aliased as \c ::type
  template<typename T,typename Default = void>
  using get_value_type = detail::get_value_type<T,Default>;


  /// \brief Helper template alias for retrieving the \c ::type of
  ///        \c get_value_type
  template<typename T, typename Default = void>
  using get_value_type_t = typename get_value_type<T, Default>::type;


  //------------------------------------------------------------------------

  namespace detail {

    /// \brief Implementation of type trait \c get_key_type
    template<typename T, typename Default, bool = has_key_type<T>::value>
    struct get_key_type : identity<typename T::key_type>{};

    template<typename T, typename Default>
    struct get_key_type<T,Default, false> : identity<Default>{};

  }

  /// \brief Type trait to retrieve the data member \c ::key_type, if it
  ///        exists. Otherwise the type defaults to \p Default
  ///
  /// The result is aliased as \c ::type
  template<typename T, typename Default = void>
  using get_key_type = detail::get_key_type<T,Default>;


  /// \brief Helper template alias for retrieving the \c ::type of
  ///        \c get_key_type
  template<typename T, typename Default = void>
  using get_key_type_t = typename get_key_type<T, Default>::type;

  //------------------------------------------------------------------------

  namespace detail {

    /// \brief Implementation of type trait \c get_mapped_type
    template<typename T, typename Default, bool = has_mapped_type<T>::value>
    struct get_mapped_type : identity<typename T::mapped_type>{};

    template<typename T, typename Default>
    struct get_mapped_type<T,Default, false> : identity<Default>{};

  }

  /// \brief Type trait to retrieve the data member \c ::mapped_type, if it
  ///        exists. Otherwise the type defaults to \p Default
  ///
  /// The result is aliased as \c ::type
  template<typename T,typename Default = void, bool = has_key_type<T>::value>
  using get_mapped_type = detail::get_mapped_type<T,Default>;

  /// \brief Helper template alias for retrieving the \c ::type of
  ///        \c get_mapped_type
  template<typename T, typename Default = void>
  using get_mapped_type_t = typename get_mapped_type<T,Default>::type;

  //--------------------------------------------------------------------------

  /// \brief Type trait to determine if \c T is a container type
  ///
  /// A basic container type has iterators (either const or non-const) and
  /// a member type \c value_type
  ///
  /// The result is aliased as \c ::value
  template<typename T>
  using is_container = conjunction<disjunction<has_iterators<T>,
                                               has_const_iterators<T>>,
                                               has_value_type<T>>;

  /// \brief Type trait to determine if \c Types are all container types
  ///
  /// The result is aliased as \c ::value
  template<typename...Types>
  using are_containers = conjunction<is_container<Types>...>;

  //------------------------------------------------------------------------

  /// \brief Type trait to determine if \c T is an associative container type
  ///
  /// An associative container is a basic container that stores all results as
  /// (key->value) pairs. These expose, in addition to the basic container elements,
  /// a \c ::mapped_type and a \c key_type
  ///
  /// The result is aliased as \c ::value
  template<typename T>
  using is_associative_container = conjunction<is_container<T>,
                                               has_key_type<T>,
                                               has_mapped_type<T>>;

  /// \brief type-trait to determine if \c Args are all associative container types
  ///
  /// The result is aliased as \c ::value
  template<typename...Types>
  using are_associative_containers
    = conjunction<is_associative_container<Types>...>;

  //--------------------------------------------------------------------------

  namespace detail {

    template<typename T, typename = void>
    struct is_contiguous_container : std::false_type{};

    template<typename T>
    struct is_contiguous_container<
      T,
      void_t<decltype(std::declval<T>().size()), decltype(std::declval<T>().data())>
    > : std::true_type{};

  } // namespace detail

  /// \brief Determines whether \p T is a contiguous container
  ///
  /// The result is aliased as \c ::value
  template<typename T>
  using is_contiguous_container = detail::is_contiguous_container<T>;

  template<typename T>
  constexpr bool is_contiguous_container_v = is_contiguous_container<T>::value;

} // namespace bit

#endif /* BIT_INTERNAL_TRAITS_TYPE_CONTAINER_HPP */
