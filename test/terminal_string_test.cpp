#include "terminal_test.hpp"
#include "expect_sequence.hpp"
#include <terminalpp/graphics.hpp>
#include <gtest/gtest.h>

using namespace terminalpp::literals;
using testing::ValuesIn;

TEST_F(a_terminal, empty_string_outputs_default_attributes)
{
    terminal_.write(append_to_result) << ""_ets;

    expect_sequence("\x1B[0m"_tb, result_);
}

TEST_F(a_terminal, basic_string_outputs_default_attributes_and_basic_string)
{
    terminal_.write(append_to_result) << "abcde"_ets;
    expect_sequence("\x1B[0mabcde"_tb, result_);
}

TEST_F(a_terminal, outputting_another_basic_string_does_not_output_default_attributes)
{
    expect_when_streaming("abcde"_tb, "abcde"_ets);
}

namespace {

using streaming_text_data = std::tuple<
    terminalpp::string,       // initial string to discard
    terminalpp::string,       // text streamed to terminal
    terminalpp::byte_storage  // expected output
>;

class streaming_text 
  : public testing::TestWithParam<streaming_text_data>,
    public terminal_test_base
{
};

}

TEST_P(streaming_text, to_a_terminal_converts_to_ansi_codes)
{
    using std::get;

    auto const &params = GetParam();
    auto const &init_string = get<0>(params);
    auto const &text_to_stream = get<1>(params);
    auto const &expected_output = get<2>(params);

    terminal_.write(discard_result) << init_string;
    terminal_.write(append_to_result) << text_to_stream;

    expect_sequence(expected_output, result_);
}


static streaming_text_data const streaming_text_data_table[] = {
    streaming_text_data{ ""_ets, ""_ets, ""_tb },

    // Test character set changes.
    streaming_text_data{ ""_ets,        "\\c0abcde"_ets, "\x1B(0abcde"_tb },
    streaming_text_data{ "\\c0abc"_ets, "\\c0de"_ets,    "de"_tb },
    streaming_text_data{ "\\c0abc"_ets, "\\c%6de"_ets,   "\x1B(%6de"_tb },

    // Test intensity (bold/faint) changes
    streaming_text_data{ ""_ets,        "\\i>abcde"_ets, "\x1B[1mabcde"_tb },
    streaming_text_data{ ""_ets,        "\\i<abcde"_ets, "\x1B[2mabcde"_tb },
    streaming_text_data{ ""_ets,        "\\i=abcde"_ets, "abcde"_tb },
    streaming_text_data{ "\\i>abc"_ets, "\\i>abcde"_ets, "abcde"_tb },
    streaming_text_data{ "\\i>abc"_ets, "\\i=de"_ets,    "\x1B[0mde"_tb },
    streaming_text_data{ "\\i>abc"_ets, "\\ixde"_ets,    "\x1B[0mde"_tb },

    // Test polarity changes
    streaming_text_data{ ""_ets,        "\\p+abcde"_ets, "abcde"_tb },
    streaming_text_data{ ""_ets,        "\\p-abcde"_ets, "\x1B[7mabcde"_tb },
    streaming_text_data{ "\\p-abc"_ets, "\\p+de"_ets,    "\x1B[0mde"_tb },
    streaming_text_data{ "\\p-abc"_ets, "\\p=de"_ets,    "\x1B[0mde"_tb },

    // Test underlining changes
    streaming_text_data{ ""_ets,        "\\u+abcde"_ets, "\x1B[4mabcde"_tb },
    streaming_text_data{ ""_ets,        "\\u-abcde"_ets, "abcde"_tb },
    streaming_text_data{ "\\u+abc"_ets, "\\u+de"_ets,    "de"_tb },
    streaming_text_data{ "\\u+abc"_ets, "\\u-de"_ets,    "\x1B[0mde"_tb },
    streaming_text_data{ "\\u+abc"_ets, "\\u=de"_ets,    "\x1B[0mde"_tb },

    // Test foreground colour
    streaming_text_data{ ""_ets,        "\\[2abc"_ets,   "\x1B[32mabc"_tb },
    streaming_text_data{ ""_ets,        "\\[3abc"_ets,   "\x1B[33mabc"_tb },
    streaming_text_data{ ""_ets,        "\\<510abc"_ets, "\x1B[38;5;202mabc"_tb },
    streaming_text_data{ ""_ets,        "\\{12abc"_ets,  "\x1B[38;5;244mabc"_tb },
    streaming_text_data{ ""_ets,        "\\[9abc"_ets,   "abc"_tb },

    streaming_text_data{ 
        ""_ets,        
        "\\[2ab\\<510cd\\{02ef\\[9gh"_ets,
        "\x1B[32mab\x1B[38;5;202mcd\x1B[38;5;234mef\x1B[0mgh"_tb },

    // Test background colour
    streaming_text_data{ ""_ets,        "\\]2abc"_ets,   "\x1B[42mabc"_tb },
    streaming_text_data{ ""_ets,        "\\>510abc"_ets, "\x1B[48;5;202mabc"_tb },
    streaming_text_data{ ""_ets,        "\\}12abc"_ets,  "\x1B[48;5;244mabc"_tb },

    streaming_text_data{ 
        ""_ets,        
        "\\]2ab\\>135cd\\}02ef\\]9gh"_ets,
        "\x1B[42mab\x1B[48;5;75mcd\x1B[48;5;234mef\x1B[0mgh"_tb },

    // Test interoperability of attributes.
    // NOTE: At a later date, it may be implemented that the algorithm will
    // branch and look for strategies for producing the shortest sequence.
    // In that case, it may be that switching several attributes off is longer
    // than switching to default then re-enabling one attribute.  It also may
    // be determined by environment - different terminals behave differently.
    streaming_text_data{ 
        ""_ets,        
        "\\[2\\]1a\\p-b\\p+c"_ets,
        "\x1B[32;41ma\x1B[7mb\x1B[27mc"_tb },

    // Test unicode output.
    // If a string contains a four-hexdigit unicode code, then
    // it should be output as a unicode character if it can be.
    // This will include commands to change to and from the utf-8
    // character set and also to reset the character set at the end.
    streaming_text_data{ ""_ets,           "\\U0000"_ets,    "\x1B%G\x00"_tb },
    streaming_text_data{ ""_ets,           "\\U0057"_ets,    "\x1B%GW"_tb },
    streaming_text_data{ "\\U0057"_ets,    "\\U010E"_ets,    "\xC4\x8E"_tb },
    streaming_text_data{ "\\U0057"_ets,    "\\U16B8"_ets,    "\xE1\x9A\xB8"_tb },

    streaming_text_data{ "\\cU\\C205"_ets, "\\U0057"_ets,    "\x1B(B\x1B%GW"_tb },
    streaming_text_data{ "\\U0057"_ets,    "\\cA\\C156"_ets, "\x1B%@\x1B(A\x9C"_tb },
};

