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

        CPPUNIT_TEST(f5_command_yields_vk_f5);
        CPPUNIT_TEST(f6_command_yields_vk_f6);
        CPPUNIT_TEST(f7_command_yields_vk_f7);
        CPPUNIT_TEST(f8_command_yields_vk_f8);
        CPPUNIT_TEST(f9_command_yields_vk_f9);
        CPPUNIT_TEST(f10_command_yields_vk_f10);
        CPPUNIT_TEST(f11_command_yields_vk_f11);
        CPPUNIT_TEST(f12_command_yields_vk_f12);

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

    void f5_command_yields_vk_f5();
    void f6_command_yields_vk_f6();
    void f7_command_yields_vk_f7();
    void f8_command_yields_vk_f8();
    void f9_command_yields_vk_f9();
    void f10_command_yields_vk_f10();
    void f11_command_yields_vk_f11();
    void f12_command_yields_vk_f12();

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
            terminalpp::vk::f1,
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
            terminalpp::vk::f2,
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
            terminalpp::vk::f3,
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
            terminalpp::vk::f4,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "14" }}
        });
}

void terminal_read_fkey_test::f5_command_yields_vk_f5()
{
    expect_token(
        "\x1B[15~",
        terminalpp::virtual_key {
            terminalpp::vk::f5,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "15" }}
        });
}

void terminal_read_fkey_test::f6_command_yields_vk_f6()
{
    expect_token(
        "\x1B[17~",
        terminalpp::virtual_key {
            terminalpp::vk::f6,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "17" }}
        });
}

void terminal_read_fkey_test::f7_command_yields_vk_f7()
{
    expect_token(
        "\x1B[18~",
        terminalpp::virtual_key {
            terminalpp::vk::f7,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "18" }}
        });
}

void terminal_read_fkey_test::f8_command_yields_vk_f8()
{
    expect_token(
        "\x1B[19~",
        terminalpp::virtual_key {
            terminalpp::vk::f8,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "19" }}
        });
}

void terminal_read_fkey_test::f9_command_yields_vk_f9()
{
    expect_token(
        "\x1B[20~",
        terminalpp::virtual_key {
            terminalpp::vk::f9,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "20" }}
        });
}

void terminal_read_fkey_test::f10_command_yields_vk_f10()
{
    expect_token(
        "\x1B[21~",
        terminalpp::virtual_key {
            terminalpp::vk::f10,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "21" }}
        });
}

void terminal_read_fkey_test::f11_command_yields_vk_f11()
{
    expect_token(
        "\x1B[23~",
        terminalpp::virtual_key {
            terminalpp::vk::f11,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "23" }}
        });
}

void terminal_read_fkey_test::f12_command_yields_vk_f12()
{
    expect_token(
        "\x1B[24~",
        terminalpp::virtual_key {
            terminalpp::vk::f12,
            0,
            1,
            terminalpp::ansi::control_sequence{'[', '~', false, { "24" }}
        });
}


void terminal_read_fkey_test::f1_ss3_yields_vk_f1()
{
    expect_token(
        "\x1BOP",
        terminalpp::virtual_key {
            terminalpp::vk::f1,
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
            terminalpp::vk::f2,
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
            terminalpp::vk::f3,
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
            terminalpp::vk::f4,
            0,
            1,
            terminalpp::ansi::control_sequence{'O', 'S', false, { "" }}
        });
}

