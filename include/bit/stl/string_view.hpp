/**
 * \file string_view.hpp
 *
 * \brief This header includes a custom implementation of the
 *        C++17 standard's basic_string_view
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */
#ifndef BIT_STL_STRING_VIEW_HPP
#define BIT_STL_STRING_VIEW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "stddef.hpp"
#include "string.hpp"
#include "detail/iterator/pointer_iterator.hpp"

#include <algorithm>
#include <string>
#include <ostream>

#include "detail/string_hash.hpp"

namespace bit {
  namespace stl {

    //////////////////////////////////////////////////////////////////////////
    /// \brief A wrapper around non-owned strings.
    ///
    /// This is an implementation of the C++17 string_view proposal
    //////////////////////////////////////////////////////////////////////////
    template<
      typename CharT,
      typename Traits = std::char_traits<CharT>
    >
    class basic_string_view
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      static_assert( std::is_same<CharT,typename Traits::char_type>::value, "CharT must be the same as Traits::char_type");

      using value_type      = CharT;
      using traits_type     = Traits;
      using size_type       = std::size_t;
      using difference_type = std::ptrdiff_t;

      using pointer         = std::add_pointer_t<value_type>;
      using const_pointer   = std::add_pointer_t<const value_type>;
      using reference       = std::add_lvalue_reference_t<value_type>;
      using const_reference = std::add_lvalue_reference_t<const value_type>;

      using const_iterator         = pointer_iterator<const_pointer,basic_string_view>;
      using iterator               = const_iterator;
      using const_reverse_iterator = std::reverse_iterator<const_iterator>;
      using reverse_iterator       = const_reverse_iterator;

      //----------------------------------------------------------------------
      // Public Members
      //----------------------------------------------------------------------
    public:

      static constexpr size_type npos = size_type(-1);

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default constructs a basic_string_view without any content
      constexpr basic_string_view() noexcept;

      /// \brief Constructs a basic_string_view by copying another one
      ///
      /// \param other the string view being copied
      constexpr basic_string_view( const basic_string_view& other ) noexcept = default;

      /// \brief Constructs a basic_string_view by moving anothe rone
      ///
      /// \param other the string view being moved
      constexpr basic_string_view( basic_string_view&& other ) noexcept = default;

      /// \brief Constructs a basic_string_view from a std::basic_string
      ///
      /// \param str the string to view
      template<typename Allocator>
      constexpr basic_string_view( const std::basic_string<CharT,Traits,Allocator>& str ) noexcept;

      /// \brief Constructs a basic_string_view from an ansi-string
      ///
      /// \param str the string to view
      constexpr basic_string_view( const value_type* str ) noexcept;

      /// \brief Constructs a basic_string_view from an ansi string of a given size
      ///
      /// \param str the string to view
      /// \param count the size of the string
      constexpr basic_string_view( const value_type* str, size_type count ) noexcept;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Assigns a basic_string_view from an ansi-string
      ///
      /// \param view the string to view
      /// \return reference to \c (*this)
      basic_string_view& operator=( const basic_string_view& view ) = default;

      //----------------------------------------------------------------------
      // Capacity
      //----------------------------------------------------------------------
    public:

      /// \brief Returns the length of the string, in terms of bytes
      ///
      /// \return the length of the string, in terms of bytes
      constexpr size_type size() const noexcept;

      /// \copydoc basic_string_view::size
      constexpr size_type length() const noexcept;

      /// \brief The largest possible number of char-like objects that can be
      ///        referred to by a basic_string_view.
      /// \return Maximum number of characters
      constexpr size_type max_size() const noexcept;

      /// \brief Returns whether the basic_string_view is empty
      ///        (i.e. whether its length is 0).
      ///
      /// \return whether the basic_string_view is empty
      constexpr bool empty() const noexcept;

      //----------------------------------------------------------------------
      // Element Access
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the data of the current basic_string_view
      ///
      /// \return the data this basic_string_view contains
      constexpr const value_type* data() const noexcept;

      /// \brief Accesses the element at index \p pos
      ///
      /// \param pos the index to access
      /// \return const reference to the character
      constexpr const_reference operator[]( size_t pos ) const noexcept;

      /// \brief Accesses the element at index \p pos
      ///
      /// \param pos the index to access
      /// \return const reference to the character
      constexpr const_reference at( size_t pos ) const;

