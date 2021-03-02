#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/behaviour.hpp"
#include "terminalpp/extent.hpp"
#include "terminalpp/point.hpp"
#include "terminalpp/string.hpp"
#include "terminalpp/ansi/control_characters.hpp"
#include "terminalpp/ansi/csi.hpp"
#include "terminalpp/ansi/dec_private_mode.hpp"
#include "terminalpp/detail/element_difference.hpp"
#include <fmt/format.h>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/optional.hpp>
#include <algorithm>

namespace terminalpp {

//* =========================================================================
/// \brief The state of a terminal, which manipulators are allowed to use and
/// edit.
//* =========================================================================
struct TERMINALPP_EXPORT terminal_state
{
    terminal_state();

    extent                   terminal_size_;
    boost::optional<element> last_element_;
    boost::optional<point>   cursor_position_;
    boost::optional<bool>    cursor_visible_;
};

namespace detail {

//* =========================================================================
/// \brief A manipulator that sets up the initial required state of a 
/// terminal.
//* =========================================================================
struct TERMINALPP_EXPORT initialise_terminal
{
    //* =====================================================================
    /// \brief Write the initializer for the 8-bit control mode if necessary.
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state, 
        WriteContinuation &&cont) const
    {
        if (beh.can_use_eight_bit_control_codes
         && !beh.uses_eight_bit_control_codes_by_default)
        {
            cont({
                std::cbegin(terminalpp::ansi::control8::enable),
                std::cend(terminalpp::ansi::control8::enable)});
        }
    }
};

//* =========================================================================
/// \brief A manipulator that initializes the attributes to the default if it
/// has not yet been done.
//* =========================================================================
struct TERMINALPP_EXPORT write_optional_default_attribute
{
    //* =====================================================================
    /// \brief Writes the default attribute to the terminal if necessary.
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state, 
        WriteContinuation &&cont) const
    {
        if (!state.last_element_)
        {
            detail::default_attribute(beh, cont);
            state.last_element_ = terminalpp::element{};
        }
    }
};

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
    constexpr write_element(terminalpp::element const &elem)
      : element_(elem)
    {
    }

    //* =====================================================================
    /// \brief Convert the text and write the result to the continuation
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        WriteContinuation &&cont) const
    {
        change_charset(
            state.last_element_->glyph_.charset_, 
            element_.glyph_.charset_,
            beh,
            cont);

        change_attribute(
            state.last_element_->attribute_,
            element_.attribute_,
            beh,
            cont);

        if (element_.glyph_.charset_ == charset::utf8)
        {
            write_utf8_glyph(cont);
        }
        else
        {
            write_regular_glyph(cont);
        }

        state.last_element_ = element_;
        
        advance_cursor_position(state);
    }

private:
    // ======================================================================
    // WRITE_UTF8_GLYPH
    // ======================================================================
    template <class WriteContinuation>
    void write_utf8_glyph(WriteContinuation &&cont) const
    {
        std::size_t const last_utf8_index = 
            [this]()
            {
                std::size_t index = 0;

                for (;
                       index < sizeof(element_.glyph_.ucharacter_)
                    && element_.glyph_.ucharacter_[index] != '\0';
                       ++index)
                {
                    if (!(element_.glyph_.ucharacter_[index] & 0x80))
                    {
                        break;
                    }
                }

                return index;
            }();

        terminalpp::bytes const data{
            element_.glyph_.ucharacter_, 
            std::max(last_utf8_index, std::size_t{1u})};
        cont(data);
    }

    // ======================================================================
    // WRITE_REGULAR_GLYPH
    // ======================================================================
    template <class WriteContinuation>
    void write_regular_glyph(WriteContinuation &&cont) const
    {
        terminalpp::bytes data{&element_.glyph_.character_, 1};
        cont(data);
    }

    // ======================================================================
    // ADVANCE_CURSOR_POSITION
    // ======================================================================
    void advance_cursor_position(terminal_state &state) const
    {
        if (state.cursor_position_)
        {
            if (++state.cursor_position_->x_ == state.terminal_size_.width_)
            {
                state.cursor_position_->x_ = 0;
                state.cursor_position_->y_ = std::min(
                    ++state.cursor_position_->y_, 
                    state.terminal_size_.height_ - 1);
            }
        }
    }

    terminalpp::element element_;
};

//* =========================================================================
/// \brief A class that is used to stream manipulators together to a 
/// terminal.
//* =========================================================================
template <class WriteContinuation>
class terminal_writer
{
public:
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    terminal_writer(
        behaviour const &beh,
        terminal_state &state, 
        WriteContinuation &&wc)
      : behaviour_(beh),
        state_(state),
        write_continuation_(std::forward<WriteContinuation>(wc))
    {
    }

    //* =====================================================================
    /// \brief Streams a manipulator to the writer, which executes it on the
    /// current state.
    //* =====================================================================
    template <class Manip>
    terminal_writer const &operator<<(Manip &&manip) const
    {
        manip(behaviour_, state_, write_continuation_);
        return *this;
    }

    //* =====================================================================
    /// \brief Streams an attributed text element to the writer, which sends
    /// the equivalent representation in ANSI protocol bytes to the
    /// continuation.
    //* =====================================================================
    terminal_writer const &operator<<(terminalpp::element &elem) const
    {
        *this << write_optional_default_attribute();
        return *this << detail::write_element(elem);
    }

    //* =====================================================================
    /// \brief Streams an attributed text element to the writer, which sends
    /// the equivalent representation in ANSI protocol bytes to the
    /// continuation.
    //* =====================================================================
    terminal_writer const &operator<<(terminalpp::element const &elem) const
    {
        *this << write_optional_default_attribute();
        return *this << detail::write_element(elem);
    }

    //* =====================================================================
    /// \brief Streams an attributed text element to the writer, which sends
    /// the equivalent representation in ANSI protocol bytes to the
    /// continuation.
    //* =====================================================================
    terminal_writer const &operator<<(terminalpp::element &&elem) const
    {
        *this << write_optional_default_attribute();
        return *this << detail::write_element(elem);
    }

    //* =====================================================================
    /// \brief Streams attributed text elements to the writer, which sends 
    /// their equivalent representation in ANSI protocol bytes to the
    /// continuation.
    //* =====================================================================
    terminal_writer const &operator<<(terminalpp::string text) const
    {
        *this << write_optional_default_attribute();
        
        boost::for_each(
            text,
            [this](terminalpp::element const &elem)
            {
                *this << detail::write_element(elem);
            });
            
        return *this;
    }

private:
    behaviour const &behaviour_;
    terminal_state &state_;
    WriteContinuation write_continuation_;
};

}

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
    /// terminal term;
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

        static const byte_storage cursor_position_suffix = {
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

        static const byte_storage cursor_horizontal_absolute_suffix = {
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

        static const byte_storage cursor_up_suffix = {
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

        static const byte_storage cursor_down_suffix = {
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

        static const byte_storage erase_all_suffix = {  
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

        static const byte_storage erase_above_suffix = {  
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

        static const byte_storage erase_below_suffix = {  
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

        static const byte_storage erase_line_suffix = {  
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

        static const byte_storage erase_line_left_suffix = {  
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

        static const byte_storage erase_line_right_suffix = {  
            // The code for erase right is 0, which can be elided.
            ansi::csi::erase_in_line,
        };

        cont(erase_line_right_suffix);
    }
};

}
