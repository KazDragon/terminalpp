#ifndef TERMINALPP_STRING_HPP_
#define TERMINALPP_STRING_HPP_

#include "terminalpp/element.hpp"
#include <cstddef>
#include <string>
#include <vector>

namespace terminalpp {

//* =========================================================================
/// \brief A class that represents strings of elements.
/// \par
/// Note: models an STL container.
//* =========================================================================
class string
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
    typedef element const    *const_reverse_iterator;
    typedef std::ptrdiff_t    difference_type;
    typedef std::size_t       size_type;

    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    string() = default;

    //* =====================================================================
    /// \brief Constructor
    /// \param text the text to build this string around.
    /// \param raw if false, then text is parsed for attribute codes.
    ///        otherwise, no parsing takes place and the string is consumed
    ///        whole as an unattributed string.
    //* =====================================================================
    string(char const *text, bool raw = false);

    //* =====================================================================
    /// \brief Constructor
    /// \param text the text to build this string around.
    /// \param len the length of text.
    /// \param raw if false, then text is parsed for attribute codes.
    ///        otherwise, no parsing takes place and the string is consumed
    ///        whole as an unattributed string.
    //* =====================================================================
    string(char const *text, std::size_t len, bool raw = false);

    //* =====================================================================
    /// \brief Constructor
    /// \param text the text to build this string around
    /// \param raw if false, then text is parsed for attribute codes.
    ///        otherwise, no parsing takes place and the string is consumed
    ///        whole as an unattributed string.
    //* =====================================================================
    string(std::string const &text, bool raw = false);

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
    string &operator+=(string const &rhs);

    //* =====================================================================
    /// \brief Equality operator
    //* =====================================================================
    friend bool operator==(string const &lhs, string const &rhs);

    //* =====================================================================
    /// \brief Inequality operator
    //* =====================================================================
    friend bool operator!=(string const &lhs, string const &rhs);

    //* =====================================================================
    /// \brief Streaming operator
    //* =====================================================================
    friend std::ostream &operator<<(std::ostream &out, string const &es);

private :
    std::vector<element> elements_;
};

//* =========================================================================
/// \brief Concatenation
//* =========================================================================
::terminalpp::string operator+(string lhs, string const &rhs);

inline namespace literals { inline namespace string_literals {

//* =========================================================================
/// \brief Construct an string from literals using "foo"_es;
//* =========================================================================
::terminalpp::string operator ""_s(
    char const *text,
    std::size_t length);

}}}

#endif