      /// \brief Access the first character of the string
      ///
      /// \note Undefined behavior if basic_string_view is empty
      ///
      /// \return reference to the first character of the string
      constexpr const_reference front() const noexcept;

      /// \brief References the last character of the string
      ///
      /// \note Undefined behavior if basic_string_view is empty
      ///
      /// \return reference to the last character of the string
      constexpr const_reference back() const noexcept;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Moves the start of the view forward by n characters.
      ///
      /// The behavior is undefined if n > size().
      ///
      /// \param n number of characters to remove from the start of the view
      constexpr void remove_prefix( size_type n ) noexcept;

      /// \brief Moves the end of the view back by n characters.
      ///
      /// The behavior is undefined if n > size().
      ///
      /// \param n number of characters to remove from the end of the view
      constexpr void remove_suffix( size_type n ) noexcept;

      /// \brief Exchanges the view with that of v.
      ///
      /// \param v view to swap with
      constexpr void swap( basic_string_view& v ) noexcept;

      //----------------------------------------------------------------------
      // Conversions
      //----------------------------------------------------------------------
    public:

      /// \brief Creates a basic_string with a copy of the content of the current view.
      ///
      /// \return A basic_string containing a copy of the characters of the current view.
      template<class Allocator>
      explicit operator std::basic_string<CharT, Traits, Allocator>() const;

      //----------------------------------------------------------------------
      // Operations
      //----------------------------------------------------------------------
    public:

      /// \brief Copies the substring [pos, pos + rcount) to the character string pointed
      ///        to by dest, where rcount is the smaller of count and size() - pos.
      ///
      /// \param dest pointer to the destination character string
      /// \param count requested substring length
      /// \param pos position of the first character
      size_type copy( value_type* dest,
                      size_type count = npos,
                      size_type pos = 0 ) const;

      /// \brief Returns a substring of this viewed string
      ///
      /// \param pos the position of the first character in the substring
      /// \param len the length of the substring
      /// \return the created substring
      constexpr basic_string_view substr( size_type pos = 0, size_type len = npos ) const;

      //----------------------------------------------------------------------

      /// \brief Compares two character sequences
      ///
      /// \param v view to compare
      /// \return negative value if this view is less than the other character
      ///         sequence, zero if the both character sequences are equal, positive
      ///         value if this view is greater than the other character sequence.
      constexpr int compare( basic_string_view v ) const noexcept;

      /// \brief Compares two character sequences
      ///
      /// \param pos   position of the first character in this view to compare
      /// \param count number of characters of this view to compare
      /// \param v     view to compare
      /// \return negative value if this view is less than the other character
      ///         sequence, zero if the both character sequences are equal, positive
      ///         value if this view is greater than the other character sequence.
      constexpr int compare( size_type pos, size_type count,
                             basic_string_view v ) const;

      /// \brief Compares two character sequences
      ///
      /// \param pos1   position of the first character in this view to compare
      /// \param count1 number of characters of this view to compare
      /// \param v      view to compare
      /// \param pos2   position of the second character in this view to compare
      /// \param count2 number of characters of the given view to compare
      /// \return negative value if this view is less than the other character
      ///         sequence, zero if the both character sequences are equal, positive
      ///         value if this view is greater than the other character sequence.
      constexpr int compare( size_type pos1, size_type count1, basic_string_view v,
                             size_type pos2, size_type count2 ) const;

      /// \brief Compares two character sequences
      ///
      /// \param s pointer to the character string to compare to
      /// \return negative value if this view is less than the other character
      ///         sequence, zero if the both character sequences are equal, positive
      ///         value if this view is greater than the other character sequence.
      constexpr int compare( const value_type* s ) const;

      /// \brief Compares two character sequences
      ///
      /// \param pos   position of the first character in this view to compare
      /// \param count number of characters of this view to compare
      /// \param s pointer to the character string to compare to
      /// \return negative value if this view is less than the other character
      ///         sequence, zero if the both character sequences are equal, positive
      ///         value if this view is greater than the other character sequence.
      constexpr int compare( size_type pos, size_type count,
                             const value_type* s ) const;

      /// \brief Compares two character sequences
      ///
      /// \param pos   position of the first character in this view to compare
      /// \param count1 number of characters of this view to compare
      /// \param s pointer to the character string to compare to
      /// \param count2 number of characters of the given view to compare
      /// \return negative value if this view is less than the other character
      ///         sequence, zero if the both character sequences are equal, positive
      ///         value if this view is greater than the other character sequence.
      constexpr int compare( size_type pos, size_type count1, const value_type* s,
                             size_type count2 ) const;

