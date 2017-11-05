/**
 * \file associative_vtables.hpp
 *
 * \brief This header contains associative-type vtables used in set_view.hpp
 *        and map_view.hpp
 *
 * \note This is an internal header file, included by other library headers.
 *       Do not attempt to use it directly.
 */
#ifndef BIT_STL_CONTAINERS_DETAIL_ASSOCIATIVE_VTABLES_HPP
#define BIT_STL_CONTAINERS_DETAIL_ASSOCIATIVE_VTABLES_HPP

#include "../../utilities/stddef.hpp"
#include <memory>

namespace bit {
  namespace stl {
    namespace detail {

      ////////////////////////////////////////////////////////////////////////
      /// \brief A type used for type-erasing associative set-containers
      ///
      ////////////////////////////////////////////////////////////////////////
      template<typename T>
      class set_vtable
      {
      public:
        //--------------------------------------------------------------------
        // Public Member Types
        //--------------------------------------------------------------------

        using count_function_t = std::size_t(*)(const void*, const T&);
        using size_function_t  = std::size_t(*)(const void*);

        //--------------------------------------------------------------------
        // Public Members
        //--------------------------------------------------------------------
      public:

        count_function_t count_ptr = nullptr;
        size_function_t  size_ptr  = nullptr;

        //--------------------------------------------------------------------
        // Accessor
        //--------------------------------------------------------------------
      public:

        /// \brief Gets the set-vtable
        ///
        /// \return The construct set-vtable
        template<typename S>
        static const set_vtable* get_vtable()
        {
          static const set_vtable retval = []
          {
            set_vtable retval;
            build_vtable<S>(&retval);
            return retval;
          }();

          return &retval;
        }

        //--------------------------------------------------------------------
        // Constructor
        //--------------------------------------------------------------------
      protected:

        /// \brief Builds the set-vtable
        ///
        /// \param table the pointer to the vtable to build
        template<typename S>
        static void build_vtable( set_vtable* table )
        {
          const auto count_function = [](const void* ptr, const T& k) -> std::size_t
          {
            const S* ps = static_cast<const S*>(ptr);
            return ps->count( k );
          };

          const auto size_function = [](const void* ptr) -> std::size_t
          {
            const S* ps = static_cast<const S*>(ptr);
            return ps->size();
          };

          table->count_ptr = count_function;
          table->size_ptr  = size_function;
        }
      };

      ////////////////////////////////////////////////////////////////////////
      ///
      ////////////////////////////////////////////////////////////////////////
      template<typename Key, typename Value>
      class map_vtable : public set_vtable<Key>
      {
      public:
        //--------------------------------------------------------------------
        // Public Member Types
        //--------------------------------------------------------------------

        using at_function_t = const Value&(*)(const void*, const Key&);

        //--------------------------------------------------------------------
        // Public Members
        //--------------------------------------------------------------------
      public:

        at_function_t at_ptr;

        //--------------------------------------------------------------------
        // Accessor
        //--------------------------------------------------------------------
      public:

        template<typename S>
        static const map_vtable* get_vtable()
        {
          static const map_vtable retval = []
          {
            map_vtable retval;
            build_vtable<S>(&retval);
            return retval;
          }();

          return &retval;
        }

        //--------------------------------------------------------------------
        // Constructor
        //--------------------------------------------------------------------
      protected:

        template<typename S>
        static void build_vtable( map_vtable* table )
        {
          const auto at_function = [](const void* ptr, const Key& key) -> bool
          {
            const S* ps = static_cast<const S*>(ptr);
            return ps->at( key );
          };

          table->at_ptr = at_function;

          set_vtable<Key>::build_vtable( table );
        }

      };

    } // namespace detail
  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONTAINERS_DETAIL_ASSOCIATIVE_VTABLES_HPP */
