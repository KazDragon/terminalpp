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
        /*
        parser empty string yields nothing
        parse text yields text
        parse command yields command
        parse meta command yields meta command
        parse mouse command yield mouse command
        -- all above for both 7- and 8- bit.

        parse partial command yields nothing
        parse partial mouse command yields nothing
        */
    CPPUNIT_TEST_SUITE_END();

private :
    void parse_empty_string_yields_nothing();
    void parse_character_yields_virtual_key();
    void parse_command_yields_command();
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