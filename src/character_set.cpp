#include "terminalpp/character_set.hpp"
#include "terminalpp/ansi/charset.hpp"
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm_ext/insert.hpp>
#include <iostream>

namespace terminalpp {

static constexpr struct {
    terminalpp::charset set;
    char const *name;
} const character_set_strings[] = {
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
};

static constexpr std::pair<charset, byte const (&)[1]> const charset_map[] =
{
    { charset::us_ascii,          ansi::charset_us_ascii            },
    { charset::sco,               ansi::charset_sco                 },
    { charset::dec,               ansi::charset_dec                 },
    { charset::dec_supplementary, ansi::charset_dec_supplementary   },
    { charset::dec_technical,     ansi::charset_dec_technical       },
    { charset::uk,                ansi::charset_uk                  },
    { charset::dutch,             ansi::charset_dutch               },
    { charset::finnish,           ansi::charset_finnish             },
    { charset::finnish,           ansi::charset_finnish_alt         },
    { charset::french,            ansi::charset_french              },
    { charset::french,            ansi::charset_french_alt          },
    { charset::french_canadian,   ansi::charset_french_canadian     },
    { charset::french_canadian,   ansi::charset_french_canadian_alt },
    { charset::german,            ansi::charset_german              },
    { charset::italian,           ansi::charset_italian             },
    { charset::danish,            ansi::charset_danish              },
    { charset::danish,            ansi::charset_danish_alt_1        },
    { charset::danish,            ansi::charset_danish_alt_2        },
    { charset::spanish,           ansi::charset_spanish             },
    { charset::swedish,           ansi::charset_swedish             },
    { charset::swedish,           ansi::charset_swedish_alt         },
    { charset::swiss,             ansi::charset_swiss               },
};

static constexpr std::pair<charset, byte const (&)[2]> const extended_charset_map[] =
{
    { charset::dec_supplementary_graphics, ansi::charset_dec_supplementary_gr },
    { charset::portuguese,                 ansi::charset_portuguese           },
};

// ==========================================================================
// LOOKUP_CHARACTER_SET
// ==========================================================================
boost::optional<character_set> lookup_character_set(bytes code)
{
    const auto len = code.size();

    if (len == 0)
    {
        return {};
    }

    if (code[0] == ansi::charset_extender)
    {
        if (len > 1)
        {
            for (auto &&mapping : extended_charset_map)
            {
                if (code[1] == mapping.second[1])
                {
                    return character_set(mapping.first);
                }
            }
        }
    }
    else
    {
        for (auto &&mapping : charset_map)
        {
            if (code[0] == mapping.second[0])
            {
                return character_set(mapping.first);
            }
        }
    }

    return {};
}

// ==========================================================================
// ENCODE_CHARACTER_SET
// ==========================================================================
byte_storage encode_character_set(character_set const &set)
{
    byte_storage result;

    auto const mapped_charset_matches_set = 
        [&set](auto const &mapping)
        {
            return mapping.first == set;
        };

    auto const charset_entry = boost::find_if(
        charset_map,
        mapped_charset_matches_set);

    if (charset_entry != std::cend(charset_map))
    {
        boost::insert(result, result.end(), charset_entry->second);
    }
    else
    {
        auto const extended_charset_entry = boost::find_if(
            extended_charset_map,
            mapped_charset_matches_set);

        if (extended_charset_entry != std::cend(extended_charset_map))
        {
            boost::insert(result, result.end(), extended_charset_entry->second);
        }
        else
        {
            // If the character set is an unknown, fall back to US ASCII.
            result = encode_character_set(character_set(charset::us_ascii));
        }
    }

    return result;
}

// ==========================================================================
// OPERATOR<<(STREAM, CHARACTER_SET)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, character_set const &set)
{
    auto it = boost::find_if(character_set_strings,
        [set](auto const &character_set_string)
        {
            return set.value_ == character_set_string.set;
        });

    if (it != std::cend(character_set_strings))
    {
        return out << it->name;
    }
    else
    {
        return out;
    }
}

}
