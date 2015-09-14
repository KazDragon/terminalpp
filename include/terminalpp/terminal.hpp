#ifndef TERMINALPP_TERMINAL_HPP_
#define TERMINALPP_TERMINAL_HPP_

#include "terminalpp/point.hpp"
#include "terminalpp/string.hpp"
#include <boost/optional.hpp>
#include <string>

namespace terminalpp {
    
//* =========================================================================
/// \brief A class responsible for combining the knowledge and state of a
/// terminal window to know what the best way to respresent a given string is.
//* =========================================================================
class terminal
{
public :
    enum class control_mode
    {
        seven_bit,
        eight_bit,
    };

    struct behaviour
    {
        constexpr behaviour()
          : can_use_eight_bit_control_codes(false),
            uses_eight_bit_control_codes_by_default(false),
            supports_cha(true),
            supports_cha_default(true),
            supports_cup_default_row(false),
            supports_cup_default_column(true),
            supports_cup_default_all(true)
        {
        }
        
        // Eight bit control codes save on a character each time an ANSI 
        // control code is used.  This could amount to quite the saving over
        // time.
        bool can_use_eight_bit_control_codes : 1;
        
        // If a terminal can use eight bit control codes, it may require a
        // code to enable that sequence.  Some terminals may default to using
        // eight bit control codes, but not understand the enable sequence, so
        // it should only be used if actually required.
        bool uses_eight_bit_control_codes_by_default : 1;
        
        // True if the terminal supports Cursor Horizontal Absolute
        bool supports_cha : 1;
        
        // True if the terminal supports the use of a default argument
        // in Cursor Horizontal Absolute
        bool supports_cha_default : 1;
        
        // True if the terminal supports the use of a default row argument
        // (only) in Cursor Position.
        bool supports_cup_default_row : 1;
        
        // True if the terminal supports the use of a default column argument
        // (only) in Cursor Position.
        bool supports_cup_default_column : 1;
        
        // True if the terminal supports the use of both arguments being 
        // default in Cursor Position
        bool supports_cup_default_all : 1;
    };
    
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    explicit terminal(behaviour const &beh = behaviour{});
    
    //* =====================================================================
    /// \brief Returns a string that will initialize the terminal.
    /// Based on the behaviour passed in the constructor, returns a string
    /// that can be sent to the terminal to put it into the best control mode
    /// that it can handle.
    //* =====================================================================
    std::string init();
    
    //* =====================================================================
    /// \brief Show the cursor.
    //* =====================================================================
    std::string show_cursor();
    
    //* =====================================================================
    /// \brief Hide the cursor.
    //* =====================================================================
    std::string hide_cursor();
    
    //* =====================================================================
    /// \brief Saves the current cursor position.
    //* =====================================================================
    std::string save_cursor();
    
    //* =====================================================================
    /// \brief Restores the previously saved cursor position.
    //* =====================================================================
    std::string restore_cursor();
    
    //* =====================================================================
    /// \brief Move the cursor to the specified position.  Note: terminals are
    /// 1-based.  I.e. the origin position is (1,1).
    //* =====================================================================
    std::string move_cursor(point const &pt);
    
private :
    enum class cursor_mode : bool
    {
        hidden,
        shown,
    };
    
    behaviour              behaviour_;
    control_mode           control_mode_ = control_mode::seven_bit;
    cursor_mode            cursor_mode_  = cursor_mode::shown;
    boost::optional<point> cursor_position_;
    boost::optional<point> saved_cursor_position_;
};

}

#endif
