#include "terminalpp/colour.hpp"
#include <gtest/gtest.h>
#include <tuple>
#include <unordered_set>

using testing::ValuesIn;

TEST(colour_test, can_construct_from_low_colour_enum)
{
    terminalpp::graphics::colour const col{terminalpp::graphics::colour::red};
    terminalpp::colour const expected_colour = terminalpp::low_colour(col);
    terminalpp::colour const result_colour{col};

    ASSERT_EQ(expected_colour, result_colour);
}

using low_colour_string = std::tuple<
    terminalpp::low_colour,
    std::string
>;

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

static low_colour_string const low_colour_strings[] = {
  low_colour_string{ terminalpp::graphics::colour::black,    "black"   },
  low_colour_string{ terminalpp::graphics::colour::red,      "red"     },
  low_colour_string{ terminalpp::graphics::colour::green,    "green"   },
  low_colour_string{ terminalpp::graphics::colour::yellow,   "yellow"  },
  low_colour_string{ terminalpp::graphics::colour::blue,     "blue"    },
  low_colour_string{ terminalpp::graphics::colour::magenta,  "magenta" },
  low_colour_string{ terminalpp::graphics::colour::cyan,     "cyan"    },
  low_colour_string{ terminalpp::graphics::colour::white,    "white"   },
  low_colour_string{ terminalpp::graphics::colour::default_, "default" }
};

INSTANTIATE_TEST_SUITE_P(
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

static high_colour_string const high_colour_strings[] = {
    high_colour_string{ 0, 0, 0, "#000" },
    high_colour_string{ 3, 0, 0, "#300" },
    high_colour_string{ 0, 4, 0, "#040" },
    high_colour_string{ 0, 0, 5, "#005" },
    high_colour_string{ 5, 3, 1, "#531" },
    high_colour_string{ 5, 5, 5, "#555" }
};

INSTANTIATE_TEST_SUITE_P(
    high_colours_can_be_streamed_to_an_ostream,
    high_colours_with_strings,
    ValuesIn(high_colour_strings)
);

using greyscale_string = std::tuple<
    terminalpp::byte,    // shade
    std::string          // expected output
>;

class greyscale_colours_with_strings
   : public testing::TestWithParam<greyscale_string>
{
};

TEST_P(greyscale_colours_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &shade = std::get<0>(param);
    auto const &expected_string = std::get<1>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << terminalpp::greyscale_colour(shade);
    ASSERT_EQ(expected_string, stream.str());
}

static greyscale_string const greyscale_strings[] = {
    greyscale_string{ 0,  "#00" },
    greyscale_string{ 9,  "#09" },
    greyscale_string{ 10, "#10" },
    greyscale_string{ 17, "#17" },
    greyscale_string{ 22, "#22" },
};

INSTANTIATE_TEST_SUITE_P(
    greyscale_colours_can_be_streamed_to_an_ostream,
    greyscale_colours_with_strings,
    ValuesIn(greyscale_strings)
);

using true_colour_string = std::tuple<
    terminalpp::byte,    // red
    terminalpp::byte,    // green
    terminalpp::byte,    // blue
    std::string          // expected output
>;

class true_colours_with_strings
  : public testing::TestWithParam<true_colour_string>
{
};

TEST_P(true_colours_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &red   = std::get<0>(param);
    auto const &green = std::get<1>(param);
    auto const &blue  = std::get<2>(param);
    auto const &expected_string = std::get<3>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << terminalpp::true_colour(red, green, blue);
    ASSERT_EQ(expected_string, stream.str());
}

static true_colour_string const true_colour_strings[] = {
    true_colour_string{ 0,   0,   0,   "#000000" },
    true_colour_string{ 80,  0,   0,   "#500000" },
    true_colour_string{ 0,   90,  0,   "#005A00" },
    true_colour_string{ 0,   0,   100, "#000064" },
    true_colour_string{ 40,  50,  60,  "#28323C" },
    true_colour_string{ 255, 255, 255, "#FFFFFF" },
};

INSTANTIATE_TEST_SUITE_P(
    true_colours_can_be_streamed_to_an_ostream,
    true_colours_with_strings,
    ValuesIn(true_colour_strings)
);

using colour_string = std::tuple<
    terminalpp::colour,
    std::string
>;

class colours_with_strings
   : public testing::TestWithParam<colour_string>
{
};

TEST_P(colours_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &colour = std::get<0>(param);
    auto const &expected_string = std::get<1>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << colour;
    ASSERT_EQ(expected_string, stream.str());
}

static colour_string const colour_strings[] = {
    colour_string{ terminalpp::graphics::colour::red,         "red"    },
    colour_string{ terminalpp::graphics::colour::green,       "green"  },
    colour_string{ terminalpp::high_colour(1, 2, 3),          "#123"   },
    colour_string{ terminalpp::high_colour(5, 5, 4),          "#554"   },
    colour_string{ terminalpp::greyscale_colour(0),           "#00"    },
    colour_string{ terminalpp::greyscale_colour(21),          "#21"    },
    colour_string{ terminalpp::true_colour(0xCD, 0x3B, 0x7A), "#CD3B7A"},
};

TEST(low_colours, can_be_inserted_into_an_unordered_set)
{
    std::unordered_set<terminalpp::low_colour> c { {} };
}

TEST(high_colours, can_be_inserted_into_an_unordered_set)
{
    std::unordered_set<terminalpp::high_colour> c { {} };
}

TEST(greyscale_colours, can_be_inserted_into_an_unordered_set)
{
    std::unordered_set<terminalpp::greyscale_colour> c { {} };
}

TEST(a_colour, can_be_inserted_into_an_unordered_set)
{
    std::unordered_set<terminalpp::colour> c { 
        terminalpp::low_colour{},
        terminalpp::high_colour{},
        terminalpp::greyscale_colour{} 
    };
}

INSTANTIATE_TEST_SUITE_P(
    colours_can_be_streamed_to_an_ostream,
    colours_with_strings,
    ValuesIn(colour_strings)
);

