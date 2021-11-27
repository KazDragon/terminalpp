#include "terminalpp/element.hpp"
#include "terminalpp/character_set.hpp"
#include "terminalpp/ansi/charset.hpp"

namespace terminalpp {
namespace detail {

namespace {

enum class parser_state {
    idle,
    escape,
    charcode_0,
    charcode_1,
    charcode_2,
    charset,
    charset_ext,
    intensity,
    polarity,
    underlining,
    fg_low_colour,
    fg_high_colour_0,
    fg_high_colour_1,
    fg_high_colour_2,
    fg_greyscale_colour_0,
    fg_greyscale_colour_1,
    fg_true_colour_0,
    fg_true_colour_1,
    fg_true_colour_2,
    fg_true_colour_3,
    fg_true_colour_4,
    fg_true_colour_5,
    bg_low_colour,
    bg_high_colour_0,
    bg_high_colour_1,
    bg_high_colour_2,
    bg_greyscale_colour_0,
    bg_greyscale_colour_1,
    bg_true_colour_0,
    bg_true_colour_1,
    bg_true_colour_2,
    bg_true_colour_3,
    bg_true_colour_4,
    bg_true_colour_5,
    utf8_0,
    utf8_1,
    utf8_2,
    utf8_3,
    done,
};

struct parser_info
{
    parser_state state {parser_state::idle};
    byte charcode{0};
    byte red{0};
    byte green{0};
    byte blue{0};
    byte greyscale{0};
    uint16_t utf8{0};
};

byte digit10_to_byte(char const ch)
{
    return static_cast<byte>(ch - '0');
}

byte digit16_to_byte(char const ch)
{
    return (ch >= '0' && ch <= '9') ? static_cast<byte>(ch - '0')
         : (ch >= 'a' && ch <= 'f') ? static_cast<byte>((ch - 'a') + 10)
         : (ch >= 'A' && ch <= 'F') ? static_cast<byte>((ch - 'A') + 10)
         : static_cast<byte>(0);
}

void parse_utf8_3(char const ch, parser_info &info, element &elem)
{
    static constexpr long const maxima[] = {
        0x00007F,
        0x0007FF,
        0x00FFFF,
        0x10FFFF
    };

    byte text[4] = {0};
    uint16_t const value = (info.utf8 * 16) + digit16_to_byte(ch);

    // At the moment, we can only convert up to 0xFFFF hex, since we only have
    // three spots in ucharacter_ to play with.  As an arbitrary decision,
    // anything above that will come out as a ? character.  Otherwise,
    // we will UTF-8 encode the value as appropriate into the ucharacter_
    // array.
    if (value <= maxima[0])
    {
        text[0] = byte(value & 0x7F);
        text[1] = 0;
        text[2] = 0;
    }
    else if (value <= maxima[1])
    {
        text[0] = byte(0b11000000 | (value >> 6));
        text[1] = byte(0b10000000 | (value & 0b00111111));
        text[2] = 0;
    }
    else if (value <= maxima[2])
    {
        text[0] = byte(0b11100000 | (value >> 12));
        text[1] = byte(0b10000000 | ((value >> 6) & 0b00111111));
        text[2] = byte(0b10000000 | (value & 0b00111111));
    }
    else
    {
        // Too high to encode right now.
        text[0] = byte('?');
        text[1] = 0;
    }

    elem.glyph_ = terminalpp::glyph(text);
    info.state = parser_state::done;
}

void parse_utf8_2(char const ch, parser_info &info, element &elem)
{
    info.utf8 *= 16;
    info.utf8 += digit16_to_byte(ch);
    info.state = parser_state::utf8_3;
}

void parse_utf8_1(char const ch, parser_info &info, element &elem)
{
    info.utf8 *= 16;
    info.utf8 += digit16_to_byte(ch);
    info.state = parser_state::utf8_2;
}

void parse_utf8_0(char const ch, parser_info &info, element &elem)
{
    info.utf8 = digit16_to_byte(ch);
    info.state = parser_state::utf8_1;
}

void parse_bg_true_colour_5(char const ch, parser_info &info, element &elem)
{
    info.blue |= digit16_to_byte(ch);

    elem.attribute_.background_colour_ = true_colour{
        info.red, info.green, info.blue
    };

    info.state = parser_state::idle;
}

void parse_bg_true_colour_4(char const ch, parser_info &info, element &elem)
{
    info.blue = digit16_to_byte(ch) << 4;
    info.state = parser_state::bg_true_colour_5;
}

void parse_bg_true_colour_3(char const ch, parser_info &info, element &elem)
{
    info.green |= digit16_to_byte(ch);
    info.state = parser_state::bg_true_colour_4;
}

void parse_bg_true_colour_2(char const ch, parser_info &info, element &elem)
{
    info.green = digit16_to_byte(ch) << 4;
    info.state = parser_state::bg_true_colour_3;
}

void parse_bg_true_colour_1(char const ch, parser_info &info, element &elem)
{
    info.red |= digit16_to_byte(ch);
    info.state = parser_state::bg_true_colour_2;
}

void parse_bg_true_colour_0(char const ch, parser_info &info, element &elem)
{
    info.red = digit16_to_byte(ch) << 4;
    info.state = parser_state::bg_true_colour_1;
}

void parse_bg_greyscale_1(char const ch, parser_info &info, element &elem)
{
    byte const col = (info.greyscale * 10) + digit10_to_byte(ch);
    elem.attribute_.background_colour_ = greyscale_colour(col);
    info.state = parser_state::idle;
}

void parse_bg_greyscale_0(char const ch, parser_info &info, element &elem)
{
    info.greyscale = digit10_to_byte(ch);
    info.state = parser_state::bg_greyscale_colour_1;
}

void parse_bg_high_colour_2(char const ch, parser_info &info, element &elem)
{
    auto const blue = digit10_to_byte(ch);
    elem.attribute_.background_colour_ = 
        high_colour(info.red, info.green, blue);
    info.state = parser_state::idle;
}

void parse_bg_high_colour_1(char const ch, parser_info &info, element &elem)
{
    info.green = digit10_to_byte(ch);
    info.state = parser_state::bg_high_colour_2;
}

void parse_bg_high_colour_0(char const ch, parser_info &info, element &elem)
{
    info.red = digit10_to_byte(ch);
    info.state = parser_state::bg_high_colour_1;
}

void parse_bg_low_colour(char const ch, parser_info &info, element &elem)
{
    auto const col_code = digit10_to_byte(ch);
    auto const col = static_cast<terminalpp::graphics::colour>(col_code);

    elem.attribute_.background_colour_ = low_colour(col);
    info.state = parser_state::idle;
}

void parse_fg_greyscale_1(char const ch, parser_info &info, element &elem)
{
    byte const col = (info.greyscale * 10) + digit10_to_byte(ch);
    elem.attribute_.foreground_colour_ = greyscale_colour(col);
    info.state = parser_state::idle;
}

void parse_fg_greyscale_0(char const ch, parser_info &info, element &elem)
{
    info.greyscale = digit10_to_byte(ch);
    info.state = parser_state::fg_greyscale_colour_1;
}

void parse_fg_true_colour_5(char const ch, parser_info &info, element &elem)
{
    info.blue |= digit16_to_byte(ch);

    elem.attribute_.foreground_colour_ = true_colour{
        info.red, info.green, info.blue
    };

    info.state = parser_state::idle;
}

void parse_fg_true_colour_4(char const ch, parser_info &info, element &elem)
{
    info.blue = digit16_to_byte(ch) << 4;
    info.state = parser_state::fg_true_colour_5;
}

void parse_fg_true_colour_3(char const ch, parser_info &info, element &elem)
{
    info.green |= digit16_to_byte(ch);
    info.state = parser_state::fg_true_colour_4;
}

void parse_fg_true_colour_2(char const ch, parser_info &info, element &elem)
{
    info.green = digit16_to_byte(ch) << 4;
    info.state = parser_state::fg_true_colour_3;
}

void parse_fg_true_colour_1(char const ch, parser_info &info, element &elem)
{
    info.red |= digit16_to_byte(ch);
    info.state = parser_state::fg_true_colour_2;
}

void parse_fg_true_colour_0(char const ch, parser_info &info, element &elem)
{
    info.red = digit16_to_byte(ch) << 4;
    info.state = parser_state::fg_true_colour_1;
}

void parse_fg_high_colour_2(char const ch, parser_info &info, element &elem)
{
    auto const blue = digit10_to_byte(ch);
    elem.attribute_.foreground_colour_ = 
        high_colour(info.red, info.green, blue);
    info.state = parser_state::idle;
}

void parse_fg_high_colour_1(char const ch, parser_info &info, element &elem)
{
    info.green = digit10_to_byte(ch);
    info.state = parser_state::fg_high_colour_2;
}

void parse_fg_high_colour_0(char const ch, parser_info &info, element &elem)
{
    info.red = digit10_to_byte(ch);
    info.state = parser_state::fg_high_colour_1;
}

void parse_fg_low_colour(char const ch, parser_info &info, element &elem)
{
    auto const col_code = digit10_to_byte(ch);
    auto const col = static_cast<terminalpp::graphics::colour>(col_code);

    elem.attribute_.foreground_colour_ = low_colour(col);
    info.state = parser_state::idle;
}

void parse_underlining(char const ch, parser_info &info, element &elem)
{
    switch(ch)
    {
        case '+':
            elem.attribute_.underlining_ = graphics::underlining::underlined;
            break;

        case '-':
            elem.attribute_.underlining_ = graphics::underlining::not_underlined;
            break;

        default:
            elem.attribute_.underlining_ = graphics::underlining::not_underlined;
            break;
    }

    info.state = parser_state::idle;
}

void parse_polarity(char const ch, parser_info &info, element &elem)
{
    switch(ch)
    {
        case '+':
            elem.attribute_.polarity_ = graphics::polarity::positive;
            break;

        case '-':
            elem.attribute_.polarity_ = graphics::polarity::negative;
            break;

        default:
            elem.attribute_.polarity_ = graphics::polarity::positive;
            break;
    }

    info.state = parser_state::idle;
}

void parse_intensity(char const ch, parser_info &info, element &elem)
{
    switch (ch)
    {
        case '>':
            elem.attribute_.intensity_ = graphics::intensity::bold;
            break;

        case '<':
            elem.attribute_.intensity_ = graphics::intensity::faint;
            break;

        default:
            elem.attribute_.intensity_ = graphics::intensity::normal;
            break;
    }

    info.state = parser_state::idle;
}

void parse_charset_ext(char const ch, parser_info &info, element &elem)
{
    byte const charset_code[] = { ansi::charset_extender, static_cast<byte>(ch) };
    auto const charset = lookup_character_set(charset_code);
    elem.glyph_.charset_ = charset ? *charset : elem.glyph_.charset_;
    info.state = parser_state::idle;
}

void parse_charset(char const ch, parser_info &info, element &elem)
{
    switch (ch)
    {
        case '%':
            info.state = parser_state::charset_ext;
            break;

        default:
        {
            byte const charset_code[] = { static_cast<byte>(ch) };
            auto const charset = lookup_character_set(charset_code);
            elem.glyph_.charset_ = charset ? *charset : elem.glyph_.charset_;
            info.state = parser_state::idle;
        }
    }

}

void parse_charcode_2(char const ch, parser_info &info, element &elem)
{
    info.charcode *= 10;
    info.charcode += digit10_to_byte(ch);
    elem.glyph_.character_ = info.charcode;
    info.state = parser_state::done;
}

void parse_charcode_1(char const ch, parser_info &info, element &elem)
{
    info.charcode *= 10;
    info.charcode += digit10_to_byte(ch);
    info.state = parser_state::charcode_2;
}

void parse_charcode_0(char const ch, parser_info &info, element &elem)
{
    info.charcode = digit10_to_byte(ch);
    info.state = parser_state::charcode_1;
}

void parse_escape(char const ch, parser_info &info, element &elem)
{
    switch (ch)
    {
        case 'C':
            info.state = parser_state::charcode_0;
            break;

        case 'c':
            info.state = parser_state::charset;
            break;

        case 'i':
            info.state = parser_state::intensity;
            break;

        case 'p':
            info.state = parser_state::polarity;
            break;

        case 'u':
            info.state = parser_state::underlining;
            break;

        case '[':
            info.state = parser_state::fg_low_colour;
            break;

        case '<':
            info.state = parser_state::fg_high_colour_0;
            break;

        case '{':
            info.state = parser_state::fg_greyscale_colour_0;
            break;

        case '(':
            info.state = parser_state::fg_true_colour_0;
            break;

        case ']':
            info.state = parser_state::bg_low_colour;
            break;

        case '>':
            info.state = parser_state::bg_high_colour_0;
            break;

        case '}':
            info.state = parser_state::bg_greyscale_colour_0;
            break;

        case ')':
            info.state = parser_state::bg_true_colour_0;
            break;

        case 'U':
            info.state = parser_state::utf8_0;
            break;

        case 'x':
            elem.attribute_ = {};
            info.state = parser_state::idle;
            break;

        default :
            elem.glyph_.character_ = static_cast<byte>(ch);
            info.state = parser_state::done;
            break;
    }
}

void parse_idle(char const ch, parser_info &info, element &elem)
{
    switch (ch)
    {
        case '\\':
            info.state = parser_state::escape;
            break;

        default:
            elem.glyph_.character_ = static_cast<byte>(ch);
            info.state = parser_state::done;
            break;
    }
}

element element_with_base(element const &elem_base)
{
    element result = elem_base;
    result.glyph_.charset_ = 
        result.glyph_.charset_ == charset::utf8
      ? charset::us_ascii
      : result.glyph_.charset_;
    result.glyph_.character_ = ' ';
    
    return result;
}

}

element parse_element(gsl::cstring_span &text, element const &elem_base)
{
    auto info = parser_info{};
    auto elem = element_with_base(elem_base);

    using handler = void (*)(char, parser_info &, element &);
    handler const handlers[] = 
    {
        parse_idle,
        parse_escape,
        parse_charcode_0,
        parse_charcode_1,
        parse_charcode_2,
        parse_charset,
        parse_charset_ext,
        parse_intensity,
        parse_polarity,
        parse_underlining,
        parse_fg_low_colour,
        parse_fg_high_colour_0,
        parse_fg_high_colour_1,
        parse_fg_high_colour_2,
        parse_fg_greyscale_0,
        parse_fg_greyscale_1,
        parse_fg_true_colour_0,
        parse_fg_true_colour_1,
        parse_fg_true_colour_2,
        parse_fg_true_colour_3,
        parse_fg_true_colour_4,
        parse_fg_true_colour_5,
        parse_bg_low_colour,
        parse_bg_high_colour_0,
        parse_bg_high_colour_1,
        parse_bg_high_colour_2,
        parse_bg_greyscale_0,
        parse_bg_greyscale_1,
        parse_bg_true_colour_0,
        parse_bg_true_colour_1,
        parse_bg_true_colour_2,
        parse_bg_true_colour_3,
        parse_bg_true_colour_4,
        parse_bg_true_colour_5,
        parse_utf8_0,
        parse_utf8_1,
        parse_utf8_2,
        parse_utf8_3,
    };

    while (!text.empty() && info.state != parser_state::done)
    {
        handlers[static_cast<int>(info.state)](text[0], info, elem);
        text = text.subspan(1);
    }

    return elem;
}

}}
