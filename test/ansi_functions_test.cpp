#include "terminalpp/ansi/functions.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

class ansi_functions_test_fixture : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(ansi_functions_test_fixture);
        CPPUNIT_TEST(set_7bit_controls_outputs_correct_sequence);
        CPPUNIT_TEST(set_8bit_controls_outputs_correct_sequence);
        CPPUNIT_TEST(full_reset_outputs_correct_sequence);

        CPPUNIT_TEST(double_height_line_top_half_outputs_correct_sequence);
        CPPUNIT_TEST(double_height_line_bottom_half_outputs_correct_sequence);
        CPPUNIT_TEST(single_width_line_outputs_correct_sequence);
        CPPUNIT_TEST(double_width_line_outputs_correct_sequence);
    CPPUNIT_TEST_SUITE_END();

private :
    void set_7bit_controls_outputs_correct_sequence();
    void set_8bit_controls_outputs_correct_sequence();
    void full_reset_outputs_correct_sequence();

    void double_height_line_top_half_outputs_correct_sequence();
    void double_height_line_bottom_half_outputs_correct_sequence();
    void single_width_line_outputs_correct_sequence();
    void double_width_line_outputs_correct_sequence();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ansi_functions_test_fixture);

void ansi_functions_test_fixture::set_7bit_controls_outputs_correct_sequence()
{
    std::string expected = "\x1B F";
    std::string result = terminalpp::ansi::set_7bit_controls();

    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::set_8bit_controls_outputs_correct_sequence()
{
    std::string expected = "\x1B G";
    std::string result = terminalpp::ansi::set_8bit_controls();

    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::full_reset_outputs_correct_sequence()
{
    std::string expected = "\x1B""c";
    std::string result = terminalpp::ansi::full_reset();

    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::double_height_line_top_half_outputs_correct_sequence()
{
    std::string expected = "\x1B#3";
    std::string result = terminalpp::ansi::double_height_line_top_half();

    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::double_height_line_bottom_half_outputs_correct_sequence()
{
    std::string expected = "\x1B#4";
    std::string result = terminalpp::ansi::double_height_line_bottom_half();

    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::single_width_line_outputs_correct_sequence()
{
    std::string expected = "\x1B#5";
    std::string result = terminalpp::ansi::single_width_line();

    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::double_width_line_outputs_correct_sequence()
{
    std::string expected = "\x1B#6";
    std::string result = terminalpp::ansi::double_width_line();

    CPPUNIT_ASSERT_EQUAL(expected, result);
}
