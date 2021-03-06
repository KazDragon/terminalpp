#pragma once

#include "terminalpp/detail/terminal_reader.hpp"
#include "terminalpp/detail/terminal_writer.hpp"
#include "terminalpp/core.hpp"
#include "terminalpp/behaviour.hpp"
#include "terminalpp/extent.hpp"
#include "terminalpp/point.hpp"
#include "terminalpp/terminal_state.hpp"
#include "terminalpp/token.hpp"
#include "terminalpp/ansi/control_characters.hpp"
#include "terminalpp/ansi/csi.hpp"
#include "terminalpp/ansi/dec_private_mode.hpp"
#include "terminalpp/ansi/osc.hpp"
#include <fmt/format.h>
#include <string>

namespace terminalpp {

//* =========================================================================
/// \brief A class that encapsulates a terminal.
///
/// The class, together with the set of manipulators provide a way of
/// writing to a terminal.  It is agnostic to the actual write method
/// used.  The writing method is passed as a WriteContinuation, which is
/// called for the required output.
//* =========================================================================
class TERMINALPP_EXPORT terminal
{
public:
    //* =====================================================================
    /// \brief Constructor.
    ///
    /// \tparam WriteContinuation is a callable that matches the
    /// signature \code void (bytes) \endcode.
    //* =====================================================================
    template <class WriteContinuation>
    explicit terminal(
        WriteContinuation &&cont,
        behaviour const &beh = behaviour{})
      : behaviour_(beh)
    {
        write(std::forward<WriteContinuation>(cont))
            << detail::initialise_terminal();
    }

    //* =====================================================================
    /// \brief Sets the size of the terminal.
    /// This is used to determine cursor locations when writing text that 
    /// wraps at the end of the line, etc.
    //* =====================================================================
    void set_size(terminalpp::extent size)
    {
        state_.terminal_size_ = size;
    }
    
    //* =====================================================================
    /// \brief Write to the terminal.
    ///
    /// \par Usage
    /// Stream in text, or use manipulators to modify the state of the 
    /// terminal.
    /// \code
    /// void raw_write(terminalpp::bytes);
    /// terminal term{raw_write};
    /// term.write(raw_write) << "Hello, world!"
    ///                       << move_cursor({17, 29});
    /// \endcode
    /// \par Writing your own manipulators.
    /// A manipulator is streamable to a writer if is has a member function
    /// with the following signature:
    /// \code
    /// template <class WriteContinuation>
    /// void operator()(terminalpp::terminal_state &, WriteContinuation &&);
    /// \endcode
    //* =====================================================================
    template <class WriteContinuation>
    detail::terminal_writer<WriteContinuation> write(WriteContinuation &&wc)
    {
        return detail::terminal_writer<WriteContinuation>(
            behaviour_,
            state_,
            std::forward<WriteContinuation>(wc));
    }

    //* =====================================================================
    /// \brief Read from the terminal.
    ///
    /// \par Usage
    /// Stream in bytes, and the resultant tokens parsed from the stream will
    /// be sent to the continuation passed in.
    /// \code
    /// using namespace terminalpp::literals;
    /// void read_tokens(terminalpp::tokens);
    /// void raw_write(terminalpp::bytes);
    /// terminal term{raw_write};
    /// term.read(read_tokens) << "\\x1B[13~"_tb;
    /// // read_tokens was called with a collection of one token, which
    /// // contained the f3 virtual key.
    //* =====================================================================
    template <class ReadContinuation>
    detail::terminal_reader<ReadContinuation> read(ReadContinuation &&rc)
    {
        return detail::terminal_reader<ReadContinuation>(
            behaviour_,
            state_,
            std::forward<ReadContinuation>(rc));
    }

private:
    behaviour behaviour_;
    terminal_state state_;
};

//* =========================================================================
/// \brief A manipulator that moves the cursor to a new location.
//* =========================================================================
class TERMINALPP_EXPORT move_cursor
{
public:
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    constexpr move_cursor(point const &destination)
      : destination_(destination)
    {
    }

