#include "terminalpp/string.hpp"

#include "terminalpp/effect.hpp"
#include "terminalpp/element.hpp"
#include "terminalpp/glyph.hpp"
#include "terminalpp/graphics.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <limits>
#include <unordered_set>
#include <cassert>

using namespace terminalpp::literals;  // NOLINT
using namespace std::string_literals;
using testing::ValuesIn;

TEST(string_test, a_default_constructed_string_is_empty)
{
    terminalpp::string str;
    ASSERT_TRUE(str.empty());

    []() consteval {
        terminalpp::string const str;
        assert(str.empty());
    }();
}

TEST(string_test, a_default_constructed_string_has_size_0)
{
    terminalpp::string str;
    ASSERT_EQ(0U, str.size());

    []() consteval {
        terminalpp::string const str;
        assert(str.size() == 0U);
    }();
}

TEST(
    string_test,
    a_default_constructed_string_has_a_max_size_of_size_t_max_value)
{
    terminalpp::string str;
    ASSERT_EQ(
        std::numeric_limits<terminalpp::string::size_type>::max(),
        str.max_size());

    []() consteval {
        terminalpp::string const str;
        assert(
            str.max_size()
            == std::numeric_limits<terminalpp::string::size_type>::max());
    }();
}

TEST(string_test, can_construct_from_string_and_attribute)
{
    terminalpp::attribute attr;
    attr.polarity_ = terminalpp::graphics::polarity::negative;

    auto str = [](terminalpp::string const &str) {
        return str;
    }(terminalpp::string(std::string("xy"), attr));

    ASSERT_EQ(size_t{2}, str.size());
    ASSERT_EQ(terminalpp::glyph('x'), str[0].glyph_);
    ASSERT_EQ(attr, str[0].attribute_);
    ASSERT_EQ(terminalpp::glyph('y'), str[1].glyph_);
    ASSERT_EQ(attr, str[1].attribute_);

    []() consteval {
        terminalpp::attribute attr;
        attr.polarity_ = terminalpp::graphics::polarity::negative;

        terminalpp::string const str{"xy", attr};
        assert(str.size() == 2U);
        assert(str[0].glyph_ == terminalpp::glyph{'x'});
        assert(str[0].attribute_ == attr);
        assert(str[1].glyph_ == terminalpp::glyph{'y'});
        assert(str[1].attribute_ == attr);
    }();
}

TEST(string_test, can_aggregate_initialize_from_string_and_attribute)
{
    terminalpp::attribute attr;
    attr.polarity_ = terminalpp::graphics::polarity::negative;

    auto str = [](terminalpp::string const &str) { return str; }({"xy", attr});

    ASSERT_EQ(size_t{2}, str.size());
    ASSERT_EQ(terminalpp::glyph('x'), str[0].glyph_);
    ASSERT_EQ(attr, str[0].attribute_);
    ASSERT_EQ(terminalpp::glyph('y'), str[1].glyph_);
    ASSERT_EQ(attr, str[1].attribute_);

    []() consteval {
        terminalpp::attribute attr;
        attr.polarity_ = terminalpp::graphics::polarity::negative;

        terminalpp::string const str{"xy", attr};
        assert(str.size() == 2U);
        assert(str[0].glyph_ == terminalpp::glyph{'x'});
        assert(str[0].attribute_ == attr);
        assert(str[1].glyph_ == terminalpp::glyph{'y'});
        assert(str[1].attribute_ == attr);
    }();
}

TEST(string_test, converting_empty_tstring_yields_plain_empty_string)
{
    terminalpp::string tstr;
    std::string str = terminalpp::to_string(tstr);
    std::string expected;

    ASSERT_EQ(expected, str);

    []() consteval {
        terminalpp::string const tstr;
        std::string const str = terminalpp::to_string(tstr);
        std::string const expected;
        assert(str == expected);
    }();
}

TEST(string_test, converting_tstring_with_attributes_yields_plain_string)
{
    auto tstr = R"(\[1Test\]2String)"_ets;
    auto str = terminalpp::to_string(tstr);

    std::string expected = "TestString";

    ASSERT_EQ(expected, str);
}

TEST(
    string_test,
    converting_tstring_with_unicode_values_yields_plain_string_with_unicode_values)
{
    auto tstr = R"(Test\U010EString)"_ets;
    auto str = terminalpp::to_string(tstr);

    std::string expected = "Test\xC4\x8EString";

    ASSERT_EQ(expected, str);
}

