#pragma once

#include "terminalpp/element.hpp"

#include <boost/container_hash/hash.hpp>

#include <algorithm>
#include <concepts>  // IWYU pragma: keep
#include <initializer_list>
#include <string>
#include <vector>
#include <cstddef>

namespace terminalpp {

//* =========================================================================
/// \brief A class that represents strings of elements.
/// \par
/// Note: models an STL container.
//* =========================================================================
class TERMINALPP_EXPORT string
{
    using elements_storage = std::vector<element>;

public:
    //* =====================================================================
    /// Container Typedefs
    //* =====================================================================
    using value_type = element;
    using reference = value_type &;
    using const_reference = value_type const &;
    using pointer = element *;
    using const_pointer = element const *;
    using iterator = elements_storage::iterator;
    using const_iterator = elements_storage::const_iterator;
    using reverse_iterator = elements_storage::reverse_iterator;
    using const_reverse_iterator = elements_storage::const_reverse_iterator;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;

    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    constexpr string() = default;

    //* =====================================================================
    /// \brief Range Constructor
    //* =====================================================================
    template <std::forward_iterator ForwardIterator>
    constexpr string(ForwardIterator &&begin, ForwardIterator &&end)
      : elements_{begin, end}
    {
    }

    //* =====================================================================
    /// \brief Initializer List Constructor
    //* =====================================================================
    constexpr string(std::initializer_list<element> const &ilist)
      : string{ilist.begin(), ilist.end()}
    {
    }

    //* =====================================================================
    /// \brief Constructor
    /// \param text the text to build this string around.
    /// Results in a string with the passed text, with all attributes
    /// their default values.
    //* =====================================================================
    constexpr string(char const *text)  // NOLINT
      : string{text, std::char_traits<char>::length(text)}
    {
    }

    //* =====================================================================
    /// \brief Constructor
    /// \param text the text to build this string around.
    /// \param len the length of text.
    /// Results in a string of length len with the passed text, with all
    /// attributes their default values.
    //* =====================================================================
    constexpr string(char const *text, size_type len)
      : elements_{text, text + len}
    {
    }

    //* =====================================================================
    /// \brief Constructor
    /// \param text the text to build this string around
    /// Results in a string with the passed text, with all attributes
    /// their default values.
    //* =====================================================================
    constexpr string(std::string const &text)  // NOLINT
      : string{text.data(), text.size()}
    {
    }

    //* =====================================================================
    /// \brief Constructor
    /// \param text the text to build this string around.
    /// \param attr the attribute to apply to each new element of the string.
    //* =====================================================================
    constexpr string(std::string const &text, terminalpp::attribute const &attr)
      : string{text}
    {
        std::ranges::for_each(
            elements_, [&attr](auto &elem) { elem.attribute_ = attr; });
    }

    //* =====================================================================
    /// \brief Construct a string of a number of identical elements.
    /// \param size the size of the string to construct.
    /// \param elem a prototype element to fill the string with
    //* =====================================================================
    constexpr string(size_type size, terminalpp::element const &elem)
      : elements_(size, elem)
    {
    }

    //* =====================================================================
    /// \brief Returns the number of elements in the string.
    //* =====================================================================
    [[nodiscard]] constexpr size_type size() const noexcept
    {
        return elements_.size();
    }

    //* =====================================================================
    /// \brief Returns an iterator to the beginning of the string.
    //* =====================================================================
    [[nodiscard]] constexpr iterator begin() noexcept
    {
        return elements_.begin();
    }

    //* =====================================================================
    /// \brief Returns an iterator to the beginning of the string.
    //* =====================================================================
    [[nodiscard]] constexpr const_iterator begin() const noexcept
    {
        return elements_.begin();
    }

    //* =====================================================================
    /// \brief Returns a reverse iterator to the reverse beginning of the
    /// string.
    //* =====================================================================
    [[nodiscard]] constexpr reverse_iterator rbegin() noexcept
    {
        return elements_.rbegin();
    }

