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
    terminalpp::byte_storage utf8_;
};

[[nodiscard]] terminalpp::bytes as_bytes(
    terminalpp::byte_storage const &storage) noexcept
{
    return {storage.data(), storage.size()};
}

[[nodiscard]] std::optional<terminalpp::bytes> utf8_default_mapping(
    terminalpp::glyph const &glyph) noexcept
{
    using namespace terminalpp::literals;  // NOLINT

    static auto const translations = std::array{
        translated_glyph{terminalpp::charset::dec, '`'_tb, "\xE2\x97\x86"_tb},
        translated_glyph{terminalpp::charset::dec, 'a'_tb, "\xE2\x96\x92"_tb},
        translated_glyph{terminalpp::charset::dec, 'b'_tb, "\xE2\x90\x89"_tb},
        translated_glyph{terminalpp::charset::dec, 'c'_tb, "\xE2\x90\x8C"_tb},
        translated_glyph{terminalpp::charset::dec, 'd'_tb, "\xE2\x90\x8D"_tb},
        translated_glyph{terminalpp::charset::dec, 'e'_tb, "\xE2\x90\x8A"_tb},
        translated_glyph{terminalpp::charset::dec, 'f'_tb, "\xC2\xB0"_tb},
        translated_glyph{terminalpp::charset::dec, 'g'_tb, "\xC2\xB1"_tb},
        translated_glyph{terminalpp::charset::dec, 'h'_tb, "\xE2\x90\xA4"_tb},
        translated_glyph{terminalpp::charset::dec, 'i'_tb, "\xE2\x90\x8B"_tb},
        translated_glyph{terminalpp::charset::dec, 'j'_tb, "\xE2\x94\x98"_tb},
        translated_glyph{terminalpp::charset::dec, 'k'_tb, "\xE2\x94\x90"_tb},
        translated_glyph{terminalpp::charset::dec, 'l'_tb, "\xE2\x94\x8C"_tb},
        translated_glyph{terminalpp::charset::dec, 'm'_tb, "\xE2\x94\x94"_tb},
        translated_glyph{terminalpp::charset::dec, 'n'_tb, "\xE2\x94\xBC"_tb},
        translated_glyph{terminalpp::charset::dec, 'o'_tb, "\xE2\x8E\xBA"_tb},
        translated_glyph{terminalpp::charset::dec, 'p'_tb, "\xE2\x8E\xBB"_tb},
        translated_glyph{terminalpp::charset::dec, 'q'_tb, "\xE2\x94\x80"_tb},
        translated_glyph{terminalpp::charset::dec, 'r'_tb, "\xE2\x8E\xBC"_tb},
        translated_glyph{terminalpp::charset::dec, 's'_tb, "\xE2\x8E\xBD"_tb},
        translated_glyph{terminalpp::charset::dec, 't'_tb, "\xE2\x94\x9C"_tb},
        translated_glyph{terminalpp::charset::dec, 'u'_tb, "\xE2\x94\xA4"_tb},
        translated_glyph{terminalpp::charset::dec, 'v'_tb, "\xE2\x94\xB4"_tb},
        translated_glyph{terminalpp::charset::dec, 'w'_tb, "\xE2\x94\xAC"_tb},
        translated_glyph{terminalpp::charset::dec, 'x'_tb, "\xE2\x94\x82"_tb},
        translated_glyph{terminalpp::charset::dec, 'y'_tb, "\xE2\x89\xA4"_tb},
        translated_glyph{terminalpp::charset::dec, 'z'_tb, "\xE2\x89\xA5"_tb},
        translated_glyph{terminalpp::charset::dec, '{'_tb, "\xCF\x80"_tb},
        translated_glyph{terminalpp::charset::dec, '|'_tb, "\xE2\x89\xA0"_tb},
        translated_glyph{terminalpp::charset::dec, '}'_tb, "\xC2\xA3"_tb},
        translated_glyph{terminalpp::charset::dec, '~'_tb, "\xC2\xB7"_tb},
        translated_glyph{terminalpp::charset::uk, '#'_tb, "\xC2\xA3"_tb},
    };

    for (auto const &translation : translations)
    {
        if (translation.charset_ == glyph.charset_
            && translation.source_ == glyph.character_)
        {
            return as_bytes(translation.utf8_);
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
            write_fn(*mapped);
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