      //----------------------------------------------------------------------


      /// \brief Finds the first substring equal to the given character sequence
      ///
      /// Finds the first occurence of \p v in this view, starting at position
      /// \p pos
      ///
      /// \param v   view to search for
      /// \param pos position at which to start the search
      /// \return Position of the first character of the found substring, or
      ///         \c npos if no such substring is found
      constexpr size_type find( basic_string_view v, size_type pos = 0 ) const;

      /// \brief Finds the first substring equal to the given character sequence
      ///
      /// Equivalent to \code find(basic_string_view(&c, 1), pos) \endcode
      ///
      /// \param ch  character to search for
      /// \param pos position at which to start the search
      /// \return Position of the first character of the found substring, or
      ///         \c npos if no such substring is found
      constexpr size_type find( value_type ch, size_type pos = 0 ) const;

      /// \brief Finds the first substring equal to the given character sequence
      ///
      /// Equivalent to \code find(basic_string_view(s, count), pos) \endcode
      ///
      /// \param s     pointer to a character string to search for
      /// \param pos   position at which to start the search
      /// \param count length of substring to search for
      /// \return Position of the first character of the found substring, or
      ///         \c npos if no such substring is found
      constexpr size_type find( const value_type* s, size_type pos, size_type count ) const;

      /// \brief Finds the first substring equal to the given character sequence
      ///
      /// Equivalent to \code find(basic_string_view(s), pos) \endcode
      ///
      /// \param s     pointer to a character string to search for
      /// \param pos   position at which to start the search
      /// \return Position of the first character of the found substring, or
      ///         \c npos if no such substring is found
      constexpr size_type find( const value_type* s, size_type pos = 0 ) const;

      //----------------------------------------------------------------------

      /// \brief Finds the last substring equal to the given character sequence
      ///
      /// Finds the last occurence of \p v in this view, starting at position
      /// \p pos
      ///
      /// \param v   view to search for
      /// \param pos position at which to start the search
      /// \return Position of the first character of the found substring or
      ///         \c npos if no such substring is found
      constexpr size_type rfind( basic_string_view v, size_type pos = npos ) const;

      /// \brief Finds the last substring equal to the given character sequence
      ///
      /// Equivalent to \code rfind(basic_string_view(&c, 1), pos) \endcode
      ///
      /// \param ch  character to search for
      /// \param pos position at which to start the search
      /// \return Position of the first character of the found substring or
      ///         \c npos if no such substring is found
      constexpr size_type rfind( value_type c, size_type pos = npos ) const;

      /// \brief Finds the last substring equal to the given character sequence
      ///
      /// Equivalent to \code rfind(basic_string_view(s, count), pos) \endcode
      ///
      /// \param s     pointer to a character string to search for
      /// \param pos   position at which to start the search
      /// \param count length of substring to search for
      /// \return Position of the first character of the found substring or
      ///         \c npos if no such substring is found
      constexpr size_type rfind( const value_type* s, size_type pos, size_type count ) const;

      /// \brief Finds the last substring equal to the given character sequence
      ///
      /// Equivalent to \code rfind(basic_string_view(s), pos) \endcode
      ///
      /// \param s     pointer to a character string to search for
      /// \param pos   position at which to start the search
      /// \return Position of the first character of the found substring or
      ///         \c npos if no such substring is found
      constexpr size_type rfind( const value_type* s, size_type pos = npos ) const;

      //----------------------------------------------------------------------

      /// \brief Finds the first character equal to any of the characters in
      ///        the given character sequence
      ///
      /// Finds the first occurence of any of the characters of \p v in this
      /// view, starting at position \p pos.
      ///
      /// \param v   view to search for
      /// \param pos position at which to start the search
      /// \return Position of the first occurrence of any character of the substring,
      ///         or \c npos if no such character is found.
      constexpr size_type find_first_of( basic_string_view v, size_type pos = 0 ) const;

      /// \brief Finds the first character equal to any of the characters in
      ///        the given character sequence
      ///
      /// Equivalent to \code find_first_of(basic_string_view(&c, 1), pos) \endcode
      ///
      /// \param ch  character to search for
      /// \param pos position at which to start the search
      /// \return Position of the first occurrence of any character of the substring,
      ///         or \c npos if no such character is found.
      constexpr size_type find_first_of( value_type c, size_type pos = 0 ) const;

