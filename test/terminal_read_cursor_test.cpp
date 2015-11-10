#include "expect_tokens.hpp"
#include "terminalpp/terminal.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class terminal_read_cursor_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(terminal_read_cursor_test);
        CPPUNIT_TEST(up_command_yields_vk_up);
        CPPUNIT_TEST(down_command_yields_vk_down);
        CPPUNIT_TEST(right_command_yields_vk_right);
        CPPUNIT_TEST(left_command_yields_vk_left);

        CPPUNIT_TEST(home_command_yields_vk_home);
        CPPUNIT_TEST(alternative_home_command_yields_vk_home);
        CPPUNIT_TEST(ins_command_yields_vk_ins);
        CPPUNIT_TEST(del_command_yields_vk_del);
        CPPUNIT_TEST(end_command_yields_vk_end);
        CPPUNIT_TEST(pgup_command_yields_vk_pgup);
        CPPUNIT_TEST(pgdn_command_yields_vk_pgdn);

        CPPUNIT_TEST(up_ss3_yields_vk_up);
        CPPUNIT_TEST(down_ss3_yields_vk_down);
        CPPUNIT_TEST(right_ss3_yields_vk_right);
        CPPUNIT_TEST(left_ss3_yields_vk_left);
        CPPUNIT_TEST(home_ss3_yields_vk_home);
        CPPUNIT_TEST(end_ss3_yields_vk_end);
    CPPUNIT_TEST_SUITE_END();

private :
    void up_command_yields_vk_up();
    void down_command_yields_vk_down();
    void right_command_yields_vk_right();
    void left_command_yields_vk_left();

    void home_command_yields_vk_home();
    void alternative_home_command_yields_vk_home();
    void ins_command_yields_vk_ins();
    void del_command_yields_vk_del();
    void end_command_yields_vk_end();
    void pgup_command_yields_vk_pgup();
    void pgdn_command_yields_vk_pgdn();

    void up_ss3_yields_vk_up();
    void down_ss3_yields_vk_down();
    void right_ss3_yields_vk_right();
    void left_ss3_yields_vk_left();
    void home_ss3_yields_vk_home();
    void end_ss3_yields_vk_end();
};

CPPUNIT_TEST_SUITE_REGISTRATION(terminal_read_cursor_test);

void terminal_read_cursor_test::up_command_yields_vk_up()
{
    expect_token(
        "\x1B[A",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_up,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', 'A', false, { "" }}
        });
}

void terminal_read_cursor_test::down_command_yields_vk_down()
{
    expect_token(
        "\x1B[B",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_down,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', 'B', false, { "" }}
        });
}

void terminal_read_cursor_test::right_command_yields_vk_right()
{
    expect_token(
        "\x1B[C",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_right,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', 'C', false, { "" }}
        });
}

void terminal_read_cursor_test::left_command_yields_vk_left()
{
    expect_token(
        "\x1B[D",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_left,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', 'D', false, { "" }}
        });
}

void terminal_read_cursor_test::home_command_yields_vk_home()
{
    expect_token(
        "\x1B[1~",
        terminalpp::virtual_key {
            terminalpp::vk::home,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "1" }}
        });
}

void terminal_read_cursor_test::alternative_home_command_yields_vk_home()
{
    expect_token(
        "\x1B[H",
        terminalpp::virtual_key {
            terminalpp::vk::home,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', 'H', false, {}}
        });
}

void terminal_read_cursor_test::ins_command_yields_vk_ins()
{
    expect_token(
        "\x1B[2~",
        terminalpp::virtual_key {
            terminalpp::vk::ins,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "2" }}
        });
}

void terminal_read_cursor_test::del_command_yields_vk_del()
{
    expect_token(
        "\x1B[3~",
        terminalpp::virtual_key {
            terminalpp::vk::del,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "3" }}
        });
}

void terminal_read_cursor_test::end_command_yields_vk_end()
{
    expect_token(
        "\x1B[4~",
        terminalpp::virtual_key {
            terminalpp::vk::end,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "4" }}
        });
}

void terminal_read_cursor_test::pgup_command_yields_vk_pgup()
{
    expect_token(
        "\x1B[5~",
        terminalpp::virtual_key {
            terminalpp::vk::pgup,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "5" }}
        });
}

void terminal_read_cursor_test::pgdn_command_yields_vk_pgdn()
{
    expect_token(
        "\x1B[6~",
        terminalpp::virtual_key {
            terminalpp::vk::pgdn,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "6" }}
        });
}

void terminal_read_cursor_test::up_ss3_yields_vk_up()
{
    expect_token(
        "\x1BOA",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_up,
            0,
            1,
            terminalpp::ansi::control_sequence{'O', 'A', false, { "" }}
        });
}

void terminal_read_cursor_test::down_ss3_yields_vk_down()
{
    expect_token(
        "\x1BOB",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_down,
            0,
            1,
            terminalpp::ansi::control_sequence{'O', 'B', false, { "" }}
        });
}

void terminal_read_cursor_test::right_ss3_yields_vk_right()
{
    expect_token(
        "\x1BOC",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_right,
            0,
            1,
            terminalpp::ansi::control_sequence{'O', 'C', false, { "" }}
        });
}

void terminal_read_cursor_test::left_ss3_yields_vk_left()
{
    expect_token(
        "\x1BOD",
        terminalpp::virtual_key {
            terminalpp::vk::cursor_left,
            0,
            1,
            terminalpp::ansi::control_sequence{'O', 'D', false, { "" }}
        });
}

void terminal_read_cursor_test::home_ss3_yields_vk_home()
{
    expect_token(
        "\x1BOH",
        terminalpp::virtual_key {
            terminalpp::vk::home,
            0,
            1,
            terminalpp::ansi::control_sequence{'O', 'H', false, { "" }}
        });
}

void terminal_read_cursor_test::end_ss3_yields_vk_end()
{
    expect_token(
        "\x1BOF",
        terminalpp::virtual_key {
            terminalpp::vk::end,
            0,
            1,
            terminalpp::ansi::control_sequence{'O', 'F', false, { "" }}
        });
}
