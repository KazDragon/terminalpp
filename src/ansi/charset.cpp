#include "terminalpp/ansi/charset.hpp"
#include <cstring>
#include <utility>

namespace terminalpp { namespace ansi {

static constexpr char const CHARSET_EXTENDER = terminalpp::ascii::PERCENT;
static constexpr std::pair<charset, char const (&)[2]> const charset_map[] =
{
    { charset::us_ascii,          CHARSET_US_ASCII          },
    { charset::sco,               CHARSET_SCO               },
    { charset::dec,               CHARSET_DEC               },
    { charset::dec_supplementary, CHARSET_DEC_SUPPLEMENTARY },
    { charset::dec_technical,     CHARSET_DEC_TECHNICAL     },
    { charset::uk,                CHARSET_UK                },
};

static constexpr std::pair<charset, char const (&)[3]> const extended_charset_map[] =
{
    { charset::dec_supplementary_graphics, CHARSET_DEC_SUPPLEMENTARY_GR },
    { charset::portuguese,                 CHARSET_PORTUGUESE           },
};

boost::optional<charset> lookup_charset(char const *code)
{
    if (code == nullptr)
    {
        return {};
    }

    auto len = strlen(code);

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
