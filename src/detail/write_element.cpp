#include "terminalpp/detail/write_element.hpp"
#include "terminalpp/element.hpp"

namespace terminalpp { namespace detail {

// ==========================================================================
// WRITE_ELEMENT
// ==========================================================================
std::string write_element(const element& elem)
{
    std::string text;
    
    if (elem.glyph_.charset_ == terminalpp::ansi::charset::utf8)
    {
        for (size_t index = 0; 
             index < sizeof(elem.glyph_.ucharacter_)
          && elem.glyph_.ucharacter_[index] != '\0'; 
             ++index)
        {
            text += elem.glyph_.ucharacter_[index];

            if (!(elem.glyph_.ucharacter_[index] & 0x80))
            {
                break;
            }
        }
    }
    else
    {
        text += elem.glyph_.character_;
    }
    
    return text;
}
    
}}

