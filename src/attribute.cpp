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

}
