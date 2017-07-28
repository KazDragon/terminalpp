#include "terminalpp/attribute.hpp"
#include <gtest/gtest.h>
#include <tuple>

using testing::ValuesIn;

TEST(colour_test, can_construct_from_low_colour_enum)
{
    terminalpp::ansi::graphics::colour col(
        terminalpp::ansi::graphics::colour::red);

    terminalpp::colour expected_colour = terminalpp::low_colour(col);

    auto result_colour = [](terminalpp::colour const &col)
    {
        return col;
    }(col);

    ASSERT_EQ(expected_colour, result_colour);
}

using low_colour_string = std::tuple<
    terminalpp::low_colour,
    std::string
>;

static low_colour_string const low_colour_strings[] = {
  low_colour_string{ terminalpp::ansi::graphics::colour::black,    "black"   },
  low_colour_string{ terminalpp::ansi::graphics::colour::red,      "red"     },
  low_colour_string{ terminalpp::ansi::graphics::colour::green,    "green"   },
  low_colour_string{ terminalpp::ansi::graphics::colour::yellow,   "yellow"  },
  low_colour_string{ terminalpp::ansi::graphics::colour::blue,     "blue"    },
  low_colour_string{ terminalpp::ansi::graphics::colour::magenta,  "magenta" },
  low_colour_string{ terminalpp::ansi::graphics::colour::cyan,     "cyan"    },
  low_colour_string{ terminalpp::ansi::graphics::colour::white,    "white"   },
  low_colour_string{ terminalpp::ansi::graphics::colour::default_, "default" }
};

class low_colours_with_strings
    : public testing::TestWithParam<low_colour_string>
{
};

TEST_P(low_colours_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &low_colour = std::get<0>(param);
    auto const &expected_string = std::get<1>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << low_colour;
    ASSERT_EQ(expected_string, stream.str());
}

INSTANTIATE_TEST_CASE_P(
    low_colours_can_be_streamed_to_an_ostream,
    low_colours_with_strings,
    ValuesIn(low_colour_strings)
);
