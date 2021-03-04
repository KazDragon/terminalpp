#include "expect_sequence.hpp"
#include "terminal_test.hpp"
#include <gtest/gtest.h>

using namespace terminalpp::literals;

TEST_F(a_terminal, enabling_mouse_mode_sends_nothing)
{
    terminal_.write(append_to_result) << terminalpp::enable_mouse();
    expect_sequence(""_tb, result_);
}

TEST_F(a_terminal, disabling_mouse_mode_sends_nothing)
{
    terminal_.write(append_to_result) << terminalpp::disable_mouse();
    expect_sequence(""_tb, result_);
}

namespace {

class a_terminal_with_basic_mouse_support : public a_terminal
{
public:
    a_terminal_with_basic_mouse_support()
      : a_terminal(
            []
            {
                terminalpp::behaviour beh;
                beh.supports_basic_mouse_tracking = true;
                return beh;
            }())
    {
    }

};

}

TEST_F(a_terminal_with_basic_mouse_support, sends_enable_basic_mouse_tracking_when_enabling_mouse)
{
    terminal_.write(append_to_result) << terminalpp::enable_mouse();
    expect_sequence("\x1B[?1000h"_tb, result_);
}

TEST_F(a_terminal_with_basic_mouse_support, sends_disable_basic_mouse_tracking_when_disabling_mouse)
{
    terminal_.write(append_to_result) << terminalpp::disable_mouse();
    expect_sequence("\x1B[?1000l"_tb, result_);
}

namespace {

class a_terminal_with_all_mouse_motion_support : public a_terminal
{
public:
    a_terminal_with_all_mouse_motion_support()
      : a_terminal(
            []
            {
                terminalpp::behaviour beh;
                beh.supports_all_mouse_motion_tracking = true;
                return beh;
            }())
    {
    }

};

}

TEST_F(a_terminal_with_all_mouse_motion_support, sends_enable_all_mouse_motion_when_enabling_mouse)
{
    terminal_.write(append_to_result) << terminalpp::enable_mouse();
    expect_sequence("\x1B[?1003h"_tb, result_);
}

TEST_F(a_terminal_with_all_mouse_motion_support, sends_disable_basic_mouse_motion_when_disabling_mouse)
{
    terminal_.write(append_to_result) << terminalpp::disable_mouse();
    expect_sequence("\x1B[?1003l"_tb, result_);
}

/*

TEST(setting_window_title_with_default_behaviour, sends_nothing)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string(""),
        terminal.set_window_title("title"));
}

TEST(setting_window_title_with_bel_behaviour, sends_window_title_with_bel)
{
    terminalpp::behaviour behaviour;
    behaviour.supports_window_title_bel = true;
    terminalpp::terminal terminal(behaviour);

    expect_sequence(
        std::string("\x1B]2;title\x7"),
        terminal.set_window_title("title"));
}

TEST(setting_window_title_with_st_behaviour, sends_window_title_with_st)
{
    terminalpp::behaviour behaviour;
    behaviour.supports_window_title_st = true;
    terminalpp::terminal terminal(behaviour);

    expect_sequence(
        std::string("\x1B]2;title\x1B\\"),
        terminal.set_window_title("title"));
}

TEST(activating_normal_screen_buffer, sends_use_normal_screen_buffer)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[?47l"),
        terminal.use_normal_screen_buffer());
}

TEST(activating_alternate_screen_buffer, sends_use_alternate_screen_buffer)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[?47h"),
        terminal.use_alternate_screen_buffer());
}
*/
