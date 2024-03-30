#include "terminalpp/colour.hpp"

#include <boost/range/algorithm/find_if.hpp>
#include <fmt/format.h>

#include <iostream>

namespace terminalpp {

// ==========================================================================
// OPERATOR<<(STREAM, LOW_COLOUR)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, low_colour const &col)
{
    static constexpr struct
    {
        graphics::colour col;
        char const *text;
    } const colour_to_text[] = {
        {graphics::colour::black,    "black"  },
        {graphics::colour::red,      "red"    },
        {graphics::colour::green,    "green"  },
        {graphics::colour::yellow,   "yellow" },
        {graphics::colour::blue,     "blue"   },
        {graphics::colour::magenta,  "magenta"},
        {graphics::colour::cyan,     "cyan"   },
        {graphics::colour::white,    "white"  },
        {graphics::colour::default_, "default"}
    };

    auto const *result = boost::find_if(
        colour_to_text, [col](auto const &entry) { return col == entry.col; });

    return out
        << (result == std::cend(colour_to_text) ? "unknown" : result->text);
}

// ==========================================================================
// OPERATOR<<(STREAM, HIGH_COLOUR)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, high_colour const &col)
{
    byte const red = ansi::graphics::high_red_component(col.value_);
    byte const green = ansi::graphics::high_green_component(col.value_);
    byte const blue = ansi::graphics::high_blue_component(col.value_);

    return out << fmt::format(
               "#{}{}{}",
               static_cast<int>(red),
               static_cast<int>(green),
               static_cast<int>(blue));
}

// ==========================================================================
// OPERATOR<<(STREAM, GREYSCALE_COLOUR)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, greyscale_colour const &col)
{
    byte const shade = ansi::graphics::greyscale_component(col.shade_);
    return out << fmt::format("#{:02}", static_cast<int>(shade));
}

// ==========================================================================
// OPERATOR<<(STREAM, TRUE_COLOUR)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, true_colour const &col)
{
    return out << fmt::format(
               "#{:02X}{:02X}{:02X}",
               static_cast<int>(col.red_),
               static_cast<int>(col.green_),
               static_cast<int>(col.blue_));
}

// ==========================================================================
// OPERATOR<<(STREAM, COLOUR)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, colour const &col)
{
    std::visit([&out](auto const &value) { out << value; }, col.value_);
    return out;
}

}  // namespace terminalpp
