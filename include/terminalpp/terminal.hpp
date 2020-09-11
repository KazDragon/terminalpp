#pragma once

#include "terminalpp/behaviour.hpp"
#include "terminalpp/extent.hpp"
#include "terminalpp/point.hpp"
#include "terminalpp/string.hpp"
#include "terminalpp/token.hpp"
#include "terminalpp/detail/parser.hpp"
#include "terminalpp/detail/terminal_control.hpp"
#include <boost/optional.hpp>
#include <string>
#include <vector>

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
class TERMINALPP_EXPORT terminal
{
public :
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

    //* =====================================================================
    /// \brief Constructor.
    //* =====================================================================
    explicit terminal(behaviour const &beh = behaviour{});

    //* =====================================================================
    /// \brief Returns a string that will initialize the terminal.
    //* =====================================================================
    std::string init();

    //* =====================================================================
    /// \brief Returns a string that will enable the best possible mouse
    /// mode for the terminal.
    //* =====================================================================
    std::string enable_mouse();

    //* =====================================================================
    /// \brief Returns a string that will disable the mouse.
    //* =====================================================================
    std::string disable_mouse();

    //* =====================================================================
    /// \brief Returns a string that will set the window title of the
    /// terminal.
    //* =====================================================================
    std::string set_window_title(std::string const &title);

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
    /// \brief Move the cursor to the specified position.  Note: although
    /// terminals are 1-based in output, this class uses (0,0) as the top-
    /// left cell and translates it automatically.
    //* =====================================================================
    std::string move_cursor(point const &pt);

    //* =====================================================================
    /// \brief Moves the cursor across the x-axis.
    //* =====================================================================
    std::string move_cursor_horizontally(coordinate_type x);

    //* =====================================================================
    /// \brief Moves the cursor across the y-axis.
    //* =====================================================================
    std::string move_cursor_vertically(coordinate_type y);

    //* =====================================================================
    /// \brief Reads a stream of data.
    //* =====================================================================
    std::vector<token> read(std::string const &data);

    //* =====================================================================
    /// \brief Writes the specified element.
    //* =====================================================================
    std::string write(element const &elem);

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

    //* =====================================================================
    /// \brief Sets the terminal to the normal screen buffer (default).
    //* =====================================================================
    std::string use_normal_screen_buffer();

    //* =====================================================================
    /// \brief Sets the terminal to the alternate screen buffer.
    //* =====================================================================
    std::string use_alternate_screen_buffer();

private :
    enum class cursor_mode : bool
    {
        hidden,
        shown,
    };

    behaviour                     behaviour_;
    detail::control_mode          control_mode_ = detail::control_mode::seven_bit;
    boost::optional<cursor_mode>  cursor_mode_;
    boost::optional<point>        cursor_position_;
    boost::optional<point>        saved_cursor_position_;
    boost::optional<extent>       size_;
    boost::optional<element>      last_element_;

    detail::parser                parser_;
};

}
