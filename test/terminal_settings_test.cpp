#include "terminalpp/terminal.hpp"
#include "expect_sequence.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

class terminal_settings_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(terminal_settings_test);
        CPPUNIT_TEST(enabling_mouse_mode_with_default_behaviour_sends_nothing);
        CPPUNIT_TEST(enabling_mouse_mode_with_basic_mouse_support_sends_basic_mouse_tracking);
    CPPUNIT_TEST_SUITE_END();

private :
    void enabling_mouse_mode_with_default_behaviour_sends_nothing();
    void enabling_mouse_mode_with_basic_mouse_support_sends_basic_mouse_tracking();
};

CPPUNIT_TEST_SUITE_REGISTRATION(terminal_settings_test);

void terminal_settings_test::enabling_mouse_mode_with_default_behaviour_sends_nothing()
{
    terminalpp::terminal terminal;

    expect_sequence(
        std::string(""),
        terminal.enable_mouse());
}

void terminal_settings_test::enabling_mouse_mode_with_basic_mouse_support_sends_basic_mouse_tracking()
{
    terminalpp::terminal::behaviour behaviour;
    behaviour.supports_basic_mouse_tracking = true;

    terminalpp::terminal terminal(behaviour);

    expect_sequence(
        std::string("\x1B[?1000h"),
        terminal.enable_mouse());
}