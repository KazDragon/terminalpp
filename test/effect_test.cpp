#include "terminalpp/effect.hpp"
#include <gtest/gtest.h>
#include <tuple>
#include <unordered_set>

using testing::ValuesIn;

using intensity_string = std::tuple<terminalpp::intensity, std::string>;

class intensities_with_strings : public testing::TestWithParam<intensity_string>
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
    intensity_string{terminalpp::graphics::intensity::normal, "normal"},
    intensity_string{terminalpp::graphics::intensity::bold, "bold"},
    intensity_string{terminalpp::graphics::intensity::faint, "faint"}};

INSTANTIATE_TEST_SUITE_P(
    intensities_can_be_streamed_to_an_ostream,
    intensities_with_strings,
    ValuesIn(intensity_strings));

using underline_string = std::tuple<terminalpp::underlining, std::string>;

class underlines_with_strings : public testing::TestWithParam<underline_string>
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
    underline_string{
        terminalpp::graphics::underlining::underlined, "underlined"},
    underline_string{
        terminalpp::graphics::underlining::not_underlined, "not underlined"},
};

INSTANTIATE_TEST_SUITE_P(
    underlines_can_be_streamed_to_an_ostream,
    underlines_with_strings,
    ValuesIn(underline_strings));

using polarity_string = std::tuple<terminalpp::polarity, std::string>;

class polarities_with_strings : public testing::TestWithParam<polarity_string>
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
    polarity_string{terminalpp::graphics::polarity::positive, "positive"},
    polarity_string{terminalpp::graphics::polarity::negative, "negative"},
};

INSTANTIATE_TEST_SUITE_P(
    polarities_can_be_streamed_to_an_ostream,
    polarities_with_strings,
    ValuesIn(polarity_strings));

using blink_string = std::tuple<terminalpp::blinking, std::string>;

class blinking_with_strings : public testing::TestWithParam<blink_string>
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
    blink_string{terminalpp::graphics::blinking::blink, "blinking"},
    blink_string{terminalpp::graphics::blinking::steady, "steady"},
};

INSTANTIATE_TEST_SUITE_P(
    blinking_can_be_streamed_to_an_ostream,
    blinking_with_strings,
    ValuesIn(blink_strings));

TEST(an_effect, can_be_inserted_into_an_unordered_set)
{
  std::unordered_set<terminalpp::intensity> e{{}};
}
