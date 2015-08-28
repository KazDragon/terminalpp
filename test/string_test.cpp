#include "terminalpp/string.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <sstream>

class string_test_fixture : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(string_test_fixture);
        CPPUNIT_TEST(string_literal_creates_string);

        CPPUNIT_TEST(empty_string_outputs_nothing);
        CPPUNIT_TEST(basic_string_outputs_basic_string);

        CPPUNIT_TEST(escaped_slash_outputs_single_slash);

        CPPUNIT_TEST(escaped_character_code_outputs_character);

        CPPUNIT_TEST(escaped_charset_code_changes_charset);
        CPPUNIT_TEST(default_charset_code_does_not_change_charset);

        CPPUNIT_TEST(bold_intensity_code_changes_intensity);
        CPPUNIT_TEST(faint_intensity_code_changes_intensity);
        CPPUNIT_TEST(normal_intensity_code_does_not_change_intensity);
        CPPUNIT_TEST(bold_then_normal_intensity_changes_intensity);

        CPPUNIT_TEST(positive_polarity_code_does_not_change_polarity);
        CPPUNIT_TEST(negative_polarity_code_changes_polarity);
        CPPUNIT_TEST(negative_then_positive_polarity_code_changes_polarities);

        CPPUNIT_TEST(positive_underlining_code_changes_underlining);
        CPPUNIT_TEST(negative_underlining_code_does_not_change_underlining);
        CPPUNIT_TEST(positive_then_negative_underlining_code_changes_underlinings);

        CPPUNIT_TEST(foreground_low_colour_code_changes_foreground_colour);
        CPPUNIT_TEST(foreground_high_colour_code_changes_foreground_colour);
        CPPUNIT_TEST(foreground_greyscale_colour_code_changes_foreground_colour);
        CPPUNIT_TEST(default_foreground_colour_code_does_not_change_foreground_colour);
        CPPUNIT_TEST(multiple_foreground_colour_codes_change_foreground_colours);

        CPPUNIT_TEST(background_low_colour_code_changes_background_colour);
        CPPUNIT_TEST(background_high_colour_code_changes_background_colour);
        CPPUNIT_TEST(background_greyscale_colour_code_changes_background_colour);
        CPPUNIT_TEST(default_background_colour_code_does_not_change_background_colour);
        CPPUNIT_TEST(multiple_background_colour_codes_change_background_colours);

        CPPUNIT_TEST(multiple_attributes_do_not_cause_default_change);

        CPPUNIT_TEST(raw_string_construction_outputs_raw_text);

        CPPUNIT_TEST(only_attributes_outputs_no_text);

    CPPUNIT_TEST_SUITE_END();

private :
    void string_literal_creates_string();

    void empty_string_outputs_nothing();
    void basic_string_outputs_basic_string();

    void escaped_slash_outputs_single_slash();

    void escaped_character_code_outputs_character();

    void escaped_charset_code_changes_charset();
    void default_charset_code_does_not_change_charset();

    void bold_intensity_code_changes_intensity();
    void faint_intensity_code_changes_intensity();
    void normal_intensity_code_does_not_change_intensity();
    void bold_then_normal_intensity_changes_intensity();

    void positive_polarity_code_does_not_change_polarity();
    void negative_polarity_code_changes_polarity();
    void negative_then_positive_polarity_code_changes_polarities();

    void positive_underlining_code_changes_underlining();
    void negative_underlining_code_does_not_change_underlining();
    void positive_then_negative_underlining_code_changes_underlinings();

    void foreground_low_colour_code_changes_foreground_colour();
    void foreground_high_colour_code_changes_foreground_colour();
    void foreground_greyscale_colour_code_changes_foreground_colour();
    void default_foreground_colour_code_does_not_change_foreground_colour();
    void multiple_foreground_colour_codes_change_foreground_colours();

    void background_low_colour_code_changes_background_colour();
    void background_high_colour_code_changes_background_colour();
    void background_greyscale_colour_code_changes_background_colour();
    void default_background_colour_code_does_not_change_background_colour();
    void multiple_background_colour_codes_change_background_colours();

    void multiple_attributes_do_not_cause_default_change();

    void raw_string_construction_outputs_raw_text();

    void only_attributes_outputs_no_text();
};

