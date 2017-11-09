/**
 * \file circular_buffer_storage.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_CONTAINERS_DETAIL_CIRCULAR_BUFFER_STORAGE_HPP
#define BIT_STL_CONTAINERS_DETAIL_CIRCULAR_BUFFER_STORAGE_HPP

#include "../../utilities/compressed_pair.hpp"

#include <tuple>
#include <utility>

namespace bit {
  namespace stl {
    namespace detail {

      template<typename T, typename Allocator>
      class circular_storage_type
      {
        //---------------------------------------------------------------------
        // Constructors
        //---------------------------------------------------------------------
      public:

        circular_storage_type( circular_storage_type&& other )
          : storage( std::move(other.storage) )
        {

        }

        circular_storage_type( circular_storage_type&& other, const Allocator& alloc )
          : storage( std::piecewise_construct,
                     std::forward_as_tuple(std::move(other.storage.first())),
                     std::forward_as_tuple(alloc) )
        {

        }

        circular_storage_type( std::size_t n, const Allocator& alloc )
          : storage( std::piecewise_construct,
                     std::forward_as_tuple(),
                     std::forward_as_tuple(alloc) )
        {
          using traits_type = std::allocator_traits<Allocator>;
          auto p = traits_type::allocate( storage.second(), n );
          // No RAII needed; allocate is the only thing that can throw at this point

          storage.first() = circular_buffer<T>( p, n );
        }

        ~circular_storage_type()
        {
          auto& buffer    = storage.first();
          auto& allocator = storage.second();
          buffer.clear();
          std::allocator_traits<Allocator>::deallocate( allocator, buffer.data(), buffer.capacity() );
        }

        circular_buffer<T>& buffer() noexcept
        {
          return storage.first();
        }

        circular_buffer<T>& buffer() const noexcept
        {
          return storage.first();
        }

        const Allocator& get_allocator() const noexcept
        {
          return storage.second();
        }

        //---------------------------------------------------------------------
        // Private Member Types
        //---------------------------------------------------------------------
      private:

        using storage_type = compressed_pair<circular_buffer<T>,Allocator>;

        //---------------------------------------------------------------------
        // Private Members
        //---------------------------------------------------------------------
      private:

        storage_type storage;
      };

    } // namespace detail

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONTAINERS_DETAIL_CIRCULAR_BUFFER_STORAGE_HPP */
