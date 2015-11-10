#include "expect_tokens.hpp"
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

        CPPUNIT_TEST(f1_command_yields_vk_f1);
        CPPUNIT_TEST(f2_command_yields_vk_f2);
        CPPUNIT_TEST(f3_command_yields_vk_f3);
        CPPUNIT_TEST(f4_command_yields_vk_f4);

        CPPUNIT_TEST(f1_ss3_yields_vk_f1);
        CPPUNIT_TEST(f2_ss3_yields_vk_f2);
        CPPUNIT_TEST(f3_ss3_yields_vk_f3);
        CPPUNIT_TEST(f4_ss3_yields_vk_f4);

        /* TODO:
         * Read of OSC/PM/APC commands with ST/BEL terminators - and 8bit
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

    void f1_command_yields_vk_f1();
    void f2_command_yields_vk_f2();
    void f3_command_yields_vk_f3();
    void f4_command_yields_vk_f4();

    void f1_ss3_yields_vk_f1();
    void f2_ss3_yields_vk_f2();
    void f3_ss3_yields_vk_f3();
    void f4_ss3_yields_vk_f4();
};

CPPUNIT_TEST_SUITE_REGISTRATION(terminal_read_test);

void terminal_read_test::read_empty_string_yields_nothing()
{
    expect_tokens("", {});
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
        "\x1B[S",
        terminalpp::ansi::control_sequence {
            '[',
            'S',
            false,
            { "" }
        });
}

void terminal_read_test::read_command_with_arguments_yields_command_with_arguments()
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
    expect_tokens("\x1B[", {});
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
    expect_tokens("\x1B[M", {});
}

void terminal_read_test::read_8bit_command_yields_command()
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

void terminal_read_test::f1_command_yields_vk_f1()
{
    expect_token(
        "\x1B[11~",
        terminalpp::virtual_key {
            terminalpp::VK_F1,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "11" }}
        });
}

void terminal_read_test::f2_command_yields_vk_f2()
{
    expect_token(
        "\x1B[12~",
        terminalpp::virtual_key {
            terminalpp::VK_F2,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "12" }}
        });
}

void terminal_read_test::f3_command_yields_vk_f3()
{
    expect_token(
        "\x1B[13~",
        terminalpp::virtual_key {
            terminalpp::VK_F3,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "13" }}
        });
}

void terminal_read_test::f4_command_yields_vk_f4()
{
    expect_token(
        "\x1B[14~",
        terminalpp::virtual_key {
            terminalpp::VK_F4,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "14" }}
        });
}

void terminal_read_test::f1_ss3_yields_vk_f1()
{
    expect_token(
        "\x1BOP",
        terminalpp::virtual_key {
            terminalpp::VK_F1,
            0,
            1,
            terminalpp::ansi::control_sequence{'O', 'P', false, { "" }}
        });
}

void terminal_read_test::f2_ss3_yields_vk_f2()
{
    expect_token(
        "\x1BOQ",
        terminalpp::virtual_key {
            terminalpp::VK_F2,
            0,
            1,
            terminalpp::ansi::control_sequence{'O', 'Q', false, { "" }}
        });
}

void terminal_read_test::f3_ss3_yields_vk_f3()
{
    expect_token(
        "\x1BOR",
        terminalpp::virtual_key {
            terminalpp::VK_F3,
            0,
            1,
            terminalpp::ansi::control_sequence{'O', 'R', false, { "" }}
        });
}

void terminal_read_test::f4_ss3_yields_vk_f4()
{
    expect_token(
        "\x1BOS",
        terminalpp::virtual_key {
            terminalpp::VK_F4,
            0,
            1,
            terminalpp::ansi::control_sequence{'O', 'S', false, { "" }}
        });
}

