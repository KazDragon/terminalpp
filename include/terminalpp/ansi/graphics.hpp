#pragma once

//* =========================================================================
/// \namespace terminalpp::ansi::graphics
/// \brief Contains constants for the Select Graphics Rendition
/// command parameters.
//* =========================================================================
namespace terminalpp { namespace ansi { namespace graphics {

static char const NO_ATTRIBUTES                     = 0;

//* =========================================================================
/// \brief The intensity (i.e. bold, faint, or normal) of an element.
//* =========================================================================
enum class intensity : char
{
    bold                                            = 1,
    faint                                           = 2,
    normal                                          = 22,
};

//* =========================================================================
/// \brief Whether an element is underlined or not.
//* =========================================================================
enum class underlining : char
{
    underlined                                      = 4,
    not_underlined                                  = 24,
};

//* =========================================================================
/// \brief Whether an element is blinking or not.
//* =========================================================================
enum class blinking : char
{
    blink                                           = 5,
    steady                                          = 25,
};

static char const FOREGROUND_COLOUR_BASE            = 30;
static char const BACKGROUND_COLOUR_BASE            = 40;

//* =========================================================================
/// \brief An enumeration of basic ANSI colours.
//* =========================================================================
enum class colour : char
{
    black                                           = 0,
    red                                             = 1,
    green                                           = 2,
    yellow                                          = 3,
    blue                                            = 4,
    magenta                                         = 5,
    cyan                                            = 6,
    white                                           = 7,
    default_                                        = 9,
};

//* =========================================================================
/// \brief The polarity of an element; a negative polarity will result in the
/// element's foreground and background colours being swapped.
//* =========================================================================
enum class polarity : char
{
    negative                                        = 7,
    positive                                        = 27,
};

}}}
