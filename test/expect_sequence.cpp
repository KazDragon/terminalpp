#include "expect_sequence.hpp"
#include <gtest/gtest.h>
#include <fmt/format.h>
#include <cctype>

namespace {

std::string escape(terminalpp::byte_storage const &text)
{
    std::string result;

    for (auto const by : text)
    {
        auto const ch = char(by);

        if (!isprint(ch))
        {
            using namespace fmt::literals;
            result += "0x{:02X}"_format(int(ch));
        }
        else
        {
            result += ch;
        }
    }

    return result;
}

}

void expect_sequence(terminalpp::byte_storage const &expected, terminalpp::byte_storage const &result)
{
    if (expected != result)
    {
        std::cout << "\n"
                  << "Expected: \"" << escape(expected) << "\"\n"
                  << "Result:   \"" << escape(result) << "\"\n";
    }

    ASSERT_EQ(expected, result);
}
