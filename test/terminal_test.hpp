#pragma once

#include "expect_sequence.hpp"
#include "fakes/fake_channel.hpp"
#include <terminalpp/terminal.hpp>
#include <functional>
#include <gtest/gtest.h>

class terminal_test_base
{
public:
    terminal_test_base(terminalpp::behaviour const &behaviour = terminalpp::behaviour{})
      : terminal_{channel_, behaviour}
    {
    }

protected:
    fake_channel channel_;
    terminalpp::terminal terminal_;
};

class a_new_terminal :
    public testing::Test,
    public terminal_test_base
{
public:
    a_new_terminal(terminalpp::behaviour const &behaviour = terminalpp::behaviour{})
      : terminal_test_base(behaviour)
    {
    }
};

class a_terminal : 
    public testing::Test,
    public terminal_test_base
{
public:
    a_terminal(terminalpp::behaviour const &behaviour = terminalpp::behaviour{})
      : terminal_test_base(behaviour)
    {
        // Skip over the (tested) terminal init sequence to set the attribute
        // to default.
        using namespace terminalpp::literals;
        terminal_ << ""_ets;
        channel_.written_.clear();
    }
};
