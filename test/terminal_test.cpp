#include "terminal_test.hpp"

#include <gmock/gmock.h>
#include <tuple>

namespace {

using namespace terminalpp::literals;  // NOLINT
using testing::ContainerEq;
using testing::ValuesIn;

TEST_F(a_terminal, is_alive_if_its_underlying_channel_is_alive)
{
    ASSERT_TRUE(terminal_.is_alive());

    channel_.close();
    ASSERT_FALSE(terminal_.is_alive());
}

TEST_F(a_terminal, closes_its_underlying_channel_if_it_is_closed)
{
    ASSERT_TRUE(channel_.is_alive());
    terminal_.close();
    ASSERT_FALSE(channel_.is_alive());
}

TEST(a_terminal_behaviour, defaults_utf8_output_to_enabled)
{
    auto const behaviour = terminalpp::behaviour{};

    EXPECT_TRUE(behaviour.utf8_by_default);
}

TEST(a_default_terminal, streams_utf8_elements_without_utf8_mode_switches)
{
    fake_channel channel;
    terminalpp::terminal terminal{channel};

    terminal << terminalpp::element{terminalpp::glyph{u8"\u010E"}};

    EXPECT_THAT(channel.written_, ContainerEq("\x1B[0m\xC4\x8E"_tb));
}

TEST(a_default_terminal, streams_ascii_after_utf8_without_resetting_charset)
{
    fake_channel channel;
    terminalpp::terminal terminal{channel};

    terminal << terminalpp::element{terminalpp::glyph{u8"\u010E"}}
             << terminalpp::element{'x'};

    EXPECT_THAT(channel.written_, ContainerEq("\x1B[0m\xC4\x8Ex"_tb));
}

TEST(a_default_terminal, keeps_cursor_control_sequences_in_7_bit_form)
{
    fake_channel channel;
    terminalpp::terminal terminal{channel};

    terminal << terminalpp::move_cursor({2, 4})
             << terminalpp::element{terminalpp::glyph{u8"\u010E"}};

    EXPECT_THAT(channel.written_, ContainerEq("\x1B[5;3H\x1B[0m\xC4\x8E"_tb));
}

TEST(a_default_terminal, maps_dec_special_graphics_to_unicode_utf8)
{
    fake_channel channel;
    terminalpp::terminal terminal{channel};

    terminal << terminalpp::element{terminalpp::glyph{'q', terminalpp::charset::dec}};

    EXPECT_THAT(channel.written_, ContainerEq("\x1B[0m\xE2\x94\x80"_tb));
}

TEST(a_legacy_terminal, preserves_dec_charset_designation_output)
{
    fake_channel channel;
    auto behaviour = terminalpp::behaviour{};
    behaviour.utf8_by_default = false;
    terminalpp::terminal terminal{channel, behaviour};

    terminal << terminalpp::element{terminalpp::glyph{'q', terminalpp::charset::dec}};

    EXPECT_THAT(channel.written_, ContainerEq("\x1B[0m\x1B(0q"_tb));
}

TEST(a_default_terminal, maps_uk_replacement_glyphs_to_unicode_utf8)
{
    fake_channel channel;
    terminalpp::terminal terminal{channel};

    terminal << terminalpp::element{terminalpp::glyph{'#', terminalpp::charset::uk}};

    EXPECT_THAT(channel.written_, ContainerEq("\x1B[0m\xC2\xA3"_tb));
}

using nrc_mapping_data =
    std::tuple<terminalpp::glyph, terminalpp::byte_storage>;

class an_nrc_default_terminal_mapping
  : public testing::TestWithParam<nrc_mapping_data>
{
};

TEST_P(an_nrc_default_terminal_mapping, maps_to_unicode_utf8)
{
    auto const &[source, expected_utf8] = GetParam();

    fake_channel channel;
    terminalpp::terminal terminal{channel};

    terminal << terminalpp::element{source};

    auto expected = "\x1B[0m"_tb;
    expected += expected_utf8;

    EXPECT_THAT(channel.written_, ContainerEq(expected));
}

const nrc_mapping_data nrc_mapping_table[] = {
    {terminalpp::glyph{'[', terminalpp::charset::dutch},           "\xC4\xB3"_tb},
    {terminalpp::glyph{'[', terminalpp::charset::finnish},         "\xC3\x84"_tb},
    {terminalpp::glyph{'[', terminalpp::charset::french},          "\xC2\xB0"_tb},
    {terminalpp::glyph{'[', terminalpp::charset::french_canadian}, "\xC3\xA2"_tb},
    {terminalpp::glyph{'~', terminalpp::charset::german},          "\xC3\x9F"_tb},
    {terminalpp::glyph{'\\', terminalpp::charset::italian},        "\xC3\xA7"_tb},
    {terminalpp::glyph{'@', terminalpp::charset::danish},          "\xC3\x84"_tb},
    {terminalpp::glyph{']', terminalpp::charset::portuguese},      "\xC3\x95"_tb},
    {terminalpp::glyph{'[', terminalpp::charset::spanish},         "\xC2\xA1"_tb},
    {terminalpp::glyph{'@', terminalpp::charset::swedish},         "\xC3\x89"_tb},
    {terminalpp::glyph{'#', terminalpp::charset::swiss},           "\xC3\xB9"_tb},
};

INSTANTIATE_TEST_SUITE_P(
    supported_nrc_characters,
    an_nrc_default_terminal_mapping,
    ValuesIn(nrc_mapping_table));

}  // namespace
