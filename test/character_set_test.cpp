#include "terminalpp/character_set.hpp"

#include <gtest/gtest.h>

#include <tuple>
#include <unordered_set>

using testing::ValuesIn;

namespace {

using character_set_string = std::tuple<terminalpp::character_set, std::string>;

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

character_set_string const character_set_strings[] = {
    // clang-format off
  character_set_string{ terminalpp::charset::dec,                        "dec",   },
  character_set_string{ terminalpp::charset::dec_supplementary,          "dec+"   },
  character_set_string{ terminalpp::charset::dec_supplementary_graphics, "dec+gr" },
  character_set_string{ terminalpp::charset::dec_technical,              "dectec" },
  character_set_string{ terminalpp::charset::uk,                         "en_uk"  },
  character_set_string{ terminalpp::charset::us_ascii,                   "en_us"  },
  character_set_string{ terminalpp::charset::dutch,                      "nl"     },
  character_set_string{ terminalpp::charset::finnish,                    "fi"     },
  character_set_string{ terminalpp::charset::french,                     "fr"     },
  character_set_string{ terminalpp::charset::french_canadian,            "fr_ca"  },
  character_set_string{ terminalpp::charset::german,                     "de"     },
  character_set_string{ terminalpp::charset::italian,                    "it"     },
  character_set_string{ terminalpp::charset::danish,                     "da"     },
  character_set_string{ terminalpp::charset::portuguese,                 "pt"     },
  character_set_string{ terminalpp::charset::spanish,                    "es"     },
  character_set_string{ terminalpp::charset::swedish,                    "su"     },
  character_set_string{ terminalpp::charset::swiss,                      "de_ch"  },
  character_set_string{ terminalpp::charset::sco,                        "sco"    },
  character_set_string{ terminalpp::charset::utf8,                       "u"      },
    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(
    character_sets_can_be_streamed_to_an_ostream,
    character_sets_with_strings,
    ValuesIn(character_set_strings));

TEST(a_character_set, can_be_inserted_into_an_unordered_set)
{
    std::unordered_set<terminalpp::character_set> c{{}};
}

}  // namespace
