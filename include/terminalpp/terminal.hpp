#pragma once

#include "terminalpp/behaviour.hpp"
#include "terminalpp/core.hpp"
#include "terminalpp/string.hpp"
#include "terminalpp/terminal_state.hpp"
#include "terminalpp/token.hpp"

#include <boost/range/algorithm/for_each.hpp>

#include <functional>
#include <utility>

namespace terminalpp {

//* =========================================================================
/// \brief A class that encapsulates a terminal.
///
/// A class that is used to stream data in and out of a terminal.
//* =========================================================================
class TERMINALPP_EXPORT terminal final
{
public:
    using read_function = std::function<void(terminalpp::tokens)>;
    using write_function = std::function<void(terminalpp::bytes)>;

    //* =====================================================================
    /// \brief Constructor.
    //* =====================================================================
    template <typename Channel>
    explicit terminal(Channel &channel, behaviour beh = behaviour{})
      : channel_{std::unique_ptr<channel_concept>{
          std::make_unique<channel_model<Channel>>(channel)}},
        behaviour_(std::move(beh))
    {
    }

    //* =====================================================================
    /// \brief Copy Constructor
    //* =====================================================================
    terminal(terminal const &) = delete;

    //* =====================================================================
    /// \brief Destructor.
    //* =====================================================================
    ~terminal();

    //* =====================================================================
    /// \brief Copy Assignment
    //* =====================================================================
    terminal &operator=(terminal const &) = delete;

    //* =====================================================================
    /// \brief Request that data be read from the terminal.
    //* =====================================================================
    void async_read(std::function<void(tokens)> const &callback);

    //* =====================================================================
    /// \brief Write data to the terminal.
    //* =====================================================================
    void write(bytes data);

    //* =====================================================================
    /// \brief Returns whether the terminal is alive or not.
    //* =====================================================================
    [[nodiscard]] bool is_alive() const;

    //* =====================================================================
    /// Closes the terminal.
    //* =====================================================================
    void close();

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
    ///     terminalpp::terminal::write_function const &write_fn) const;
    /// \endcode
    //* =====================================================================
    template <
        typename Manip,
        typename = std::enable_if_t<
            !std::is_convertible_v<std::remove_cv_t<Manip>, terminalpp::element>
            && !std::is_convertible_v<
                std::remove_cv_t<Manip>,
                terminalpp::string>>>
    terminal &operator<<(Manip &&manip)
    {
        manip(behaviour_, state_, [this](bytes data) { write(data); });
        return *this;
    }

    //* =====================================================================
    /// \brief Write a single element to the terminal
    //* =====================================================================
    terminal &operator<<(terminalpp::element const &elem);

    //* =====================================================================
    /// \brief Write an attributed string to the terminal.
    //* =====================================================================
    terminal &operator<<(terminalpp::string const &text);

    //* =====================================================================
    /// \brief Read from the terminal.
    ///
    /// \par Usage
    /// Stream in bytes, and the resultant tokens parsed from the stream will
    /// be sent to the write function.
    /// \code
    /// using namespace terminalpp::literals;
    /// void raw_read(terminalpp::tokens);
    /// void raw_write(terminalpp::bytes);
    /// terminal term{raw_read, raw_write};
    /// term >> "\\x1B[13~"_tb;
    /// // read_tokens was called with a collection of one token, which
    /// // contained the f3 virtual key.
    /// \endcode
    //* =====================================================================
    // terminal &operator>>(terminalpp::bytes data);

private:
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    explicit terminal(behaviour beh);

    //* =====================================================================
    /// \brief An interface for a channel model.
    //* =====================================================================
    struct channel_concept
    {
        //* =================================================================
        /// \brief Destructor
        //* =================================================================
        virtual ~channel_concept() = default;

        //* =================================================================
        /// \brief Asynchronously read from the channel and call the function
        /// back when it's available.
        //* =================================================================
        virtual void async_read(std::function<void(bytes)> const &) = 0;

        //* =================================================================
        /// \brief Write the given data to the channel.
        //* =================================================================
        virtual void write(bytes data) = 0;

        //* =================================================================
        /// \brief Returns whether the channel is alive.
        //* =================================================================
        [[nodiscard]] virtual bool is_alive() const = 0;

        //* =================================================================
        /// \brief Closes the channel.
        //* =================================================================
        virtual void close() = 0;
    };

    //* =====================================================================
    /// \brief An implementation of the channel model.
    //* =====================================================================
    template <typename Channel>
    struct channel_model final : channel_concept
    {
        //* =================================================================
        /// \brief Constructor
        //* =================================================================
        explicit channel_model(Channel &channel) : channel_(channel)
        {
        }

        //* =================================================================
        /// \brief Asynchronously read from the channel and call the function
        /// back when it's available.
        //* =================================================================
        void async_read(std::function<void(bytes)> const &callback) override
        {
            channel_.async_read(callback);
        }

        //* =================================================================
        /// \brief Write the given data to the channel.
        //* =================================================================
        void write(bytes data) override
        {
            channel_.write(data);
        }

        //* =================================================================
        /// \brief Returns whether the channel is alive.
        //* =================================================================
        [[nodiscard]] bool is_alive() const override
        {
            return channel_.is_alive();
        }

        //* =================================================================
        /// \brief Closes the channel.
        //* =================================================================
        void close() override
        {
            channel_.close();
        }

        Channel &channel_;
    };

    std::unique_ptr<channel_concept> channel_;
    behaviour behaviour_;
    terminal_state state_;
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
        terminal::write_function const &write_fn) const;

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
        terminal::write_function const &write_fn) const;
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
        terminal::write_function const &write_fn) const;

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
        terminal::write_function const &write_fn) const;
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
        terminal::write_function const &write_fn) const;
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
        terminal::write_function const &write_fn) const;
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
        terminal::write_function const &write_fn) const;
};

//* =========================================================================
/// \brief A manipulator that erases the entire display.
//* =========================================================================
class TERMINALPP_EXPORT erase_display
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to erase the display.
    //* =====================================================================
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        terminal::write_function const &write_fn) const;
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
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        terminal::write_function const &write_fn) const;
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
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        terminal::write_function const &write_fn) const;
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
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        terminal::write_function const &write_fn) const;
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
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        terminal::write_function const &write_fn) const;
};

//* =========================================================================
/// \brief A manipulator that erases from the current cursor position to the
/// end of the line.
//* =========================================================================
class TERMINALPP_EXPORT erase_line_right
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to erase the display
    //* =====================================================================
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        terminal::write_function const &write_fn) const;
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
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        terminal::write_function const &write_fn) const;
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
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        terminal::write_function const &write_fn) const;
};

//* =========================================================================
/// \brief A manipulator that sets the window title according to the terminal
/// behaviour.
//* =========================================================================
class TERMINALPP_EXPORT set_window_title
{
public:
    explicit set_window_title(std::string title) : title_(std::move(title))
    {
    }

    //* =====================================================================
    /// \brief Writes ANSI codes necessary to disable the mouse
    //* =====================================================================
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        terminal::write_function const &write_fn) const;

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
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        terminal::write_function const &write_fn) const;
};

//* =========================================================================
/// \brief A manipulator that enables the use of the alternate screen buffer.
//* =========================================================================
class TERMINALPP_EXPORT use_alternate_screen_buffer
{
public:
    //* =====================================================================
    /// \brief Writes ANSI codes necessary to use the alternate screen buffer.
    //* =====================================================================
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state,
        terminal::write_function const &write_fn) const;
};

}  // namespace terminalpp
