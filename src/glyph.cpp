#include "terminalpp/glyph.hpp"
#include <iomanip>
#include <iostream>

namespace terminalpp {

static bool const is_printable_dec[] = {
/* 0x00 - 0x07 */ false, false, false, false, false, false, false, false,
/* 0x08 - 0x0F */ false, false, true,  false, false, false, false, false,
/* 0x10 - 0x17 */ false, false, false, false, false, false, false, false,
/* 0x18 - 0x1F */ false, false, false, false, false, false, false, false,
/* 0x20 - 0x27 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x28 - 0x2F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x30 - 0x37 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x38 - 0x3F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x40 - 0x47 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x48 - 0x4F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x50 - 0x57 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x58 - 0x5F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x60 - 0x67 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x68 - 0x6F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x70 - 0x77 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x78 - 0x7F */ true,  true,  true,  true,  true,  true,  true,  false,
/* 0x80 - 0x87 */ false, false, false, false, false, false, false, false,
/* 0x88 - 0x8F */ false, false, false, false, false, false, false, false,
/* 0x90 - 0x97 */ false, false, false, false, false, false, false, false,
/* 0x98 - 0x9F */ false, false, false, false, false, false, false, false,
/* 0xA0 - 0xA7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xA8 - 0xAF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB0 - 0xB7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB8 - 0xBF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC0 - 0xC7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC8 - 0xCF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD0 - 0xD7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD8 - 0xDF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE0 - 0xE7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE8 - 0xEF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF0 - 0xF7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF8 - 0xFF */ true,  true,  true,  true,  true,  true,  true,  false,
};

static bool const is_printable_uk[] = {
/* 0x00 - 0x07 */ false, false, false, false, false, false, false, false,
/* 0x08 - 0x0F */ false, false, true,  false, false, false, false, false,
/* 0x10 - 0x17 */ false, false, false, false, false, false, false, false,
/* 0x18 - 0x1F */ false, false, false, false, false, false, false, false,
/* 0x20 - 0x27 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x28 - 0x2F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x30 - 0x37 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x38 - 0x3F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x40 - 0x47 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x48 - 0x4F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x50 - 0x57 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x58 - 0x5F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x60 - 0x67 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x68 - 0x6F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x70 - 0x77 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x78 - 0x7F */ true,  true,  true,  true,  true,  true,  true,  false,
/* 0x80 - 0x87 */ false, false, false, false, false, false, false, false,
/* 0x88 - 0x8F */ false, false, false, false, false, false, false, false,
/* 0x90 - 0x97 */ false, false, false, false, false, false, false, false,
/* 0x98 - 0x9F */ false, false, false, false, false, false, false, false,
/* 0xA0 - 0xA7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xA8 - 0xAF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB0 - 0xB7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB8 - 0xBF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC0 - 0xC7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC8 - 0xCF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD0 - 0xD7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD8 - 0xDF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE0 - 0xE7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE8 - 0xEF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF0 - 0xF7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF8 - 0xFF */ true,  true,  true,  true,  true,  true,  true,  false,
};

static bool const is_printable_us_ascii[] = {
/* 0x00 - 0x07 */ false, false, false, false, false, false, false, false,
/* 0x08 - 0x0F */ false, false, true,  false, false, false, false, false,
/* 0x10 - 0x17 */ false, false, false, false, false, false, false, false,
/* 0x18 - 0x1F */ false, false, false, false, false, false, false, false,
/* 0x20 - 0x27 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x28 - 0x2F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x30 - 0x37 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x38 - 0x3F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x40 - 0x47 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x48 - 0x4F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x50 - 0x57 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x58 - 0x5F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x60 - 0x67 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x68 - 0x6F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x70 - 0x77 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x78 - 0x7F */ true,  true,  true,  true,  true,  true,  true,  false,
/* 0x80 - 0x87 */ false, false, false, false, false, false, false, false,
/* 0x88 - 0x8F */ false, false, false, false, false, false, false, false,
/* 0x90 - 0x97 */ false, false, false, false, false, false, false, false,
/* 0x98 - 0x9F */ false, false, false, false, false, false, false, false,
/* 0xA0 - 0xA7 */ false, false, false, false, false, false, false, false,
/* 0xA8 - 0xAF */ false, false, false, false, false, false, false, false,
/* 0xB0 - 0xB7 */ false, false, false, false, false, false, false, false,
/* 0xB8 - 0xBF */ false, false, false, false, false, false, false, false,
/* 0xC0 - 0xC7 */ false, false, false, false, false, false, false, false,
/* 0xC8 - 0xCF */ false, false, false, false, false, false, false, false,
/* 0xD0 - 0xD7 */ false, false, false, false, false, false, false, false,
/* 0xD8 - 0xDF */ false, false, false, false, false, false, false, false,
/* 0xE0 - 0xE7 */ false, false, false, false, false, false, false, false,
/* 0xE8 - 0xEF */ false, false, false, false, false, false, false, false,
/* 0xF0 - 0xF7 */ false, false, false, false, false, false, false, false,
/* 0xF8 - 0xFF */ false, false, false, false, false, false, false, false,
};

static bool const is_printable_sco[] = {
/* 0x00 - 0x07 */ false, false, false, false, false, false, false, false,
/* 0x08 - 0x0F */ false, false, true,  false, false, false, false, false,
/* 0x10 - 0x17 */ false, false, false, false, false, false, false, false,
/* 0x18 - 0x1F */ false, false, false, false, false, false, false, false,
/* 0x20 - 0x27 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x28 - 0x2F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x30 - 0x37 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x38 - 0x3F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x40 - 0x47 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x48 - 0x4F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x50 - 0x57 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x58 - 0x5F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x60 - 0x67 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x68 - 0x6F */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x70 - 0x77 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0x78 - 0x7F */ true,  true,  true,  true,  true,  true,  true,  false,
/* 0x80 - 0x87 */ false, false, false, false, false, false, false, false,
/* 0x88 - 0x8F */ false, false, false, false, false, false, false, false,
/* 0x90 - 0x97 */ false, false, false, false, false, false, false, false,
/* 0x98 - 0x9F */ false, false, false, false, false, false, false, false,
/* 0xA0 - 0xA7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xA8 - 0xAF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB0 - 0xB7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xB8 - 0xBF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC0 - 0xC7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xC8 - 0xCF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD0 - 0xD7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xD8 - 0xDF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE0 - 0xE7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xE8 - 0xEF */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF0 - 0xF7 */ true,  true,  true,  true,  true,  true,  true,  true,
/* 0xF8 - 0xFF */ true,  true,  true,  true,  true,  true,  true,  false,
};

// ==========================================================================
// IS_PRINTABLE
// ==========================================================================
bool is_printable(glyph const &gly)
{
    bool const *lookup = is_printable_dec;

    switch (gly.charset_.value_)
    {
    default :
        // Fall-through
    case terminalpp::charset::dec:
        lookup = is_printable_dec;
        break;

    case terminalpp::charset::uk:
        lookup = is_printable_uk;
        break;

    case terminalpp::charset::us_ascii:
        lookup = is_printable_us_ascii;
        break;

    case terminalpp::charset::sco:
        lookup = is_printable_sco;
        break;
    }

    return lookup[byte(gly.character_)];
}

// ==========================================================================
// OUTPUT_CHARSET_AND_CHARACTER
// ==========================================================================
static std::ostream &output_charset_and_character(
    std::ostream &out,
    glyph const &gly)
{
    if (gly.charset_ != character_set())
    {
        out << gly.charset_ << ":";
    }

    switch (gly.character_)
    {
        case '\r' : return out << "\\r";
        case '\n' : return out << "\\n";
        case '\t' : return out << "\\t";
        default :
            if (is_printable(gly))
            {
                return out << gly.character_;
            }
            else
            {
                return out << "0x" << std::setw(2) << std::setfill('0')
                           << std::hex << std::uppercase
                           << int(gly.character_);
            }
    }
}

// ==========================================================================
// UTF8_DECODE
// ==========================================================================
static std::uint32_t utf8_decode(glyph const &gly)
{
    std::uint32_t value = 0;

    if ((gly.ucharacter_[0] & 0b100000000) == 0)
    {
        value = gly.ucharacter_[0];
    }

    if ((gly.ucharacter_[0] & 0b11100000) == 0b11000000)
    {
        value  = byte((gly.ucharacter_[0] & 0b00011111) << 6);
        value |= byte((gly.ucharacter_[1] & 0b00111111) << 0);
    }

    if ((gly.ucharacter_[0] & 0b11110000) == 0b11100000)
    {
        value  = byte((gly.ucharacter_[0] & 0b00001111) << 12);
        value |= byte((gly.ucharacter_[1] & 0b00111111) << 6);
        value |= byte((gly.ucharacter_[2] & 0b00111111) << 0);
    }

    return value;
}

// ==========================================================================
// OPERATOR<<(STREAM, GLYPH)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, glyph const &gly)
{
    if (gly.charset_ == terminalpp::charset::utf8)
    {
        if (gly.ucharacter_[0] <= 0x7F)
        {
            return output_charset_and_character(out, gly);
        }
        else
        {
            return out << "U+"
                       << std::setw(4) << std::hex << std::setfill('0')
                       << std::uppercase
                       << utf8_decode(gly);
        }
    }
    else
    {
        return output_charset_and_character(out, gly);
    }
}

}
