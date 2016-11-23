#include <terminalpp/extent.hpp>
#include <gtest/gtest.h>
#include <sstream>

TEST(extents, can_be_streamed)
{
    static std::string const expected = "extent[7, 32]";

    std::stringstream stream;
    stream << terminalpp::extent(7, 32);

    ASSERT_EQ(expected, stream.str());
}