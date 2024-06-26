#include <gtest/gtest.h>
#include <terminalpp/glyph.hpp>

#include <unordered_set>

using testing::ValuesIn;
using namespace terminalpp::literals;  // NOLINT

TEST(glyph_test, comparing_alike_unicode_glyphs_returns_true)
{
    ASSERT_EQ(
        terminalpp::glyph(u8"\U00002501"), terminalpp::glyph(u8"\U00002501"));
}

TEST(glyph_test, comparing_dissimilar_unicode_glyphs_returns_false)
{
    ASSERT_NE(
        terminalpp::glyph(u8"\U00002501"), terminalpp::glyph(u8"\U00002502"));
}

using glyph_string = std::tuple<terminalpp::glyph, std::string>;

class glyphs_with_strings : public testing::TestWithParam<glyph_string>
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
  // clang-format off
    glyph_string { 'c'_tb, "c" },
    glyph_string { 'Z'_tb, "Z" },
    glyph_string { ' '_tb, " " },

    glyph_string { '\0'_tb,   "0x00" },
    glyph_string { '\7'_tb,   "0x07" },
    glyph_string { '\x1B'_tb, "0x1B" },

    glyph_string { '\n'_tb,   "\\n" },
    glyph_string { '\r'_tb,   "\\r" },
    glyph_string { '\t'_tb,   "\\t" },

    glyph_string { { '\xC1'_tb, terminalpp::charset::sco   }, "sco:\xC1" },
    glyph_string { { 'Z'_tb,    terminalpp::charset::uk    }, "en_uk:Z" },
    glyph_string { { '\x07'_tb, terminalpp::charset::dutch }, "nl:0x07" },

    glyph_string { terminalpp::glyph{u8"\U00000001"}, "u:0x01" },
    glyph_string { terminalpp::glyph{u8"\U00000007"}, "u:0x07" },
    glyph_string { terminalpp::glyph{u8"\U00000009"}, "u:\\t"  },
    glyph_string { terminalpp::glyph{u8"\U0000000A"}, "u:\\n"  },
    glyph_string { terminalpp::glyph{u8"\U0000000D"}, "u:\\r"  },
    glyph_string { terminalpp::glyph{u8"\U0000001B"}, "u:0x1B" },
    glyph_string { terminalpp::glyph{u8"\U0000005A"}, "u:Z"    },
    glyph_string { terminalpp::glyph{u8"\U00000061"}, "u:a"    },
    glyph_string { terminalpp::glyph{u8"\U0000007F"}, "u:0x7F" },
    glyph_string { terminalpp::glyph{u8"\U00000080"}, "U+0080" },
    glyph_string { terminalpp::glyph{u8"\U000007FF"}, "U+07FF" },
    glyph_string { terminalpp::glyph{u8"\U00000800"}, "U+0800" },
    glyph_string { terminalpp::glyph{u8"\U00002501"}, "U+2501" },
    glyph_string { terminalpp::glyph{u8"\U00001701"}, "U+1701" },
  // clang-format on
};

INSTANTIATE_TEST_SUITE_P(
    glyphs_can_be_streamed_to_an_ostream,
    glyphs_with_strings,
    ValuesIn(glyph_strings));

TEST(a_glyph, can_be_inserted_into_an_unordered_set)
{
    std::unordered_set<terminalpp::glyph> g{
        {}, {terminalpp::glyph{u8"\U000007FF"}}};
}