#pragma once
#include "terminalpp/core.hpp"

//* =========================================================================
/// \namespace terminalpp::ansi::graphics
/// \brief Contains constants for the Select Graphics Rendition
/// command parameters.
//* =========================================================================
namespace terminalpp { namespace ansi { namespace graphics {

static constexpr byte no_attributes = 0;

// Intensity Constants
static constexpr byte bold   = 1;
static constexpr byte faint  = 2;
static constexpr byte normal_intensity = 22;

// Underlining Constants
static constexpr byte underlined     = 4;
static constexpr byte not_underlined = 24;

// Blinking Constants
static constexpr byte blinking = 5;
static constexpr byte steady   = 25;

// Polarity Constants
static constexpr byte negative_polarity = 7;
static constexpr byte positive_polarity = 27;

// "Low" colour constants
static constexpr byte foreground_colour_base = 30;
static constexpr byte background_colour_base = 40;

static constexpr byte colour_black   = 0;
static constexpr byte colour_red     = 1;
static constexpr byte colour_green   = 2;
static constexpr byte colour_yellow  = 3;
static constexpr byte colour_blue    = 4;
static constexpr byte colour_magenta = 5;
static constexpr byte colour_cyan    = 6;
static constexpr byte colour_white   = 7;
static constexpr byte colour_default = 9;

// "High" colour constants.
// High colours are the 216 RGB colours of the 256-colour palette,  where 
// there are 6 possible values for each of R, G, B, and the colour 
// components are stored according to multiples of that number such that
// the value of the colour is 36R + 6G + B.

// ==========================================================================
/// \brief Encode an RGB value.
// ==========================================================================
constexpr byte encode_high_components(byte red, byte green, byte blue)
{
    return red * 36 + green * 6 + blue;
}

// ==========================================================================
/// \brief Extract the red component of a high colour value.
// ==========================================================================
constexpr byte high_red_component(byte value)
{
    return value / 36;
}

// ==========================================================================
/// \brief Extract the green component of a high colour value.
// ==========================================================================
constexpr byte high_green_component(byte value)
{
    return (value % 36) / 6;
}

// ==========================================================================
/// \brief Extract the blue component of a high colour value.
// ==========================================================================
constexpr byte high_blue_component(byte value)
{
    return value % 6;
}

}}}