      /// \brief Finds the first character equal to any of the characters in
      ///        the given character sequence
      ///
      /// Equivalent to \code find_first_of(basic_string_view(s, count), pos) \endcode
      ///
      /// \param s     pointer to a character string to search for
      /// \param pos   position at which to start the search
      /// \param count length of substring to search for
      /// \return Position of the first occurrence of any character of the substring,
      ///         or \c npos if no such character is found.
      constexpr size_type find_first_of( const value_type* s, size_type pos, size_type count ) const;

      /// \brief Finds the first character equal to any of the characters in
      ///        the given character sequence
      ///
      /// Equivalent to \code find_first_of(basic_string_view(s), pos) \endcode
      ///
      /// \param s     pointer to a character string to search for
      /// \param pos   position at which to start the search
      /// \return Position of the first occurrence of any character of the substring,
      ///         or \c npos if no such character is found.
      constexpr size_type find_first_of( const value_type* s, size_type pos = 0 ) const;

      //----------------------------------------------------------------------

      /// \brief Finds the last character equal to any of the characters in the
      ///        given character sequence
      ///
      /// Finds the last occurence of any of the characters of \p v in this view,
      /// starting at position \p pos
      ///
      /// \param v   view to search for
      /// \param pos position at which to start the search
      /// \return Position of the last occurrence of any character of the substring,
      ///         or \c npos if no such character is found.
      constexpr size_type find_last_of( basic_string_view v, size_type pos = npos ) const;

      /// \brief Finds the last character equal to any of the characters in the
      ///        given character sequence
      ///
      /// Equivalent to \code find_last_of(basic_string_view(&c, 1), pos) \endcode
      ///
      /// \param ch  character to search for
      /// \param pos position at which to start the search
      /// \return Position of the last occurrence of any character of the substring,
      ///         or \c npos if no such character is found.
      constexpr size_type find_last_of( value_type c, size_type pos = npos ) const;

      /// \brief Finds the last character equal to any of the characters in the
      ///        given character sequence
      ///
      /// Equivalent to \code find_last_of(basic_string_view(s, count), pos) \endcode
      ///
      /// \param s     pointer to a character string to search for
      /// \param pos   position at which to start the search
      /// \param count length of substring to search for
      /// \return Position of the last occurrence of any character of the substring,
      ///         or \c npos if no such character is found.
      constexpr size_type find_last_of( const value_type* s, size_type pos, size_type count ) const;

      /// \brief Finds the last character equal to any of the characters in the
      ///        given character sequence
      ///
      /// Equivalent to \code find_last_of(basic_string_view(s), pos) \endcode
      ///
      /// \param s     pointer to a character string to search for
      /// \param pos   position at which to start the search
      ///
      /// \return Position of the last occurrence of any character of the substring,
      ///         or \c npos if no such character is found.
      constexpr size_type find_last_of( const value_type* s, size_type pos = npos ) const;

      //----------------------------------------------------------------------

      /// \brief Finds the first character not equal to any of the characters in
      ///        the given character sequence
      ///
      /// Finds the first character not equal to any of the characters of \p v
      /// in this view, starting at position \p pos
      ///
      /// \param v   view to search for
      /// \param pos position at which to start the search
      /// \return Position of the first character not equal to any of the characters
      ///         in the given string, or npos if no such character is found
      constexpr size_type find_first_not_of( basic_string_view v, size_type pos = 0 ) const;

      /// \brief Finds the first character not equal to any of the characters in
      ///        the given character sequence
      ///
      /// Equivalent to \code find_first_not_of(basic_string_view(&c, 1), pos) \endcode
      ///
      /// \param ch  character to search for
      /// \param pos position at which to start the search
      /// \return Position of the first character not equal to any of the characters
      ///         in the given string, or npos if no such character is found
      constexpr size_type find_first_not_of( value_type c, size_type pos = 0 ) const;

      /// \brief Finds the first character not equal to any of the characters in
      ///        the given character sequence
      ///
      /// Equivalent to \code find_first_not_of(basic_string_view(s, count), pos) \endcode
      ///
      /// \param s     pointer to a character string to search for
      /// \param pos   position at which to start the search
      /// \param count length of substring to search for
      /// \return Position of the first character not equal to any of the characters
      ///         in the given string, or npos if no such character is found
      constexpr size_type find_first_not_of( const value_type* s, size_type pos, size_type count ) const;

