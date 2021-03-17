#pragma once

#include "terminalpp/detail/element_difference.hpp"
#include "terminalpp/behaviour.hpp"
#include "terminalpp/terminal_state.hpp"
#include "terminalpp/string.hpp"
#include <boost/range/algorithm/for_each.hpp>
#include <type_traits>

namespace terminalpp { namespace detail {

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
    constexpr explicit write_element(terminalpp::element const &elem)
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
                // Terminals differ in their behaviour when reaching the
                // end of the line.  Some wrap to the next line, some bounce
                // against the edge.  To maintain consistency, forget the
                // current cursor position.
                state.cursor_position_ = {};
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
    template <
        typename Manip,
        typename = typename std::enable_if<
            !std::is_convertible<typename std::remove_cv<Manip>::type, terminalpp::element>::value
         && !std::is_convertible<typename std::remove_cv<Manip>::type, terminalpp::string>::value
        >::type
    >
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
    terminal_writer const &operator<<(terminalpp::element const &elem) const
    {
        *this << write_optional_default_attribute();
        return *this << detail::write_element(elem);
    }

    //* =====================================================================
    /// \brief Streams attributed text elements to the writer, which sends 
    /// their equivalent representation in ANSI protocol bytes to the
    /// continuation.
    //* =====================================================================
    terminal_writer const &operator<<(terminalpp::string const &text) const
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

}}