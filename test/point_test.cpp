#include <gtest/gtest.h>
#include <terminalpp/point.hpp>

#include <sstream>
#include <tuple>

using testing::ValuesIn;

namespace {

using point_string = std::tuple<terminalpp::point, std::string_view>;

class points_with_strings : public testing::TestWithParam<point_string>
{
};

TEST_P(points_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &[pt, expected] = GetParam();

    std::stringstream stream;
    std::ostream &out = stream;

    out << pt;
    ASSERT_EQ(expected, stream.str());
}

INSTANTIATE_TEST_SUITE_P(
    points_can_be_streamed_to_an_ostream,
    points_with_strings,
    ValuesIn(std::initializer_list<point_string>{
        {{0, 0},                                            "point(0,0)"          },
        {{76, 94},                                          "point(76,94)"        },
        {{-4, 63},                                          "point(-4,63)"        },
        {{96583, 1231234},                                  "point(96583,1231234)"},
        {terminalpp::point{1, 2} + terminalpp::point{4, 7}, "point(5,9)"          },
        {terminalpp::point{1, 2} - terminalpp::point{4, 7}, "point(-3,-5)"        },
}));

using point_relops_data = std::tuple<
    terminalpp::point,  // lhs
    terminalpp::point,  // rhs
    bool,               // less
    bool,               // less-equal
    bool,               // equal
    bool,               // greater-equal
    bool                // greater
    >;

class points_compare : public testing::TestWithParam<point_relops_data>
{
};

TEST_P(points_compare, according_to_relops)
{
    auto const &[lhs, rhs, less, less_equal, equal, greater_equal, greater] =
        GetParam();

    ASSERT_EQ(less, lhs < rhs);
    ASSERT_EQ(less_equal, lhs <= rhs);
    ASSERT_EQ(equal, lhs == rhs);
    ASSERT_EQ(!equal, lhs != rhs);
    ASSERT_EQ(greater_equal, lhs >= rhs);
    ASSERT_EQ(greater, lhs > rhs);
}

INSTANTIATE_TEST_SUITE_P(
    using_relational_operators,
    points_compare,
    ValuesIn(std::initializer_list<point_relops_data>{
        {{0, 0}, {1, 1}, true,  true,  false, false, false},
        {{1, 0}, {1, 1}, true,  true,  false, false, false},
        {{2, 0}, {1, 1}, true,  true,  false, false, false},
        {{0, 1}, {1, 1}, true,  true,  false, false, false},
        {{1, 1}, {1, 1}, false, true,  true,  true,  false},
        {{2, 1}, {1, 1}, false, false, false, true,  true },
        {{0, 2}, {1, 1}, false, false, false, true,  true },
        {{1, 2}, {1, 1}, false, false, false, true,  true },
        {{2, 2}, {1, 1}, false, false, false, true,  true }
}));

}  // namespace
