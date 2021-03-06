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

    ASSERT_EQ(expected_result, result_);

}

static token_test_data const token_test_data_table[] = {
    token_test_data{ ""_tb,                 {} },

    // Single characters yield virtual keys
    token_test_data{ "z"_tb,                { terminalpp::virtual_key{ terminalpp::vk::lowercase_z, terminalpp::vk_modifier::none, 1, { 'z'_tb } } } },
    token_test_data{ "a"_tb,                { terminalpp::virtual_key{ terminalpp::vk::lowercase_a, terminalpp::vk_modifier::none, 1, { 'a'_tb } } } },
    token_test_data{ "J"_tb,                { terminalpp::virtual_key{ terminalpp::vk::uppercase_j, terminalpp::vk_modifier::none, 1, { 'J'_tb } } } },
    token_test_data{ "X"_tb,                { terminalpp::virtual_key{ terminalpp::vk::uppercase_x, terminalpp::vk_modifier::none, 1, { 'X'_tb } } } },

    // Protocol-encoded commands are converted to control sequences
    token_test_data{ "\x1B[S"_tb,           { terminalpp::control_sequence{'[', 'S', false, { ""_tb }} } },
    token_test_data{ "\x9BS"_tb,            { terminalpp::control_sequence{'[', 'S', false, { ""_tb }} } },
    token_test_data{ "\x1B[22;33S"_tb,      { terminalpp::control_sequence{'[', 'S', false, { "22"_tb, "33"_tb }} } },
    token_test_data{ "\x9B"_tb "22;33S"_tb, { terminalpp::control_sequence{'[', 'S', false, { "22"_tb, "33"_tb }} } },
    token_test_data{ "\x1B?M"_tb,           { terminalpp::control_sequence{'?', 'M', false, { ""_tb }} } },

    // Doubly-escaped protocol-encoded commands are converted to control sequences with the meta flag.
    token_test_data{ "\x1B\x1B[S"_tb,       { terminalpp::control_sequence{'[', 'S', true,  { ""_tb }} } },
    token_test_data{ "\x1B\x1B[Z"_tb,       { terminalpp::control_sequence{'[', 'Z', true,  { ""_tb }} } },

    // Extended commands are converted to extended control sequences
    token_test_data{ "\x1B[?6n"_tb,         { terminalpp::control_sequence{'[', 'n', false, { "6"_tb }, '?'} } },
    token_test_data{ "\x1B[>5c"_tb,         { terminalpp::control_sequence{'[', 'c', false, { "5"_tb }, '>'} } },
    token_test_data{ "\x1B[!p"_tb,          { terminalpp::control_sequence{'[', 'p', false, { ""_tb  }, '!'} } },
    token_test_data{ "\x9B!p"_tb,           { terminalpp::control_sequence{'[', 'p', false, { ""_tb  }, '!'} } },

    // ANSI mouse events are converted to the respective structure
    token_test_data{ "\x1B[M"_tb,           {} },
    token_test_data{ "\x1B[M @B"_tb,        { terminalpp::mouse::event{ 
        terminalpp::mouse::event_type::left_button_down, 
        { 31, 33 }
    }}},
    token_test_data{ "\x1B[M!X4"_tb,        { terminalpp::mouse::event{ 
        terminalpp::mouse::event_type::middle_button_down, 
        { 55, 19 }
    }}},

    // Partial commands yield nothing, including partial but otherwise
    // complete-looking mouse commands.
    token_test_data{ "\x1B"_tb,             {} },
    token_test_data{ "\x1B["_tb,            {} },
    token_test_data{ "\x1B[M"_tb,           {} },
};

INSTANTIATE_TEST_SUITE_P(
    reading_terminal_bytes_in_a_terminal_yields_tokens,
    a_terminal_reading_input_tokens,
    ValuesIn(token_test_data_table)
);

namespace {

using partial_token_test_data = std::tuple<
    terminalpp::byte_storage, // First input byte sequence
    terminalpp::byte_storage, // Second input byte sequence
    terminalpp::token_storage // Expected output
>;

class a_terminal_reading_partial_input_tokens :
    public testing::TestWithParam<partial_token_test_data>,
    public terminal_read_test_base
{
};

}

TEST_P(a_terminal_reading_partial_input_tokens, tokenizes_the_results)
{
    using std::get;

    auto const &param = GetParam();
    auto const &first_input_sequence = get<0>(param);
    auto const &second_input_sequence = get<1>(param);
    auto const &expected_result = get<2>(param);

    terminal_.read(append_to_result) 
        >> first_input_sequence
        >> second_input_sequence;

    ASSERT_EQ(expected_result, result_);
}

static partial_token_test_data const partial_token_test_data_table[] = {
    partial_token_test_data{ "\x1B"_tb,   "[A"_tb,  { terminalpp::control_sequence{'[', 'A', false, { ""_tb }} } },
    partial_token_test_data{ "\x9B"_tb,   "A"_tb,   { terminalpp::control_sequence{'[', 'A', false, { ""_tb }} } },
    partial_token_test_data{ "\x1B["_tb,  "A"_tb,   { terminalpp::control_sequence{'[', 'A', false, { ""_tb }} } },
    partial_token_test_data{ "\x1B[M"_tb, "!X4"_tb, { terminalpp::mouse::event{ 
        terminalpp::mouse::event_type::middle_button_down, 
        { 55, 19 }
    }}},
};

INSTANTIATE_TEST_SUITE_P(
    reading_split_packets_of_ansi_tokens_parses_to_tokens,
    a_terminal_reading_partial_input_tokens,
    ValuesIn(partial_token_test_data_table)
);
