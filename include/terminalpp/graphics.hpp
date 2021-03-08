#pragma once
#include "terminalpp/ansi/graphics.hpp"

namespace terminalpp { namespace graphics {

//* =========================================================================
/// \brief An enumeration of basic ANSI colours.
//* =========================================================================
enum class colour : byte
{
    black    = terminalpp::ansi::graphics::colour_black,
    red      = terminalpp::ansi::graphics::colour_red,
    green    = terminalpp::ansi::graphics::colour_green,
    yellow   = terminalpp::ansi::graphics::colour_yellow,
    blue     = terminalpp::ansi::graphics::colour_blue,
    magenta  = terminalpp::ansi::graphics::colour_magenta,
    cyan     = terminalpp::ansi::graphics::colour_cyan,
    white    = terminalpp::ansi::graphics::colour_white,
    default_ = terminalpp::ansi::graphics::colour_default,
};


//* =========================================================================
/// \brief The intensity (i.e. bold, faint, or normal) of an element.
//* =========================================================================
enum class intensity : byte
{
    bold   = terminalpp::ansi::graphics::bold,
    faint  = terminalpp::ansi::graphics::faint,
    normal = terminalpp::ansi::graphics::normal_intensity,
};

//* =========================================================================
/// \brief Whether an element is underlined or not.
//* =========================================================================
enum class underlining : byte
{
    underlined     = terminalpp::ansi::graphics::underlined,
    not_underlined = terminalpp::ansi::graphics::not_underlined,
};

//* =========================================================================
/// \brief Whether an element is blinking or not.
//* =========================================================================
enum class blinking : byte
{
    blink  = terminalpp::ansi::graphics::blinking,
    steady = terminalpp::ansi::graphics::steady,
};

//* =========================================================================
/// \brief The polarity of an element; a negative polarity will result in the
/// element's foreground and background colours being swapped.
//* =========================================================================
enum class polarity : byte
{
    negative = terminalpp::ansi::graphics::negative_polarity,
    positive = terminalpp::ansi::graphics::positive_polarity,
};

}}