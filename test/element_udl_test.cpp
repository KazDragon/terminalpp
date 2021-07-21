#include <terminalpp/element.hpp>
#include <gtest/gtest.h>

TEST(a, b)
{
    using namespace terminalpp::literals;
    constexpr terminalpp::element expected_element = {};
    constexpr terminalpp::element elem = ""_elem;

    ASSERT_EQ(expected_element, elem);
}
