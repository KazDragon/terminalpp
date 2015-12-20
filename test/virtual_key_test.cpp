#include "terminalpp/virtual_key.hpp"
#include <gtest/gtest.h>

TEST(virtual_key_test, default_vk_modifier_matches_none)
{
    terminalpp::vk_modifier vk_none = terminalpp::vk_modifier::none;
    ASSERT_TRUE(
        (vk_none & terminalpp::vk_modifier::shift)
            == terminalpp::vk_modifier::none);
}

TEST(virtual_key_test, oring_several_modifiers_matches_only_those_modifiers)
{
    terminalpp::vk_modifier vk_shift_ctrl =
        terminalpp::vk_modifier::shift
      | terminalpp::vk_modifier::ctrl;

    ASSERT_TRUE(
        (vk_shift_ctrl & terminalpp::vk_modifier::shift)
            == terminalpp::vk_modifier::shift);

    ASSERT_TRUE(
        (vk_shift_ctrl & terminalpp::vk_modifier::ctrl)
            == terminalpp::vk_modifier::ctrl);

    ASSERT_TRUE(
        (vk_shift_ctrl & terminalpp::vk_modifier::meta)
            == terminalpp::vk_modifier::none);
}

TEST(virtual_key_test, or_assignment_matches_those_modifiers_orred)
{
    terminalpp::vk_modifier vk = terminalpp::vk_modifier::meta;
    vk |= terminalpp::vk_modifier::shift;

    ASSERT_TRUE(
        vk == (terminalpp::vk_modifier::meta | terminalpp::vk_modifier::shift));
}

TEST(virtual_key_test, and_assignment_matches_intersection)
{
    terminalpp::vk_modifier vk = terminalpp::vk_modifier::shift
                               | terminalpp::vk_modifier::ctrl;

    vk &= (terminalpp::vk_modifier::shift | terminalpp::vk_modifier::meta);

    ASSERT_TRUE(vk == terminalpp::vk_modifier::shift);
}
