#include "terminalpp/terminal.hpp"
#include "expect_sequence.hpp"
#include <gtest/gtest.h>
#include <string>
#include <iostream>

TEST(terminal_cursor_test, move_from_unknown_location_performs_full_move)
{
    // When moving to a location from an unknown position (such as it is by
    // default), then the full cursor position sequence is returned.
    terminalpp::terminal terminal(terminalpp::terminal::behaviour{});
    
    expect_sequence(
        std::string("\x1B[3;3H"),
        terminal.move_cursor({2, 2}));
}

TEST(terminal_cursor_test, move_to_same_location_does_nothing)
{
    // When moving from one location to the same location, the result should
    // be an empty string.
    terminalpp::terminal terminal;
    terminal.move_cursor({10, 10});
    
    expect_sequence(std::string{}, terminal.move_cursor({10, 10}));
}

TEST(terminal_cursor_test, move_to_origin_column_supports_cha_and_default_arg_sends_short_sequence)
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
        terminal.move_cursor({0, 10}));
}

TEST(terminal_cursor_test, move_to_origin_column_supports_cha_not_default_arg_sends_cha_sequence)
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
        terminal.move_cursor({0, 10}));
}

TEST(terminal_cursor_test, move_to_origin_column_no_cha_sends_cub)
{
    // When moving to the origin column, but CHA is not supported, then
    // the terminal will send Cursor Backward (CUB) instead.
    terminalpp::terminal::behaviour behaviour;
    behaviour.supports_cha         = false;
    behaviour.supports_cha_default = false;
    
    terminalpp::terminal terminal(behaviour);
    terminal.move_cursor({10, 10});
    
    expect_sequence(
        std::string("\x1B[10D"),
        terminal.move_cursor({0, 10}));
}

TEST(terminal_cursor_test, move_to_column_to_the_left_uses_cub)
{
    // When moving to a column to the left (that is not < 10, since that
    // is CHA's domain), the terminal will send Cursor Backward (CUB).
    terminalpp::terminal terminal;
    terminal.move_cursor({20, 10});
    
    expect_sequence(
        std::string("\x1B[5D"),
        terminal.move_cursor({15, 10}));
}

TEST(terminal_cursor_test, move_to_column_to_the_right_uses_cuf)
{
    // When moving to a column to the right (that is not < 10, since that
    // is CHA's domain), the terminal will send Cursor Forward (CUF).
    terminalpp::terminal terminal;
    terminal.move_cursor({20, 10});
    
    expect_sequence(
        std::string("\x1B[5C"),
        terminal.move_cursor({25, 10}));
}

TEST(terminal_cursor_test, move_to_column_under_9_supports_cha_uses_cha)
{
    // When moving to a column < 10, the shortest sequence is to use
    // CHA, since it only requires one extra digit in all cases.
    terminalpp::terminal::behaviour behaviour;
    behaviour.supports_cha = true;
    
    terminalpp::terminal terminal(behaviour);
    terminal.move_cursor({20, 10});
    
    expect_sequence(
        std::string("\x1B[9G"),
        terminal.move_cursor({8, 10}));
}

TEST(terminal_cursor_test, move_to_column_under_9_no_cha_uses_cub_or_cuf)
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

TEST(terminal_cursor_test, move_to_origin_row_uses_cuu)
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

TEST(terminal_cursor_test, move_to_row_above_uses_cuu)
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

TEST(terminal_cursor_test, move_to_row_below_uses_cud)
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

TEST(terminal_cursor_test, move_to_different_column_and_row_uses_cup)
{
    // When moving to a different column and row, CUP is used.
    terminalpp::terminal terminal;
    terminal.move_cursor({5, 5});
    
    expect_sequence(
        std::string("\x1B[4;11H"),
        terminal.move_cursor({10, 3}));
}

TEST(terminal_cursor_test, show_cursor_by_default_shows_cursor)
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("\x1B[?25h"),
        terminal.show_cursor());
}

TEST(terminal_cursor_test, hide_cursor_by_default_hides_cursor)
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("\x1B[?25l"),
        terminal.hide_cursor());
}

TEST(terminal_cursor_test, show_cursor_when_shown_does_nothing)
{
    terminalpp::terminal terminal;
    terminal.show_cursor();
    
    expect_sequence(
        std::string(""),
        terminal.show_cursor());
}

TEST(terminal_cursor_test, hide_cursor_when_shown_hides_cursor)
{
    terminalpp::terminal terminal;
    terminal.show_cursor();
    
    expect_sequence(
        std::string("\x1B[?25l"),
        terminal.hide_cursor());
}

TEST(terminal_cursor_test, show_cursor_when_hidden_sends_show_cursor)
{
    terminalpp::terminal terminal;
    terminal.hide_cursor();
    
    expect_sequence(
        std::string("\x1B[?25h"),
        terminal.show_cursor());
}

TEST(terminal_cursor_test, hide_cursor_when_hidden_does_nothing)
{
    terminalpp::terminal terminal;
    terminal.hide_cursor();
    
    expect_sequence(
        std::string(""),
        terminal.hide_cursor());
}

TEST(terminal_cursor_test, save_cursor_position_saves_position)
{
    terminalpp::terminal terminal;
    
    expect_sequence(
        std::string("\x1B[s"),
        terminal.save_cursor());            
}

TEST(terminal_cursor_test, restore_cursor_position_restores_position)
{
    terminalpp::terminal terminal;
    terminal.move_cursor({5, 5});
    terminal.save_cursor();
    terminal.move_cursor({10, 10});
    
    expect_sequence(
        std::string("\x1B[u"),
        terminal.restore_cursor());
    
    expect_sequence(
        std::string(""),
        terminal.move_cursor({5, 5}));
}
