#include "terminal_test.hpp"

#include <gmock/gmock.h>

namespace {

using namespace terminalpp::literals;  // NOLINT
using testing::ContainerEq;

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

}  // namespace
