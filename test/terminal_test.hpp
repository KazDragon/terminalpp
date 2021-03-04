#pragma once

#include "expect_sequence.hpp"
#include <terminalpp/terminal.hpp>
#include <functional>
#include <gtest/gtest.h>

class terminal_test_base
{
public:
    terminal_test_base(terminalpp::behaviour const &behaviour = terminalpp::behaviour{})
      : terminal_(append_to_result, behaviour)
    {
    }

    void expect_when_streaming(
        terminalpp::bytes  const &expected_result,
        terminalpp::string const &encoded_text)
    {
        using namespace terminalpp::literals;
        terminal_.write(discard_result) << ""_ets;
        terminal_.write(append_to_result) << encoded_text;

        expect_sequence(expected_result, result_);
    }

protected:
    std::function<void (terminalpp::bytes)> append_to_result =
        [this](terminalpp::bytes data)
        {
            this->result_.append(std::cbegin(data), std::cend(data));
        };

    std::function<void (terminalpp::bytes)> discard_result =
        [this](terminalpp::bytes)
        {
        };

    terminalpp::terminal  terminal_;
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
