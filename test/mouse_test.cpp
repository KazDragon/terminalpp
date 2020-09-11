#include <terminalpp/ansi/mouse.hpp>
#include <gtest/gtest.h>
#include <tuple>

using testing::ValuesIn;

TEST(a_default_constructed_mouse_report, has_known_values)
{
    terminalpp::ansi::mouse::report report;

    ASSERT_EQ(terminalpp::ansi::mouse::report::NO_BUTTON_CHANGE, report.button_);
    ASSERT_EQ(0, report.x_position_);
    ASSERT_EQ(0, report.y_position_);
}

using mouse_report_test_data = std::tuple<
    terminalpp::ansi::mouse::report, // input data
    std::string                      // expected output
>;

class mouse_reports_with_strings
  : public testing::TestWithParam<mouse_report_test_data>
{
};

TEST_P(mouse_reports_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &rep   = std::get<0>(param);
    auto const &expected_string = std::get<1>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << rep;
    ASSERT_EQ(expected_string, stream.str());
}

static mouse_report_test_data const mouse_report_strings[] = {
    // A default report should print out that no button has changed at (0,0)
    mouse_report_test_data{
        terminalpp::ansi::mouse::report{},
        "mouse_report[0, 0, no-change]"
    },

    // A report with different button states should print out those states
    mouse_report_test_data{
        terminalpp::ansi::mouse::report{
            terminalpp::ansi::mouse::report::LEFT_BUTTON_DOWN
        },
        "mouse_report[0, 0, lmb]"
    },
    mouse_report_test_data{
        terminalpp::ansi::mouse::report{
            terminalpp::ansi::mouse::report::MIDDLE_BUTTON_DOWN
        },
        "mouse_report[0, 0, mmb]"
    },
    mouse_report_test_data{
        terminalpp::ansi::mouse::report{
            terminalpp::ansi::mouse::report::RIGHT_BUTTON_DOWN
        },
        "mouse_report[0, 0, rmb]"
    },
    mouse_report_test_data{
        terminalpp::ansi::mouse::report{
            terminalpp::ansi::mouse::report::BUTTON_UP
        },
        "mouse_report[0, 0, up]"
    },
    mouse_report_test_data{
        terminalpp::ansi::mouse::report{
            terminalpp::ansi::mouse::report::NO_BUTTON_CHANGE
        },
        "mouse_report[0, 0, no-change]"
    },
    mouse_report_test_data{
        terminalpp::ansi::mouse::report{
            terminalpp::ansi::mouse::report::SCROLLWHEEL_DOWN
        },
        "mouse_report[0, 0, sdn]"
    },
    mouse_report_test_data{
        terminalpp::ansi::mouse::report{
            terminalpp::ansi::mouse::report::SCROLLWHEEL_UP
        },
        "mouse_report[0, 0, sup]"
    },

    // Reports with different co-ordinates should output those values
    mouse_report_test_data{
        terminalpp::ansi::mouse::report{
            terminalpp::ansi::mouse::report::LEFT_BUTTON_DOWN,
            15, 17
        },
        "mouse_report[15, 17, lmb]"
    },
};

INSTANTIATE_TEST_SUITE_P(
    mouse_reports_can_be_streamed_to_an_ostream,
    mouse_reports_with_strings,
    ValuesIn(mouse_report_strings)
);

