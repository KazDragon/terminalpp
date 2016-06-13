#pragma once

// Namespace for Select Graphics Rendition parameters
namespace terminalpp { namespace ansi { namespace graphics {

static char const NO_ATTRIBUTES                     = 0;

enum class intensity : char
{
    bold                                            = 1,
    faint                                           = 2,
    normal                                          = 22,
};

enum class underlining : char
{
    underlined                                      = 4,
    not_underlined                                  = 24,
};

enum class blinking : char
{
    blink                                           = 5,
    steady                                          = 25,
};

static char const FOREGROUND_COLOUR_BASE            = 30;
static char const BACKGROUND_COLOUR_BASE            = 40;

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

enum class polarity : char
{
    negative                                        = 7,
    positive                                        = 27,
};

}}}
