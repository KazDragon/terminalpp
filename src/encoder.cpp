#include "terminalpp/encoder.hpp"

namespace terminalpp {

// ==========================================================================
// ENCODE
// ==========================================================================
terminalpp::string encode(gsl::cstring_span text)
{
    string result;

    while (element prev_element; !text.empty())
    {
        result += detail::parse_element(text, prev_element);
        prev_element = *result.rbegin();
    }

    return result;
}

}
