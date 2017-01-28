/**
 * \file utf8_string.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_UTF8_STRING_HPP
#define BIT_STL_UTF8_STRING_HPP

namespace bit {
  namespace stl {

    class utf8_string_iterator
    {
      using iterator_category = std::forward_iterator_tag;
      using value_type = char32_t;
      using difference_type = std::ptrdiff_t;
      using pointer = char32_t*;
      using reference = char32_t&;

      value_type* operator->();

      const value_type* operator->() const;

      value_type& operator*();

      const value_type& operator*() const;
    };

    //////////////////////////////////////////////////////////////////////////
    /// \brief A string wrapper around UTF-8 strings
    //////////////////////////////////////////////////////////////////////////
    template<typename Allocator = std::allocator<char>>
    class utf8_string
    {
      template<typename CharT> struct is_char : std::false_type{};
      template<> struct is_char<char> : std::true_type{};
      template<> struct is_char<wchar_t>  : std::true_type{};
      template<> struct is_char<char16_t> : std::true_type{};
      template<> struct is_char<char32_t> : std::true_type{};

      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using value_type     = char;
      using allocator_type = Allocator;

      using size_type       = typename std::allocator_traits<Allocator>::size_type;
      using difference_type = typename std::allocator_traits<Allocator>::difference_type;

      using reference       = typename std::allocator_traits<Allocator>::reference;
      using const_reference = typename std::allocator_traits<Allocator>::const_reference;
      using pointer         = typename std::allocator_traits<Allocator>::pointer;
      using const_pointer   = typename std::allocator_traits<Allocator>::const_pointer;

      //----------------------------------------------------------------------
      // Public Members
      //----------------------------------------------------------------------
    public:

      static constexpr size_type npos = size_type(-1);

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      // (1)
      utf8_string();

      // (1)
      explicit utf8_string( const Allocator& alloc );

      // (2)
      template<typename CharT>
      utf8_string( size_type count,
                   CharT ch,
                   const Allocator& alloc = Allocator() );


      // (3)
      template<typename CharT, typename Traits, typename Allocator>
      utf8_string( const std::basic_string<CharT,Traits,Allocator> other,
                   size_type pos,
                   const Allocator& alloc = Allocator() );

      // (3)
      template<typename CharT, typename Traits, typename Allocator>
      utf8_string( const std::basic_string<CharT,Traits,Allocator> other,
                   size_type pos,
                   size_type count,
                   const Allocator& alloc = Allocator() );

      // (4)
      template<typename CharT>
      utf8_string( const CharT*,
                   size_type count,
                   const Allocator& alloc = Allocator() );

      // (5)
      template<typename CharT>
      utf8_string( const CharT*,
                   const Allocator& alloc = Allocator() );

      // (6)
      template<typename InputIterator>
      utf8_string( InputIterator first, InputIterator last,
                   const Allocator& alloc = Allocator() );

      // (7)
      utf8_string( const utf8_string& other );

      // (7)
      utf8_string( const utf8_string& other, const Allocator& alloc  );

      // (8)
      utf8_string( utf8_string&& other );

      // (8)
      utf8_string( utf8_string&& other, const Allocator& alloc  );

      // (9)
      template<typename CharT>
      utf8_string( std::initializer_list<CharT> init,
                   const Allocator& alloc = Allocator() );

      //----------------------------------------------------------------------
      // Private Constructors
      //----------------------------------------------------------------------
    private:

      utf8_string( wchar_t*, size_type pos, size_type count, const Allocator& alloc );

      utf8_string( char16_t*, size_type pos, size_type count, const Allocator& alloc );

      utf8_string( char32_t*, size_type pos, size_type count, const Allocator& alloc );

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      using string_type = std::basic_string<char,std::char_traits<char>,Allocator>;

      string_type m_string; ///<
      std::size_t m_chars;  ///<
    };

  } // namespace stl
} // namespace bit

#endif /* BIT_STL_UTF8_STRING_HPP */
