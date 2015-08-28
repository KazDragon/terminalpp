#include "terminalpp/ansi/charset.hpp"
#include <cstring>

namespace terminalpp { namespace ansi {

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

    switch (code[0])
    {
        default :
            return {};
        case '%' :
            if (len > 1)
            {
                switch (code[1])
                {
                    default : return {};
                    case CHARSET_DEC_SUPPLEMENTARY_GR[1] :
                        return charset::dec_supplementary_graphics;
                    case CHARSET_PORTUGUESE[1] :
                        return charset::portuguese;
                }
            }
            else
            {
                return {};
            }
            break;
                    case CHARSET_DEC[0]               : return charset::dec;
                    case CHARSET_DEC_SUPPLEMENTARY[0] : return charset::dec_supplementary;
                    case CHARSET_UK[0]                : return charset::uk;
                    case CHARSET_US_ASCII[0]          : return charset::us_ascii;
                    case CHARSET_SCO[0]               : return charset::sco;

                    // TODO: More locales.  Note that multiple-choice locales, such as
                    // French Canadian and Norwegian/Danish, may rely on the type of the
                    // terminal being used.
    }
}

std::string charset_to_string(charset const &charset)
{
    switch (charset)
    {
        default                : return CHARSET_US_ASCII;
        case charset::us_ascii : return CHARSET_US_ASCII;
        case charset::dec      : return CHARSET_DEC;
        case charset::dec_supplementary : return CHARSET_DEC_SUPPLEMENTARY;
        case charset::dec_supplementary_graphics : return CHARSET_DEC_SUPPLEMENTARY_GR;
        case charset::uk       : return CHARSET_UK;
        case charset::sco      : return CHARSET_SCO;

        // TODO: More locales.
    }
}

}}
