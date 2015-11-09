#include "terminalpp/terminal.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class terminal_read_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(terminal_read_test);
        CPPUNIT_TEST(read_empty_string_yields_nothing);
        CPPUNIT_TEST(read_character_yields_virtual_key);
        CPPUNIT_TEST(read_command_yields_command);
        CPPUNIT_TEST(read_command_with_arguments_yields_command_with_arguments);
        CPPUNIT_TEST(read_meta_command_yields_meta_command);
        CPPUNIT_TEST(read_mouse_command_yields_mouse_report);
        CPPUNIT_TEST(read_non_mouse_similar_command_yields_command);
        CPPUNIT_TEST(read_partial_command_yields_nothing);
        CPPUNIT_TEST(read_partial_command_then_read_remainder_yields_command);
        CPPUNIT_TEST(read_partial_mouse_command_yields_nothing);
        CPPUNIT_TEST(read_8bit_command_yields_command);

        CPPUNIT_TEST(cursor_up_command_yields_vk_up);
        CPPUNIT_TEST(cursor_down_command_yields_vk_down);
        CPPUNIT_TEST(cursor_right_command_yields_vk_right);
        CPPUNIT_TEST(cursor_left_command_yields_vk_left);

        CPPUNIT_TEST(cursor_home_command_yields_vk_home);
        CPPUNIT_TEST(cursor_ins_command_yields_vk_ins);
        CPPUNIT_TEST(cursor_del_command_yields_vk_del);
        CPPUNIT_TEST(cursor_end_command_yields_vk_end);
        CPPUNIT_TEST(cursor_pgup_command_yields_vk_pgup);
        CPPUNIT_TEST(cursor_pgdn_command_yields_vk_pgdn);

        CPPUNIT_TEST(cursor_up_ss3_yields_vk_up);
        CPPUNIT_TEST(cursor_down_ss3_yields_vk_down);
        CPPUNIT_TEST(cursor_right_ss3_yields_vk_right);
        CPPUNIT_TEST(cursor_left_ss3_yields_vk_left);
        CPPUNIT_TEST(cursor_home_ss3_yields_vk_home);
        CPPUNIT_TEST(cursor_end_ss3_yields_vk_end);

        /* TODO:
         * Read of OSC/PM/APC commands with ST/BEL terminators - and 8bit
         * Read of arrow keys translated to VKs.
         * Read of other numeric keypad keys to VKs
         * Read of function keys to VKs
         * Read of VKs with modifiers (shift, ctrl, etc.)
         */

    CPPUNIT_TEST_SUITE_END();

private :
    void read_empty_string_yields_nothing();
    void read_character_yields_virtual_key();
    void read_command_yields_command();
    void read_command_with_arguments_yields_command_with_arguments();
    void read_meta_command_yields_meta_command();
    void read_mouse_command_yields_mouse_report();
    void read_non_mouse_similar_command_yields_command();
    void read_partial_command_yields_nothing();
    void read_partial_command_then_read_remainder_yields_command();
    void read_partial_mouse_command_yields_nothing();
    void read_8bit_command_yields_command();

    void cursor_up_command_yields_vk_up();
    void cursor_down_command_yields_vk_down();
    void cursor_right_command_yields_vk_right();
    void cursor_left_command_yields_vk_left();

    void cursor_home_command_yields_vk_home();
    void cursor_ins_command_yields_vk_ins();
    void cursor_del_command_yields_vk_del();
    void cursor_end_command_yields_vk_end();
    void cursor_pgup_command_yields_vk_pgup();
    void cursor_pgdn_command_yields_vk_pgdn();

    void cursor_up_ss3_yields_vk_up();
    void cursor_down_ss3_yields_vk_down();
    void cursor_right_ss3_yields_vk_right();
    void cursor_left_ss3_yields_vk_left();
    void cursor_home_ss3_yields_vk_home();
    void cursor_end_ss3_yields_vk_end();
};

CPPUNIT_TEST_SUITE_REGISTRATION(terminal_read_test);

template <class Expected> void expect_token(
    std::string const &input,
    Expected const &expected)
{
    terminalpp::terminal terminal;

    auto result = terminal.read(input);

    CPPUNIT_ASSERT_EQUAL(false, result.empty());

    CPPUNIT_ASSERT_EQUAL(
        boost::get<Expected>(expected),
        boost::get<Expected>(result[0]));
}

void terminal_read_test::read_empty_string_yields_nothing()
{
    terminalpp::terminal terminal;

    std::string input = "";

    auto result = terminal.read(input);

    CPPUNIT_ASSERT_EQUAL(size_t{0}, result.size());
}

void terminal_read_test::read_character_yields_virtual_key()
{
    expect_token(
        "z",
        terminalpp::virtual_key{
            terminalpp::VK_LOWERCASE_Z,
            0,
            1,
            { 'z' }
        });
}

void terminal_read_test::read_command_yields_command()
{
    expect_token(
        "\x1B[H",
        terminalpp::ansi::control_sequence {
            '[',
            'H',
            false,
            { "" }
        });
}

void terminal_read_test::read_command_with_arguments_yields_command_with_arguments()
{
    expect_token(
        "\x1B[22;33H",
        terminalpp::ansi::control_sequence {
            '[',
            'H',
            false,
            { "22", "33" }
        });
}

void terminal_read_test::read_meta_command_yields_meta_command()
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

