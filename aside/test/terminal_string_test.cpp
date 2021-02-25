#include "terminal_test.hpp"
#include "expect_sequence.hpp"
#include <gtest/gtest.h>

using namespace terminalpp::literals;

TEST(terminal_string_test, empty_string_outputs_default_attributes)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[0m"),
        terminal.write(""_ets));
}

TEST(terminal_string_test, outputting_an_empty_string_after_an_empty_string_outputs_nothing)
{
    terminalpp::terminal terminal;
    terminal.write(""_ets);

    expect_sequence(
        std::string(""),
        terminal.write(""_ets));
}

TEST(terminal_string_test, basic_string_outputs_default_attributes_and_basic_string)
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string("\x1B[0mabcde"),
        terminal.write("abcde"_ets));
}

TEST(terminal_string_test, outputting_another_basic_string_does_not_output_default_attributes)
{
    terminalpp::terminal terminal;
    terminal.write("abcde"_ets);

    expect_sequence(
        std::string("abcde"),
        terminal.write("abcde"_ets));
}

TEST_F(a_terminal, changed_charset_outputs_charset_code)
{
    expect_sequence(
        std::string("\x1B(0abcde"),
        terminal_.write("\\c0abcde"_ets));
}

TEST_F(a_terminal, changed_charset_then_second_charset_outputs_charset_codes)
{
    expect_sequence(
        std::string("\x1B(0abc\x1B(Ade"),
        terminal_.write("\\c0abc\\cAde"_ets));
}

TEST_F(a_terminal, bold_intensity_outputs_intensity)
{
    expect_sequence(
        std::string("\x1B[1mabcde"),
        terminal_.write("\\i>abcde"_ets));
}

TEST_F(a_terminal, faint_intensity_outputs_intensity)
{
    expect_sequence(
        std::string("\x1B[2mabcde"),
        terminal_.write("\\i<abcde"_ets));
}

TEST_F(a_terminal, normal_intensity_does_not_output_intensity)
{
    expect_sequence(
        std::string("abcde"),
        terminal_.write("\\i=abcde"_ets));
}

TEST_F(a_terminal, bold_then_normal_intensity_outputs_intensity)
{
    // Note: an alternative possible normal string would be
    // \x1B[22m, but since this is longer, \x1B[0m (all attributes to default)
    // should be chosen.
    expect_sequence(
        std::string("\x1B[1mabc\x1B[0mde"),
        terminal_.write("\\i>abc\\i=de"_ets));
}

TEST_F(a_terminal, default_intensity_is_normal_intensity)
{
    expect_sequence(
        std::string("\x1B[1mabc\x1B[0mde"),
        terminal_.write("\\i>abc\\ixde"_ets));
}

TEST_F(a_terminal, positive_polarity_does_not_output_polarity)
{
    expect_sequence(
        std::string("abcde"),
        terminal_.write("\\p+abcde"_ets));
}

TEST_F(a_terminal, negative_polarity_outputs_polarity)
{
    expect_sequence(
        std::string("\x1B[7mabcde"),
        terminal_.write("\\p-abcde"_ets));
}

TEST_F(a_terminal, negative_then_positive_polarity_outputs_polarity)
{
    expect_sequence(
        std::string("\x1B[7mabc\x1B[0mde"),
        terminal_.write("\\p-abc\\p+de"_ets));
}

TEST_F(a_terminal, default_polarity_is_positive_polarity)
{
    expect_sequence(
        std::string("\x1B[7mabc\x1B[0mde"),
        terminal_.write("\\p-abc\\p=de"_ets));
}

TEST_F(a_terminal, positive_underlining_outputs_underlining)
{
    expect_sequence(
        std::string("\x1B[4mabcde"),
        terminal_.write("\\u+abcde"_ets));
}

TEST_F(a_terminal, negative_underlining_does_not_output_underlining)
{
    expect_sequence(
        std::string("abcde"),
        terminal_.write("\\u-abcde"_ets));
}

TEST_F(a_terminal, positive_then_negative_underlining_outputs_underlining)
{
    expect_sequence(
        std::string("\x1B[4mabc\x1B[0mde"),
        terminal_.write("\\u+abc\\u-de"_ets));
}

TEST_F(a_terminal, default_underlining_is_negative_underlining)
{
    expect_sequence(
        std::string("\x1B[4mabc\x1B[0mde"),
        terminal_.write("\\u+abc\\u=de"_ets));
}

TEST_F(a_terminal, foreground_low_colour_outputs_foreground_colour)
{
    expect_sequence(
        std::string("\x1B[32mabc"),
        terminal_.write("\\[2abc"_ets));
}

TEST_F(a_terminal, foreground_high_colour_outputs_foreground_colour)
{
    expect_sequence(
        std::string("\x1B[38;5;202mabc"),
        terminal_.write("\\<510abc"_ets));
}

TEST_F(a_terminal, foreground_greyscale_colour_outputs_foreground_colour)
{
    expect_sequence(
        std::string("\x1B[38;5;244mabc"),
        terminal_.write("\\{12abc"_ets));
}

TEST_F(a_terminal, default_foreground_colour_does_not_output_foreground_colour)
{
    expect_sequence(
        std::string("abc"),
        terminal_.write("\\[9abc"_ets));
}

TEST_F(a_terminal, multiple_foreground_colour_codes_outputs_foreground_colours)
{
    expect_sequence(
        std::string("\x1B[32mab\x1B[38;5;202mcd\x1B[38;5;234mef\x1B[0mgh"),
        terminal_.write("\\[2ab\\<510cd\\{02ef\\[9gh"_ets));
}


