#include "terminal_test.hpp"

#include <gmock/gmock.h>

using namespace terminalpp::literals;  // NOLINT
using testing::ContainerEq;

namespace {

TEST_F(a_terminal, enabling_mouse_mode_sends_nothing)
{
    terminal_ << terminalpp::enable_mouse();
    EXPECT_THAT(channel_.written_, ContainerEq(""_tb));
}

TEST_F(a_terminal, disabling_mouse_mode_sends_nothing)
{
    terminal_ << terminalpp::disable_mouse();
    EXPECT_THAT(channel_.written_, ContainerEq(""_tb));
}

namespace {

class a_terminal_with_basic_mouse_support : public a_terminal
{
public:
    a_terminal_with_basic_mouse_support()
      : a_terminal([] {
            terminalpp::behaviour beh;
            beh.supports_basic_mouse_tracking = true;
            return beh;
        }())
    {
    }
};

}  // namespace

TEST_F(
    a_terminal_with_basic_mouse_support,
    sends_enable_basic_mouse_tracking_when_enabling_mouse)
{
    terminal_ << terminalpp::enable_mouse();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[?1000h"_tb));
}

TEST_F(
    a_terminal_with_basic_mouse_support,
    sends_disable_basic_mouse_tracking_when_disabling_mouse)
{
    terminal_ << terminalpp::disable_mouse();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[?1000l"_tb));
}

namespace {

class a_terminal_with_all_mouse_motion_support : public a_terminal
{
public:
    a_terminal_with_all_mouse_motion_support()
      : a_terminal([] {
            terminalpp::behaviour beh;
            beh.supports_all_mouse_motion_tracking = true;
            return beh;
        }())
    {
    }
};

}  // namespace

TEST_F(
    a_terminal_with_all_mouse_motion_support,
    sends_enable_all_mouse_motion_when_enabling_mouse)
{
    terminal_ << terminalpp::enable_mouse();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[?1003h"_tb));
}

TEST_F(
    a_terminal_with_all_mouse_motion_support,
    sends_disable_basic_mouse_motion_when_disabling_mouse)
{
    terminal_ << terminalpp::disable_mouse();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[?1003l"_tb));
}

TEST_F(a_terminal, setting_window_title_sends_nothing)
{
    terminal_ << terminalpp::set_window_title("title");
    EXPECT_THAT(channel_.written_, ContainerEq(""_tb));
}

namespace {

class a_terminal_with_support_for_window_title_bel : public a_terminal
{
public:
    a_terminal_with_support_for_window_title_bel()
      : a_terminal([] {
            terminalpp::behaviour beh;
            beh.supports_window_title_bel = true;
            return beh;
        }())
    {
    }
};

}  // namespace

TEST_F(
    a_terminal_with_support_for_window_title_bel, sends_window_title_with_bel)
{
    terminal_ << terminalpp::set_window_title("title");
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B]2;title\x7"_tb));
}

namespace {

class a_terminal_with_support_for_window_title_st : public a_terminal
{
public:
    a_terminal_with_support_for_window_title_st()
      : a_terminal([] {
            terminalpp::behaviour beh;
            beh.supports_window_title_st = true;
            return beh;
        }())
    {
    }
};

}  // namespace

TEST_F(a_terminal_with_support_for_window_title_st, sends_window_title_with_bel)
{
    terminal_ << terminalpp::set_window_title("title");
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B]2;title\x1B\\"_tb));
}

TEST_F(
    a_terminal,
    activating_normal_screen_buffer_sends_use_normal_screen_buffer_codes)
{
    terminal_ << terminalpp::use_normal_screen_buffer();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[?47l"_tb));
}

TEST_F(
    a_terminal,
    activating_alternate_screen_buffer_sends_use_alternate_screen_buffer_codes)
{
    terminal_ << terminalpp::use_alternate_screen_buffer();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[?47h"_tb));
}

}  // namespace
