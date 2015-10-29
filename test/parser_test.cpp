#include "terminalpp/detail/parser.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class parser_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(parser_test);
        CPPUNIT_TEST(parse_empty_string_yields_nothing);
        CPPUNIT_TEST(parse_character_yields_virtual_key);
        CPPUNIT_TEST(parse_command_yields_command);
        CPPUNIT_TEST(parse_command_with_arguments_yields_command_with_arguments);
        CPPUNIT_TEST(parse_meta_command_yields_meta_command);
        CPPUNIT_TEST(parse_mouse_command_yields_mouse_report);
        CPPUNIT_TEST(parse_non_mouse_similar_command_yields_command);
        CPPUNIT_TEST(parse_partial_command_yields_nothing);
        CPPUNIT_TEST(parse_partial_mouse_command_yields_nothing);
        /*
        TODO list
        parse upper case character yields shift modifier
        -- all above for both 7- and 8- bit.
        */
    CPPUNIT_TEST_SUITE_END();

private :
    void parse_empty_string_yields_nothing();
    void parse_character_yields_virtual_key();
    void parse_command_yields_command();
    void parse_command_with_arguments_yields_command_with_arguments();
    void parse_meta_command_yields_meta_command();
    void parse_mouse_command_yields_mouse_report();
    void parse_non_mouse_similar_command_yields_command();
    void parse_partial_command_yields_nothing();
    void parse_partial_mouse_command_yields_nothing();
};

CPPUNIT_TEST_SUITE_REGISTRATION(parser_test);

void parser_test::parse_empty_string_yields_nothing()
{
    std::string input = "";
    auto begin = input.begin();
    auto end = input.end();

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(size_t{0}, result.size());
    CPPUNIT_ASSERT(begin == end);
}

void parser_test::parse_character_yields_virtual_key()
{
    std::string input = "z";
    auto begin = input.begin();
    auto end = input.end();

    auto expected = std::vector<terminalpp::token>{
        terminalpp::virtual_key {
            terminalpp::VK_LOWERCASE_Z,
            0,
            { input[0] }
        }
    };

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::virtual_key>(expected[0]),
        boost::get<terminalpp::virtual_key>(result[0]));
    CPPUNIT_ASSERT(begin == end);
}

void parser_test::parse_command_yields_command()
{
    std::string input = "\x1B[H";
    auto begin = input.begin();
    auto end = input.end();

    auto expected = std::vector<terminalpp::token>{
        terminalpp::ansi::control_sequence {
            '[',
            'H',
            false,
            { 0 }
        }
    };

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::control_sequence>(expected[0]),
        boost::get<terminalpp::ansi::control_sequence>(result[0]));
    CPPUNIT_ASSERT(begin == end);
}

void parser_test::parse_command_with_arguments_yields_command_with_arguments()
{
    std::string input = "\x1B[22;33H";
    auto begin = input.begin();
    auto end = input.end();

    auto expected = std::vector<terminalpp::token> {
        terminalpp::ansi::control_sequence {
            '[',
            'H',
            false,
            { 22, 33 }
        }
    };

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::control_sequence>(expected[0]),
        boost::get<terminalpp::ansi::control_sequence>(result[0]));
    CPPUNIT_ASSERT(begin == end);
}

void parser_test::parse_meta_command_yields_meta_command()
{
    std::string input = "\x1B\x1B[A";
    auto begin = input.begin();
    auto end = input.end();

    auto expected = std::vector<terminalpp::token> {
        terminalpp::ansi::control_sequence {
            '[',
            'A',
            true,
            { 0 }
        }
    };

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::control_sequence>(expected[0]),
        boost::get<terminalpp::ansi::control_sequence>(result[0]));
    CPPUNIT_ASSERT(begin == end);
}

void parser_test::parse_mouse_command_yields_mouse_report()
{
    std::string input = "\x1B[M @B";
    auto begin = input.begin();
    auto end = input.end();

    auto expected = std::vector<terminalpp::token> {
        terminalpp::ansi::mouse::report {
            terminalpp::ansi::mouse::report::LEFT_BUTTON_DOWN,
            32,
            34
        }
    };

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::mouse::report>(expected[0]),
        boost::get<terminalpp::ansi::mouse::report>(result[0]));
    CPPUNIT_ASSERT(begin == end);
}

void parser_test::parse_non_mouse_similar_command_yields_command()
{
    std::string input = "\x1B?M";
    auto begin = input.begin();
    auto end = input.end();

    auto expected = std::vector<terminalpp::token> {
        terminalpp::ansi::control_sequence {
            '?',
            'M',
            false,
            { 0 }
        }
    };

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::control_sequence>(expected[0]),
        boost::get<terminalpp::ansi::control_sequence>(result[0]));
    CPPUNIT_ASSERT(begin == end);
}

void parser_test::parse_partial_command_yields_nothing()
{
    std::string input = "\x1B[";
    auto begin = input.begin();
    auto end = input.end();

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(size_t{0}, result.size());
    CPPUNIT_ASSERT(begin == input.begin());
}

void parser_test::parse_partial_mouse_command_yields_nothing()
{
    std::string input = "\x1B[M";
    auto begin = input.begin();
    auto end = input.end();

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(size_t{0}, result.size());
    CPPUNIT_ASSERT(begin == input.begin());
}