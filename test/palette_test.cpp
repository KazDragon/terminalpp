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
