#include "terminalpp/detail/element_difference.hpp"
#include "terminalpp/detail/terminal_charset_control.hpp"
#include "terminalpp/behaviour.hpp"
#include "terminalpp/element.hpp"
#include "terminalpp/ansi/protocol.hpp"
#include <fmt/format.h>

// TODO: In some cases, switching from one character set to the other
// wont make any difference, so we can "carry" the charset for as long as
// necessary.  E.g. the character 'a' is the same in the UK and US ASCII sets,
// but different in DEC (where it is a shadowed block).  Therefore, when
// printing a glyph in UK charset then 'a' in US charset, it's not actually
// necessary to change charset (yet).

using namespace fmt::literals;
using namespace terminalpp::literals;

namespace terminalpp { namespace detail {

namespace {

// ==========================================================================
// CHANGE_CHARSET
// ==========================================================================
static byte_storage change_charset(
    terminalpp::character_set const &source,
    terminalpp::character_set const &dest,
    behaviour const &terminal_behaviour)
{
    byte_storage result;

    if (source != dest)
    {
        if (dest == terminalpp::ansi::charset::utf8)
        {
            // Some terminal emulators don't recognize unicode characters when
            // not in the default character set, even when prefixing with the
            // "enter unicode" sequence.  For those, we first drop back to the
            // default character set before selecting unicode.
            if (!terminal_behaviour.unicode_in_all_charsets)
            {
                result += change_charset(
                    source, terminalpp::ansi::charset::us_ascii, terminal_behaviour);
            }

            result += terminalpp::detail::select_utf8_charset();
        }
        else
        {
            if (source == terminalpp::ansi::charset::utf8)
            {
                result += terminalpp::detail::select_default_charset();
            }

            result += terminalpp::detail::designate_g0_charset(dest.value_);
        }
    }

    return result;
}

// ==========================================================================
// APPEND_GRAPHICS_CHANGE
// ==========================================================================
template <class GraphicsAttribute>
static void append_graphics_change(
    byte_storage &change,
    GraphicsAttribute const &source,
    GraphicsAttribute const &dest)
{
    if (source == dest)
    {
        return;
    }

    if (!change.empty())
    {
        change += terminalpp::ansi::PS;
    }

    change += to_bytes("{}"_format(int(dest.value_)));
}

// ==========================================================================
// LOW_FOREGROUND_COLOUR_CODE
// ==========================================================================
static byte_storage low_foreground_colour_code(terminalpp::low_colour const &col)
{
    int value = int(col.value_)
              + terminalpp::ansi::graphics::FOREGROUND_COLOUR_BASE;

    return to_bytes("{}"_format(value));
}

// ==========================================================================
// HIGH_FOREGROUND_COLOUR_CODE
// ==========================================================================
static byte_storage high_foreground_colour_code(terminalpp::high_colour const &col)
{
    return to_bytes("38;5;{}"_format(int(col.value_)));
}

// ==========================================================================
// GREYSCALE_FOREGROUND_COLOUR_CODE
// ==========================================================================
static byte_storage greyscale_foreground_colour_code(
    terminalpp::greyscale_colour const &col)
{
    return to_bytes("38;5;{}"_format(int(col.shade_)));
}

// ==========================================================================
// FOREGROUND_COLOUR_CODE
// ==========================================================================
static byte_storage foreground_colour_code(terminalpp::colour const &col)
{
    switch (col.type_)
    {
        default :
            // Fall-through
        case terminalpp::colour::type::low :
            return low_foreground_colour_code(col.low_colour_);
            break;

        case terminalpp::colour::type::high :
            return high_foreground_colour_code(col.high_colour_);
            break;

        case terminalpp::colour::type::greyscale :
            return greyscale_foreground_colour_code(col.greyscale_colour_);
            break;
    }
}

// ==========================================================================
// APPEND_FOREGROUND_COLOUR
// ==========================================================================
static void append_foreground_colour(
    byte_storage &change,
    terminalpp::colour const &source,
    terminalpp::colour const &dest)
{
    if (source == dest)
    {
        return;
    }

    if (!change.empty())
    {
        change += terminalpp::ansi::PS;
    }

    change += foreground_colour_code(dest);
}

// ==========================================================================
// LOW_BACKGROUND_COLOUR_CODE
// ==========================================================================
static byte_storage low_background_colour_code(terminalpp::low_colour const &col)
{
    int value = int(col.value_)
      + terminalpp::ansi::graphics::BACKGROUND_COLOUR_BASE;

    return to_bytes("{}"_format(value));
}

// ==========================================================================
// HIGH_BACKGROUND_COLOUR_CODE
// ==========================================================================
static byte_storage high_background_colour_code(terminalpp::high_colour const &col)
{
    return to_bytes("48;5;{}"_format(int(col.value_)));
}

// ==========================================================================
// GREYSCALE_BACKGROUND_COLOUR_CODE
// ==========================================================================
static byte_storage greyscale_background_colour_code(
    terminalpp::greyscale_colour const &col)
{
    return to_bytes("48;5;{}"_format(int(col.shade_)));
}

// ==========================================================================
// BACKGROUND_COLOUR_CODE
// ==========================================================================
static byte_storage background_colour_code(terminalpp::colour const &col)
{
    switch (col.type_)
    {
        default :
            // Fall-through
        case terminalpp::colour::type::low :
            return low_background_colour_code(col.low_colour_);
            break;

        case terminalpp::colour::type::high :
            return high_background_colour_code(col.high_colour_);
            break;

        case terminalpp::colour::type::greyscale :
            return greyscale_background_colour_code(col.greyscale_colour_);
            break;
    }
}

// ==========================================================================
// APPEND_BAKCGROUND_COLOUR
// ==========================================================================
static void append_background_colour(
    byte_storage &change,
    terminalpp::colour const &source,
    terminalpp::colour const &dest)
{
    if (source == dest)
    {
        return;
    }

    if (!change.empty())
    {
        change += terminalpp::ansi::PS;
    }

    change += background_colour_code(dest);
}

// ==========================================================================
// CHANGE_ATTRIBUTE
// ==========================================================================
static byte_storage change_attribute(
    terminalpp::attribute const &source,
    terminalpp::attribute const &dest)
{
    if (source == dest)
    {
        return ""_tb;
    }

    if (dest == terminalpp::attribute{})
    {
        return default_attribute();
    }

    byte_storage change;

    append_graphics_change(change, source.intensity_, dest.intensity_);
    append_graphics_change(change, source.polarity_, dest.polarity_);
    append_graphics_change(change, source.underlining_, dest.underlining_);
    append_foreground_colour(change, source.foreground_colour_, dest.foreground_colour_);
    append_background_colour(change, source.background_colour_, dest.background_colour_);

    byte_storage result =
        terminalpp::ansi::control7::CSI
      + change
      + terminalpp::ansi::csi::SELECT_GRAPHICS_RENDITION;

    return result;
}

}

// ==========================================================================
// DEFAULT_ATTRIBUTE
// ==========================================================================
byte_storage default_attribute()
{
    static auto const default_attribute_string = to_bytes("{}{}{}"_format(
        terminalpp::ansi::control7::CSI,
        int(terminalpp::ansi::graphics::NO_ATTRIBUTES),
        terminalpp::ansi::csi::SELECT_GRAPHICS_RENDITION));

    return default_attribute_string;
}

// ==========================================================================
// ELEMENT_DIFFERENCE
// ==========================================================================
byte_storage element_difference(
    terminalpp::element const &lhs,
    terminalpp::element const &rhs,
    behaviour const &terminal_behaviour)
{
    byte_storage result;

    result += change_charset(
        lhs.glyph_.charset_, rhs.glyph_.charset_, terminal_behaviour);
    result += change_attribute(lhs.attribute_, rhs.attribute_);

    return result;
}

}}