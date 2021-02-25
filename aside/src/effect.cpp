#include "terminalpp/effect.hpp"
#include <iostream>

namespace terminalpp {

// ==========================================================================
// OPERATOR<<(STREAM, INTENSITY)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, intensity const &effect)
{
    switch (effect.value_)
    {
        default :
            // Fall-through
        case terminalpp::ansi::graphics::intensity::normal :
            return out << "normal";

        case terminalpp::ansi::graphics::intensity::bold :
            return out << "bold";

        case terminalpp::ansi::graphics::intensity::faint :
            return out << "faint";
    }
}

// ==========================================================================
// OPERATOR<<(STREAM, UNDERLINING)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, underlining const &effect)
{
    return out
        << (effect.value_ == terminalpp::ansi::graphics::underlining::underlined
          ? "underlined"
          : "not underlined");
}

// ==========================================================================
// OPERATOR<<(STREAM, POLARITY)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, polarity const &effect)
{
    return out
        << (effect.value_ == terminalpp::ansi::graphics::polarity::positive
          ? "positive"
          : "negative");
}

// ==========================================================================
// OPERATOR<<(STREAM, BLINKING)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, blinking const &effect)
{
    return out
        << (effect.value_ == terminalpp::ansi::graphics::blinking::blink
          ? "blinking"
          : "steady");
}

}