TEST(
    string_test,
    constructing_a_string_of_no_elements_constructs_an_empty_string)
{
    static auto const space = terminalpp::element(' ');
    ASSERT_EQ(terminalpp::string(0, space), terminalpp::string());

    []() consteval {
        terminalpp::element const space{' '};
        assert((terminalpp::string(0, space) == terminalpp::string{}));
    }();
}

TEST(
    string_test,
    constructing_a_string_with_a_size_and_an_element_constructs_a_string_of_that_many_elements)
{
    static auto const elem = terminalpp::element('?');
    static auto const size = static_cast<std::size_t>(36);
    static auto const expected = [&]() {
        terminalpp::string result;
        for (std::size_t index = 0; index < size; ++index)
        {
            result += elem;
        }

        return result;
    }();

    ASSERT_EQ(terminalpp::string(size, elem), expected);

    []() consteval {
        terminalpp::element const elem{'?'};
        std::size_t const size{36U};
        terminalpp::string result;
        auto const expected = [&] {
            terminalpp::string result;
            for (std::size_t index = 0; index < size; ++index)
            {
                result += elem;
            }

            return result;
        }();

        assert(terminalpp::string(size, elem) == expected);
    }();
}

TEST(string_test, a_string_with_data_is_not_empty)
{
    terminalpp::string const str("abcde"_ts);
    ASSERT_FALSE(str.empty());

    []() consteval {
        terminalpp::string const str{"abcde"};
        assert(!str.empty());
    }();
}

TEST(string_test, a_string_with_data_has_the_size_of_the_number_of_elements)
{
    terminalpp::string const str0("abcde"_ts);
    ASSERT_EQ(5U, str0.size());

    terminalpp::string const str1(R"(aard\[1vark)"_ets);
    ASSERT_EQ(8U, str1.size());
}

TEST(string_test, can_iterate_over_a_string)
{
    terminalpp::string str = "abcde"_ts;
    std::string result;

    std::ranges::transform(
        str, std::back_inserter(result), [](terminalpp::element const &elem) {
            return static_cast<char>(elem.glyph_.character_);
        });

    std::string const expected = "abcde";
    ASSERT_EQ(expected, result);

    []() consteval {
        terminalpp::string str = "abcde"_ts;
        std::string result;

        std::ranges::transform(
            str,
            std::back_inserter(result),
            [](terminalpp::element const &elem) {
                return static_cast<char>(elem.glyph_.character_);
            });

        assert(result == "abcde"_ts);
    }();
}

TEST(string_test, can_iterate_over_a_const_string)
{
    terminalpp::string const str = "abcde"_ts;
    std::string result;

    std::ranges::transform(
        str, std::back_inserter(result), [](terminalpp::element const &elem) {
            return static_cast<char>(elem.glyph_.character_);
        });

    std::string const expected = "abcde";
    ASSERT_EQ(expected, result);

    []() consteval {
        terminalpp::string const str = "abcde"_ts;
        std::string result;

        std::ranges::transform(
            str,
            std::back_inserter(result),
            [](terminalpp::element const &elem) {
                return static_cast<char>(elem.glyph_.character_);
            });

        assert(result == "abcde"_ts);
    }();
}

TEST(string_test, can_iterate_backwards_over_a_string)
{
    terminalpp::string str = "abcde"_ts;
    std::string result;

    std::transform(  // NOLINT
        str.rbegin(),
        str.rend(),
        std::back_inserter(result),
        [](terminalpp::element const &elem) {
            return static_cast<char>(elem.glyph_.character_);
        });

    std::string const expected = "edcba";
    ASSERT_EQ(expected, result);

    []() consteval {
        terminalpp::string str = "abcde"_ts;
        std::string result;

        std::transform(  // NOLINT
            str.rbegin(),
            str.rend(),
            std::back_inserter(result),
            [](terminalpp::element const &elem) {
                return static_cast<char>(elem.glyph_.character_);
            });

        assert(result == "edcba"_ts);
    }();
}

