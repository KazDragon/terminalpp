#include "terminalpp/character_set.hpp"

#include <algorithm>
#include <iostream>

namespace terminalpp {

static constexpr struct
{
    terminalpp::charset set;
    char const *name;
} const character_set_strings[] = {
  // clang-format off
    { terminalpp::charset::dec,                        "dec"    },
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

// ==========================================================================
// OPERATOR<<(STREAM, CHARACTER_SET)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, character_set const &set)
{
    if (auto const *it = std::ranges::find(
            character_set_strings,
            set.value_,
            [](auto const &character_set_string) {
                return character_set_string.set;
            });
        it != std::cend(character_set_strings))
    {
        return out << it->name;
    }
    else
    {
        return out;
    }
}

}  // namespace terminalpp
