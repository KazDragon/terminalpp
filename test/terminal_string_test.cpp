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

        CPPUNIT_TEST(foreground_low_colour_outputs_foreground_colour);
        CPPUNIT_TEST(foreground_high_colour_outputs_foreground_colour);
        CPPUNIT_TEST(foreground_greyscale_colour_outputs_foreground_colour);
        CPPUNIT_TEST(default_foreground_colour_does_not_output_foreground_colour);
        CPPUNIT_TEST(multiple_foreground_colour_codes_outputs_foreground_colours);

        CPPUNIT_TEST(background_low_colour_outputs_background_colour);
        CPPUNIT_TEST(background_high_colour_outputs_background_colour);
        CPPUNIT_TEST(background_greyscale_colour_outputs_background_colour);
        CPPUNIT_TEST(default_background_colour_does_not_output_background_colour);
        CPPUNIT_TEST(multiple_background_colour_codes_outputs_background_colours);

        CPPUNIT_TEST(multiple_attributes_do_not_output_default_change);
        CPPUNIT_TEST(encoded_glyphs_output_unicode_text);

        CPPUNIT_TEST(writing_string_moves_cursor);
        CPPUNIT_TEST(writing_past_terminal_width_moves_cursor_to_next_line);
        CPPUNIT_TEST(writing_far_past_terminal_width_moves_multiple_lines);
        CPPUNIT_TEST(writing_past_last_line_scrolls_last_line);
        
        CPPUNIT_TEST(can_write_single_element);
        CPPUNIT_TEST(writing_single_element_moves_cursor);
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

    void foreground_low_colour_outputs_foreground_colour();
    void foreground_high_colour_outputs_foreground_colour();
    void foreground_greyscale_colour_outputs_foreground_colour();
    void default_foreground_colour_does_not_output_foreground_colour();
    void multiple_foreground_colour_codes_outputs_foreground_colours();

    void background_low_colour_outputs_background_colour();
    void background_high_colour_outputs_background_colour();
    void background_greyscale_colour_outputs_background_colour();
    void default_background_colour_does_not_output_background_colour();
    void multiple_background_colour_codes_outputs_background_colours();

    void multiple_attributes_do_not_output_default_change();
    void encoded_glyphs_output_unicode_text();

    void writing_string_moves_cursor();
    void writing_past_terminal_width_moves_cursor_to_next_line();
    void writing_far_past_terminal_width_moves_multiple_lines();
    void writing_past_last_line_scrolls_last_line();
    
    void can_write_single_element();
    void writing_single_element_moves_cursor();
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

void terminal_string_test_fixture::foreground_low_colour_outputs_foreground_colour()
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[32mabc"),
        terminal.write("\\[2abc"_ets));
}

void terminal_string_test_fixture::foreground_high_colour_outputs_foreground_colour()
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[38;5;202mabc"),
        terminal.write("\\<510abc"_ets));
}

void terminal_string_test_fixture::foreground_greyscale_colour_outputs_foreground_colour()
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[38;5;244mabc"),
        terminal.write("\\{12abc"_ets));
}

void terminal_string_test_fixture::default_foreground_colour_does_not_output_foreground_colour()
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("abc"),
        terminal.write("\\[9abc"_ets));
}

void terminal_string_test_fixture::multiple_foreground_colour_codes_outputs_foreground_colours()
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[32mab\x1B[38;5;202mcd\x1B[38;5;234mef\x1B[0mgh"),
        terminal.write("\\[2ab\\<510cd\\{02ef\\[9gh"_ets));
}


void terminal_string_test_fixture::background_low_colour_outputs_background_colour()
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[42mabc"),
        terminal.write("\\]2abc"_ets));
}

void terminal_string_test_fixture::background_high_colour_outputs_background_colour()
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[48;5;202mabc"),
        terminal.write("\\>510abc"_ets));
}

void terminal_string_test_fixture::background_greyscale_colour_outputs_background_colour()
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[48;5;244mabc"),
        terminal.write("\\}12abc"_ets));
}

void terminal_string_test_fixture::default_background_colour_does_not_output_background_colour()
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("abc"),
        terminal.write("\\]9abc"_ets));
}

void terminal_string_test_fixture::multiple_background_colour_codes_outputs_background_colours()
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[42mab\x1B[48;5;75mcd\x1B[48;5;234mef\x1B[0mgh"),
        terminal.write("\\]2ab\\>135cd\\}02ef\\]9gh"_ets));
}

void terminal_string_test_fixture::multiple_attributes_do_not_output_default_change()
{
    // Test that, when switching off and on multiple attributes, they do not in
    // general go back to default.  Instead, they should toggle specific flags.
    // NOTE: At a later date, it may be implemented that the algorithm will
    // branch and look for strategies for producing the shortest sequence.
    // In that case, it may be that switching several attributes off is longer
    // than switching to default then re-enabling one attribute.  It also may
    // be determined by environment - different terminals behave differently.
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[32;41ma\x1B[7mb\x1B[27mc"),
        terminal.write("\\[2\\]1a\\p-b\\p+c"_ets));
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

void terminal_string_test_fixture::encoded_glyphs_output_unicode_text()
{
    // If a string contains a four-hexdigit unicode code, then
    // it should be output as a unicode character if it can be.
    // This will include commands to change to and from the utf-8
    // character set and also to reset the character set at the end.
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B%GW"),
        terminal.write("\\U0057"_ets));

    expect_sequence(
        std::string("\xC4\x8E"),
        terminal.write("\\U010E"_ets));

    expect_sequence(
        std::string("\xE1\x9A\xB8"),
        terminal.write("\\U16B8"_ets));
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

void terminal_string_test_fixture::can_write_single_element()
{
    terminalpp::terminal terminal;
    terminalpp::element  elem('X');
    elem.attribute_.foreground_colour_ = 
        terminalpp::ansi::graphics::colour::red;
    
    expect_sequence(
        std::string("\x1B[31mX"),
        terminal.write(elem));
}

void terminal_string_test_fixture::writing_single_element_moves_cursor()
{
    terminalpp::terminal terminal;
    terminal.set_size({5, 5});
    terminal.move_cursor({0, 0});
    terminal.write('x');
    
    expect_sequence(
        std::string(""),
        terminal.move_cursor({1, 0}));
}


