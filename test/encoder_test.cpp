#include "terminalpp/encoder.hpp"
#include "io/string.hpp"
#include <gtest/gtest.h>

void expect_encoding(
    terminalpp::string const &expected_result,
    std::string const &coded_value)
{
    terminalpp::string result = terminalpp::encode(coded_value);

    if (result != expected_result)
    {
        std::cerr << "\nResult mismatch: \n"
                     "  expected: " << expected_result << "\n"
                     "  actual:   " << result << std::endl;
    }

    ASSERT_EQ(expected_result, result);
}

TEST(string_encoder_test, empty_string_encodes_to_empty_string)
{
    expect_encoding({}, "");
}

TEST(string_encoder_test, escaped_slash_encodes_to_single_slash)
{
    expect_encoding(
        {
            {'\\'}
        },
        "\\\\");
}

TEST(string_encoder_test, escaped_character_code_encodes_to_character)
{
    expect_encoding(
        {
            {'a'}
        },
        "\\C097");
}

TEST(string_encoder_test, charset_code_encodes_charset)
{
    expect_encoding(
        {
            { terminalpp::glyph('a', terminalpp::ansi::charset::dec) },
            { terminalpp::glyph('b', terminalpp::ansi::charset::dec) },
            { terminalpp::glyph('c', terminalpp::ansi::charset::dec) }
        },
        "\\c0abc");
}

TEST(string_encoder_test, extended_charset_code_encodes_charset)
{
    expect_encoding(
        {
            { terminalpp::glyph('a', terminalpp::ansi::charset::portuguese) }
        },
        "\\c%6a");
}

TEST(string_encoder_test, bold_intensity_code_encodes_bold_intensity)
{
    terminalpp::attribute bold_attribute;
    bold_attribute.intensity_ = terminalpp::ansi::graphics::intensity::bold;

    expect_encoding(
        {
            { 'a', bold_attribute },
            { 'b', bold_attribute },
            { 'c', bold_attribute }
        },
        "\\i>abc");
}

TEST(string_encoder_test, faint_intensity_code_encodes_faint_intensity)
{
    terminalpp::attribute faint_attribute;
    faint_attribute.intensity_ = terminalpp::ansi::graphics::intensity::faint;

    expect_encoding(
        {
            { 'a', faint_attribute },
            { 'b', faint_attribute },
            { 'c', faint_attribute },
        },
        "\\i<abc");
}

TEST(string_encoder_test, normal_intensity_code_encodes_normal_intensity)
{
    expect_encoding(
        {
            { 'a' }, { 'b' }, { 'c' },
        },
        "\\i=abc");
}

TEST(string_encoder_test, default_code_encodes_normal_intensity)
{
    expect_encoding(
        {
            { 'a' }, { 'b' }, { 'c' },
        },
        "\\ixabc");
}

TEST(string_encoder_test, default_and_normal_revert_bold_and_faint)
{
    terminalpp::attribute bold_attribute;
    bold_attribute.intensity_ = terminalpp::ansi::graphics::intensity::bold;

    terminalpp::attribute faint_attribute;
    faint_attribute.intensity_ = terminalpp::ansi::graphics::intensity::faint;

    expect_encoding(
        {
            { 'a', bold_attribute },
            { 'b', },
            { 'c', bold_attribute },
            { 'd', },
            { 'a', faint_attribute },
            { 'b', },
            { 'c', faint_attribute },
            { 'd', },
        },
        "\\i>a\\i=b\\i>c\\ixd"
        "\\i<a\\i=b\\i<c\\ixd");
}

TEST(string_encoder_test, positive_polarity_code_encodes_positive_polarity)
{
    expect_encoding(
        {
            { 'a' }, { 'b' }, { 'c' },
        },
        "\\p+abc");
}

TEST(string_encoder_test, negative_polarity_code_encodes_negative_polarity)
{
    terminalpp::attribute negative_polarity;
    negative_polarity.polarity_ = terminalpp::ansi::graphics::polarity::negative;

    expect_encoding(
        {
            { 'a', negative_polarity },
            { 'b', negative_polarity },
            { 'c', negative_polarity },
        },
        "\\p-abc");
}

TEST(string_encoder_test, positive_and_negative_polarity_revert_each_other)
{
    terminalpp::attribute negative_polarity;
    negative_polarity.polarity_ = terminalpp::ansi::graphics::polarity::negative;

    expect_encoding(
        {
            { 'a', },
            { 'b', negative_polarity },
            { 'c', },
        },
        "\\p+a\\p-b\\p+c");
}

TEST(string_encoder_test, positive_underlining_code_encodes_positive_underlining)
{
    terminalpp::attribute underlining;
    underlining.underlining_ = terminalpp::ansi::graphics::underlining::underlined;

    expect_encoding(
        {
            { 'a', underlining },
            { 'b', underlining },
            { 'c', underlining },
        },
        "\\u+abc");
}

