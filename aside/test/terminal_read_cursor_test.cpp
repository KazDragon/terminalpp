#include "expect_tokens.hpp"
#include "terminalpp/terminal.hpp"
#include <gtest/gtest.h>

TEST(terminal_read_cursor_test, up_command_yields_vk_up)
{
    expect_token(
        "\x1B[A",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_up,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', 'A', false, { "" }}
        });
}

TEST(terminal_read_cursor_test, down_command_yields_vk_down)
{
    expect_token(
        "\x1B[B",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_down,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', 'B', false, { "" }}
        });
}

TEST(terminal_read_cursor_test, right_command_yields_vk_right)
{
    expect_token(
        "\x1B[C",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_right,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', 'C', false, { "" }}
        });
}

TEST(terminal_read_cursor_test, left_command_yields_vk_left)
{
    expect_token(
        "\x1B[D",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_left,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', 'D', false, { "" }}
        });
}

TEST(terminal_read_cursor_test, direction_commands_with_repeat_count_yield_vk_with_repeat_count)
{
    expect_token(
        "\x1B[1;A",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_up,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', 'A', false, { "1" }}
        });

    expect_token(
        "\x1B[2;B",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_down,
            terminalpp::vk_modifier::none,
            2,
            terminalpp::ansi::control_sequence{'[', 'B', false, { "2" }}
        });

    expect_token(
        "\x1B[3;C",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_right,
            terminalpp::vk_modifier::none,
            3,
            terminalpp::ansi::control_sequence{'[', 'C', false, { "3" }}
        });

    expect_token(
        "\x1B[4;D",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_left,
            terminalpp::vk_modifier::none,
            4,
            terminalpp::ansi::control_sequence{'[', 'D', false, { "4" }}
        });
}

TEST(terminal_read_cursor_test, direction_meta_command_yields_meta_vk)
{
    expect_token(
        "\x1B\x1B[A",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_up,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'[', 'A', true, { "" }}
        });

    expect_token(
        "\x1B\x1B[B",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_down,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'[', 'B', true, { "" }}
        });

    expect_token(
        "\x1B\x1B[C",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_right,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'[', 'C', true, { "" }}
        });

    expect_token(
        "\x1B\x1B[D",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_left,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'[', 'D', false, { "" }}
        });
}

TEST(terminal_read_cursor_test, home_command_yields_vk_home)
{
    expect_token(
        "\x1B[1~",
        terminalpp::virtual_key {
            terminalpp::vk::home,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "1" }}
        });
}

TEST(terminal_read_cursor_test, alternative_home_command_yields_vk_home)
{
    expect_token(
        "\x1B[H",
        terminalpp::virtual_key {
            terminalpp::vk::home,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', 'H', false, {}}
        });
}

TEST(terminal_read_cursor_test, ins_command_yields_vk_ins)
{
    expect_token(
        "\x1B[2~",
        terminalpp::virtual_key {
            terminalpp::vk::ins,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "2" }}
        });
}

TEST(terminal_read_cursor_test, del_command_yields_vk_del)
{
    expect_token(
        "\x1B[3~",
        terminalpp::virtual_key {
            terminalpp::vk::del,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "3" }}
        });
}

TEST(terminal_read_cursor_test, end_command_yields_vk_end)
{
    expect_token(
        "\x1B[4~",
        terminalpp::virtual_key {
            terminalpp::vk::end,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "4" }}
        });
}

TEST(terminal_read_cursor_test, pgup_command_yields_vk_pgup)
{
    expect_token(
        "\x1B[5~",
        terminalpp::virtual_key {
            terminalpp::vk::pgup,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "5" }}
        });
}

TEST(terminal_read_cursor_test, pgdn_command_yields_vk_pgdn)
{
    expect_token(
        "\x1B[6~",
        terminalpp::virtual_key {
            terminalpp::vk::pgdn,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "6" }}
        });
}

TEST(terminal_read_cursor_test, cursor_meta_command_yields_meta_vk)
{
    expect_token(
        "\x1B\x1B[1~",
        terminalpp::virtual_key {
            terminalpp::vk::home,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'[', '~', true, { "1" }}
        });

    expect_token(
        "\x1B\x1B[H",
        terminalpp::virtual_key {
            terminalpp::vk::home,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'[', 'H', true, {}}
        });

    expect_token(
        "\x1B\x1B[2~",
        terminalpp::virtual_key {
            terminalpp::vk::ins,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'[', '~', true, { "2" }}
        });

    expect_token(
        "\x1B\x1B[3~",
        terminalpp::virtual_key {
            terminalpp::vk::del,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'[', '~', true, { "3" }}
        });

    expect_token(
        "\x1B\x1B[4~",
        terminalpp::virtual_key {
            terminalpp::vk::end,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'[', '~', true, { "4" }}
        });

    expect_token(
        "\x1B\x1B[5~",
        terminalpp::virtual_key {
            terminalpp::vk::pgup,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'[', '~', true, { "5" }}
        });

    expect_token(
        "\x1B\x1B[6~",
        terminalpp::virtual_key {
            terminalpp::vk::pgdn,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'[', '~', true, { "6" }}
        });
}

