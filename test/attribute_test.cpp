#include "terminalpp/attribute.hpp"

#include <gtest/gtest.h>

#include <tuple>
#include <unordered_set>

using testing::ValuesIn;

namespace {

using attribute_string = std::tuple<terminalpp::attribute, std::string_view>;

class attributes_with_strings : public testing::TestWithParam<attribute_string>
{
};

TEST_P(attributes_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &[attr, expected_string] = GetParam();

    std::stringstream stream;
    std::ostream &out = stream;

    out << attr;
    ASSERT_EQ(expected_string, stream.str());
}

constexpr attribute_string attribute_strings[] = {
    // All defaults
    {},

    // One non-default value
    {{.foreground_colour_ = terminalpp::graphics::colour::red},
     "foreground[red]"},
    {{.background_colour_ = terminalpp::high_colour(1, 2, 3)},
     "background[#123]"},
    {{.intensity_ = terminalpp::graphics::intensity::bold}, "bold"},
    {{.underlining_ = terminalpp::graphics::underlining::underlined},
     "underlined"},
    {{.polarity_ = terminalpp::graphics::polarity::negative}, "negative"},
    {{.blinking_ = terminalpp::graphics::blinking::blink}, "blinking"},

    // Many non-default values
    {{.background_colour_ = terminalpp::greyscale_colour(7),
      .underlining_ = terminalpp::graphics::underlining::underlined},
     "background[#07],underlined"},
    {{.background_colour_ = terminalpp::graphics::colour::green,
      .underlining_ = terminalpp::graphics::underlining::not_underlined,
      .polarity_ = terminalpp::graphics::polarity::negative,
      .blinking_ = terminalpp::graphics::blinking::blink},
     "background[green],negative,blinking"},
};

INSTANTIATE_TEST_SUITE_P(
    attributes_can_be_streamed_to_an_ostream,
    attributes_with_strings,
    ValuesIn(attribute_strings));

TEST(an_attribute, can_be_inserted_into_an_unordered_set)
{
    std::unordered_set<terminalpp::attribute> a{{}};
}

}  // namespace
