#include "terminalpp/effect.hpp"

#include <gtest/gtest.h>

#include <tuple>
#include <unordered_set>

using testing::ValuesIn;

namespace {

using intensity_string = std::tuple<terminalpp::intensity, std::string_view>;

class intensities_with_strings : public testing::TestWithParam<intensity_string>
{
};

TEST_P(intensities_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &[intensity, expected_string] = GetParam();

    std::stringstream stream;
    std::ostream &out = stream;

    out << intensity;
    ASSERT_EQ(expected_string, stream.str());
}

constexpr intensity_string intensity_strings[] = {
    {terminalpp::graphics::intensity::normal, "normal"},
    {terminalpp::graphics::intensity::bold,   "bold"  },
    {terminalpp::graphics::intensity::faint,  "faint" }
};

INSTANTIATE_TEST_SUITE_P(
    intensities_can_be_streamed_to_an_ostream,
    intensities_with_strings,
    ValuesIn(intensity_strings));

using underline_string = std::tuple<terminalpp::underlining, std::string_view>;

class underlines_with_strings : public testing::TestWithParam<underline_string>
{
};

TEST_P(underlines_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &[underline, expected_string] = GetParam();

    std::stringstream stream;
    std::ostream &out = stream;

    out << underline;
    ASSERT_EQ(expected_string, stream.str());
}

constexpr underline_string underline_strings[] = {
    {terminalpp::graphics::underlining::underlined,     "underlined"    },
    {terminalpp::graphics::underlining::not_underlined, "not underlined"},
};

INSTANTIATE_TEST_SUITE_P(
    underlines_can_be_streamed_to_an_ostream,
    underlines_with_strings,
    ValuesIn(underline_strings));

using polarity_string = std::tuple<terminalpp::polarity, std::string_view>;

class polarities_with_strings : public testing::TestWithParam<polarity_string>
{
};

TEST_P(polarities_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &[polarity, expected_string] = GetParam();

    std::stringstream stream;
    std::ostream &out = stream;

    out << polarity;
    ASSERT_EQ(expected_string, stream.str());
}

constexpr polarity_string polarity_strings[] = {
    {terminalpp::graphics::polarity::positive, "positive"},
    {terminalpp::graphics::polarity::negative, "negative"},
};

INSTANTIATE_TEST_SUITE_P(
    polarities_can_be_streamed_to_an_ostream,
    polarities_with_strings,
    ValuesIn(polarity_strings));

using blink_string = std::tuple<terminalpp::blinking, std::string_view>;

class blinking_with_strings : public testing::TestWithParam<blink_string>
{
};

TEST_P(blinking_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &[blink, expected_string] = GetParam();

    std::stringstream stream;
    std::ostream &out = stream;

    out << blink;
    ASSERT_EQ(expected_string, stream.str());
}

constexpr blink_string blink_strings[] = {
    {terminalpp::graphics::blinking::blink,  "blinking"},
    {terminalpp::graphics::blinking::steady, "steady"  },
};

INSTANTIATE_TEST_SUITE_P(
    blinking_can_be_streamed_to_an_ostream,
    blinking_with_strings,
    ValuesIn(blink_strings));

TEST(an_effect, can_be_inserted_into_an_unordered_set)
{
    std::unordered_set<terminalpp::intensity> e{{}};
}

}  // namespace
