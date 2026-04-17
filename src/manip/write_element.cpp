#include "terminalpp/detail/element_difference.hpp"
#include "terminalpp/terminal.hpp"

#include <array>
#include <optional>

namespace terminalpp {
namespace {

struct translated_glyph
{
    terminalpp::character_set charset_;
    terminalpp::byte source_;
    terminalpp::glyph replacement_;
};

[[nodiscard]] std::optional<terminalpp::glyph> utf8_default_mapping(
    terminalpp::glyph const &glyph) noexcept
{
    static constexpr auto translations = std::array{
        // clang-format off
        translated_glyph{terminalpp::charset::dec, '`', terminalpp::glyph{u8"\u25C6"}},
        translated_glyph{terminalpp::charset::dec, 'a', terminalpp::glyph{u8"\u2592"}},
        translated_glyph{terminalpp::charset::dec, 'b', terminalpp::glyph{u8"\u2409"}},
        translated_glyph{terminalpp::charset::dec, 'c', terminalpp::glyph{u8"\u240C"}},
        translated_glyph{terminalpp::charset::dec, 'd', terminalpp::glyph{u8"\u240D"}},
        translated_glyph{terminalpp::charset::dec, 'e', terminalpp::glyph{u8"\u240A"}},
        translated_glyph{terminalpp::charset::dec, 'f', terminalpp::glyph{u8"\u00B0"}},
        translated_glyph{terminalpp::charset::dec, 'g', terminalpp::glyph{u8"\u00B1"}},
        translated_glyph{terminalpp::charset::dec, 'h', terminalpp::glyph{u8"\u2424"}},
        translated_glyph{terminalpp::charset::dec, 'i', terminalpp::glyph{u8"\u240B"}},
        translated_glyph{terminalpp::charset::dec, 'j', terminalpp::glyph{u8"\u2518"}},
        translated_glyph{terminalpp::charset::dec, 'k', terminalpp::glyph{u8"\u2510"}},
        translated_glyph{terminalpp::charset::dec, 'l', terminalpp::glyph{u8"\u250C"}},
        translated_glyph{terminalpp::charset::dec, 'm', terminalpp::glyph{u8"\u2514"}},
        translated_glyph{terminalpp::charset::dec, 'n', terminalpp::glyph{u8"\u253C"}},
        translated_glyph{terminalpp::charset::dec, 'o', terminalpp::glyph{u8"\u23BA"}},
        translated_glyph{terminalpp::charset::dec, 'p', terminalpp::glyph{u8"\u23BB"}},
        translated_glyph{terminalpp::charset::dec, 'q', terminalpp::glyph{u8"\u2500"}},
        translated_glyph{terminalpp::charset::dec, 'r', terminalpp::glyph{u8"\u23BC"}},
        translated_glyph{terminalpp::charset::dec, 's', terminalpp::glyph{u8"\u23BD"}},
        translated_glyph{terminalpp::charset::dec, 't', terminalpp::glyph{u8"\u251C"}},
        translated_glyph{terminalpp::charset::dec, 'u', terminalpp::glyph{u8"\u2524"}},
        translated_glyph{terminalpp::charset::dec, 'v', terminalpp::glyph{u8"\u2534"}},
        translated_glyph{terminalpp::charset::dec, 'w', terminalpp::glyph{u8"\u252C"}},
        translated_glyph{terminalpp::charset::dec, 'x', terminalpp::glyph{u8"\u2502"}},
        translated_glyph{terminalpp::charset::dec, 'y', terminalpp::glyph{u8"\u2264"}},
        translated_glyph{terminalpp::charset::dec, 'z', terminalpp::glyph{u8"\u2265"}},
        translated_glyph{terminalpp::charset::dec, '{', terminalpp::glyph{u8"\u03C0"}},
        translated_glyph{terminalpp::charset::dec, '|', terminalpp::glyph{u8"\u2260"}},
        translated_glyph{terminalpp::charset::dec, '}', terminalpp::glyph{u8"\u00A3"}},
        translated_glyph{terminalpp::charset::dec, '~', terminalpp::glyph{u8"\u00B7"}},
        translated_glyph{terminalpp::charset::uk, '#', terminalpp::glyph{u8"\u00A3"}},
        translated_glyph{terminalpp::charset::dutch, '@', terminalpp::glyph{u8"\u00BE"}},
        translated_glyph{terminalpp::charset::dutch, '[', terminalpp::glyph{u8"\u0133"}},
        translated_glyph{terminalpp::charset::dutch, '\\', terminalpp::glyph{u8"\u00BD"}},
        translated_glyph{terminalpp::charset::dutch, ']', terminalpp::glyph{u8"\u00A6"}},
        translated_glyph{terminalpp::charset::dutch, '{', terminalpp::glyph{u8"\u00A8"}},
        translated_glyph{terminalpp::charset::dutch, '|', terminalpp::glyph{u8"\u0192"}},
        translated_glyph{terminalpp::charset::dutch, '}', terminalpp::glyph{u8"\u00BC"}},
        translated_glyph{terminalpp::charset::dutch, '~', terminalpp::glyph{u8"\u00B4"}},
        translated_glyph{terminalpp::charset::finnish, '[', terminalpp::glyph{u8"\u00C4"}},
        translated_glyph{terminalpp::charset::finnish, '\\', terminalpp::glyph{u8"\u00D6"}},
        translated_glyph{terminalpp::charset::finnish, ']', terminalpp::glyph{u8"\u00C5"}},
        translated_glyph{terminalpp::charset::finnish, '^', terminalpp::glyph{u8"\u00DC"}},
        translated_glyph{terminalpp::charset::finnish, '`', terminalpp::glyph{u8"\u00E9"}},
        translated_glyph{terminalpp::charset::finnish, '{', terminalpp::glyph{u8"\u00E4"}},
        translated_glyph{terminalpp::charset::finnish, '|', terminalpp::glyph{u8"\u00F6"}},
        translated_glyph{terminalpp::charset::finnish, '}', terminalpp::glyph{u8"\u00E5"}},
        translated_glyph{terminalpp::charset::finnish, '~', terminalpp::glyph{u8"\u00FC"}},
        translated_glyph{terminalpp::charset::french, '#', terminalpp::glyph{u8"\u00A3"}},
        translated_glyph{terminalpp::charset::french, '@', terminalpp::glyph{u8"\u00E0"}},
        translated_glyph{terminalpp::charset::french, '[', terminalpp::glyph{u8"\u00B0"}},
        translated_glyph{terminalpp::charset::french, '\\', terminalpp::glyph{u8"\u00E7"}},
        translated_glyph{terminalpp::charset::french, ']', terminalpp::glyph{u8"\u00A7"}},
        translated_glyph{terminalpp::charset::french, '{', terminalpp::glyph{u8"\u00E9"}},
        translated_glyph{terminalpp::charset::french, '|', terminalpp::glyph{u8"\u00F9"}},
        translated_glyph{terminalpp::charset::french, '}', terminalpp::glyph{u8"\u00E8"}},
        translated_glyph{terminalpp::charset::french, '~', terminalpp::glyph{u8"\u00A8"}},
        translated_glyph{terminalpp::charset::french_canadian, '@', terminalpp::glyph{u8"\u00E0"}},
        translated_glyph{terminalpp::charset::french_canadian, '[', terminalpp::glyph{u8"\u00E2"}},
        translated_glyph{terminalpp::charset::french_canadian, '\\', terminalpp::glyph{u8"\u00E7"}},
        translated_glyph{terminalpp::charset::french_canadian, ']', terminalpp::glyph{u8"\u00EA"}},
        translated_glyph{terminalpp::charset::french_canadian, '^', terminalpp::glyph{u8"\u00EE"}},
        translated_glyph{terminalpp::charset::french_canadian, '`', terminalpp::glyph{u8"\u00F4"}},
        translated_glyph{terminalpp::charset::french_canadian, '{', terminalpp::glyph{u8"\u00E9"}},
        translated_glyph{terminalpp::charset::french_canadian, '|', terminalpp::glyph{u8"\u00F9"}},
        translated_glyph{terminalpp::charset::french_canadian, '}', terminalpp::glyph{u8"\u00E8"}},
        translated_glyph{terminalpp::charset::french_canadian, '~', terminalpp::glyph{u8"\u00FB"}},
        translated_glyph{terminalpp::charset::german, '@', terminalpp::glyph{u8"\u00A7"}},
        translated_glyph{terminalpp::charset::german, '[', terminalpp::glyph{u8"\u00C4"}},
        translated_glyph{terminalpp::charset::german, '\\', terminalpp::glyph{u8"\u00D6"}},
        translated_glyph{terminalpp::charset::german, ']', terminalpp::glyph{u8"\u00DC"}},
        translated_glyph{terminalpp::charset::german, '{', terminalpp::glyph{u8"\u00E4"}},
        translated_glyph{terminalpp::charset::german, '|', terminalpp::glyph{u8"\u00F6"}},
        translated_glyph{terminalpp::charset::german, '}', terminalpp::glyph{u8"\u00FC"}},
        translated_glyph{terminalpp::charset::german, '~', terminalpp::glyph{u8"\u00DF"}},
        translated_glyph{terminalpp::charset::italian, '#', terminalpp::glyph{u8"\u00A3"}},
        translated_glyph{terminalpp::charset::italian, '@', terminalpp::glyph{u8"\u00A7"}},
        translated_glyph{terminalpp::charset::italian, '[', terminalpp::glyph{u8"\u00B0"}},
        translated_glyph{terminalpp::charset::italian, '\\', terminalpp::glyph{u8"\u00E7"}},
        translated_glyph{terminalpp::charset::italian, ']', terminalpp::glyph{u8"\u00E9"}},
        translated_glyph{terminalpp::charset::italian, '`', terminalpp::glyph{u8"\u00F9"}},
        translated_glyph{terminalpp::charset::italian, '{', terminalpp::glyph{u8"\u00E0"}},
        translated_glyph{terminalpp::charset::italian, '|', terminalpp::glyph{u8"\u00F2"}},
        translated_glyph{terminalpp::charset::italian, '}', terminalpp::glyph{u8"\u00E8"}},
        translated_glyph{terminalpp::charset::italian, '~', terminalpp::glyph{u8"\u00EC"}},
        translated_glyph{terminalpp::charset::danish, '@', terminalpp::glyph{u8"\u00C4"}},
        translated_glyph{terminalpp::charset::danish, '[', terminalpp::glyph{u8"\u00C6"}},
        translated_glyph{terminalpp::charset::danish, '\\', terminalpp::glyph{u8"\u00D8"}},
        translated_glyph{terminalpp::charset::danish, ']', terminalpp::glyph{u8"\u00C5"}},
        translated_glyph{terminalpp::charset::danish, '^', terminalpp::glyph{u8"\u00DC"}},
        translated_glyph{terminalpp::charset::danish, '`', terminalpp::glyph{u8"\u00E4"}},
        translated_glyph{terminalpp::charset::danish, '{', terminalpp::glyph{u8"\u00E6"}},
        translated_glyph{terminalpp::charset::danish, '|', terminalpp::glyph{u8"\u00F8"}},
        translated_glyph{terminalpp::charset::danish, '}', terminalpp::glyph{u8"\u00E5"}},
        translated_glyph{terminalpp::charset::danish, '~', terminalpp::glyph{u8"\u00FC"}},
        translated_glyph{terminalpp::charset::portuguese, '[', terminalpp::glyph{u8"\u00C3"}},
        translated_glyph{terminalpp::charset::portuguese, '\\', terminalpp::glyph{u8"\u00C7"}},
        translated_glyph{terminalpp::charset::portuguese, ']', terminalpp::glyph{u8"\u00D5"}},
        translated_glyph{terminalpp::charset::portuguese, '{', terminalpp::glyph{u8"\u00E3"}},
        translated_glyph{terminalpp::charset::portuguese, '|', terminalpp::glyph{u8"\u00E7"}},
        translated_glyph{terminalpp::charset::portuguese, '}', terminalpp::glyph{u8"\u00F5"}},
        translated_glyph{terminalpp::charset::spanish, '#', terminalpp::glyph{u8"\u00A3"}},
        translated_glyph{terminalpp::charset::spanish, '@', terminalpp::glyph{u8"\u00A7"}},
        translated_glyph{terminalpp::charset::spanish, '[', terminalpp::glyph{u8"\u00A1"}},
        translated_glyph{terminalpp::charset::spanish, '\\', terminalpp::glyph{u8"\u00D1"}},
        translated_glyph{terminalpp::charset::spanish, ']', terminalpp::glyph{u8"\u00BF"}},
        translated_glyph{terminalpp::charset::spanish, '{', terminalpp::glyph{u8"\u00B0"}},
        translated_glyph{terminalpp::charset::spanish, '|', terminalpp::glyph{u8"\u00F1"}},
        translated_glyph{terminalpp::charset::spanish, '}', terminalpp::glyph{u8"\u00E7"}},
        translated_glyph{terminalpp::charset::swedish, '@', terminalpp::glyph{u8"\u00C9"}},
        translated_glyph{terminalpp::charset::swedish, '[', terminalpp::glyph{u8"\u00C4"}},
        translated_glyph{terminalpp::charset::swedish, '\\', terminalpp::glyph{u8"\u00D6"}},
        translated_glyph{terminalpp::charset::swedish, ']', terminalpp::glyph{u8"\u00C5"}},
        translated_glyph{terminalpp::charset::swedish, '^', terminalpp::glyph{u8"\u00DC"}},
        translated_glyph{terminalpp::charset::swedish, '`', terminalpp::glyph{u8"\u00E9"}},
        translated_glyph{terminalpp::charset::swedish, '{', terminalpp::glyph{u8"\u00E4"}},
        translated_glyph{terminalpp::charset::swedish, '|', terminalpp::glyph{u8"\u00F6"}},
        translated_glyph{terminalpp::charset::swedish, '}', terminalpp::glyph{u8"\u00E5"}},
        translated_glyph{terminalpp::charset::swedish, '~', terminalpp::glyph{u8"\u00FC"}},
        translated_glyph{terminalpp::charset::swiss, '#', terminalpp::glyph{u8"\u00F9"}},
        translated_glyph{terminalpp::charset::swiss, '@', terminalpp::glyph{u8"\u00E0"}},
        translated_glyph{terminalpp::charset::swiss, '[', terminalpp::glyph{u8"\u00E9"}},
        translated_glyph{terminalpp::charset::swiss, '\\', terminalpp::glyph{u8"\u00E7"}},
        translated_glyph{terminalpp::charset::swiss, ']', terminalpp::glyph{u8"\u00EA"}},
        translated_glyph{terminalpp::charset::swiss, '^', terminalpp::glyph{u8"\u00EE"}},
        translated_glyph{terminalpp::charset::swiss, '_', terminalpp::glyph{u8"\u00E8"}},
        translated_glyph{terminalpp::charset::swiss, '`', terminalpp::glyph{u8"\u00F4"}},
        translated_glyph{terminalpp::charset::swiss, '{', terminalpp::glyph{u8"\u00E4"}},
        translated_glyph{terminalpp::charset::swiss, '|', terminalpp::glyph{u8"\u00F6"}},
        translated_glyph{terminalpp::charset::swiss, '}', terminalpp::glyph{u8"\u00FC"}},
        translated_glyph{terminalpp::charset::swiss, '~', terminalpp::glyph{u8"\u00FB"}},
        // clang-format on
    };

    for (auto const &translation : translations)
    {
        if (translation.charset_ == glyph.charset_
            && translation.source_ == glyph.character_)
        {
            return translation.replacement_;
        }
    }

    return std::nullopt;
}

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
    element const &elem,
    behaviour const &beh,
    terminal::write_function const &write_fn)
{
    if (beh.utf8_by_default)
    {
        if (elem.glyph_.charset_ == charset::utf8)
        {
            write_utf8_glyph(elem, write_fn);
        }
        else if (auto const mapped = utf8_default_mapping(elem.glyph_))
        {
            write_utf8_glyph(*mapped, write_fn);
        }
        else
        {
            write_regular_glyph(elem, write_fn);
        }
    }
    else if (elem.glyph_.charset_ == charset::utf8)
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

    write_single_element(element_, beh, write_fn);

    state.last_element_ = element_;

    advance_cursor_position(state);
}

}  // namespace terminalpp
