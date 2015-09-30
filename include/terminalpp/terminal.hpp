#ifndef TERMINALPP_TERMINAL_HPP_
#define TERMINALPP_TERMINAL_HPP_

#include "terminalpp/extent.hpp"
#include "terminalpp/point.hpp"
#include "terminalpp/string.hpp"
#include <boost/optional.hpp>
#include <string>

namespace terminalpp {
    
//* =========================================================================
/// \brief A class responsible for combining the knowledge and state of a
/// terminal window to know what the best way to respresent a given string is.
/// \par
/// Note: the terminal itself does not send any results anywhere -- instead,
/// a string is returned that is an ANSI sequence of character that will cause
/// the required action to be accomplished on the remote terminal -- although
/// the function descriptions are written as if that were so.  That is just 
/// for clarity's sake (it's easier to write "moves the cursor to the 
/// position" than "returns a string that represents the ANSI sequence of 
/// characters that will move the cursor to the position."
//* =========================================================================
class terminal
{
public :
    enum class control_mode
    {
        seven_bit,
        eight_bit,
    };
    
    // In erase_in_display, there is the choice of erasing every line
    // above the cursor, every line below the cursor, or the entire
    // display.
    enum class erase_display {
        below,
        above,
        all
    };

    // In erase_in_line, there is the choice of eraseing everything
    // to the left of the cursor, everything to the right of the cursor,
    // or everything on the current line.
    enum class erase_line {
        right,
        left,
        all
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
    /// \brief Sets the (local) size of the terminal.
    /// There is nothing transmitted by this.  This is so that the client
    /// can set how large the terminal is expected to be.  This affects 
    /// things like when does a cursor scroll the screen, etc.
    //* =====================================================================
    void set_size(extent const &size);
    
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
    
    //* =====================================================================
    /// \brief Writes the specified sequence of characters.
    //* =====================================================================
    std::string write(string const &str);
    
    //* =====================================================================
    /// \brief Erases the display in the specified manner.
    //* =====================================================================
    std::string erase_in_display(erase_display how);

    //* =====================================================================
    /// \brief Erases the current line in the specified manner.
    //* =====================================================================
    std::string erase_in_line(erase_line how);
    
private :
    enum class cursor_mode : bool
    {
        hidden,
        shown,
    };
    
    behaviour                behaviour_;
    control_mode             control_mode_ = control_mode::seven_bit;
    cursor_mode              cursor_mode_  = cursor_mode::shown;
    boost::optional<point>   cursor_position_;
    boost::optional<point>   saved_cursor_position_;
    boost::optional<extent>  size_;
    element                  last_element_;
};

}

#endif
