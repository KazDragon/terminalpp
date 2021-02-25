#pragma once

#include <terminalpp/terminal.hpp>
#include <functional>
#include <gtest/gtest.h>

class a_terminal : public testing::Test
{
public:
    a_terminal()
      : terminal_(append_to_result)
    {
    }

protected:
    std::function<void (terminalpp::bytes)> append_to_result =
        [this](terminalpp::bytes data)
        {
            this->result_.append(std::cbegin(data), std::cend(data));
        };

    terminalpp::terminal terminal_;
    terminalpp::byte_storage result_;
};
