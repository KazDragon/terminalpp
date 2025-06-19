#include "terminalpp/character_set.hpp"

#include <gtest/gtest.h>

#include <tuple>
#include <unordered_set>

using testing::ValuesIn;

namespace {

using character_set_string =
    std::tuple<terminalpp::character_set, std::string_view>;

class character_sets_with_strings
  : public testing::TestWithParam<character_set_string>
{
};

TEST_P(character_sets_with_strings, can_be_streamed_to_an_ostream)
{
    auto const &[set, expected_string] = GetParam();

    std::stringstream stream;
    std::ostream &out = stream;

    out << terminalpp::character_set(set);
    ASSERT_EQ(expected_string, stream.str());
}

constexpr character_set_string character_set_strings[] = {
    // clang-format off
  { terminalpp::charset::dec,                        "dec",   },
  { terminalpp::charset::dec_supplementary,          "dec+"   },
  { terminalpp::charset::dec_supplementary_graphics, "dec+gr" },
  { terminalpp::charset::dec_technical,              "dectec" },
  { terminalpp::charset::uk,                         "en_uk"  },
  { terminalpp::charset::us_ascii,                   "en_us"  },
  { terminalpp::charset::dutch,                      "nl"     },
  { terminalpp::charset::finnish,                    "fi"     },
  { terminalpp::charset::french,                     "fr"     },
  { terminalpp::charset::french_canadian,            "fr_ca"  },
  { terminalpp::charset::german,                     "de"     },
  { terminalpp::charset::italian,                    "it"     },
  { terminalpp::charset::danish,                     "da"     },
  { terminalpp::charset::portuguese,                 "pt"     },
  { terminalpp::charset::spanish,                    "es"     },
  { terminalpp::charset::swedish,                    "su"     },
  { terminalpp::charset::swiss,                      "de_ch"  },
  { terminalpp::charset::sco,                        "sco"    },
  { terminalpp::charset::utf8,                       "u"      },
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
