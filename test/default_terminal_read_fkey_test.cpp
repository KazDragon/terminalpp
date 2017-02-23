#include "expect_tokens.hpp"
#include "terminalpp/terminal.hpp"
#include <gtest/gtest.h>

TEST(terminal_read_fkey_test, f1_command_yields_vk_f1)
{
    expect_token(
        "\x1B[11~",
        terminalpp::virtual_key {
            terminalpp::vk::f1,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "11" }}
        });
}

TEST(terminal_read_fkey_test, f2_command_yields_vk_f2)
{
    expect_token(
        "\x1B[12~",
        terminalpp::virtual_key {
            terminalpp::vk::f2,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "12" }}
        });
}

TEST(terminal_read_fkey_test, f3_command_yields_vk_f3)
{
    expect_token(
        "\x1B[13~",
        terminalpp::virtual_key {
            terminalpp::vk::f3,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "13" }}
        });
}

TEST(terminal_read_fkey_test, f4_command_yields_vk_f4)
{
    expect_token(
        "\x1B[14~",
        terminalpp::virtual_key {
            terminalpp::vk::f4,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "14" }}
        });
}

TEST(terminal_read_fkey_test, f5_command_yields_vk_f5)
{
    expect_token(
        "\x1B[15~",
        terminalpp::virtual_key {
            terminalpp::vk::f5,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "15" }}
        });
}

TEST(terminal_read_fkey_test, f6_command_yields_vk_f6)
{
    expect_token(
        "\x1B[17~",
        terminalpp::virtual_key {
            terminalpp::vk::f6,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "17" }}
        });
}

TEST(terminal_read_fkey_test, f7_command_yields_vk_f7)
{
    expect_token(
        "\x1B[18~",
        terminalpp::virtual_key {
            terminalpp::vk::f7,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "18" }}
        });
}

TEST(terminal_read_fkey_test, f8_command_yields_vk_f8)
{
    expect_token(
        "\x1B[19~",
        terminalpp::virtual_key {
            terminalpp::vk::f8,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "19" }}
        });
}

TEST(terminal_read_fkey_test, f9_command_yields_vk_f9)
{
    expect_token(
        "\x1B[20~",
        terminalpp::virtual_key {
            terminalpp::vk::f9,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "20" }}
        });
}

TEST(terminal_read_fkey_test, f10_command_yields_vk_f10)
{
    expect_token(
        "\x1B[21~",
        terminalpp::virtual_key {
            terminalpp::vk::f10,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "21" }}
        });
}

TEST(terminal_read_fkey_test, f11_command_yields_vk_f11)
{
    expect_token(
        "\x1B[23~",
        terminalpp::virtual_key {
            terminalpp::vk::f11,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "23" }}
        });
}

TEST(terminal_read_fkey_test, f12_command_yields_vk_f12)
{
    expect_token(
        "\x1B[24~",
        terminalpp::virtual_key {
            terminalpp::vk::f12,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "24" }}
        });
}

void expect_fkey_with_modifier(
    std::string const &fkey_code,
    std::string const &fkey_modifier_code,
    terminalpp::vk const &expected_vk,
    terminalpp::vk_modifier const &expected_vk_modifier)
{
    expect_token(
        "\x1B[" + fkey_code + ';' + fkey_modifier_code + '~',
        terminalpp::virtual_key {
            expected_vk,
            expected_vk_modifier,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, {
                fkey_code,
                fkey_modifier_code
            }}
        });
}

