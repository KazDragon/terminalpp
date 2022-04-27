#include "expect_sequence.hpp"
#include <terminalpp/palette.hpp>
#include <terminalpp/terminal.hpp>
#include <gtest/gtest.h>

using namespace terminalpp::literals;
using testing::ValuesIn;

using colour_attribute_data = std::tuple<
    terminalpp::attribute,   // palette attribute
    terminalpp::byte_storage // expected output for "x"
>;

namespace {

class colour_attribute_strings
  : public testing::TestWithParam<colour_attribute_data>
{
};

}

colour_attribute_data const colour_attributes[] = {
    colour_attribute_data{ terminalpp::palette::black,   "\x1B[30mx"_tb },
    colour_attribute_data{ terminalpp::palette::maroon,  "\x1B[31mx"_tb },
    colour_attribute_data{ terminalpp::palette::green,   "\x1B[32mx"_tb },
    colour_attribute_data{ terminalpp::palette::olive,   "\x1B[33mx"_tb },
    colour_attribute_data{ terminalpp::palette::navy,    "\x1B[34mx"_tb },
    colour_attribute_data{ terminalpp::palette::purple,  "\x1B[35mx"_tb },
    colour_attribute_data{ terminalpp::palette::teal,    "\x1B[36mx"_tb },
    colour_attribute_data{ terminalpp::palette::silver,  "\x1B[37mx"_tb },

    colour_attribute_data{ { {}, terminalpp::palette::black },   "\x1B[40mx"_tb },
    colour_attribute_data{ { {}, terminalpp::palette::maroon },  "\x1B[41mx"_tb },
    colour_attribute_data{ { {}, terminalpp::palette::green },   "\x1B[42mx"_tb },
    colour_attribute_data{ { {}, terminalpp::palette::olive },   "\x1B[43mx"_tb },
    colour_attribute_data{ { {}, terminalpp::palette::navy },    "\x1B[44mx"_tb },
    colour_attribute_data{ { {}, terminalpp::palette::purple },  "\x1B[45mx"_tb },
    colour_attribute_data{ { {}, terminalpp::palette::teal },    "\x1B[46mx"_tb },
    colour_attribute_data{ { {}, terminalpp::palette::silver },  "\x1B[47mx"_tb },

    colour_attribute_data{ terminalpp::palette::fg_grey,    "\x1B[1;30mx"_tb },
    colour_attribute_data{ terminalpp::palette::fg_red,     "\x1B[1;31mx"_tb },
    colour_attribute_data{ terminalpp::palette::fg_lime,    "\x1B[1;32mx"_tb },
    colour_attribute_data{ terminalpp::palette::fg_yellow,  "\x1B[1;33mx"_tb },
    colour_attribute_data{ terminalpp::palette::fg_blue,    "\x1B[1;34mx"_tb },
    colour_attribute_data{ terminalpp::palette::fg_fuchsia, "\x1B[1;35mx"_tb },
    colour_attribute_data{ terminalpp::palette::fg_aqua,    "\x1B[1;36mx"_tb },
    colour_attribute_data{ terminalpp::palette::fg_white,   "\x1B[1;37mx"_tb },

    colour_attribute_data{ terminalpp::palette::bg_grey,    "\x1B[1;40mx"_tb },
    colour_attribute_data{ terminalpp::palette::bg_red,     "\x1B[1;41mx"_tb },
    colour_attribute_data{ terminalpp::palette::bg_lime,    "\x1B[1;42mx"_tb },
    colour_attribute_data{ terminalpp::palette::bg_yellow,  "\x1B[1;43mx"_tb },
    colour_attribute_data{ terminalpp::palette::bg_blue,    "\x1B[1;44mx"_tb },
    colour_attribute_data{ terminalpp::palette::bg_fuchsia, "\x1B[1;45mx"_tb },
    colour_attribute_data{ terminalpp::palette::bg_aqua,    "\x1B[1;46mx"_tb },
    colour_attribute_data{ terminalpp::palette::bg_white,   "\x1B[1;47mx"_tb },

    colour_attribute_data{ terminalpp::palette::grey0,    "\x1B[38;5;16mx"_tb  },
    colour_attribute_data{ terminalpp::palette::grey3,    "\x1B[38;5;232mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey7,    "\x1B[38;5;233mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey11,   "\x1B[38;5;234mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey15,   "\x1B[38;5;235mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey19,   "\x1B[38;5;236mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey23,   "\x1B[38;5;237mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey27,   "\x1B[38;5;238mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey30,   "\x1B[38;5;239mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey35,   "\x1B[38;5;240mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey37,   "\x1B[38;5;59mx"_tb  },
    colour_attribute_data{ terminalpp::palette::grey39,   "\x1B[38;5;241mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey42,   "\x1B[38;5;242mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey46,   "\x1B[38;5;243mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey50,   "\x1B[38;5;244mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey53,   "\x1B[38;5;102mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey54,   "\x1B[38;5;245mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey58,   "\x1B[38;5;246mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey62,   "\x1B[38;5;247mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey66,   "\x1B[38;5;248mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey69,   "\x1B[38;5;145mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey70,   "\x1B[38;5;249mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey74,   "\x1B[38;5;250mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey78,   "\x1B[38;5;251mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey82,   "\x1B[38;5;252mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey84,   "\x1B[38;5;188mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey85,   "\x1B[38;5;253mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey89,   "\x1B[38;5;254mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey93,   "\x1B[38;5;255mx"_tb },
    colour_attribute_data{ terminalpp::palette::grey100,  "\x1B[38;5;231mx"_tb },
};

TEST_P(colour_attribute_strings, output_the_correct_ansi_data)
{
    using std::get;

    auto const &param    = GetParam();
    auto const &attr     = get<0>(param);
    auto const &expected = get<1>(param);

    terminalpp::element const elem = {'x', attr};

    terminalpp::byte_storage result;
    terminalpp::terminal terminal{
        [](terminalpp::tokens) {
            FAIL();
        },
        [&result](terminalpp::bytes data)
        {
            result.append(std::cbegin(data), std::cend(data));
        }};

    // First write a space in the default attribute.  Thereafter, we write 
    // only what is not default about the palette-based element.
    terminal << ""_ets;
    result.clear();

    terminal << elem;
    expect_sequence(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    palette_colours_stream_to_terminals,
    colour_attribute_strings,
    ValuesIn(colour_attributes)
);
