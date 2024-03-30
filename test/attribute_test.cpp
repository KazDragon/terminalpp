#include "terminalpp/attribute.hpp"

#include <gtest/gtest.h>

#include <tuple>
#include <unordered_set>

using testing::ValuesIn;

using attribute_string = std::tuple<terminalpp::attribute, std::string>;

class attributes_with_strings : public testing::TestWithParam<attribute_string>
{
};

TEST_P(attributes_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &attr = std::get<0>(param);
    auto const &expected_string = std::get<1>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << attr;
    ASSERT_EQ(expected_string, stream.str());
}

static attribute_string const attribute_strings[] = {
  // All defaults
    attribute_string{},

 // One non-default value
    attribute_string{
                     terminalpp::attribute{
            terminalpp::colour{terminalpp::graphics::colour::red}},
                     "foreground[red]"},
    attribute_string{
                     terminalpp::attribute{
            {}, terminalpp::colour{terminalpp::high_colour(1, 2, 3)}},
                     "background[#123]"},
    attribute_string{
                     terminalpp::attribute{{}, {}, terminalpp::graphics::intensity::bold},
                     "bold"},
    attribute_string{
                     terminalpp::attribute{
            {}, {}, {}, terminalpp::graphics::underlining::underlined},
                     "underlined"},
    attribute_string{
                     terminalpp::attribute{
            {}, {}, {}, {}, terminalpp::graphics::polarity::negative},
                     "negative"},
    attribute_string{
                     terminalpp::attribute{
            {}, {}, {}, {}, {}, terminalpp::graphics::blinking::blink},
                     "blinking"},

 // Many non-default values
    attribute_string{
                     terminalpp::attribute{
            {},
            terminalpp::greyscale_colour(7),
            {},
            terminalpp::graphics::underlining::underlined},
                     "background[#07],underlined"},
    attribute_string{
                     terminalpp::attribute{
            {},
            terminalpp::graphics::colour::green,
            {},
            terminalpp::graphics::underlining::not_underlined,
            terminalpp::graphics::polarity::negative,
            terminalpp::graphics::blinking::blink},
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