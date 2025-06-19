#include "fakes/fake_channel.hpp"

#include <gmock/gmock.h>
#include <terminalpp/palette.hpp>
#include <terminalpp/terminal.hpp>

using namespace terminalpp::literals;  // NOLINT
using testing::ContainerEq;
using testing::ValuesIn;

namespace {

using colour_attribute_data = std::tuple<
    terminalpp::attribute,    // palette attribute
    terminalpp::byte_storage  // expected output for "x"
    >;

class colour_attribute_strings
  : public testing::TestWithParam<colour_attribute_data>
{
};

constexpr colour_attribute_data colour_attributes[] = {
    {{.foreground_colour_ = terminalpp::palette::black},   "\x1B[30mx"_tb      },
    {{.foreground_colour_ = terminalpp::palette::maroon},  "\x1B[31mx"_tb      },
    {{.foreground_colour_ = terminalpp::palette::green},   "\x1B[32mx"_tb      },
    {{.foreground_colour_ = terminalpp::palette::olive},   "\x1B[33mx"_tb      },
    {{.foreground_colour_ = terminalpp::palette::navy},    "\x1B[34mx"_tb      },
    {{.foreground_colour_ = terminalpp::palette::purple},  "\x1B[35mx"_tb      },
    {{.foreground_colour_ = terminalpp::palette::teal},    "\x1B[36mx"_tb      },
    {{.foreground_colour_ = terminalpp::palette::silver},  "\x1B[37mx"_tb      },

    {{.background_colour_ = terminalpp::palette::black},   "\x1B[40mx"_tb      },
    {{.background_colour_ = terminalpp::palette::maroon},  "\x1B[41mx"_tb      },
    {{.background_colour_ = terminalpp::palette::green},   "\x1B[42mx"_tb      },
    {{.background_colour_ = terminalpp::palette::olive},   "\x1B[43mx"_tb      },
    {{.background_colour_ = terminalpp::palette::navy},    "\x1B[44mx"_tb      },
    {{.background_colour_ = terminalpp::palette::purple},  "\x1B[45mx"_tb      },
    {{.background_colour_ = terminalpp::palette::teal},    "\x1B[46mx"_tb      },
    {{.background_colour_ = terminalpp::palette::silver},  "\x1B[47mx"_tb      },

    {terminalpp::palette::fg_grey,                         "\x1B[1;30mx"_tb    },
    {terminalpp::palette::fg_red,                          "\x1B[1;31mx"_tb    },
    {terminalpp::palette::fg_lime,                         "\x1B[1;32mx"_tb    },
    {terminalpp::palette::fg_yellow,                       "\x1B[1;33mx"_tb    },
    {terminalpp::palette::fg_blue,                         "\x1B[1;34mx"_tb    },
    {terminalpp::palette::fg_fuchsia,                      "\x1B[1;35mx"_tb    },
    {terminalpp::palette::fg_aqua,                         "\x1B[1;36mx"_tb    },
    {terminalpp::palette::fg_white,                        "\x1B[1;37mx"_tb    },

    {terminalpp::palette::bg_grey,                         "\x1B[1;40mx"_tb    },
    {terminalpp::palette::bg_red,                          "\x1B[1;41mx"_tb    },
    {terminalpp::palette::bg_lime,                         "\x1B[1;42mx"_tb    },
    {terminalpp::palette::bg_yellow,                       "\x1B[1;43mx"_tb    },
    {terminalpp::palette::bg_blue,                         "\x1B[1;44mx"_tb    },
    {terminalpp::palette::bg_fuchsia,                      "\x1B[1;45mx"_tb    },
    {terminalpp::palette::bg_aqua,                         "\x1B[1;46mx"_tb    },
    {terminalpp::palette::bg_white,                        "\x1B[1;47mx"_tb    },

    {{.foreground_colour_ = terminalpp::palette::grey0},   "\x1B[38;5;16mx"_tb },
    {{.foreground_colour_ = terminalpp::palette::grey3},   "\x1B[38;5;232mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey7},   "\x1B[38;5;233mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey11},  "\x1B[38;5;234mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey15},  "\x1B[38;5;235mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey19},  "\x1B[38;5;236mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey23},  "\x1B[38;5;237mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey27},  "\x1B[38;5;238mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey30},  "\x1B[38;5;239mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey35},  "\x1B[38;5;240mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey37},  "\x1B[38;5;59mx"_tb },
    {{.foreground_colour_ = terminalpp::palette::grey39},  "\x1B[38;5;241mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey42},  "\x1B[38;5;242mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey46},  "\x1B[38;5;243mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey50},  "\x1B[38;5;244mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey53},  "\x1B[38;5;102mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey54},  "\x1B[38;5;245mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey58},  "\x1B[38;5;246mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey62},  "\x1B[38;5;247mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey66},  "\x1B[38;5;248mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey69},  "\x1B[38;5;145mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey70},  "\x1B[38;5;249mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey74},  "\x1B[38;5;250mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey78},  "\x1B[38;5;251mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey82},  "\x1B[38;5;252mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey84},  "\x1B[38;5;188mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey85},  "\x1B[38;5;253mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey89},  "\x1B[38;5;254mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey93},  "\x1B[38;5;255mx"_tb},
    {{.foreground_colour_ = terminalpp::palette::grey100},
     "\x1B[38;5;231mx"_tb                                                      },
};

TEST_P(colour_attribute_strings, output_the_correct_ansi_data)
{
    using std::get;

    auto const &[attr, expected] = GetParam();

    terminalpp::element const elem = {'x', attr};

    fake_channel channel;
    terminalpp::terminal terminal{channel};

    // First write a space in the default attribute.  Thereafter, we write
    // only what is not default about the palette-based element.
    terminal << ""_ets;
    channel.written_.clear();

    terminal << elem;
    EXPECT_THAT(channel.written_, ContainerEq(expected));
}

INSTANTIATE_TEST_SUITE_P(
    palette_colours_stream_to_terminals,
    colour_attribute_strings,
    ValuesIn(colour_attributes));

}  // namespace