      /// \brief Finds the first character not equal to any of the characters in
      ///        the given character sequence
      ///
      /// Equivalent to \code find_first_not_of(basic_string_view(s), pos) \endcode
      ///
      /// \param s     pointer to a character string to search for
      /// \param pos   position at which to start the search
      /// \return Position of the first character not equal to any of the characters
      ///         in the given string, or npos if no such character is found
      constexpr size_type find_first_not_of( const value_type* s, size_type pos = 0 ) const;

      //----------------------------------------------------------------------

      /// \brief Finds the last character not equal to any of the characters in
      ///        the given character sequence
      ///
      /// Finds the last character not equal to any of the characters of \p v
      /// in this view, starting at position \p pos
      ///
      /// \param v   view to search for
      /// \param pos position at which to start the search
      /// \return Position of the last character not equal to any of the characters
      ///         in the given string, or npos if no such character is found
      constexpr size_type find_last_not_of( basic_string_view v, size_type pos = npos ) const;

      /// \brief Finds the last character not equal to any of the characters in
      ///        the given character sequence
      ///
      /// Equivalent to \code find_last_not_of(basic_string_view(&c, 1), pos) \endcode
      ///
      /// \param ch  character to search for
      /// \param pos position at which to start the search
      /// \return Position of the last character not equal to any of the characters
      ///         in the given string, or npos if no such character is found
      constexpr size_type find_last_not_of( value_type c, size_type pos = npos ) const;

      /// \brief Finds the last character not equal to any of the characters in
      ///        the given character sequence
      ///
      /// Equivalent to \code find_last_not_of(basic_string_view(s, count), pos) \endcode
      ///
      /// \param s     pointer to a character string to search for
      /// \param pos   position at which to start the search
      /// \param count length of substring to search for
      /// \return Position of the last character not equal to any of the characters
      ///         in the given string, or npos if no such character is found
      constexpr size_type find_last_not_of( const value_type* s, size_type pos, size_type count ) const;

      /// \brief Finds the last character not equal to any of the characters in
      ///        the given character sequence
      ///
      /// Equivalent to \code find_last_not_of(basic_string_view(s), pos) \endcode
      ///
      /// \param s     pointer to a character string to search for
      /// \param pos   position at which to start the search
      /// \return Position of the last character not equal to any of the characters
      ///         in the given string, or npos if no such character is found
      constexpr size_type find_last_not_of( const value_type* s, size_type pos = npos ) const;

      //----------------------------------------------------------------------
      // Iterators
      //----------------------------------------------------------------------
    public:

      /// \brief Retrieves the begin iterator for this basic_string_view
      ///
      /// \return the begin iterator
      constexpr const_iterator begin() const noexcept;

      /// \copydoc basic_string_view::begin()
      constexpr const_iterator cbegin() const noexcept;

      /// \brief Retrieves the end iterator for this basic_string_view
      ///
      /// \return the end iterator
      constexpr const_iterator end() const noexcept;

      /// \copydoc basic_string_view::end()
      constexpr const_iterator cend() const noexcept;

      /// \brief Retrieves the reverse iterator for this basic_string_view
      ///
      /// \return the begin reverse iterator
      constexpr const_reverse_iterator rbegin() const noexcept;

      /// \copydoc basic_string_view::rbegin()
      constexpr const_reverse_iterator crbegin() const noexcept;

      /// \brief Retrieves the reverse end iterator for this basic_string_view
      ///
      /// \return the end reverse iterator
      constexpr const_reverse_iterator rend() const noexcept;

      /// \copydoc basic_string_view::rend()
      constexpr const_reverse_iterator crend() const noexcept;

      //----------------------------------------------------------------------
      // Private Member
      //----------------------------------------------------------------------
    private:

      const value_type* m_str;  ///< The internal string type
      size_type        m_size; ///< The size of this string

    };

    //------------------------------------------------------------------------

    //////////////////////////////////////////////////////////////////////////
    /// \brief A wrapper around non-owned zero-terminated strings.
    ///
    /// This is an extension to the C++17 string_view
    ///
    /// This class is used to interop with C libraries that expect normal
    /// strings
    //////////////////////////////////////////////////////////////////////////
    template<
      typename CharT,
      typename Traits = std::char_traits<CharT>
    >
    class basic_zstring_view : public basic_string_view<CharT,Traits>
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      static_assert( std::is_same<CharT,typename Traits::char_type>::value, "CharT must be the same as Traits::char_type");

