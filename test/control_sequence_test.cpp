#include <gtest/gtest.h>
#include <terminalpp/control_sequence.hpp>

#include <tuple>

using testing::ValuesIn;
using namespace terminalpp::literals;  // NOLINT

TEST(a_default_constructed_control_sequence, has_a_known_value)
{
    terminalpp::control_sequence seq;

    ASSERT_EQ('\0', seq.initiator);
    ASSERT_EQ('\0', seq.command);
    ASSERT_FALSE(seq.meta);
    ASSERT_TRUE(seq.arguments.empty());
    ASSERT_EQ('\0', seq.extender);
}

using control_sequence_test_data = std::tuple<
    terminalpp::control_sequence,  // input data
    std::string                    // expected output
    >;

class control_sequences_with_strings
  : public testing::TestWithParam<control_sequence_test_data>
{
};

TEST_P(control_sequences_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &seq = std::get<0>(param);
    auto const &expected_string = std::get<1>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << seq;
    ASSERT_EQ(expected_string, stream.str());
}

static terminalpp::control_sequence const default_sequence = {};

static control_sequence_test_data const control_sequence_strings[] = {
  // A default sequence should just print out its wrapper
    control_sequence_test_data{
                               terminalpp::control_sequence{},                                "control_sequence[]"             },

 // A control sequence with only the initiator changed outputs only the
  // initiator
    control_sequence_test_data{
                               terminalpp::control_sequence{'['},                             "control_sequence[initiator:'[']"},
    control_sequence_test_data{
                               terminalpp::control_sequence{'?'},                             "control_sequence[initiator:'?']"},

 // A control sequence with only the command changed outputs only the command
    control_sequence_test_data{
                               terminalpp::control_sequence{default_sequence.initiator, 'm'},
                               "control_sequence[command:'m']"                                                                 },
    control_sequence_test_data{
                               terminalpp::control_sequence{default_sequence.initiator, 'H'},
                               "control_sequence[command:'H']"                                                                 },

 // A control sequence with only the meta flag raised outputs only the meta
  // flag
    control_sequence_test_data{
                               terminalpp::control_sequence{
            default_sequence.initiator, default_sequence.command, true},
                               "control_sequence[meta]"                                                                        },

 // A control sequence with only one argument outputs the argument
    control_sequence_test_data{
                               terminalpp::control_sequence{
            default_sequence.initiator,
            default_sequence.command,
            default_sequence.meta,
            {"arg0"_tb}},
                               R"(control_sequence[args:"arg0"])"                                                              },

 // A control sequence with multiple arguments outputs the arguments
  // separated by ;
    control_sequence_test_data{
                               terminalpp::control_sequence{
            default_sequence.initiator,
            default_sequence.command,
            default_sequence.meta,
            {"arg0"_tb, "arg1"_tb}},
                               R"(control_sequence[args:"arg0;arg1"])"                                                         },
    control_sequence_test_data{
                               terminalpp::control_sequence{
            default_sequence.initiator,
            default_sequence.command,
            default_sequence.meta,
            {"arg0"_tb, "arg1"_tb, "arg2"_tb}},
                               R"(control_sequence[args:"arg0;arg1;arg2"])"                                                    },

 // control sequences with only an extender output only the extender
    control_sequence_test_data{
                               terminalpp::control_sequence{
            default_sequence.initiator,
            default_sequence.command,
            default_sequence.meta,
            default_sequence.arguments,
            '*'},
                               "control_sequence[extender:'*']"                                                                },
    control_sequence_test_data{
                               terminalpp::control_sequence{
            default_sequence.initiator,
            default_sequence.command,
            default_sequence.meta,
            default_sequence.arguments,
            '?'},
                               "control_sequence[extender:'?']"                                                                },

 // Control sequences with multiple active fields separate them with commas
    control_sequence_test_data{
                               terminalpp::control_sequence{'[', 'H', true, {"29"_tb}, '?'},
                               R"(control_sequence[initiator:'[', command:'H', meta, args:"29", extender:'?'])"                },

    control_sequence_test_data{
                               terminalpp::control_sequence{
            '[', 'H', default_sequence.meta, {"29"_tb}, '?'},
                               R"(control_sequence[initiator:'[', command:'H', args:"29", extender:'?'])"                      },
};

INSTANTIATE_TEST_SUITE_P(
    control_sequences_can_be_streamed_to_an_ostream,
    control_sequences_with_strings,
    ValuesIn(control_sequence_strings));
