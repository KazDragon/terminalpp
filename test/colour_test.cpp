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

    out << terminalpp::low_colour(low_colour);
    ASSERT_EQ(expected_string, stream.str());
}

INSTANTIATE_TEST_CASE_P(
    low_colours_can_be_streamed_to_an_ostream,
    low_colours_with_strings,
    ValuesIn(low_colour_strings)
);

using high_colour_string = std::tuple<
    terminalpp::byte,    // red
    terminalpp::byte,    // green
    terminalpp::byte,    // blue
    std::string          // expected output
>;

static high_colour_string const high_colour_strings[] = {
    high_colour_string{ 0, 0, 0, "#000" },
    high_colour_string{ 3, 0, 0, "#300" },
    high_colour_string{ 0, 4, 0, "#040" },
    high_colour_string{ 0, 0, 5, "#005" },
    high_colour_string{ 5, 3, 1, "#531" }
};

class high_colours_with_strings
  : public testing::TestWithParam<high_colour_string>
{
};

TEST_P(high_colours_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &red   = std::get<0>(param);
    auto const &green = std::get<1>(param);
    auto const &blue  = std::get<2>(param);
    auto const &expected_string = std::get<3>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << terminalpp::high_colour(red, green, blue);
    ASSERT_EQ(expected_string, stream.str());
}

INSTANTIATE_TEST_CASE_P(
    high_colours_can_be_streamed_to_an_ostream,
    high_colours_with_strings,
    ValuesIn(high_colour_strings)
);
