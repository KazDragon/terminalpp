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
        
        CPPUNIT_TEST(writing_string_moves_cursor);
        CPPUNIT_TEST(writing_past_terminal_width_moves_cursor_to_next_line);
        CPPUNIT_TEST(writing_far_past_terminal_width_moves_multiple_lines);
        CPPUNIT_TEST(writing_past_last_line_scrolls_last_line);
    CPPUNIT_TEST_SUITE_END();
    
private :
    void empty_string_outputs_nothing();
    void basic_string_outputs_basic_string();
    
    void changed_charset_outputs_charset_code();
    void changed_charset_then_second_charset_outputs_charset_codes();
    
    void writing_string_moves_cursor();
    void writing_past_terminal_width_moves_cursor_to_next_line();
    void writing_far_past_terminal_width_moves_multiple_lines();
    void writing_past_last_line_scrolls_last_line();
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

void terminal_string_test_fixture::writing_string_moves_cursor()
{
    terminalpp::terminal terminal;
    
    terminal.move_cursor({5, 5});
    terminal.write("abcde");
    
    expect_sequence(
        std::string(""),
        terminal.move_cursor({10, 5}));
}

void terminal_string_test_fixture::writing_past_terminal_width_moves_cursor_to_next_line()
{
    terminalpp::terminal terminal;
    terminal.set_size({10, 10});
    terminal.move_cursor({8, 8});
    terminal.write("abcde");
    
    expect_sequence(
        std::string(""),
        terminal.move_cursor({3, 9}));
}

void terminal_string_test_fixture::writing_far_past_terminal_width_moves_multiple_lines()
{
    terminalpp::terminal terminal;
    terminal.set_size({10, 10});
    terminal.move_cursor({8, 8});
    terminal.write("abcdefghijklmno");
    
    expect_sequence(
        std::string(""),
        terminal.move_cursor({3, 10}));
}

void terminal_string_test_fixture::writing_past_last_line_scrolls_last_line()
{
    terminalpp::terminal terminal;
    terminal.set_size({10, 10});
    terminal.move_cursor({8, 10});
    terminal.write("abcdefghijklmno");
    
    expect_sequence(
        std::string(""),
        terminal.move_cursor({3, 10}));
}


