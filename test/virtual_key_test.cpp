#include "terminalpp/virtual_key.hpp"
#include <gtest/gtest.h>
#include <tuple>

using testing::ValuesIn;
using namespace terminalpp::literals;

TEST(a_default_constructed_vk, has_default_members)
{
    terminalpp::virtual_key vk;

    ASSERT_EQ(terminalpp::vk::nul, vk.key);
    ASSERT_EQ(terminalpp::vk_modifier::none, vk.modifiers);
    ASSERT_EQ(0, vk.repeat_count);

    auto *psequence = boost::get<terminalpp::byte>(&vk.sequence);
    ASSERT_NE(nullptr, psequence);
    ASSERT_EQ(0, *psequence);
}

TEST(anding_a_default_vk_modifer, matches_none)
{
    terminalpp::vk_modifier vk_none = terminalpp::vk_modifier::none;
    ASSERT_TRUE(
        (vk_none & terminalpp::vk_modifier::shift)
            == terminalpp::vk_modifier::none);
}

TEST(oring_several_vk_modifiers, matches_only_those_modifiers)
{
    terminalpp::vk_modifier vk_shift_ctrl =
        terminalpp::vk_modifier::shift
      | terminalpp::vk_modifier::ctrl;

    ASSERT_TRUE(
        (vk_shift_ctrl & terminalpp::vk_modifier::shift)
            == terminalpp::vk_modifier::shift);

    ASSERT_TRUE(
        (vk_shift_ctrl & terminalpp::vk_modifier::ctrl)
            == terminalpp::vk_modifier::ctrl);

    ASSERT_TRUE(
        (vk_shift_ctrl & terminalpp::vk_modifier::meta)
            == terminalpp::vk_modifier::none);
}

TEST(or_assigning_vk_modifiers, matches_those_modifiers_orred)
{
    terminalpp::vk_modifier vk = terminalpp::vk_modifier::meta;
    vk |= terminalpp::vk_modifier::shift;

    ASSERT_TRUE(
        vk == (terminalpp::vk_modifier::meta | terminalpp::vk_modifier::shift));
}

TEST(and_assigning_vk_modifiers, matches_intersection)
{
    terminalpp::vk_modifier vk = terminalpp::vk_modifier::shift
                               | terminalpp::vk_modifier::ctrl;

    vk &= (terminalpp::vk_modifier::shift | terminalpp::vk_modifier::meta);

    ASSERT_TRUE(vk == terminalpp::vk_modifier::shift);
}

using virtual_key_test_data = std::tuple<
    terminalpp::virtual_key, // input data
    std::string              // expected output
>;

class virtual_keys_with_strings
  : public testing::TestWithParam<virtual_key_test_data>
{
};

TEST_P(virtual_keys_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &vk    = std::get<0>(param);
    auto const &expected_string = std::get<1>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << vk;
    ASSERT_EQ(expected_string, stream.str());
}

static terminalpp::virtual_key const default_vk = {};

