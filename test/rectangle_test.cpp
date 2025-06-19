#include <gtest/gtest.h>
#include <terminalpp/rectangle.hpp>

using testing::ValuesIn;

namespace {

using rectangle_string = std::tuple<terminalpp::rectangle, std::string>;

class rectangles_with_strings : public testing::TestWithParam<rectangle_string>
{
};

TEST_P(rectangles_with_strings, can_be_streamed_to_an_ostream)
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
    rectangles_can_be_streamed_to_an_ostream,
    rectangles_with_strings,
    ValuesIn(std::vector<rectangle_string>{
        // clang-format off
        rectangle_string{ {{0, 0},   {0, 0}},    "rectangle(point(0,0), extent(0,0))"   },
        rectangle_string{ {{76, 94}, {32, 41}},  "rectangle(point(76,94), extent(32,41))"   },
        rectangle_string{ {{-4, 63}, {12, -92}}, "rectangle(point(-4,63), extent(12,-92))"   },
        // clang-format on
}));

}  // namespace
