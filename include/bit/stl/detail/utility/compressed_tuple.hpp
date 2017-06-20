/**
 * \file compressed_tuple.hpp
 *
 * \brief This header contains a utility for compressing tuples to leverage
 *        EBO
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_DETAIL_UTILITY_COMPRESSED_TUPLE_HPP
#define BIT_STL_DETAIL_UTILITY_COMPRESSED_TUPLE_HPP

#include <type_traits>

namespace bit {
  namespace stl {
    namespace detail {
      template<typename...Types>
      struct type_list{};

      template<typename T, typename List>
      struct is_in_list;

      template<typename T>
      struct is_in_list<T,type_list<>> : std::false_type{};

      template<typename T, typename T0, typename...Ts>
      struct is_in_list<T,type_list<T0,Ts...>> : is_in_list<T,type_list<Ts...>>{};

      template<typename T, typename...Ts>
      struct is_in_list<T,type_list<T,Ts...>> : std::true_type{};

      template<typename T0, typename List, bool = std::is_final<T0>::value, bool = is_in_list<T0,List>::value>
      class compressed_tuple_impl;

      template<typename T0, typename T1, typename...Ts,bool B>
      class compressed_tuple_impl<T0,type_list<T1,Ts...>,true,B>
        : public compressed_tuple_impl<T1,type_list<Ts...>>
      {
      public:

        using base_type = compressed_tuple_impl<T1,type_list<Ts...>>;

        template<typename Arg0, typename...Args>
        constexpr compressed_tuple_impl( Arg0&& arg0, Args&&...args )
          : base_type( std::forward<Args>(args)... ),
            m_current( std::forward<Arg0>(arg0) )
        {

        }

        constexpr compressed_tuple_impl( const compressed_tuple_impl& other ) = default;
        constexpr compressed_tuple_impl( compressed_tuple_impl&& other ) = default;

        compressed_tuple_impl& operator=( const compressed_tuple_impl& other ) = default;
        compressed_tuple_impl& operator=( compressed_tuple_impl&& other ) = default;

        constexpr T0& current(){ return m_current; }
        constexpr const T0& current() const{ return m_current; }

        constexpr base_type& next(){ return (*this); }
        constexpr const base_type& next() const{ return (*this); }

      private:

        T0 m_current;
      };

      template<typename T0, typename T1, typename...Ts>
      class compressed_tuple_impl<T0,type_list<T1,Ts...>,false,true>
        : public compressed_tuple_impl<T1,type_list<Ts...>>
      {
      public:

        using base_type = compressed_tuple_impl<T1,type_list<Ts...>>;

        template<typename Arg0, typename...Args>
        constexpr compressed_tuple_impl( Arg0&& arg0, Args&&...args )
          : base_type( std::forward<Args>(args)... ),
            m_current( std::forward<Arg0>(arg0) )
        {

        }

        constexpr compressed_tuple_impl( const compressed_tuple_impl& other ) = default;
        constexpr compressed_tuple_impl( compressed_tuple_impl&& other ) = default;

        compressed_tuple_impl& operator=( const compressed_tuple_impl& other ) = default;
        compressed_tuple_impl& operator=( compressed_tuple_impl&& other ) = default;

        constexpr T0& current(){ return m_current; }
        constexpr const T0& current() const{ return m_current; }

        constexpr base_type& next(){ return (*this); }
        constexpr const base_type& next() const{ return (*this); }

      private:

        T0 m_current;
      };

      template<typename T0, typename T1, typename...Ts>
      class compressed_tuple_impl<T0,type_list<T1,Ts...>,false,false>
        : T0, public compressed_tuple_impl<T1,type_list<Ts...>>
      {
      public:
        using base_type = compressed_tuple_impl<T1,type_list<Ts...>>;

        template<typename Arg0, typename...Args>
        constexpr compressed_tuple_impl( Arg0&& arg0, Args&&...args )
          : base_type( std::forward<Args>(args)... ),
            T0( std::forward<Arg0>(arg0) )
        {

        }

        constexpr compressed_tuple_impl( const compressed_tuple_impl& other ) = default;
        constexpr compressed_tuple_impl( compressed_tuple_impl&& other ) = default;

        compressed_tuple_impl& operator=( const compressed_tuple_impl& other ) = default;
        compressed_tuple_impl& operator=( compressed_tuple_impl&& other ) = default;

        constexpr T0& current(){ return (*this); }
        constexpr const T0& current() const{ return (*this); }

        constexpr base_type& next(){ return (*this); }
        constexpr const base_type& next() const{ return (*this); }
      };

      template<typename T0,bool B>
      class compressed_tuple_impl<T0,type_list<>,true,B>
      {
      public:

        template<typename Arg0, typename...Args>
        constexpr compressed_tuple_impl( Arg0&& arg0, Args&&...args )
          : m_current( std::forward<Arg0>(arg0) )
        {

        }

        constexpr compressed_tuple_impl( const compressed_tuple_impl& other ) = default;
        constexpr compressed_tuple_impl( compressed_tuple_impl&& other ) = default;

        compressed_tuple_impl& operator=( const compressed_tuple_impl& other ) = default;
        compressed_tuple_impl& operator=( compressed_tuple_impl&& other ) = default;

        constexpr T0& current(){ return m_current; }
        constexpr const T0& current() const{ return m_current; }

      private:

        T0 m_current;
      };

      template<typename T0>
      class compressed_tuple_impl<T0,type_list<>,false,true>
      {
      public:

        template<typename Arg0, typename...Args>
        constexpr compressed_tuple_impl( Arg0&& arg0, Args&&...args )
          : m_current( std::forward<Arg0>(arg0) )
        {

        }

        constexpr compressed_tuple_impl( const compressed_tuple_impl& other ) = default;
        constexpr compressed_tuple_impl( compressed_tuple_impl&& other ) = default;

        compressed_tuple_impl& operator=( const compressed_tuple_impl& other ) = default;
        compressed_tuple_impl& operator=( compressed_tuple_impl&& other ) = default;

        constexpr T0& current(){ return m_current; }
        constexpr const T0& current() const{ return m_current; }

      private:

        T0 m_current;
      };

      template<typename T0>
      class compressed_tuple_impl<T0,type_list<>,false,false>
        : T0
      {
      public:

        template<typename Arg0, typename...Args>
        constexpr compressed_tuple_impl( Arg0&& arg0, Args&&...args )
          : T0( std::forward<Arg0>(arg0) )
        {

        }

        constexpr compressed_tuple_impl( const compressed_tuple_impl& other ) = default;
        constexpr compressed_tuple_impl( compressed_tuple_impl&& other ) = default;

        compressed_tuple_impl& operator=( const compressed_tuple_impl& other ) = default;
        compressed_tuple_impl& operator=( compressed_tuple_impl&& other ) = default;

        constexpr T0& current(){ return (*this); }
        constexpr const T0& current() const{ return (*this); }
      };
    } // namespace detail

    template<typename...Ts>
    class compressed_tuple;

    //////////////////////////////////////////////////////////////////////////
    ///
    /// \tparam Types the types to compress
    //////////////////////////////////////////////////////////////////////////
    template<typename T0, typename...Ts>
    class compressed_tuple<T0,Ts...>
      : protected detail::compressed_tuple_impl<T0,detail::type_list<Ts...>>
    {
    public:

      template<typename...Args>
      constexpr compressed_tuple( Args&&...args )
        : detail::compressed_tuple_impl<T0,detail::type_list<Ts...>>( std::forward<Args>(args)... )
      {

      }

      constexpr compressed_tuple( const compressed_tuple& other ) = default;
      constexpr compressed_tuple( compressed_tuple&& other ) = default;

      compressed_tuple& operator=( const compressed_tuple& other ) = default;
      compressed_tuple& operator=( compressed_tuple&& other ) = default;

    };

    template<>
    class compressed_tuple<>
    {
    public:

      constexpr compressed_tuple() noexcept = default;
      constexpr compressed_tuple( const compressed_tuple& other ) = default;
      constexpr compressed_tuple( compressed_tuple&& other ) = default;

      compressed_tuple& operator=( const compressed_tuple& other ) = default;
      compressed_tuple& operator=( compressed_tuple&& other ) = default;
    };

    template<typename...Args>
    constexpr compressed_tuple<std::decay_t<Args>...> make_compressed_tuple( Args&&...args )
    {
      return { std::forward<Args>(args)... };
    }


    template<std::size_t N, typename...Args>
    constexpr std::tuple_element_t<N,std::tuple<Args...>>&
      get( compressed_tuple<Args...>& );

    template<std::size_t N, typename...Args>
    constexpr const std::tuple_element_t<N,std::tuple<Args...>>&
      get( const compressed_tuple<Args...>& );

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_DETAIL_UTILITY_COMPRESSED_TUPLE_HPP */
