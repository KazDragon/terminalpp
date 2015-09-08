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
    CPPUNIT_TEST_SUITE_END();
    
private :
    void move_from_unknown_location_performs_full_move();
    void move_to_same_location_does_nothing();
    void move_to_origin_column_supports_cha_and_default_arg_sends_short_sequence();
    void move_to_origin_column_supports_cha_not_default_arg_sends_cha_sequence();
    void move_to_origin_column_no_cha_sends_cub();
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
