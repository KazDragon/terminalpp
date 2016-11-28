#include "terminalpp/terminal.hpp"
#include "expect_sequence.hpp"
#include <gtest/gtest.h>

using namespace terminalpp::literals;

TEST(terminal_string_test, empty_string_outputs_nothing)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string(""),
        terminal.write(""_ets));
}

TEST(terminal_string_test, basic_string_outputs_basic_string)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("abcde"),
        terminal.write("abcde"_ets));
}

TEST(terminal_string_test, changed_charset_outputs_charset_code)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B(0abcde"),
        terminal.write("\\c0abcde"_ets));
}

TEST(terminal_string_test, changed_charset_then_second_charset_outputs_charset_codes)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B(0abc\x1B(Ade"),
        terminal.write("\\c0abc\\cAde"_ets));
}

TEST(terminal_string_test, bold_intensity_outputs_intensity)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[1mabcde"),
        terminal.write("\\i>abcde"_ets));
}

TEST(terminal_string_test, faint_intensity_outputs_intensity)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[2mabcde"),
        terminal.write("\\i<abcde"_ets));
}

TEST(terminal_string_test, normal_intensity_does_not_output_intensity)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("abcde"),
        terminal.write("\\i=abcde"_ets));
}

TEST(terminal_string_test, bold_then_normal_intensity_outputs_intensity)
{
    // Note: an alternative possible normal string would be
    // \x1B[22m, but since this is longer, \x1B[0m (all attributes to default)
    // should be chosen.
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[1mabc\x1B[0mde"),
        terminal.write("\\i>abc\\i=de"_ets));
}

TEST(terminal_string_test, default_intensity_is_normal_intensity)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[1mabc\x1B[0mde"),
        terminal.write("\\i>abc\\ixde"_ets));
}

TEST(terminal_string_test, positive_polarity_does_not_output_polarity)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("abcde"),
        terminal.write("\\p+abcde"_ets));
}

TEST(terminal_string_test, negative_polarity_outputs_polarity)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[7mabcde"),
        terminal.write("\\p-abcde"_ets));
}

TEST(terminal_string_test, negative_then_positive_polarity_outputs_polarity)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[7mabc\x1B[0mde"),
        terminal.write("\\p-abc\\p+de"_ets));
}

TEST(terminal_string_test, default_polarity_is_positive_polarity)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[7mabc\x1B[0mde"),
        terminal.write("\\p-abc\\p=de"_ets));
}

TEST(terminal_string_test, positive_underlining_outputs_underlining)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[4mabcde"),
        terminal.write("\\u+abcde"_ets));
}

TEST(terminal_string_test, negative_underlining_does_not_output_underlining)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("abcde"),
        terminal.write("\\u-abcde"_ets));
}

TEST(terminal_string_test, positive_then_negative_underlining_outputs_underlining)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[4mabc\x1B[0mde"),
        terminal.write("\\u+abc\\u-de"_ets));
}

TEST(terminal_string_test, default_underlining_is_negative_underlining)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[4mabc\x1B[0mde"),
        terminal.write("\\u+abc\\u=de"_ets));
}

TEST(terminal_string_test, foreground_low_colour_outputs_foreground_colour)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[32mabc"),
        terminal.write("\\[2abc"_ets));
}

TEST(terminal_string_test, foreground_high_colour_outputs_foreground_colour)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[38;5;202mabc"),
        terminal.write("\\<510abc"_ets));
}

TEST(terminal_string_test, foreground_greyscale_colour_outputs_foreground_colour)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[38;5;244mabc"),
        terminal.write("\\{12abc"_ets));
}

TEST(terminal_string_test, default_foreground_colour_does_not_output_foreground_colour)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("abc"),
        terminal.write("\\[9abc"_ets));
}

TEST(terminal_string_test, multiple_foreground_colour_codes_outputs_foreground_colours)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[32mab\x1B[38;5;202mcd\x1B[38;5;234mef\x1B[0mgh"),
        terminal.write("\\[2ab\\<510cd\\{02ef\\[9gh"_ets));
}


TEST(terminal_string_test, background_low_colour_outputs_background_colour)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[42mabc"),
        terminal.write("\\]2abc"_ets));
}

TEST(terminal_string_test, background_high_colour_outputs_background_colour)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[48;5;202mabc"),
        terminal.write("\\>510abc"_ets));
}