      using typename basic_string_view<CharT,Traits>::value_type;
      using typename basic_string_view<CharT,Traits>::traits_type;
      using typename basic_string_view<CharT,Traits>::size_type;
      using typename basic_string_view<CharT,Traits>::difference_type;

      using typename basic_string_view<CharT,Traits>::pointer;
      using typename basic_string_view<CharT,Traits>::const_pointer;
      using typename basic_string_view<CharT,Traits>::reference;
      using typename basic_string_view<CharT,Traits>::const_reference;

      using typename basic_string_view<CharT,Traits>::const_iterator;
      using typename basic_string_view<CharT,Traits>::iterator;
      using typename basic_string_view<CharT,Traits>::const_reverse_iterator;
      using typename basic_string_view<CharT,Traits>::reverse_iterator;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Default constructs a basic_string_view without any content
      constexpr basic_zstring_view() noexcept = default;

      /// \brief Constructs a basic_string_view by copying another one
      ///
      /// \param other the string view being copied
      constexpr basic_zstring_view( const basic_zstring_view& other ) noexcept = default;

      /// \brief Constructs a basic_string_view by moving anothe rone
      ///
      /// \param other the string view being moved
      constexpr basic_zstring_view( basic_zstring_view&& other ) noexcept = default;

      /// \brief Constructs a basic_string_view from an ansi-string
      ///
      /// \param str the string to view
      constexpr basic_zstring_view( const value_type* str ) noexcept;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Assigns a basic_zstring_view from an ansi-string
      ///
      /// \param view the string to view
      /// \return reference to \c (*this)
      basic_zstring_view& operator=( const basic_zstring_view& view ) = default;

      //----------------------------------------------------------------------
      // Modifiers
      //----------------------------------------------------------------------
    public:

      /// \brief Delete remove_prefix in zstring_view
      constexpr void remove_prefix( size_type n ) noexcept = delete;

      /// \brief Delete remove_suffix in zstring_view
      constexpr void remove_suffix( size_type n ) noexcept = delete;

