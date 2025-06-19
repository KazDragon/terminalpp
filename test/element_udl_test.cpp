#include <gtest/gtest.h>
#include <terminalpp/element.hpp>
#include <terminalpp/palette.hpp>

using namespace terminalpp::literals;  // NOLINT
using testing::ValuesIn;

namespace {

using udl_element = std::tuple<
    terminalpp::element,  // Input element as udl
    terminalpp::element   // Output element
    >;

class element_udl_test : public testing::TestWithParam<udl_element>
{
};

TEST_P(element_udl_test, parse_udl)
{
    using std::get;

    auto const &[udl_element, expected_element] = GetParam();

    ASSERT_EQ(expected_element, udl_element);
}

constexpr udl_element udl_elements[] = {
    // Empty string returns default element.
    {""_ete,                      {}                                                       },

    // Plain characters return those characters as elements.
    {"a"_ete,                     {'a'}                                                    },
    {"x"_ete,                     {'x'}                                                    },
    {"Z"_ete,                     {'Z'}                                                    },
    {"?"_ete,                     {'?'}                                                    },
    {"*"_ete,                     {'*'}                                                    },

    // Multiple plain characters return the first character.
    {"ab"_ete,                    {'a'}                                                    },
    {"zxcv"_ete,                  {'z'}                                                    },

    // A solo escape character returns a default element.
    {R"(\)"_ete,                  {}                                                       },

    // A double escape character returns a backslash.
    {R"(\\)"_ete,                 {'\\'}                                                   },

    // Extras after the slash are ignored.
    {R"(\\\)"_ete,                {'\\'}                                                   },
    {R"(\\\\)"_ete,               {'\\'}                                                   },

    // Unfinished character codes return a default character.
    {R"(\C)"_ete,                 {}                                                       },
    {R"(\C0)"_ete,                {}                                                       },
    {R"(\C09)"_ete,               {}                                                       },

    // A complete character code returns that character.
    {R"(\C097)"_ete,              {'a'}                                                    },

    // Extras after the code are ignored.
    {R"(\C098\)"_ete,             {'b'}                                                    },
    {R"(\C098\C)"_ete,            {'b'}                                                    },
    {R"(\C098\C0)"_ete,           {'b'}                                                    },
    {R"(\C098\C09)"_ete,          {'b'}                                                    },
    {R"(\C098\C098)"_ete,         {'b'}                                                    },

    // Charset codes
    {R"(\c0a)"_ete,               {{'a', terminalpp::charset::dec}}                        },
    {R"(\c4i)"_ete,               {{'i', terminalpp::charset::dutch}}                      },

    // Extended charset codes
    {R"(\c%6x)"_ete,              {{'x', terminalpp::charset::portuguese}}                 },
    {R"(\c%5j)"_ete,              {{'j', terminalpp::charset::dec_supplementary_graphics}} },

    // Extras after the code take precedence
    {R"(\c0\c%5d)"_ete,
     {{'d', terminalpp::charset::dec_supplementary_graphics}}                              },

    // Unknown character sets are ignored.
    {R"(\c%6\c?x)"_ete,           {{'x', terminalpp::charset::portuguese}}                 },
    {R"(\c%6\c%?y)"_ete,          {{'y', terminalpp::charset::portuguese}}                 },

    // Intensity
    {R"(\i>a)"_ete,
     {'a', {.intensity_ = terminalpp::graphics::intensity::bold}}                          },
    {R"(\i<a)"_ete,
     {'a', {.intensity_ = terminalpp::graphics::intensity::faint}}                         },
    {R"(\i=a)"_ete,
     {'a', {.intensity_ = terminalpp::graphics::intensity::normal}}                        },
    {R"(\ixa)"_ete,
     {'a', {.intensity_ = terminalpp::graphics::intensity::normal}}                        },

    // Extras after the intensity take precedence.
    {R"(\i>\i<a)"_ete,
     {'a', {.intensity_ = terminalpp::graphics::intensity::faint}}                         },
    {R"(\i>\ixa)"_ete,
     {'a', {.intensity_ = terminalpp::graphics::intensity::normal}}                        },
    {R"(\i>\i=a)"_ete,
     {'a', {.intensity_ = terminalpp::graphics::intensity::normal}}                        },

    // Polarity
    {R"(\p+a)"_ete,
     {'a', {.polarity_ = terminalpp::graphics::polarity::positive}}                        },
    {R"(\p-a)"_ete,
     {'a', {.polarity_ = terminalpp::graphics::polarity::negative}}                        },
    {R"(\pxa)"_ete,
     {'a', {.polarity_ = terminalpp::graphics::polarity::positive}}                        },

    // Extras after polarity take precedence.
    {R"(\p+\pxa)"_ete,
     {'a', {.polarity_ = terminalpp::graphics::polarity::positive}}                        },
    {R"(\p-\pxa)"_ete,
     {'a', {.polarity_ = terminalpp::graphics::polarity::positive}}                        },

    // Underlining
    {R"(\u+a)"_ete,
     {'a', {.underlining_ = terminalpp::graphics::underlining::underlined}}                },
    {R"(\u-a)"_ete,
     {'a',
      {.underlining_ = terminalpp::graphics::underlining::not_underlined}}                 },
    {R"(\uxa)"_ete,
     {'a',
      {.underlining_ = terminalpp::graphics::underlining::not_underlined}}                 },

    // Extras after underlining take precedence.
    {R"(\u+\uxa)"_ete,
     {'a',
      {.underlining_ = terminalpp::graphics::underlining::not_underlined}}                 },
    {R"(\u-\uxa)"_ete,
     {'a',
      {.underlining_ = terminalpp::graphics::underlining::not_underlined}}                 },

    // Low foreground colour.
    {R"(\[2a)"_ete,               {'a', {.foreground_colour_ = terminalpp::palette::green}}},
    {R"(\[3a)"_ete,               {'a', {.foreground_colour_ = terminalpp::palette::olive}}},

    // Extras after low foreground colour take precedence.
    {R"(\[2\[3a)"_ete,
     {'a', {.foreground_colour_ = terminalpp::palette::olive}}                             },
    {R"(\[3\[2a)"_ete,
     {'a', {.foreground_colour_ = terminalpp::palette::green}}                             },

    // High foreground colour.
    {R"(\<000a)"_ete,
     {'a', {.foreground_colour_ = terminalpp::high_colour{0, 0, 0}}}                       },
    {R"(\<850a)"_ete,
     {'a', {.foreground_colour_ = terminalpp::high_colour{8, 5, 0}}}                       },
    {R"(\<085a)"_ete,
     {'a', {.foreground_colour_ = terminalpp::high_colour{0, 8, 5}}}                       },

    // Extras after high foreground colour take precedence.
    {R"(\<850\<085a)"_ete,
     {'a', {.foreground_colour_ = terminalpp::high_colour{0, 8, 5}}}                       },
    {R"(\<085\<850a)"_ete,
     {'a', {.foreground_colour_ = terminalpp::high_colour{8, 5, 0}}}                       },

    // Greyscale foreground colour.
    {R"(\{00a)"_ete,
     {'a', {.foreground_colour_ = terminalpp::greyscale_colour{0}}}                        },
    {R"(\{17a)"_ete,
     {'a', {.foreground_colour_ = terminalpp::greyscale_colour{17}}}                       },
    {R"(\{22a)"_ete,
     {'a', {.foreground_colour_ = terminalpp::greyscale_colour{22}}}                       },

    // Extras after greyscale foreground colour take precedence.
    {R"(\{17\{22a)"_ete,
     {'a', {.foreground_colour_ = terminalpp::greyscale_colour{22}}}                       },
    {R"(\{22\{17a)"_ete,
     {'a', {.foreground_colour_ = terminalpp::greyscale_colour{17}}}                       },

    // True foreground colour.
    {R"(\(000000a)"_ete,
     {'a', {.foreground_colour_ = terminalpp::true_colour{0, 0, 0}}}                       },
    {R"(\(A917BEa)"_ete,
     {'a', {.foreground_colour_ = terminalpp::true_colour{0xA9, 0x17, 0xBE}}}              },

    // Extras after true foreground colour take precedence.
    {R"(\(A917BE\(B37EA2a)"_ete,
     {'a', {.foreground_colour_ = terminalpp::true_colour{0xB3, 0x7E, 0xA2}}}              },
    {R"(\(B37EA2\(A917BEa)"_ete,
     {'a', {.foreground_colour_ = terminalpp::true_colour{0xA9, 0x17, 0xBE}}}              },

    //
    // Low background colour.
    {R"(\]2a)"_ete,               {'a', {.background_colour_ = terminalpp::palette::green}}},
    {R"(\]3a)"_ete,               {'a', {.background_colour_ = terminalpp::palette::olive}}},

    // Extras after low background colour take precedence.
    {R"(\]2\]3a)"_ete,
     {'a', {.background_colour_ = terminalpp::palette::olive}}                             },
    {R"(\]3\]2a)"_ete,
     {'a', {.background_colour_ = terminalpp::palette::green}}                             },

    // High background colour.
    {R"(\>000a)"_ete,
     {'a', {.background_colour_ = terminalpp::high_colour{0, 0, 0}}}                       },
    {R"(\>850a)"_ete,
     {'a', {.background_colour_ = terminalpp::high_colour{8, 5, 0}}}                       },
    {R"(\>085a)"_ete,
     {'a', {.background_colour_ = terminalpp::high_colour{0, 8, 5}}}                       },

    // Extras after high background colour take precedence.
    {R"(\>850\>085a)"_ete,
     {'a', {.background_colour_ = terminalpp::high_colour{0, 8, 5}}}                       },
    {R"(\>085\>850a)"_ete,
     {'a', {.background_colour_ = terminalpp::high_colour{8, 5, 0}}}                       },

    // Greyscale background colour.
    {R"(\}00a)"_ete,
     {'a', {.background_colour_ = terminalpp::greyscale_colour{0}}}                        },
    {R"(\}17a)"_ete,
     {'a', {.background_colour_ = terminalpp::greyscale_colour{17}}}                       },
    {R"(\}22a)"_ete,
     {'a', {.background_colour_ = terminalpp::greyscale_colour{22}}}                       },

    // Extras after greyscale background colour take precedence.
    {R"(\}17\}22a)"_ete,
     {'a', {.background_colour_ = terminalpp::greyscale_colour{22}}}                       },
    {R"(\}22\}17a)"_ete,
     {'a', {.background_colour_ = terminalpp::greyscale_colour{17}}}                       },

    // True foreground colour.
    {R"(\)000000a)"_ete,
     {'a', {.background_colour_ = terminalpp::true_colour{0, 0, 0}}}                       },
    {R"(\)A917BEa)"_ete,
     {'a', {.background_colour_ = terminalpp::true_colour{0xA9, 0x17, 0xBE}}}              },

    // Extras after true background colour take precedence.
    {R"(\)A917BE\)B37EA2a)"_ete,
     {'a', {.background_colour_ = terminalpp::true_colour{0xB3, 0x7E, 0xA2}}}              },
    {R"(\)B37EA2\)A917BEa)"_ete,
     {'a', {.background_colour_ = terminalpp::true_colour{0xA9, 0x17, 0xBE}}}              },

    // Incomplete unicode character codes return a default character.
    {R"(\U)"_ete,                 {}                                                       },
    {R"(\U0)"_ete,                {}                                                       },
    {R"(\U01)"_ete,               {}                                                       },
    {R"(\U010)"_ete,              {}                                                       },

    // Complete unicode character code returns a unicode character.
    {R"(\U010E)"_ete,             {terminalpp::glyph{"\xC4\x8E"}}                          },
    {R"(\U0057)"_ete,             {terminalpp::glyph{R"(W)"}}                              },
    {R"(\U16B8)"_ete,             {terminalpp::glyph{"\xE1\x9A\xB8"}}                      },

    // Multiple characters after a unicode character are ignored.
    {R"(\U010Ex)"_ete,            {terminalpp::glyph{"\xC4\x8E"}}                          },
    {R"(\U010E\C097)"_ete,        {terminalpp::glyph{"\xC4\x8E"}}                          },
    {R"(\U010E\U16B8)"_ete,       {terminalpp::glyph{"\xC4\x8E"}}                          },

    // Default code removes all attributes
    {R"(\>201\{22\p-\u+\xa)"_ete, {'a'}                                                    },
};

INSTANTIATE_TEST_SUITE_P(
    elements_can_be_made_from_a_udl, element_udl_test, ValuesIn(udl_elements));

}  // namespace
