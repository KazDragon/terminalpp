#pragma once

#include "expect_sequence.hpp"
#include <terminalpp/terminal.hpp>
#include <functional>
#include <gtest/gtest.h>

class terminal_test_base
{
public:
    terminal_test_base(terminalpp::behaviour const &behaviour = terminalpp::behaviour{})
      : terminal_{
            [](terminalpp::tokens) { /* unused */ },
            [this](terminalpp::bytes data) { 
                this->result_.append(std::cbegin(data), std::cend(data)); 
            },
            behaviour
        }
    {
        using namespace terminalpp::literals;
        terminal_ << ""_ets;
        result_.clear();
    }

    void expect_when_streaming(
        terminalpp::bytes  const &expected_result,
        terminalpp::string const &encoded_text)
    {
        terminal_ << encoded_text;
        expect_sequence(expected_result, result_);
    }

protected:
    terminalpp::terminal terminal_;
    terminalpp::byte_storage result_;
};

class a_terminal : 
    public testing::Test,
    public terminal_test_base
{
public:
    a_terminal(terminalpp::behaviour const &behaviour = terminalpp::behaviour{})
      : terminal_test_base(behaviour)
    {
    }
};
