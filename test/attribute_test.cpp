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
    high_colour_string{ 5, 3, 1, "#531" }
};

INSTANTIATE_TEST_CASE_P(
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

INSTANTIATE_TEST_CASE_P(
    greyscale_colours_can_be_streamed_to_an_ostream,
    greyscale_colours_with_strings,
    ValuesIn(greyscale_strings)
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
    colour_string{ terminalpp::ansi::graphics::colour::red,   "red"   },
    colour_string{ terminalpp::ansi::graphics::colour::green, "green" },
    colour_string{ terminalpp::high_colour(1, 2, 3),          "#123"  },
    colour_string{ terminalpp::high_colour(5, 5, 4),          "#554"  },
    colour_string{ terminalpp::greyscale_colour(0),           "#00"   },
    colour_string{ terminalpp::greyscale_colour(21),          "#21"   },
};

INSTANTIATE_TEST_CASE_P(
    colours_can_be_streamed_to_an_ostream,
    colours_with_strings,
    ValuesIn(colour_strings)
);

using intensity_string = std::tuple<
    terminalpp::intensity,
    std::string
>;

class intensities_with_strings
   : public testing::TestWithParam<intensity_string>
{
};

TEST_P(intensities_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &intensity = std::get<0>(param);
    auto const &expected_string = std::get<1>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << intensity;
    ASSERT_EQ(expected_string, stream.str());
}

static intensity_string const intensity_strings[] = {
    intensity_string{ terminalpp::ansi::graphics::intensity::normal,   "normal" },
    intensity_string{ terminalpp::ansi::graphics::intensity::bold,     "bold"   },
    intensity_string{ terminalpp::ansi::graphics::intensity::faint,    "faint"  }
};

INSTANTIATE_TEST_CASE_P(
    intensities_can_be_streamed_to_an_ostream,
    intensities_with_strings,
    ValuesIn(intensity_strings)
);

using underline_string = std::tuple<
    terminalpp::underlining,
    std::string
>;

class underlines_with_strings
   : public testing::TestWithParam<underline_string>
{
};

TEST_P(underlines_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &underline = std::get<0>(param);
    auto const &expected_string = std::get<1>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << underline;
    ASSERT_EQ(expected_string, stream.str());
}

static underline_string const underline_strings[] = {
    underline_string{ terminalpp::ansi::graphics::underlining::underlined,     "underlined"     },
    underline_string{ terminalpp::ansi::graphics::underlining::not_underlined, "not underlined" },
};

INSTANTIATE_TEST_CASE_P(
    underlines_can_be_streamed_to_an_ostream,
    underlines_with_strings,
    ValuesIn(underline_strings)
);

using polarity_string = std::tuple<
    terminalpp::polarity,
    std::string
>;

class polarities_with_strings
   : public testing::TestWithParam<polarity_string>
{
};

TEST_P(polarities_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &polarity = std::get<0>(param);
    auto const &expected_string = std::get<1>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << polarity;
    ASSERT_EQ(expected_string, stream.str());
}

static polarity_string const polarity_strings[] = {
    polarity_string{ terminalpp::ansi::graphics::polarity::positive, "positive" },
    polarity_string{ terminalpp::ansi::graphics::polarity::negative, "negative" },
};

INSTANTIATE_TEST_CASE_P(
    polarities_can_be_streamed_to_an_ostream,
    polarities_with_strings,
    ValuesIn(polarity_strings)
);

using blink_string = std::tuple<
    terminalpp::blinking,
    std::string
>;

class blinking_with_strings
   : public testing::TestWithParam<blink_string>
{
};

TEST_P(blinking_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &blink = std::get<0>(param);
    auto const &expected_string = std::get<1>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << blink;
    ASSERT_EQ(expected_string, stream.str());
}

static blink_string const blink_strings[] = {
    blink_string{ terminalpp::ansi::graphics::blinking::blink,  "blinking" },
    blink_string{ terminalpp::ansi::graphics::blinking::steady, "steady"   },
};

INSTANTIATE_TEST_CASE_P(
    blinking_can_be_streamed_to_an_ostream,
    blinking_with_strings,
    ValuesIn(blink_strings)
);

using attribute_string = std::tuple<
    terminalpp::attribute,
    std::string
>;

class attributes_with_strings
   : public testing::TestWithParam<attribute_string>
{
};

TEST_P(attributes_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &attr  = std::get<0>(param);
    auto const &expected_string = std::get<1>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << attr;
    ASSERT_EQ(expected_string, stream.str());
}

static attribute_string const attribute_strings[] = {
    // All defaults
    attribute_string { {},  "" },

    // One non-default value
    attribute_string {
        terminalpp::attribute {
            terminalpp::colour{ terminalpp::ansi::graphics::colour::red }
        },
        "foreground[red]"
    },
    attribute_string {
        terminalpp::attribute {
            {},
            terminalpp::colour{ terminalpp::high_colour(1, 2, 3) }
        },
        "background[#123]"
    },
    attribute_string {
        terminalpp::attribute {
            {},
            {},
            terminalpp::ansi::graphics::intensity::bold
        },
        "bold"
    },
    attribute_string {
        terminalpp::attribute {
            {},
            {},
            {},
            terminalpp::ansi::graphics::underlining::underlined
        },
        "underlined"
    },
    attribute_string {
        terminalpp::attribute {
            {},
            {},
            {},
            {},
            terminalpp::ansi::graphics::polarity::negative
        },
        "negative"
    },
    attribute_string {
        terminalpp::attribute {
            {},
            {},
            {},
            {},
            {},
            terminalpp::ansi::graphics::blinking::blink
        },
        "blinking"
    },

    // Many non-default values
    attribute_string {
        terminalpp::attribute {
            {},
            terminalpp::greyscale_colour(7),
            {},
            terminalpp::ansi::graphics::underlining::underlined
        },
        "background[#07],underlined"
    },
    attribute_string {
        terminalpp::attribute {
            {},
            terminalpp::ansi::graphics::colour::green,
            {},
            terminalpp::ansi::graphics::underlining::not_underlined,
            terminalpp::ansi::graphics::polarity::negative,
            terminalpp::ansi::graphics::blinking::blink
        },
        "background[green],negative,blinking"
    },
};

INSTANTIATE_TEST_CASE_P(
    attributes_can_be_streamed_to_an_ostream,
    attributes_with_strings,
    ValuesIn(attribute_strings)
);
