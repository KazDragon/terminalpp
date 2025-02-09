#include "terminal_test.hpp"

#include <gmock/gmock.h>

using namespace terminalpp::literals;  // NOLINT
using testing::ContainerEq;

TEST_F(a_terminal, can_erase_its_entire_display)
{
    terminal_ << terminalpp::erase_display();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[2J"_tb));
}

TEST_F(
    a_terminal,
    when_the_attribute_is_non_default_resets_attributes_before_erasing_the_display)
{
    terminal_ << R"(\[1a)"_ets;
    channel_.written_.clear();

    terminal_ << terminalpp::erase_display();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[0m\x1B[2J"_tb));
}

TEST_F(
    a_terminal,
    that_erased_display_with_non_default_attribute_writes_attributes_afterwards)
{
    terminal_ << R"(\[1a)"_ets << terminalpp::erase_display();
    channel_.written_.clear();

    terminal_ << R"(\[1a)"_ets;
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[31ma"_tb));
}

TEST_F(a_terminal, can_erase_its_display_above_the_cursor)
{
    terminal_ << terminalpp::erase_display_above();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[1J"_tb));
}

TEST_F(
    a_terminal,
    when_the_attribute_is_non_default_resets_attributes_before_erasing_the_display_above)
{
    terminal_ << R"(\[1a)"_ets;
    channel_.written_.clear();

    terminal_ << terminalpp::erase_display_above();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[0m\x1B[1J"_tb));
}

TEST_F(
    a_terminal,
    that_erased_display_above_with_non_default_attribute_writes_attributes_afterwards)
{
    terminal_ << R"(\[1a)"_ets << terminalpp::erase_display_above();
    channel_.written_.clear();

    terminal_ << R"(\[1a)"_ets;
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[31ma"_tb));
}

TEST_F(a_terminal, can_erase_its_display_below_the_cursor)
{
    terminal_ << terminalpp::erase_display_below();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[J"_tb));
}

TEST_F(
    a_terminal,
    when_the_attribute_is_non_default_resets_attributes_before_erasing_the_display_below)
{
    terminal_ << R"(\[1a)"_ets;
    channel_.written_.clear();

    terminal_ << terminalpp::erase_display_below();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[0m\x1B[J"_tb));
}

TEST_F(
    a_terminal,
    that_erased_display_below_with_non_default_attribute_writes_attributes_afterwards)
{
    terminal_ << R"(\[1a)"_ets << terminalpp::erase_display_below();
    channel_.written_.clear();

    terminal_ << R"(\[1a)"_ets;
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[31ma"_tb));
}

TEST_F(a_terminal, can_erase_its_current_line)
{
    terminal_ << terminalpp::erase_line();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[2K"_tb));
}

TEST_F(
    a_terminal,
    when_the_attribute_is_non_default_resets_attributes_before_erasing_the_current_line)
{
    terminal_ << R"(\[1a)"_ets;
    channel_.written_.clear();

    terminal_ << terminalpp::erase_line();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[0m\x1B[2K"_tb));
}

TEST_F(
    a_terminal,
    that_erased_the_current_line_with_non_default_attribute_writes_attributes_afterwards)
{
    terminal_ << R"(\[1a)"_ets << terminalpp::erase_line();
    channel_.written_.clear();

    terminal_ << R"(\[1a)"_ets;
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[31ma"_tb));
}

TEST_F(a_terminal, can_erase_to_the_left_of_the_cursor)
{
    terminal_ << terminalpp::erase_line_left();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[1K"_tb));
}

TEST_F(
    a_terminal,
    when_the_attribute_is_non_default_resets_attributes_before_erasing_to_the_left_of_the_current_line)
{
    terminal_ << R"(\[1a)"_ets;
    channel_.written_.clear();

    terminal_ << terminalpp::erase_line_left();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[0m\x1B[1K"_tb));
}

TEST_F(
    a_terminal,
    that_erased_to_the_left_of_the_current_line_with_non_default_attribute_writes_attributes_afterwards)
{
    terminal_ << R"(\[1a)"_ets << terminalpp::erase_line_left();
    channel_.written_.clear();

    terminal_ << R"(\[1a)"_ets;
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[31ma"_tb));
}

TEST_F(a_terminal, can_erase_to_the_right_of_the_cursor)
{
    terminal_ << terminalpp::erase_line_right();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[K"_tb));
}

TEST_F(
    a_terminal,
    when_the_attribute_is_non_default_resets_attributes_before_erasing_to_the_right_of_the_current_line)
{
    terminal_ << R"(\[1a)"_ets;
    channel_.written_.clear();

    terminal_ << terminalpp::erase_line_right();
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[0m\x1B[K"_tb));
}

TEST_F(
    a_terminal,
    that_erased_to_the_right_of_the_current_line_with_non_default_attribute_writes_attributes_afterwards)
{
    terminal_ << R"(\[1a)"_ets << terminalpp::erase_line_right();
    channel_.written_.clear();

    terminal_ << R"(\[1a)"_ets;
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[31ma"_tb));
}
