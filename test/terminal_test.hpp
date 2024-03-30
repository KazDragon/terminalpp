#pragma once

#include "fakes/fake_channel.hpp"

#include <gtest/gtest.h>
#include <terminalpp/terminal.hpp>

class terminal_test_base
{
public:
    explicit terminal_test_base(
        terminalpp::behaviour const &behaviour = terminalpp::behaviour{})
      : terminal_{channel_, behaviour}
    {
    }

protected:
    fake_channel channel_;
    terminalpp::terminal terminal_;
};

class a_new_terminal : public testing::Test, public terminal_test_base
{
public:
    explicit a_new_terminal(
        terminalpp::behaviour const &behaviour = terminalpp::behaviour{})
      : terminal_test_base(behaviour)
    {
    }
};

class a_terminal : public testing::Test, public terminal_test_base
{
public:
    explicit a_terminal(
        terminalpp::behaviour const &behaviour = terminalpp::behaviour{})
      : terminal_test_base(behaviour)
    {
        // Skip over the (tested) terminal init sequence to set the attribute
        // to default.
        using namespace terminalpp::literals;  // NOLINT
        terminal_ << ""_ets;
        channel_.written_.clear();
    }
};