void expect_fkeys_with_modifier(
    std::string const &fkey_modifier_code,
    terminalpp::vk_modifier const &expected_vk_modifier)
{
    expect_fkey_with_modifier(
        std::to_string(terminalpp::ansi::csi::KEYPAD_F1), fkey_modifier_code,
        terminalpp::vk::f1, expected_vk_modifier);
    expect_fkey_with_modifier(
        std::to_string(terminalpp::ansi::csi::KEYPAD_F2), fkey_modifier_code,
        terminalpp::vk::f2, expected_vk_modifier);
    expect_fkey_with_modifier(
        std::to_string(terminalpp::ansi::csi::KEYPAD_F3), fkey_modifier_code,
        terminalpp::vk::f3, expected_vk_modifier);
    expect_fkey_with_modifier(
        std::to_string(terminalpp::ansi::csi::KEYPAD_F4), fkey_modifier_code,
        terminalpp::vk::f4, expected_vk_modifier);
    expect_fkey_with_modifier(
        std::to_string(terminalpp::ansi::csi::KEYPAD_F5), fkey_modifier_code,
        terminalpp::vk::f5, expected_vk_modifier);
    expect_fkey_with_modifier(
        std::to_string(terminalpp::ansi::csi::KEYPAD_F6), fkey_modifier_code,
        terminalpp::vk::f6, expected_vk_modifier);
    expect_fkey_with_modifier(
        std::to_string(terminalpp::ansi::csi::KEYPAD_F7), fkey_modifier_code,
        terminalpp::vk::f7, expected_vk_modifier);
    expect_fkey_with_modifier(
        std::to_string(terminalpp::ansi::csi::KEYPAD_F8), fkey_modifier_code,
        terminalpp::vk::f8, expected_vk_modifier);
    expect_fkey_with_modifier(
        std::to_string(terminalpp::ansi::csi::KEYPAD_F9), fkey_modifier_code,
        terminalpp::vk::f9, expected_vk_modifier);
    expect_fkey_with_modifier(
        std::to_string(terminalpp::ansi::csi::KEYPAD_F10), fkey_modifier_code,
        terminalpp::vk::f10, expected_vk_modifier);
    expect_fkey_with_modifier(
        std::to_string(terminalpp::ansi::csi::KEYPAD_F11), fkey_modifier_code,
        terminalpp::vk::f11, expected_vk_modifier);
    expect_fkey_with_modifier(
        std::to_string(terminalpp::ansi::csi::KEYPAD_F12), fkey_modifier_code,
        terminalpp::vk::f12, expected_vk_modifier);
}

TEST(terminal_read_fkey_test, shift_f_command_yields_vk_shift_f)
{
    expect_fkeys_with_modifier("2", terminalpp::vk_modifier::shift);
}

TEST(terminal_read_fkey_test, ctrl_f_command_yields_vk_ctrl_f)
{
    expect_fkeys_with_modifier("5", terminalpp::vk_modifier::ctrl);
}

TEST(terminal_read_fkey_test, shift_ctrl_f_command_yields_vk_shift_ctrl_f)
{
    expect_fkeys_with_modifier(
        "6", terminalpp::vk_modifier::shift | terminalpp::vk_modifier::ctrl);
}

TEST(terminal_read_fkey_test, alt_f_command_yields_vk_alt_f)
{
    expect_fkeys_with_modifier("3", terminalpp::vk_modifier::alt);
}

TEST(terminal_read_fkey_test, alt_shift_f_command_yields_vk_alt_shift_f)
{
    expect_fkeys_with_modifier(
        "4", terminalpp::vk_modifier::alt | terminalpp::vk_modifier::shift);
}

TEST(terminal_read_fkey_test, alt_ctrl_f_command_yields_vk_alt_ctrl_f)
{
    expect_fkeys_with_modifier(
        "7", terminalpp::vk_modifier::alt | terminalpp::vk_modifier::ctrl);
}

TEST(terminal_read_fkey_test, alt_shift_ctrl_f_command_yields_vk_alt_shift_ctrl_f)
{
    expect_fkeys_with_modifier(
        "8",
        terminalpp::vk_modifier::alt
      | terminalpp::vk_modifier::shift
      | terminalpp::vk_modifier::ctrl);
}

TEST(terminal_read_fkey_test, alt_shift_ctrl_meta_f_command_yields_vk_meta_alt_shift_ctrl_f)
{
    expect_token(
        "\x1B\x1B[15;8~",
        terminalpp::virtual_key {
            terminalpp::vk::f5,
            terminalpp::vk_modifier::alt
          | terminalpp::vk_modifier::shift
          | terminalpp::vk_modifier::ctrl
          | terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'[', '~', true, {
                "15",
                "8"
            }}
        });
}

TEST(terminal_read_fkey_test, meta_f_command_yields_vk_meta_f)
{
    expect_fkeys_with_modifier("9", terminalpp::vk_modifier::meta);
}

