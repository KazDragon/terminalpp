#include "expect_tokens.hpp"
#include "terminalpp/terminal.hpp"
#include <gtest/gtest.h>

TEST(terminal_read_test, read_empty_string_yields_nothing)
{
    expect_tokens("", {});
}

TEST(terminal_read_test, read_character_yields_virtual_key)
{
    expect_token(
        "z",
        terminalpp::virtual_key{
            terminalpp::vk::lowercase_z,
            terminalpp::vk_modifier::none,
            1,
            { 'z' }
        });
}

TEST(terminal_read_test, read_uppercase_character_yields_character_without_modifier)
{
    // We consider uppercase letters to be entirely different keypresses.
    expect_token(
        "Z",
        terminalpp::virtual_key{
            terminalpp::vk::uppercase_z,
            terminalpp::vk_modifier::none,
            1,
            { 'Z' }
        });
}

TEST(terminal_read_test, read_command_yields_command)
{
    expect_token(
        "\x1B[S",
        terminalpp::ansi::control_sequence {
            '[',
            'S',
            false,
            { "" }
        });
}

TEST(terminal_read_test, read_command_with_arguments_yields_command_with_arguments)
{
    expect_token(
        "\x1B[22;33S",
        terminalpp::ansi::control_sequence {
            '[',
            'S',
            false,
            { "22", "33" }
        });
}

TEST(terminal_read_test, read_meta_command_yields_meta_command)
{
    expect_token(
        "\x1B\x1B[S",
        terminalpp::ansi::control_sequence {
            '[',
            'S',
            true,
            { "" }
        });
}

TEST(terminal_read_test, read_mouse_command_yields_mouse_report)
{
    expect_token(
        "\x1B[M @B",
        terminalpp::ansi::mouse::report {
            terminalpp::ansi::mouse::report::LEFT_BUTTON_DOWN,
            31,
            33
        });
}

TEST(terminal_read_test, read_non_mouse_similar_command_yields_command)
{
    expect_token(
        "\x1B?M",
        terminalpp::ansi::control_sequence {
            '?',
            'M',
            false,
            { "" }
        });
}

TEST(terminal_read_test, read_partial_command_yields_nothing)
{
    expect_tokens("\x1B[", {});
}

TEST(terminal_read_test, read_partial_command_then_read_remainder_yields_command)
{
    terminalpp::terminal terminal;

    std::string input0 = "\x1B[";
    std::string input1 = "E";

    auto expected = std::vector<terminalpp::token> {
        terminalpp::ansi::control_sequence {
            '[',
            'E',
            false,
            { "" }
        }
    };

    terminal.read(input0);
    auto result = terminal.read(input1);

    ASSERT_EQ(expected.size(), result.size());
    ASSERT_EQ(
        boost::get<terminalpp::ansi::control_sequence>(expected[0]),
        boost::get<terminalpp::ansi::control_sequence>(result[0]));
}

TEST(terminal_read_test, read_partial_mouse_command_yields_nothing)
{
    expect_tokens("\x1B[M", {});
}

TEST(terminal_read_test, read_8bit_command_yields_command)
{
    expect_token(
        "\x9B""22;33S",
        terminalpp::ansi::control_sequence {
            '[',
            'S',
            false,
            { "22", "33" }
        });
}

TEST(terminal_read_test, read_query_extended_command_yields_extended_command)
{
    expect_token(
        "\x1B[?6n",
        terminalpp::ansi::control_sequence {
            '[',
            'n',
            false,
            { "6" },
            '?'
        });
}

TEST(terminal_read_test, read_gt_extended_command_yields_extended_command)
{
    expect_token(
        "\x1B[>5c",
        terminalpp::ansi::control_sequence {
            '[',
            'c',
            false,
            { "5" },
            '>'
        });
}

TEST(terminal_read_test, read_bang_extended_command_yields_extended_command)
{
    expect_token(
        "\x1B[!p",
        terminalpp::ansi::control_sequence {
            '[',
            'p',
            false,
            { "" },
            '!'
        });
}
