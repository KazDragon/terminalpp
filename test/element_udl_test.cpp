#include <terminalpp/element.hpp>
#include <gtest/gtest.h>
#include <utility>

using namespace terminalpp::literals;
using testing::ValuesIn;

using udl_element = std::tuple<
    terminalpp::element, // Input element as udl
    terminalpp::element  // Output element
>;

class element_udl_test
  : public testing::TestWithParam<udl_element>
{
};

TEST_P(element_udl_test, parse_udl)
{
    using std::get;

    auto const &param = GetParam();
    auto const &udl_element = get<0>(param);
    auto const &expected_element = get<1>(param);

    ASSERT_EQ(expected_element, udl_element);
}

namespace {
terminalpp::element with_charset(terminalpp::element elem, terminalpp::charset charset)
{
    elem.glyph_.charset_ = charset;
    return elem;
}

terminalpp::element with_intensity(terminalpp::element elem, terminalpp::graphics::intensity intensity)
{
    elem.attribute_.intensity_ = intensity;
    return elem;
}

}

static udl_element const udl_elements[] = {
    // Empty string returns default element.
    udl_element{""_ete, terminalpp::element{}},

    // Plain characters return those characters as elements.
    udl_element{"a"_ete, terminalpp::element{'a'}},
    udl_element{"x"_ete, terminalpp::element{'x'}},
    udl_element{"Z"_ete, terminalpp::element{'Z'}},
    udl_element{"?"_ete, terminalpp::element{'?'}},
    udl_element{"*"_ete, terminalpp::element{'*'}},

    // Multiple plain characters return the first character.
    udl_element{"ab"_ete, terminalpp::element{'a'}},
    udl_element{"zxcv"_ete, terminalpp::element{'z'}},

    // A solo escape character returns a default element.
    udl_element{"\\"_ete, terminalpp::element{}},

    // A double escape character returns a backslash.
    udl_element{"\\\\"_ete, terminalpp::element{'\\'}},

    // Extras after the slash are ignored.
    udl_element{"\\\\\\"_ete, terminalpp::element{'\\'}},
    udl_element{"\\\\\\\\"_ete, terminalpp::element{'\\'}},

    // Unfinished character codes return a default character.
    udl_element{"\\C"_ete, terminalpp::element{}},
    udl_element{"\\C0"_ete, terminalpp::element{}},
    udl_element{"\\C09"_ete, terminalpp::element{}},

    // A complete character code returns that character.
    udl_element{"\\C097"_ete, terminalpp::element{'a'}},

    // Extras after the code are ignored.
    udl_element("\\C098\\"_ete, terminalpp::element{'b'}),
    udl_element("\\C098\\C"_ete, terminalpp::element{'b'}),
    udl_element("\\C098\\C0"_ete, terminalpp::element{'b'}),
    udl_element("\\C098\\C09"_ete, terminalpp::element{'b'}),
    udl_element("\\C098\\C098"_ete, terminalpp::element{'b'}),

    // Charset codes
    udl_element{"\\c0a"_ete, with_charset({'a'}, terminalpp::charset::dec)},
    udl_element{"\\c4i"_ete, with_charset({'i'}, terminalpp::charset::dutch)},

    // Extended charset codes
    udl_element{"\\c%6x"_ete, with_charset({'x'}, terminalpp::charset::portuguese)},
    udl_element{"\\c%5j"_ete, with_charset({'j'}, terminalpp::charset::dec_supplementary_graphics)},

    // Extras after the code take precedence
    udl_element{"\\c0\\c%5d"_ete, with_charset({'d'}, terminalpp::charset::dec_supplementary_graphics)},

    // Intensity
    udl_element{"\\i>a"_ete, with_intensity({'a'}, terminalpp::graphics::intensity::bold)},
    udl_element{"\\i<a"_ete, with_intensity({'a'}, terminalpp::graphics::intensity::faint)},
    udl_element{"\\i=a"_ete, with_intensity({'a'}, terminalpp::graphics::intensity::normal)},
    udl_element{"\\ixa"_ete, with_intensity({'a'}, terminalpp::graphics::intensity::normal)},

    // Extras after the intensity take precedence.
    udl_element{"\\i>\\i<a"_ete, with_intensity({'a'}, terminalpp::graphics::intensity::faint)},
    udl_element{"\\i>\\ixa"_ete, with_intensity({'a'}, terminalpp::graphics::intensity::normal)},
    udl_element{"\\i>\\i=a"_ete, with_intensity({'a'}, terminalpp::graphics::intensity::normal)},
};

INSTANTIATE_TEST_SUITE_P(
    elements_can_be_made_from_a_udl,
    element_udl_test,
    ValuesIn(udl_elements)
);
