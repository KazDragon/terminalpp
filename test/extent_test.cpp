#include <gtest/gtest.h>
#include <terminalpp/extent.hpp>

#include <initializer_list>
#include <sstream>
#include <tuple>

using testing::ValuesIn;

namespace {

using extent_string = std::tuple<terminalpp::extent, std::string_view>;

class extents_with_strings : public testing::TestWithParam<extent_string>
{
};

TEST_P(extents_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &[ext, expected] = GetParam();

    std::stringstream stream;
    std::ostream &out = stream;

    out << ext;
    ASSERT_EQ(expected, stream.str());
}

INSTANTIATE_TEST_SUITE_P(
    extents_can_be_streamed_to_an_ostream,
    extents_with_strings,
    ValuesIn(std::initializer_list<extent_string>{
        // clang-format off
        extent_string{ {0, 0},           "extent(0,0)"   },
        extent_string{ {76, 94},         "extent(76,94)" },
        extent_string{ {-4, 63},         "extent(-4,63)" },
        extent_string{ {96583, 1231234}, "extent(96583,1231234)" },
        extent_string{ terminalpp::extent{0, 1} + terminalpp::extent{2, 4}, "extent(2,5)"},
        extent_string{ terminalpp::extent{0, 1} - terminalpp::extent{2, 4}, "extent(-2,-3)"},
        // clang-format on
}));

}  // namespace
