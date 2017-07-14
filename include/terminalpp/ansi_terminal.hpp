#pragma once

#include "terminalpp/behaviour.hpp"
#include "terminalpp/terminal.hpp"
#include "terminalpp/detail/parser.hpp"
#include "terminalpp/detail/terminal_control.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A default implementation of the terminal interface.
//* =========================================================================
class TERMINALPP_EXPORT ansi_terminal
  : public terminal
{
public :
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    explicit ansi_terminal(behaviour const &beh = behaviour{});

    //* =====================================================================
    /// \brief Returns a string that will initialize the terminal.
    /// Based on the behaviour passed in the constructor, returns a string
    /// that can be sent to the terminal to put it into the best control mode
    /// that it can handle.
    //* =====================================================================
    std::string init() override;

    //* =====================================================================
    /// \brief Returns a string that will enable the best possible mouse
    /// mode for the terminal.
    //* =====================================================================
    std::string enable_mouse() override;

    //* =====================================================================
    /// \brief Returns a string that will disable the mouse.
    //* =====================================================================
    std::string disable_mouse() override;

    //* =====================================================================
    /// \brief Returns a string that will set the window title of the
    /// terminal.
    //* =====================================================================
    std::string set_window_title(std::string const &title) override;

    //* =====================================================================
    /// \brief Sets the (local) size of the terminal.
    /// There is nothing transmitted by this.  This is so that the client
    /// can set how large the terminal is expected to be.  This affects
    /// things like when does a cursor scroll the screen, etc.
    //* =====================================================================
    void set_size(extent const &size) override;

    //* =====================================================================
    /// \brief Show the cursor.
    //* =====================================================================
    std::string show_cursor() override;

    //* =====================================================================
    /// \brief Hide the cursor.
    //* =====================================================================
    std::string hide_cursor() override;

    //* =====================================================================
    /// \brief Saves the current cursor position.
    //* =====================================================================
    std::string save_cursor() override;

    //* =====================================================================
    /// \brief Restores the previously saved cursor position.
    //* =====================================================================
    std::string restore_cursor() override;

    //* =====================================================================
    /// \brief Move the cursor to the specified position.  Note: terminals are
    /// 1-based.  I.e. the origin position is (1,1).
    //* =====================================================================
    std::string move_cursor(point const &pt) override;

    //* =====================================================================
    /// \brief Reads a stream of data.
    //* =====================================================================
    std::vector<token> read(std::string const &data) override;

    //* =====================================================================
    /// \brief Writes the specified element.
    //* =====================================================================
    std::string write(element const &elem) override;

    //* =====================================================================
    /// \brief Writes the specified sequence of characters.
    //* =====================================================================
    std::string write(string const &str) override;

    //* =====================================================================
    /// \brief Erases the display in the specified manner.
    //* =====================================================================
    std::string erase_in_display(erase_display how) override;

    //* =====================================================================
    /// \brief Erases the current line in the specified manner.
    //* =====================================================================
    std::string erase_in_line(erase_line how) override;

    //* =====================================================================
    /// \brief Sets the terminal to the normal screen buffer (default).
    //* =====================================================================
    std::string use_normal_screen_buffer() override;

    //* =====================================================================
    /// \brief Sets the terminal to the alternate screen buffer.
    //* =====================================================================
    std::string use_alternate_screen_buffer() override;

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
    element                       last_element_;

    detail::parser                parser_;
};

}
