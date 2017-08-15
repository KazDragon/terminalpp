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