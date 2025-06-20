#include "terminalpp/colour.hpp"
#include "terminalpp/graphics.hpp"
#include "terminalpp/string.hpp"

#include <gtest/gtest.h>

namespace {

void expect_encoding(
    terminalpp::string const &expected_result, std::string const &coded_value)
{
    terminalpp::string result = terminalpp::encode(coded_value);

    if (result != expected_result)
    {
        std::cerr << "\nResult mismatch: \n"
                     "  expected: "
                  << expected_result
                  << "\n"
                     "  actual:   "
                  << result << '\n';
    }

    ASSERT_EQ(expected_result, result);
}

TEST(string_encoder_test, empty_string_encodes_to_empty_string)
{
    expect_encoding({}, "");
}

TEST(string_encoder_test, escaped_slash_encodes_to_single_slash)
{
    expect_encoding({{'\\'}}, "\\\\");
}

TEST(string_encoder_test, escaped_character_code_encodes_to_character)
{
    expect_encoding({{'a'}}, "\\C097");
}

TEST(string_encoder_test, charset_code_encodes_charset)
{
    expect_encoding(
        {{terminalpp::glyph('a', terminalpp::charset::dec)},
         {terminalpp::glyph('b', terminalpp::charset::dec)},
         {terminalpp::glyph('c', terminalpp::charset::dec)}},
        "\\c0abc");
}

TEST(string_encoder_test, extended_charset_code_encodes_charset)
{
    expect_encoding(
        {{terminalpp::glyph('a', terminalpp::charset::portuguese)}}, "\\c%6a");
}

TEST(string_encoder_test, bold_intensity_code_encodes_bold_intensity)
{
    terminalpp::attribute bold_attribute;
    bold_attribute.intensity_ = terminalpp::graphics::intensity::bold;

    expect_encoding(
        {
            {'a', bold_attribute},
            {'b', bold_attribute},
            {'c', bold_attribute}
    },
        "\\i>abc");
}

TEST(string_encoder_test, faint_intensity_code_encodes_faint_intensity)
{
    terminalpp::attribute faint_attribute;
    faint_attribute.intensity_ = terminalpp::graphics::intensity::faint;

    expect_encoding(
        {
            {'a', faint_attribute},
            {'b', faint_attribute},
            {'c', faint_attribute},
    },
        "\\i<abc");
}

TEST(string_encoder_test, normal_intensity_code_encodes_normal_intensity)
{
    expect_encoding(
        {
            {'a'},
            {'b'},
            {'c'},
        },
        "\\i=abc");
}

TEST(string_encoder_test, default_code_encodes_normal_intensity)
{
    expect_encoding(
        {
            {'a'},
            {'b'},
            {'c'},
        },
        "\\ixabc");
}

TEST(string_encoder_test, default_and_normal_revert_bold_and_faint)
{
    expect_encoding(
        {
            {'a', {.intensity_ = terminalpp::graphics::intensity::bold} },
            {'b', {}                                                    },
            {'c', {.intensity_ = terminalpp::graphics::intensity::bold} },
            {'d', {}                                                    },
            {'a', {.intensity_ = terminalpp::graphics::intensity::faint}},
            {'b', {}                                                    },
            {'c', {.intensity_ = terminalpp::graphics::intensity::faint}},
            {'d', {}                                                    },
    },
        "\\i>a\\i=b\\i>c\\ixd"
        "\\i<a\\i=b\\i<c\\ixd");
}

TEST(string_encoder_test, positive_polarity_code_encodes_positive_polarity)
{
    expect_encoding(
        {
            {'a'},
            {'b'},
            {'c'},
        },
        "\\p+abc");
}

TEST(string_encoder_test, negative_polarity_code_encodes_negative_polarity)
{
    expect_encoding(
        {
            {'a', {.polarity_ = terminalpp::graphics::polarity::negative}},
            {'b', {.polarity_ = terminalpp::graphics::polarity::negative}},
            {'c', {.polarity_ = terminalpp::graphics::polarity::negative}},
    },
        "\\p-abc");
}

TEST(string_encoder_test, positive_and_negative_polarity_revert_each_other)
{
    terminalpp::attribute negative_polarity;
    negative_polarity.polarity_ = terminalpp::graphics::polarity::negative;

    expect_encoding(
        {
            {'a', {}                                                     },
            {'b', {.polarity_ = terminalpp::graphics::polarity::negative}},
            {'c', {}                                                     },
    },
        R"(\p+a\p-b\p+c)");
}

TEST(
    string_encoder_test, positive_underlining_code_encodes_positive_underlining)
{
    expect_encoding(
        {
            {'a',
             {.underlining_ = terminalpp::graphics::underlining::underlined}},
            {'b',
             {.underlining_ = terminalpp::graphics::underlining::underlined}},
            {'c',
             {.underlining_ = terminalpp::graphics::underlining::underlined}},
    },
        "\\u+abc");
}

TEST(
    string_encoder_test, negative_underlining_code_encodes_negative_underlining)
{
    expect_encoding(
        {
            {'a'},
            {'b'},
            {'c'},
        },
        "\\u-abc");
}

TEST(string_encoder_test, positive_and_negative_underlining_revert_each_other)
{
    expect_encoding(
        {
            {'a',
             {.underlining_ = terminalpp::graphics::underlining::underlined}},
            {'b', {}                                                        },
            {'c',
             {.underlining_ = terminalpp::graphics::underlining::underlined}},
    },
        R"(\u+a\u-b\u+c)");
}

TEST(string_encoder_test, low_foreground_colour_code_encodes_colour)
{
    expect_encoding(
        {
            {'a', {.foreground_colour_ = terminalpp::graphics::colour::green}},
            {'b', {.foreground_colour_ = terminalpp::graphics::colour::green}},
            {'c', {.foreground_colour_ = terminalpp::graphics::colour::green}},
    },
        "\\[2abc");
}

TEST(string_encoder_test, high_foreground_colour_code_encodes_colour)
{
    expect_encoding(
        {
            {'a', {.foreground_colour_ = terminalpp::high_colour{5, 1, 2}}},
            {'b', {.foreground_colour_ = terminalpp::high_colour{5, 1, 2}}},
            {'c', {.foreground_colour_ = terminalpp::high_colour{5, 1, 2}}},
    },
        "\\<512abc");
}

TEST(string_encoder_test, greyscale_foreground_colour_code_encodes_colour)
{
    expect_encoding(
        {
            {'a', {.foreground_colour_ = terminalpp::greyscale_colour{22}}},
            {'b', {.foreground_colour_ = terminalpp::greyscale_colour{22}}},
            {'c', {.foreground_colour_ = terminalpp::greyscale_colour{22}}},
    },
        "\\{22abc");
}

TEST(string_encoder_test, true_foreground_colour_code_encodes_colour)
{
    expect_encoding(
        {
            {'a',
             {.foreground_colour_ = terminalpp::true_colour{0xA7, 0xE9, 0x1C}}},
            {'b',
             {.foreground_colour_ = terminalpp::true_colour{0xA7, 0xE9, 0x1C}}},
            {'c',
             {.foreground_colour_ = terminalpp::true_colour{0xA7, 0xE9, 0x1C}}},
    },
        "\\(A7E91Cabc");
}

TEST(string_encoder_test, low_background_colour_code_encodes_colour)
{
    expect_encoding(
        {
            {'a', {.background_colour_ = terminalpp::graphics::colour::green}},
            {'b', {.background_colour_ = terminalpp::graphics::colour::green}},
            {'c', {.background_colour_ = terminalpp::graphics::colour::green}},
    },
        "\\]2abc");
}

TEST(string_encoder_test, high_background_colour_code_encodes_colour)
{
    expect_encoding(
        {
            {'a', {.background_colour_ = terminalpp::high_colour{5, 1, 2}}},
            {'b', {.background_colour_ = terminalpp::high_colour{5, 1, 2}}},
            {'c', {.background_colour_ = terminalpp::high_colour{5, 1, 2}}},
    },
        "\\>512abc");
}

TEST(string_encoder_test, greyscale_background_colour_code_encodes_colour)
{
    expect_encoding(
        {
            {'a', {.background_colour_ = terminalpp::greyscale_colour{22}}},
            {'b', {.background_colour_ = terminalpp::greyscale_colour{22}}},
            {'c', {.background_colour_ = terminalpp::greyscale_colour{22}}},
    },
        "\\}22abc");
}

TEST(string_encoder_test, true_background_colour_code_encodes_colour)
{
    terminalpp::attribute true_background_colour_attribute;
    true_background_colour_attribute.background_colour_ =
        terminalpp::true_colour(0xA7, 0xE9, 0x1C);

    expect_encoding(
        {
            {'a',
             {.background_colour_ = terminalpp::true_colour{0xA7, 0xE9, 0x1C}}},
            {'b',
             {.background_colour_ = terminalpp::true_colour{0xA7, 0xE9, 0x1C}}},
            {'c',
             {.background_colour_ = terminalpp::true_colour{0xA7, 0xE9, 0x1C}}},
    },
        "\\)A7E91Cabc");
}

TEST(string_encoder_test, unicode_codes_encode_unicode_text)
{
    static constexpr terminalpp::glyph glyph_0057("W");
    static constexpr terminalpp::glyph glyph_010E("\xC4\x8E");      // NOLINT
    static constexpr terminalpp::glyph glyph_16B8("\xE1\x9A\xB8");  // NOLINT

    expect_encoding({{glyph_0057}}, "\\U0057");

    expect_encoding({{glyph_010E}}, "\\U010E");

    expect_encoding({{glyph_16B8}}, "\\U16B8");
}

TEST(string_encoder_test, default_code_removes_all_attributes)
{
    expect_encoding({{'a'}}, R"(\>201\{22\p-\u+\xa)");
}

TEST(string_encoder_test, default_code_then_colour_code_encodes_colour)
{
    // When testing this out RL, I discovered that 512 is a really,
    // really hideous pink.  I absolutely have to use it for something.
    expect_encoding(
        {
            {'a', {.background_colour_ = terminalpp::high_colour{5, 1, 2}}}
    },
        "\\x\\>512a");
}

}  // namespace