TEST(terminal_read_fkey_test, meta_shift_f_command_yields_vk_meta_shift_f)
{
    expect_fkeys_with_modifier(
        "10", terminalpp::vk_modifier::meta | terminalpp::vk_modifier::shift);
}

TEST(terminal_read_fkey_test, meta_ctrl_f_command_yields_vk_meta_ctrl_f)
{
    expect_fkeys_with_modifier(
        "13", terminalpp::vk_modifier::meta | terminalpp::vk_modifier::ctrl);
}

TEST(terminal_read_fkey_test, meta_shift_ctrl_f_command_yields_vk_meta_shift_ctrl_f)
{
    expect_fkeys_with_modifier(
        "14",
        terminalpp::vk_modifier::meta
      | terminalpp::vk_modifier::shift
      | terminalpp::vk_modifier::ctrl);
}

TEST(terminal_read_fkey_test, meta_alt_f_command_yields_vk_meta_alt_f)
{
    expect_fkeys_with_modifier(
        "11", terminalpp::vk_modifier::meta | terminalpp::vk_modifier::alt);
}

TEST(terminal_read_fkey_test, meta_alt_shift_f_command_yields_vk_meta_alt_shift_f)
{
    expect_fkeys_with_modifier(
        "12",
        terminalpp::vk_modifier::meta
      | terminalpp::vk_modifier::alt
      | terminalpp::vk_modifier::shift);
}

TEST(terminal_read_fkey_test, meta_alt_ctrl_f_command_yields_vk_meta_alt_ctrl_f)
{
    expect_fkeys_with_modifier(
        "15",
        terminalpp::vk_modifier::meta
      | terminalpp::vk_modifier::alt
      | terminalpp::vk_modifier::ctrl);
}

TEST(terminal_read_fkey_test, meta_alt_shift_ctrl_f_command_yields_vk_meta_alt_shift_ctrl_f)
{
    expect_fkeys_with_modifier(
        "16",
        terminalpp::vk_modifier::meta
      | terminalpp::vk_modifier::alt
      | terminalpp::vk_modifier::shift
      | terminalpp::vk_modifier::ctrl);
}

TEST(terminal_read_fkey_test, f1_ss3_yields_vk_f1)
{
    expect_token(
        "\x1BOP",
        terminalpp::virtual_key {
            terminalpp::vk::f1,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'O', 'P', false, { "" }}
        });
}

TEST(terminal_read_fkey_test, f2_ss3_yields_vk_f2)
{
    expect_token(
        "\x1BOQ",
        terminalpp::virtual_key {
            terminalpp::vk::f2,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'O', 'Q', false, { "" }}
        });
}

TEST(terminal_read_fkey_test, f3_ss3_yields_vk_f3)
{
    expect_token(
        "\x1BOR",
        terminalpp::virtual_key {
            terminalpp::vk::f3,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'O', 'R', false, { "" }}
        });
}

TEST(terminal_read_fkey_test, f4_ss3_yields_vk_f4)
{
    expect_token(
        "\x1BOS",
        terminalpp::virtual_key {
            terminalpp::vk::f4,
            terminalpp::vk_modifier::none,
            1,
            terminalpp::ansi::control_sequence{'O', 'S', false, { "" }}
        });
}

TEST(terminal_read_fkey_test, f_meta_ss3_yields_meta_vk)
{
    expect_token(
        "\x1B\x1BOP",
        terminalpp::virtual_key {
            terminalpp::vk::f1,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'O', 'P', true, { "" }}
        });

    expect_token(
        "\x1B\x1BOQ",
        terminalpp::virtual_key {
            terminalpp::vk::f2,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'O', 'Q', true, { "" }}
        });

    expect_token(
        "\x1B\x1BOR",
        terminalpp::virtual_key {
            terminalpp::vk::f3,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'O', 'R', true, { "" }}
        });

    expect_token(
        "\x1B\x1BOS",
        terminalpp::virtual_key {
            terminalpp::vk::f4,
            terminalpp::vk_modifier::meta,
            1,
            terminalpp::ansi::control_sequence{'O', 'S', true, { "" }}
        });

}
