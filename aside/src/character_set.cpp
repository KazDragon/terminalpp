#include "terminalpp/character_set.hpp"
#include <algorithm>
#include <iostream>

namespace terminalpp {

static struct {
    terminalpp::ansi::charset set;
    char const *name;
} const character_set_strings[] = {
    { terminalpp::ansi::charset::dec,                        "dec"    },
    { terminalpp::ansi::charset::dec,                        "dec",   },
    { terminalpp::ansi::charset::dec_supplementary,          "dec+"   },
    { terminalpp::ansi::charset::dec_supplementary_graphics, "dec+gr" },
    { terminalpp::ansi::charset::dec_technical,              "dectec" },
    { terminalpp::ansi::charset::uk,                         "en_uk"  },
    { terminalpp::ansi::charset::us_ascii,                   "en_us"  },
    { terminalpp::ansi::charset::dutch,                      "nl"     },
    { terminalpp::ansi::charset::finnish,                    "fi"     },
    { terminalpp::ansi::charset::french,                     "fr"     },
    { terminalpp::ansi::charset::french_canadian,            "fr_ca"  },
    { terminalpp::ansi::charset::german,                     "de"     },
    { terminalpp::ansi::charset::italian,                    "it"     },
    { terminalpp::ansi::charset::danish,                     "da"     },
    { terminalpp::ansi::charset::portuguese,                 "pt"     },
    { terminalpp::ansi::charset::spanish,                    "es"     },
    { terminalpp::ansi::charset::swedish,                    "su"     },
    { terminalpp::ansi::charset::swiss,                      "de_ch"  },
    { terminalpp::ansi::charset::sco,                        "sco"    },
    { terminalpp::ansi::charset::utf8,                       "u"      },
};

// ==========================================================================
// OPERATOR<<(STREAM, CHARACTER_SET)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, character_set const &set)
{
    auto it = std::find_if(
        std::begin(character_set_strings),
        std::end(character_set_strings),
        [set](auto const &character_set_string)
        {
            return set.value_ == character_set_string.set;
        });

    if (it != std::end(character_set_strings))
    {
        return out << it->name;
    }
    else
    {
        return out;
    }
}

}
