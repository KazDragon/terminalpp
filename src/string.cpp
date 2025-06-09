#include "terminalpp/string.hpp"

#include "terminalpp/element.hpp"
#include "terminalpp/encoder.hpp"

#include <cstring>

namespace terminalpp {

// ==========================================================================
// OPERATOR <<
// ==========================================================================
std::ostream &operator<<(std::ostream &out, string const &text)
{
    bool add_comma = false;

    for (auto const &elem : text)
    {
        if (add_comma)
        {
            out << ",";
        }

        out << "element[" << elem << "]";

        add_comma = true;
    }

    return out;
}

inline namespace literals {
inline namespace string_literals {

// ==========================================================================
// OPERATOR""_ets
// ==========================================================================
string operator""_ets(char const *text, string::size_type len)
{
    return encode(std::span{text, len});
}

}  // namespace string_literals
}  // namespace literals
}  // namespace terminalpp
