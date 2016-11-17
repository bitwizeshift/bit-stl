/**
 * \file hashed_string_view.hpp
 *
 * \brief todo: fill in documentation
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_HASHED_STRING_VIEW_HPP
#define BIT_HASHED_STRING_VIEW_HPP

#include "string_view.hpp"

namespace bit {

  ////////////////////////////////////////////////////////////////////////////
  /// \class bfg::basic_hashed_string_view
  ///
  /// \brief The basic_hashed_string_view is a compile-time hashed wrapper
  ///        around a non-owning string (#basic_string_view).
  ///
  /// This provides compile-time hashed values for string literals, or
  /// constant-time hashed values for non-literal strings.
  ///
  /// Since the hash is stored with the string, it allows easy checking of
  /// the hash multiple times without any concerns for performance.
  ////////////////////////////////////////////////////////////////////////////
  template<
    typename CharT,
    typename Traits = std::char_traits<CharT>
  >
  class basic_hashed_string_view final
  {
    //------------------------------------------------------------------------
    // Public Member Types
    //------------------------------------------------------------------------
  public:

    using string_view_type = basic_string_view<CharT,Traits>;

    using char_type   = CharT;
    using traits_type = Traits;
    using size_type   = std::size_t;
    using hash_type   = std::size_t;

    struct const_char_wrapper
    {
      const_char_wrapper( const char_type* ptr ) : ptr(ptr){}

      const char_type* ptr;
    };

    //------------------------------------------------------------------------
    // Constructors
    //------------------------------------------------------------------------
  public:

    /// \brief Default constructs a basic_hashed_string_view without any content
    constexpr basic_hashed_string_view() noexcept;

    /// \brief Constructs a basic_hashed_string_view by copying another one
    ///
    /// \param rhs the string view being copied
    constexpr basic_hashed_string_view( const basic_hashed_string_view& rhs ) noexcept = default;

    /// \brief Constructs a basic_hashed_string_view by moving another one
    ///
    /// \param rhs the string view being moved
    constexpr basic_hashed_string_view( basic_hashed_string_view&& rhs ) noexcept = default;

    /// \brief Constructs a basic_hashed_string_view from a constant string
    ///
    /// \param str the string to convert into a hash
    template<size_t N>
    constexpr basic_hashed_string_view( const char_type(&str)[N] ) noexcept;

    /// \brief Constructs a basic_hashed_string_view from a std::basic_string
    ///
    /// \param str the string to view
    template<typename Allocator>
    constexpr basic_hashed_string_view( const std::basic_string<CharT,Traits,Allocator>& str ) noexcept;

    /// \brief Constructs a basic_hashed_string_view from an ansi-string
    ///
    /// \param str the string to view
    basic_hashed_string_view( const_char_wrapper str ) noexcept;

    /// \brief Constructs a basic_hashed_string_view from an ansi string of a given size
    ///
    /// \param str the string to view
    /// \param count the size of the string
    constexpr basic_hashed_string_view( const char_type* str, size_type count ) noexcept;

    //------------------------------------------------------------------------
    // Accessors
    //------------------------------------------------------------------------
  public:

    /// \brief Accessor to retrieve the hash from this hashed_string_view
    ///
    /// \return the hash for the string
    constexpr hash_type hash() const noexcept;

    /// \brief Accessor to retrieve the string for this hash
    ///
    /// \return the string being viewed
    constexpr string_view_type view() const noexcept;

    /// \brief Gets the data of the current basic_string_view
    ///
    /// \return the data this basic_string_view contains
    constexpr const char_type* c_str() const noexcept;

    /// \brief Gets the data of the current basic_string_view
    ///
    /// \return the data this basic_string_view contains
    constexpr const char_type* data() const noexcept;

    /// \brief Returns the length of the string, in terms of bytes
    ///
    /// \return the length of the string, in terms of bytes
    constexpr size_type size() const noexcept;

    /// \brief Swaps this hashed string with \p other
    ///
    /// \param other the other hashed string to swap with
    void swap( basic_hashed_string_view& other ) noexcept;

    //------------------------------------------------------------------------
    // Private Members
    //------------------------------------------------------------------------
  private:

    string_view_type m_view; ///< The string that this hash string represents
    hash_type        m_hash; ///< The type for this hash
  };

  //--------------------------------------------------------------------------
  // Comparison Operators
  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  constexpr bool operator == ( const basic_hashed_string_view<CharT,Traits>& lhs,
                               const basic_hashed_string_view<CharT,Traits>& rhs ) noexcept;

  template<typename CharT, typename Traits>
  constexpr bool operator != ( const basic_hashed_string_view<CharT,Traits>& lhs,
                               const basic_hashed_string_view<CharT,Traits>& rhs ) noexcept;

  template<typename CharT, typename Traits>
  constexpr bool operator < ( const basic_hashed_string_view<CharT,Traits>& lhs,
                              const basic_hashed_string_view<CharT,Traits>& rhs ) noexcept;

  template<typename CharT, typename Traits>
  constexpr bool operator > ( const basic_hashed_string_view<CharT,Traits>& lhs,
                              const basic_hashed_string_view<CharT,Traits>& rhs ) noexcept;

  template<typename CharT, typename Traits>
  constexpr bool operator <= ( const basic_hashed_string_view<CharT,Traits>& lhs,
                               const basic_hashed_string_view<CharT,Traits>& rhs ) noexcept;

  template<typename CharT, typename Traits>
  constexpr bool operator >= ( const basic_hashed_string_view<CharT,Traits>& lhs,
                               const basic_hashed_string_view<CharT,Traits>& rhs ) noexcept;

  //--------------------------------------------------------------------------
  // Mutators
  //--------------------------------------------------------------------------

  template<typename CharT, typename Traits>
  void swap( basic_hashed_string_view<CharT,Traits>& lhs,
             basic_hashed_string_view<CharT,Traits>& rhs ) noexcept;

  //--------------------------------------------------------------------------
  // Public Types
  //--------------------------------------------------------------------------

  using hashed_string_view    = basic_hashed_string_view<char>;
  using hashed_wstring_view   = basic_hashed_string_view<wchar_t>;
  using hashed_u16string_view = basic_hashed_string_view<char16_t>;
  using hashed_u32string_view = basic_hashed_string_view<char32_t>;

  //--------------------------------------------------------------------------
  // Hash Functions
  //--------------------------------------------------------------------------

  /// \brief Retrieves the hash from a given basic_hashed_string_view
  ///
  /// \param str the basic_hashed_string_view to retrieve the hash from
  /// \return the hash of the string
  template<typename CharT, typename Traits>
  constexpr std::size_t hash_value( const basic_hashed_string_view<CharT,Traits>& str )
    noexcept;

} // namespace bit

#include "detail/hashed_string_view.inl"

#endif /* BIT_HASHED_STRING_VIEW_HPP */
