#include "terminalpp/element.hpp"

namespace terminalpp {
namespace detail {

element parse_element(gsl::cstring_span text)
{
    element elem;

    for (auto const ch : text)
    {
        switch (ch)
        {
        case '\\' :
            return elem;
        default:
            elem.glyph_.character_ = static_cast<byte>(text[0]);
            return elem;
        }
    }

    return elem;
}

}}
