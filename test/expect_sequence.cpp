#include "expect_sequence.hpp"
#include <fmt/format.h>
#include <gtest/gtest.h>
#include <cctype>

namespace {

std::string escape(terminalpp::bytes const &text)
{
  std::string result;

  for (auto const by : text)
  {
    auto const ch = static_cast<char>(by);

    if (isprint(ch) == 0)
    {
      result += fmt::format("0x{:02X}", static_cast<int>(ch));
    }
    else
    {
      result += ch;
    }
  }

  return result;
}

}  // namespace

void expect_sequence(
    terminalpp::bytes const &expected, terminalpp::bytes const &result)
{
  if (expected != result)
  {
    std::cout << fmt::format(
        "\n"
        "Expected: \"{}\"\n"
        "Result:   \"{}\"\n",
        escape(expected),
        escape(result));
  }

  ASSERT_EQ(expected, result);
}
