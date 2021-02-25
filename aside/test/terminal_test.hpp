#pragma once

#include <terminalpp/terminal.hpp>
#include <terminalpp/string.hpp>
#include <gtest/gtest.h>

class a_terminal : public testing::Test
{
protected:
    a_terminal()
    {
        using namespace terminalpp::literals;

        // Here we stimulate the terminal to output its initial attribute-clear
        // so that it isn't involved in every other test.
        terminal_.write(""_ets);
    }

    terminalpp::terminal terminal_;
};
