#include <gtest/gtest.h>
#include <terminalpp/mouse.hpp>
#include <tuple>

using testing::ValuesIn;

TEST(a_default_constructed_mouse_event, has_known_values)
{
  terminalpp::mouse::event ev;

  ASSERT_EQ(terminalpp::mouse::event_type::no_button_change, ev.action_);
  ASSERT_EQ(0, ev.position_.x_);
  ASSERT_EQ(0, ev.position_.y_);
}

using mouse_event_test_data = std::tuple<
    terminalpp::mouse::event,  // input data
    std::string                // expected output
    >;

class mouse_events_with_strings
  : public testing::TestWithParam<mouse_event_test_data>
{
};

TEST_P(mouse_events_with_strings, can_be_streamed_to_an_ostream)
{
  auto const &param = GetParam();
  auto const &rep = std::get<0>(param);
  auto const &expected_string = std::get<1>(param);

  std::stringstream stream;
  std::ostream &out = stream;

  out << rep;
  ASSERT_EQ(expected_string, stream.str());
}

static mouse_event_test_data const mouse_event_strings[] = {
    // A default report should print out that no button has changed at (0,0)
    mouse_event_test_data{
        terminalpp::mouse::event{}, "mouse_event[point(0,0), no-change]"},

    // A report with different button states should print out those states
    mouse_event_test_data{
        terminalpp::mouse::event{
            terminalpp::mouse::event_type::left_button_down},
        "mouse_event[point(0,0), lmb]"},
    mouse_event_test_data{
        terminalpp::mouse::event{
            terminalpp::mouse::event_type::middle_button_down},
        "mouse_event[point(0,0), mmb]"},
    mouse_event_test_data{
        terminalpp::mouse::event{
            terminalpp::mouse::event_type::right_button_down},
        "mouse_event[point(0,0), rmb]"},
    mouse_event_test_data{
        terminalpp::mouse::event{terminalpp::mouse::event_type::button_up},
        "mouse_event[point(0,0), up]"},
    mouse_event_test_data{
        terminalpp::mouse::event{
            terminalpp::mouse::event_type::no_button_change},
        "mouse_event[point(0,0), no-change]"},
    mouse_event_test_data{
        terminalpp::mouse::event{
            terminalpp::mouse::event_type::scrollwheel_down},
        "mouse_event[point(0,0), sdn]"},
    mouse_event_test_data{
        terminalpp::mouse::event{terminalpp::mouse::event_type::scrollwheel_up},
        "mouse_event[point(0,0), sup]"},

    // Reports with different co-ordinates should output those values
    mouse_event_test_data{
        terminalpp::mouse::event{
            terminalpp::mouse::event_type::left_button_down, {15, 17}},
        "mouse_event[point(15,17), lmb]"},
};

INSTANTIATE_TEST_SUITE_P(
    mouse_events_can_be_streamed_to_an_ostream,
    mouse_events_with_strings,
    ValuesIn(mouse_event_strings));
