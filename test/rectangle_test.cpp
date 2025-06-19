#include <gtest/gtest.h>
#include <terminalpp/rectangle.hpp>

using testing::ValuesIn;

namespace {

using rectangle_string = std::tuple<terminalpp::rectangle, std::string_view>;

class rectangles_with_strings : public testing::TestWithParam<rectangle_string>
{
};

TEST_P(rectangles_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &[rect, expected] = GetParam();

    std::stringstream stream;
    std::ostream &out = stream;

    out << rect;
    ASSERT_EQ(expected, stream.str());
}

INSTANTIATE_TEST_SUITE_P(
    rectangles_can_be_streamed_to_an_ostream,
    rectangles_with_strings,
    ValuesIn(std::initializer_list<rectangle_string>{
        // clang-format off
        { {{0, 0},   {0, 0}},    "rectangle(point(0,0), extent(0,0))"   },
        { {{76, 94}, {32, 41}},  "rectangle(point(76,94), extent(32,41))"   },
        { {{-4, 63}, {12, -92}}, "rectangle(point(-4,63), extent(12,-92))"   },
        // clang-format on
}));

}  // namespace
