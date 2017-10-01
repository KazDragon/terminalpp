#include "terminalpp/virtual_key.hpp"
#include <gtest/gtest.h>

TEST(a_default_constructed_vk, has_default_members)
{
    terminalpp::virtual_key vk;

    ASSERT_EQ(terminalpp::vk::nul, vk.key);
    ASSERT_EQ(terminalpp::vk_modifier::none, vk.modifiers);
    ASSERT_EQ(0, vk.repeat_count);

    char *psequence = boost::get<char>(&vk.sequence);
    ASSERT_NE(nullptr, psequence);
    ASSERT_EQ('\0', *psequence);
}

TEST(anding_a_default_vk_modifer, matches_none)
{
    terminalpp::vk_modifier vk_none = terminalpp::vk_modifier::none;
    ASSERT_TRUE(
        (vk_none & terminalpp::vk_modifier::shift)
            == terminalpp::vk_modifier::none);
}

TEST(oring_several_vk_modifiers, matches_only_those_modifiers)
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

TEST(or_assigning_vk_modifiers, matches_those_modifiers_orred)
{
    terminalpp::vk_modifier vk = terminalpp::vk_modifier::meta;
    vk |= terminalpp::vk_modifier::shift;

    ASSERT_TRUE(
        vk == (terminalpp::vk_modifier::meta | terminalpp::vk_modifier::shift));
}

TEST(and_assigning_vk_modifiers, matches_intersection)
{
    terminalpp::vk_modifier vk = terminalpp::vk_modifier::shift
                               | terminalpp::vk_modifier::ctrl;

    vk &= (terminalpp::vk_modifier::shift | terminalpp::vk_modifier::meta);

    ASSERT_TRUE(vk == terminalpp::vk_modifier::shift);
}
