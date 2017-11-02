/**
 * \file string_span.hpp
 *
 * \brief Thie file contains a mutable view of a string
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_STL_CONTAINERS_STRING_SPAN_HPP
#define BIT_STL_CONTAINERS_STRING_SPAN_HPP

#include "span.hpp"

#include "../traits/negation.hpp"
#include "../traits/conjunction.hpp"

#include "../concepts/ContiguousContainer.hpp"

namespace bit {
  namespace stl {

    //------------------------------------------------------------------------
    // Type Aliases
    //------------------------------------------------------------------------

    template<typename CharT, typename Traits = std::char_traits<CharT>, std::ptrdiff_t Extent = dynamic_extent>
    using basic_zstring = CharT*;

    template<std::ptrdiff_t Extent = dynamic_extent>
    using zstring = basic_zstring<char, std::char_traits<char>, Extent>;

    template<std::ptrdiff_t Extent = dynamic_extent>
    using wzstring = basic_zstring<wchar_t, std::char_traits<wchar_t>, Extent>;

    template<std::ptrdiff_t Extent = dynamic_extent>
    using u16zstring = basic_zstring<char16_t, std::char_traits<char16_t>, Extent>;

    template<std::ptrdiff_t Extent = dynamic_extent>
    using u32zstring = basic_zstring<char32_t, std::char_traits<char32_t>, Extent>;

    //------------------------------------------------------------------------

    template<typename CharT, typename Traits, std::ptrdiff_t Extent>
    class basic_string_span;

    template<std::ptrdiff_t Extent>
    using string_span = basic_string_span<char, std::char_traits<char>, Extent>;

    template<std::ptrdiff_t Extent>
    using wstring_span = basic_string_span<wchar_t, std::char_traits<wchar_t>, Extent>;

    template<std::ptrdiff_t Extent>
    using u16string_span = basic_string_span<char16_t, std::char_traits<char16_t>, Extent>;

    template<std::ptrdiff_t Extent>
    using u32string_span = basic_string_span<char32_t, std::char_traits<char32_t>, Extent>;

    //------------------------------------------------------------------------

    template<typename CharT, typename Traits, std::ptrdiff_t Extent>
    class basic_zstring_span;

    template<std::ptrdiff_t Extent>
    using zstring_span = basic_zstring_span<char, std::char_traits<char>,Extent>;

    template<std::ptrdiff_t Extent>
    using wzstring_span = basic_zstring_span<wchar_t, std::char_traits<wchar_t>,Extent>;

    template<std::ptrdiff_t Extent>
    using u16zstring_span = basic_zstring_span<char16_t, std::char_traits<char16_t>,Extent>;

    template<std::ptrdiff_t Extent>
    using u32zstring_span = basic_zstring_span<char32_t, std::char_traits<char32_t>,Extent>;

    //------------------------------------------------------------------------

    namespace detail {

      template<typename T>
      struct is_string_span : std::false_type{};

      template<typename CharT, typename Traits, std::ptrdiff_t Extent>
      struct is_string_span<basic_string_span<CharT,Traits,Extent>> : std::true_type{};

      template<typename CharT, typename Traits, std::ptrdiff_t Extent>
      struct is_string_span<basic_zstring_span<CharT,Traits,Extent>> : std::true_type{};

      template<typename T>
      struct is_zstring_span : std::false_type{};

      template<typename CharT, typename Traits, std::ptrdiff_t Extent>
      struct is_zstring_span<basic_zstring_span<CharT,Traits,Extent>> : std::true_type{};

    } // namespace detail

    /// \brief type-trait to determine whether the type is a string_span
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    using is_string_span = detail::is_string_span<std::remove_cv_t<T>>;

    /// \brief type-trait to determine whether the type is a null-terminated
    ///        string
    ///
    /// The result is aliased as \c ::value
    template<typename T>
    using is_zstring_span = detail::is_zstring_span<std::remove_cv_t<T>>;

    namespace detail {

      template<typename Container, typename Pointer>
      struct string_span_is_string :
        conjunction<
          negation<is_string_span<Container>>,
          is_contiguous_container<Container>,
          std::is_convertible<typename Container::pointer, Pointer>,
          std::is_convertible<typename Container::pointer, decltype(std::declval<Container&>().data())>
        >{};

    } // namespace detail

    //////////////////////////////////////////////////////////////////////////
    /// \brief A light-weight non-owning wrapper around strings.
    ///
    /// \tparam CharT the type of character to wrap around
    /// \tparam Traits the type of traits to use
    /// \tparam Extent The maximum size of this string span (default: unbounded)
    //////////////////////////////////////////////////////////////////////////
    template<
      typename CharT,
      typename Traits = std::char_traits<CharT>,
      std::ptrdiff_t Extent = dynamic_extent
    >
    class basic_string_span
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      static_assert( std::is_same<CharT,typename Traits::char_type>::value, "basic_string_span: char_type is not the same as CharT" );

      using value_type      = CharT;
      using traits_type     = Traits;
      using pointer         = std::add_pointer_t<value_type>;
      using const_pointer   = std::add_pointer_t<std::add_const_t<value_type>>;
      using reference       = std::add_lvalue_reference_t<value_type>;
      using const_reference = std::add_lvalue_reference_t<std::add_const_t<value_type>>;

      using impl_type  = span<CharT,Extent>;
      using size_type  = std::ptrdiff_t;
      using index_type = std::ptrdiff_t;

      using iterator               = tagged_iterator<CharT*,basic_string_span>;
      using const_iterator         = tagged_iterator<const CharT*,basic_string_span>;
      using reverse_iterator       = std::reverse_iterator<iterator>;
      using const_reverse_iterator = std::reverse_iterator<const_iterator>;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs an empty basic_string_span
      constexpr basic_string_span() noexcept = default;

      /// \brief Copy-constructs a basic_string_span from another one
      ///
      /// \param other the other basic_string_span to copy
      constexpr basic_string_span( const basic_string_span& other ) noexcept = default;

      /// \brief Move-constructs a basic_string_span from another one
      ///
      /// \param other the other basic_string_span to move
      constexpr basic_string_span( basic_string_span&& other ) noexcept = default;

      /// \brief Constructs an empty basic_string_span
      ///
      /// \param ptr the nullptr
      constexpr basic_string_span( std::nullptr_t ptr ) noexcept;

      /// \brief Constructs a basic_string_span given a pointer to the string
      ///        and the size
      ///
      /// \param ptr pointer to the string
      /// \param length the length of the string
      constexpr basic_string_span( pointer ptr, size_type length ) noexcept;

      /// \brief Constructs a basic_string_span given a pointer to the start
      ///        and end of the string
      ///
      /// \param first a pointer to the first entry
      /// \param last a pointer to the last entry
      constexpr basic_string_span( pointer first, pointer last ) noexcept;

      /// \brief Constructs a basic_string_span given an array of N characters
      ///
      /// \param arr the array
      template<std::size_t N>
      constexpr basic_string_span( value_type (&arr)[N] ) noexcept;

      /// \brief Constructs a basic_string_span given a contiguous container
      ///        of characters
      ///
      /// \param container the container to use
      template<typename Container, typename = std::enable_if_t<detail::string_span_is_string<Container,pointer>::value>>
      constexpr basic_string_span( Container& container );

      /// \brief Constructs a basic_string_span given a contiguous container
      ///        of characters
      ///
      /// \param container the container to use
      template<typename Container, typename = std::enable_if_t<detail::string_span_is_string<Container,pointer>::value>>
      constexpr basic_string_span( const Container& container );

      /// \brief Constructs a basic_string_span given a basic string
      ///
      /// \param str the string to use
      template<typename OtherTraits, typename Allocator>
      constexpr basic_string_span( const std::basic_string<value_type, OtherTraits, Allocator>& str ) noexcept;

      /// \brief Constructs a basic_string_span given another basic_string_span
      ///
      /// \param span the span to use
      template<typename OtherCharT, std::ptrdiff_t OtherExtent, typename = std::enable_if_t<std::is_convertible<typename basic_string_span<OtherCharT, Traits, OtherExtent>::impl_type, impl_type>::value>>
      constexpr basic_string_span( basic_string_span<OtherCharT,Traits,OtherExtent> span ) noexcept;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Copy-assigns a basic_string_span
      ///
      /// \param other the basic_string_span to copy
      constexpr basic_string_span& operator=( const basic_string_span& other ) noexcept = default;

      /// \brief Move-assigns a basic_string_span
      ///
      /// \param other the basic_string_span to move
      constexpr basic_string_span& operator=( basic_string_span&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Capacity
      //----------------------------------------------------------------------
    public:

      /// \brief Returns the size of the basic_string_span
      ///
      /// \return the number of entries in the basic_string_span
      constexpr size_type length() const noexcept;

      /// \brief Returns the size of the basic_string_span
      ///
      /// \return the number of entries in the basic_string_span
      constexpr size_type size() const noexcept;

      /// \brief Returns the size of the basic_string_span in bytes
      ///
      /// \return the number of bytes in the basic_string_span
      constexpr size_type length_bytes() const noexcept;

      /// \brief Returns the size of the basic_string_span in bytes
      ///
      /// \return the number of bytes in the basic_string_span
      constexpr size_type size_bytes() const noexcept;

      /// \brief Returns whether the basic_string_span is empty
      ///        (i.e. whether its size is 0).
      ///
      /// \return \c true if the basic_string_span is empty
      constexpr bool empty() const noexcept;

      //----------------------------------------------------------------------
      // Element Access
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the data of the current basic_string_span
      ///
      /// \return the data this non-const basic_string_span contains
      constexpr pointer data() noexcept;

      /// \copydoc basic_string_span::data()
      constexpr const_pointer data() const noexcept;

      /// \brief Accesses the element at index \p pos
      ///
      /// \param pos the index to access
      /// \return const reference to the entry
      constexpr reference operator[]( index_type pos ) noexcept;

      /// \copydoc basic_string_span::operator[]( index_type )
      constexpr const_reference operator[]( index_type pos ) const noexcept;

      /// \brief Accesses the element at index \p pos
      ///
      /// \param pos the index to access
      /// \return const reference to the entry
      constexpr reference at( index_type pos );

      /// \copydoc basic_string_span::at( index_type )
      constexpr const_reference at( index_type pos ) const;

      /// \brief Access the first entry of the span
      ///
      /// \note Undefined behavior if span is empty
      ///
      /// \return reference to the first entry of the span
      constexpr reference front() noexcept;

      /// \copydoc basic_string_span::front()
      constexpr const_reference front() const noexcept;

      /// \brief References the last entry of the span
      ///
      /// \note Undefined behavior if span is empty
      ///
      /// \return reference to the last entry of the span
      constexpr reference back() noexcept;

      /// \copydoc basic_string_span::back()
      constexpr const_reference back() const noexcept;

      //----------------------------------------------------------------------
      // Operations
      //----------------------------------------------------------------------
    public:

      /// \brief Returns a subview of this span
      ///
      /// \param offset the position of the first entry in the subview
      /// \param count  the length of the subview
      /// \return the created span subview
      constexpr basic_string_span<CharT,Traits,dynamic_extent> substr( size_type offset, size_type count = dynamic_extent ) const ;

      /// \brief Returns a subview consisting of the first \p n entries
      ///        of the span
      ///
      /// \param n the number of entries from the beginning of the span
      /// \return the created span subview
      constexpr basic_string_span<CharT,Traits,dynamic_extent> first( size_type n ) const;

      /// \brief Returns a subview consisting of the last \p n entries
      ///        of the span
      ///
      /// \param n the number of entries from the end of the span
      /// \return the created span subview
      constexpr basic_string_span<CharT,Traits,dynamic_extent> last( size_type n ) const;

      /// \brief Returns a subview consisting of the last \c size - \p n entries
      ///        of the span
      ///
      /// \param n the number of entries from the beginning of the span
      /// \return the created span subview
      constexpr basic_string_span<CharT,Traits,dynamic_extent> remove_prefix( size_type n ) const;

      /// \brief Returns a subview consisting of the first \c size - \p n entries
      ///        of the span
      ///
      /// \param n the number of entries from the end of the span
      /// \return the created span subview
      constexpr basic_string_span<CharT,Traits,dynamic_extent> remove_suffix( size_type n ) const;

      //----------------------------------------------------------------------
      // Iterators
      //----------------------------------------------------------------------
    public:

      /// \brief Retrieves the begin iterator for this basic_string_span
      ///
      /// \return the begin iterator
      constexpr iterator begin() const noexcept;

      /// \brief Retrieves the end iterator for this basic_string_span
      ///
      /// \return the end iterator
      constexpr iterator end() const noexcept;

      /// \copydoc basic_string_span::begin()
      constexpr const_iterator cbegin() const noexcept;

      /// \copydoc basic_string_span::end()
      constexpr const_iterator cend() const noexcept;

      //----------------------------------------------------------------------

      /// \brief Retrieves the reverse begin iterator for this basic_string_span
      ///
      /// \return the reverse begin iterator
      constexpr reverse_iterator rbegin() const noexcept;

      /// \brief Retrieves the reverse end iterator for this basic_string_span
      ///
      /// \return the reverse end iterator
      constexpr reverse_iterator rend() const noexcept;

      /// \copydoc basic_string_span::rbegin()
      constexpr const_reverse_iterator crbegin() const noexcept;

      /// \brief basic_string_span::rend()
      constexpr const_reverse_iterator crend() const noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      impl_type m_span; ///< The internal span being used

    };

    //------------------------------------------------------------------------

    //////////////////////////////////////////////////////////////////////////
    /// \brief A light-weight non-owning wrapper around strings.
    ///
    /// This is just a limited API of the basic_string_span
    ///
    /// \tparam CharT the type of character to wrap around
    /// \tparam Traits the type of traits to use
    /// \tparam Extent The maximum size of this string span (default: unbounded)
    //////////////////////////////////////////////////////////////////////////
    template<
      typename CharT,
      typename Traits = std::char_traits<CharT>,
      std::ptrdiff_t Extent = dynamic_extent
    >
    class basic_zstring_span : public basic_string_span<CharT,Traits,Extent>
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using typename basic_string_span<CharT,Traits,Extent>::value_type;
      using typename basic_string_span<CharT,Traits,Extent>::traits_type;
      using typename basic_string_span<CharT,Traits,Extent>::size_type;
      using typename basic_string_span<CharT,Traits,Extent>::index_type;

      using typename basic_string_span<CharT,Traits,Extent>::pointer;
      using typename basic_string_span<CharT,Traits,Extent>::const_pointer;
      using typename basic_string_span<CharT,Traits,Extent>::reference;
      using typename basic_string_span<CharT,Traits,Extent>::const_reference;

      using typename basic_string_span<CharT,Traits,Extent>::const_iterator;
      using typename basic_string_span<CharT,Traits,Extent>::iterator;
      using typename basic_string_span<CharT,Traits,Extent>::const_reverse_iterator;
      using typename basic_string_span<CharT,Traits,Extent>::reverse_iterator;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a string_span from null-terminated string
      ///
      /// \param str the null-terminated string
      constexpr basic_zstring_span( value_type* str ) noexcept;

      /// \brief Copy-constructs a basic_zstring_span from another one
      ///
      /// \param other the other basic_zstring_span to copy
      constexpr basic_zstring_span( const basic_zstring_span& other ) noexcept = default;

      /// \brief Move-constructs a basic_zstring_span from another one
      ///
      /// \param other the other basic_zstring_span to move
      constexpr basic_zstring_span( basic_zstring_span&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Assignment
      //----------------------------------------------------------------------
    public:

      /// \brief Copy-assigns a basic_zstring_span
      ///
      /// \param other the basic_string_span to copy
      constexpr basic_zstring_span& operator=( const basic_zstring_span& other ) noexcept = default;

      /// \brief Move-assigns a basic_zstring_span
      ///
      /// \param other the basic_string_span to move
      constexpr basic_zstring_span& operator=( basic_zstring_span&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Element Access
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the data of the current basic_zstring_span
      ///
      /// \return pointer to the null-terminated string
      constexpr const_pointer c_str() const noexcept;

    };
  } // namespace stl
} // namespace bit

#include "detail/string_span.inl"

#endif /* BIT_STL_CONTAINERS_STRING_SPAN_HPP */