TEST(string_test, can_iterate_backwards_over_a_const_string)
{
    terminalpp::string const str = "abcde"_ets;
    std::string result;

    std::transform(  // NOLINT
        str.rbegin(),
        str.rend(),
        std::back_inserter(result),
        [](terminalpp::element const &elem) {
            return static_cast<char>(elem.glyph_.character_);
        });

    std::string const expected = "edcba";
    ASSERT_EQ(expected, result);

    []() consteval {
        terminalpp::string const str = "abcde"_ts;
        std::string result;

        std::transform(  // NOLINT
            str.rbegin(),
            str.rend(),
            std::back_inserter(result),
            [](terminalpp::element const &elem) {
                return static_cast<char>(elem.glyph_.character_);
            });

        assert(result == "edcba"_ts);
    }();
}

TEST(string_test, can_append_characters_to_a_string)
{
    terminalpp::string str = "tes";
    str += 't';

    auto const expected = "test"_ets;
    ASSERT_EQ(expected, str);

    []() consteval {
        terminalpp::string str{"tes"s};
        str += 't';

        terminalpp::string const expected = "test"s;
        assert(str == expected);
    }();
}

TEST(string_test, can_append_bytes_to_a_string)
{
    terminalpp::string str = "tes";
    str += 't'_tb;

    auto const expected = "test"_ets;
    ASSERT_EQ(expected, str);
}

TEST(string_test, can_append_c_strings_to_a_string)
{
    terminalpp::string str = "tes";
    str += "t";

    auto const expected = "test"_ets;
    ASSERT_EQ(expected, str);
}

TEST(string_test, can_append_std_strings_to_a_string)
{
    terminalpp::string str = "tes";
    str += std::string("t");

    auto const expected = "test"_ets;
    ASSERT_EQ(expected, str);

    []() consteval {
        terminalpp::string str = "tes";
        str += std::string("t");

        auto const expected = "test"_ts;
        assert(str == expected);
    }();
}

TEST(string_test, can_append_terminal_strings_to_a_string)
{
    terminalpp::string str = "tes";
    str += terminalpp::string("t");

    auto const expected = "test"_ets;
    ASSERT_EQ(expected, str);
}

using string_string = std::tuple<terminalpp::string, std::string>;

class strings_with_strings : public testing::TestWithParam<string_string>
{
};

TEST_P(strings_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &element = std::get<0>(param);
    auto const &expected_string = std::get<1>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << element;
    ASSERT_EQ(expected_string, stream.str());
}

static string_string const string_strings[] = {
    string_string{{},                {}                                                                     },
    string_string{"c"_ets,           "element[glyph[c]]"                                                    },
    string_string{
                  R"(\[1r\]2g)"_ets, "element[glyph[r],attribute[foreground[red]]],"
        "element[glyph[g],attribute[foreground[red],background[green]]]"}
};

INSTANTIATE_TEST_SUITE_P(
    strings_can_be_streamed_to_an_ostream,
    strings_with_strings,
    ValuesIn(string_strings));

using string_relops_data = std::tuple<
    terminalpp::string,  // lhs
    terminalpp::string,  // rhs
    bool,                // less
    bool,                // less-equal
    bool,                // equal
    bool,                // greater-equal
    bool                 // greater
    >;

class strings_compare : public testing::TestWithParam<string_relops_data>
{
};

TEST_P(strings_compare, according_to_relops)
{
    auto const &param = GetParam();
    auto const &lhs = std::get<0>(param);
    auto const &rhs = std::get<1>(param);
    auto const &less = std::get<2>(param);
    auto const &less_equal = std::get<3>(param);
    auto const &equal = std::get<4>(param);
    auto const &greater_equal = std::get<5>(param);
    auto const &greater = std::get<6>(param);

    ASSERT_EQ(less, lhs < rhs);
    ASSERT_EQ(less_equal, lhs <= rhs);
    ASSERT_EQ(equal, lhs == rhs);
    ASSERT_EQ(!equal, lhs != rhs);
    ASSERT_EQ(greater_equal, lhs >= rhs);
    ASSERT_EQ(greater, lhs > rhs);
}