static virtual_key_test_data const virtual_key_strings[] = {
    // A virtual key should just output the wrapper.
    virtual_key_test_data{
        terminalpp::virtual_key{},
        "virtual_key[]"
    },
    // Virtual keys with non-default printable characters should print those out
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::question_mark
        },
        "virtual_key[vk:'?']"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::uppercase_m
        },
        "virtual_key[vk:'M']"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::space
        },
        "virtual_key[vk:' ']"
    },

    // Virtual keys with whitespace characters should print out slash codes
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::lf
        },
        "virtual_key[vk:'\\n']"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::cr
        },
        "virtual_key[vk:'\\r']"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::ht
        },
        "virtual_key[vk:'\\t']"
    },

    // Virtual keys with non-printable control characters should print out
    // the hex code of the value.
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::esc
        },
        "virtual_key[vk:'\\x1B']"
    },

    // Virtual non-ASCII codes should print the name of the key
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::cursor_up
        },
        "virtual_key[vk:cursor_up]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::cursor_down
        },
        "virtual_key[vk:cursor_down]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::cursor_left
        },
        "virtual_key[vk:cursor_left]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::cursor_right
        },
        "virtual_key[vk:cursor_right]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::home
        },
        "virtual_key[vk:home]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::end
        },
        "virtual_key[vk:end]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::ins
        },
        "virtual_key[vk:ins]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::end
        },
        "virtual_key[vk:end]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::pgup
        },
        "virtual_key[vk:pgup]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::pgdn
        },
        "virtual_key[vk:pgdn]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::bt
        },
        "virtual_key[vk:bt]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::enter
        },
        "virtual_key[vk:enter]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::f1
        },
        "virtual_key[vk:f1]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::f2
        },
        "virtual_key[vk:f2]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::f3
        },
        "virtual_key[vk:f3]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::f4
        },
        "virtual_key[vk:f4]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::f5
        },
        "virtual_key[vk:f5]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::f6
        },
        "virtual_key[vk:f6]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::f7
        },
        "virtual_key[vk:f7]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::f8
        },
        "virtual_key[vk:f8]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::f9
        },
        "virtual_key[vk:f9]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::f10
        },
        "virtual_key[vk:f10]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::f11
        },
        "virtual_key[vk:f11]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::f12
        },
        "virtual_key[vk:f12]"
    },
    // etc.

    // Virtual keys with non-default modifiers should print out the modifier
    virtual_key_test_data{
        terminalpp::virtual_key{
            default_vk.key,
            terminalpp::vk_modifier::shift
        },
        "virtual_key[shift]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            default_vk.key,
            terminalpp::vk_modifier::ctrl
        },
        "virtual_key[ctrl]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            default_vk.key,
            terminalpp::vk_modifier::alt
        },
        "virtual_key[alt]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            default_vk.key,
            terminalpp::vk_modifier::meta
        },
        "virtual_key[meta]"
    },

    virtual_key_test_data{
        terminalpp::virtual_key{
            default_vk.key,
            terminalpp::vk_modifier::shift | terminalpp::vk_modifier::ctrl
          | terminalpp::vk_modifier::alt | terminalpp::vk_modifier::meta
        },
        "virtual_key[shift|ctrl|alt|meta]"
    },

    // If the repeat count is non-zero, that should be printed out
    virtual_key_test_data{
        terminalpp::virtual_key{
            default_vk.key,
            default_vk.modifiers,
            1
        },
        "virtual_key[repeat:1]"
    },
    virtual_key_test_data{
        terminalpp::virtual_key{
            default_vk.key,
            default_vk.modifiers,
            23
        },
        "virtual_key[repeat:23]"
    },

    // If the received data is a character, that should be printed out
    virtual_key_test_data{
        terminalpp::virtual_key{
            default_vk.key,
            default_vk.modifiers,
            default_vk.repeat_count,
            'Z'
        },
        "virtual_key[seq:Z]"
    },

    // If the received data is a sequence, that should be printed out
    virtual_key_test_data{
        terminalpp::virtual_key{
            default_vk.key,
            default_vk.modifiers,
            default_vk.repeat_count,
            terminalpp::control_sequence{
                '[',
                'H',
                false,
                { {"23"_tb} }
            }
        },
        "virtual_key[seq:control_sequence[initiator:'[', command:'H', args:\"23\"]]"
    },

    // If we receive several fields, they should be separated with commas
    virtual_key_test_data{
        terminalpp::virtual_key{
            terminalpp::vk::uppercase_a,
            terminalpp::vk_modifier::shift,
            17,
            'A'
        },
        "virtual_key[vk:'A', shift, repeat:17, seq:A]"
    },
};

INSTANTIATE_TEST_SUITE_P(
    virtual_keys_can_be_streamed_to_an_ostream,
    virtual_keys_with_strings,
    ValuesIn(virtual_key_strings)
);
