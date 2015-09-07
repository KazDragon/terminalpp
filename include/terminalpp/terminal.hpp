#ifndef TERMINALPP_TERMINAL_HPP_
#define TERMINALPP_TERMINAL_HPP_

#include "terminalpp/string.hpp"
#include <string>

namespace terminalpp {
    
//* =========================================================================
/// \brief A class responsible for combining the knowledge and state of a
/// terminal window to know what the best way to respresent a given string is.
//* =========================================================================
class terminal
{
public :
    struct behaviour
    {
        // Eight bit control codes save on a character each time an ANSI 
        // control code is used.  This could amount to quite the saving over
        // time.
        bool can_use_eight_bit_control_codes         = false;
        
        // If a terminal can use eight bit control codes, it may require a
        // code to enable that sequence.  Some terminals may default to using
        // eight bit control codes, but not understand the enable sequence, so
        // it should only be used if actually required.
        bool uses_eight_bit_control_codes_by_default = false;
    };
    
    constexpr terminal(behaviour const &beh)
      : behaviour_(beh),
        control_mode_(control_mode::seven_bit)
    {
    }
    
    /**
     * \brief Returns a string that will initialize the terminal.
     * Based on the behaviour passed in the constructor, returns a string
     * that can be sent to the terminal to put it into the best control mode
     * that it can handle.
     */
    std::string init();
    
private :
    enum class control_mode
    {
        seven_bit,
        eight_bit,
    };
    
    behaviour    behaviour_;
    control_mode control_mode_;
};

}

#endif