CPPUNIT_TEST_SUITE_REGISTRATION(string_test_fixture);

namespace {

void expect_conversion(
    std::string const &test_data,
    std::string const &expected_result)
{
    std::stringstream stream;
    std::string result;

    auto string = terminalpp::string(test_data);
    stream << string;
    result = stream.str();

    CPPUNIT_ASSERT_EQUAL(expected_result, result);
}

}

void string_test_fixture::string_literal_creates_string()
{
    using namespace terminalpp::literals;
    CPPUNIT_ASSERT_EQUAL(terminalpp::string("abcde"), "abcde"_ts);
}

void string_test_fixture::empty_string_outputs_nothing()
{
    // Test that an empty string outputs an empty string.
    expect_conversion("", "");
}

void string_test_fixture::basic_string_outputs_basic_string()
{
    // Test that a string with no attributes outputs a plain
    // string with no adornments.
    expect_conversion("basic string", "basic string");
}

void string_test_fixture::escaped_slash_outputs_single_slash()
{
    // Test that a string with an escaped slash ("\\") outputs a single slash.
    expect_conversion("\\\\", "\\");
}

void string_test_fixture::escaped_character_code_outputs_character()
{
    // Test that a string with an escaped character code (e.g. "\C097")
    // outputs the respective character (in this case, 'a').
    expect_conversion("\\C097", "a");
}

void string_test_fixture::escaped_charset_code_changes_charset()
{
    // Test that an escaped character set code, when followed by a character,
    // will change the character set for the characters following it.  A code
    // to revert the character set will appear after it.
    expect_conversion("\\cAabc", "\x1B(Aabc\x1B(B");
}

void string_test_fixture::default_charset_code_does_not_change_charset()
{
    // Test that changing from the default charset to the default charset does
    // not output any extra character codes.
    expect_conversion("\\cBabc", "abc");
}

void string_test_fixture::bold_intensity_code_changes_intensity()
{
    // Test that the code for bold intensity, when followed by characters,
    // will change the intensity for those characters.  Afterwards, a sequence
    // should be output to restore normal intensity.
    expect_conversion("\\i>abc", "\x1B[1mabc\x1B[0m");
}

void string_test_fixture::faint_intensity_code_changes_intensity()
{
    // Test that the code for faint intensity, when followed by characters,
    // will change the intensity for those characters.  Afterwards, a sequence
    // should be output to restore normal intensity.
    expect_conversion("\\i<abc", "\x1B[2mabc\x1B[0m");
}

void string_test_fixture::normal_intensity_code_does_not_change_intensity()
{
    // Test that the code for normal intensity, when followed by characters,
    // does not change the intensity.
    expect_conversion("\\i=abc", "abc");
}

void string_test_fixture::bold_then_normal_intensity_changes_intensity()
{
    // Test that the code for bold intensity, when followed by characters and
    // then the normal intensity, outputs the appropriate codes.  It should
    // not end in a sequence to restore normal intensity because that is
    // already done.
    expect_conversion("\\i>ab\\i=cd", "\x1B[1mab\x1B[0mcd");
}

void string_test_fixture::positive_polarity_code_does_not_change_polarity()
{
    // Test that the code for positive intensity, when followed by characters,
    // does not change the polarity (since the default polarity is positive).
    expect_conversion("\\p+abc", "abc");
}

void string_test_fixture::negative_polarity_code_changes_polarity()
{
    // Test that the code for negative polarity, when followed by characters,
    // outputs a sequence to change the polarity, and is reversed at the end
    // of the string.
    expect_conversion("\\p-abc", "\x1B[7mabc\x1B[0m");
}

void string_test_fixture::negative_then_positive_polarity_code_changes_polarities()
{
    // Test that the code for negative polarity, when followed by characters
    // and then positive polarity, outputs the appropriate sequence.
    expect_conversion("\\p-ab\\p+cd", "\x1B[7mab\x1B[0mcd");
}