    //* =====================================================================
    /// \brief Writes the ANSI protocol codes necessary to move the cursor to
    /// the initialized location to the continuation.
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state, 
        WriteContinuation &&cont) const
    {
        if (!state.cursor_position_)
        {
            write_cursor_position(beh, cont);
        }
        else
        {
            move_from_known_position(beh, state, cont);
        }

        state.cursor_position_ = destination_;
    }

private:
    // ======================================================================
    // MOVE_FROM_KNOWN_POSITION
    // ======================================================================
    template <class WriteContinuation>
    void move_from_known_position(
        behaviour const &beh,
        terminal_state &state,
        WriteContinuation &&cont) const
    {
        if (*state.cursor_position_ != destination_)
        {
            if (state.cursor_position_->y_ == destination_.y_)
            {
                write_cursor_horizontal_absolute(beh, cont);
            }
            else if (state.cursor_position_->x_ == destination_.x_)
            {
                auto const distance = 
                    state.cursor_position_->y_ - destination_.y_;

                if (distance > 0)
                {
                    write_cursor_up(beh, distance, cont);
                }
                else
                {
                    write_cursor_down(beh, -distance, cont);
                }
            }
            else
            {
                write_cursor_position(beh, cont);
            }
        }
    }

    // ======================================================================
    // WRITE_CURSOR_POSITION
    // ======================================================================
    template <class WriteContinuation>
    void write_cursor_position(
        behaviour const &beh,
        WriteContinuation &&cont) const
    {
        using namespace terminalpp::literals;
        using namespace fmt::literals;

        detail::csi(beh, cont);

        if (destination_.x_ != 0 || destination_.y_ != 0)
        {
            if (destination_.x_ == 0)
            {
                cont(to_bytes("{}"_format(destination_.y_ + 1)));
            }
            else
            {
                cont(to_bytes("{};{}"_format(
                    destination_.y_ + 1,
                    destination_.x_ + 1
                )));
            }
        }

        static byte_storage const cursor_position_suffix = {
            ansi::csi::cursor_position
        };

        cont(cursor_position_suffix);
    }

    // ======================================================================
    // WRITE_CURSOR_HORIZONTAL_ABSOLUTE
    // ======================================================================
    template <class WriteContinuation>
    void write_cursor_horizontal_absolute(
        behaviour const &beh,
        WriteContinuation &&cont) const
    {
        using namespace terminalpp::literals;
        using namespace fmt::literals;

        detail::csi(beh, cont);

        if (destination_.x_ != 0)
        {
            cont(to_bytes("{}"_format(destination_.x_ + 1)));
        }

        static byte_storage const cursor_horizontal_absolute_suffix = {
            ansi::csi::cursor_horizontal_absolute
        };

        cont(cursor_horizontal_absolute_suffix);
    }

    // ======================================================================
    // WRITE_CURSOR_UP
    // ======================================================================
    template <class WriteContinuation>
    void write_cursor_up(
        behaviour const &beh,
        coordinate_type const distance,
        WriteContinuation &&cont) const
    {
        using namespace terminalpp::literals;
        using namespace fmt::literals;

        detail::csi(beh, cont);

        if (distance != 1)
        {
            cont(to_bytes("{}"_format(distance)));
        }

        static byte_storage const cursor_up_suffix = {
            ansi::csi::cursor_up
        };

        cont(cursor_up_suffix);
    }

    // ======================================================================
    // WRITE_CURSOR_DOWN
    // ======================================================================
    template <class WriteContinuation>
    void write_cursor_down(
        behaviour const &beh,
        coordinate_type const distance,
        WriteContinuation &&cont) const
    {
        using namespace terminalpp::literals;
        using namespace fmt::literals;

        detail::csi(beh, cont);

        if (distance != 1)
        {
            cont(to_bytes("{}"_format(distance)));
        }

        static byte_storage const cursor_down_suffix = {
            ansi::csi::cursor_down
        };

        cont(cursor_down_suffix);
    }

    point destination_;
};

