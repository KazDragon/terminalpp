#include "terminalpp/attribute.hpp"
#include <iostream>

namespace terminalpp {

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
// STREAM OPERATOR
// ==========================================================================
std::ostream &operator<<(std::ostream &out, attribute const &attr)
{
    out << "attr[";

    // TODO: add attributes.

    out << "]";

    return out;
}

}
