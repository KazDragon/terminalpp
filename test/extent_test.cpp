#include <terminalpp/extent.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>

using testing::ValuesIn;

using extent_string = std::tuple<terminalpp::extent, std::string>;

class extents_with_strings
    : public testing::TestWithParam<extent_string>
{
};

TEST_P(extents_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &pt = std::get<0>(param);
    auto const &expected = std::get<1>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << pt;
    ASSERT_EQ(expected, stream.str());
}

INSTANTIATE_TEST_CASE_P(
    extents_can_be_streamed_to_an_ostream,
    extents_with_strings,
    ValuesIn(std::vector<extent_string>{
        extent_string{ {0, 0},           "extent(0,0)"   },
        extent_string{ {76, 94},         "extent(76,94)" },
        extent_string{ {-4, 63},         "extent(-4,63)" },
        extent_string{ {96583, 1231234}, "extent(96583,1231234)" }
    }));

