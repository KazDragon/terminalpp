#include "terminalpp/detail/string_to_elements.hpp"
#include "terminalpp/ansi/functions.hpp"
#include <cstdlib>
#include <cstring>

namespace terminalpp { namespace detail {

void utf8_encode_glyph(glyph &gly, char fourth)
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

std::vector<terminalpp::element> string_to_elements(std::string const &text)
{
    return string_to_elements(text.c_str(), text.size());
}

std::vector<terminalpp::element> string_to_elements(char const* text)
{
    return string_to_elements(text, strlen(text));
}

std::vector<terminalpp::element> string_to_elements(char const *text, size_t len)
{
    enum class state
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

    std::vector<terminalpp::element> result;
    state current_state = state::normal;
    terminalpp::element current_element;
    bool element_complete = false;

    for (size_t index = 0; index < len; ++index)
    {
        auto const current_character = text[index];

        switch(current_state)
        {
            default :
                // fall-through
            case state::normal :
                if (text[index] == '\\')
                {
                    current_state = state::escaped;
                }
                else
                {
                    current_element.glyph_.character_ = current_character;
                    element_complete = true;
                }
                break;

            case state::escaped :
                switch (current_character)
                {
                    default :
                        current_element.glyph_.character_ = current_character;
                        current_state = state::normal;
                        element_complete = true;
                        break;

                    case 'C' :
                        current_state = state::character_code_0;
                        break;

                    case 'c' :
                        current_state = state::character_set;
                        break;

                    case 'i' :
                        current_state = state::intensity;
                        break;

                    case 'p' :
                        current_state = state::polarity;
                        break;

                    case 'u' :
                        current_state = state::underlining;
                        break;

                    case '[' :
                        current_state = state::low_colour_foreground;
                        break;

                    case '<' :
                        current_state = state::high_colour_foreground_red;
                        break;

                    case '{' :
                        current_state = state::greyscale_colour_foreground_0;
                        break;

                    case ']' :
                        current_state = state::low_colour_background;
                        break;

                    case '>' :
                        current_state = state::high_colour_background_red;
                        break;

                    case '}' :
                        current_state = state::greyscale_colour_background_0;
                        break;
                        
                    case 'U' :
                        current_state = state::utf8_0;
                        break;
                }
                break;

            case state::character_code_0 :
                current_element.glyph_.character_ =
                    char((current_character - '0') * 100);
                current_state = state::character_code_1;
                break;

            case state::character_code_1 :
                current_element.glyph_.character_ +=
                    char((current_character - '0') * 10);
                current_state = state::character_code_2;
                break;

            case state::character_code_2 :
                current_element.glyph_.character_ +=
                    char((current_character - '0'));
                current_state = state::normal;
                element_complete = true;
                break;

            case state::character_set :
                if (current_character == '%')
                {
                    current_state = state::character_set_ext;
                }
                else
                {
                    char charset_code[] = {current_character, 0};
                    auto charset =
                        terminalpp::ansi::lookup_charset(charset_code);

                    if (charset)
                    {
                        current_element.glyph_.charset_ = charset.get();
                    }

                    current_state = state::normal;
                }
                break;

            case state::character_set_ext :
            {
                char charset_code[] = {'%', current_character};
                auto charset =
                    terminalpp::ansi::lookup_charset(charset_code);

                if (charset)
                {
                    current_element.glyph_.charset_ = charset.get();
                }

                current_state = state::normal;
            }

            case state::intensity :
                switch (current_character)
                {
                    default :
                        // Fall-through
                    case '=' :
                        current_element.attribute_.intensity_ =
                            terminalpp::ansi::graphics::intensity::normal;
                        break;

                    case '>' :
                        current_element.attribute_.intensity_ =
                            terminalpp::ansi::graphics::intensity::bold;
                        break;

                    case '<' :
                        current_element.attribute_.intensity_ =
                            terminalpp::ansi::graphics::intensity::faint;
                        break;

                }

                current_state = state::normal;
                break;

            case state::polarity :
                switch (current_character)
                {
                    default :
                        // Fall-through
                    case '=' :
                        // Fall-through
                    case '+' :
                        current_element.attribute_.polarity_ =
                            terminalpp::ansi::graphics::polarity::positive;
                        break;

                    case '-' :
                        current_element.attribute_.polarity_ =
                            terminalpp::ansi::graphics::polarity::negative;
                        break;
                }

                current_state = state::normal;
                break;

            case state::underlining :
                switch (current_character)
                {
                    default :
                        // Fall-through :
                    case '=' :
                        // Fall-through :
                    case '-' :
                        current_element.attribute_.underlining_ =
                            terminalpp::ansi::graphics::underlining::not_underlined;
                        break;

                    case '+' :
                        current_element.attribute_.underlining_ =
                            terminalpp::ansi::graphics::underlining::underlined;
                        break;
                }

                current_state = state::normal;
                break;

            case state::low_colour_foreground :
                current_element.attribute_.foreground_colour_ =
                    terminalpp::low_colour(char(current_character - '0'));
                current_state = state::normal;
                break;

            case state::high_colour_foreground_red :
                current_element.attribute_.foreground_colour_ =
                    terminalpp::high_colour(char(current_character - '0'), 0, 0);
                current_state = state::high_colour_foreground_green;
                break;

            case state::high_colour_foreground_green :
                current_element.attribute_.foreground_colour_
                    .high_colour_.green_ = char(current_character - '0');
                current_state = state::high_colour_foreground_blue;
                break;

            case state::high_colour_foreground_blue :
                current_element.attribute_.foreground_colour_
                    .high_colour_.blue_ = char(current_character - '0');
                current_state = state::normal;
                break;

            case state::greyscale_colour_foreground_0 :
                current_element.attribute_.foreground_colour_ =
                    terminalpp::greyscale_colour(
                        char((current_character - '0') * 10));
                current_state = state::greyscale_colour_foreground_1;
                break;

            case state::greyscale_colour_foreground_1 :
                current_element.attribute_.foreground_colour_
                    .greyscale_colour_.shade_ += char(current_character - '0');
                current_state = state::normal;
                break;

            case state::low_colour_background :
                current_element.attribute_.background_colour_ =
                    terminalpp::low_colour(char(current_character - '0'));
                current_state = state::normal;
                break;

            case state::high_colour_background_red :
                current_element.attribute_.background_colour_ =
                    terminalpp::high_colour(char(current_character - '0'), 0, 0);
                current_state = state::high_colour_background_green;
                break;

            case state::high_colour_background_green :
                current_element.attribute_.background_colour_
                    .high_colour_.green_ = char(current_character - '0');
                current_state = state::high_colour_background_blue;
                break;

            case state::high_colour_background_blue :
                current_element.attribute_.background_colour_
                    .high_colour_.blue_ = char(current_character - '0');
                current_state = state::normal;
                break;

            case state::greyscale_colour_background_0 :
                current_element.attribute_.background_colour_ =
                    terminalpp::greyscale_colour(
                        char((current_character - '0') * 10));
                current_state = state::greyscale_colour_background_1;
                break;

            case state::greyscale_colour_background_1 :
                current_element.attribute_.background_colour_
                    .greyscale_colour_.shade_ += char(current_character - '0');
                current_state = state::normal;
                break;
                
            case state::utf8_0 :
                current_element.glyph_.charset_ =
                    terminalpp::ansi::charset::utf8;
                current_element.glyph_.ucharacter_[0] = current_character;
                current_state = state::utf8_1;
                break;
                
            case state::utf8_1 :
                current_element.glyph_.ucharacter_[1] = current_character;
                current_state = state::utf8_2;
                break;
                
            case state::utf8_2 :
                current_element.glyph_.ucharacter_[2] = current_character;
                current_state = state::utf8_3;
                break;
                
            case state::utf8_3 :
                utf8_encode_glyph(current_element.glyph_, current_character);
                current_state = state::normal;
                element_complete = true;
                break;
        }

        if (element_complete)
        {
            result.push_back(current_element);
            element_complete = false;
        }
    }

    return result;
}


}}
