#include "terminalpp/ansi/charset.hpp"
#include <algorithm>
#include <cstring>
#include <utility>

namespace terminalpp { namespace ansi {

static constexpr std::pair<charset, char const (&)[2]> const charset_map[] =
{
    { charset::us_ascii,          CHARSET_US_ASCII            },
    { charset::sco,               CHARSET_SCO                 },
    { charset::dec,               CHARSET_DEC                 },
    { charset::dec_supplementary, CHARSET_DEC_SUPPLEMENTARY   },
    { charset::dec_technical,     CHARSET_DEC_TECHNICAL       },
    { charset::uk,                CHARSET_UK                  },
    { charset::dutch,             CHARSET_DUTCH               },
    { charset::finnish,           CHARSET_FINNISH             },
    { charset::finnish,           CHARSET_FINNISH_ALT         },
    { charset::french,            CHARSET_FRENCH              },
    { charset::french,            CHARSET_FRENCH_ALT          },
    { charset::french_canadian,   CHARSET_FRENCH_CANADIAN     },
    { charset::french_canadian,   CHARSET_FRENCH_CANADIAN_ALT },
    { charset::german,            CHARSET_GERMAN              },
    { charset::italian,           CHARSET_ITALIAN             },
    { charset::danish,            CHARSET_DANISH              },
    { charset::danish,            CHARSET_DANISH_ALT_1        },
    { charset::danish,            CHARSET_DANISH_ALT_2        },
    { charset::spanish,           CHARSET_SPANISH             },
    { charset::swedish,           CHARSET_SWEDISH             },
    { charset::swedish,           CHARSET_SWEDISH_ALT         },
    { charset::swiss,             CHARSET_SWISS               },
};

static constexpr std::pair<charset, char const (&)[3]> const extended_charset_map[] =
{
    { charset::dec_supplementary_graphics, CHARSET_DEC_SUPPLEMENTARY_GR },
    { charset::portuguese,                 CHARSET_PORTUGUESE           },
};

boost::optional<charset> lookup_charset(char const *code)
{
    auto len = code == nullptr ? 0 : strlen(code);

    if (len == 0)
    {
        return {};
    }

    if (code[0] == CHARSET_EXTENDER)
    {
        if (len > 1)
        {
            for (auto &&mapping : extended_charset_map)
            {
                if (code[1] == mapping.second[1])
                {
                    return mapping.first;
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
                return mapping.first;
            }
        }
    }

    return {};
}

std::string charset_to_string(charset const &charset)
{
    for (auto &&mapping : charset_map)
    {
        if (mapping.first == charset)
        {
            return mapping.second;
        }
    }

    for (auto &&mapping : extended_charset_map)
    {
        if (mapping.first == charset)
        {
            return mapping.second;
        }
    }

    return CHARSET_US_ASCII;
}

}}
