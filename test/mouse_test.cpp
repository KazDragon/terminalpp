#include <gtest/gtest.h>
#include <terminalpp/mouse.hpp>

#include <tuple>

namespace {

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
    std::string_view           // expected output
    >;

class mouse_events_with_strings
  : public testing::TestWithParam<mouse_event_test_data>
{
};

TEST_P(mouse_events_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &[rep, expected_string] = GetParam();

    std::stringstream stream;
    std::ostream &out = stream;

    out << rep;
    ASSERT_EQ(expected_string, stream.str());
}

constexpr mouse_event_test_data const mouse_event_strings[] = {
    // A default report should print out that no button has changed at (0,0)
    {terminalpp::mouse::event{},                                             "mouse_event[point(0,0), no-change]"},

    // A report with different button states should print out those states
    {terminalpp::mouse::event{
         .action_ = terminalpp::mouse::event_type::left_button_down},
     "mouse_event[point(0,0), lmb]"                                                                              },
    {terminalpp::mouse::event{
         .action_ = terminalpp::mouse::event_type::middle_button_down},
     "mouse_event[point(0,0), mmb]"                                                                              },
    {terminalpp::mouse::event{
         .action_ = terminalpp::mouse::event_type::right_button_down},
     "mouse_event[point(0,0), rmb]"                                                                              },
    {terminalpp::mouse::event{
         .action_ = terminalpp::mouse::event_type::button_up},
     "mouse_event[point(0,0), up]"                                                                               },
    {terminalpp::mouse::event{
         .action_ = terminalpp::mouse::event_type::no_button_change},
     "mouse_event[point(0,0), no-change]"                                                                        },
    {terminalpp::mouse::event{
         .action_ = terminalpp::mouse::event_type::scrollwheel_down},
     "mouse_event[point(0,0), sdn]"                                                                              },
    {terminalpp::mouse::event{
         .action_ = terminalpp::mouse::event_type::scrollwheel_up},
     "mouse_event[point(0,0), sup]"                                                                              },

    // Reports with different co-ordinates should output those values
    {terminalpp::mouse::event{
         .action_ = terminalpp::mouse::event_type::left_button_down,
         .position_ = {15, 17}},
     "mouse_event[point(15,17), lmb]"                                                                            },
};

INSTANTIATE_TEST_SUITE_P(
    mouse_events_can_be_streamed_to_an_ostream,
    mouse_events_with_strings,
    ValuesIn(mouse_event_strings));

}  // namespace
