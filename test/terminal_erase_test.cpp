#include "terminal_test.hpp"
#include "expect_sequence.hpp"
#include <gtest/gtest.h>

TEST_F(a_terminal, can_erase_its_entire_display)
{
    terminalpp::terminal terminal;

    expect_sequence(
        // str seq actual output,
        std::string("\x1B[2J"),

        // action
        terminal.erase_in_display(terminalpp::terminal::erase_display::all));
}

TEST_F(a_terminal, can_erase_its_entire_display_above_the_cursor)
{
    terminalpp::terminal terminal;

    expect_sequence(
        // str seq actual output,
        std::string("\x1B[1J"),

        // action
        terminal.erase_in_display(terminalpp::terminal::erase_display::above));
}

TEST_F(a_terminal, can_erase_its_entire_display_below_the_cursor)
{
    terminalpp::terminal terminal;

    expect_sequence(
        // str seq actual output,
        std::string("\x1B[J"),

        // action
        terminal.erase_in_display(terminalpp::terminal::erase_display::below));
}

TEST_F(a_terminal, can_erase_an_entire_line)
{
    terminalpp::terminal terminal;

    expect_sequence(
        // str seq actual output,
        std::string("\x1B[2K"),

        // action
        terminal.erase_in_line(terminalpp::terminal::erase_line::all));
}

TEST_F(a_terminal, can_erase_an_entire_line_to_the_left_of_the_cursor)
{
    terminalpp::terminal terminal;

    expect_sequence(
        // str seq actual output,
        std::string("\x1B[1K"),

        // action
        terminal.erase_in_line(terminalpp::terminal::erase_line::left));
}

TEST_F(a_terminal, can_erase_an_entire_line_to_the_right_of_the_cursor)
{
    terminalpp::terminal terminal;

    expect_sequence(
        // str seq actual output,
        std::string("\x1B[K"),

        // action
        terminal.erase_in_line(terminalpp::terminal::erase_line::right));
}
