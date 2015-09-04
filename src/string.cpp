#include "terminalpp/string.hpp"
#include "terminalpp/element.hpp"
#include "terminalpp/detail/element_difference.hpp"
#include "terminalpp/detail/string_to_elements.hpp"
#include <cstring>
#include <limits>

namespace terminalpp {

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
string::string(const char* text)
  : string(text, strlen(text))
{
}

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
string::string(const char* text, std::size_t len)
  : elements_(text, text + len)
{
}

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
string::string(const std::string& text)
  : string(text.c_str(), text.size())
{
}

// ==========================================================================
// SIZE
// ==========================================================================
std::size_t string::size() const
{
    return elements_.size();
}

// ==========================================================================
// BEGIN
// ==========================================================================
string::const_iterator string::begin() const
{
    return &*elements_.begin();
}

// ==========================================================================
// BEGIN
// ==========================================================================
string::iterator string::begin()
{
    return &*elements_.begin();
}

// ==========================================================================
// RBEGIN
// ==========================================================================
string::const_reverse_iterator string::rbegin() const
{
    return &*elements_.rbegin();
}

// ==========================================================================
// END
// ==========================================================================
string::const_iterator string::end() const
{
    return &*elements_.end();
}

// ==========================================================================
// END
// ==========================================================================
string::iterator string::end()
{
    return &*elements_.end();
}

// ==========================================================================
// REND
// ==========================================================================
string::const_reverse_iterator string::rend() const
{
    return &*elements_.rend();
}

// ==========================================================================
// MAX_SIZE
// ==========================================================================
string::size_type string::max_size() const
{
    return std::numeric_limits<size_type>::max();
}

// ==========================================================================
// EMPTY
// ==========================================================================
bool string::empty() const
{
    return elements_.empty();
}

// ==========================================================================
// OPERATOR []
// ==========================================================================
string::reference string::operator[](string::size_type index)
{
    return elements_[index];
}

// ==========================================================================
// OPERATOR []
// ==========================================================================
string::const_reference string::operator[](string::size_type index) const
{
    return elements_[index];
}

// ==========================================================================
// OPERATOR +=
// ==========================================================================
string &string::operator+=(char ch)
{
    return operator+=(element(ch));
}

// ==========================================================================
// OPERATOR +=
// ==========================================================================
string &string::operator+=(element const &elem)
{
    elements_.insert(elements_.end(), elem);
    return *this;
}

// ==========================================================================
// OPERATOR +=
// ==========================================================================
string &string::operator+=(string const &rhs)
{
    elements_.insert(elements_.end(), rhs.begin(), rhs.end());
    return *this;
}

// ==========================================================================
// OPERATOR ==
// ==========================================================================
bool operator==(string const &lhs, string const &rhs)
{
    return lhs.elements_ == rhs.elements_;
}

// ==========================================================================
// OPERATOR !=
// ==========================================================================
bool operator!=(string const &lhs, string const &rhs)
{
    return !(lhs == rhs);
}

// ==========================================================================
// OPERATOR <<
// ==========================================================================
std::ostream &operator<<(std::ostream &out, string const &es)
{
    std::string text;
    element current_element;

    for (auto const &elem : es.elements_)
    {
        text += detail::element_difference(current_element, elem);

        if (elem.glyph_.charset_ == terminalpp::ansi::charset::utf8)
        {
            for (size_t index = 0; 
                 index < sizeof(elem.glyph_.ucharacter_)
              && elem.glyph_.ucharacter_[index] != '\0'; 
                 ++index)
            {
                text += elem.glyph_.ucharacter_[index];

                if (!(elem.glyph_.ucharacter_[index] & 0x80))
                {
                    break;
                }
            }
        }
        else
        {
            text += elem.glyph_.character_;
        }

        current_element = elem;
    }

    text += detail::element_difference(current_element, {});

    out << text;
    return out;
}

// ==========================================================================
// OPERATOR +
// ==========================================================================
string operator+(string lhs, char rhs)
{
    return lhs += rhs;
}

// ==========================================================================
// OPERATOR +
// ==========================================================================
string operator+(string lhs, element const &rhs)
{
    return lhs += rhs;
}

// ==========================================================================
// OPERATOR +
// ==========================================================================
string operator+(string lhs, string const &rhs)
{
    return lhs += rhs;
}

inline namespace literals { inline namespace string_literals {

terminalpp::string operator ""_ts(char const *text, std::size_t len)
{
    return terminalpp::string(text, len);
}

}}}
