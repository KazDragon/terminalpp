#include "terminalpp/element.hpp"

#include <gtest/gtest.h>

#include <unordered_set>

using testing::ValuesIn;

namespace {

TEST(element_test, elements_are_small)
{
    ASSERT_EQ(16, sizeof(terminalpp::element));
}

TEST(element_test, can_implicitly_construct_element_from_glyph)
{
    auto elem = [](terminalpp::element const &elem) {
        return elem;
    }(terminalpp::glyph('x'));

    ASSERT_EQ('x', elem.glyph_.character_);
}

TEST(element_test, can_implicitly_construct_element_from_char)
{
    auto elem = [](terminalpp::element const &elem) { return elem; }('x');

    ASSERT_EQ('x', elem.glyph_.character_);
}

TEST(element_test, can_aggregate_initialize_from_glyph)
{
    auto elem = [](terminalpp::element const &elem) {
        return elem;
    }({terminalpp::glyph('x')});

    ASSERT_EQ('x', elem.glyph_.character_);
}

TEST(element_test, can_aggregate_initialize_from_char)
{
    auto elem = [](terminalpp::element const &elem) { return elem; }({'x'});

    ASSERT_EQ('x', elem.glyph_.character_);
}

using element_string = std::tuple<terminalpp::element, std::string_view>;

class elements_with_strings : public testing::TestWithParam<element_string>
{
};

TEST_P(elements_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &element = std::get<0>(param);
    auto const &expected_string = std::get<1>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << element;
    ASSERT_EQ(expected_string, stream.str());
}

constexpr element_string element_strings[] = {
    {terminalpp::element{},                                               "glyph[ ]"   },
    {terminalpp::glyph{"\\U0000005A"},                                    "glyph[u:\\]"},
    {{'x',
      terminalpp::attribute{
          .foreground_colour_ = terminalpp::graphics::colour::red}},
     "glyph[x],attribute[foreground[red]]"                                             }
};

INSTANTIATE_TEST_SUITE_P(
    elements_can_be_streamed_to_an_ostream,
    elements_with_strings,
    ValuesIn(element_strings));

TEST(an_element, can_be_inserted_into_an_unordered_set)
{
    std::unordered_set<terminalpp::element> e{{}};
}

}  // namespace