INSTANTIATE_TEST_SUITE_P(
    using_relational_operators,
    strings_compare,
    ValuesIn(std::vector<string_relops_data>{
        // Basic string comparisons
        string_relops_data{"",               "",               false, true,  true,  true,  false},

        string_relops_data{"",               "a",              true,  true,  false, false, false},
        string_relops_data{"a",              "",               false, false, false, true,  true },

        string_relops_data{"a",              "b",              true,  true,  false, false, false},
        string_relops_data{"b",              "a",              false, false, false, true,  true },
        string_relops_data{"b",              "b",              false, true,  true,  true,  false},

        string_relops_data{"ad",             "b",              true,  true,  false, false, false},
        string_relops_data{"b",              "ad",             false, false, false, true,  true },

        // String comparisons based on attributes
        // o Foreground colour
        //   o Low colour
        string_relops_data{"a",              "\\[1a"_ets,      false, false, false, true,  true },
        string_relops_data{"\\[1a"_ets,      "a",              true,  true,  false, false, false},
        string_relops_data{
                           "\\[1a"_ets,      "\\[1a"_ets,      false, true,  true,  true,  false},
        string_relops_data{
                           "\\[1a"_ets,      "\\[2a"_ets,      true,  true,  false, false, false},

        //   o High colour
        string_relops_data{"a",              "\\<001a"_ets,    true,  true,  false, false, false},
        string_relops_data{"\\<001a"_ets,    "a",              false, false, false, true,  true },
        string_relops_data{
                           "\\<001a"_ets,    "\\<001a"_ets,    false, true,  true,  true,  false},
        string_relops_data{
                           "\\<001a"_ets,    "\\<002a"_ets,    true,  true,  false, false, false},

        //   o Greyscale colour
        string_relops_data{"a",              "\\{01a"_ets,     true,  true,  false, false, false},
        string_relops_data{"\\{01a"_ets,     "a",              false, false, false, true,  true },
        string_relops_data{
                           "\\{01a"_ets,     "\\{01a"_ets,     false, true,  true,  true,  false},
        string_relops_data{
                           "\\{01a"_ets,     "\\{02a"_ets,     true,  true,  false, false, false},

        //   o True colour
        string_relops_data{
                           "a"_ets,          "\\(010101a"_ets, true,  true,  false, false, false},
        string_relops_data{
                           "\\(010101a"_ets, "a"_ets,          false, false, false, true,  true },
        string_relops_data{
                           "\\(010101a"_ets, "\\(010101a"_ets, false, true,  true,  true,  false},

        string_relops_data{
                           "\\(010101a"_ets, "\\(010102a"_ets,
                           true,                                      true,
                           false,                                                   false,
                           false                                                                },
        string_relops_data{
                           "\\(010101a"_ets, "\\(010201a"_ets,
                           true,                                      true,
                           false,                                                   false,
                           false                                                                },
        string_relops_data{
                           "\\(010101a"_ets, "\\(000101a"_ets,
                           false,                                     false,
                           false,                                                   true,
                           true                                                                 },
        string_relops_data{
                           "\\(010101a"_ets, "\\(010001a"_ets,
                           false,                                     false,
                           false,                                                   true,
                           true                                                                 },
        string_relops_data{
                           "\\(010101a"_ets, "\\(010100a"_ets,
                           false,                                     false,
                           false,                                                   true,
                           true                                                                 },
        string_relops_data{
                           "\\(010001a"_ets, "\\(010100a"_ets,
                           true,                                      true,
                           false,                                                   false,
                           false                                                                },

        // o Background colour
        //   o Low colour
        string_relops_data{"a",              "\\]1a"_ets,      false, false, false, true,  true },
        string_relops_data{"\\]1a"_ets,      "a",              true,  true,  false, false, false},
        string_relops_data{
                           "\\]1a"_ets,      "\\]1a"_ets,      false, true,  true,  true,  false},
        string_relops_data{
                           "\\]1a"_ets,      "\\]2a"_ets,      true,  true,  false, false, false},

        //   o High colour
        string_relops_data{"a",              "\\>001a"_ets,    true,  true,  false, false, false},
        string_relops_data{"\\>001a"_ets,    "a",              false, false, false, true,  true },
        string_relops_data{
                           "\\>001a"_ets,    "\\>001a"_ets,    false, true,  true,  true,  false},
        string_relops_data{
                           "\\>001a"_ets,    "\\>002a"_ets,    true,  true,  false, false, false},

        //   o Greyscale colour
        string_relops_data{"a",              "\\}01a"_ets,     true,  true,  false, false, false},
        string_relops_data{"\\}01a"_ets,     "a",              false, false, false, true,  true },
        string_relops_data{
                           "\\}01a"_ets,     "\\}01a"_ets,     false, true,  true,  true,  false},
        string_relops_data{
                           "\\}01a"_ets,     "\\}02a"_ets,     true,  true,  false, false, false},

        //   o True colour
        string_relops_data{
                           "a"_ets,          "\\)010101a"_ets, true,  true,  false, false, false},
        string_relops_data{
                           "\\)010101a"_ets, "a"_ets,          false, false, false, true,  true },
        string_relops_data{
                           "\\)010101a"_ets, "\\)010101a"_ets, false, true,  true,  true,  false},

        string_relops_data{
                           "\\)010101a"_ets, "\\)010102a"_ets,
                           true,                                      true,
                           false,                                                   false,
                           false                                                                },
        string_relops_data{
                           "\\)010101a"_ets, "\\)010201a"_ets,
                           true,                                      true,
                           false,                                                   false,
                           false                                                                },
        string_relops_data{
                           "\\)010101a"_ets, "\\)000101a"_ets,
                           false,                                     false,
                           false,                                                   true,
                           true                                                                 },
        string_relops_data{
                           "\\)010101a"_ets, "\\)010001a"_ets,
                           false,                                     false,
                           false,                                                   true,
                           true                                                                 },
        string_relops_data{
                           "\\)010101a"_ets, "\\)010100a"_ets,
                           false,                                     false,
                           false,                                                   true,
                           true                                                                 },
        string_relops_data{
                           "\\)010001a"_ets, "\\)010100a"_ets,
                           true,                                      true,
                           false,                                                   false,
                           false                                                                },

        // o Intensity
        string_relops_data{"a",              "\\i>a"_ets,      false, false, false, true,  true },
        string_relops_data{"\\i>a"_ets,      "a",              true,  true,  false, false, false},
        string_relops_data{
                           "\\i>a"_ets,      "\\i>a"_ets,      false, true,  true,  true,  false},
        string_relops_data{
                           "\\i<a"_ets,      "\\i>a"_ets,      false, false, false, true,  true },

        // o Underlining
        string_relops_data{"a",              "\\u+a"_ets,      false, false, false, true,  true },
        string_relops_data{"\\u+a"_ets,      "a",              true,  true,  false, false, false},
        string_relops_data{
                           "\\u+a"_ets,      "\\u+a"_ets,      false, true,  true,  true,  false},
        string_relops_data{
                           "\\u-a"_ets,      "\\u+a"_ets,      false, false, false, true,  true },

        // o Polarity
        string_relops_data{"a",              "\\p-a"_ets,      false, false, false, true,  true },
        string_relops_data{"\\p-a"_ets,      "a",              true,  true,  false, false, false},
        string_relops_data{
                           "\\p-a"_ets,      "\\p-a"_ets,      false, true,  true,  true,  false},
        string_relops_data{
                           "\\p+a"_ets,      "\\p-a"_ets,      false, false, false, true,  true },

        // o Blinking (TODO - currently there is no shortcut for blinking)

        // o Character sets
        string_relops_data{"a",              "\\cAa"_ets,      false, false, false, true,  true },
        string_relops_data{"\\cAa"_ets,      "a",              true,  true,  false, false, false},
        string_relops_data{
                           "\\cAa"_ets,      "\\cAa"_ets,      false, true,  true,  true,  false},

        string_relops_data{"a",              "\\c4a"_ets,      true,  true,  false, false, false},
        string_relops_data{"\\c4a"_ets,      "a",              false, false, false, true,  true },
        string_relops_data{
                           "\\c4a"_ets,      "\\c4a"_ets,      false, true,  true,  true,  false},

        // o Unicode characters
        string_relops_data{"a",              "\\U0061"_ets,    true,  true,  false, false, false},
        string_relops_data{"\\U0061"_ets,    "a",              false, false, false, true,  true },
        string_relops_data{
                           "\\U0061"_ets,    "\\U0061"_ets,    false, true,  true,  true,  false},
        string_relops_data{
                           "\\U0061"_ets,    "\\U0062"_ets,    true,  true,  false, false, false},
        string_relops_data{
                           "\\U0061"_ets,    "\\UFFFF"_ets,    true,  true,  false, false, false},
}));

TEST(a_string, can_be_inserted_into_an_unordered_set)
{
    std::unordered_set<terminalpp::string> s{""_ets};
}