INSTANTIATE_TEST_SUITE_P(
    text_can_be_streamed_to_a_terminal,
    streaming_text,
    ValuesIn(streaming_text_data_table)
);

TEST_F(a_terminal, can_stream_a_single_element)
{
    terminalpp::element const elem{'X', {terminalpp::graphics::colour::red}};

    terminal_.write(discard_result) << ""_ets;
    terminal_.write(append_to_result) << elem;

    expect_sequence("\x1B[31mX"_tb, result_);
}

TEST(a_terminal_that_supports_unicode_in_all_charsets, skips_charset_switch_before_selecting_utf8_charset)
{
    terminalpp::behaviour const behaviour = 
        []()
        {
            terminalpp::behaviour behaviour;
            behaviour.unicode_in_all_charsets = true;
            return behaviour;
        }();

    terminalpp::byte_storage result;
    auto const discard_result = [](terminalpp::bytes){};
    auto const append_result =
        [&result](terminalpp::bytes data)
        {
            result.append(data.begin(), data.end());
        };

    terminalpp::terminal terminal{behaviour};
    terminal.write(append_result) << "\\cU\\C205\\U0057"_ets;

    expect_sequence("\x1B[0m\x1B(U\xCD\x1B%GW"_tb, result);
}

namespace {

using write_position_data = std::tuple<
    terminalpp::point,  // Initial cursor position
    terminalpp::string, // String to write
    terminalpp::point   // Expected terminal position
>;

class writing_at_a_position
  : public testing::TestWithParam<write_position_data>,
    public terminal_test_base
{
public:
    writing_at_a_position()
    {
        // All tests run in a 10x10 screen
        terminal_.set_size({10, 10});
    }
};

}

TEST_P(writing_at_a_position, leaves_the_cursor_at_the_specified_position)
{
    using std::get;

    auto const &params = GetParam();
    auto const &init_position = get<0>(params);
    auto const &text_to_stream = get<1>(params);
    auto const &expected_position = get<2>(params);

    terminal_.write(discard_result) 
        << ""_ets
        << terminalpp::move_cursor(init_position)
        << text_to_stream;

    terminal_.write(append_to_result)
        << terminalpp::move_cursor(expected_position);

    // Moving to the position we are already at should yield no required
    // output.
    expect_sequence(""_tb, result_);
}

static write_position_data const write_position_data_table[] = {
    // Writing within the same row moves the cursor to the write
    write_position_data{ {0, 0}, ""_ets,                {0, 0} },
    write_position_data{ {0, 0}, "x"_ets,               {1, 0} },
    write_position_data{ {0, 0}, "abcde"_ets,           {5, 0} },
    write_position_data{ {2, 3}, "abcde"_ets,           {7, 3} },
};

INSTANTIATE_TEST_SUITE_P(
    streaming_text_moves_the_cursor,
    writing_at_a_position,
    ValuesIn(write_position_data_table)
);
