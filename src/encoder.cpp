#include "terminalpp/encoder.hpp"
#include <cstring>

namespace terminalpp { namespace {

// ==========================================================================
// UTF8_ENCODE_GLYPH
// ==========================================================================
static void utf8_encode_glyph(glyph &gly, char fourth)
{
    static const terminalpp::u32 maxima[] = {
        0x00007F,
        0x0007FF,
        0x00FFFF,
        0x10FFFF
    };
    // Do excuse the weird parameters.  At this point in the parsing, the
    // first, second and third characters are already stored in the glyph.
    char text[] = {
        gly.ucharacter_[0], gly.ucharacter_[1], gly.ucharacter_[2], fourth, 0
    };

    auto value = strtol(text, nullptr, 16);

    // At the moment, we can only convert up to 0xFFFF hex, since we only have
    // three spots in ucharacter_ to play with.  As an arbitrary decision,
    // anything above that will come out as a ? character.  Otherwise,
    // we will UTF-8 encode the value as appropriate into the ucharacter_
    // array.
    if (value <= maxima[0])
    {
        gly.ucharacter_[0] = char(value & 0x7F);
        gly.ucharacter_[1] = 0;
    }
    else if (value <= maxima[1])
    {
        gly.ucharacter_[0] = char(0b11000000 | (value >> 6));
        gly.ucharacter_[1] = char(0b10000000 | (value & 0b00111111));
        gly.ucharacter_[2] = 0;
    }
    else if (value <= maxima[2])
    {
        gly.ucharacter_[0] = char(0b11100000 | (value >> 12));
        gly.ucharacter_[1] = char(0b10000000 | ((value >> 6) & 0b00111111));
        gly.ucharacter_[2] = char(0b10000000 | (value & 0b00111111));
    }
    else
    {
        // Too high to encode right now.
        gly.ucharacter_[0] = '?';
        gly.ucharacter_[1] = 0;
    }
}

enum class encoding_state
{
    normal,
    escaped,
    character_code_0,
    character_code_1,
    character_code_2,
    character_set,
    character_set_ext,
    intensity,
    polarity,
    underlining,
    low_colour_foreground,
    high_colour_foreground_red,
    high_colour_foreground_green,
    high_colour_foreground_blue,
    greyscale_colour_foreground_0,
    greyscale_colour_foreground_1,
    low_colour_background,
    high_colour_background_red,
    high_colour_background_green,
    high_colour_background_blue,
    greyscale_colour_background_0,
    greyscale_colour_background_1,
    utf8_0,
    utf8_1,
    utf8_2,
    utf8_3,
};

struct encoding_data
{
    terminalpp::element current_element;
    bool                element_complete = false;
    terminalpp::u8      red;
    terminalpp::u8      green;
};

// ==========================================================================
// ENCODE_NORMAL
// ==========================================================================
static encoding_state encode_normal(char ch, encoding_data &data)
{
    if (ch == '\\')
    {
        return encoding_state::escaped;
    }
    else
    {
        data.current_element.glyph_.character_ = ch;
        data.element_complete = true;
    }

    return encoding_state::normal;
}

// ==========================================================================
// ENCODE_ESCAPED
// ==========================================================================
static encoding_state encode_escaped(char ch, encoding_data &data)
{
    switch (ch)
    {
        default :
            data.current_element.glyph_.character_ = ch;
            data.element_complete = true;
            return encoding_state::normal;

        case 'x' :
            data.current_element.attribute_ = {};
            return encoding_state::normal;

        case 'C' :
            return encoding_state::character_code_0;

        case 'c' :
            return encoding_state::character_set;

        case 'i' :
            return encoding_state::intensity;

        case 'p' :
            return encoding_state::polarity;

        case 'u' :
            return encoding_state::underlining;

        case '[' :
            return encoding_state::low_colour_foreground;

        case '<' :
            return encoding_state::high_colour_foreground_red;

        case '{' :
            return encoding_state::greyscale_colour_foreground_0;

        case ']' :
            return encoding_state::low_colour_background;

        case '>' :
            return encoding_state::high_colour_background_red;

        case '}' :
            return encoding_state::greyscale_colour_background_0;

        case 'U' :
            return encoding_state::utf8_0;
    }
}

// ==========================================================================
// ENCODE_CHARACTER_CODE_0
// ==========================================================================
static encoding_state encode_character_code_0(char ch, encoding_data &data)
{
    data.current_element.glyph_.character_ = char((ch - '0') * 100);
    return encoding_state::character_code_1;
}

// ==========================================================================
// ENCODE_CHARACTER_CODE_1
// ==========================================================================
static encoding_state encode_character_code_1(char ch, encoding_data &data)
{
    data.current_element.glyph_.character_ += char((ch - '0') * 10);
    return encoding_state::character_code_2;
}

// ==========================================================================
// ENCODE_CHARACTER_CODE_2
// ==========================================================================
static encoding_state encode_character_code_2(char ch, encoding_data &data)
{
    data.current_element.glyph_.character_ += char((ch - '0'));
    data.element_complete = true;
    return encoding_state::normal;
}

// ==========================================================================
// ENCODE_CHARACTER_SET
// ==========================================================================
static encoding_state encode_character_set(char ch, encoding_data &data)
{
    if (ch == '%')
    {
        return encoding_state::character_set_ext;
    }
    else
    {
        char charset_code[] = {ch, 0};
        auto charset =
            terminalpp::ansi::lookup_charset(charset_code);

        if (charset)
        {
            data.current_element.glyph_.charset_ = charset.get();
        }

        return encoding_state::normal;
    }
}

// ==========================================================================
// ENCODE_CHARACTER_SET_EXT
// ==========================================================================
static encoding_state encode_character_set_ext(char ch, encoding_data &data)
{
    char charset_code[] = {'%', ch, '\0'};
    auto charset =
        terminalpp::ansi::lookup_charset(charset_code);

    if (charset)
    {
        data.current_element.glyph_.charset_ = charset.get();
    }

    return encoding_state::normal;
}

// ==========================================================================
// ENCODE_INTENSITY
// ==========================================================================
static encoding_state encode_intensity(char ch, encoding_data &data)
{
    switch (ch)
    {
        default :
            // Fall-through
        case '=' :
            data.current_element.attribute_.intensity_ =
                terminalpp::ansi::graphics::intensity::normal;
            break;

        case '>' :
            data.current_element.attribute_.intensity_ =
                terminalpp::ansi::graphics::intensity::bold;
            break;

        case '<' :
            data.current_element.attribute_.intensity_ =
                terminalpp::ansi::graphics::intensity::faint;
            break;
    }

    return encoding_state::normal;
}

// ==========================================================================
// ENCODE_POLARITY
// ==========================================================================
static encoding_state encode_polarity(char ch, encoding_data &data)
{
    switch (ch)
    {
        default :
            // Fall-through
        case '=' :
            // Fall-through
        case '+' :
            data.current_element.attribute_.polarity_ =
                terminalpp::ansi::graphics::polarity::positive;
            break;

        case '-' :
            data.current_element.attribute_.polarity_ =
                terminalpp::ansi::graphics::polarity::negative;
            break;
    }

    return encoding_state::normal;
}

// ==========================================================================
// ENCODE_UNDERLINING
// ==========================================================================
static encoding_state encode_underlining(char ch, encoding_data &data)
{
    switch (ch)
    {
        default :
            // Fall-through :
        case '=' :
            // Fall-through :
        case '-' :
            data.current_element.attribute_.underlining_ =
                terminalpp::ansi::graphics::underlining::not_underlined;
            break;

        case '+' :
            data.current_element.attribute_.underlining_ =
                terminalpp::ansi::graphics::underlining::underlined;
            break;
    }

    return encoding_state::normal;
}

// ==========================================================================
// ENCODE_LOW_COLOUR_FOREGROUND
// ==========================================================================
static encoding_state encode_low_colour_foreground(char ch, encoding_data &data)
{
    data.current_element.attribute_.foreground_colour_ =
        terminalpp::low_colour(
            terminalpp::ansi::graphics::colour(ch - '0'));
    return encoding_state::normal;
}

// ==========================================================================
// ENCODE_LOW_COLOUR_BACKGROUND
// ==========================================================================
static encoding_state encode_low_colour_background(char ch, encoding_data &data)
{
    data.current_element.attribute_.background_colour_ =
        terminalpp::low_colour(
            terminalpp::ansi::graphics::colour(ch - '0'));
    return encoding_state::normal;
}

// ==========================================================================
// ENCODE_HIGH_COLOUR_FOREGROUND_RED
// ==========================================================================
static encoding_state encode_high_colour_foreground_red(char ch, encoding_data &data)
{
    data.red = char(ch - '0');
    return encoding_state::high_colour_foreground_green;
}

// ==========================================================================
// ENCODE_HIGH_COLOUR_FOREGROUND_GREEN
// ==========================================================================
static encoding_state encode_high_colour_foreground_green(char ch, encoding_data &data)
{
    data.green = char(ch - '0');
    return encoding_state::high_colour_foreground_blue;
}

// ==========================================================================
// ENCODE_HIGH_COLOUR_FOREGROUND_BLUE
// ==========================================================================
static encoding_state encode_high_colour_foreground_blue(char ch, encoding_data &data)
{
    data.current_element.attribute_.foreground_colour_ =
        high_colour(data.red, data.green, char(ch - '0'));
    return encoding_state::normal;
}

// ==========================================================================
// ENCODE_HIGH_COLOUR_BACKGROUND_RED
// ==========================================================================
static encoding_state encode_high_colour_background_red(char ch, encoding_data &data)
{
    data.red = char(ch - '0');
    return encoding_state::high_colour_background_green;
}

// ==========================================================================
// ENCODE_HIGH_COLOUR_BACKGROUND_GREEN
// ==========================================================================
static encoding_state encode_high_colour_background_green(char ch, encoding_data &data)
{
    data.green = char(ch - '0');
    return encoding_state::high_colour_background_blue;
}

// ==========================================================================
// ENCODE_HIGH_COLOUR_BACKGROUND_BLUE
// ==========================================================================
static encoding_state encode_high_colour_background_blue(char ch, encoding_data &data)
{
    data.current_element.attribute_.background_colour_ =
        high_colour(data.red, data.green, char(ch - '0'));
    return encoding_state::normal;
}

// ==========================================================================
// ENCODE_GREYSCALE_FOREGROUND_0
// ==========================================================================
static encoding_state encode_greyscale_foreground_0(char ch, encoding_data &data)
{
    data.current_element.attribute_.foreground_colour_ =
        terminalpp::greyscale_colour(char((ch - '0') * 10));
    return encoding_state::greyscale_colour_foreground_1;
}

// ==========================================================================
// ENCODE_GREYSCALE_FOREGROUND_1
// ==========================================================================
static encoding_state encode_greyscale_foreground_1(char ch, encoding_data &data)
{
    data.current_element.attribute_.foreground_colour_
        .greyscale_colour_.shade_ += char(ch - '0');
    return encoding_state::normal;
}

// ==========================================================================
// ENCODE_GREYSCALE_BACKGROUND_0
// ==========================================================================
static encoding_state encode_greyscale_background_0(char ch, encoding_data &data)
{
    data.current_element.attribute_.background_colour_ =
        terminalpp::greyscale_colour(char((ch - '0') * 10));
    return encoding_state::greyscale_colour_background_1;
}

// ==========================================================================
// ENCODE_GREYSCALE_BACKGROUND_1
// ==========================================================================
static encoding_state encode_greyscale_background_1(char ch, encoding_data &data)
{
    data.current_element.attribute_.background_colour_
        .greyscale_colour_.shade_ += char(ch - '0');
    return encoding_state::normal;
}

// ==========================================================================
// ENCODE_UTF8_0
// ==========================================================================
static encoding_state encode_utf8_0(char ch, encoding_data &data)
{
    data.current_element.glyph_.charset_ = terminalpp::ansi::charset::utf8;
    data.current_element.glyph_.ucharacter_[0] = ch;
    return encoding_state::utf8_1;
}

// ==========================================================================
// ENCODE_UTF8_1
// ==========================================================================
static encoding_state encode_utf8_1(char ch, encoding_data &data)
{
    data.current_element.glyph_.ucharacter_[1] = ch;
    return encoding_state::utf8_2;
}

// ==========================================================================
// ENCODE_UTF8_2
// ==========================================================================
static encoding_state encode_utf8_2(char ch, encoding_data &data)
{
    data.current_element.glyph_.ucharacter_[2] = ch;
    return encoding_state::utf8_3;

}

// ==========================================================================
// ENCODE_UTF8_3
// ==========================================================================
static encoding_state encode_utf8_3(char ch, encoding_data &data)
{
    utf8_encode_glyph(data.current_element.glyph_, ch);
    data.element_complete = true;
    return encoding_state::normal;
}

}

// ==========================================================================
// ENCODE
// ==========================================================================
terminalpp::string encode(std::string const &text)
{
    return encode(text.c_str(), text.size());
}

//* =========================================================================
/// \brief A function that converts a char* into a terminalpp::string,
/// parsing its contents according to the String To Elements protocol.
//* =========================================================================
terminalpp::string encode(char const *text)
{
    return encode(text, strlen(text));
}

//* =========================================================================
/// \brief A function that converts a char* of a given length into a
/// terminalpp::string, parsing its contents according to the String To
/// Elements protocol.
//* =========================================================================
terminalpp::string encode(char const *text, size_t length)
{
    terminalpp::string result;
    encoding_data data;
    encoding_state state = encoding_state::normal;

    std::for_each(
        text, text + length, [&data, &state, &result](char ch)
    {
        switch (state)
        {
            //default :
                // Fall-through
            case encoding_state::normal :
                state = encode_normal(ch, data);
                break;

            case encoding_state::escaped :
                state = encode_escaped(ch, data);
                break;

            case encoding_state::character_code_0 :
                state = encode_character_code_0(ch, data);
                break;

            case encoding_state::character_code_1 :
                state = encode_character_code_1(ch, data);
                break;

            case encoding_state::character_code_2 :
                state = encode_character_code_2(ch, data);
                break;

            case encoding_state::character_set :
                state = encode_character_set(ch, data);
                break;

            case encoding_state::character_set_ext :
                state = encode_character_set_ext(ch, data);
                break;

            case encoding_state::intensity :
                state = encode_intensity(ch, data);
                break;

            case encoding_state::polarity :
                state = encode_polarity(ch, data);
                break;

            case encoding_state::underlining :
                state = encode_underlining(ch, data);
                break;

            case encoding_state::low_colour_background :
                state = encode_low_colour_background(ch, data);
                break;

            case encoding_state::low_colour_foreground :
                state = encode_low_colour_foreground(ch, data);
                break;

            case encoding_state::high_colour_background_red :
                state = encode_high_colour_background_red(ch, data);
                break;

            case encoding_state::high_colour_background_green :
                state = encode_high_colour_background_green(ch, data);
                break;

            case encoding_state::high_colour_background_blue :
                state = encode_high_colour_background_blue(ch, data);
                break;

            case encoding_state::high_colour_foreground_red :
                state = encode_high_colour_foreground_red(ch, data);
                break;

            case encoding_state::high_colour_foreground_green :
                state = encode_high_colour_foreground_green(ch, data);
                break;

            case encoding_state::high_colour_foreground_blue :
                state = encode_high_colour_foreground_blue(ch, data);
                break;

            case encoding_state::greyscale_colour_background_0 :
                state = encode_greyscale_background_0(ch, data);
                break;

            case encoding_state::greyscale_colour_background_1 :
                state = encode_greyscale_background_1(ch, data);
                break;

            case encoding_state::greyscale_colour_foreground_0 :
                state = encode_greyscale_foreground_0(ch, data);
                break;

            case encoding_state::greyscale_colour_foreground_1 :
                state = encode_greyscale_foreground_1(ch, data);
                break;

            case encoding_state::utf8_0 :
                state = encode_utf8_0(ch, data);
                break;

            case encoding_state::utf8_1 :
                state = encode_utf8_1(ch, data);
                break;

            case encoding_state::utf8_2 :
                state = encode_utf8_2(ch, data);
                break;

            case encoding_state::utf8_3 :
                state = encode_utf8_3(ch, data);
                break;
        }

        if (data.element_complete)
        {
            result += data.current_element;

            if (data.current_element.glyph_.charset_ == ansi::charset::utf8)
            {
                // TODO: This should really pop back to whatever the charset
                // was before.
                data.current_element.glyph_.charset_ = ansi::charset::us_ascii;
            }

            data.element_complete = false;
        }
    });

    return result;
}

};
