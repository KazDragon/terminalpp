#include "terminalpp/detail/element_difference.hpp"
#include "terminalpp/element.hpp"
#include "terminalpp/ansi/protocol.hpp"
#include "terminalpp/ansi/functions.hpp"
#include <boost/format.hpp>

// TODO: In some cases, switching from one character set to the other
// wont make any difference, so we can "carry" the charset for as long as
// necessary.  E.g. the character 'a' is the same in the UK and US ASCII sets,
// but different in DEC (where it is a shadowed block).  Therefore, when
// printing a glyph in UK charset then 'a' in US charset, it's not actually
// necessary to change charset (yet).

namespace terminalpp { namespace detail {

namespace {

// ==========================================================================
// CHANGE_CHARSET
// ==========================================================================
std::string change_charset(
    terminalpp::ansi::charset const &source,
    terminalpp::ansi::charset const &dest)
{
    std::string result;

    if (source != dest)
    {
        if (dest == terminalpp::ansi::charset::utf8)
        {
            result = terminalpp::ansi::select_utf8_charset();
        }
        else
        {
            if (source == terminalpp::ansi::charset::utf8)
            {
                result += terminalpp::ansi::select_default_charset();
            }

            result += terminalpp::ansi::designate_g0_charset(dest);
        }
    }

    return result;
}

// ==========================================================================
// APPEND_GRAPHICS_CHANGE
// ==========================================================================
template <class GraphicsAttribute>
void append_graphics_change(
    std::string &change,
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

    change += boost::str(boost::format("%d") % int(dest));
}

// ==========================================================================
// LOW_FOREGROUND_COLOUR_CODE
// ==========================================================================
std::string low_foreground_colour_code(terminalpp::low_colour const &col)
{
    int value = int(col.value_)
              + terminalpp::ansi::graphics::FOREGROUND_COLOUR_BASE;

    return boost::str(boost::format("%d") % value);
}

// ==========================================================================
// HIGH_FOREGROUND_COLOUR_CODE
// ==========================================================================
std::string high_foreground_colour_code(terminalpp::high_colour const &col)
{
    int value = col.red_ * 36
              + col.green_ * 6
              + col.blue_
              + 16;

    return boost::str(boost::format("38;5;%d") % value);
}

// ==========================================================================
// GREYSCALE_FOREGROUND_COLOUR_CODE
// ==========================================================================
std::string greyscale_foreground_colour_code(
    terminalpp::greyscale_colour const &col)
{
    int value = col.shade_ + 232;

    return boost::str(boost::format("38;5;%d") % value);
}

// ==========================================================================
// FOREGROUND_COLOUR_CODE
// ==========================================================================
std::string foreground_colour_code(terminalpp::colour const &col)
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
void append_foreground_colour(
    std::string &change,
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
std::string low_background_colour_code(terminalpp::low_colour const &col)
{
    int value = int(col.value_)
    + terminalpp::ansi::graphics::BACKGROUND_COLOUR_BASE;

    return boost::str(boost::format("%d") % value);
}

// ==========================================================================
// HIGH_BACKGROUND_COLOUR_CODE
// ==========================================================================
std::string high_background_colour_code(terminalpp::high_colour const &col)
{
    int value = col.red_ * 36
    + col.green_ * 6
    + col.blue_
    + 16;

    return boost::str(boost::format("48;5;%d") % value);
}

// ==========================================================================
// GREYSCALE_BACKGROUND_COLOUR_CODE
// ==========================================================================
std::string greyscale_background_colour_code(
    terminalpp::greyscale_colour const &col)
{
    int value = col.shade_ + 232;

    return boost::str(boost::format("48;5;%d") % value);
}

// ==========================================================================
// BACKGROUND_COLOUR_CODE
// ==========================================================================
std::string background_colour_code(terminalpp::colour const &col)
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
void append_background_colour(
    std::string &change,
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
// DEFAULT_ATTRIBUTE
// ==========================================================================
std::string default_attribute()
{
    return boost::str(
        boost::format("%s%d%c")
      % terminalpp::ansi::control7::CSI
      % int(terminalpp::ansi::graphics::NO_ATTRIBUTES)
      % terminalpp::ansi::csi::SELECT_GRAPHICS_RENDITION);
}

// ==========================================================================
// CHANGE_ATTRIBUTE
// ==========================================================================
std::string change_attribute(
    terminalpp::attribute const &source,
    terminalpp::attribute const &dest)
{
    if (source == dest)
    {
        return "";
    }

    if (dest == terminalpp::attribute{})
    {
        return default_attribute();
    }

    std::string change;

    append_graphics_change(change, source.intensity_, dest.intensity_);
    append_graphics_change(change, source.polarity_, dest.polarity_);
    append_graphics_change(change, source.underlining_, dest.underlining_);
    append_foreground_colour(change, source.foreground_colour_, dest.foreground_colour_);
    append_background_colour(change, source.background_colour_, dest.background_colour_);

    std::string result =
        terminalpp::ansi::control7::CSI
      + change
      + terminalpp::ansi::csi::SELECT_GRAPHICS_RENDITION;

    return result;
}

}

// ==========================================================================
// ELEMENT_DIFFERENCE
// ==========================================================================
std::string element_difference(
    terminalpp::element const &lhs,
    terminalpp::element const &rhs)
{
    std::string result;

    result += change_charset(lhs.glyph_.charset_, rhs.glyph_.charset_);
    result += change_attribute(lhs.attribute_, rhs.attribute_);

    return result;
}

}}
