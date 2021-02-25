#include "terminalpp/colour.hpp"
#include <boost/range/algorithm/find_if.hpp>
#include <iostream>

namespace terminalpp {

// ==========================================================================
// OPERATOR<<(STREAM, LOW_COLOUR)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, low_colour const &col)
{
    static constexpr struct
    {
        colour_code col;
        char const *text;
    } const colour_to_text[] = {
        { colour_code::black,    "black"   },
        { colour_code::red,      "red"     },
        { colour_code::green,    "green"   },
        { colour_code::yellow,   "yellow"  },
        { colour_code::blue,     "blue"    },
        { colour_code::magenta,  "magenta" },
        { colour_code::cyan,     "cyan"    },
        { colour_code::white,    "white"   },
        { colour_code::default_, "default" }
    };

    auto result = boost::find_if(
        colour_to_text,
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
    byte const value = col.value_ - detail::high_colour_offset;
    byte const red   = ansi::graphics::high_red_component(value);
    byte const green = ansi::graphics::high_green_component(value);
    byte const blue  = ansi::graphics::high_blue_component(value);

    return out << "#"
               << std::to_string(int(red))
               << std::to_string(int(green))
               << std::to_string(int(blue));

}

// ==========================================================================
// OPERATOR<<(STREAM, GREYSCALE_COLOUR)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, greyscale_colour const &col)
{
    byte const shade = col.shade_ - detail::greyscale_colour_offset;
    return out << "#"
               << (shade < 10 ? "0" : "")
               << std::to_string(int(shade));
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

}
