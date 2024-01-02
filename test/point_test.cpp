#include <gtest/gtest.h>
#include <terminalpp/point.hpp>
#include <sstream>
#include <tuple>

using testing::ValuesIn;

using point_string = std::tuple<terminalpp::point, std::string>;

class points_with_strings : public testing::TestWithParam<point_string>
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

INSTANTIATE_TEST_SUITE_P(
    points_can_be_streamed_to_an_ostream,
    points_with_strings,
    ValuesIn(std::vector<point_string>{
        // clang-format off
        point_string{ {0, 0},           "point(0,0)"   },
        point_string{ {76, 94},         "point(76,94)" },
        point_string{ {-4, 63},         "point(-4,63)" },
        point_string{ {96583, 1231234}, "point(96583,1231234)" }
        // clang-format on
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
  auto const &param = GetParam();
  auto const &lhs = std::get<0>(param);
  auto const &rhs = std::get<1>(param);
  auto const &less = std::get<2>(param);
  auto const &less_equal = std::get<3>(param);
  auto const &equal = std::get<4>(param);
  auto const &greater_equal = std::get<5>(param);
  auto const &greater = std::get<6>(param);

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
    ValuesIn(std::vector<point_relops_data>{
        // clang-format off
        point_relops_data{{0, 0}, {1, 1}, true,  true,  false, false, false },
        point_relops_data{{1, 0}, {1, 1}, true,  true,  false, false, false },
        point_relops_data{{2, 0}, {1, 1}, true,  true,  false, false, false },
        point_relops_data{{0, 1}, {1, 1}, true,  true,  false, false, false },
        point_relops_data{{1, 1}, {1, 1}, false, true,  true,  true,  false },
        point_relops_data{{2, 1}, {1, 1}, false, false, false, true,  true  },
        point_relops_data{{0, 2}, {1, 1}, false, false, false, true,  true  },
        point_relops_data{{1, 2}, {1, 1}, false, false, false, true,  true  },
        point_relops_data{{2, 2}, {1, 1}, false, false, false, true,  true  }
        // clang-format on
    }));
