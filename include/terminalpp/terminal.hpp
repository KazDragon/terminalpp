#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/behaviour.hpp"
#include "terminalpp/terminal_state.hpp"
#include "terminalpp/token.hpp"
#include "terminalpp/string.hpp"
#include <boost/range/algorithm/for_each.hpp>
#include <functional>

namespace terminalpp {

using read_function = std::function<void (terminalpp::tokens)>;
using write_function = std::function<void (terminalpp::bytes)>;

//* =========================================================================
/// \brief A manipulator that converts encoded attribute strings into ANSI 
/// protocol bytes.
//* =========================================================================
class TERMINALPP_EXPORT write_element
{
public:
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    constexpr explicit write_element(terminalpp::element const &elem)
      : element_(elem)
    {
    }

    //* =====================================================================
    /// \brief Convert the text and write the result to the write function
    //* =====================================================================
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        write_function const &write_fn) const;

private:        
    terminalpp::element element_;
};

//* =========================================================================
/// \brief A manipulator that outputs ANSI protocol bytes for the default
/// attribute, if necessary.
///
/// This occurs if the current attribute is unknown, e.g. at the start of 
/// output, or at a line break with certain terminals.
//* =========================================================================
struct TERMINALPP_EXPORT write_optional_default_attribute
{
    //* =====================================================================
    /// \brief Writes the default attribute to the terminal if necessary.
    //* =====================================================================
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        write_function const &write_fn) const;
};

//* =========================================================================
/// \brief A class that encapsulates a terminal.
///
/// A class that is used to stream data in and out of a terminal.
//* =========================================================================
class TERMINALPP_EXPORT terminal
{
public:

    //* =====================================================================
    /// \brief Constructor.
    //* =====================================================================
    explicit terminal(
        read_function read_fn,
        write_function write_fn,
        behaviour beh = behaviour{});

    //* =====================================================================
    /// \brief Sets the size of the terminal.
    /// This is used to determine cursor locations when writing text that 
    /// wraps at the end of the line, etc.
    //* =====================================================================
    void set_size(extent size);
    
    //* =====================================================================
    /// \brief Write to the terminal.
    ///
    /// \par Usage
    /// Stream in text, or use manipulators to modify the state of the 
    /// terminal.
    /// \code
    /// void raw_read(terminalpp::tokens);
    /// void raw_write(terminalpp::bytes);
    /// terminal term{raw_read, raw_write};
    /// term << "Hello, world!"
    ///      << move_cursor({17, 29});
    /// \endcode
    /// \par Writing your own manipulators.
    /// A manipulator is streamable to a writer if is has a member function
    /// with the following signature:
    /// \code
    /// void operator()(
    ///     terminalpp::behaviour const &beh,
    ///     terminalpp::terminal_state &state,
    ///     terminalpp::write_function const &write_fn) const;
    /// \endcode
    //* =====================================================================
    template <
        typename Manip,
        typename = typename std::enable_if<
            !std::is_convertible<typename std::remove_cv<Manip>::type, terminalpp::element>::value
         && !std::is_convertible<typename std::remove_cv<Manip>::type, terminalpp::string>::value
        >::type
    >
    terminal &operator<<(Manip &&manip)
    {
        manip(behaviour_, state_, write_);
        return *this;
    }

    //* =====================================================================
    /// \brief Write a single element to the terminal
    //* =====================================================================
    terminal &operator<<(terminalpp::element const &elem)
    {
        *this << write_optional_default_attribute();
        return *this << write_element(elem);
    }

    //* =====================================================================
    /// \brief Write an attributed string to the terminal.
    //* =====================================================================
    terminal &operator<<(terminalpp::string const &text)
    {
        *this << write_optional_default_attribute();
        
        boost::for_each(
            text,
            [this](terminalpp::element const &elem)
            {
                *this << write_element(elem);
            });

        return *this;
    }

    //* =====================================================================
    /// \brief Read from the terminal.
    ///
    /// \par Usage
    /// Stream in bytes, and the resultant tokens parsed from the stream will
    /// be sent to the write function.
    /// \code
    /// using namespace terminalpp::literals;
    /// void read_tokens(terminalpp::tokens);
    /// void raw_write(terminalpp::bytes);
    /// terminal term{raw_write};
    /// term.read(read_tokens) >> "\\x1B[13~"_tb;
    /// // read_tokens was called with a collection of one token, which
    /// // contained the f3 virtual key.
    /// \endcode
    //* =====================================================================
    /*
    template <class ReadContinuation>
    detail::terminal_reader<ReadContinuation> read(ReadContinuation &&rc)
    {
        return detail::terminal_reader<ReadContinuation>(
            behaviour_,
            state_,
            std::forward<ReadContinuation>(rc));
    }
    */

private:
    read_function read_;
    write_function write_;
    
    behaviour behaviour_;
    terminal_state state_;
};

//* =========================================================================
/// \brief A manipulator that outputs ANSI protocol bytes to move the cursor
/// to the specified location.
//* =========================================================================
class TERMINALPP_EXPORT move_cursor
{
public:
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    constexpr explicit move_cursor(point const &destination)
      : destination_(destination)
    {
    }

    //* =====================================================================
    /// \brief Writes the ANSI protocol codes necessary to move the cursor to
    /// the initialized location to write_fn.
    //* =====================================================================
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        write_function const &write_fn) const;

private:
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
    /// write function.
    //* =====================================================================
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        write_function const &write_fn) const;
};

//* =========================================================================
/// \brief A manipulator that shows the cursor.
//* =========================================================================
class TERMINALPP_EXPORT show_cursor
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to show the cursor to the
    /// write function.
    //* =====================================================================
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        write_function const &write_fn) const;
};

//* =========================================================================
/// \brief A manipulator that saves the cursor position
//* =========================================================================
class TERMINALPP_EXPORT save_cursor_position
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to save the cursor position.
    //* =====================================================================
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        write_function const &write_fn) const;
};

//* =========================================================================
/// \brief A manipulator that restores the cursor position
//* =========================================================================
class TERMINALPP_EXPORT restore_cursor_position
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to restore the cursor position.
    //* =====================================================================
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        write_function const &write_fn) const;
};

#if 0

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
        detail::change_to_default_attribute(state.last_element_, beh, cont);
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
        detail::change_to_default_attribute(state.last_element_, beh, cont);
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
        detail::change_to_default_attribute(state.last_element_, beh, cont);
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
        detail::change_to_default_attribute(state.last_element_, beh, cont);
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
        detail::change_to_default_attribute(state.last_element_, beh, cont);
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
        detail::change_to_default_attribute(state.last_element_, beh, cont);
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
        terminalpp::terminal_state &/*state*/,
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
        terminalpp::terminal_state &/*state*/,
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
    explicit set_window_title(std::string const &title)
      : title_(title)
    {
    }
    
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to disable the mouse
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &/*state*/,
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
    /// \brief Writes ANSI codes necessary to use the normal screen buffer.
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &/*state*/,
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
    /// \brief Writes ANSI codes necessary to use the alternate screen 
    /// buffer.
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &/*state*/,
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

#endif

}
