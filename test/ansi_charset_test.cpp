#include "terminalpp/ansi/charset.hpp"
#include <gtest/gtest.h>

using testing::ValuesIn;

TEST(looking_up_empty_charset, returns_no_charset)
{
    auto const empty_charset = terminalpp::bytes{};
    auto const expected_result = boost::none;

    auto const result = terminalpp::ansi::lookup_charset(empty_charset);
    ASSERT_EQ(expected_result, result);
}

TEST(looking_up_an_unknown_charset, returns_no_charset)
{
    static constexpr terminalpp::byte unknown_character_set[] = { 
        terminalpp::detail::ascii::LOWERCASE_X 
    };

    auto const unknown_charset = terminalpp::bytes{unknown_character_set};
    auto const expected_result = boost::none;

    auto const result = terminalpp::ansi::lookup_charset(unknown_charset);
    ASSERT_EQ(expected_result, result);
}

namespace {

using charset_bytes = std::tuple<
    terminalpp::bytes,         // input character set code
    terminalpp::ansi::charset  // expected character set
>;

class bytes_to_charset
  : public testing::TestWithParam<charset_bytes>
{
};

}

TEST_P(bytes_to_charset, can_be_converted_to_bytes)
{
    using namespace std;

    auto const &param = GetParam();
    auto const &character_set_bytes    = get<0>(param);
    auto const &expected_character_set = get<1>(param);

    auto const result = terminalpp::ansi::lookup_charset(character_set_bytes);
    ASSERT_TRUE(result.is_initialized());
    ASSERT_EQ(expected_character_set, *result);
}

static charset_bytes const charset_bytes_table[] = {
    charset_bytes{ terminalpp::ansi::CHARSET_DEC,                  terminalpp::ansi::charset::dec                        },
    charset_bytes{ terminalpp::ansi::CHARSET_DEC_SUPPLEMENTARY,    terminalpp::ansi::charset::dec_supplementary          },
    charset_bytes{ terminalpp::ansi::CHARSET_DEC_SUPPLEMENTARY_GR, terminalpp::ansi::charset::dec_supplementary_graphics },
    charset_bytes{ terminalpp::ansi::CHARSET_DEC_TECHNICAL,        terminalpp::ansi::charset::dec_technical              },
    charset_bytes{ terminalpp::ansi::CHARSET_UK,                   terminalpp::ansi::charset::uk                         },
    charset_bytes{ terminalpp::ansi::CHARSET_US_ASCII,             terminalpp::ansi::charset::us_ascii                   },
    charset_bytes{ terminalpp::ansi::CHARSET_DUTCH,                terminalpp::ansi::charset::dutch                      },
    charset_bytes{ terminalpp::ansi::CHARSET_FINNISH,              terminalpp::ansi::charset::finnish                    },
    charset_bytes{ terminalpp::ansi::CHARSET_FINNISH_ALT,          terminalpp::ansi::charset::finnish                    },
    charset_bytes{ terminalpp::ansi::CHARSET_FRENCH,               terminalpp::ansi::charset::french                     },
    charset_bytes{ terminalpp::ansi::CHARSET_FRENCH_ALT,           terminalpp::ansi::charset::french                     },
    charset_bytes{ terminalpp::ansi::CHARSET_FRENCH_CANADIAN,      terminalpp::ansi::charset::french_canadian            },
    charset_bytes{ terminalpp::ansi::CHARSET_FRENCH_CANADIAN_ALT,  terminalpp::ansi::charset::french_canadian            },
    charset_bytes{ terminalpp::ansi::CHARSET_GERMAN,               terminalpp::ansi::charset::german                     },
    charset_bytes{ terminalpp::ansi::CHARSET_ITALIAN,              terminalpp::ansi::charset::italian                    },
    charset_bytes{ terminalpp::ansi::CHARSET_DANISH,               terminalpp::ansi::charset::danish                     },
    charset_bytes{ terminalpp::ansi::CHARSET_DANISH_ALT_1,         terminalpp::ansi::charset::danish                     },
    charset_bytes{ terminalpp::ansi::CHARSET_DANISH_ALT_2,         terminalpp::ansi::charset::danish                     },
    charset_bytes{ terminalpp::ansi::CHARSET_PORTUGUESE,           terminalpp::ansi::charset::portuguese                 },
};

INSTANTIATE_TEST_SUITE_P(
    bytes_can_be_converted_to_a_character_set,
    bytes_to_charset,
    ValuesIn(charset_bytes_table)
);
