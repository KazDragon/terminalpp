#include "terminal_test.hpp"
#include "expect_sequence.hpp"
#include <gtest/gtest.h>

using namespace terminalpp::literals;

TEST_F(a_terminal, can_erase_its_entire_display)
{
    terminal_.write(append_to_result) << terminalpp::erase_display();
    expect_sequence("\x1B[2J"_tb, result_);
}

TEST_F(a_terminal, when_the_attribute_is_non_default_resets_attributes_before_erasing_the_display)
{
    terminal_.write(discard_result) << "\\[1a"_ets;
    terminal_.write(append_to_result) << terminalpp::erase_display();
    expect_sequence("\x1B[0m\x1B[2J"_tb, result_);
}

TEST_F(a_terminal, that_erased_display_with_non_default_attribute_writes_attributes_afterwards)
{
    terminal_.write(discard_result) << "\\[1a"_ets << terminalpp::erase_display();
    terminal_.write(append_to_result) << "\\[1a"_ets;
    expect_sequence("\x1B[31ma"_tb, result_);
}
TEST_F(a_terminal, can_erase_its_display_above_the_cursor)
{
    terminal_.write(append_to_result) << terminalpp::erase_display_above();
    expect_sequence("\x1B[1J"_tb, result_);
}

TEST_F(a_terminal, when_the_attribute_is_non_default_resets_attributes_before_erasing_the_display_above)
{
    terminal_.write(discard_result) << "\\[1a"_ets;
    terminal_.write(append_to_result) << terminalpp::erase_display_above();
    expect_sequence("\x1B[0m\x1B[1J"_tb, result_);
}

TEST_F(a_terminal, that_erased_display_above_with_non_default_attribute_writes_attributes_afterwards)
{
    terminal_.write(discard_result) << "\\[1a"_ets << terminalpp::erase_display_above();
    terminal_.write(append_to_result) << "\\[1a"_ets;
    expect_sequence("\x1B[31ma"_tb, result_);
}

TEST_F(a_terminal, can_erase_its_display_below_the_cursor)
{
    terminal_.write(append_to_result) << terminalpp::erase_display_below();
    expect_sequence("\x1B[J"_tb, result_);
}

TEST_F(a_terminal, when_the_attribute_is_non_default_resets_attributes_before_erasing_the_display_below)
{
    terminal_.write(discard_result) << "\\[1a"_ets;
    terminal_.write(append_to_result) << terminalpp::erase_display_below();
    expect_sequence("\x1B[0m\x1B[J"_tb, result_);
}

TEST_F(a_terminal, that_erased_display_below_with_non_default_attribute_writes_attributes_afterwards)
{
    terminal_.write(discard_result) << "\\[1a"_ets << terminalpp::erase_display_below();
    terminal_.write(append_to_result) << "\\[1a"_ets;
    expect_sequence("\x1B[31ma"_tb, result_);
}

TEST_F(a_terminal, can_erase_its_current_line)
{
    terminal_.write(append_to_result) << terminalpp::erase_line();
    expect_sequence("\x1B[2K"_tb, result_);
}

TEST_F(a_terminal, can_erase_to_the_left_of_the_cursor)
{
    terminal_.write(append_to_result) << terminalpp::erase_line_left();
    expect_sequence("\x1B[1K"_tb, result_);
}

TEST_F(a_terminal, can_erase_to_the_right_of_the_cursor)
{
    terminal_.write(append_to_result) << terminalpp::erase_line_right();
    expect_sequence("\x1B[K"_tb, result_);
}
