#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/behaviour.hpp"
#include "terminalpp/string.hpp"
#include "terminalpp/ansi/control_characters.hpp"
#include "terminalpp/detail/element_difference.hpp"
#include <boost/range/algorithm/for_each.hpp>
#include <boost/optional.hpp>

namespace terminalpp {

class terminal;

template <class WriteContinuation>
class TERMINALPP_EXPORT terminal_writer;

//* =========================================================================
/// \brief The state of a terminal, which manipulators are allowed to use and
/// edit.
//* =========================================================================
struct terminal_state
{
    boost::optional<element> last_element_;
};

namespace detail {

//* =========================================================================
/// \brief A manipulator that sets up the initial required state of a 
/// terminal.
//* =========================================================================
struct initialise_terminal
{
    //* =====================================================================
    /// \brief Write the initializer for the 8-bit control mode if necessary.
    //* =====================================================================
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state, 
        WriteContinuation &&cont)
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
struct write_optional_default_attribute
{
    template <class WriteContinuation>
    void operator()(
        terminalpp::behaviour const &beh,
        terminalpp::terminal_state &state, 
        WriteContinuation &&cont)
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
struct write_element
{
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    write_element(terminalpp::element const &elem)
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
        WriteContinuation &&cont)
    {
        change_charset(
            state.last_element_->glyph_.charset_, 
            element_.glyph_.charset_,
            beh,
            cont);

        terminalpp::bytes data{&element_.glyph_.character_, 1};
        cont(data);
        state.last_element_ = element_;
    }

    terminalpp::element element_;
};

//* =========================================================================
/// \brief A class that is used to stream manipulators together to a 
/// terminal.
//* =========================================================================
template <class WriteContinuation>
class TERMINALPP_EXPORT terminal_writer
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

}
