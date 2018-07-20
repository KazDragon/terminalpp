#pragma once

#include "terminalpp/extent.hpp"
#include "terminalpp/point.hpp"
#include "terminalpp/string.hpp"
#include "terminalpp/token.hpp"
#include "nonstd/span.hpp"
#include <functional>
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
    /// \brief Destructor.
    //* =====================================================================
    virtual ~terminal() = default;

    //* =====================================================================
    /// \brief Returns a string that will initialize the terminal.
    //* =====================================================================
    virtual std::string init() = 0;

    //* =====================================================================
    /// \brief Returns a string that will enable the best possible mouse
    /// mode for the terminal.
    //* =====================================================================
    virtual std::string enable_mouse() = 0;

    //* =====================================================================
    /// \brief Returns a string that will disable the mouse.
    //* =====================================================================
    virtual std::string disable_mouse() = 0;

    //* =====================================================================
    /// \brief Returns a string that will set the window title of the
    /// terminal.
    //* =====================================================================
    virtual std::string set_window_title(std::string const &title) = 0;

    //* =====================================================================
    /// \brief Sets the (local) size of the terminal.
    /// There is nothing transmitted by this.  This is so that the client
    /// can set how large the terminal is expected to be.  This affects
    /// things like when does a cursor scroll the screen, etc.
    //* =====================================================================
    virtual void set_size(extent const &size) = 0;

    //* =====================================================================
    /// \brief Show the cursor.
    //* =====================================================================
    virtual std::string show_cursor() = 0;

    //* =====================================================================
    /// \brief Hide the cursor.
    //* =====================================================================
    virtual std::string hide_cursor() = 0;

    //* =====================================================================
    /// \brief Saves the current cursor position.
    //* =====================================================================
    virtual std::string save_cursor() = 0;

    //* =====================================================================
    /// \brief Restores the previously saved cursor position.
    //* =====================================================================
    virtual std::string restore_cursor() = 0;

    //* =====================================================================
    /// \brief Move the cursor to the specified position.  Note: terminals are
    /// 1-based.  I.e. the origin position is (1,1).
    //* =====================================================================
    virtual std::string move_cursor(point const &pt) = 0;

    //* =====================================================================
    /// \brief Reads a stream of data, passing the result of parsing the
    /// data to the continuation function specified.
    //* =====================================================================
    virtual void read(
        std::string const &data,
        std::function<void (nonstd::span<token> const &)> const &cont) = 0;

    //* =====================================================================
    /// \brief Writes the specified element.
    //* =====================================================================
    virtual std::string write(element const &elem) = 0;

    //* =====================================================================
    /// \brief Writes the specified sequence of characters.
    //* =====================================================================
    virtual std::string write(string const &str) = 0;

    //* =====================================================================
    /// \brief Erases the display in the specified manner.
    //* =====================================================================
    virtual std::string erase_in_display(erase_display how) = 0;

    //* =====================================================================
    /// \brief Erases the current line in the specified manner.
    //* =====================================================================
    virtual std::string erase_in_line(erase_line how) = 0;

    //* =====================================================================
    /// \brief Sets the terminal to the normal screen buffer (default).
    //* =====================================================================
    virtual std::string use_normal_screen_buffer() = 0;

    //* =====================================================================
    /// \brief Sets the terminal to the alternate screen buffer.
    //* =====================================================================
    virtual std::string use_alternate_screen_buffer() = 0;
};

}
