#include "terminalpp/attribute.hpp"
#include <algorithm>
#include <ostream>

namespace terminalpp {

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

}
