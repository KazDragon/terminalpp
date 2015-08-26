#include "terminalpp/detail/string_to_elements.hpp"

#include <cstring>

namespace terminalpp { namespace detail {

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
        locale,
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

                    case 'l' :
                        current_state = state::locale;
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

            case state::locale :
                current_element.glyph_.locale_ = current_character;
                current_state = state::normal;
                break;

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
