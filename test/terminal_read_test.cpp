#include "terminalpp/terminal.hpp"
#include <gtest/gtest.h>

using namespace terminalpp::literals;
using testing::ValuesIn;

namespace {

class terminal_read_test_base
{
public:
    terminal_read_test_base(terminalpp::behaviour const &behaviour = terminalpp::behaviour{})
      : terminal_(behaviour)
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

    token_test_data{ "AB"_tb,               {
        terminalpp::virtual_key{ 
            terminalpp::vk::uppercase_a, 
            terminalpp::vk_modifier::none, 
            1, { 'A'_tb } 
        },
        terminalpp::virtual_key{ 
            terminalpp::vk::uppercase_b, 
            terminalpp::vk_modifier::none, 
            1, { 'B'_tb } 
        },
    }},

    // Partial commands yield nothing, including partial but otherwise
    // complete-looking mouse commands.
    token_test_data{ "\x1B"_tb,             {} },
    token_test_data{ "\x1B["_tb,            {} },
    token_test_data{ "\x1B[M"_tb,           {} },

    // Protocol-encoded commands are converted to control sequences
    token_test_data{ "\x1B[S"_tb,           { terminalpp::control_sequence{'[', 'S', false, { ""_tb }} } },
    token_test_data{ "\x9BS"_tb,            { terminalpp::control_sequence{'[', 'S', false, { ""_tb }} } },
    token_test_data{ "\x1B[22;33S"_tb,      { terminalpp::control_sequence{'[', 'S', false, { "22"_tb, "33"_tb }} } },
    token_test_data{ "\x9B"_tb "22;33S"_tb, { terminalpp::control_sequence{'[', 'S', false, { "22"_tb, "33"_tb }} } },
    token_test_data{ "\x1B?M"_tb,           { terminalpp::control_sequence{'?', 'M', false, { ""_tb }} } },

    // Doubly-escaped protocol-encoded commands are converted to control sequences with the meta flag.
    token_test_data{ "\x1B\x1B[S"_tb,       { terminalpp::control_sequence{'[', 'S', true,  { ""_tb }} } },
    token_test_data{ "\x1B\x1B[T"_tb,       { terminalpp::control_sequence{'[', 'T', true,  { ""_tb }} } },

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

