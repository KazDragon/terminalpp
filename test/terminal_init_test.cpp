#include "terminalpp/terminal.hpp"
#include "expect_sequence.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(terminal_init_test, cannot_use_eight_bit_control_codes_does_nothing)
{
    // If a terminal cannot support 8-bit control codes, then there's no need
    // to send any kind of initialization sequence.
    terminalpp::terminal::behaviour behaviour;
    behaviour.can_use_eight_bit_control_codes = false;
    
    terminalpp::terminal terminal(behaviour);
    expect_sequence(
        std::string(""),
        terminal.init());
}

TEST(terminal_init_test, starts_in_eight_bit_mode_does_nothing)
{
    // If a terminal can support 8-bit control codes, and does so without any
    // prompting, then there is also no reason to send any kind of
    // initialization sequence.
    terminalpp::terminal::behaviour behaviour;
    behaviour.can_use_eight_bit_control_codes = true;
    behaviour.uses_eight_bit_control_codes_by_default = true;
    
    terminalpp::terminal terminal(behaviour);
    expect_sequence(
        std::string(""),
        terminal.init());
}

TEST(terminal_init_test, requires_eight_bit_mode_switch_sends_command)
{
    // If a terminal supports 8-bit control codes but requires a command to
    // switch it into that mode, then we expect that that sequence will be
    // sent.
    terminalpp::terminal::behaviour behaviour;
    behaviour.can_use_eight_bit_control_codes = true;
    behaviour.uses_eight_bit_control_codes_by_default = false;
    
    terminalpp::terminal terminal(behaviour);
    expect_sequence(
        std::string("\x1B G"),
        terminal.init());
}
