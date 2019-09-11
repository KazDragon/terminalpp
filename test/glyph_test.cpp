#include <terminalpp/glyph.hpp>
#include <gtest/gtest.h>
#include <unordered_set>

using testing::ValuesIn;

TEST(glyph_test, comparing_alike_unicode_glyphs_returns_true)
{
    ASSERT_EQ(terminalpp::glyph("\U00002501"), terminalpp::glyph("\U00002501"));
}

TEST(glyph_test, comparing_dissimmilar_unicode_glyphs_returns_false)
{
    ASSERT_NE(terminalpp::glyph("\U00002501"), terminalpp::glyph("\U00002502"));
}

using glyph_string = std::tuple<
    terminalpp::glyph,
    std::string
>;

class glyphs_with_strings
  : public testing::TestWithParam<glyph_string>
{
};

TEST_P(glyphs_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &glyph = std::get<0>(param);
    auto const &expected_string = std::get<1>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << glyph;
    ASSERT_EQ(expected_string, stream.str());
}

static glyph_string const glyph_strings[] = {
    glyph_string { 'c', "c" },
    glyph_string { 'Z', "Z" },
    glyph_string { ' ', " " },

    glyph_string { '\0',   "0x00" },
    glyph_string { '\7',   "0x07" },
    glyph_string { '\x1B', "0x1B" },

    glyph_string { '\n',   "\\n" },
    glyph_string { '\r',   "\\r" },
    glyph_string { '\t',   "\\t" },

    glyph_string { { '\xC1', terminalpp::ansi::charset::sco   }, "sco:\xC1" },
    glyph_string { { 'Z',    terminalpp::ansi::charset::uk    }, "en_uk:Z" },
    glyph_string { { '\x07', terminalpp::ansi::charset::dutch }, "nl:0x07" },

    glyph_string { terminalpp::glyph{"\U00000001"}, "u:0x01" },
    glyph_string { terminalpp::glyph{"\U00000007"}, "u:0x07" },
    glyph_string { terminalpp::glyph{"\U00000009"}, "u:\\t"  },
    glyph_string { terminalpp::glyph{"\U0000000A"}, "u:\\n"  },
    glyph_string { terminalpp::glyph{"\U0000000D"}, "u:\\r"  },
    glyph_string { terminalpp::glyph{"\U0000001B"}, "u:0x1B" },
    glyph_string { terminalpp::glyph{"\U0000005A"}, "u:Z"    },
    glyph_string { terminalpp::glyph{"\U00000061"}, "u:a"    },
    glyph_string { terminalpp::glyph{"\U0000007F"}, "u:0x7F" },
    glyph_string { terminalpp::glyph{"\U00000080"}, "U+0080" },
    glyph_string { terminalpp::glyph{"\U000007FF"}, "U+07FF" },
    glyph_string { terminalpp::glyph{"\U00000800"}, "U+0800" },
    glyph_string { terminalpp::glyph{"\U00002501"}, "U+2501" },
    glyph_string { terminalpp::glyph{"\U00001701"}, "U+1701" },

};

INSTANTIATE_TEST_CASE_P(
    glyphs_can_be_streamed_to_an_ostream,
    glyphs_with_strings,
    ValuesIn(glyph_strings)
);

TEST(a_glyph, can_be_inserted_into_an_unordered_set)
{
    std::unordered_set<terminalpp::glyph> g { 
        {},
        { terminalpp::glyph{"\U000007FF"} }
    };
}