TEST(terminal_string_test, background_greyscale_colour_outputs_background_colour)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[48;5;244mabc"),
        terminal.write("\\}12abc"_ets));
}

TEST(terminal_string_test, default_background_colour_does_not_output_background_colour)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("abc"),
        terminal.write("\\]9abc"_ets));
}

TEST(terminal_string_test, multiple_background_colour_codes_outputs_background_colours)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[42mab\x1B[48;5;75mcd\x1B[48;5;234mef\x1B[0mgh"),
        terminal.write("\\]2ab\\>135cd\\}02ef\\]9gh"_ets));
}

TEST(terminal_string_test, multiple_attributes_do_not_output_default_change)
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

TEST(terminal_string_test, writing_string_moves_cursor)
{
    terminalpp::terminal terminal;

    terminal.move_cursor({5, 5});
    terminal.write("abcde");

    expect_sequence(
        std::string(""),
        terminal.move_cursor({10, 5}));
}

TEST(terminal_string_test, encoded_glyphs_output_unicode_text)
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

TEST(terminal_string_test, writing_past_terminal_width_moves_cursor_to_next_line)
{
    terminalpp::terminal terminal;
    terminal.set_size({10, 10});
    terminal.move_cursor({8, 8});
    terminal.write("abcde");

    expect_sequence(
        std::string(""),
        terminal.move_cursor({3, 9}));
}

TEST(terminal_string_test, writing_far_past_terminal_width_moves_multiple_lines)
{
    terminalpp::terminal terminal;
    terminal.set_size({10, 10});
    terminal.move_cursor({8, 8});
    terminal.write("abcdefghijklmno");

    expect_sequence(
        std::string(""),
        terminal.move_cursor({3, 10}));
}

TEST(terminal_string_test, writing_past_last_line_scrolls_last_line)
{
    terminalpp::terminal terminal;
    terminal.set_size({10, 10});
    terminal.move_cursor({8, 10});
    terminal.write("abcdefghijklmno");

    expect_sequence(
        std::string(""),
        terminal.move_cursor({3, 10}));
}

TEST(terminal_string_test, can_write_single_element)
{
    terminalpp::terminal terminal;
    terminalpp::element  elem('X');
    elem.attribute_.foreground_colour_ =
        terminalpp::ansi::graphics::colour::red;

    expect_sequence(
        std::string("\x1B[31mX"),
        terminal.write(elem));
}

TEST(terminal_string_test, writing_single_element_moves_cursor)
{
    terminalpp::terminal terminal;
    terminal.set_size({5, 5});
    terminal.move_cursor({0, 0});
    terminal.write('x');

    expect_sequence(
        std::string(""),
        terminal.move_cursor({1, 0}));
}

TEST(terminal_string_test, writing_unicode_after_default_charset_does_not_change_charset_first)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string(" \x1B%GW"),
        terminal.write(" \\U0057"_ets));
}

TEST(terminal_string_test, writing_unicode_after_sco_charset_reverts_charset_first)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B(U\xCD\x1B(B\x1B%GW"),
        terminal.write("\\cU\\C205\\U0057"_ets));
}

TEST(terminal_string_test, behaviour_unicode_in_all_charsets_writing_unicode_after_sco_does_not_change_charset_first)
{
    terminalpp::terminal::behaviour behaviour;
    behaviour.unicode_in_all_charsets = true;

    terminalpp::terminal terminal(behaviour);
    expect_sequence(
        std::string("\x1B(U\xCD\x1B%GW"),
        terminal.write("\\cU\\C205\\U0057"_ets));

}

TEST(terminal_string_test, changing_character_set_after_unicode_first_selects_default_charset)
{
    terminalpp::terminal terminal;
    expect_sequence(
        std::string("\x1B%GW\x1B%@\x1B(A\x9C"),
        terminal.write("\\U0057\\cA\\C156"_ets));
}
