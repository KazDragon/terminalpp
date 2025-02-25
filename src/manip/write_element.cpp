#include "terminalpp/detail/element_difference.hpp"
#include "terminalpp/terminal.hpp"

namespace terminalpp {
namespace {

// ==========================================================================
// WRITE_UTF8_GLYPH
// ==========================================================================
void write_utf8_glyph(
    element const &elem, terminal::write_function const &write_fn)
{
    std::size_t const last_utf8_index = [&elem]() {
        std::size_t index = 0;

        for (; index < sizeof(elem.glyph_.ucharacter_)
               && elem.glyph_.ucharacter_[index] != '\0';
             ++index)
        {
            if ((elem.glyph_.ucharacter_[index] & 0x80) == 0)
            {
                break;
            }
        }

        return index;
    }();

    terminalpp::bytes const data{
        elem.glyph_.ucharacter_, std::max(last_utf8_index, std::size_t{1U})};
    write_fn(data);
}

// ==========================================================================
// WRITE_REGULAR_GLYPH
// ==========================================================================
void write_regular_glyph(
    element const &elem, terminal::write_function const &write_fn)
{
    terminalpp::bytes data{&elem.glyph_.character_, 1};
    write_fn(data);
}

// ==========================================================================
// WRITE_SINGLE_ELEMENT
// ==========================================================================
void write_single_element(
    element const &elem, terminal::write_function const &write_fn)
{
    if (elem.glyph_.charset_ == charset::utf8)
    {
        write_utf8_glyph(elem, write_fn);
    }
    else
    {
        write_regular_glyph(elem, write_fn);
    }
}

// ==========================================================================
// ADVANCE_CURSOR_POSITION
// ==========================================================================
void advance_cursor_position(terminal_state &state)
{
    if (state.cursor_position_)
    {
        if (++state.cursor_position_->x_ == state.terminal_size_.width_)
        {
            // Terminals differ in their behaviour when reaching the
            // end of the line.  Some wrap to the next line, some bounce
            // against the edge.  To maintain consistency, forget the
            // current cursor position.
            state.cursor_position_ = {};
        }
    }
}

}  // namespace

// ==========================================================================
// WRITE_ELEMENT::OPERATOR()
// ==========================================================================
void write_element::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    terminal::write_function const &write_fn) const
{
    static auto const default_element = element{};
    auto const &last_element = state.last_element_.has_value()
                                 ? *state.last_element_
                                 : default_element;

    detail::change_charset(
        last_element.glyph_.charset_, element_.glyph_.charset_, beh, write_fn);

    detail::change_attribute(
        last_element.attribute_, element_.attribute_, beh, write_fn);

    write_single_element(element_, write_fn);

    state.last_element_ = element_;

    advance_cursor_position(state);
}

}  // namespace terminalpp
