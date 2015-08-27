#include "terminalpp/detail/element_difference.hpp"
#include "terminalpp/ansi/protocol.hpp"
#include <boost/format.hpp>

namespace terminalpp { namespace detail {

namespace {

std::string change_locale(char source, char dest)
{
    return source == dest
      ? std::string{}
      : std::string{
            terminalpp::ansi::ESCAPE,
            terminalpp::ansi::character_set::CHARACTER_SET_G0,
            dest,
        };
}

template <class GraphicsAttribute>
std::string change_graphics_attribute(
    GraphicsAttribute const &source,
    GraphicsAttribute const &dest,
    bool separator_required)
{
    if (source == dest)
    {
        return {};
    }

    std::string result;

    if (separator_required)
    {
        result += terminalpp::ansi::PARAMETER_SEPARATOR;
    }

    result += boost::str(boost::format("%d") % int(dest));

    return result;
}

std::string low_foreground_colour_code(terminalpp::low_colour const &col)
{
    int value = int(col.value_)
              + terminalpp::ansi::graphics::FOREGROUND_COLOUR_BASE;

    return boost::str(boost::format("%d") % value);
}

std::string high_foreground_colour_code(terminalpp::high_colour const &col)
{
    int value = col.red_ * 36
              + col.green_ * 6
              + col.blue_
              + 16;

    return boost::str(boost::format("38;5;%d") % value);
}

std::string greyscale_foreground_colour_code(
    terminalpp::greyscale_colour const &col)
{
    int value = col.shade_ + 232;

    return boost::str(boost::format("38;5;%d") % value);
}

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

std::string change_foreground_colour(
    terminalpp::colour const &source,
    terminalpp::colour const &dest,
    bool separator_required)
{
    if (source == dest)
    {
        return {};
    }

    std::string result;

    if (separator_required)
    {
        result += terminalpp::ansi::PARAMETER_SEPARATOR;
    }

    result += foreground_colour_code(dest);

    return result;
}

std::string low_background_colour_code(terminalpp::low_colour const &col)
{
    int value = int(col.value_)
    + terminalpp::ansi::graphics::BACKGROUND_COLOUR_BASE;

    return boost::str(boost::format("%d") % value);
}

std::string high_background_colour_code(terminalpp::high_colour const &col)
{
    int value = col.red_ * 36
    + col.green_ * 6
    + col.blue_
    + 16;

    return boost::str(boost::format("48;5;%d") % value);
}

std::string greyscale_background_colour_code(
    terminalpp::greyscale_colour const &col)
{
    int value = col.shade_ + 232;

    return boost::str(boost::format("48;5;%d") % value);
}

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

std::string change_background_colour(
    terminalpp::colour const &source,
    terminalpp::colour const &dest,
    bool separator_required)
{
    if (source == dest)
    {
        return {};
    }

    std::string result;

    if (separator_required)
    {
        result += terminalpp::ansi::PARAMETER_SEPARATOR;
    }

    result += background_colour_code(dest);

    return result;
}

std::string default_attribute()
{
    return boost::str(
        boost::format("%c%c%d%c")
      % terminalpp::ansi::ESCAPE
      % terminalpp::ansi::CONTROL_SEQUENCE_INTRODUCER
      % int(terminalpp::ansi::graphics::NO_ATTRIBUTES)
      % terminalpp::ansi::SELECT_GRAPHICS_RENDITION);
}

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

    change += change_graphics_attribute(
        source.intensity_,
        dest.intensity_,
        !change.empty());

    change += change_graphics_attribute(
        source.polarity_,
        dest.polarity_,
        !change.empty());

    change += change_graphics_attribute(
        source.underlining_,
        dest.underlining_,
        !change.empty());

    change += change_foreground_colour(
        source.foreground_colour_,
        dest.foreground_colour_,
        !change.empty());

    change += change_background_colour(
        source.background_colour_,
        dest.background_colour_,
        !change.empty());

    std::string result = {
        terminalpp::ansi::ESCAPE,
        terminalpp::ansi::CONTROL_SEQUENCE_INTRODUCER,
    };

    result += change;

    result += {
        terminalpp::ansi::SELECT_GRAPHICS_RENDITION
    };

    return result;
}

}

std::string element_difference(
    terminalpp::element const &lhs,
    terminalpp::element const &rhs)
{
    std::string result;

    result += change_locale(lhs.glyph_.locale_, rhs.glyph_.locale_);
    result += change_attribute(lhs.attribute_, rhs.attribute_);

    return result;
}

}}
