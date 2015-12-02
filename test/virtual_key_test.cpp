#include "terminalpp/virtual_key.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class virtual_key_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(virtual_key_test);
        CPPUNIT_TEST(default_vk_modifier_matches_none);
        CPPUNIT_TEST(oring_several_modifiers_matches_only_those_modifiers);
        CPPUNIT_TEST(or_assignment_matches_those_modifiers_orred);
        CPPUNIT_TEST(and_assignment_matches_intersection);
    CPPUNIT_TEST_SUITE_END();

private :
    void default_vk_modifier_matches_none();
    void oring_several_modifiers_matches_only_those_modifiers();
    void or_assignment_matches_those_modifiers_orred();
    void and_assignment_matches_intersection();
};

CPPUNIT_TEST_SUITE_REGISTRATION(virtual_key_test);

void virtual_key_test::default_vk_modifier_matches_none()
{
    terminalpp::vk_modifier vk_none = terminalpp::vk_modifier::none;
    CPPUNIT_ASSERT(
        (vk_none & terminalpp::vk_modifier::shift)
            == terminalpp::vk_modifier::none);
}

void virtual_key_test::oring_several_modifiers_matches_only_those_modifiers()
{
    terminalpp::vk_modifier vk_shift_ctrl =
        terminalpp::vk_modifier::shift
      | terminalpp::vk_modifier::ctrl;

    CPPUNIT_ASSERT(
        (vk_shift_ctrl & terminalpp::vk_modifier::shift)
            == terminalpp::vk_modifier::shift);

    CPPUNIT_ASSERT(
        (vk_shift_ctrl & terminalpp::vk_modifier::ctrl)
            == terminalpp::vk_modifier::ctrl);

    CPPUNIT_ASSERT(
        (vk_shift_ctrl & terminalpp::vk_modifier::meta)
            == terminalpp::vk_modifier::none);
}

void virtual_key_test::or_assignment_matches_those_modifiers_orred()
{
    terminalpp::vk_modifier vk = terminalpp::vk_modifier::meta;
    vk |= terminalpp::vk_modifier::shift;

    CPPUNIT_ASSERT(
        vk == (terminalpp::vk_modifier::meta | terminalpp::vk_modifier::shift));
}

void virtual_key_test::and_assignment_matches_intersection()
{
    terminalpp::vk_modifier vk = terminalpp::vk_modifier::shift
                               | terminalpp::vk_modifier::ctrl;

    vk &= (terminalpp::vk_modifier::shift | terminalpp::vk_modifier::meta);

    CPPUNIT_ASSERT(vk == terminalpp::vk_modifier::shift);
}
