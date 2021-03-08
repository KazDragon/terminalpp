#include "terminalpp/terminal.hpp"
#include "expect_sequence.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace terminalpp::literals;

TEST(a_terminal_without_8_bit_support, when_init_is_called_sends_nothing)
{
    // If a terminal cannot support 8-bit control codes, then there's no need
    // to send any kind of initialization sequence.
    terminalpp::behaviour behaviour;
    behaviour.can_use_eight_bit_control_codes = false;

    terminalpp::byte_storage init_result;
    terminalpp::terminal terminal(
        [&](terminalpp::bytes data)
        {
            init_result.append(data.begin(), data.end());
        },
        behaviour);

    expect_sequence(""_tb, init_result);
}

TEST(a_terminal_that_starts_in_8_bit_mode, when_init_is_called_sends_nothing)
{
    // If a terminal can support 8-bit control codes, and does so without any
    // prompting, then there is also no reason to send any kind of
    // initialization sequence.
    terminalpp::behaviour behaviour;
    behaviour.can_use_eight_bit_control_codes = true;
    behaviour.uses_eight_bit_control_codes_by_default = true;

    terminalpp::byte_storage init_result;
    terminalpp::terminal terminal(
        [&](terminalpp::bytes data)
        {
            init_result.append(data.begin(), data.end());
        },
        behaviour);

    expect_sequence(""_tb, init_result);
}

TEST(a_terminal_that_supports_8_bit_mode_but_starts_in_7_bit_mode,
     when_init_is_called_sends_8_bit_mode_command)
{
    // If a terminal supports 8-bit control codes but requires a command to
    // switch it into that mode, then we expect that that sequence will be
    // sent.
    terminalpp::behaviour behaviour;
    behaviour.can_use_eight_bit_control_codes = true;
    behaviour.uses_eight_bit_control_codes_by_default = false;

    terminalpp::byte_storage init_result;
    terminalpp::terminal terminal(
        [&](terminalpp::bytes data)
        {
            init_result.append(data.begin(), data.end());
        },
        behaviour);

    expect_sequence("\x1B G"_tb, init_result);
}
