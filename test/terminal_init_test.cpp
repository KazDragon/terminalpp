#include "terminalpp/terminal.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

class terminal_init_test_fixture : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(terminal_init_test_fixture);
        CPPUNIT_TEST(cannot_use_eight_bit_control_codes_does_nothing);
        CPPUNIT_TEST(starts_in_eight_bit_mode_does_nothing);
        CPPUNIT_TEST(requires_eight_bit_mode_switch_sends_command);
    CPPUNIT_TEST_SUITE_END();
    
private :
    void cannot_use_eight_bit_control_codes_does_nothing();
    void starts_in_eight_bit_mode_does_nothing();
    void requires_eight_bit_mode_switch_sends_command();
};

CPPUNIT_TEST_SUITE_REGISTRATION(terminal_init_test_fixture);

void terminal_init_test_fixture::cannot_use_eight_bit_control_codes_does_nothing()
{
    // If a terminal cannot support 8-bit control codes, then there's no need
    // to send any kind of initialization sequence.
    terminalpp::terminal::behaviour behaviour;
    behaviour.can_use_eight_bit_control_codes = false;
    
    terminalpp::terminal terminal(behaviour);
    auto init_string = terminal.init();
    
    CPPUNIT_ASSERT_EQUAL(std::string(""), init_string);
}

void terminal_init_test_fixture::starts_in_eight_bit_mode_does_nothing()
{
    // If a terminal can support 8-bit control codes, and does so without any
    // prompting, then there is also no reason to send any kind of
    // initialization sequence.
    terminalpp::terminal::behaviour behaviour;
    behaviour.can_use_eight_bit_control_codes = true;
    behaviour.uses_eight_bit_control_codes_by_default = true;
    
    terminalpp::terminal terminal(behaviour);
    auto init_string = terminal.init();
    
    CPPUNIT_ASSERT_EQUAL(std::string(""), init_string);
}

void terminal_init_test_fixture::requires_eight_bit_mode_switch_sends_command()
{
    // If a terminal supports 8-bit control codes but requires a command to
    // switch it into that mode, then we expect that that sequence will be
    // sent.
    terminalpp::terminal::behaviour behaviour;
    behaviour.can_use_eight_bit_control_codes = true;
    behaviour.uses_eight_bit_control_codes_by_default = false;
    
    terminalpp::terminal terminal(behaviour);
    auto init_string = terminal.init();
    
    CPPUNIT_ASSERT_EQUAL(std::string("\x1B G"), init_string);
}
