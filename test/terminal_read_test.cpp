#include "expect_tokens.hpp"
#include "terminalpp/terminal.hpp"
#include <gtest/gtest.h>

using namespace terminalpp::literals;
using testing::ValuesIn;

namespace {

class terminal_read_test_base
{
public:
    terminal_read_test_base(terminalpp::behaviour const &behaviour = terminalpp::behaviour{})
      : terminal_([](terminalpp::bytes) {}, behaviour)
    {
    }

protected:
    std::vector<terminalpp::token> result_;

    std::function<void (terminalpp::tokens)> discard_result =
        [](terminalpp::tokens)
        {
        };

    std::function<void (terminalpp::tokens)> append_to_result =
        [this](terminalpp::tokens tokens)
        {
            result_.insert(result_.end(), tokens.cbegin(), tokens.cend());
        };

    terminalpp::terminal terminal_;
};

using token_test_data = std::tuple<
    terminalpp::byte_storage, // Input byte sequence
    terminalpp::token_storage // Expected output
>;

class a_terminal_reading_input_tokens :
    public testing::TestWithParam<token_test_data>,
    public terminal_read_test_base
{
};

}

TEST_P(a_terminal_reading_input_tokens, tokenizes_the_results)
{
    using std::get;

    auto const &param = GetParam();
    auto const &input_sequence = get<0>(param);
    auto const &expected_result = get<1>(param);

    terminal_.read(append_to_result) >> input_sequence;

    expect_tokens(expected_result, result_);
}

static token_test_data const token_test_data_table[] = {
    { ""_tb, {} },

    // Single characters yield virtual keys
    { "z"_tb, { terminalpp::virtual_key{ terminalpp::vk::lowercase_z, terminalpp::vk_modifier::none, 1, { 'z'_tb } } } },
    { "a"_tb, { terminalpp::virtual_key{ terminalpp::vk::lowercase_a, terminalpp::vk_modifier::none, 1, { 'a'_tb } } } },
    { "J"_tb, { terminalpp::virtual_key{ terminalpp::vk::uppercase_j, terminalpp::vk_modifier::none, 1, { 'J'_tb } } } },
    { "X"_tb, { terminalpp::virtual_key{ terminalpp::vk::uppercase_x, terminalpp::vk_modifier::none, 1, { 'X'_tb } } } },

    // Protocol-encoded commands are converted to control sequences
    { "\x1B[S"_tb,      { terminalpp::control_sequence{'[', 'S', false, { ""_tb }} } },
    { "\x1B[22;33S"_tb, { terminalpp::control_sequence{'[', 'S', false, { "22"_tb, "33"_tb }} } },

    // Doubly-escaped protocol-encoded commands are converted to control sequences with the meta flag.
    { "\x1B\x1B[S"_tb,  { terminalpp::control_sequence{'[', 'S', true,  { ""_tb }} } },
};

INSTANTIATE_TEST_SUITE_P(
    reading_terminal_bytes_in_a_terminal_yields_tokens,
    a_terminal_reading_input_tokens,
    ValuesIn(token_test_data_table)
);

/*

TEST(terminal_read_test, read_mouse_command_yields_mouse_report)
{
    expect_token(
        "\x1B[M @B",
        terminalpp::ansi::mouse::report {
            terminalpp::ansi::mouse::report::LEFT_BUTTON_DOWN,
            31,
            33
        });
}

TEST(terminal_read_test, read_non_mouse_similar_command_yields_command)
{
    expect_token(
        "\x1B?M",
        terminalpp::ansi::control_sequence {
            '?',
            'M',
            false,
            { "" }
        });
}

TEST(terminal_read_test, read_partial_command_yields_nothing)
{
    expect_tokens("\x1B[", {});
}

TEST(terminal_read_test, read_partial_command_then_read_remainder_yields_command)
{
    terminalpp::terminal terminal;

    std::string input0 = "\x1B[";
    std::string input1 = "E";

    auto expected = std::vector<terminalpp::token> {
        terminalpp::ansi::control_sequence {
            '[',
            'E',
            false,
            { "" }
        }
    };

    terminal.read(input0);
    auto result = terminal.read(input1);

    ASSERT_EQ(expected.size(), result.size());
    ASSERT_EQ(
        boost::get<terminalpp::ansi::control_sequence>(expected[0]),
        boost::get<terminalpp::ansi::control_sequence>(result[0]));
}

TEST(terminal_read_test, read_partial_mouse_command_yields_nothing)
{
    expect_tokens("\x1B[M", {});
}

TEST(terminal_read_test, read_8bit_command_yields_command)
{
    expect_token(
        "\x9B""22;33S",
        terminalpp::ansi::control_sequence {
            '[',
            'S',
            false,
            { "22", "33" }
        });
}

TEST(terminal_read_test, read_query_extended_command_yields_extended_command)
{
    expect_token(
        "\x1B[?6n",
        terminalpp::ansi::control_sequence {
            '[',
            'n',
            false,
            { "6" },
            '?'
        });
}

TEST(terminal_read_test, read_gt_extended_command_yields_extended_command)
{
    expect_token(
        "\x1B[>5c",
        terminalpp::ansi::control_sequence {
            '[',
            'c',
            false,
            { "5" },
            '>'
        });
}

TEST(terminal_read_test, read_bang_extended_command_yields_extended_command)
{
    expect_token(
        "\x1B[!p",
        terminalpp::ansi::control_sequence {
            '[',
            'p',
            false,
            { "" },
            '!'
        });
}
*/
