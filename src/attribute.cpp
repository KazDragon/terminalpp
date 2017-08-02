#include "terminalpp/attribute.hpp"
#include <algorithm>
#include <ostream>

namespace terminalpp {

// ==========================================================================
// OPERATOR<<(STREAM, LOW_COLOUR)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, low_colour const &col)
{
    static constexpr struct
    {
        ansi::graphics::colour col;
        char const *text;
    } const colour_to_text[] = {
        { ansi::graphics::colour::black,    "black"   },
        { ansi::graphics::colour::red,      "red"     },
        { ansi::graphics::colour::green,    "green"   },
        { ansi::graphics::colour::yellow,   "yellow"  },
        { ansi::graphics::colour::blue,     "blue"    },
        { ansi::graphics::colour::magenta,  "magenta" },
        { ansi::graphics::colour::cyan,     "cyan"    },
        { ansi::graphics::colour::white,    "white"   },
        { ansi::graphics::colour::default_, "default" }
    };

    auto result = std::find_if(
        std::begin(colour_to_text),
        std::end(colour_to_text),
        [col](auto const &entry)
        {
            return col == entry.col;
        });

    return out << (result == std::end(colour_to_text)
                ? "unknown"
                : result->text);
}

// ==========================================================================
// OPERATOR<<(STREAM, HIGH_COLOUR)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, high_colour const &col)
{
    int const value = col.value_ - 16;
    int const red   = value / 36;
    int const green = (value % 36) / 6;
    int const blue  = value % 6;

    return out << "#"
               << std::to_string(red)
               << std::to_string(green)
               << std::to_string(blue);

}

// ==========================================================================
// OPERATOR<<(STREAM, GREYSCALE_COLOUR)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, greyscale_colour const &col)
{
    int const shade = col.shade_ - 232;
    return out << "#"
               << (shade < 10 ? "0" : "")
               << std::to_string(shade);
}

// ==========================================================================
// OPERATOR<<(STREAM, COLOUR)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, colour const &col)
{
    switch (col.type_)
    {
        default :
            // Fall-through
        case colour::type::low :
            return out << col.low_colour_;

        case colour::type::high :
            return out << col.high_colour_;

        case colour::type::greyscale :
            return out << col.greyscale_colour_;
    }
}

// ==========================================================================
// OPERATOR<<(STREAM, INTENSITY)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, intensity const &effect)
{
    switch (effect.value_)
    {
        default :
            // Fall-through
        case terminalpp::ansi::graphics::intensity::normal :
            return out << "normal";

        case terminalpp::ansi::graphics::intensity::bold :
            return out << "bold";

        case terminalpp::ansi::graphics::intensity::faint :
            return out << "faint";
    }
}

// ==========================================================================
// OPERATOR<<(STREAM, UNDERLINING)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, underlining const &effect)
{
    return out
        << (effect.value_ == terminalpp::ansi::graphics::underlining::underlined
          ? "underlined"
          : "not underlined");
}

// ==========================================================================
// OPERATOR<<(STREAM, POLARITY)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, polarity const &effect)
{
    return out
        << (effect.value_ == terminalpp::ansi::graphics::polarity::positive
          ? "positive"
          : "negative");
}

// ==========================================================================
// OPERATOR<<(STREAM, BLINKING)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, blinking const &effect)
{
    return out
        << (effect.value_ == terminalpp::ansi::graphics::blinking::blink
          ? "blinking"
          : "steady");
}

// ==========================================================================
// ==========================================================================
template <class T>
bool output_non_default_attribute(
    std::ostream &out,
    T const &value,
    bool with_comma,
    char const *prefix = "",
    char const *suffix = "")
{
    if (value != T())
    {
        if (with_comma)
        {
            out << ",";
        }

        out << prefix << value << suffix;
        return true;
    }
    else
    {
        return false;
    }
}

// ==========================================================================
// OPERATOR<<(STREAM, ATTRIBUTE)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, attribute const &attr)
{
    bool with_comma = false;

    with_comma |= output_non_default_attribute(out, attr.foreground_colour_, with_comma, "foreground[", "]");
    with_comma |= output_non_default_attribute(out, attr.background_colour_, with_comma, "background[", "]");
    with_comma |= output_non_default_attribute(out, attr.intensity_, with_comma);
    with_comma |= output_non_default_attribute(out, attr.underlining_, with_comma);
    with_comma |= output_non_default_attribute(out, attr.polarity_, with_comma);
    with_comma |= output_non_default_attribute(out, attr.blinking_, with_comma);

    return out;
}

}
