#include "terminalpp/encoder.hpp"

namespace terminalpp {

// ==========================================================================
// ENCODE
// ==========================================================================
terminalpp::string encode(std::string const &text)
{
    return encode(text.c_str(), text.size());
}

//* =========================================================================
/// \brief A function that converts a char* into a terminalpp::string,
/// parsing its contents according to the String To Elements protocol.
//* =========================================================================
terminalpp::string encode(char const *text)
{
    return encode(text, strlen(text));
}

//* =========================================================================
/// \brief A function that converts a char* of a given length into a
/// terminalpp::string, parsing its contents according to the String To
/// Elements protocol.
//* =========================================================================
terminalpp::string encode(char const *text, size_t length)
{
    gsl::cstring_span text_span(text, length);

    string result;
    element prev_element;

    while (!text_span.empty())
    {
        result += detail::parse_element(text_span, prev_element);
        prev_element = *result.rbegin();
    }

    return result;
}

}
