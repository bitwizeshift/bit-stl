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
          : m_storage( std::move(other.m_storage) )
        {

        }

        circular_storage_type( circular_storage_type&& other, const Allocator& alloc )
          : m_storage( std::piecewise_construct,
                     std::forward_as_tuple(std::move(other.m_storage.first())),
                     std::forward_as_tuple(alloc) )
        {

        }

        circular_storage_type( std::size_t n, const Allocator& alloc )
          : m_storage( std::piecewise_construct,
                     std::forward_as_tuple(),
                     std::forward_as_tuple(alloc) )
        {
          if( n == 0 ) return;

          using traits_type = std::allocator_traits<Allocator>;

          auto p = traits_type::allocate( m_storage.second(), n );
          // No RAII needed; allocate is the only thing that can throw at this point

          m_storage.first() = circular_buffer<T>( p, n );
        }

        ~circular_storage_type()
        {
          using traits_type = std::allocator_traits<Allocator>;
          auto& buffer    = m_storage.first();
          auto& allocator = m_storage.second();

          // Deconstruct all entries, then deallocate the memory
          if( buffer.data() != nullptr ) {
            buffer.clear();
            traits_type::deallocate( allocator, buffer.data(), buffer.capacity() );
          }
        }

        circular_buffer<T>& buffer() noexcept
        {
          return m_storage.first();
        }

        const circular_buffer<T>& buffer() const noexcept
        {
          return m_storage.first();
        }

        const Allocator& get_allocator() const noexcept
        {
          return m_storage.second();
        }

        void swap( circular_storage_type& other )
        {
          using std::swap;

          m_storage.swap(other.m_storage);
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

        storage_type m_storage;
      };

    } // namespace detail

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_CONTAINERS_DETAIL_CIRCULAR_BUFFER_STORAGE_HPP */
