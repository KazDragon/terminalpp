#include "terminalpp/character_set.hpp"
#include <gtest/gtest.h>
#include <tuple>

using testing::ValuesIn;

using character_set_string = std::tuple<
    terminalpp::character_set,
    std::string
>;

class character_sets_with_strings
    : public testing::TestWithParam<character_set_string>
{
};

TEST_P(character_sets_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &param = GetParam();
    auto const &set = std::get<0>(param);
    auto const &expected_string = std::get<1>(param);

    std::stringstream stream;
    std::ostream &out = stream;

    out << terminalpp::character_set(set);
    ASSERT_EQ(expected_string, stream.str());
}

static character_set_string const character_set_strings[] = {
  character_set_string{ terminalpp::ansi::charset::dec,                        "dec",   },
  character_set_string{ terminalpp::ansi::charset::dec_supplementary,          "dec+"   },
  character_set_string{ terminalpp::ansi::charset::dec_supplementary_graphics, "dec+gr" },
  character_set_string{ terminalpp::ansi::charset::dec_technical,              "dectec" },
  character_set_string{ terminalpp::ansi::charset::uk,                         "en_uk"  },
  character_set_string{ terminalpp::ansi::charset::us_ascii,                   "en_us"  },
  character_set_string{ terminalpp::ansi::charset::dutch,                      "nl"     },
  character_set_string{ terminalpp::ansi::charset::finnish,                    "fi"     },
  character_set_string{ terminalpp::ansi::charset::french,                     "fr"     },
  character_set_string{ terminalpp::ansi::charset::french_canadian,            "fr_ca"  },
  character_set_string{ terminalpp::ansi::charset::german,                     "de"     },
  character_set_string{ terminalpp::ansi::charset::italian,                    "it"     },
  character_set_string{ terminalpp::ansi::charset::danish,                     "da"     },
  character_set_string{ terminalpp::ansi::charset::portuguese,                 "pt"     },
  character_set_string{ terminalpp::ansi::charset::spanish,                    "es"     },
  character_set_string{ terminalpp::ansi::charset::swedish,                    "su"     },
  character_set_string{ terminalpp::ansi::charset::swiss,                      "de_ch"  },
  character_set_string{ terminalpp::ansi::charset::sco,                        "sco"    },
  character_set_string{ terminalpp::ansi::charset::utf8,                       "u"      },
};

INSTANTIATE_TEST_CASE_P(
    character_sets_can_be_streamed_to_an_ostream,
    character_sets_with_strings,
    ValuesIn(character_set_strings)
);
