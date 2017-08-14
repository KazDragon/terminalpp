#include "terminalpp/element.hpp"
#include <gtest/gtest.h>

using testing::ValuesIn;

TEST(element_test, elements_are_small)
{
    ASSERT_EQ(12, sizeof(terminalpp::element));
}

TEST(element_test, can_implicitly_construct_element_from_glyph)
{
    auto elem = [](terminalpp::element const &elem)
    {
        return elem;
    }(terminalpp::glyph('x'));

    ASSERT_EQ('x', elem.glyph_.character_);
}

TEST(element_test, can_implicitly_construct_element_from_char)
{
    auto elem = [](terminalpp::element const &elem)
    {
        return elem;
    }('x');

    ASSERT_EQ('x', elem.glyph_.character_);
}

TEST(element_test, can_aggregate_initialize_from_glyph)
{
    auto elem = [](terminalpp::element const &elem)
    {
        return elem;
    }({terminalpp::glyph('x')});

    ASSERT_EQ('x', elem.glyph_.character_);
}

TEST(element_test, can_aggregate_initialize_from_char)
{
    auto elem = [](terminalpp::element const &elem)
    {
        return elem;
    }({'x'});

    ASSERT_EQ('x', elem.glyph_.character_);
}

using element_string = std::tuple<
    terminalpp::element,
    std::string
>;

class elements_with_strings
  : public testing::TestWithParam<element_string>
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

static element_string const element_strings[] = {
    element_string{ terminalpp::element{}, "glyph[ ]" },
    element_string{ terminalpp::glyph{"\\U0000005A"}, "glyph[u:\\]" },
    element_string{ {
            'x',
            terminalpp::attribute{terminalpp::ansi::graphics::colour::red}
        },
        "glyph[x],attribute[foreground[red]]"
    }
};

INSTANTIATE_TEST_CASE_P(
    elements_can_be_streamed_to_an_ostream,
    elements_with_strings,
    ValuesIn(element_strings)
);
