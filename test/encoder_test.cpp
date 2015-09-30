#include "terminalpp/encoder.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class string_encoder_test_fixture : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(string_encoder_test_fixture);
        CPPUNIT_TEST(empty_string_encodes_to_empty_string);
        
        CPPUNIT_TEST(escaped_slash_encodes_to_single_slash);
        CPPUNIT_TEST(escaped_character_code_encodes_to_character);
        
        CPPUNIT_TEST(charset_code_encodes_charset);
        
        CPPUNIT_TEST(bold_intensity_code_encodes_bold_intensity);
        CPPUNIT_TEST(faint_intensity_code_encodes_faint_intensity);
        CPPUNIT_TEST(normal_intensity_code_encodes_normal_intensity);
        CPPUNIT_TEST(default_code_encodes_normal_intensity);
        CPPUNIT_TEST(default_and_normal_revert_bold_and_faint);
        
        CPPUNIT_TEST(positive_polarity_code_encodes_positive_polarity);
        CPPUNIT_TEST(negative_polarity_code_encodes_negative_polarity);
        CPPUNIT_TEST(positive_and_negative_polarity_revert_each_other);
        
        CPPUNIT_TEST(positive_underlining_code_encodes_positive_underlining);
        CPPUNIT_TEST(negative_underlining_code_encodes_negative_underlining);
        CPPUNIT_TEST(positive_and_negative_underlining_revert_each_other);
        
        CPPUNIT_TEST(low_foreground_colour_code_encodes_colour);
        CPPUNIT_TEST(high_foreground_colour_code_encodes_colour);
        CPPUNIT_TEST(greyscale_foreground_colour_code_encodes_colour);

        CPPUNIT_TEST(low_background_colour_code_encodes_colour);
        CPPUNIT_TEST(high_background_colour_code_encodes_colour);
        CPPUNIT_TEST(greyscale_background_colour_code_encodes_colour);
        
        CPPUNIT_TEST(unicode_codes_encode_unicode_text);
        CPPUNIT_TEST(default_code_removes_all_attributes);
    CPPUNIT_TEST_SUITE_END();
private :
    void empty_string_encodes_to_empty_string();
    
    void escaped_slash_encodes_to_single_slash();
    void escaped_character_code_encodes_to_character();
    
    void charset_code_encodes_charset();
    
    void bold_intensity_code_encodes_bold_intensity();
    void faint_intensity_code_encodes_faint_intensity();
    void normal_intensity_code_encodes_normal_intensity();
    void default_code_encodes_normal_intensity();
    void default_and_normal_revert_bold_and_faint();
    
    void positive_polarity_code_encodes_positive_polarity();
    void negative_polarity_code_encodes_negative_polarity();
    void positive_and_negative_polarity_revert_each_other();
    
    void positive_underlining_code_encodes_positive_underlining();
    void negative_underlining_code_encodes_negative_underlining();
    void positive_and_negative_underlining_revert_each_other();
    
    void low_foreground_colour_code_encodes_colour();
    void high_foreground_colour_code_encodes_colour();
    void greyscale_foreground_colour_code_encodes_colour();
    
    void low_background_colour_code_encodes_colour();
    void high_background_colour_code_encodes_colour();
    void greyscale_background_colour_code_encodes_colour();
    
    void unicode_codes_encode_unicode_text();
    
    void default_code_removes_all_attributes();
};

CPPUNIT_TEST_SUITE_REGISTRATION(string_encoder_test_fixture);

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
    
    CPPUNIT_ASSERT_EQUAL(expected_result, result);
}

void string_encoder_test_fixture::empty_string_encodes_to_empty_string()
{
    expect_encoding({}, "");
}

void string_encoder_test_fixture::escaped_slash_encodes_to_single_slash()
{
    expect_encoding(
        {
            {'\\'}
        },
        "\\\\");
}

void string_encoder_test_fixture::escaped_character_code_encodes_to_character()
{
    expect_encoding(
        {
            {'a'}
        },
        "\\C097");
}

void string_encoder_test_fixture::charset_code_encodes_charset()
{
    expect_encoding(
        {
            { terminalpp::glyph('a', terminalpp::ansi::charset::dec) },
            { terminalpp::glyph('b', terminalpp::ansi::charset::dec) },
            { terminalpp::glyph('c', terminalpp::ansi::charset::dec) }
        },
        "\\c0abc");
}

void string_encoder_test_fixture::bold_intensity_code_encodes_bold_intensity()
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

void string_encoder_test_fixture::faint_intensity_code_encodes_faint_intensity()
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

void string_encoder_test_fixture::normal_intensity_code_encodes_normal_intensity()
{
    expect_encoding(
        {
            { 'a' }, { 'b' }, { 'c' },
        },
        "\\i=abc");
}

void string_encoder_test_fixture::default_code_encodes_normal_intensity()
{
    expect_encoding(
        {
            { 'a' }, { 'b' }, { 'c' },
        },
        "\\ixabc");
}

void string_encoder_test_fixture::default_and_normal_revert_bold_and_faint()
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

void string_encoder_test_fixture::positive_polarity_code_encodes_positive_polarity()
{
    expect_encoding(
        {
            { 'a' }, { 'b' }, { 'c' },
        },
        "\\p+abc");
}

void string_encoder_test_fixture::negative_polarity_code_encodes_negative_polarity()
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

void string_encoder_test_fixture::positive_and_negative_polarity_revert_each_other()
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

void string_encoder_test_fixture::positive_underlining_code_encodes_positive_underlining()
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

void string_encoder_test_fixture::negative_underlining_code_encodes_negative_underlining()
{
    expect_encoding(
        {
            { 'a' }, 
            { 'b' }, 
            { 'c' },
        },
        "\\u-abc");
}

void string_encoder_test_fixture::positive_and_negative_underlining_revert_each_other()
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

void string_encoder_test_fixture::low_foreground_colour_code_encodes_colour()
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

void string_encoder_test_fixture::high_foreground_colour_code_encodes_colour()
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

void string_encoder_test_fixture::greyscale_foreground_colour_code_encodes_colour()
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

void string_encoder_test_fixture::low_background_colour_code_encodes_colour()
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

void string_encoder_test_fixture::high_background_colour_code_encodes_colour()
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

void string_encoder_test_fixture::greyscale_background_colour_code_encodes_colour()
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

void string_encoder_test_fixture::unicode_codes_encode_unicode_text()
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

void string_encoder_test_fixture::default_code_removes_all_attributes()
{
    expect_encoding(
        {{'a'}},
        "\\>201\\{22\\p-\\u+\\xa");
}
