#include "terminal_test.hpp"

#include <gmock/gmock.h>
#include <terminalpp/graphics.hpp>

using namespace terminalpp::literals;  // NOLINT
using testing::ContainerEq;
using testing::ValuesIn;

namespace {

TEST_F(a_new_terminal, empty_string_outputs_default_attributes)
{
    terminal_ << ""_ets;
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[0m"_tb));
}

TEST_F(a_new_terminal, basic_string_outputs_default_attributes_and_basic_string)
{
    terminal_ << "abcde"_ets;
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[0mabcde"_tb));
}

TEST_F(
    a_new_terminal,
    outputting_another_basic_string_does_not_output_default_attributes)
{
    terminal_ << "abc"_ets;
    channel_.written_.clear();

    terminal_ << "abcde"_ets;
    EXPECT_THAT(channel_.written_, ContainerEq("abcde"_tb));
}

namespace {

using streaming_text_data = std::tuple<
    terminalpp::string,       // initial string to discard
    terminalpp::string,       // text streamed to terminal
    terminalpp::byte_storage  // expected output
    >;

class streaming_text : public testing::TestWithParam<streaming_text_data>,
                       public terminal_test_base
{
};

}  // namespace

TEST_P(streaming_text, to_a_terminal_converts_to_ansi_codes)
{
    using std::get;

    auto const &[init_string, text_to_stream, expected_output] = GetParam();

    terminal_ << init_string;
    channel_.written_.clear();

    terminal_ << text_to_stream;

    EXPECT_THAT(channel_.written_, ContainerEq(expected_output));
}

streaming_text_data const streaming_text_data_table[] = {
    {""_ets,            ""_ets,                   ""_tb                                                   },

    // Test character set changes.
    {""_ets,            R"(\c0abcde)"_ets,        "\x1B(0abcde"_tb                                        },
    {R"(\c0abc)"_ets,   R"(\c0de)"_ets,           "de"_tb                                                 },
    {R"(\c0abc)"_ets,   R"(\c%6de)"_ets,          "\x1B(%6de"_tb                                          },

    // Test intensity (bold/faint) changes
    {""_ets,            R"(\i>abcde)"_ets,        "\x1B[1mabcde"_tb                                       },
    {""_ets,            R"(\i<abcde)"_ets,        "\x1B[2mabcde"_tb                                       },
    {""_ets,            R"(\i=abcde)"_ets,        "abcde"_tb                                              },
    {R"(\i>abc)"_ets,   R"(\i>abcde)"_ets,        "abcde"_tb                                              },
    {R"(\i>abc)"_ets,   R"(\i=de)"_ets,           "\x1B[0mde"_tb                                          },
    {R"(\i>abc)"_ets,   R"(\ixde)"_ets,           "\x1B[0mde"_tb                                          },

    // Bold-faint transitions must go through an intermediate normal state
    // because certain terminals have a "bold-and-faint" combination that is
    // not useful.
    {R"(\i<a)"_ets,     R"(\i>b)"_ets,            "\x1B[22;1mb"_tb                                        },
    {R"(\i>a)"_ets,     R"(\i<b)"_ets,            "\x1B[22;2mb"_tb                                        },

    // Test polarity changes
    {""_ets,            R"(\p+abcde)"_ets,        "abcde"_tb                                              },
    {""_ets,            R"(\p-abcde)"_ets,        "\x1B[7mabcde"_tb                                       },
    {R"(\p-abc)"_ets,   R"(\p+de)"_ets,           "\x1B[0mde"_tb                                          },
    {R"(\p-abc)"_ets,   R"(\p=de)"_ets,           "\x1B[0mde"_tb                                          },

    // Test underlining changes
    {""_ets,            R"(\u+abcde)"_ets,        "\x1B[4mabcde"_tb                                       },
    {""_ets,            R"(\u-abcde)"_ets,        "abcde"_tb                                              },
    {R"(\u+abc)"_ets,   R"(\u+de)"_ets,           "de"_tb                                                 },
    {R"(\u+abc)"_ets,   R"(\u-de)"_ets,           "\x1B[0mde"_tb                                          },
    {R"(\u+abc)"_ets,   R"(\u=de)"_ets,           "\x1B[0mde"_tb                                          },

    // Test foreground colour
    {""_ets,            R"(\[2abc)"_ets,          "\x1B[32mabc"_tb                                        },
    {""_ets,            R"(\[3abc)"_ets,          "\x1B[33mabc"_tb                                        },
    {""_ets,            R"(\<510abc)"_ets,        "\x1B[38;5;202mabc"_tb                                  },
    {""_ets,            R"(\{12abc)"_ets,         "\x1B[38;5;244mabc"_tb                                  },
    {""_ets,            R"(\[9abc)"_ets,          "abc"_tb                                                },
    {""_ets,            R"(\(000000abc)"_ets,     "\x1B[38;2;0;0;0mabc"_tb                                },
    {""_ets,            R"(\(FF0000abc)"_ets,     "\x1B[38;2;255;0;0mabc"_tb                              },
    {""_ets,            R"(\(00FF00abc)"_ets,     "\x1B[38;2;0;255;0mabc"_tb                              },
    {""_ets,            R"(\(0000FFabc)"_ets,     "\x1B[38;2;0;0;255mabc"_tb                              },

    {""_ets,
     R"(\[2ab\<510cd\{02ef\[9gh)"_ets,            "\x1B[32mab\x1B[38;5;202mcd\x1B[38;5;234mef\x1B[0mgh"_tb},

    // Test background colour
    {""_ets,            R"(\]2abc)"_ets,          "\x1B[42mabc"_tb                                        },
    {""_ets,            R"(\>510abc)"_ets,        "\x1B[48;5;202mabc"_tb                                  },
    {""_ets,            R"(\}12abc)"_ets,         "\x1B[48;5;244mabc"_tb                                  },
    {""_ets,            R"(\)000000abc)"_ets,     "\x1B[48;2;0;0;0mabc"_tb                                },
    {""_ets,            R"(\)FF0000abc)"_ets,     "\x1B[48;2;255;0;0mabc"_tb                              },
    {""_ets,            R"(\)00FF00abc)"_ets,     "\x1B[48;2;0;255;0mabc"_tb                              },
    {""_ets,            R"(\)0000FFabc)"_ets,     "\x1B[48;2;0;0;255mabc"_tb                              },

    {""_ets,
     R"(\]2ab\>135cd\}02ef\]9gh)"_ets,            "\x1B[42mab\x1B[48;5;75mcd\x1B[48;5;234mef\x1B[0mgh"_tb },

    // Test interoperability of attributes.
    // NOTE: At a later date, it may be implemented that the algorithm will
    // branch and look for strategies for producing the shortest sequence.
    // In that case, it may be that switching several attributes off is longer
    // than switching to default then re-enabling one attribute.  It also may
    // be determined by environment - different terminals behave differently.
    {""_ets,            R"(\[2\]1a\p-b\p+c)"_ets, "\x1B[32;41ma\x1B[7mb\x1B[27mc"_tb                      },

    // Test unicode output.
    // If a string contains a four-hexdigit unicode code, then
    // it should be output as a unicode character if it can be.
    // This will include commands to change to and from the utf-8
    // character set and also to reset the character set at the end.
    {""_ets,            R"(\U0000)"_ets,          "\x1B%G\x00"_tb                                         },
    {""_ets,            R"(\U0057)"_ets,          "\x1B%GW"_tb                                            },
    {R"(\U0057)"_ets,   R"(\U010E)"_ets,          "\xC4\x8E"_tb                                           },
    {R"(\U0057)"_ets,   R"(\U16B8)"_ets,          "\xE1\x9A\xB8"_tb                                       },

    {R"(\cU\C205)"_ets, R"(\U0057)"_ets,          "\x1B(B\x1B%GW"_tb                                      },
    {R"(\U0057)"_ets,   R"(\cA\C156)"_ets,        "\x1B%@\x1B(A\x9C"_tb                                   },
};

INSTANTIATE_TEST_SUITE_P(
    text_can_be_streamed_to_a_terminal,
    streaming_text,
    ValuesIn(streaming_text_data_table));

TEST_F(a_terminal, can_stream_a_single_element)
{
    terminalpp::element const elem{
        'X', {.foreground_colour_ = terminalpp::graphics::colour::red}};
    terminal_ << elem;

    EXPECT_THAT(channel_.written_, ContainerEq("\x1B[31mX"_tb));
}

namespace {

class a_terminal_that_supports_unicode_in_all_charsets : public a_terminal
{
public:
    a_terminal_that_supports_unicode_in_all_charsets()
      : a_terminal{[] {
            terminalpp::behaviour behaviour;
            behaviour.unicode_in_all_charsets = true;
            return behaviour;
        }()}
    {
    }
};

}  // namespace

TEST_F(
    a_terminal_that_supports_unicode_in_all_charsets,
    skips_charset_switch_before_selecting_utf8_charset)
{
    terminal_ << R"(\cU\C205\U0057)"_ets;
    EXPECT_THAT(channel_.written_, ContainerEq("\x1B(U\xCD\x1B%GW"_tb));
}

namespace {

using write_position_data = std::tuple<
    terminalpp::point,   // Initial cursor position
    terminalpp::string,  // String to write
    terminalpp::point    // Expected terminal position
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

}  // namespace

TEST_P(writing_at_a_position, leaves_the_cursor_at_the_specified_position)
{
    using std::get;

    auto const &params = GetParam();
    auto const &init_position = get<0>(params);
    auto const &text_to_stream = get<1>(params);
    auto const &expected_position = get<2>(params);

    terminal_ << ""_ets << terminalpp::move_cursor(init_position)
              << text_to_stream;
    channel_.written_.clear();

    terminal_ << terminalpp::move_cursor(expected_position);

    // Moving to the position we are already at should yield no required
    // output.
    EXPECT_THAT(channel_.written_, ContainerEq(""_tb));
}

write_position_data const write_position_data_table[] = {
    // Writing within the same row moves the cursor to the right
    {{0, 0}, ""_ets,      {0, 0}},
    {{0, 0}, "x"_ets,     {1, 0}},
    {{0, 0}, "abcde"_ets, {5, 0}},
    {{2, 3}, "abcde"_ets, {7, 3}},
};

INSTANTIATE_TEST_SUITE_P(
    streaming_text_moves_the_cursor,
    writing_at_a_position,
    ValuesIn(write_position_data_table));

}  // namespace
