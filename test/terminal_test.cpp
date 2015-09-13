#include "terminalpp/terminal.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <iostream>

class terminal_test_fixture : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(terminal_test_fixture);
        CPPUNIT_TEST(move_from_unknown_location_performs_full_move);
        
        CPPUNIT_TEST(move_to_same_location_does_nothing);
        
        CPPUNIT_TEST(move_to_origin_column_supports_cha_and_default_arg_sends_short_sequence);
        CPPUNIT_TEST(move_to_origin_column_supports_cha_not_default_arg_sends_cha_sequence);
        CPPUNIT_TEST(move_to_origin_column_no_cha_sends_cub);
        
        CPPUNIT_TEST(move_to_column_to_the_left_uses_cub);
        CPPUNIT_TEST(move_to_column_to_the_right_uses_cuf);
        CPPUNIT_TEST(move_to_column_under_10_supports_cha_uses_cha);
        CPPUNIT_TEST(move_to_column_under_10_no_cha_uses_cub_or_cuf);
        
        CPPUNIT_TEST(move_to_origin_row_uses_cuu);
        CPPUNIT_TEST(move_to_row_above_uses_cuu);
        CPPUNIT_TEST(move_to_row_below_uses_cud);
        
        CPPUNIT_TEST(move_to_different_column_and_row_uses_cup);
    CPPUNIT_TEST_SUITE_END();
    
private :
    void move_from_unknown_location_performs_full_move();
    
    void move_to_same_location_does_nothing();
    
    void move_to_origin_column_supports_cha_and_default_arg_sends_short_sequence();
    void move_to_origin_column_supports_cha_not_default_arg_sends_cha_sequence();
    void move_to_origin_column_no_cha_sends_cub();
    
    void move_to_column_to_the_left_uses_cub();
    void move_to_column_to_the_right_uses_cuf();
    void move_to_column_under_10_supports_cha_uses_cha();
    void move_to_column_under_10_no_cha_uses_cub_or_cuf();
    
    void move_to_origin_row_uses_cuu();
    void move_to_row_above_uses_cuu();
    void move_to_row_below_uses_cud();
    
    void move_to_different_column_and_row_uses_cup();
};

CPPUNIT_TEST_SUITE_REGISTRATION(terminal_test_fixture);

