#pragma once

#include "terminalpp/element.hpp"
#include <cstddef>
#include <initializer_list>
#include <string>
#include <vector>

namespace terminalpp {

//* =========================================================================
/// \brief A class that represents strings of elements.
/// \par
/// Note: models an STL container.
//* =========================================================================
class TERMINALPP_EXPORT string
{
public :
    //* =====================================================================
    /// Container Typedefs
    //* =====================================================================
    typedef element           value_type;
    typedef value_type       &reference;
    typedef value_type const &const_reference;
    typedef element          *pointer;
    typedef element const    *const_pointer;
    typedef element          *iterator;
    typedef element const    *const_iterator;
    typedef element          *reverse_iterator;
    typedef element const    *const_reverse_iterator;
    typedef std::ptrdiff_t    difference_type;
    typedef std::size_t       size_type;

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
    string(char const *text);

    //* =====================================================================
    /// \brief Constructor
    /// \param text the text to build this string around.
    /// \param len the length of text.
    /// Results in a string of length len with the passed text, with all
    /// attributes their default values.
    //* =====================================================================
    string(char const *text, std::size_t len);

    //* =====================================================================
    /// \brief Constructor
    /// \param text the text to build this string around
    /// Results in a string with the passed text, with all attributes
    /// their default values.
    //* =====================================================================
    string(std::string const &text);

    //* =====================================================================
    /// \brief Constructor
    /// \param text the text to build this string around.
    /// \param attr the attribute to apply to each new element of the string.
    //* =====================================================================
    string(std::string const &text, terminalpp::attribute const &attr);

    //* =====================================================================
    /// \brief Returns the number of elements in the string.
    //* =====================================================================
    std::size_t size() const;

    //* =====================================================================
    /// \brief Returns an iterator to the beginning of the string.
    //* =====================================================================
    iterator begin();

    //* =====================================================================
    /// \brief Returns an iterator to the beginning of the string.
    //* =====================================================================
    const_iterator begin() const;

    //* =====================================================================
    /// \brief Returns a reverse iterator to the reverse beginning of the
    /// string.
    //* =====================================================================
    reverse_iterator rbegin();

    //* =====================================================================
    /// \brief Returns a reverse iterator to the reverse beginning of the
    /// string.
    //* =====================================================================
    const_reverse_iterator rbegin() const;

    //* =====================================================================
    /// \brief Returns an iterator to the end of the string.
    //* =====================================================================
    iterator end();

    //* =====================================================================
    /// \brief Returns an iterator to the end of the string.
    //* =====================================================================
    const_iterator end() const;

    //* =====================================================================
    /// \brief Returns a reverse iterator to the reverse end of the string
    //* =====================================================================
    reverse_iterator rend();

    //* =====================================================================
    /// \brief Returns a reverse iterator to the reverse end of the string
    //* =====================================================================
    const_reverse_iterator rend() const;

    //* =====================================================================
    /// \brief Returns an iterator to the beginning of the string.
    //* =====================================================================
    const_iterator cbegin();

    //* =====================================================================
    /// \brief Returns an iterator to the end of the string.
    //* =====================================================================
    const_iterator cend();

    //* =====================================================================
    /// \brief Swaps the contents of this and another string.
    //* =====================================================================
    void swap(string &other);

    //* =====================================================================
    /// \brief Returns the maximum size of the string allowed.
    //* =====================================================================
    size_type max_size() const;

    //* =====================================================================
    /// \brief Returns whether the string is empty or not.
    //* =====================================================================
    bool empty() const;

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
    string &operator+=(char ch);

    //* =====================================================================
    /// \brief Append operator
    //* =====================================================================
    string &operator+=(element const &elem);

    //* =====================================================================
    /// \brief Append operator
    //* =====================================================================
    string &operator+=(string const &rhs);

    //* =====================================================================
    /// \brief Equality operator
    //* =====================================================================
    TERMINALPP_EXPORT
    friend bool operator==(string const &lhs, string const &rhs);

    //* =====================================================================
    /// \brief Inequality operator
    //* =====================================================================
    TERMINALPP_EXPORT
    friend bool operator!=(string const &lhs, string const &rhs);

private :
    std::vector<element> elements_;
};

//* =========================================================================
/// \brief Concatenation
//* =========================================================================
TERMINALPP_EXPORT
::terminalpp::string operator+(string lhs, string const &rhs);

//* =========================================================================
/// \brief Concatenation
//* =========================================================================
TERMINALPP_EXPORT
::terminalpp::string operator+(string lhs, char rhs);

//* =========================================================================
/// \brief Concatenation
//* =========================================================================
TERMINALPP_EXPORT
::terminalpp::string operator+(string lhs, element const &rhs);

//* =========================================================================
/// \brief Convert a terminalpp::string to a std::string by removing all
/// attributes and charset information.
//* =========================================================================
TERMINALPP_EXPORT
::std::string to_string(terminalpp::string const &tstr);

inline namespace literals { inline namespace string_literals {

//* =========================================================================
/// \brief Construct an string from literals using "foo"_ts;
//* =========================================================================
TERMINALPP_EXPORT
::terminalpp::string operator ""_ts(
    char const *text,
    std::size_t length);

//* =========================================================================
/// \brief Construct an encoded string from literals using "foo"_ets;
//* =========================================================================
TERMINALPP_EXPORT
::terminalpp::string operator ""_ets(
    char const *text,
    std::size_t length);

}}}