TEST(terminal_read_cursor_test, cursor_command_with_modifiers_yields_vk_with_modifiers)
{
    expect_token(
        "\x1B[1;5~",
        terminalpp::virtual_key {
            terminalpp::vk::home,
            terminalpp::vk_modifier::ctrl,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "1", "5" }}
        });

    expect_token(
        "\x1B[2;3~",
        terminalpp::virtual_key {
            terminalpp::vk::ins,
            terminalpp::vk_modifier::alt,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "2", "3" }}
        });

    expect_token(
        "\x1B[3;2~",
        terminalpp::virtual_key {
            terminalpp::vk::del,
            terminalpp::vk_modifier::shift,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "3", "2" }}
        });

    expect_token(
        "\x1B[4;9~",
        terminalpp::virtual_key {
            terminalpp::vk::end,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "4", "9" }}
        });

    expect_token(
        "\x1B[5;7~",
        terminalpp::virtual_key {
            terminalpp::vk::pgup,
            terminalpp::vk_modifier::ctrl | terminalpp::vk_modifier::alt,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "5", "7" }}
        });

    expect_token(
        "\x1B[6;5~",
        terminalpp::virtual_key {
            terminalpp::vk::pgdn,
            terminalpp::vk_modifier::ctrl,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "6", "5" }}
        });
}

TEST(terminal_read_cursor_test, up_ss3_yields_vk_up)
{
    expect_token(
        "\x1BOA",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_up,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'O', 'A', false, { "" }}
        });
}

TEST(terminal_read_cursor_test, down_ss3_yields_vk_down)
{
    expect_token(
        "\x1BOB",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_down,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'O', 'B', false, { "" }}
        });
}

TEST(terminal_read_cursor_test, right_ss3_yields_vk_right)
{
    expect_token(
        "\x1BOC",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_right,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'O', 'C', false, { "" }}
        });
}

TEST(terminal_read_cursor_test, left_ss3_yields_vk_left)
{
    expect_token(
        "\x1BOD",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_left,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'O', 'D', false, { "" }}
        });
}

TEST(terminal_read_cursor_test, home_ss3_yields_vk_home)
{
    expect_token(
        "\x1BOH",
        terminalpp::virtual_key {
            terminalpp::vk::home,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'O', 'H', false, { "" }}
        });
}

TEST(terminal_read_cursor_test, end_ss3_yields_vk_end)
{
    expect_token(
        "\x1BOF",
        terminalpp::virtual_key {
            terminalpp::vk::end,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'O', 'F', false, { "" }}
        });
}

TEST(terminal_read_cursor_test, cursor_meta_ss3_yields_meta_vk)
{
    expect_token(
        "\x1B\x1BOA",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_up,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'O', 'A', true, { "" }}
        });

    expect_token(
        "\x1B\x1BOB",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_down,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'O', 'B', true, { "" }}
        });

    expect_token(
        "\x1B\x1BOC",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_right,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'O', 'C', true, { "" }}
        });

    expect_token(
        "\x1B\x1BOD",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_left,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'O', 'D', true, { "" }}
        });

    expect_token(
        "\x1B\x1BOH",
        terminalpp::virtual_key {
            terminalpp::vk::home,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'O', 'H', true, { "" }}
        });

    expect_token(
        "\x1B\x1BOF",
        terminalpp::virtual_key {
            terminalpp::vk::end,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'O', 'F', true, { "" }}
        });
}

TEST(terminal_read_cursor_test, tab_key_yields_vk_tab)
{
    expect_token(
        "\t",
        terminalpp::virtual_key {
            terminalpp::vk::ht,
            terminalpp::vk_modifier::none,
            1,
            '\t'
        });
}

TEST(terminal_read_cursor_test, tab_command_yields_vk_tab)
{
    expect_token(
        "\x1B[I",
        terminalpp::virtual_key {
            terminalpp::vk::ht,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', 'I', false, { "" }}
        });
}

TEST(terminal_read_cursor_test, tab_ss3_yields_vk_tab)
{
    expect_token(
        "\x1BOI",
        terminalpp::virtual_key {
            terminalpp::vk::ht,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'O', 'I', false, { "" }}
        });
}

