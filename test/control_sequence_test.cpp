#include <gtest/gtest.h>
#include <terminalpp/control_sequence.hpp>

#include <tuple>

using testing::ValuesIn;
using namespace terminalpp::literals;  // NOLINT

namespace {

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
    auto const &[seq, expected_string] = GetParam();

    std::stringstream stream;
    std::ostream &out = stream;

    out << seq;
    ASSERT_EQ(expected_string, stream.str());
}

constexpr terminalpp::control_sequence default_sequence = {};

control_sequence_test_data const control_sequence_strings[] = {
    // A default sequence should just print out its wrapper
    {terminalpp::control_sequence{},                                    "control_sequence[]"},

    // A control sequence with only the initiator changed outputs only the
    // initiator
    {terminalpp::control_sequence{.initiator = '['},
     "control_sequence[initiator:'[']"                                                      },
    {terminalpp::control_sequence{.initiator = '?'},
     "control_sequence[initiator:'?']"                                                      },

    // A control sequence with only the command changed outputs only the command
    {terminalpp::control_sequence{
         .initiator = default_sequence.initiator, .command = 'm'},
     "control_sequence[command:'m']"                                                        },
    {terminalpp::control_sequence{
         .initiator = default_sequence.initiator, .command = 'H'},
     "control_sequence[command:'H']"                                                        },

    // A control sequence with only the meta flag raised outputs only the meta
    // flag
    {terminalpp::control_sequence{
         .initiator = default_sequence.initiator,
         .command = default_sequence.command,
         .meta = true},
     "control_sequence[meta]"                                                               },

    // A control sequence with only one argument outputs the argument
    {terminalpp::control_sequence{
         .initiator = default_sequence.initiator,
         .command = default_sequence.command,
         .meta = default_sequence.meta,
         .arguments = {"arg0"_tb}},
     R"(control_sequence[args:"arg0"])"                                                     },

    // A control sequence with multiple arguments outputs the arguments
    // separated by ;
    {terminalpp::control_sequence{
         .initiator = default_sequence.initiator,
         .command = default_sequence.command,
         .meta = default_sequence.meta,
         .arguments = {"arg0"_tb, "arg1"_tb}},
     R"(control_sequence[args:"arg0;arg1"])"                                                },
    {terminalpp::control_sequence{
         .initiator = default_sequence.initiator,
         .command = default_sequence.command,
         .meta = default_sequence.meta,
         .arguments = {"arg0"_tb, "arg1"_tb, "arg2"_tb}},
     R"(control_sequence[args:"arg0;arg1;arg2"])"                                           },

    // control sequences with only an extender output only the extender
    {terminalpp::control_sequence{
         .initiator = default_sequence.initiator,
         .command = default_sequence.command,
         .meta = default_sequence.meta,
         .arguments = default_sequence.arguments,
         .extender = '*'},
     "control_sequence[extender:'*']"                                                       },
    {terminalpp::control_sequence{
         .initiator = default_sequence.initiator,
         .command = default_sequence.command,
         .meta = default_sequence.meta,
         .arguments = default_sequence.arguments,
         .extender = '?'},
     "control_sequence[extender:'?']"                                                       },

    // Control sequences with multiple active fields separate them with commas
    {terminalpp::control_sequence{
         .initiator = '[',
         .command = 'H',
         .meta = true,
         .arguments = {"29"_tb},
         .extender = '?'},
     R"(control_sequence[initiator:'[', command:'H', meta, args:"29", extender:'?'])"       },

    {terminalpp::control_sequence{
         .initiator = '[',
         .command = 'H',
         .meta = default_sequence.meta,
         .arguments = {"29"_tb},
         .extender = '?'},
     R"(control_sequence[initiator:'[', command:'H', args:"29", extender:'?'])"             },
};

INSTANTIATE_TEST_SUITE_P(
    control_sequences_can_be_streamed_to_an_ostream,
    control_sequences_with_strings,
    ValuesIn(control_sequence_strings));

}  // namespace
