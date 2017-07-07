#include <terminalpp/glyph.hpp>
#include <gtest/gtest.h>

TEST(glyph_test, comparing_alike_unicode_glyphs_returns_true)
{
    ASSERT_EQ(terminalpp::glyph("\U00002501"), terminalpp::glyph("\U00002501"));
}

TEST(glyph_test, comparing_dissimmilar_unicode_glyphs_returns_false)
{
    ASSERT_NE(terminalpp::glyph("\U00002501"), terminalpp::glyph("\U00002502"));
}

