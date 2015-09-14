#include "terminalpp/terminal.hpp"
#include "expect_sequence.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace terminalpp::literals;

class terminal_string_test_fixture : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(terminal_string_test_fixture);
        CPPUNIT_TEST(empty_string_outputs_nothing);
        CPPUNIT_TEST(basic_string_outputs_basic_string);

        CPPUNIT_TEST(changed_charset_outputs_charset_code);
        CPPUNIT_TEST(changed_charset_then_second_charset_outputs_charset_codes);
    CPPUNIT_TEST_SUITE_END();
    
private :
    void empty_string_outputs_nothing();
    void basic_string_outputs_basic_string();
    
    void changed_charset_outputs_charset_code();
    void changed_charset_then_second_charset_outputs_charset_codes();
};

CPPUNIT_TEST_SUITE_REGISTRATION(terminal_string_test_fixture);

void terminal_string_test_fixture::empty_string_outputs_nothing()
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string(""),
        terminal.write(""_ets));
}

void terminal_string_test_fixture::basic_string_outputs_basic_string()
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("abcde"),
        terminal.write("abcde"_ets));
}

void terminal_string_test_fixture::changed_charset_outputs_charset_code()
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("\x1B(0abcde"),
        terminal.write("\\c0abcde"_ets));
}

void terminal_string_test_fixture::changed_charset_then_second_charset_outputs_charset_codes()
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("\x1B(0abc\x1B(Ade"),
        terminal.write("\\c0abc\\cAde"_ets));
}
