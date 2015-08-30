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
        
        CPPUNIT_TEST(select_default_charset_outputs_correct_sequence);
        CPPUNIT_TEST(select_utf8_charset_outputs_correct_sequence);
        CPPUNIT_TEST(designate_g0_charset_outputs_correct_sequences);
        CPPUNIT_TEST(designate_g1_charset_outputs_correct_sequences);
        CPPUNIT_TEST(designate_g2_charset_outputs_correct_sequences);
        CPPUNIT_TEST(designate_g3_charset_outputs_correct_sequences);
        
        CPPUNIT_TEST(move_cursor_up_1_skips_amount);
        CPPUNIT_TEST(move_cursor_up_2_outputs_correct_sequence);
        CPPUNIT_TEST(move_cursor_down_1_skips_amount);
        CPPUNIT_TEST(move_cursor_down_2_outputs_correct_sequence);
        CPPUNIT_TEST(move_cursor_forward_1_skips_amount);
        CPPUNIT_TEST(move_cursor_forward_2_outputs_correct_sequence);
        CPPUNIT_TEST(move_cursor_backward_1_skips_amount);
        CPPUNIT_TEST(move_cursor_backward_2_outputs_correct_sequence);
        CPPUNIT_TEST(move_cursor_to_column_origin_skips_column);
        CPPUNIT_TEST(move_cursor_to_column_outputs_correct_sequence);
        CPPUNIT_TEST(move_cursor_position_to_origin_skips_column_and_row);
        CPPUNIT_TEST(move_cursor_position_to_origin_row_skips_row);
        CPPUNIT_TEST(move_cursor_position_to_origin_column_skips_column);
        CPPUNIT_TEST(move_cursor_position_outputs_correct_sequence);
    CPPUNIT_TEST_SUITE_END();
    
private :
    void set_7bit_controls_outputs_correct_sequence();
    void set_8bit_controls_outputs_correct_sequence();
    void full_reset_outputs_correct_sequence();
    
    void double_height_line_top_half_outputs_correct_sequence();
    void double_height_line_bottom_half_outputs_correct_sequence();
    void single_width_line_outputs_correct_sequence();
    void double_width_line_outputs_correct_sequence();
    
    void select_default_charset_outputs_correct_sequence();
    void select_utf8_charset_outputs_correct_sequence();
    void designate_g0_charset_outputs_correct_sequences();
    void designate_g1_charset_outputs_correct_sequences();
    void designate_g2_charset_outputs_correct_sequences();
    void designate_g3_charset_outputs_correct_sequences();
    
    void move_cursor_up_1_skips_amount();
    void move_cursor_up_2_outputs_correct_sequence();
    void move_cursor_down_1_skips_amount();
    void move_cursor_down_2_outputs_correct_sequence();
    void move_cursor_forward_1_skips_amount();
    void move_cursor_forward_2_outputs_correct_sequence();
    void move_cursor_backward_1_skips_amount();
    void move_cursor_backward_2_outputs_correct_sequence();
    void move_cursor_to_column_origin_skips_column();
    void move_cursor_to_column_outputs_correct_sequence();
    void move_cursor_position_to_origin_skips_column_and_row();
    void move_cursor_position_to_origin_row_skips_row();
    void move_cursor_position_to_origin_column_skips_column();
    void move_cursor_position_outputs_correct_sequence();
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

