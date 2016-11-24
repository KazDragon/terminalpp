#include "terminalpp/attribute.hpp"
#include <iostream>

namespace terminalpp {

static const auto default_colour =
    low_colour(terminalpp::ansi::graphics::colour::default_);

// ==========================================================================
// STREAM OPERATOR
// ==========================================================================
std::ostream &operator<<(std::ostream &out, low_colour const &col)
{
    switch (col.value_)
    {
        default :
            // Fall-through
        case terminalpp::ansi::graphics::colour::default_ :
            out << "default";
            break;

        case terminalpp::ansi::graphics::colour::black :
            out << "black";
            break;

        case terminalpp::ansi::graphics::colour::red :
            out << "red";
            break;

        case terminalpp::ansi::graphics::colour::green :
            out << "green";
            break;

        case terminalpp::ansi::graphics::colour::yellow :
            out << "yellow";
            break;

        case terminalpp::ansi::graphics::colour::blue :
            out << "blue";
            break;

        case terminalpp::ansi::graphics::colour::magenta :
            out << "magenta";
            break;

        case terminalpp::ansi::graphics::colour::cyan :
            out << "cyan";
            break;

        case terminalpp::ansi::graphics::colour::white :
            out << "white";
            break;
    }

    return out;
}

// ==========================================================================
// STREAM OPERATOR
// ==========================================================================
std::ostream &operator<<(std::ostream &out, high_colour const &col)
{
    // Offset for normal ANSI colours.
    int const colour_value = col.value_ - 16;

    int const red_value = (colour_value / 36) % 6;
    int const green_value = (colour_value / 6) % 6;
    int const blue_value = colour_value % 6;

    out << "R:" << red_value << ","
        << "G:" << green_value << ","
        << "B:" << blue_value;

    return out;
}

// ==========================================================================
// STREAM OPERATOR
// ==========================================================================
std::ostream &operator<<(std::ostream &out, greyscale_colour const &col)
{
    out << "grey:" << col.shade_ - 232;
    return out;
}

// ==========================================================================
// STREAM OPERATOR
// ==========================================================================
std::ostream &operator<<(std::ostream &out, colour const &col)
{
    out << "colour[";

    switch (col.type_)
    {
        case colour::type::low :
            out << col.low_colour_;
            break;

        case colour::type::high :
            out << col.high_colour_;
            break;

        case colour::type::greyscale :
            out << col.greyscale_colour_;
            break;

        default :
            break;
    }

    out << "]";

    return out;
}

// ==========================================================================
// APPEND_COMMA_IF_NECESSARY
// ==========================================================================
static void append_comma_if_necessary(std::ostream &out, bool necessary)
{
    if (necessary)
    {
        out << ",";
    }
}

// ==========================================================================
// APPEND_FOREGROUND_COLOUR
// ==========================================================================
static void append_foreground_colour(
    std::ostream &out,
    attribute const &attr,
    bool &comma)
{
    if (attr.foreground_colour_ != default_colour)
    {
        append_comma_if_necessary(out, comma);
        out << "fg:" << attr.foreground_colour_;
        comma = true;
    }
}

// ==========================================================================
// APPEND_BACKGROUND_COLOUR
// ==========================================================================
static void append_background_colour(
    std::ostream &out,
    attribute const &attr,
    bool &comma)
{
    if (attr.background_colour_ != default_colour)
    {
        append_comma_if_necessary(out, comma);
        out << "fg:" << attr.background_colour_;
        comma = true;
    }
}

// ==========================================================================
// APPEND_INTENSITY
// ==========================================================================
static void append_intensity(
    std::ostream &out,
    attribute const &attr,
    bool &comma)
{
    static const auto default_intensity =
        terminalpp::ansi::graphics::intensity::normal;

    if (attr.intensity_ != default_intensity)
    {
        append_comma_if_necessary(out, comma);

        if (attr.intensity_ == ansi::graphics::intensity::bold)
        {
            out << "bold";
        }
        else if (attr.intensity_ == ansi::graphics::intensity::faint)
        {
            out << "faint";
        }

        comma = true;
    }
}

// ==========================================================================
// APPEND_UNDERLINING
// ==========================================================================
static void append_underlining(
    std::ostream &out,
    attribute const &attr,
    bool &comma)
{
    static const auto default_underlining =
        terminalpp::ansi::graphics::underlining::not_underlined;

    if (attr.underlining_ != default_underlining)
    {
        append_comma_if_necessary(out, comma);

        if (attr.underlining_ == ansi::graphics::underlining::underlined)
        {
            out << "underlined";
        }

        comma = true;
    }
}

// ==========================================================================
// APPEND_POLARITY
// ==========================================================================
static void append_polarity(
    std::ostream &out,
    attribute const &attr,
    bool &comma)
{
    static const auto default_polarity =
        terminalpp::ansi::graphics::polarity::positive;

    if (attr.polarity_ != default_polarity)
    {
        append_comma_if_necessary(out, comma);

        if (attr.polarity_ == ansi::graphics::polarity::negative)
        {
            out << "inverse";
        }

        comma = true;
    }
}

// ==========================================================================
// APPEND_BLINKING
// ==========================================================================
static void append_blinking(
    std::ostream &out,
    attribute const &attr,
    bool &comma)
{
    static const auto default_blinking =
        terminalpp::ansi::graphics::blinking::steady;

    if (attr.blinking_ != default_blinking)
    {
        append_comma_if_necessary(out, comma);

        if (attr.blinking_ == ansi::graphics::blinking::blink)
        {
            out << "blinking";
        }

        comma = true;
    }
}

// ==========================================================================
// STREAM OPERATOR
// ==========================================================================
std::ostream &operator<<(std::ostream &out, attribute const &attr)
{
    bool comma = false;

    out << "attr[";

    append_foreground_colour(out, attr, comma);
    append_background_colour(out, attr, comma);
    append_intensity(out, attr, comma);
    append_underlining(out, attr, comma);
    append_polarity(out, attr, comma);
    append_blinking(out, attr, comma);

    out << "]";

    return out;
}

}