    //* =====================================================================
    /// \brief Returns a reverse iterator to the reverse beginning of the
    /// string.
    //* =====================================================================
    [[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept
    {
        return elements_.rbegin();
    }

    //* =====================================================================
    /// \brief Returns an iterator to the end of the string.
    //* =====================================================================
    [[nodiscard]] constexpr iterator end() noexcept
    {
        return elements_.end();
    }

    //* =====================================================================
    /// \brief Returns an iterator to the end of the string.
    //* =====================================================================
    [[nodiscard]] constexpr const_iterator end() const noexcept
    {
        return elements_.end();
    }

    //* =====================================================================
    /// \brief Returns a reverse iterator to the reverse end of the string
    //* =====================================================================
    [[nodiscard]] constexpr reverse_iterator rend() noexcept
    {
        return elements_.rend();
    }

    //* =====================================================================
    /// \brief Returns a reverse iterator to the reverse end of the string
    //* =====================================================================
    [[nodiscard]] constexpr const_reverse_iterator rend() const noexcept
    {
        return elements_.rend();
    }

    //* =====================================================================
    /// \brief Returns an iterator to the beginning of the string.
    //* =====================================================================
    [[nodiscard]] constexpr const_iterator cbegin() noexcept
    {
        return elements_.cbegin();
    }

    //* =====================================================================
    /// \brief Returns an iterator to the end of the string.
    //* =====================================================================
    [[nodiscard]] constexpr const_iterator cend() noexcept
    {
        return elements_.cend();
    }

    //* =====================================================================
    /// \brief Swaps the contents of this and another string.
    //* =====================================================================
    constexpr void swap(string &other) noexcept
    {
        std::swap(elements_, other.elements_);
    }

    //* =====================================================================
    /// \brief Returns the maximum size of the string allowed.
    //* =====================================================================
    [[nodiscard]] constexpr size_type max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max();
    }

    //* =====================================================================
    /// \brief Returns whether the string is empty or not.
    //* =====================================================================
    [[nodiscard]] constexpr bool empty() const noexcept
    {
        return elements_.empty();
    }

    //* =====================================================================
    /// \brief Array access operator
    //* =====================================================================
    [[nodiscard]] constexpr reference operator[](size_type index) noexcept
    {
        return elements_[index];
    }

    //* =====================================================================
    /// \brief Array access operator
    //* =====================================================================
    [[nodiscard]] constexpr const_reference operator[](
        size_type index) const noexcept
    {
        return elements_[index];
    }

    //* =====================================================================
    /// \brief Append operator
    //* =====================================================================
    constexpr string &operator+=(element const &elem)
    {
        elements_.insert(elements_.end(), elem);
        return *this;
    }

    //* =====================================================================
    /// \brief Append operator
    //* =====================================================================
    [[nodiscard]] friend string operator+(string lhs, element const &rhs)
    {
        return lhs += rhs;
    }

    //* =====================================================================
    /// \brief Append operator
    //* =====================================================================
    constexpr string &operator+=(string const &rhs)
    {
        elements_.insert(elements_.end(), rhs.begin(), rhs.end());
        return *this;
    }

    //* =====================================================================
    /// \brief Append operator
    //* =====================================================================
    [[nodiscard]] friend string operator+(string lhs, string const &rhs)
    {
        return lhs += rhs;
    }

    //* =====================================================================
    /// \brief Inserts an element at the iterator position.
    //* =====================================================================
    constexpr void insert(iterator pos, element const &elem)
    {
        elements_.insert(pos, elem);
    }

    //* =====================================================================
    /// \brief Inserts a range of elements at the iterator position.
    //* =====================================================================
    template <class InputIterator>
    constexpr void insert(
        iterator pos, InputIterator range_begin, InputIterator range_end)
    {
        elements_.insert(pos, range_begin, range_end);
    }

    //* =====================================================================
    /// \brief Erase
    //* =====================================================================
    constexpr void erase()
    {
        elements_.clear();
    }

    //* =====================================================================
    /// \brief Erase
    //* =====================================================================
    constexpr void erase(iterator range_begin)
    {
        elements_.erase(range_begin, elements_.end());
    }

    //* =====================================================================
    /// \brief Erase
    //* =====================================================================
    constexpr void erase(iterator range_begin, iterator range_end)
    {
        elements_.erase(range_begin, range_end);
    }

    //* =====================================================================
    /// \brief Relational operators for strings
    //* =====================================================================
    [[nodiscard]] constexpr friend auto operator<=>(
        string const &lhs, string const &rhs) noexcept = default;

    //* =====================================================================
    /// \brief Equality operator
    //* =====================================================================
    TERMINALPP_EXPORT
    constexpr friend bool operator==(
        string const &lhs, string const &rhs) noexcept = default;

    //* =====================================================================
    /// \brief Hash function
    //* =====================================================================
    [[nodiscard]] friend std::size_t hash_value(string const &str) noexcept
    {
        return boost::hash_range(str.elements_.begin(), str.elements_.end());
    }

private:
    elements_storage elements_;
};

//* =========================================================================
/// \brief Streaming output operator for strings.  Prints the text out
/// element by element so that it is readable.  Note: NOT rendered as if
/// to a terminal.
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, string const &text);

//* =========================================================================
/// \brief Convert a terminalpp::string to a std::string by removing all
/// attributes and charset information.
//* =========================================================================
TERMINALPP_EXPORT
[[nodiscard]] constexpr ::std::string to_string(terminalpp::string const &tstr)
{
    std::string result;

    for (auto const &elem : tstr)
    {
        if (elem.glyph_.charset_ == charset::utf8)
        {
            for (auto const &ch : elem.glyph_.ucharacter_)
            {
                if (ch == 0)
                {
                    break;
                }

                result += static_cast<char>(ch);
            }
        }
        else
        {
            result += static_cast<char>(elem.glyph_.character_);
        }
    }

    return result;
}

//* =========================================================================
/// \brief A function that converts a std::string into a terminalpp::string,
/// parsing its contents according to the String To Elements protocol.
//* =========================================================================
TERMINALPP_EXPORT
constexpr terminalpp::string encode(std::span<char const> text)
{
    string result;
    element prev_element;

    while (!text.empty())
    {
        result += detail::parse_element(text, prev_element);
        prev_element = *result.rbegin();
    }

    return result;
}

inline namespace literals {
inline namespace string_literals {

//* =========================================================================
/// \brief Construct an string from literals using "foo"_ts;
//* =========================================================================
TERMINALPP_EXPORT
[[nodiscard]] constexpr ::terminalpp::string operator""_ts(
    char const *text, ::terminalpp::string::size_type length)
{
    return {text, length};
}

//* =========================================================================
/// \brief Construct an encoded string from literals using "foo"_ets;
//* =========================================================================
TERMINALPP_EXPORT
[[nodiscard]] constexpr ::terminalpp::string operator""_ets(
    char const *text, ::terminalpp::string::size_type length)
{
    return encode(std::span{text, length});
}

}  // namespace string_literals
}  // namespace literals
}  // namespace terminalpp

namespace std {

template <>
struct hash<terminalpp::string>
{
    using argument_type = terminalpp::string;
    using result_type = std::size_t;

    [[nodiscard]] result_type operator()(
        argument_type const &str) const noexcept
    {
        return hash_value(str);
    }
};

}  // namespace std