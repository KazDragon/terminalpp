#pragma once
#include "terminalpp/core.hpp"

//* =========================================================================
/// \namespace terminalpp::ansi::graphics
/// \brief Contains constants for the Select Graphics Rendition
/// command parameters.
//* =========================================================================
namespace terminalpp::ansi::graphics {

// clang-format off
inline constexpr byte no_attributes = 0;

// Intensity Constants
inline constexpr byte bold   = 1;
inline constexpr byte faint  = 2;
inline constexpr byte normal_intensity = 22;

// Underlining Constants
inline constexpr byte underlined     = 4;
inline constexpr byte not_underlined = 24;

// Blinking Constants
inline constexpr byte blinking = 5;
inline constexpr byte steady   = 25;

// Polarity Constants
inline constexpr byte negative_polarity = 7;
inline constexpr byte positive_polarity = 27;

// "Low" colour constants
inline constexpr byte foreground_colour_base = 30;
inline constexpr byte background_colour_base = 40;

inline constexpr byte colour_black   = 0;
inline constexpr byte colour_red     = 1;
inline constexpr byte colour_green   = 2;
inline constexpr byte colour_yellow  = 3;
inline constexpr byte colour_blue    = 4;
inline constexpr byte colour_magenta = 5;
inline constexpr byte colour_cyan    = 6;
inline constexpr byte colour_white   = 7;
inline constexpr byte colour_default = 9;
// clang-format on

// "High" colour constants.
// High colours are the middle 216 RGB colours of the 256-colour palette,
// where there are 6 possible values for each of R, G, B, and the colour
// components are stored according to multiples of that number such that
// the value of the colour is 36R + 6G + B.  This is then stored offset
// 16.
inline constexpr byte high_colour_offset = 16;

// High colours (16-231) are sorted according to their respective hues.
inline constexpr auto red_coefficient = 36;
inline constexpr auto green_coefficient = 6;
inline constexpr auto blue_coefficient = 1;

// ==========================================================================
/// \brief Encode an RGB value.
// ==========================================================================
constexpr byte encode_high_components(byte red, byte green, byte blue) noexcept
{
    return high_colour_offset + (red * red_coefficient)
         + (green * green_coefficient) + (blue * blue_coefficient);
}

// ==========================================================================
/// \brief Extract the red component of a high colour value.
// ==========================================================================
constexpr byte high_red_component(byte value) noexcept
{
    return (value - high_colour_offset) / red_coefficient;
}

// ==========================================================================
/// \brief Extract the green component of a high colour value.
// ==========================================================================
constexpr byte high_green_component(byte value) noexcept
{
    return ((value - high_colour_offset) % red_coefficient) / green_coefficient;
}

// ==========================================================================
/// \brief Extract the blue component of a high colour value.
// ==========================================================================
constexpr byte high_blue_component(byte value) noexcept
{
    return (value - high_colour_offset) % green_coefficient;
}

// "Greyscale" colour constants.
// Greyscale colours are last 24 RGB colours of the 256-colour palette,
// each of which represents a grey colour from black to white. This value
// is then stored offset 232.
inline constexpr byte greyscale_colour_offset = 232;

// ==========================================================================
/// \brief Encode a greyscale value.
// ==========================================================================
constexpr byte encode_greyscale_component(byte grey) noexcept
{
    return greyscale_colour_offset + grey;
}

// ==========================================================================
/// \brief Extract a greyscale value.
// ==========================================================================
constexpr byte greyscale_component(byte value) noexcept
{
    return value - greyscale_colour_offset;
}

}  // namespace terminalpp::ansi::graphics