TEST_F(a_terminal, background_low_colour_outputs_background_colour)
{
    expect_sequence(
        std::string("\x1B[42mabc"),
        terminal_.write("\\]2abc"_ets));
}

TEST_F(a_terminal, background_high_colour_outputs_background_colour)
{
    expect_sequence(
        std::string("\x1B[48;5;202mabc"),
        terminal_.write("\\>510abc"_ets));
}

TEST_F(a_terminal, background_greyscale_colour_outputs_background_colour)
{
    expect_sequence(
        std::string("\x1B[48;5;244mabc"),
        terminal_.write("\\}12abc"_ets));
}

TEST_F(a_terminal, default_background_colour_does_not_output_background_colour)
{
    expect_sequence(
        std::string("abc"),
        terminal_.write("\\]9abc"_ets));
}

TEST_F(a_terminal, multiple_background_colour_codes_outputs_background_colours)
{
    expect_sequence(
        std::string("\x1B[42mab\x1B[48;5;75mcd\x1B[48;5;234mef\x1B[0mgh"),
        terminal_.write("\\]2ab\\>135cd\\}02ef\\]9gh"_ets));
}

TEST_F(a_terminal, multiple_attributes_do_not_output_default_change)
{
    // Test that, when switching off and on multiple attributes, they do not in
    // general go back to default.  Instead, they should toggle specific flags.
    // NOTE: At a later date, it may be implemented that the algorithm will
    // branch and look for strategies for producing the shortest sequence.
    // In that case, it may be that switching several attributes off is longer
    // than switching to default then re-enabling one attribute.  It also may
    // be determined by environment - different terminals behave differently.
    expect_sequence(
        std::string("\x1B[32;41ma\x1B[7mb\x1B[27mc"),
        terminal_.write("\\[2\\]1a\\p-b\\p+c"_ets));
}

TEST_F(a_terminal, writing_string_moves_cursor)
{
    terminal_.move_cursor({5, 5});
    terminal_.write("abcde");

    expect_sequence(
        std::string(""),
        terminal_.move_cursor({10, 5}));
}

TEST_F(a_terminal, encoded_glyphs_output_unicode_text)
{
    // If a string contains a four-hexdigit unicode code, then
    // it should be output as a unicode character if it can be.
    // This will include commands to change to and from the utf-8
    // character set and also to reset the character set at the end.
    expect_sequence(
        std::string("\x1B%GW"),
        terminal_.write("\\U0057"_ets));

    expect_sequence(
        std::string("\xC4\x8E"),
        terminal_.write("\\U010E"_ets));

    expect_sequence(
        std::string("\xE1\x9A\xB8"),
        terminal_.write("\\U16B8"_ets));
}

TEST_F(a_terminal, writing_past_terminal_width_moves_cursor_to_next_line)
{
    terminal_.set_size({10, 10});
    terminal_.move_cursor({8, 8});
    terminal_.write("abcde");

    expect_sequence(
        std::string(""),
        terminal_.move_cursor({3, 9}));
}

TEST_F(a_terminal, writing_far_past_terminal_width_moves_multiple_lines)
{
    terminal_.set_size({10, 10});
    terminal_.move_cursor({8, 8});
    terminal_.write("abcdefghijklmno");

    expect_sequence(
        std::string(""),
        terminal_.move_cursor({3, 10}));
}

TEST_F(a_terminal, writing_past_last_line_scrolls_last_line)
{
    terminal_.set_size({10, 10});
    terminal_.move_cursor({8, 10});
    terminal_.write("abcdefghijklmno");

    expect_sequence(
        std::string(""),
        terminal_.move_cursor({3, 10}));
}

TEST_F(a_terminal, can_write_single_element)
{
    terminalpp::element  elem('X');
    elem.attribute_.foreground_colour_ =
        terminalpp::ansi::graphics::colour::red;

    expect_sequence(
        std::string("\x1B[31mX"),
        terminal_.write(elem));
}

TEST_F(a_terminal, writing_single_element_moves_cursor)
{
    terminal_.set_size({5, 5});
    terminal_.move_cursor({0, 0});
    terminal_.write('x');

    expect_sequence(
        std::string(""),
        terminal_.move_cursor({1, 0}));
}

TEST_F(a_terminal, writing_unicode_after_default_charset_does_not_change_charset_first)
{
    expect_sequence(
        std::string(" \x1B%GW"),
        terminal_.write(" \\U0057"_ets));
}

TEST_F(a_terminal, writing_unicode_after_sco_charset_reverts_charset_first)
{
    expect_sequence(
        std::string("\x1B(U\xCD\x1B(B\x1B%GW"),
        terminal_.write("\\cU\\C205\\U0057"_ets));
}

TEST(terminal_string_test, behaviour_unicode_in_all_charsets_writing_unicode_after_sco_does_not_change_charset_first)
{
    terminalpp::behaviour behaviour;
    behaviour.unicode_in_all_charsets = true;
    terminalpp::terminal terminal{behaviour};

    expect_sequence(
        std::string("\x1B[0m\x1B(U\xCD\x1B%GW"),
        terminal.write("\\cU\\C205\\U0057"_ets));

}

TEST_F(a_terminal, changing_character_set_after_unicode_first_selects_default_charset)
{
    expect_sequence(
        std::string("\x1B%GW\x1B%@\x1B(A\x9C"),
        terminal_.write("\\U0057\\cA\\C156"_ets));
}
