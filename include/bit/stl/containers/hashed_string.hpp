/**
 * \file hashed_string.hpp
 *
 * \brief This header contains the definition for a hashed_string data type
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_CONTAINERS_HASHED_STRING_HPP
#define BIT_STL_CONTAINERS_HASHED_STRING_HPP

#include "string.hpp"             // bit::stl::hash_value
#include "hashed_string_view.hpp" // bit::stl::hashed_string_view

#include <string>      // std::basic_string
#include <type_traits> // std::is_nothrow_*

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief The basic_hashed_string is a wrapper around an owning
    ///        basic_string with the hash.
    ///
    /// This provides runtime hashed values for std::basic_strings
    ///
    /// Since the hash is stored with the string, it allows easy checking of
    /// the hash multiple times without any concerns for performance.
    ///
    /// \tparam CharT the type of string
    /// \tparam Traits the type of the traits
    /// \tparam Allocator the allocator
    //////////////////////////////////////////////////////////////////////////
    template<
      typename CharT,
      typename Traits = std::char_traits<CharT>,
      typename Allocator = std::allocator<CharT>
    >
    class basic_hashed_string
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using string_type      = std::basic_string<CharT,Traits,Allocator>;
      using string_view_type = basic_string_view<CharT,Traits>;

      using char_type   = CharT;
      using traits_type = Traits;
      using size_type   = std::size_t;
      using hash_type   = std::size_t;

      //----------------------------------------------------------------------
      // Constructor / Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Default-constructs a basic hashed string
      basic_hashed_string()
        noexcept( std::is_nothrow_default_constructible<Allocator>::value );

      /// \brief Constructs a basic hashed string from a given allocator
      ///
      /// \param alloc the allocator to copy
      explicit basic_hashed_string( const Allocator& alloc )
        noexcept( std::is_nothrow_copy_constructible<Allocator>::value );

      basic_hashed_string( size_type count,
                           CharT ch,
                           const Allocator& alloc = Allocator() );

      basic_hashed_string( const string_type& other,
                           size_type pos,
                           size_type count = string_type::npos,
                           const Allocator& alloc = Allocator() );

      basic_hashed_string( const CharT* s,
                           size_type count,
                           const Allocator& alloc = Allocator() );

      basic_hashed_string( const CharT* s,
                           const Allocator& alloc = Allocator() );

      template<typename InputIt>
      basic_hashed_string( InputIt first, InputIt last,
                           const Allocator& alloc = Allocator() );

      basic_hashed_string( const basic_hashed_string& other );

      basic_hashed_string( const basic_hashed_string& other,
                           const Allocator& alloc );

      basic_hashed_string( basic_hashed_string&& other ) noexcept;

      basic_hashed_string( basic_hashed_string&& other,
                           const Allocator& alloc );

      basic_hashed_string( std::initializer_list<CharT> init,
                           const Allocator& alloc = Allocator() );

      //----------------------------------------------------------------------

      /// \brief Copy-assigns a basic_hashed_string from another one
      ///
      /// \param other the other string to copy
      /// \return reference to \c (*this)
      basic_hashed_string& operator=( const basic_hashed_string& other ) = default;

      /// \brief Move-assigns a basic_hashed_string from another one
      ///
      /// \param other the other string to move
      /// \return reference to \c (*this)
      basic_hashed_string& operator=( basic_hashed_string&& other ) = default;

      /// \brief Assigns a basic_hashed_string from hashed_string_view
      ///
      /// \param other the view to copy
      /// \return reference to \c (*this)
      basic_hashed_string& operator=( string_view_type other );

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Accessor to retrieve the hash from this hashed_string_view
      ///
      /// \return the hash for the string
      hash_type hash() const noexcept;

      /// \brief Accessor to retrieve the string for this hash
      ///
      /// \return the string type
      string_view_type view() const noexcept;

      /// \brief Gets the data of the current basic_string_view
      ///
      /// \return the data this basic_string_view contains
      const char_type* c_str() const noexcept;

      /// \brief Gets the data of the current basic_string_view
      ///
      /// \return the data this basic_string_view contains
      const char_type* data() const noexcept;

      /// \brief Returns the length of the string, in terms of bytes
      ///
      /// \return the length of the string, in terms of bytes
      size_type size() const noexcept;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Swaps this hashed string with \p other
      ///
      /// \param other the other hashed string to swap with
      void swap( basic_hashed_string& other ) noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      string_type m_string; ///< The string that this hash string represents
      hash_type   m_hash;   ///< The type for this hash
    };

    //------------------------------------------------------------------------
    // Public Types
    //------------------------------------------------------------------------

    using hashed_string = basic_hashed_string<char>;
    using hashed_wstring = basic_hashed_string<wchar_t>;
    using hashed_u16string = basic_hashed_string<char16_t>;
    using hashed_u32string = basic_hashed_string<char32_t>;

    namespace ci {

      using hashed_string = basic_hashed_string<char, insensitive_char_traits<char>>;
      using hashed_wstring = basic_hashed_string<wchar_t, insensitive_char_traits<wchar_t>>;
      using hashed_u16string = basic_hashed_string<char16_t, insensitive_char_traits<char16_t>>;
      using hashed_u32string = basic_hashed_string<char32_t, insensitive_char_traits<char32_t>>;

    } // namespace ci

    //------------------------------------------------------------------------
    // Modifiers
    //------------------------------------------------------------------------

    template<typename CharT, typename Traits, typename Allocator>
    void swap( basic_hashed_string<CharT,Traits,Allocator>& lhs,
               basic_hashed_string<CharT,Traits,Allocator>& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Hash Functions
    //------------------------------------------------------------------------

    /// \brief Retrieves the hash from a given basic_hashed_string_view
    ///
    /// \param str the basic_hashed_string_view to retrieve the hash from
    /// \return the hash of the string
    template<typename CharT, typename Traits, typename Allocator>
    std::size_t
      hash_value( const basic_hashed_string<CharT,Traits,Allocator>& str )
      noexcept;

    //------------------------------------------------------------------------
    // Comparison Operators
    //------------------------------------------------------------------------

    template<typename CharT, typename Traits, typename Allocator>
    bool operator == ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                       const basic_hashed_string<CharT,Traits,Allocator>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator == ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                       const basic_hashed_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator == ( const basic_hashed_string_view<CharT,Traits>& lhs,
                       const basic_hashed_string<CharT,Traits,Allocator>& rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename CharT, typename Traits, typename Allocator>
    bool operator != ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                       const basic_hashed_string<CharT,Traits,Allocator>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator != ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                       const basic_hashed_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator != ( const basic_hashed_string_view<CharT,Traits>& lhs,
                       const basic_hashed_string<CharT,Traits,Allocator>& rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename CharT, typename Traits, typename Allocator>
    bool operator < ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                      const basic_hashed_string<CharT,Traits,Allocator>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator < ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                      const basic_hashed_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator < ( const basic_hashed_string_view<CharT,Traits>& lhs,
                      const basic_hashed_string<CharT,Traits,Allocator>& rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename CharT, typename Traits, typename Allocator>
    bool operator > ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                      const basic_hashed_string<CharT,Traits,Allocator>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator > ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                      const basic_hashed_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator > ( const basic_hashed_string_view<CharT,Traits>& lhs,
                      const basic_hashed_string<CharT,Traits,Allocator>& rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename CharT, typename Traits, typename Allocator>
    bool operator <= ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                       const basic_hashed_string<CharT,Traits,Allocator>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator <= ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                       const basic_hashed_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator <= ( const basic_hashed_string_view<CharT,Traits>& lhs,
                       const basic_hashed_string<CharT,Traits,Allocator>& rhs ) noexcept;

    //------------------------------------------------------------------------

    template<typename CharT, typename Traits, typename Allocator>
    bool operator >= ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                       const basic_hashed_string<CharT,Traits,Allocator>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator >= ( const basic_hashed_string<CharT,Traits,Allocator>& lhs,
                       const basic_hashed_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator >= ( const basic_hashed_string_view<CharT,Traits>& lhs,
                       const basic_hashed_string<CharT,Traits,Allocator>& rhs ) noexcept;

  } // namespace stl
} // namespace bit

#include "detail/hashed_string.inl"

#endif /* BIT_STL_CONTAINERS_HASHED_STRING_HPP */
