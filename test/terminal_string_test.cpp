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
        
        CPPUNIT_TEST(bold_intensity_outputs_intensity);
        CPPUNIT_TEST(faint_intensity_outputs_intensity);
        CPPUNIT_TEST(normal_intensity_does_not_output_intensity);
        CPPUNIT_TEST(bold_then_normal_intensity_outputs_intensity);
        CPPUNIT_TEST(default_intensity_is_normal_intensity);
        
        CPPUNIT_TEST(positive_polarity_does_not_output_polarity);
        CPPUNIT_TEST(negative_polarity_outputs_polarity);
        CPPUNIT_TEST(negative_then_positive_polarity_outputs_polarity);
        CPPUNIT_TEST(default_polarity_is_positive_polarity);
        
        CPPUNIT_TEST(positive_underlining_outputs_underlining);
        CPPUNIT_TEST(negative_underlining_does_not_output_underlining);
        CPPUNIT_TEST(positive_then_negative_underlining_outputs_underlining);
        CPPUNIT_TEST(default_underlining_is_negative_underlining);

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
    
    void bold_intensity_outputs_intensity();
    void faint_intensity_outputs_intensity();
    void normal_intensity_does_not_output_intensity();
    void bold_then_normal_intensity_outputs_intensity();
    void default_intensity_is_normal_intensity();
    
    void positive_polarity_does_not_output_polarity();
    void negative_polarity_outputs_polarity();
    void negative_then_positive_polarity_outputs_polarity();
    void default_polarity_is_positive_polarity();
    
    void positive_underlining_outputs_underlining();
    void negative_underlining_does_not_output_underlining();
    void positive_then_negative_underlining_outputs_underlining();
    void default_underlining_is_negative_underlining();
    
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

void terminal_string_test_fixture::bold_intensity_outputs_intensity()
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("\x1B[1mabcde"),
        terminal.write("\\i>abcde"_ets));
}

void terminal_string_test_fixture::faint_intensity_outputs_intensity()
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("\x1B[2mabcde"),
        terminal.write("\\i<abcde"_ets));
}

void terminal_string_test_fixture::normal_intensity_does_not_output_intensity()
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("abcde"),
        terminal.write("\\i=abcde"_ets));
}

void terminal_string_test_fixture::bold_then_normal_intensity_outputs_intensity()
{
    // Note: an alternative possible normal string would be 
    // \x1B[22m, but since this is longer, \x1B[0m (all attributes to default)
    // should be chosen.
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("\x1B[1mabc\x1B[0mde"),
        terminal.write("\\i>abc\\i=de"_ets));
}

void terminal_string_test_fixture::default_intensity_is_normal_intensity()
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("\x1B[1mabc\x1B[0mde"),
        terminal.write("\\i>abc\\ixde"_ets));
}

void terminal_string_test_fixture::positive_polarity_does_not_output_polarity()
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("abcde"),
        terminal.write("\\p+abcde"_ets));
}

void terminal_string_test_fixture::negative_polarity_outputs_polarity()
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("\x1B[7mabcde"),
        terminal.write("\\p-abcde"_ets));
}

void terminal_string_test_fixture::negative_then_positive_polarity_outputs_polarity()
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("\x1B[7mabc\x1B[0mde"),
        terminal.write("\\p-abc\\p+de"_ets));
}

void terminal_string_test_fixture::default_polarity_is_positive_polarity()
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("\x1B[7mabc\x1B[0mde"),
        terminal.write("\\p-abc\\p=de"_ets));
}

void terminal_string_test_fixture::positive_underlining_outputs_underlining()
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("\x1B[4mabcde"),
        terminal.write("\\u+abcde"_ets));
}

void terminal_string_test_fixture::negative_underlining_does_not_output_underlining()
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("abcde"),
        terminal.write("\\u-abcde"_ets));
}

void terminal_string_test_fixture::positive_then_negative_underlining_outputs_underlining()
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("\x1B[4mabc\x1B[0mde"),
        terminal.write("\\u+abc\\u-de"_ets));
}

void terminal_string_test_fixture::default_underlining_is_negative_underlining()
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("\x1B[4mabc\x1B[0mde"),
        terminal.write("\\u+abc\\u=de"_ets));
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


