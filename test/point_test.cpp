#include <terminalpp/point.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <sstream>

using testing::ValuesIn;

using point_string = std::tuple<terminalpp::point, std::string>;

class points_with_strings
    : public testing::TestWithParam<point_string>
{
};

TEST_P(points_with_strings, can_be_streamed_to_an_ostream)
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
    points_can_be_streamed_to_an_ostream,
    points_with_strings,
    ValuesIn(std::vector<point_string>{
        point_string{ {0, 0},           "point(0,0)"   },
        point_string{ {76, 94},         "point(76,94)" },
        point_string{ {-4, 63},         "point(-4,63)" },
        point_string{ {96583, 1231234}, "point(96583,1231234)" }
    }));