TEST(string_encoder_test, negative_underlining_code_encodes_negative_underlining)
{
    expect_encoding(
        {
            { 'a' },
            { 'b' },
            { 'c' },
        },
        "\\u-abc");
}

TEST(string_encoder_test, positive_and_negative_underlining_revert_each_other)
{
    terminalpp::attribute underlined;
    underlined.underlining_ = terminalpp::ansi::graphics::underlining::underlined;

    expect_encoding(
        {
            { 'a', underlined },
            { 'b', },
            { 'c', underlined },
        },
        "\\u+a\\u-b\\u+c");
}

TEST(string_encoder_test, low_foreground_colour_code_encodes_colour)
{
    terminalpp::attribute low_foreground_colour_attribute;
    low_foreground_colour_attribute.foreground_colour_ =
        terminalpp::low_colour(terminalpp::ansi::graphics::colour::green);

    expect_encoding(
        {
            { 'a', low_foreground_colour_attribute },
            { 'b', low_foreground_colour_attribute },
            { 'c', low_foreground_colour_attribute },
        },
        "\\[2abc");
}

TEST(string_encoder_test, high_foreground_colour_code_encodes_colour)
{
    terminalpp::attribute high_foreground_colour_attribute;
    high_foreground_colour_attribute.foreground_colour_ =
        terminalpp::high_colour(5, 1, 2);

    expect_encoding(
        {
            { 'a', high_foreground_colour_attribute },
            { 'b', high_foreground_colour_attribute },
            { 'c', high_foreground_colour_attribute },
        },
        "\\<512abc");
}

TEST(string_encoder_test, greyscale_foreground_colour_code_encodes_colour)
{
    terminalpp::attribute greyscale_foreground_colour_attribute;
    greyscale_foreground_colour_attribute.foreground_colour_ =
        terminalpp::greyscale_colour(22);

    expect_encoding(
        {
            { 'a', greyscale_foreground_colour_attribute },
            { 'b', greyscale_foreground_colour_attribute },
            { 'c', greyscale_foreground_colour_attribute },
        },
        "\\{22abc");
}

TEST(string_encoder_test, low_background_colour_code_encodes_colour)
{
    terminalpp::attribute low_background_colour_attribute;
    low_background_colour_attribute.background_colour_ =
        terminalpp::low_colour(terminalpp::ansi::graphics::colour::green);

    expect_encoding(
        {
            { 'a', low_background_colour_attribute },
            { 'b', low_background_colour_attribute },
            { 'c', low_background_colour_attribute },
        },
        "\\]2abc");
}

TEST(string_encoder_test, high_background_colour_code_encodes_colour)
{
    terminalpp::attribute high_background_colour_attribute;
    high_background_colour_attribute.background_colour_ =
        terminalpp::high_colour(5, 1, 2);

    expect_encoding(
        {
            { 'a', high_background_colour_attribute },
            { 'b', high_background_colour_attribute },
            { 'c', high_background_colour_attribute },
        },
        "\\>512abc");
}

TEST(string_encoder_test, greyscale_background_colour_code_encodes_colour)
{
    terminalpp::attribute greyscale_background_colour_attribute;
    greyscale_background_colour_attribute.background_colour_ =
        terminalpp::greyscale_colour(22);

    expect_encoding(
        {
            { 'a', greyscale_background_colour_attribute },
            { 'b', greyscale_background_colour_attribute },
            { 'c', greyscale_background_colour_attribute },
        },
        "\\}22abc");
}

TEST(string_encoder_test, unicode_codes_encode_unicode_text)
{
    terminalpp::glyph glyph_0057("W");
    terminalpp::glyph glyph_010E("\xC4\x8E");
    terminalpp::glyph glyph_16B8("\xE1\x9A\xB8");

    expect_encoding(
        {
            { glyph_0057 }
        },
        "\\U0057");

    expect_encoding(
        {
            { glyph_010E }
        },
        "\\U010E");

    expect_encoding(
        {
            { glyph_16B8 }
        },
        "\\U16B8");
}

TEST(string_encoder_test, default_code_removes_all_attributes)
{
    expect_encoding(
        {{'a'}},
        "\\>201\\{22\\p-\\u+\\xa");
}

TEST(string_encoder_test, default_code_then_colour_code_encodes_colour)
{
    terminalpp::attribute high_background_colour_attribute;
    high_background_colour_attribute.background_colour_ =
        terminalpp::high_colour(5, 1, 2);

    // When testing this out RL, I discovered that 512 is a really,
    // really hideous pink.  I absolutely have to use it for something.
    expect_encoding(
        {
            { 'a', high_background_colour_attribute }
        },
        "\\x\\>512a");

}