void ansi_functions_test_fixture::select_default_charset_outputs_correct_sequence()
{
    std::string expected = "\x1B%@";
    std::string result = terminalpp::ansi::select_default_charset();
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::select_utf8_charset_outputs_correct_sequence()
{
    std::string expected = "\x1B%G";
    std::string result = terminalpp::ansi::select_utf8_charset();
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::designate_g0_charset_outputs_correct_sequences()
{
    std::string expected_dec      = "\x1B(0";
    std::string expected_uk       = "\x1B(A";
    std::string expected_us_ascii = "\x1B(B";
    std::string expected_dec_sgr  = "\x1B(%5";
    
    CPPUNIT_ASSERT_EQUAL(
        expected_dec,
        terminalpp::ansi::designate_g0_charset(
            terminalpp::ansi::charset::dec));

    CPPUNIT_ASSERT_EQUAL(
        expected_uk,
        terminalpp::ansi::designate_g0_charset(
            terminalpp::ansi::charset::uk));

    CPPUNIT_ASSERT_EQUAL(
        expected_us_ascii,
        terminalpp::ansi::designate_g0_charset(
            terminalpp::ansi::charset::us_ascii));

    CPPUNIT_ASSERT_EQUAL(
        expected_dec_sgr,
        terminalpp::ansi::designate_g0_charset(
            terminalpp::ansi::charset::dec_supplementary_graphics));
}

void ansi_functions_test_fixture::designate_g1_charset_outputs_correct_sequences()
{
    std::string expected_dec      = "\x1B)0";
    std::string expected_uk       = "\x1B)A";
    std::string expected_us_ascii = "\x1B)B";
    std::string expected_dec_sgr  = "\x1B)%5";
    
    CPPUNIT_ASSERT_EQUAL(
        expected_dec,
        terminalpp::ansi::designate_g1_charset(
            terminalpp::ansi::charset::dec));

    CPPUNIT_ASSERT_EQUAL(
        expected_uk,
        terminalpp::ansi::designate_g1_charset(
            terminalpp::ansi::charset::uk));

    CPPUNIT_ASSERT_EQUAL(
        expected_us_ascii,
        terminalpp::ansi::designate_g1_charset(
            terminalpp::ansi::charset::us_ascii));

    CPPUNIT_ASSERT_EQUAL(
        expected_dec_sgr,
        terminalpp::ansi::designate_g1_charset(
            terminalpp::ansi::charset::dec_supplementary_graphics));
}

void ansi_functions_test_fixture::designate_g2_charset_outputs_correct_sequences()
{
    std::string expected_dec      = "\x1B*0";
    std::string expected_uk       = "\x1B*A";
    std::string expected_us_ascii = "\x1B*B";
    std::string expected_dec_sgr  = "\x1B*%5";
    
    CPPUNIT_ASSERT_EQUAL(
        expected_dec,
        terminalpp::ansi::designate_g2_charset(
            terminalpp::ansi::charset::dec));

    CPPUNIT_ASSERT_EQUAL(
        expected_uk,
        terminalpp::ansi::designate_g2_charset(
            terminalpp::ansi::charset::uk));

    CPPUNIT_ASSERT_EQUAL(
        expected_us_ascii,
        terminalpp::ansi::designate_g2_charset(
            terminalpp::ansi::charset::us_ascii));

    CPPUNIT_ASSERT_EQUAL(
        expected_dec_sgr,
        terminalpp::ansi::designate_g2_charset(
            terminalpp::ansi::charset::dec_supplementary_graphics));
}

void ansi_functions_test_fixture::designate_g3_charset_outputs_correct_sequences()
{
    std::string expected_dec      = "\x1B+0";
    std::string expected_uk       = "\x1B+A";
    std::string expected_us_ascii = "\x1B+B";
    std::string expected_dec_sgr  = "\x1B+%5";
    
    CPPUNIT_ASSERT_EQUAL(
        expected_dec,
        terminalpp::ansi::designate_g3_charset(
            terminalpp::ansi::charset::dec));

    CPPUNIT_ASSERT_EQUAL(
        expected_uk,
        terminalpp::ansi::designate_g3_charset(
            terminalpp::ansi::charset::uk));

    CPPUNIT_ASSERT_EQUAL(
        expected_us_ascii,
        terminalpp::ansi::designate_g3_charset(
            terminalpp::ansi::charset::us_ascii));

    CPPUNIT_ASSERT_EQUAL(
        expected_dec_sgr,
        terminalpp::ansi::designate_g3_charset(
            terminalpp::ansi::charset::dec_supplementary_graphics));
}

void ansi_functions_test_fixture::move_cursor_up_1_skips_amount()
{
    std::string expected = "\x1B[A";
    std::string result = terminalpp::ansi::move_cursor_up();
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::move_cursor_up_2_outputs_correct_sequence()
{
    std::string expected = "\x1B[2A";
    std::string result = terminalpp::ansi::move_cursor_up(2);
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::move_cursor_down_1_skips_amount()
{
    std::string expected = "\x1B[B";
    std::string result = terminalpp::ansi::move_cursor_down();
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::move_cursor_down_2_outputs_correct_sequence()
{
    std::string expected = "\x1B[2B";
    std::string result = terminalpp::ansi::move_cursor_down(2);
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::move_cursor_forward_1_skips_amount()
{
    std::string expected = "\x1B[C";
    std::string result = terminalpp::ansi::move_cursor_forward();
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::move_cursor_forward_2_outputs_correct_sequence()
{
    std::string expected = "\x1B[2C";
    std::string result = terminalpp::ansi::move_cursor_forward(2);
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::move_cursor_backward_1_skips_amount()
{
    std::string expected = "\x1B[D";
    std::string result = terminalpp::ansi::move_cursor_backward();
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::move_cursor_backward_2_outputs_correct_sequence()
{
    std::string expected = "\x1B[2D";
    std::string result = terminalpp::ansi::move_cursor_backward(2);
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::move_cursor_to_column_origin_skips_column()
{
    std::string expected = "\x1B[G";
    std::string result = terminalpp::ansi::move_cursor_to_column();
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::move_cursor_to_column_outputs_correct_sequence()
{
    std::string expected = "\x1B[2G";
    std::string result = terminalpp::ansi::move_cursor_to_column(2);
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::move_cursor_position_to_origin_skips_column_and_row()
{
    std::string expected = "\x1B[H";
    std::string result = terminalpp::ansi::move_cursor_to_position(1, 1);
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::move_cursor_position_to_origin_row_skips_row()
{
    std::string expected = "\x1B[7H";
    std::string result = terminalpp::ansi::move_cursor_to_position(7, 1);
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::move_cursor_position_to_origin_column_skips_column()
{
    std::string expected = "\x1B[;7H";
    std::string result = terminalpp::ansi::move_cursor_to_position(1, 7);
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void ansi_functions_test_fixture::move_cursor_position_outputs_correct_sequence()
{
    std::string expected = "\x1B[7;6H";
    std::string result = terminalpp::ansi::move_cursor_to_position(7, 6);
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}
