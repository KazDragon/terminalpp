#include "terminalpp/string.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <sstream>

class string_test_fixture : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(string_test_fixture);
        CPPUNIT_TEST(empty_string_outputs_nothing);
        CPPUNIT_TEST(basic_string_outputs_basic_string);
        CPPUNIT_TEST(escaped_slash_outputs_single_slash);
        CPPUNIT_TEST(escaped_character_code_outputs_character);
    CPPUNIT_TEST_SUITE_END();

private :
    void empty_string_outputs_nothing();
    void basic_string_outputs_basic_string();
    void escaped_slash_outputs_single_slash();
    void escaped_character_code_outputs_character();
};

CPPUNIT_TEST_SUITE_REGISTRATION(string_test_fixture);

namespace {

void expect_conversion(
    std::string const &test_data,
    std::string const &expected_result)
{
    // Test that an empty string outputs an empty string.
    std::stringstream stream;
    std::string result;

    auto string = terminalpp::string(test_data);
    stream << string;
    result = stream.str();

    CPPUNIT_ASSERT_EQUAL(expected_result, result);
}

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

