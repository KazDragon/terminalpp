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
};

CPPUNIT_TEST_SUITE_REGISTRATION(terminal_read_test);

void terminal_read_test::read_empty_string_yields_nothing()
{
    terminalpp::terminal terminal;

    std::string input = "";

    auto result = terminal.read(input);

    CPPUNIT_ASSERT_EQUAL(size_t{0}, result.size());
}

void terminal_read_test::read_character_yields_virtual_key()
{
    terminalpp::terminal terminal;

    std::string input = "z";

    auto expected = std::vector<terminalpp::token>{
        terminalpp::virtual_key {
            terminalpp::VK_LOWERCASE_Z,
            0,
            1,
            { input[0] }
        }
    };

    auto result = terminal.read(input);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::virtual_key>(expected[0]),
        boost::get<terminalpp::virtual_key>(result[0]));
}

void terminal_read_test::read_command_yields_command()
{
    terminalpp::terminal terminal;

    std::string input = "\x1B[H";

    auto expected = std::vector<terminalpp::token>{
        terminalpp::ansi::control_sequence {
            '[',
            'H',
            false,
            { "" }
        }
    };

    auto result = terminal.read(input);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::control_sequence>(expected[0]),
        boost::get<terminalpp::ansi::control_sequence>(result[0]));
}

void terminal_read_test::read_command_with_arguments_yields_command_with_arguments()
{
    terminalpp::terminal terminal;

    std::string input = "\x1B[22;33H";

    auto expected = std::vector<terminalpp::token> {
        terminalpp::ansi::control_sequence {
            '[',
            'H',
            false,
            { "22", "33" }
        }
    };

    auto result = terminal.read(input);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::control_sequence>(expected[0]),
        boost::get<terminalpp::ansi::control_sequence>(result[0]));
}

void terminal_read_test::read_meta_command_yields_meta_command()
{
    terminalpp::terminal terminal;

    std::string input = "\x1B\x1B[A";

    auto expected = std::vector<terminalpp::token> {
        terminalpp::ansi::control_sequence {
            '[',
            'A',
            true,
            { "" }
        }
    };

    auto result = terminal.read(input);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::control_sequence>(expected[0]),
        boost::get<terminalpp::ansi::control_sequence>(result[0]));
}

void terminal_read_test::read_mouse_command_yields_mouse_report()
{
    terminalpp::terminal terminal;

    std::string input = "\x1B[M @B";

    auto expected = std::vector<terminalpp::token> {
        terminalpp::ansi::mouse::report {
            terminalpp::ansi::mouse::report::LEFT_BUTTON_DOWN,
            32,
            34
        }
    };

    auto result = terminal.read(input);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::mouse::report>(expected[0]),
        boost::get<terminalpp::ansi::mouse::report>(result[0]));
}

void terminal_read_test::read_non_mouse_similar_command_yields_command()
{
    terminalpp::terminal terminal;

    std::string input = "\x1B?M";

    auto expected = std::vector<terminalpp::token> {
        terminalpp::ansi::control_sequence {
            '?',
            'M',
            false,
            { "" }
        }
    };

    auto result = terminal.read(input);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::control_sequence>(expected[0]),
        boost::get<terminalpp::ansi::control_sequence>(result[0]));
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
    terminalpp::terminal terminal;

    std::string input = "\x9B""22;33H";

    auto expected = std::vector<terminalpp::token> {
        terminalpp::ansi::control_sequence {
            '[',
            'H',
            false,
            { "22", "33" }
        }
    };

    auto result = terminal.read(input);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::control_sequence>(expected[0]),
        boost::get<terminalpp::ansi::control_sequence>(result[0]));
}
