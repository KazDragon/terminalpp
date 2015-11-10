#include "expect_tokens.hpp"
#include "terminalpp/terminal.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class terminal_read_fkey_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(terminal_read_fkey_test);
        CPPUNIT_TEST(f1_command_yields_vk_f1);
        CPPUNIT_TEST(f2_command_yields_vk_f2);
        CPPUNIT_TEST(f3_command_yields_vk_f3);
        CPPUNIT_TEST(f4_command_yields_vk_f4);

        CPPUNIT_TEST(f1_ss3_yields_vk_f1);
        CPPUNIT_TEST(f2_ss3_yields_vk_f2);
        CPPUNIT_TEST(f3_ss3_yields_vk_f3);
        CPPUNIT_TEST(f4_ss3_yields_vk_f4);
    CPPUNIT_TEST_SUITE_END();

private :
    void f1_command_yields_vk_f1();
    void f2_command_yields_vk_f2();
    void f3_command_yields_vk_f3();
    void f4_command_yields_vk_f4();

    void f1_ss3_yields_vk_f1();
    void f2_ss3_yields_vk_f2();
    void f3_ss3_yields_vk_f3();
    void f4_ss3_yields_vk_f4();
};

CPPUNIT_TEST_SUITE_REGISTRATION(terminal_read_fkey_test);

void terminal_read_fkey_test::f1_command_yields_vk_f1()
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

void terminal_read_fkey_test::f2_command_yields_vk_f2()
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

void terminal_read_fkey_test::f3_command_yields_vk_f3()
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

void terminal_read_fkey_test::f4_command_yields_vk_f4()
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

void terminal_read_fkey_test::f1_ss3_yields_vk_f1()
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

void terminal_read_fkey_test::f2_ss3_yields_vk_f2()
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

void terminal_read_fkey_test::f3_ss3_yields_vk_f3()
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

void terminal_read_fkey_test::f4_ss3_yields_vk_f4()
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

