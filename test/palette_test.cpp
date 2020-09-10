#include <terminalpp/palette.hpp>
#include <terminalpp/ansi_terminal.hpp>
#include <gtest/gtest.h>

using testing::ValuesIn;

using colour_attribute_data = std::tuple<
    terminalpp::attribute, // palette attribute
    std::string            // expected output for "x"
>;

namespace {

class colour_attribute_strings
  : public testing::TestWithParam<colour_attribute_data>
{
};

}

colour_attribute_data const colour_attributes[] = {
    colour_attribute_data{ terminalpp::palette::black,   "\x1B[30mx" },
    colour_attribute_data{ terminalpp::palette::maroon,  "\x1B[31mx" },
    colour_attribute_data{ terminalpp::palette::green,   "\x1B[32mx" },
    colour_attribute_data{ terminalpp::palette::olive,   "\x1B[33mx" },
    colour_attribute_data{ terminalpp::palette::navy,    "\x1B[34mx" },
    colour_attribute_data{ terminalpp::palette::purple,  "\x1B[35mx" },
    colour_attribute_data{ terminalpp::palette::teal,    "\x1B[36mx" },
    colour_attribute_data{ terminalpp::palette::silver,  "\x1B[37mx" },

    colour_attribute_data{ terminalpp::palette::grey,    "\x1B[1;30mx" },
    colour_attribute_data{ terminalpp::palette::red,     "\x1B[1;31mx" },
    colour_attribute_data{ terminalpp::palette::lime,    "\x1B[1;32mx" },
    colour_attribute_data{ terminalpp::palette::yellow,  "\x1B[1;33mx" },
    colour_attribute_data{ terminalpp::palette::blue,    "\x1B[1;34mx" },
    colour_attribute_data{ terminalpp::palette::fuchsia, "\x1B[1;35mx" },
    colour_attribute_data{ terminalpp::palette::aqua,    "\x1B[1;36mx" },
    colour_attribute_data{ terminalpp::palette::white,   "\x1B[1;37mx" },

    colour_attribute_data{ terminalpp::palette::grey0,    "\x1B[38;5;16mx"  },
    colour_attribute_data{ terminalpp::palette::grey3,    "\x1B[38;5;232mx" },
    colour_attribute_data{ terminalpp::palette::grey7,    "\x1B[38;5;233mx" },
    colour_attribute_data{ terminalpp::palette::grey11,   "\x1B[38;5;234mx" },
    colour_attribute_data{ terminalpp::palette::grey15,   "\x1B[38;5;235mx" },
    colour_attribute_data{ terminalpp::palette::grey19,   "\x1B[38;5;236mx" },
    colour_attribute_data{ terminalpp::palette::grey23,   "\x1B[38;5;237mx" },
    colour_attribute_data{ terminalpp::palette::grey27,   "\x1B[38;5;238mx" },
    colour_attribute_data{ terminalpp::palette::grey30,   "\x1B[38;5;239mx" },
    colour_attribute_data{ terminalpp::palette::grey35,   "\x1B[38;5;240mx" },
    colour_attribute_data{ terminalpp::palette::grey37,   "\x1B[38;5;59mx"  },
    colour_attribute_data{ terminalpp::palette::grey39,   "\x1B[38;5;241mx" },
    colour_attribute_data{ terminalpp::palette::grey42,   "\x1B[38;5;242mx" },
    colour_attribute_data{ terminalpp::palette::grey46,   "\x1B[38;5;243mx" },
    colour_attribute_data{ terminalpp::palette::grey50,   "\x1B[38;5;244mx" },
    colour_attribute_data{ terminalpp::palette::grey53,   "\x1B[38;5;102mx" },
    colour_attribute_data{ terminalpp::palette::grey54,   "\x1B[38;5;245mx" },
    colour_attribute_data{ terminalpp::palette::grey58,   "\x1B[38;5;246mx" },
    colour_attribute_data{ terminalpp::palette::grey62,   "\x1B[38;5;247mx" },
    colour_attribute_data{ terminalpp::palette::grey66,   "\x1B[38;5;248mx" },
    colour_attribute_data{ terminalpp::palette::grey69,   "\x1B[38;5;145mx" },
    colour_attribute_data{ terminalpp::palette::grey70,   "\x1B[38;5;249mx" },
    colour_attribute_data{ terminalpp::palette::grey74,   "\x1B[38;5;250mx" },
    colour_attribute_data{ terminalpp::palette::grey78,   "\x1B[38;5;251mx" },
    colour_attribute_data{ terminalpp::palette::grey82,   "\x1B[38;5;252mx" },
    colour_attribute_data{ terminalpp::palette::grey84,   "\x1B[38;5;188mx" },
    colour_attribute_data{ terminalpp::palette::grey85,   "\x1B[38;5;253mx" },
    colour_attribute_data{ terminalpp::palette::grey89,   "\x1B[38;5;254mx" },
    colour_attribute_data{ terminalpp::palette::grey93,   "\x1B[38;5;255mx" },
    colour_attribute_data{ terminalpp::palette::grey100,  "\x1B[38;5;231mx" },
};

TEST_P(colour_attribute_strings, output_the_correct_ansi_data)
{
    using std::get;

    auto const &param    = GetParam();
    auto const &attr     = get<0>(param);
    auto const &expected = get<1>(param);

    terminalpp::element const elem = {'x', attr};
    terminalpp::ansi_terminal terminal;

    // First write a space in the default attribute.  Thereafter, we write 
    // only what is not default about the palette-based element.
    terminal.write(' ');
    ASSERT_EQ(expected, terminal.write(elem));
}

INSTANTIATE_TEST_CASE_P(
    palette_colours_stream_to_terminals,
    colour_attribute_strings,
    ValuesIn(colour_attributes)
);
