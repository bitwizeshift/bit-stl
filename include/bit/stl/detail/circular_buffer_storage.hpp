/**
 * \file circular_buffer_storage.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_DETAIL_CIRCULAR_BUFFER_STORAGE_HPP
#define BIT_STL_DETAIL_CIRCULAR_BUFFER_STORAGE_HPP

namespace bit {
  namespace stl {

  namespace detail {

    template<typename T, typename Allocator>
    struct circular_storage_type : Allocator
    {
      circular_storage_type( circular_storage_type&& other ) noexcept
        : Allocator( std::move(other) ),
          buffer( std::move(other.buffer) )
      {

      }

      circular_storage_type( circular_storage_type&& other, const Allocator& alloc ) noexcept
        : Allocator( alloc ),
          buffer( std::move(other.buffer) )
      {

      }

      circular_storage_type( std::size_t n, const Allocator& alloc )
        : Allocator(alloc),
          buffer( std::allocator_traits<Allocator>::allocate( (*this), n ), n )
      {
      }

      ~circular_storage_type()
      {
        buffer.clear();
        std::allocator_traits<Allocator>::deallocate( (*this), buffer.data(), buffer.capacity() );
      }

      circular_buffer<T> buffer;
    };

  } // namespace detail

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_DETAIL_CIRCULAR_BUFFER_STORAGE_HPP */