void string_test_fixture::positive_underlining_code_changes_underlining()
{
    expect_conversion("\\u+abc", "\x1B[4mabc\x1B[0m");
}

void string_test_fixture::negative_underlining_code_does_not_change_underlining()
{
    expect_conversion("\\u-abc", "abc");
}

void string_test_fixture::positive_then_negative_underlining_code_changes_underlinings()
{
    expect_conversion("\\u+ab\\u-cd", "\x1B[4mab\x1B[0mcd");
}

void string_test_fixture::foreground_low_colour_code_changes_foreground_colour()
{
    expect_conversion("\\[2abc", "\x1B[32mabc\x1B[0m");
}

void string_test_fixture::foreground_high_colour_code_changes_foreground_colour()
{
    expect_conversion("\\<510abc", "\x1B[38;5;202mabc\x1B[0m");
}

void string_test_fixture::foreground_greyscale_colour_code_changes_foreground_colour()
{
    expect_conversion("\\{12abc", "\x1B[38;5;244mabc\x1B[0m");
}

void string_test_fixture::default_foreground_colour_code_does_not_change_foreground_colour()
{
    expect_conversion("\\[9abc", "abc");
}

void string_test_fixture::multiple_foreground_colour_codes_change_foreground_colours()
{
    expect_conversion(
        "\\[2ab" "\\<510cd" "\\{02ef" "\\[9gh",
        "\x1B[32mab" "\x1B[38;5;202mcd" "\x1B[38;5;234mef" "\x1B[0mgh");
}

void string_test_fixture::background_low_colour_code_changes_background_colour()
{
    expect_conversion("\\]2abc", "\x1B[42mabc\x1B[0m");
}

void string_test_fixture::background_high_colour_code_changes_background_colour()
{
    expect_conversion("\\>135abc", "\x1B[48;5;75mabc\x1B[0m");
}

void string_test_fixture::background_greyscale_colour_code_changes_background_colour()
{
    expect_conversion("\\}23abc", "\x1B[48;5;255mabc\x1B[0m");
}

void string_test_fixture::default_background_colour_code_does_not_change_background_colour()
{
    expect_conversion("\\]9abc", "abc");
}

void string_test_fixture::multiple_background_colour_codes_change_background_colours()
{
    expect_conversion(
        "\\]2ab" "\\>135cd" "\\}02ef" "\\]9gh",
        "\x1B[42mab" "\x1B[48;5;75mcd" "\x1B[48;5;234mef" "\x1B[0mgh");
}

void string_test_fixture::multiple_attributes_do_not_cause_default_change()
{
    // Test that, when switching off and on multiple attributes, they do not in
    // general go back to default.  Instead, they should toggle specific flags.
    // NOTE: At a later date, it may be implemented that the algorithm will
    // branch and look for strategies for producing the shortest sequence.
    // In that case, it may be that switching several attributes off is longer
    // than switching to default then re-enabling one attribute.  It also may
    // be determined by environment - different terminals behave differently.
    expect_conversion(
        "\\[2\\]1a\\p-b\\p+c",
        "\x1B[32;41ma" "\x1B[7mb" "\x1B[27mc" "\x1B[0m");
}

void string_test_fixture::raw_string_construction_outputs_raw_text()
{
    // When a string is created raw, then it does not parse the text for
    // attribute codes.  Instead, it creates a string as if everything were
    // escaped.
    std::string const test_data = "\\p-!";
    std::string const expected_result = "\\p-!";

    std::stringstream stream;
    std::string result;

    auto string = terminalpp::string(test_data, true);
    stream << string;
    result = stream.str();

    CPPUNIT_ASSERT_EQUAL(expected_result, result);
}

void string_test_fixture::only_attributes_outputs_no_text()
{
    // If a string comprises only attributes, then no text should be output.
    expect_conversion("\\[2\\]1\\p-\\i>", "");
}
