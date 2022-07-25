#include "terminal_test.hpp"
#include "expect_sequence.hpp"
#include <gtest/gtest.h>

using namespace terminalpp::literals;

TEST_F(a_terminal, can_erase_its_entire_display)
{
    terminal_ << terminalpp::erase_display();
    expect_sequence("\x1B[2J"_tb, channel_.written_);
}

TEST_F(a_terminal, when_the_attribute_is_non_default_resets_attributes_before_erasing_the_display)
{
    terminal_ << "\\[1a"_ets;
    channel_.written_.clear();

    terminal_ << terminalpp::erase_display();
    expect_sequence("\x1B[0m\x1B[2J"_tb, channel_.written_);
}

TEST_F(a_terminal, that_erased_display_with_non_default_attribute_writes_attributes_afterwards)
{
    terminal_ << "\\[1a"_ets << terminalpp::erase_display();
    channel_.written_.clear();

    terminal_ << "\\[1a"_ets;
    expect_sequence("\x1B[31ma"_tb, channel_.written_);
}

TEST_F(a_terminal, can_erase_its_display_above_the_cursor)
{
    terminal_ << terminalpp::erase_display_above();
    expect_sequence("\x1B[1J"_tb, channel_.written_);
}

TEST_F(a_terminal, when_the_attribute_is_non_default_resets_attributes_before_erasing_the_display_above)
{
    terminal_ << "\\[1a"_ets;
    channel_.written_.clear();

    terminal_ << terminalpp::erase_display_above();
    expect_sequence("\x1B[0m\x1B[1J"_tb, channel_.written_);
}

TEST_F(a_terminal, that_erased_display_above_with_non_default_attribute_writes_attributes_afterwards)
{
    terminal_ << "\\[1a"_ets << terminalpp::erase_display_above();
    channel_.written_.clear();

    terminal_ << "\\[1a"_ets;
    expect_sequence("\x1B[31ma"_tb, channel_.written_);
}

TEST_F(a_terminal, can_erase_its_display_below_the_cursor)
{
    terminal_ << terminalpp::erase_display_below();
    expect_sequence("\x1B[J"_tb, channel_.written_);
}

TEST_F(a_terminal, when_the_attribute_is_non_default_resets_attributes_before_erasing_the_display_below)
{
    terminal_ << "\\[1a"_ets;
    channel_.written_.clear();

    terminal_ << terminalpp::erase_display_below();
    expect_sequence("\x1B[0m\x1B[J"_tb, channel_.written_);
}

TEST_F(a_terminal, that_erased_display_below_with_non_default_attribute_writes_attributes_afterwards)
{
    terminal_ << "\\[1a"_ets << terminalpp::erase_display_below();
    channel_.written_.clear();

    terminal_ << "\\[1a"_ets;
    expect_sequence("\x1B[31ma"_tb, channel_.written_);
}

TEST_F(a_terminal, can_erase_its_current_line)
{
    terminal_ << terminalpp::erase_line();
    expect_sequence("\x1B[2K"_tb, channel_.written_);
}

TEST_F(a_terminal, when_the_attribute_is_non_default_resets_attributes_before_erasing_the_current_line)
{
    terminal_ << "\\[1a"_ets;
    channel_.written_.clear();

    terminal_ << terminalpp::erase_line();
    expect_sequence("\x1B[0m\x1B[2K"_tb, channel_.written_);
}

TEST_F(a_terminal, that_erased_the_current_line_with_non_default_attribute_writes_attributes_afterwards)
{
    terminal_ << "\\[1a"_ets << terminalpp::erase_line();
    channel_.written_.clear();

    terminal_ << "\\[1a"_ets;
    expect_sequence("\x1B[31ma"_tb, channel_.written_);
}

TEST_F(a_terminal, can_erase_to_the_left_of_the_cursor)
{
    terminal_ << terminalpp::erase_line_left();
    expect_sequence("\x1B[1K"_tb, channel_.written_);
}

TEST_F(a_terminal, when_the_attribute_is_non_default_resets_attributes_before_erasing_to_the_left_of_the_current_line)
{
    terminal_ << "\\[1a"_ets;
    channel_.written_.clear();

    terminal_ << terminalpp::erase_line_left();
    expect_sequence("\x1B[0m\x1B[1K"_tb, channel_.written_);
}

TEST_F(a_terminal, that_erased_to_the_left_of_the_current_line_with_non_default_attribute_writes_attributes_afterwards)
{
    terminal_ << "\\[1a"_ets << terminalpp::erase_line_left();
    channel_.written_.clear();

    terminal_ << "\\[1a"_ets;
    expect_sequence("\x1B[31ma"_tb, channel_.written_);
}

TEST_F(a_terminal, can_erase_to_the_right_of_the_cursor)
{
    terminal_ << terminalpp::erase_line_right();
    expect_sequence("\x1B[K"_tb, channel_.written_);
}

TEST_F(a_terminal, when_the_attribute_is_non_default_resets_attributes_before_erasing_to_the_right_of_the_current_line)
{
    terminal_ << "\\[1a"_ets;
    channel_.written_.clear();

    terminal_ << terminalpp::erase_line_right();
    expect_sequence("\x1B[0m\x1B[K"_tb, channel_.written_);
}

TEST_F(a_terminal, that_erased_to_the_right_of_the_current_line_with_non_default_attribute_writes_attributes_afterwards)
{
    terminal_ << "\\[1a"_ets << terminalpp::erase_line_right();
    channel_.written_.clear();

    terminal_ << "\\[1a"_ets;
    expect_sequence("\x1B[31ma"_tb, channel_.written_);
}
