#pragma once

#include "terminalpp/element.hpp"

#include <boost/container_hash/hash.hpp>
#include <boost/operators.hpp>

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
  : private boost::addable<
        string,
        boost::addable<
            string,
            byte,
            boost::addable<
                string,
                element,
                boost::less_than_comparable<
                    string,
                    boost::equality_comparable<string>>>>>
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
    string() = default;

    //* =====================================================================
    /// \brief Range Constructor
    //* =====================================================================
    template <class ForwardIterator>
    string(ForwardIterator &&begin, ForwardIterator &&end)
      : elements_(begin, end)
    {
    }

    //* =====================================================================
    /// \brief Initializer List Constructor
    //* =====================================================================
    string(std::initializer_list<element> const &ilist);

    //* =====================================================================
    /// \brief Constructor
    /// \param text the text to build this string around.
    /// Results in a string with the passed text, with all attributes
    /// their default values.
    //* =====================================================================
    string(char const *text);  // NOLINT

    //* =====================================================================
    /// \brief Constructor
    /// \param text the text to build this string around.
    /// \param len the length of text.
    /// Results in a string of length len with the passed text, with all
    /// attributes their default values.
    //* =====================================================================
    string(char const *text, size_type len);

    //* =====================================================================
    /// \brief Constructor
    /// \param text the text to build this string around
    /// Results in a string with the passed text, with all attributes
    /// their default values.
    //* =====================================================================
    string(std::string const &text);  // NOLINT

    //* =====================================================================
    /// \brief Constructor
    /// \param text the text to build this string around.
    /// \param attr the attribute to apply to each new element of the string.
    //* =====================================================================
    string(std::string const &text, terminalpp::attribute const &attr);

    //* =====================================================================
    /// \brief Construct a string of a number of identical elements.
    /// \param size the size of the string to construct.
    /// \param elem a prototype element to fill the string with
    //* =====================================================================
    string(size_type size, terminalpp::element const &elem);

    //* =====================================================================
    /// \brief Returns the number of elements in the string.
    //* =====================================================================
    [[nodiscard]] size_type size() const;

    //* =====================================================================
    /// \brief Returns an iterator to the beginning of the string.
    //* =====================================================================
    [[nodiscard]] iterator begin();

    //* =====================================================================
    /// \brief Returns an iterator to the beginning of the string.
    //* =====================================================================
    [[nodiscard]] const_iterator begin() const;

    //* =====================================================================
    /// \brief Returns a reverse iterator to the reverse beginning of the
    /// string.
    //* =====================================================================
    [[nodiscard]] reverse_iterator rbegin();

    //* =====================================================================
    /// \brief Returns a reverse iterator to the reverse beginning of the
    /// string.
    //* =====================================================================
    [[nodiscard]] const_reverse_iterator rbegin() const;

    //* =====================================================================
    /// \brief Returns an iterator to the end of the string.
    //* =====================================================================
    [[nodiscard]] iterator end();

    //* =====================================================================
    /// \brief Returns an iterator to the end of the string.
    //* =====================================================================
    [[nodiscard]] const_iterator end() const;

    //* =====================================================================
    /// \brief Returns a reverse iterator to the reverse end of the string
    //* =====================================================================
    [[nodiscard]] reverse_iterator rend();

    //* =====================================================================
    /// \brief Returns a reverse iterator to the reverse end of the string
    //* =====================================================================
    [[nodiscard]] const_reverse_iterator rend() const;

    //* =====================================================================
    /// \brief Returns an iterator to the beginning of the string.
    //* =====================================================================
    [[nodiscard]] const_iterator cbegin();

    //* =====================================================================
    /// \brief Returns an iterator to the end of the string.
    //* =====================================================================
    [[nodiscard]] const_iterator cend();

    //* =====================================================================
    /// \brief Swaps the contents of this and another string.
    //* =====================================================================
    void swap(string &other) noexcept;

    //* =====================================================================
    /// \brief Returns the maximum size of the string allowed.
    //* =====================================================================
    [[nodiscard]] size_type max_size() const;

    //* =====================================================================
    /// \brief Returns whether the string is empty or not.
    //* =====================================================================
    [[nodiscard]] bool empty() const;

    //* =====================================================================
    /// \brief Array access operator
    //* =====================================================================
    reference operator[](size_type index);

    //* =====================================================================
    /// \brief Array access operator
    //* =====================================================================
    const_reference operator[](size_type index) const;

    //* =====================================================================
    /// \brief Append operator
    //* =====================================================================
    string &operator+=(element const &elem);

    //* =====================================================================
    /// \brief Append operator
    //* =====================================================================
    string &operator+=(string const &rhs);

    //* =====================================================================
    /// \brief Inserts an element at the iterator position.
    //* =====================================================================
    void insert(iterator pos, element const &elem);

    //* =====================================================================
    /// \brief Inserts a range of elements at the iterator position.
    //* =====================================================================
    template <class InputIterator>
    void insert(
        iterator pos, InputIterator range_begin, InputIterator range_end)
    {
        elements_.insert(pos, range_begin, range_end);
    }

    //* =====================================================================
    /// \brief Erase
    //* =====================================================================
    void erase();

    //* =====================================================================
    /// \brief Erase
    //* =====================================================================
    void erase(iterator range_begin);

    //* =====================================================================
    /// \brief Erase
    //* =====================================================================
    void erase(iterator range_begin, iterator range_end);

    //* =====================================================================
    /// \brief Less-than operator
    //* =====================================================================
    TERMINALPP_EXPORT
    friend bool operator<(string const &lhs, string const &rhs);

    //* =====================================================================
    /// \brief Equality operator
    //* =====================================================================
    TERMINALPP_EXPORT
    friend bool operator==(string const &lhs, string const &rhs);

    //* =====================================================================
    /// \brief Hash function
    //* =====================================================================
    friend std::size_t hash_value(string const &str) noexcept
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
::std::string to_string(terminalpp::string const &tstr);

inline namespace literals {
inline namespace string_literals {

//* =========================================================================
/// \brief Construct an string from literals using "foo"_ts;
//* =========================================================================
TERMINALPP_EXPORT
::terminalpp::string operator""_ts(
    char const *text, ::terminalpp::string::size_type length);

//* =========================================================================
/// \brief Construct an encoded string from literals using "foo"_ets;
//* =========================================================================
TERMINALPP_EXPORT
::terminalpp::string operator""_ets(
    char const *text, ::terminalpp::string::size_type length);

}  // namespace string_literals
}  // namespace literals
}  // namespace terminalpp

namespace std {

template <>
struct hash<terminalpp::string>
{
    using argument_type = terminalpp::string;
    using result_type = std::size_t;

    result_type operator()(argument_type const &str) const noexcept
    {
        return hash_value(str);
    }
};

}  // namespace std