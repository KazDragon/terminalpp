#include "expect_sequence.hpp"
#include <gtest/gtest.h>
#include <fmt/format.h>
#include <cctype>

namespace {

std::string escape(terminalpp::bytes const &text)
{
    std::string result;

    for (auto const by : text)
    {
        auto const ch = char(by);

        if (!isprint(ch))
        {
            result += fmt::format("0x{:02X}", int(ch));
        }
        else
        {
            result += ch;
        }
    }

    return result;
}

}

void expect_sequence(terminalpp::bytes const &expected, terminalpp::bytes const &result)
{
    if (expected != result)
    {
        std::cout << "\n"
                  << "Expected: \"" << escape(expected) << "\"\n"
                  << "Result:   \"" << escape(result) << "\"\n";
    }

    ASSERT_EQ(expected, result);
}
