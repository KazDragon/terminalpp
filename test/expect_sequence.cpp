#include "expect_sequence.hpp"
#include <gtest/gtest.h>
#include <fmt/format.h>
#include <cctype>

static std::string escape(std::string const &str)
{
    std::string result;

    for (auto ch : str)
    {
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

void expect_sequence(std::string const &expected, std::string const &result)
{
    if (expected != result)
    {
        std::cout << "\n"
                  << "Expected: \"" << escape(expected) << "\"\n"
                  << "Result:   \"" << escape(result) << "\"\n";
    }

    ASSERT_EQ(expected, result);
}