void expect_sequence(std::string const &expected, std::string const &result)
{
    if (expected != result)
    {
        std::cout << "\n"
                  << "Expected: \"" << expected << "\"\n"
                  << "Result:   \"" << result << "\"\n";
    }
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void terminal_test_fixture::move_from_unknown_location_performs_full_move()
{
    // When moving to a location from an unknown position (such as it is by
    // default), then the full cursor position sequence is returned.
    terminalpp::terminal terminal(terminalpp::terminal::behaviour{});
    
    expect_sequence(
        std::string("\x1B[2;2H"),
        terminal.move_cursor({2, 2}));
}

void terminal_test_fixture::move_to_same_location_does_nothing()
{
    // When moving from one location to the same location, the result should
    // be an empty string.
    terminalpp::terminal terminal;
    terminal.move_cursor({10, 10});
    
    expect_sequence(std::string{}, terminal.move_cursor({10, 10}));
}

void terminal_test_fixture::move_to_origin_column_supports_cha_and_default_arg_sends_short_sequence()
{
    // When moving to the origin column from a known position, and the 
    // terminal supports Cursor Horizontal Absolute, and supports
    // use of the default argument to CHA, then a short code is output.
    terminalpp::terminal::behaviour behaviour;
    behaviour.supports_cha         = true;
    behaviour.supports_cha_default = true;
    
    terminalpp::terminal terminal(behaviour);
    terminal.move_cursor({10, 10});
    
    expect_sequence(
        std::string("\x1B[G"),
        terminal.move_cursor({1, 10}));
}

void terminal_test_fixture::move_to_origin_column_supports_cha_not_default_arg_sends_cha_sequence()
{
    // When moving to the origin column, where CHA is supported but not its
    // default argument, then the 1 is sent.  This is still the shortest
    // sequence, either matching CUB or shorter if it has to move at least
    // 10 columns.
    terminalpp::terminal::behaviour behaviour;
    behaviour.supports_cha         = true;
    behaviour.supports_cha_default = false;
    
    terminalpp::terminal terminal(behaviour);
    terminal.move_cursor({10, 10});
    
    expect_sequence(
        std::string("\x1B[1G"),
        terminal.move_cursor({1, 10}));
}

void terminal_test_fixture::move_to_origin_column_no_cha_sends_cub()
{
    // When moving to the origin column, but CHA is not supported, then
    // the terminal will send Cursor Backward (CUB) instead.
    terminalpp::terminal::behaviour behaviour;
    behaviour.supports_cha         = false;
    behaviour.supports_cha_default = false;
    
    terminalpp::terminal terminal(behaviour);
    terminal.move_cursor({10, 10});
    
    expect_sequence(
        std::string("\x1B[9D"),
        terminal.move_cursor({1, 10}));
}

void terminal_test_fixture::move_to_column_to_the_left_uses_cub()
{
    // When moving to a column to the left (that is not < 10, since that
    // is CHA's domain), the terminal will send Cursor Backward (CUB).
    terminalpp::terminal terminal;
    terminal.move_cursor({20, 10});
    
    expect_sequence(
        std::string("\x1B[5D"),
        terminal.move_cursor({15, 10}));
}

void terminal_test_fixture::move_to_column_to_the_right_uses_cuf()
{
    // When moving to a column to the right (that is not < 10, since that
    // is CHA's domain), the terminal will send Cursor Forward (CUF).
    terminalpp::terminal terminal;
    terminal.move_cursor({20, 10});
    
    expect_sequence(
        std::string("\x1B[5C"),
        terminal.move_cursor({25, 10}));
}

void terminal_test_fixture::move_to_column_under_10_supports_cha_uses_cha()
{
    // When moving to a column < 10, the shortest sequence is to use
    // CHA, since it only requires one extra digit in all cases.
    terminalpp::terminal::behaviour behaviour;
    behaviour.supports_cha = true;
    
    terminalpp::terminal terminal(behaviour);
    terminal.move_cursor({20, 10});
    
    expect_sequence(
        std::string("\x1B[9G"),
        terminal.move_cursor({9, 10}));
}

void terminal_test_fixture::move_to_column_under_10_no_cha_uses_cub_or_cuf()
{
    // When moving to column < 10, but CHA is not supported, then we must
    // use either CUB or CUF instead.
    terminalpp::terminal::behaviour behaviour;
    behaviour.supports_cha = false;
    
    terminalpp::terminal terminal(behaviour);
    terminal.move_cursor({20, 10});
    
    expect_sequence(
        std::string("\x1B[15D"),
        terminal.move_cursor({5, 10}));
    
    expect_sequence(
        std::string("\x1B[4C"),
        terminal.move_cursor({9, 10}));
}

void terminal_test_fixture::move_to_origin_row_uses_cuu()
{
    // When moving to the origin column, we should use CUU in all 
    // circumstances
    //  Note: it is possible that CUP is shorter if:
    //    o the terminal supports sending CUP with a default column argument
    //    o the step from cursor to origin is > 100.
    //    o the current row is < 10.
    //  E.g. ^[;9H is shorter than
    //       ^[100A
    //  However, with most terminals being 24<=>80 rows, this is highly 
    //  unlikely, and not worth checking.
    terminalpp::terminal terminal;
    terminal.move_cursor({9, 9});
    
    expect_sequence(
        std::string("\x1B[8A"),
        terminal.move_cursor({9, 1}));
}

void terminal_test_fixture::move_to_row_above_uses_cuu()
{
    // When moving to a row above, we should use CUU in all circumstances.
    terminalpp::terminal terminal;
    terminal.move_cursor({9, 9});
    
    expect_sequence(
        std::string("\x1B[2A"),
        terminal.move_cursor({9, 7}));
    
    // Check that we also use the default argument if moving only one space.
    expect_sequence(
        std::string("\x1B[A"),
        terminal.move_cursor({9, 6}));
}

void terminal_test_fixture::move_to_row_below_uses_cud()
{
    // When moving to a row below, we should use CUD in all circumstances.
    terminalpp::terminal terminal;
    terminal.move_cursor({9, 9});
    
    expect_sequence(
        std::string("\x1B[2B"),
        terminal.move_cursor({9, 11}));
    
    // Check that we also use the default argument if moving only one space.
    expect_sequence(
        std::string("\x1B[B"),
        terminal.move_cursor({9, 12}));
}

void terminal_test_fixture::move_to_different_column_and_row_uses_cup()
{
    // When moving to a different column and row, CUP is used.
    terminalpp::terminal terminal;
    terminal.move_cursor({5, 5});
    
    expect_sequence(
        std::string("\x1B[3;10H"),
        terminal.move_cursor({10, 3}));
}
