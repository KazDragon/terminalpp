#include "terminalpp/string.hpp"
#include "terminalpp/element.hpp"
#include "terminalpp/encoder.hpp"
#include <algorithm>
#include <cstring>
#include <limits>

namespace terminalpp {

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
string::string(std::initializer_list<element> const &ilist)
  : string(ilist.begin(), ilist.end())
{
}

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
// CONSTRUCTOR
// ==========================================================================
string::string(std::string const &text, terminalpp::attribute const &attr)
 : string(text)
{
    std::for_each(elements_.begin(), elements_.end(),
    [&attr](auto &elem)
    {
        elem.attribute_ = attr;
    });
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

// ==========================================================================
// TO_STRING
// ==========================================================================
std::string to_string(string const &tstr)
{
    std::string result;

    for(auto const &elem : tstr)
    {
        if (elem.glyph_.charset_ == ansi::charset::utf8)
        {
            for (auto const &ch : elem.glyph_.ucharacter_)
            {
                if (ch == 0)
                {
                    break;
                }

                result += ch;
            }
        }
        else
        {
            result += elem.glyph_.character_;
        }
    }

    return result;
}

inline namespace literals { inline namespace string_literals {

// ==========================================================================
// OPERATOR""_ts
// ==========================================================================
terminalpp::string operator ""_ts(char const *text, std::size_t len)
{
    return terminalpp::string(text, len);
}

// ==========================================================================
// OPERATOR""_ets
// ==========================================================================
terminalpp::string operator ""_ets(char const *text, std::size_t len)
{
    return terminalpp::encode(text, len);
}

}}}
