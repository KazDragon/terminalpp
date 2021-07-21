#include "terminalpp/element.hpp"

namespace terminalpp {
namespace detail {

enum class parse_state
{
    idle,
    escape,
    done,
};

namespace {

parse_state parse_idle(element &elem, char ch)
{
    switch (ch)
    {
        case '\\':
            return parse_state::escape;
        default:
            elem.glyph_.character_ = static_cast<byte>(ch);
            return parse_state::done;
    }
}

parse_state parse_escape(element &elem, char ch)
{
    elem.glyph_.character_ = static_cast<byte>(ch);
    return parse_state::done;
}

}

element parse_element(gsl::cstring_span &text)
{
    element elem;
    auto state = parse_state::idle;

    while(!text.empty())
    {
        auto const ch = text[0];

        switch(state)
        {
            case parse_state::idle:
                state = parse_idle(elem, ch);
                break;

            case parse_state::escape:
                state = parse_escape(elem, ch);
                break;

            default:
                break;
        }

        text = text.subspan(1);

        if (state == parse_state::done)
        {
            break;
        }
    }

    return elem;
}

}}
