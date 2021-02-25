#include "terminalpp/ansi/charset.hpp"
#include <algorithm>
#include <cstring>
#include <utility>

namespace terminalpp { namespace ansi {

// TODO: reinstate this code when it becomes necessary.
#if 0
// Locale/Locale Code Conversion

//* =========================================================================
/// \brief Convert a character set to its respective ANSI code.
/// E.g. charset_to_string(charset::portuguese) yields "%6".
//* =========================================================================
TERMINALPP_EXPORT
byte_storage charset_to_string(charset const &loc);

byte_storage charset_to_string(charset const &cs)
{
    for (auto const &mapping : charset_map)
    {
        if (mapping.first == cs)
        {
            return mapping.second;
        }
    }

    for (auto const &mapping : extended_charset_map)
    {
        if (mapping.first == cs)
        {
            return mapping.second;
        }
    }

    return CHARSET_US_ASCII;
}
#endif

}}