//* =========================================================================
/// \brief A manipulator that hides the cursor.
//* =========================================================================
class TERMINALPP_EXPORT hide_cursor
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to hide the cursor to the
    /// continuation.
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        WriteContinuation &&cont) const
    {
        if (!state.cursor_visible_ || *state.cursor_visible_)
        {
            detail::dec_pm(beh, cont);
            cont({
                std::cbegin(ansi::dec_pm::cursor), 
                std::cend(ansi::dec_pm::cursor)});
            cont({
                std::cbegin(ansi::dec_pm::reset),
                std::cend(ansi::dec_pm::reset)});
        }

        state.cursor_visible_ = false;
    }
};

//* =========================================================================
/// \brief A manipulator that shows the cursor.
//* =========================================================================
class TERMINALPP_EXPORT show_cursor
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to show the cursor to the
    /// continuation.
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        WriteContinuation &&cont) const
    {
        if (!state.cursor_visible_ || !*state.cursor_visible_)
        {
            detail::dec_pm(beh, cont);
            cont({
                std::cbegin(ansi::dec_pm::cursor), 
                std::cend(ansi::dec_pm::cursor)});
            cont({
                std::cbegin(ansi::dec_pm::set),
                std::cend(ansi::dec_pm::set)});
        }

        state.cursor_visible_ = true;
    }
};

//* =========================================================================
/// \brief A manipulator that erases the entire display.
//* =========================================================================
class TERMINALPP_EXPORT erase_display
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to erase the display
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        WriteContinuation &&cont) const
    {
        detail::csi(beh, cont);

        static byte_storage const erase_all_suffix = {  
            ansi::csi::erase_in_display_all,
            ansi::csi::erase_in_display,
        };

        cont(erase_all_suffix);
    }
};

//* =========================================================================
/// \brief A manipulator that erases the display from the line of the cursor
/// to the top.
//* =========================================================================
class TERMINALPP_EXPORT erase_display_above
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to erase the display
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        WriteContinuation &&cont) const
    {
        detail::csi(beh, cont);

        static byte_storage const erase_above_suffix = {  
            ansi::csi::erase_in_display_above,
            ansi::csi::erase_in_display,
        };

        cont(erase_above_suffix);
    }
};

//* =========================================================================
/// \brief A manipulator that erases the display from the line of the cursor
/// to the bottom.
//* =========================================================================
class TERMINALPP_EXPORT erase_display_below
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to erase the display
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        WriteContinuation &&cont) const
    {
        detail::csi(beh, cont);

        static byte_storage const erase_below_suffix = {  
            // The constant for erase below is 0, which can be elided
            ansi::csi::erase_in_display,
        };

        cont(erase_below_suffix);
    }
};

//* =========================================================================
/// \brief A manipulator that erases the current line of the display.
//* =========================================================================
class TERMINALPP_EXPORT erase_line
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to erase the display
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        WriteContinuation &&cont) const
    {
        detail::csi(beh, cont);

        static byte_storage const erase_line_suffix = {  
            ansi::csi::erase_in_line_all,
            ansi::csi::erase_in_line,
        };

        cont(erase_line_suffix);
    }
};

//* =========================================================================
/// \brief A manipulator that erases from the current cursor position to the
/// beginning of the line.
//* =========================================================================
class TERMINALPP_EXPORT erase_line_left
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to erase the display
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        WriteContinuation &&cont) const
    {
        detail::csi(beh, cont);

        static byte_storage const erase_line_left_suffix = {  
            ansi::csi::erase_in_line_left,
            ansi::csi::erase_in_line,
        };

        cont(erase_line_left_suffix);
    }
};

//* =========================================================================
/// \brief A manipulator that erases from the current cursor position to the
/// beginning of the line.
//* =========================================================================
class TERMINALPP_EXPORT erase_line_right
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to erase the display
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        WriteContinuation &&cont) const
    {
        detail::csi(beh, cont);

        static byte_storage const erase_line_right_suffix = {  
            // The code for erase right is 0, which can be elided.
            ansi::csi::erase_in_line,
        };

        cont(erase_line_right_suffix);
    }
};

