#include "terminalpp/default_terminal.hpp"
#include "expect_sequence.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(enabling_mouse_mode_with_default_behaviour, sends_nothing)
{
    terminalpp::default_terminal terminal;

    expect_sequence(
        std::string(""),
        terminal.enable_mouse());
}

TEST(disabling_mouse_mode_with_default_behaviour, sends_nothing)
{
    terminalpp::default_terminal terminal;

    expect_sequence(
        std::string(""),
        terminal.disable_mouse());
}

TEST(enabling_mouse_mode_with_basic_mouse_support, sends_enable_basic_mouse_tracking)
{
    terminalpp::behaviour behaviour;
    behaviour.supports_basic_mouse_tracking = true;

    terminalpp::default_terminal terminal(behaviour);

    expect_sequence(
        std::string("\x1B[?1000h"),
        terminal.enable_mouse());
}

TEST(disabling_mouse_mode_with_basic_mouse_support, sends_disable_basic_mouse_tracking)
{
    terminalpp::behaviour behaviour;
    behaviour.supports_basic_mouse_tracking = true;

    terminalpp::default_terminal terminal(behaviour);

    expect_sequence(
        std::string("\x1B[?1000l"),
        terminal.disable_mouse());
}

TEST(enabling_mouse_mode_with_all_mouse_tracking_support, sends_enable_all_mouse_tracking)
{
    terminalpp::behaviour behaviour;
    behaviour.supports_all_mouse_motion_tracking = true;
    terminalpp::default_terminal terminal(behaviour);

    expect_sequence(
        std::string("\x1B[?1003h"),
        terminal.enable_mouse());
}

TEST(disabling_mouse_mode_with_all_mouse_tracking_support, sends_disable_all_mouse_tracking)
{
    terminalpp::behaviour behaviour;
    behaviour.supports_all_mouse_motion_tracking = true;
    terminalpp::default_terminal terminal(behaviour);

    expect_sequence(
        std::string("\x1B[?1003l"),
        terminal.disable_mouse());
}

TEST(setting_window_title_with_default_behaviour, sends_nothing)
{
    terminalpp::default_terminal terminal;

    expect_sequence(
        std::string(""),
        terminal.set_window_title("title"));
}

TEST(setting_window_title_with_bel_behaviour, sends_window_title_with_bel)
{
    terminalpp::behaviour behaviour;
    behaviour.supports_window_title_bel = true;
    terminalpp::default_terminal terminal(behaviour);

    expect_sequence(
        std::string("\x1B]2;title\x7"),
        terminal.set_window_title("title"));
}

TEST(setting_window_title_with_st_behaviour, sends_window_title_with_st)
{
    terminalpp::behaviour behaviour;
    behaviour.supports_window_title_st = true;
    terminalpp::default_terminal terminal(behaviour);

    expect_sequence(
        std::string("\x1B]2;title\x1B\\"),
        terminal.set_window_title("title"));
}

TEST(activating_normal_screen_buffer, sends_use_normal_screen_buffer)
{
    terminalpp::default_terminal terminal;

    expect_sequence(
        std::string("\x1B[?47l"),
        terminal.use_normal_screen_buffer());
}

TEST(activating_alternate_screen_buffer, sends_use_alternate_screen_buffer)
{
    terminalpp::default_terminal terminal;

    expect_sequence(
        std::string("\x1B[?47h"),
        terminal.use_alternate_screen_buffer());
}
