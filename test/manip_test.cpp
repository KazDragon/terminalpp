#include <terminalpp/ansi_terminal.hpp>
#include <terminalpp/terminal_manip.hpp>
#include <gtest/gtest.h>

using namespace terminalpp::literals;

TEST(a_terminal, can_have_a_terminal_string_streamed_to_it)
{
    terminalpp::ansi_terminal terminal;

    std::string const expected_result = "test";
    std::string const result = terminal << "test"_ets;

    ASSERT_EQ(expected_result, result);
}

TEST(a_terminal, can_have_an_attributed_terminal_string_streamed_to_it)
{
    terminalpp::ansi_terminal terminal;
    std::string const expected_result = "\x1B[31mtest";
    std::string const result = terminal << "\\[1test"_ets;

    ASSERT_EQ(expected_result, result);
}

TEST(a_terminal, can_have_a_cursor_move_streamed_to_it)
{
    terminalpp::ansi_terminal reference_terminal;
    std::string const expected_result = reference_terminal.move_cursor({5, 10});

    terminalpp::ansi_terminal terminal;
    std::string const result = terminal << terminalpp::move_cursor({5, 10});

    ASSERT_EQ(expected_result, result);
}

TEST(a_terminal, can_have_a_position_and_a_cursor_move_streamed_to_it)
{
    terminalpp::ansi_terminal reference_terminal;
    std::string expected_result = reference_terminal.move_cursor({10, 5});
    expected_result += reference_terminal.write("test");

    terminalpp::ansi_terminal terminal;
    std::string result =
        terminal << terminalpp::move_cursor({10, 5})
                 << "test"_ets;

    ASSERT_EQ(expected_result, result);
}