    // Cursor keys are converted to the respective virtual keys.
    token_test_data{ "\x1B[A"_tb,           { terminalpp::virtual_key{
        terminalpp::vk::cursor_up,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'[', 'A', false, { ""_tb } }
    }}},
    token_test_data{ "\x1B[B"_tb,           { terminalpp::virtual_key{
        terminalpp::vk::cursor_down,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'[', 'B', false, { ""_tb } }
    }}},
    token_test_data{ "\x1B[C"_tb,           { terminalpp::virtual_key{
        terminalpp::vk::cursor_right,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'[', 'C', false, { ""_tb } }
    }}},
    token_test_data{ "\x1B[D"_tb,           { terminalpp::virtual_key{
        terminalpp::vk::cursor_left,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'[', 'D', false, { ""_tb } }
    }}},

    token_test_data{ "\x1B[1A"_tb,           { terminalpp::virtual_key{
        terminalpp::vk::cursor_up,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'[', 'A', false, { "1"_tb } }
    }}},
    token_test_data{ "\x1B[2A"_tb,           { terminalpp::virtual_key{
        terminalpp::vk::cursor_up,
        terminalpp::vk_modifier::none,
        2,
        terminalpp::control_sequence{'[', 'A', false, { "2"_tb } }
    }}},
    token_test_data{ "\x1B[3A"_tb,           { terminalpp::virtual_key{
        terminalpp::vk::cursor_up,
        terminalpp::vk_modifier::none,
        3,
        terminalpp::control_sequence{'[', 'A', false, { "3"_tb } }
    }}},

    token_test_data{ "\x1B\x1B[A"_tb,           { terminalpp::virtual_key{
        terminalpp::vk::cursor_up,
        terminalpp::vk_modifier::meta,
        1,
        terminalpp::control_sequence{'[', 'A', true,  { ""_tb } }
    }}},

    // Other special keyboard keys are converted to the respective virtual keys
    token_test_data{ "\x1B[1~"_tb,           { terminalpp::virtual_key{
        terminalpp::vk::home,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'[', '~', false, { "1"_tb } }
    }}},
    token_test_data{ "\x1B[2~"_tb,           { terminalpp::virtual_key{
        terminalpp::vk::ins,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'[', '~', false, { "2"_tb } }
    }}},
    token_test_data{ "\x1B[3~"_tb,           { terminalpp::virtual_key{
        terminalpp::vk::del,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'[', '~', false, { "3"_tb } }
    }}},
    token_test_data{ "\x1B[4~"_tb,           { terminalpp::virtual_key{
        terminalpp::vk::end,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'[', '~', false, { "4"_tb } }
    }}},
    token_test_data{ "\x1B[5~"_tb,           { terminalpp::virtual_key{
        terminalpp::vk::pgup,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'[', '~', false, { "5"_tb } }
    }}},
    token_test_data{ "\x1B[6~"_tb,           { terminalpp::virtual_key{
        terminalpp::vk::pgdn,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'[', '~', false, { "6"_tb } }
    }}},

    // Keypad commands can have modifiers
    token_test_data{ "\x1B[6;5~"_tb,         { terminalpp::virtual_key{
        terminalpp::vk::pgdn,
        terminalpp::vk_modifier::ctrl,
        1,
        terminalpp::control_sequence{'[', '~', false,  { "6"_tb, "5"_tb } }
    }}},
    token_test_data{ "\x1B\x1B[6~"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::pgdn,
        terminalpp::vk_modifier::meta,
        1,
        terminalpp::control_sequence{'[', '~', true,  { "6"_tb } }
    }}},

    // Alternative sequences for control keys
    token_test_data{ "\x1B[H"_tb,            { terminalpp::virtual_key{
        terminalpp::vk::home,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'[', 'H', false, { ""_tb } }
    }}},
    token_test_data{ "\x1B[F"_tb,            { terminalpp::virtual_key{
        terminalpp::vk::end,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'[', 'F', false, { ""_tb } }
    }}},
    token_test_data{ "\x1BOA"_tb,            { terminalpp::virtual_key{
        terminalpp::vk::cursor_up,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'O', 'A', false, { ""_tb } }
    }}},
    token_test_data{ "\x1BOB"_tb,            { terminalpp::virtual_key{
        terminalpp::vk::cursor_down,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'O', 'B', false, { ""_tb } }
    }}},
    token_test_data{ "\x1BOC"_tb,            { terminalpp::virtual_key{
        terminalpp::vk::cursor_right,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'O', 'C', false, { ""_tb } }
    }}},
    token_test_data{ "\x1BOD"_tb,            { terminalpp::virtual_key{
        terminalpp::vk::cursor_left,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'O', 'D', false, { ""_tb } }
    }}},

    // All forms of tab key should yield the same virtual key
    token_test_data{ "\t"_tb,                { terminalpp::virtual_key{
        terminalpp::vk::ht,
        terminalpp::vk_modifier::none,
        1,
        '\t'
    }}},
    token_test_data{ "\x1B[I"_tb,            { terminalpp::virtual_key{
        terminalpp::vk::ht,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'[', 'I', false, { ""_tb } }
    }}},
    token_test_data{ "\x1B[7I"_tb,            { terminalpp::virtual_key{
        terminalpp::vk::ht,
        terminalpp::vk_modifier::none,
        7,
        terminalpp::control_sequence{'[', 'I', false, { "7"_tb } }
    }}},
    token_test_data{ "\x9BI"_tb,             { terminalpp::virtual_key{
        terminalpp::vk::ht,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'[', 'I', false, { ""_tb } }
    }}},
    token_test_data{ "\x1BOI"_tb,            { terminalpp::virtual_key{
        terminalpp::vk::ht,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'O', 'I', false, { ""_tb } }
    }}},
    token_test_data{ "\x8FI"_tb,             { terminalpp::virtual_key{
        terminalpp::vk::ht,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'O', 'I', false, { ""_tb } }
    }}},

    token_test_data{ "\x1B[Z"_tb,            { terminalpp::virtual_key{
        terminalpp::vk::bt,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'[', 'Z', false, { ""_tb } }
    }}},

    // Various forms of carriage return should be converted to the respective 
    // virtual keys.
    token_test_data{ "\r\n"_tb,              { terminalpp::virtual_key{
        terminalpp::vk::enter,
        terminalpp::vk_modifier::none,
        1,
        '\n'
    }}},
    // Including this common but incorrect form.
    token_test_data{ "\n\r"_tb,              { terminalpp::virtual_key{
        terminalpp::vk::enter,
        terminalpp::vk_modifier::none,
        1,
        '\n'
    }}},
    token_test_data{ "\r\0"_tb,              { terminalpp::virtual_key{
        terminalpp::vk::enter,
        terminalpp::vk_modifier::none,
        1,
        '\n'
    }}},
    token_test_data{ "\r\0\r\0"_tb,               {
        terminalpp::virtual_key{ 
            terminalpp::vk::enter,
            terminalpp::vk_modifier::none,
            1,
            '\n'
        },
        terminalpp::virtual_key{ 
            terminalpp::vk::enter,
            terminalpp::vk_modifier::none,
            1,
            '\n'
        },
    }},
    token_test_data{ "\n\n"_tb,               {
        terminalpp::virtual_key{ 
            terminalpp::vk::enter,
            terminalpp::vk_modifier::none,
            1,
            '\n'
        },
        terminalpp::virtual_key{ 
            terminalpp::vk::enter,
            terminalpp::vk_modifier::none,
            1,
            '\n'
        },
    }},
    token_test_data{ "\x1BOM"_tb,            { terminalpp::virtual_key{
        terminalpp::vk::enter,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{'O', 'M', false, { ""_tb } }
    }}},

    // Function keys are converted to the respective virtual keys
    token_test_data{ "\x1B[11~"_tb,         { terminalpp::virtual_key{
        terminalpp::vk::f1,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "11"_tb }}
    }}},
    token_test_data{ "\x1B[12~"_tb,         { terminalpp::virtual_key{
        terminalpp::vk::f2,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "12"_tb }}
    }}},
    token_test_data{ "\x1B[13~"_tb,         { terminalpp::virtual_key{
        terminalpp::vk::f3,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "13"_tb }}
    }}},
    token_test_data{ "\x1B[14~"_tb,         { terminalpp::virtual_key{
        terminalpp::vk::f4,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "14"_tb }}
    }}},
    token_test_data{ "\x1B[15~"_tb,         { terminalpp::virtual_key{
        terminalpp::vk::f5,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "15"_tb }}
    }}},
    // Sic.  The protocol really skips over 16~ and goes to 17~ for f6.
    token_test_data{ "\x1B[17~"_tb,         { terminalpp::virtual_key{
        terminalpp::vk::f6,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "17"_tb }}
    }}},
    token_test_data{ "\x1B[18~"_tb,         { terminalpp::virtual_key{
        terminalpp::vk::f7,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "18"_tb }}
    }}},
    token_test_data{ "\x1B[19~"_tb,         { terminalpp::virtual_key{
        terminalpp::vk::f8,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "19"_tb }}
    }}},
    token_test_data{ "\x1B[20~"_tb,         { terminalpp::virtual_key{
        terminalpp::vk::f9,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "20"_tb }}
    }}},
    token_test_data{ "\x1B[21~"_tb,         { terminalpp::virtual_key{
        terminalpp::vk::f10,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "21"_tb }}
    }}},
    // Sic.  The protocol really skips over 22~ and goes to 23~ for f11.
    token_test_data{ "\x1B[23~"_tb,         { terminalpp::virtual_key{
        terminalpp::vk::f11,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "23"_tb }}
    }}},
    token_test_data{ "\x1B[24~"_tb,         { terminalpp::virtual_key{
        terminalpp::vk::f12,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "24"_tb }}
    }}},

    // Function keys may have modifiers
    token_test_data{ "\x1B[24;0~"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f12,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "24"_tb, "0"_tb }}
    }}},
    token_test_data{ "\x1B[24;2~"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f12,
        terminalpp::vk_modifier::shift,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "24"_tb, "2"_tb }}
    }}},
    token_test_data{ "\x1B[24;3~"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f12,
        terminalpp::vk_modifier::alt,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "24"_tb, "3"_tb }}
    }}},
    token_test_data{ "\x1B[24;4~"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f12,
        terminalpp::vk_modifier::shift | terminalpp::vk_modifier::alt,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "24"_tb, "4"_tb }}
    }}},
    token_test_data{ "\x1B[24;5~"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f12,
        terminalpp::vk_modifier::ctrl,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "24"_tb, "5"_tb }}
    }}},
    token_test_data{ "\x1B[24;6~"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f12,
        terminalpp::vk_modifier::shift | terminalpp::vk_modifier::ctrl,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "24"_tb, "6"_tb }}
    }}},
    token_test_data{ "\x1B[24;7~"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f12,
        terminalpp::vk_modifier::alt | terminalpp::vk_modifier::ctrl,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "24"_tb, "7"_tb }}
    }}},
    token_test_data{ "\x1B[24;8~"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f12,
        terminalpp::vk_modifier::shift | terminalpp::vk_modifier::alt | terminalpp::vk_modifier::ctrl,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "24"_tb, "8"_tb }}
    }}},
    token_test_data{ "\x1B[24;9~"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f12,
        terminalpp::vk_modifier::meta,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "24"_tb, "9"_tb }}
    }}},
    token_test_data{ "\x1B[24;10~"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f12,
        terminalpp::vk_modifier::meta | terminalpp::vk_modifier::shift,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "24"_tb, "10"_tb }}
    }}},
    token_test_data{ "\x1B[24;11~"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f12,
        terminalpp::vk_modifier::meta | terminalpp::vk_modifier::alt,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "24"_tb, "11"_tb }}
    }}},
    token_test_data{ "\x1B[24;12~"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f12,
        terminalpp::vk_modifier::meta | terminalpp::vk_modifier::shift | terminalpp::vk_modifier::alt,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "24"_tb, "12"_tb }}
    }}},
    token_test_data{ "\x1B[24;13~"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f12,
        terminalpp::vk_modifier::meta | terminalpp::vk_modifier::ctrl,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "24"_tb, "13"_tb }}
    }}},
    token_test_data{ "\x1B[24;14~"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f12,
        terminalpp::vk_modifier::meta | terminalpp::vk_modifier::shift | terminalpp::vk_modifier::ctrl,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "24"_tb, "14"_tb }}
    }}},
    token_test_data{ "\x1B[24;15~"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f12,
        terminalpp::vk_modifier::meta | terminalpp::vk_modifier::ctrl | terminalpp::vk_modifier::alt,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "24"_tb, "15"_tb }}
    }}},
    token_test_data{ "\x1B[24;16~"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f12,
        terminalpp::vk_modifier::meta | terminalpp::vk_modifier::shift | terminalpp::vk_modifier::ctrl | terminalpp::vk_modifier::alt,
        1,
        terminalpp::control_sequence{ '[', '~', false, { "24"_tb, "16"_tb }}
    }}},

    // We can also parse alternative SS3 fkey sequences
    token_test_data{ "\x1BOP"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f1,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{ 'O', 'P', false, { ""_tb } }
    }}},
    token_test_data{ "\x1BOQ"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f2,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{ 'O', 'Q', false, { ""_tb } }
    }}},
    token_test_data{ "\x1BOR"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f3,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{ 'O', 'R', false, { ""_tb } }
    }}},
    token_test_data{ "\x1BOS"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f4,
        terminalpp::vk_modifier::none,
        1,
        terminalpp::control_sequence{ 'O', 'S', false, { ""_tb } }
    }}},
    token_test_data{ "\x1B\x1BOS"_tb,       { terminalpp::virtual_key{
        terminalpp::vk::f4,
        terminalpp::vk_modifier::meta,
        1,
        terminalpp::control_sequence{ 'O', 'S', true,  { ""_tb } }
    }}},
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
    partial_token_test_data{ "\x1B"_tb,   "[X"_tb,  { terminalpp::control_sequence{'[', 'X', false, { ""_tb }} } },
    partial_token_test_data{ "\x9B"_tb,   "X"_tb,   { terminalpp::control_sequence{'[', 'X', false, { ""_tb }} } },
    partial_token_test_data{ "\x1B["_tb,  "X"_tb,   { terminalpp::control_sequence{'[', 'X', false, { ""_tb }} } },
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
