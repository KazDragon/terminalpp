#include "terminalpp/default_terminal.hpp"
#include "expect_sequence.hpp"
#include <gtest/gtest.h>
#include <string>
#include <iostream>

TEST(a_default_terminal_with_an_unknown_location, sends_absolute_coordinates_when_moving)
{
    terminalpp::default_terminal terminal;

    expect_sequence(
        std::string("\x1B[3;3H"),
        terminal.move_cursor({2, 2}));
}

TEST(a_default_terminal_with_a_known_location, sends_nothing_when_moving_to_the_same_coordinates)
{
    terminalpp::default_terminal terminal;
    terminal.move_cursor({10, 10});

    expect_sequence(std::string{}, terminal.move_cursor({10, 10}));
}

TEST(a_default_terminal_supporting_cha_default_and_a_known_location,
     when_moving_to_the_home_column_sends_cha_with_no_argument)
{
    terminalpp::behaviour behaviour;
    behaviour.supports_cha         = true;
    behaviour.supports_cha_default = true;

    terminalpp::default_terminal terminal(behaviour);
    terminal.move_cursor({10, 10});

    expect_sequence(
        std::string("\x1B[G"),
        terminal.move_cursor({0, 10}));
}

TEST(a_default_terminal_supporting_cha_but_not_cha_default_and_a_known_location,
     when_moving_to_the_home_column_sends_cha_with_column_argument)
{
    terminalpp::behaviour behaviour;
    behaviour.supports_cha         = true;
    behaviour.supports_cha_default = false;

    terminalpp::default_terminal terminal(behaviour);
    terminal.move_cursor({10, 10});

    expect_sequence(
        std::string("\x1B[1G"),
        terminal.move_cursor({0, 10}));
}

TEST(a_default_terminal_not_supporting_cha_and_a_known_location,
     when_moving_to_the_home_column_sends_cub)
{
    terminalpp::behaviour behaviour;
    behaviour.supports_cha         = false;
    behaviour.supports_cha_default = false;

    terminalpp::default_terminal terminal(behaviour);
    terminal.move_cursor({10, 10});

    expect_sequence(
        std::string("\x1B[10D"),
        terminal.move_cursor({0, 10}));
}

TEST(a_default_terminal_with_known_location,
     when_moving_left_to_at_least_the_tenth_column_sends_cub)
{
    terminalpp::default_terminal terminal;
    terminal.move_cursor({20, 10});

    expect_sequence(
        std::string("\x1B[11D"),
        terminal.move_cursor({9, 10}));
}

TEST(a_default_terminal_with_known_location,
     when_moving_left_to_less_than_the_tenth_column_sends_cha)
{
    terminalpp::behaviour behaviour;
    behaviour.supports_cha = true;

    terminalpp::default_terminal terminal(behaviour);
    terminal.move_cursor({20, 10});

    expect_sequence(
        std::string("\x1B[9G"),
        terminal.move_cursor({8, 10}));
}

TEST(a_default_terminal_with_known_location,
     when_moving_right_to_at_least_the_tenth_column_sends_cuf)
{
    terminalpp::default_terminal terminal;
    terminal.move_cursor({5, 10});

    expect_sequence(
        std::string("\x1B[4C"),
        terminal.move_cursor({9, 10}));
}

TEST(a_default_terminal_with_known_location,
     when_moving_right_to_less_than_the_tenth_column_sends_cha)
{
    terminalpp::default_terminal terminal;
    terminal.move_cursor({5, 10});

    expect_sequence(
        std::string("\x1B[9G"),
        terminal.move_cursor({8, 10}));
}

TEST(terminal_cursor_test, move_to_column_under_9_no_cha_uses_cub_or_cuf)
{
    // When moving to column < 10, but CHA is not supported, then we must
    // use either CUB or CUF instead.
    terminalpp::behaviour behaviour;
    behaviour.supports_cha = false;

    terminalpp::default_terminal terminal(behaviour);
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
    terminalpp::default_terminal terminal;
    terminal.move_cursor({9, 9});

    expect_sequence(
        std::string("\x1B[8A"),
        terminal.move_cursor({9, 1}));
}

TEST(terminal_cursor_test, move_to_row_above_uses_cuu)
{
    // When moving to a row above, we should use CUU in all circumstances.
    terminalpp::default_terminal terminal;
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
    terminalpp::default_terminal terminal;
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
    terminalpp::default_terminal terminal;
    terminal.move_cursor({5, 5});

    expect_sequence(
        std::string("\x1B[4;11H"),
        terminal.move_cursor({10, 3}));
}

TEST(terminal_cursor_test, show_cursor_by_default_shows_cursor)
{
    terminalpp::default_terminal terminal;

    expect_sequence(
        std::string("\x1B[?25h"),
        terminal.show_cursor());
}

TEST(terminal_cursor_test, hide_cursor_by_default_hides_cursor)
{
    terminalpp::default_terminal terminal;

    expect_sequence(
        std::string("\x1B[?25l"),
        terminal.hide_cursor());
}

TEST(terminal_cursor_test, show_cursor_when_shown_does_nothing)
{
    terminalpp::default_terminal terminal;
    terminal.show_cursor();

    expect_sequence(
        std::string(""),
        terminal.show_cursor());
}

TEST(terminal_cursor_test, hide_cursor_when_shown_hides_cursor)
{
    terminalpp::default_terminal terminal;
    terminal.show_cursor();

    expect_sequence(
        std::string("\x1B[?25l"),
        terminal.hide_cursor());
}

TEST(terminal_cursor_test, show_cursor_when_hidden_sends_show_cursor)
{
    terminalpp::default_terminal terminal;
    terminal.hide_cursor();

    expect_sequence(
        std::string("\x1B[?25h"),
        terminal.show_cursor());
}

TEST(terminal_cursor_test, hide_cursor_when_hidden_does_nothing)
{
    terminalpp::default_terminal terminal;
    terminal.hide_cursor();

    expect_sequence(
        std::string(""),
        terminal.hide_cursor());
}

TEST(terminal_cursor_test, save_cursor_position_saves_position)
{
    terminalpp::default_terminal terminal;

    expect_sequence(
        std::string("\x1B[s"),
        terminal.save_cursor());
}

TEST(terminal_cursor_test, restore_cursor_position_restores_position)
{
    terminalpp::default_terminal terminal;
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