//* =========================================================================
/// \brief A manipulator that enables mouse clicks according to the terminal
/// behaviour.
//* =========================================================================
class TERMINALPP_EXPORT enable_mouse
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to enable the mouse
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        WriteContinuation &&cont) const
    {
        if (beh.supports_basic_mouse_tracking)
        {
            detail::dec_pm(beh, cont);
            cont({
                std::cbegin(ansi::dec_pm::basic_mouse_tracking),
                std::cend(ansi::dec_pm::basic_mouse_tracking)});
            cont({
                std::cbegin(ansi::dec_pm::set),
                std::cend(ansi::dec_pm::set)});
        }
        else if (beh.supports_all_mouse_motion_tracking)
        {
            detail::dec_pm(beh, cont);
            cont({
                std::cbegin(ansi::dec_pm::all_motion_mouse_tracking),
                std::cend(ansi::dec_pm::all_motion_mouse_tracking)});
            cont({
                std::cbegin(ansi::dec_pm::set),
                std::cend(ansi::dec_pm::set)});
        }
    }
};

//* =========================================================================
/// \brief A manipulator that disables mouse clicks according to the terminal
/// behaviour.
//* =========================================================================
class TERMINALPP_EXPORT disable_mouse
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to disable the mouse
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        WriteContinuation &&cont) const
    {
        if (beh.supports_basic_mouse_tracking)
        {
            detail::dec_pm(beh, cont);
            cont({
                std::cbegin(ansi::dec_pm::basic_mouse_tracking),
                std::cend(ansi::dec_pm::basic_mouse_tracking)});
            cont({
                std::cbegin(ansi::dec_pm::reset),
                std::cend(ansi::dec_pm::reset)});
        }
        else if (beh.supports_all_mouse_motion_tracking)
        {
            detail::dec_pm(beh, cont);
            cont({
                std::cbegin(ansi::dec_pm::all_motion_mouse_tracking),
                std::cend(ansi::dec_pm::all_motion_mouse_tracking)});
            cont({
                std::cbegin(ansi::dec_pm::reset),
                std::cend(ansi::dec_pm::reset)});
        }
    }
};

//* =========================================================================
/// \brief A manipulator that sets the window title according to the terminal
/// behaviour.
//* =========================================================================
class TERMINALPP_EXPORT set_window_title
{
public:
    set_window_title(std::string const &title)
      : title_(title)
    {
    }
    
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to disable the mouse
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        WriteContinuation &&cont) const
    {
        static byte_storage const set_window_title_prefix = {
            ansi::osc::set_window_title,
            ansi::ps,
        };

        if (beh.supports_window_title_bel)
        {
            detail::osc(beh, cont);

            cont(set_window_title_prefix);
            cont({
                reinterpret_cast<byte const *>(title_.data()),
                title_.size()});

            static byte_storage const set_window_title_bel_suffix = {
                detail::ascii::bel
            };

            cont(set_window_title_bel_suffix);
        }
        else if (beh.supports_window_title_st)
        {
            detail::osc(beh, cont);

            cont(set_window_title_prefix);
            cont({
                reinterpret_cast<byte const *>(title_.data()),
                title_.size()});

            detail::st(beh, cont);
        }
    }

private:
    std::string title_;
};

//* =========================================================================
/// \brief A manipulator that enables the use of the normal screen buffer.
//* =========================================================================
class TERMINALPP_EXPORT use_normal_screen_buffer
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to enable the mouse
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        WriteContinuation &&cont) const
    {
        detail::dec_pm(beh, cont);

        cont({
            std::cbegin(ansi::dec_pm::use_alternate_screen_buffer),
            std::cend(ansi::dec_pm::use_alternate_screen_buffer)});

        cont({
            std::cbegin(ansi::dec_pm::reset),
            std::cend(ansi::dec_pm::reset) });
    }
};

//* =========================================================================
/// \brief A manipulator that enables the use of the alternate screen buffer.
//* =========================================================================
class TERMINALPP_EXPORT use_alternate_screen_buffer
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to enable the mouse
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        WriteContinuation &&cont) const
    {
        detail::dec_pm(beh, cont);

        cont({
            std::cbegin(ansi::dec_pm::use_alternate_screen_buffer),
            std::cend(ansi::dec_pm::use_alternate_screen_buffer) });

        cont({
            std::cbegin(ansi::dec_pm::set),
            std::cend(ansi::dec_pm::set) });
    }
};

}
