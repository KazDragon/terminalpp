#include "terminalpp/colour.hpp"

#include <gtest/gtest.h>

#include <tuple>
#include <unordered_set>

using testing::ValuesIn;

namespace {

TEST(colour_test, can_construct_from_low_colour_enum)
{
    terminalpp::graphics::colour const col{terminalpp::graphics::colour::red};
    terminalpp::colour const expected_colour = terminalpp::low_colour(col);
    terminalpp::colour const result_colour{col};

    ASSERT_EQ(expected_colour, result_colour);
}

using low_colour_string = std::tuple<terminalpp::low_colour, std::string_view>;

class low_colours_with_strings
  : public testing::TestWithParam<low_colour_string>
{
};

TEST_P(low_colours_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &[low_colour, expected_string] = GetParam();

    std::stringstream stream;
    std::ostream &out = stream;

    out << terminalpp::low_colour(low_colour);
    ASSERT_EQ(expected_string, stream.str());
}

constexpr low_colour_string low_colour_strings[] = {
    // clang-format off
    { terminalpp::graphics::colour::black,    "black"   },
    { terminalpp::graphics::colour::red,      "red"     },
    { terminalpp::graphics::colour::green,    "green"   },
    { terminalpp::graphics::colour::yellow,   "yellow"  },
    { terminalpp::graphics::colour::blue,     "blue"    },
    { terminalpp::graphics::colour::magenta,  "magenta" },
    { terminalpp::graphics::colour::cyan,     "cyan"    },
    { terminalpp::graphics::colour::white,    "white"   },
    { terminalpp::graphics::colour::default_, "default" }
    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(
    low_colours_can_be_streamed_to_an_ostream,
    low_colours_with_strings,
    ValuesIn(low_colour_strings));

using high_colour_string = std::tuple<
    terminalpp::byte,  // red
    terminalpp::byte,  // green
    terminalpp::byte,  // blue
    std::string        // expected output
    >;

class high_colours_with_strings
  : public testing::TestWithParam<high_colour_string>
{
};

TEST_P(high_colours_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &[red, green, blue, expected_string] = GetParam();

    std::stringstream stream;
    std::ostream &out = stream;

    out << terminalpp::high_colour(red, green, blue);
    ASSERT_EQ(expected_string, stream.str());
}

constexpr high_colour_string high_colour_strings[] = {
    {0, 0, 0, "#000"},
    {3, 0, 0, "#300"},
    {0, 4, 0, "#040"},
    {0, 0, 5, "#005"},
    {5, 3, 1, "#531"},
    {5, 5, 5, "#555"}
};

INSTANTIATE_TEST_SUITE_P(
    high_colours_can_be_streamed_to_an_ostream,
    high_colours_with_strings,
    ValuesIn(high_colour_strings));

using greyscale_string = std::tuple<
    terminalpp::byte,  // shade
    std::string        // expected output
    >;

class greyscale_colours_with_strings
  : public testing::TestWithParam<greyscale_string>
{
};

TEST_P(greyscale_colours_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &[shade, expected_string] = GetParam();

    std::stringstream stream;
    std::ostream &out = stream;

    out << terminalpp::greyscale_colour(shade);
    ASSERT_EQ(expected_string, stream.str());
}

constexpr greyscale_string greyscale_strings[] = {
    // clang-format off
    { 0,  "#00" },
    { 9,  "#09" },
    { 10, "#10" },
    { 17, "#17" },
    { 22, "#22" },
    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(
    greyscale_colours_can_be_streamed_to_an_ostream,
    greyscale_colours_with_strings,
    ValuesIn(greyscale_strings));

using true_colour_string = std::tuple<
    terminalpp::byte,  // red
    terminalpp::byte,  // green
    terminalpp::byte,  // blue
    std::string        // expected output
    >;

class true_colours_with_strings
  : public testing::TestWithParam<true_colour_string>
{
};

TEST_P(true_colours_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &[red, green, blue, expected_string] = GetParam();

    std::stringstream stream;
    std::ostream &out = stream;

    out << terminalpp::true_colour(red, green, blue);
    ASSERT_EQ(expected_string, stream.str());
}

constexpr true_colour_string true_colour_strings[] = {
    // clang-format off
    { 0,   0,   0,   "#000000" },
    { 80,  0,   0,   "#500000" },
    { 0,   90,  0,   "#005A00" },
    { 0,   0,   100, "#000064" },
    { 40,  50,  60,  "#28323C" },
    { 255, 255, 255, "#FFFFFF" },
    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(
    true_colours_can_be_streamed_to_an_ostream,
    true_colours_with_strings,
    ValuesIn(true_colour_strings));

using colour_string = std::tuple<terminalpp::colour, std::string_view>;

class colours_with_strings : public testing::TestWithParam<colour_string>
{
};

TEST_P(colours_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &[colour, expected_string] = GetParam();

    std::stringstream stream;
    std::ostream &out = stream;

    out << colour;
    ASSERT_EQ(expected_string, stream.str());
}

constexpr colour_string colour_strings[] = {
    {terminalpp::graphics::colour::red, "red"},
    {terminalpp::graphics::colour::green, "green"},
    {terminalpp::high_colour(1, 2, 3), "#123"},
    {terminalpp::high_colour(5, 5, 4), "#554"},
    {terminalpp::greyscale_colour(0), "#00"},
    {terminalpp::greyscale_colour(21), "#21"},
    {terminalpp::true_colour(0xCD, 0x3B, 0x7A), "#CD3B7A"},
};

TEST(low_colours, can_be_inserted_into_an_unordered_set)
{
    std::unordered_set<terminalpp::low_colour> c{{}};
}

TEST(high_colours, can_be_inserted_into_an_unordered_set)
{
    std::unordered_set<terminalpp::high_colour> c{{}};
}

TEST(greyscale_colours, can_be_inserted_into_an_unordered_set)
{
    std::unordered_set<terminalpp::greyscale_colour> c{{}};
}

TEST(true_colours, can_be_inserted_into_an_unordered_set)
{
    std::unordered_set<terminalpp::true_colour> c{{}};
}

TEST(a_colour, can_be_inserted_into_an_unordered_set)
{
    std::unordered_set<terminalpp::colour> c{
        terminalpp::low_colour{},
        terminalpp::high_colour{},
        terminalpp::greyscale_colour{},
        terminalpp::true_colour{}};
}

INSTANTIATE_TEST_SUITE_P(
    colours_can_be_streamed_to_an_ostream,
    colours_with_strings,
    ValuesIn(colour_strings));

}  // namespace