TEST(terminal_read_cursor_test, reverse_tab_command_yields_vk_reverse_tab)
{
    expect_token(
        "\x1B[Z",
        terminalpp::virtual_key {
            terminalpp::vk::bt,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', 'Z', false, { "" }}
        });
}

TEST(terminal_read_cursor_test, tab_meta_commands_yield_meta_vk)
{
    expect_token(
        "\x1B\x1B[I",
        terminalpp::virtual_key {
            terminalpp::vk::ht,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'[', 'I', true, { "" }}
        });

    expect_token(
        "\x1B\x1BOI",
        terminalpp::virtual_key {
            terminalpp::vk::ht,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'O', 'I', true, { "" }}
        });

    expect_token(
        "\x1B\x1B[Z",
        terminalpp::virtual_key {
            terminalpp::vk::bt,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'[', 'Z', true, { "" }}
        });
}

TEST(terminal_read_cursor_test, tab_command_with_repeat_count_yields_vk_with_repeat_count)
{
    expect_token(
        "\x1B[7I",
        terminalpp::virtual_key {
            terminalpp::vk::ht,
            terminalpp::vk_modifier::none,
            7,
            terminalpp::ansi::control_sequence{'[', 'I', false, { "7" }}
        });
}

TEST(terminal_read_cursor_test, reverse_tab_command_with_repeat_count_yields_vk_with_repeat_count)
{
    expect_token(
        "\x1B[10Z",
        terminalpp::virtual_key {
            terminalpp::vk::bt,
            terminalpp::vk_modifier::none,
            10,
            terminalpp::ansi::control_sequence{'[', 'I', false, { "10" }}
        });
}

TEST(terminal_read_cursor_test, crlf_yields_vk_enter)
{
    expect_tokens(
        "\r\na",
        {
            { terminalpp::virtual_key {
                terminalpp::vk::enter,
                terminalpp::vk_modifier::none,
                1,
                '\n'
            }},
            { terminalpp::virtual_key {
                terminalpp::vk::lowercase_a,
                terminalpp::vk_modifier::none,
                1,
                'a'
            }}
        });
}

TEST(terminal_read_cursor_test, crnul_yields_vk_enter)
{
    std::string text("\r\0", 2);

    expect_token(
        text,
        terminalpp::virtual_key {
            terminalpp::vk::enter,
            terminalpp::vk_modifier::none,
            1,
            '\n'
        });
}

TEST(terminal_read_cursor_test, cr_then_nul_yields_enter_only)
{
    terminalpp::terminal terminal;

    auto expected_after_cr = terminalpp::virtual_key {
        terminalpp::vk::enter,
        terminalpp::vk_modifier::none,
        1,
        '\n'
    };

    auto actual_after_cr = terminal.read("\r");
    ASSERT_EQ(size_t{1}, actual_after_cr.size());
    ASSERT_EQ(
        expected_after_cr,
        boost::get<terminalpp::virtual_key>(actual_after_cr[0]));

    auto actual_after_nul = terminal.read(std::string("\0", 1));
    ASSERT_TRUE(actual_after_nul.empty());
}

TEST(terminal_read_cursor_test, lfcr_yields_vk_enter)
{
    expect_token(
        "\n\r",
        terminalpp::virtual_key {
            terminalpp::vk::enter,
            terminalpp::vk_modifier::none,
            1,
            '\n'
        });
}

TEST(terminal_read_cursor_test, lf_yields_vk_enter)
{
    expect_tokens(
        "\na",
        {
            { terminalpp::virtual_key {
                terminalpp::vk::enter,
                terminalpp::vk_modifier::none,
                1,
                '\n'
            }},
            { terminalpp::virtual_key {
                terminalpp::vk::lowercase_a,
                terminalpp::vk_modifier::none,
                1,
                'a'
            }}
        });
}

TEST(terminal_read_cursor_test, lflf_yields_two_vk_enters)
{
    expect_tokens(
        "\n\n",
        {
            { terminalpp::virtual_key {
                terminalpp::vk::enter,
                terminalpp::vk_modifier::none,
                1,
                '\n'
            }},
            { terminalpp::virtual_key {
                terminalpp::vk::enter,
                terminalpp::vk_modifier::none,
                1,
                '\n'
            }}
        });
}

TEST(terminal_read_cursor_test, enter_ss3_yields_vk_end)
{
    expect_token(
        "\x1BOM",
        terminalpp::virtual_key {
            terminalpp::vk::enter,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{ 'O', 'M', false, { "" } }
        });
}
