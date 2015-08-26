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