void terminal_read_test::read_mouse_command_yields_mouse_report()
{
    expect_token(
        "\x1B[M @B",
        terminalpp::ansi::mouse::report {
            terminalpp::ansi::mouse::report::LEFT_BUTTON_DOWN,
            32,
            34
        });
}

void terminal_read_test::read_non_mouse_similar_command_yields_command()
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

void terminal_read_test::read_partial_command_yields_nothing()
{
    terminalpp::terminal terminal;

    std::string input = "\x1B[";

    auto result = terminal.read(input);

    CPPUNIT_ASSERT_EQUAL(size_t{0}, result.size());
}

void terminal_read_test::read_partial_command_then_read_remainder_yields_command()
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

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::control_sequence>(expected[0]),
        boost::get<terminalpp::ansi::control_sequence>(result[0]));
}

void terminal_read_test::read_partial_mouse_command_yields_nothing()
{
    terminalpp::terminal terminal;

    std::string input = "\x1B[M";

    auto result = terminal.read(input);

    CPPUNIT_ASSERT_EQUAL(size_t{0}, result.size());
}

void terminal_read_test::read_8bit_command_yields_command()
{
    expect_token(
        "\x9B""22;33H",
        terminalpp::ansi::control_sequence {
            '[',
            'H',
            false,
            { "22", "33" }
        });
}

void terminal_read_test::cursor_up_command_yields_vk_up()
{
    expect_token(
        "\x1B[A",
        terminalpp::virtual_key {
            terminalpp::VK_UP,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', 'A', false, { "" }}
        });
}

void terminal_read_test::cursor_down_command_yields_vk_down()
{
    expect_token(
        "\x1B[B",
        terminalpp::virtual_key {
            terminalpp::VK_DOWN,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', 'B', false, { "" }}
        });
}

void terminal_read_test::cursor_right_command_yields_vk_right()
{
    expect_token(
        "\x1B[C",
        terminalpp::virtual_key {
            terminalpp::VK_RIGHT,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', 'C', false, { "" }}
        });
}

void terminal_read_test::cursor_left_command_yields_vk_left()
{
    expect_token(
        "\x1B[D",
        terminalpp::virtual_key {
            terminalpp::VK_LEFT,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', 'D', false, { "" }}
        });
}

void terminal_read_test::cursor_home_command_yields_vk_home()
{
    expect_token(
        "\x1B[1~",
        terminalpp::virtual_key {
            terminalpp::VK_HOME,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "1" }}
        });
}

void terminal_read_test::cursor_ins_command_yields_vk_ins()
{
    expect_token(
        "\x1B[2~",
        terminalpp::virtual_key {
            terminalpp::VK_INS,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "2" }}
        });
}

void terminal_read_test::cursor_del_command_yields_vk_del()
{
    expect_token(
        "\x1B[3~",
        terminalpp::virtual_key {
            terminalpp::VK_DEL,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "3" }}
        });
}

void terminal_read_test::cursor_end_command_yields_vk_end()
{
    expect_token(
        "\x1B[4~",
        terminalpp::virtual_key {
            terminalpp::VK_END,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "4" }}
        });
}

void terminal_read_test::cursor_pgup_command_yields_vk_pgup()
{
    expect_token(
        "\x1B[5~",
        terminalpp::virtual_key {
            terminalpp::VK_PGUP,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "5" }}
        });
}

void terminal_read_test::cursor_pgdn_command_yields_vk_pgdn()
{
    expect_token(
        "\x1B[6~",
        terminalpp::virtual_key {
            terminalpp::VK_PGDN,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "6" }}
        });
}

void terminal_read_test::cursor_up_ss3_yields_vk_up()
{
    expect_token(
        "\x1BOA",
        terminalpp::virtual_key {
            terminalpp::VK_UP,
            0,
            1,
            terminalpp::ansi::control_sequence{'O', 'A', false, { "" }}
        });
}

void terminal_read_test::cursor_down_ss3_yields_vk_down()
{
    expect_token(
        "\x1BOB",
        terminalpp::virtual_key {
            terminalpp::VK_DOWN,
            0,
            1,
            terminalpp::ansi::control_sequence{'O', 'B', false, { "" }}
        });
}

void terminal_read_test::cursor_right_ss3_yields_vk_right()
{
    expect_token(
        "\x1BOC",
        terminalpp::virtual_key {
            terminalpp::VK_RIGHT,
            0,
            1,
            terminalpp::ansi::control_sequence{'O', 'C', false, { "" }}
        });
}

void terminal_read_test::cursor_left_ss3_yields_vk_left()
{
    expect_token(
        "\x1BOD",
        terminalpp::virtual_key {
            terminalpp::VK_LEFT,
            0,
            1,
            terminalpp::ansi::control_sequence{'O', 'D', false, { "" }}
        });
}

void terminal_read_test::cursor_home_ss3_yields_vk_home()
{
    expect_token(
        "\x1BOH",
        terminalpp::virtual_key {
            terminalpp::VK_HOME,
            0,
            1,
            terminalpp::ansi::control_sequence{'O', 'H', false, { "" }}
        });
}

void terminal_read_test::cursor_end_ss3_yields_vk_end()
{
    expect_token(
        "\x1BOF",
        terminalpp::virtual_key {
            terminalpp::VK_END,
            0,
            1,
            terminalpp::ansi::control_sequence{'O', 'F', false, { "" }}
        });
}

