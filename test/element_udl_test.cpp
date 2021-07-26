#include <terminalpp/element.hpp>
#include <terminalpp/palette.hpp>
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

terminalpp::element with_polarity(terminalpp::element elem, terminalpp::graphics::polarity polarity)
{
    elem.attribute_.polarity_ = polarity;
    return elem;
}

terminalpp::element with_underlining(terminalpp::element elem, terminalpp::graphics::underlining underlining)
{
    elem.attribute_.underlining_ = underlining;
    return elem;
}

terminalpp::element with_foreground_colour(terminalpp::element elem, terminalpp::colour col)
{
    elem.attribute_.foreground_colour_ = col;
    return elem;
}

terminalpp::element with_background_colour(terminalpp::element elem, terminalpp::colour col)
{
    elem.attribute_.background_colour_ = col;
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

    // Polarity
    udl_element{"\\p+a"_ete, with_polarity({'a'}, terminalpp::graphics::polarity::positive)},
    udl_element{"\\p-a"_ete, with_polarity({'a'}, terminalpp::graphics::polarity::negative)},
    udl_element{"\\pxa"_ete, with_polarity({'a'}, terminalpp::graphics::polarity::positive)},

    // Extras after polarity take precedence.
    udl_element{"\\p+\\pxa"_ete, with_polarity({'a'}, terminalpp::graphics::polarity::positive)},
    udl_element{"\\p-\\pxa"_ete, with_polarity({'a'}, terminalpp::graphics::polarity::positive)},

    // Underlining
    udl_element{"\\u+a"_ete, with_underlining({'a'}, terminalpp::graphics::underlining::underlined)},
    udl_element{"\\u-a"_ete, with_underlining({'a'}, terminalpp::graphics::underlining::not_underlined)},
    udl_element{"\\uxa"_ete, with_underlining({'a'}, terminalpp::graphics::underlining::not_underlined)},

    // Extras after underlining take precedence.
    udl_element{"\\u+\\uxa"_ete, with_underlining({'a'}, terminalpp::graphics::underlining::not_underlined)},
    udl_element{"\\u-\\uxa"_ete, with_underlining({'a'}, terminalpp::graphics::underlining::not_underlined)},

    // Low foreground colour.
    udl_element{"\\[2a"_ete, with_foreground_colour({'a'}, terminalpp::palette::green)},
    udl_element{"\\[3a"_ete, with_foreground_colour({'a'}, terminalpp::palette::olive)},

    // Extras after low foreground colour take precedence.
    udl_element{"\\[2\\[3a"_ete, with_foreground_colour({'a'}, terminalpp::palette::olive)},
    udl_element{"\\[3\\[2a"_ete, with_foreground_colour({'a'}, terminalpp::palette::green)},

    // High foreground colour.
    udl_element{"\\<000a"_ete, with_foreground_colour({'a'}, terminalpp::high_colour{0, 0, 0})},
    udl_element{"\\<850a"_ete, with_foreground_colour({'a'}, terminalpp::high_colour{8, 5, 0})},
    udl_element{"\\<085a"_ete, with_foreground_colour({'a'}, terminalpp::high_colour{0, 8, 5})},

    // Extras after high foreground colour take precedence.
    udl_element{"\\<850\\<085a"_ete, with_foreground_colour({'a'}, terminalpp::high_colour{0, 8, 5})},
    udl_element{"\\<085\\<850a"_ete, with_foreground_colour({'a'}, terminalpp::high_colour{8, 5, 0})},

    // Greyscale foreground colour.
    udl_element{"\\{00a"_ete, with_foreground_colour({'a'}, terminalpp::greyscale_colour{0})},
    udl_element{"\\{17a"_ete, with_foreground_colour({'a'}, terminalpp::greyscale_colour{17})},
    udl_element{"\\{22a"_ete, with_foreground_colour({'a'}, terminalpp::greyscale_colour{22})},

    // Extras after greyscale foreground colour take precedence.
    udl_element{"\\{17\\{22a"_ete, with_foreground_colour({'a'}, terminalpp::greyscale_colour{22})},
    udl_element{"\\{22\\{17a"_ete, with_foreground_colour({'a'}, terminalpp::greyscale_colour{17})},
//
    // Low background colour.
    udl_element{"\\]2a"_ete, with_background_colour({'a'}, terminalpp::palette::green)},
    udl_element{"\\]3a"_ete, with_background_colour({'a'}, terminalpp::palette::olive)},

    // Extras after low background colour take precedence.
    udl_element{"\\]2\\]3a"_ete, with_background_colour({'a'}, terminalpp::palette::olive)},
    udl_element{"\\]3\\]2a"_ete, with_background_colour({'a'}, terminalpp::palette::green)},

    // High background colour.
    udl_element{"\\>000a"_ete, with_background_colour({'a'}, terminalpp::high_colour{0, 0, 0})},
    udl_element{"\\>850a"_ete, with_background_colour({'a'}, terminalpp::high_colour{8, 5, 0})},
    udl_element{"\\>085a"_ete, with_background_colour({'a'}, terminalpp::high_colour{0, 8, 5})},

    // Extras after high background colour take precedence.
    udl_element{"\\>850\\>085a"_ete, with_background_colour({'a'}, terminalpp::high_colour{0, 8, 5})},
    udl_element{"\\>085\\>850a"_ete, with_background_colour({'a'}, terminalpp::high_colour{8, 5, 0})},

    // Greyscale background colour.
    udl_element{"\\}00a"_ete, with_background_colour({'a'}, terminalpp::greyscale_colour{0})},
    udl_element{"\\}17a"_ete, with_background_colour({'a'}, terminalpp::greyscale_colour{17})},
    udl_element{"\\}22a"_ete, with_background_colour({'a'}, terminalpp::greyscale_colour{22})},

    // Extras after greyscale background colour take precedence.
    udl_element{"\\}17\\}22a"_ete, with_background_colour({'a'}, terminalpp::greyscale_colour{22})},
    udl_element{"\\}22\\}17a"_ete, with_background_colour({'a'}, terminalpp::greyscale_colour{17})},

    // Incomplete unicode character codes return a default character.
    udl_element{"\\U"_ete, terminalpp::element{}},
    udl_element{"\\U0"_ete, terminalpp::element{}},
    udl_element{"\\U01"_ete, terminalpp::element{}},
    udl_element{"\\U010"_ete, terminalpp::element{}},

    // Complete unicode character code returns a unicode character.
    udl_element{"\\U010E"_ete, terminalpp::element{terminalpp::glyph{"\xC4\x8E"}}},
    udl_element{"\\U0057"_ete, terminalpp::element{terminalpp::glyph{"\x57"}}},
    udl_element{"\\U16B8"_ete, terminalpp::element{terminalpp::glyph{"\xE1\x9A\xB8"}}},

    // Multiple characters after a unicode character are ignored.
    udl_element{"\\U010Ex"_ete, terminalpp::element{terminalpp::glyph{"\xC4\x8E"}}},
    udl_element{"\\U010E\\C097"_ete, terminalpp::element{terminalpp::glyph{"\xC4\x8E"}}},
    udl_element{"\\U010E\\U16B8"_ete, terminalpp::element{terminalpp::glyph{"\xC4\x8E"}}},

    // Default code removes all attributes
    udl_element{"\\>201\\{22\\p-\\u+\\xa"_ete, terminalpp::element{'a'}},
};

INSTANTIATE_TEST_SUITE_P(
    elements_can_be_made_from_a_udl,
    element_udl_test,
    ValuesIn(udl_elements)
);
