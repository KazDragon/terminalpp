#include <gtest/gtest.h>
#include <terminalpp/glyph.hpp>

#include <unordered_set>

using testing::ValuesIn;
using namespace terminalpp::literals;  // NOLINT

namespace {

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

using glyph_string = std::tuple<terminalpp::glyph, std::string_view>;

class glyphs_with_strings : public testing::TestWithParam<glyph_string>
{
};

TEST_P(glyphs_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &[glyph, expected_string] = GetParam();

    std::stringstream stream;
    std::ostream &out = stream;

    out << glyph;
    ASSERT_EQ(expected_string, stream.str());
}

constexpr glyph_string glyph_strings[] = {
    {'c'_tb,                                  "c"       },
    {'Z'_tb,                                  "Z"       },
    {' '_tb,                                  " "       },

    {'\0'_tb,                                 "0x00"    },
    {'\7'_tb,                                 "0x07"    },
    {'\x1B'_tb,                               "0x1B"    },

    {'\n'_tb,                                 "\\n"     },
    {'\r'_tb,                                 "\\r"     },
    {'\t'_tb,                                 "\\t"     },

    {{'\xC1'_tb, terminalpp::charset::sco},   "sco:\xC1"},
    {{'Z'_tb, terminalpp::charset::uk},       "en_uk:Z" },
    {{'\x07'_tb, terminalpp::charset::dutch}, "nl:0x07" },

    {terminalpp::glyph{u8"\U00000001"},       "u:0x01"  },
    {terminalpp::glyph{u8"\U00000007"},       "u:0x07"  },
    {terminalpp::glyph{u8"\U00000009"},       "u:\\t"   },
    {terminalpp::glyph{u8"\U0000000A"},       "u:\\n"   },
    {terminalpp::glyph{u8"\U0000000D"},       "u:\\r"   },
    {terminalpp::glyph{u8"\U0000001B"},       "u:0x1B"  },
    {terminalpp::glyph{u8"\U0000005A"},       "u:Z"     },
    {terminalpp::glyph{u8"\U00000061"},       "u:a"     },
    {terminalpp::glyph{u8"\U0000007F"},       "u:0x7F"  },
    {terminalpp::glyph{u8"\U00000080"},       "U+0080"  },
    {terminalpp::glyph{u8"\U000007FF"},       "U+07FF"  },
    {terminalpp::glyph{u8"\U00000800"},       "U+0800"  },
    {terminalpp::glyph{u8"\U00002501"},       "U+2501"  },
    {terminalpp::glyph{u8"\U00001701"},       "U+1701"  },
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

}  // namespace
