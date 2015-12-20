#include "terminalpp/terminal.hpp"
#include "expect_sequence.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(terminal_settings_test, enabling_mouse_mode_with_default_behaviour_sends_nothing)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string(""),
        terminal.enable_mouse());
}

TEST(terminal_settings_test, enabling_mouse_mode_with_basic_mouse_support_sends_basic_mouse_tracking)
{
    terminalpp::terminal::behaviour behaviour;
    behaviour.supports_basic_mouse_tracking = true;

    terminalpp::terminal terminal(behaviour);

    expect_sequence(
        std::string("\x1B[?1000h"),
        terminal.enable_mouse());
}

TEST(terminal_settings_test, enabling_mouse_mode_with_all_mouse_tracking_support_sends_all_mouse_tracking)
{
    terminalpp::terminal::behaviour behaviour;
    behaviour.supports_all_mouse_motion_tracking = true;
    terminalpp::terminal terminal(behaviour);

    expect_sequence(
        std::string("\x1B[?1003h"),
        terminal.enable_mouse());
}

TEST(terminal_settings_test, setting_window_title_with_default_behaviour_sends_nothing)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string(""),
        terminal.set_window_title("title"));
}

TEST(terminal_settings_test, setting_window_title_with_bel_behaviour_sends_window_title_with_bel)
{
    terminalpp::terminal::behaviour behaviour;
    behaviour.supports_window_title_bel = true;
    terminalpp::terminal terminal(behaviour);

    expect_sequence(
        std::string("\x1B]2;title\x7"),
        terminal.set_window_title("title"));
}

TEST(terminal_settings_test, setting_window_title_with_st_behaviour_sends_window_title_with_st)
{
    terminalpp::terminal::behaviour behaviour;
    behaviour.supports_window_title_st = true;
    terminalpp::terminal terminal(behaviour);

    expect_sequence(
        std::string("\x1B]2;title\x1B\\"),
        terminal.set_window_title("title"));
}