      //----------------------------------------------------------------------
      // Element Access
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the data of the current basic_zstring_view
      ///
      /// \return the data this basic_zstring_view contains
      constexpr const value_type* c_str() const noexcept;

    };

    //------------------------------------------------------------------------
    // Type Aliases
    //------------------------------------------------------------------------

    using string_view    = basic_string_view<char>;
    using wstring_view   = basic_string_view<wchar_t>;
    using u16string_view = basic_string_view<char16_t>;
    using u32string_view = basic_string_view<char32_t>;

    using zstring_view    = basic_zstring_view<char>;
    using wzstring_view   = basic_zstring_view<wchar_t>;
    using u16zstring_view = basic_zstring_view<char16_t>;
    using u32zstring_view = basic_zstring_view<char32_t>;

    namespace ci {

      using string_view    = basic_string_view<char, insensitive_char_traits<char>>;
      using wstring_view   = basic_string_view<wchar_t, insensitive_char_traits<wchar_t>>;
      using u16string_view = basic_string_view<char16_t, insensitive_char_traits<char16_t>>;
      using u32string_view = basic_string_view<char32_t, insensitive_char_traits<char32_t>>;

      using zstring_view    = basic_zstring_view<char, insensitive_char_traits<char>>;
      using wzstring_view   = basic_zstring_view<wchar_t, insensitive_char_traits<wchar_t>>;
      using u16zstring_view = basic_zstring_view<char16_t, insensitive_char_traits<char16_t>>;
      using u32zstring_view = basic_zstring_view<char32_t, insensitive_char_traits<char32_t>>;

    } // namespace ci

    //------------------------------------------------------------------------
    // Hash Functions
    //------------------------------------------------------------------------

    /// \brief Retrieves the hash from a given basic_string_view
    ///
    /// \param str the basic_ string_view to retrieve the hash from
    /// \return the hash of the string
    template<typename CharT, typename Traits>
    constexpr std::size_t hash_value( const basic_string_view<CharT,Traits>& str )
      noexcept;

    //------------------------------------------------------------------------
    // Public Functions
    //------------------------------------------------------------------------

    /// \brief Overload for ostream output of basic_string_view
    ///
    /// \param o   The output stream to print to
    /// \param str the string to print
    /// \return reference to the output stream
    template<typename CharT, typename Traits>
    std::basic_ostream<CharT,Traits>& operator << ( std::basic_ostream<CharT,Traits>& o,
                                                    const basic_string_view<CharT,Traits>& str );

    template<typename CharT, typename Traits>
    void swap( basic_string_view<CharT,Traits>& lhs,
               basic_string_view<CharT,Traits>& rhs ) noexcept;

    //------------------------------------------------------------------------
    // Literals
    //------------------------------------------------------------------------

    inline namespace literals {
      inline namespace string_view_literals {

        constexpr string_view operator "" _sv(const char* str, size_t len) noexcept;
        constexpr wstring_view operator "" _sv(const wchar_t* str, size_t len) noexcept;
        constexpr u16string_view operator "" _sv(const char16_t* str, size_t len) noexcept;
        constexpr u32string_view operator "" _sv(const char32_t* str, size_t len) noexcept;

      } // inline namespace string_view_literals
    } // inline namespace literals

    //------------------------------------------------------------------------
    // Comparison Functions
    //------------------------------------------------------------------------

    /// \brief Compares equality between the two basic_string_views
    ///
    /// \param lhs the left string view
    /// \param rhs the right string view
    /// \return true if the two strings are the same
    template<typename CharT, typename Traits>
    bool operator == ( const basic_string_view<CharT,Traits>& lhs,
                       const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, std::size_t N>
    bool operator == ( const basic_string_view<CharT,Traits>& lhs,
                       CharT (&rhs)[N] ) noexcept;

    template<typename CharT, typename Traits, std::size_t N>
    bool operator == ( CharT (&lhs)[N],
                       const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits>
    bool operator == ( basic_string_view<CharT,Traits> lhs,
                       const CharT* rhs )  noexcept;

    template<typename CharT, typename Traits>
    bool operator == ( const CharT* lhs,
                       const basic_string_view<CharT,Traits>& rhs )  noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator == ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                       const basic_string_view<CharT,Traits>& rhs )  noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator == ( const basic_string_view<CharT,Traits>& lhs,
                       const std::basic_string<CharT,Traits,Allocator>& rhs ) noexcept;

    //----------------------------------------------------------------------------

    /// \brief Compares inequality between the two basic_string_views
    ///
    /// \param lhs the left string view
    /// \param rhs the right string view
    /// \return true if the two strings are different
    template<typename CharT, typename Traits>
    bool operator != ( const basic_string_view<CharT,Traits>& lhs,
                       const basic_string_view<CharT,Traits>& rhs ) noexcept;


    template<typename CharT, typename Traits, std::size_t N>
    bool operator != ( const basic_string_view<CharT,Traits>& lhs,
                       CharT (&rhs)[N] ) noexcept;

    template<typename CharT, typename Traits, std::size_t N>
    bool operator != ( CharT (&lhs)[N],
                       const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits>
    bool operator != ( const basic_string_view<CharT,Traits>& lhs,
                       const CharT* rhs ) noexcept;

    template<typename CharT, typename Traits>
    bool operator != ( const CharT* lhs,
                       const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator != ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                       const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator != ( const basic_string_view<CharT,Traits>& lhs,
                       const std::basic_string<CharT,Traits,Allocator>& rhs ) noexcept;

    //----------------------------------------------------------------------------

    /// \brief Checks if the left string is less than the right substring
    ///
    /// \param lhs the left string view
    /// \param rhs the right string view
    /// \return true if the left string has a character less than the right
    ///         string, or if the right string is shorter than the left string
    template<typename CharT, typename Traits>
    bool operator < ( const basic_string_view<CharT,Traits>& lhs,
                      const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits>
    bool operator < ( const basic_string_view<CharT,Traits>& lhs,
                      const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, std::size_t N>
    bool operator < ( const basic_string_view<CharT,Traits>& lhs,
                      CharT (&rhs)[N] ) noexcept;

    template<typename CharT, typename Traits, std::size_t N>
    bool operator < ( CharT (&lhs)[N],
                      const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits>
    bool operator < ( const basic_string_view<CharT,Traits>& lhs,
                      const CharT* rhs )  noexcept;

    template<typename CharT, typename Traits>
    bool  operator < ( const CharT* lhs,
                       const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator < ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                      const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator < ( const basic_string_view<CharT,Traits>& lhs,
                      const std::basic_string<CharT,Traits,Allocator>& rhs ) noexcept;

    //----------------------------------------------------------------------------

    ///
    /// \param lhs
    /// \param rhs
    /// \return
    template<typename CharT, typename Traits>
    bool operator > ( const basic_string_view<CharT,Traits>& lhs,
                      const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits>
    bool operator > ( const basic_string_view<CharT,Traits>& lhs,
                      const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, std::size_t N>
    bool operator > ( const basic_string_view<CharT,Traits>& lhs,
                      CharT (&rhs)[N] ) noexcept;

    template<typename CharT, typename Traits, std::size_t N>
    bool operator > ( CharT (&lhs)[N],
                      const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits>
    bool operator > ( const basic_string_view<CharT,Traits>& lhs,
                      const CharT* rhs ) noexcept;

    template<typename CharT, typename Traits>
    bool operator > ( const CharT* lhs,
                      const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator > ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                      const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator > ( const basic_string_view<CharT,Traits>& lhs,
                      const std::basic_string<CharT,Traits,Allocator>& rhs ) noexcept;

    //----------------------------------------------------------------------------

    ///
    /// \param lhs
    /// \param rhs
    /// \return
    template<typename CharT, typename Traits>
    bool operator <= ( const basic_string_view<CharT,Traits>& lhs,
                       const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits>
    bool operator <= ( const basic_string_view<CharT,Traits>& lhs,
                       const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, std::size_t N>
    bool operator <= ( const basic_string_view<CharT,Traits>& lhs,
                       CharT (&rhs)[N] ) noexcept;

    template<typename CharT, typename Traits, std::size_t N>
    bool operator <= ( CharT (&lhs)[N],
                       const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits>
    bool operator <= ( const basic_string_view<CharT,Traits>& lhs,
                       const CharT* rhs ) noexcept;

    template<typename CharT, typename Traits>
    bool operator <= ( const CharT* lhs,
                       const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator <= ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                       const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator <= ( const basic_string_view<CharT,Traits>& lhs,
                       const std::basic_string<CharT,Traits,Allocator>& rhs ) noexcept;

    //----------------------------------------------------------------------------

    ///
    /// \param lhs
    /// \param rhs
    /// \return
    template<typename CharT, typename Traits>
    bool operator >= ( const basic_string_view<CharT,Traits>& lhs,
                       const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits>
    bool operator >= ( const basic_string_view<CharT,Traits>& lhs,
                       const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, std::size_t N>
    bool operator >= ( const basic_string_view<CharT,Traits>& lhs,
                       CharT (&rhs)[N] ) noexcept;

    template<typename CharT, typename Traits, std::size_t N>
    bool operator >= ( CharT (&lhs)[N],
                       const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits>
    bool operator >= ( const basic_string_view<CharT,Traits>& lhs,
                       const CharT* rhs ) noexcept;

    template<typename CharT, typename Traits>
    bool operator >= ( const CharT* lhs,
                       const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator >= ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                       const basic_string_view<CharT,Traits>& rhs ) noexcept;

    template<typename CharT, typename Traits, typename Allocator>
    bool operator >= ( const basic_string_view<CharT,Traits>& lhs,
                       const std::basic_string<CharT,Traits,Allocator>& rhs ) noexcept;

    //----------------------------------------------------------------------------
    // String Concatenation
    //----------------------------------------------------------------------------

    template<typename CharT, typename Traits, typename Allocator>
    std::basic_string<CharT,Traits,Allocator> operator + ( const std::basic_string<CharT,Traits,Allocator>& lhs,
                                                           const basic_string_view<CharT,Traits>& rhs );

    template<typename CharT, typename Traits, typename Allocator>
    std::basic_string<CharT,Traits,Allocator> operator + ( const basic_string_view<CharT,Traits>& lhs,
                                                           const std::basic_string<CharT,Traits,Allocator>& rhs );

    template<typename CharT, typename Traits, typename Allocator>
    std::basic_string<CharT,Traits,Allocator>& operator += ( std::basic_string<CharT,Traits,Allocator>& lhs,
                                                             const basic_string_view<CharT,Traits>& rhs );

  } // namespace stl

  inline namespace literals {
    using namespace stl::literals;
  } // inline namespace literals
} // namespace bit

#include "detail/string_view.inl"

#endif /* BIT_STL_STRING_VIEW_HPP */
