#pragma once

#include "terminalpp/detail/well_known_virtual_key.hpp"
#include "terminalpp/behaviour.hpp"
#include "terminalpp/terminal_state.hpp"
#include <boost/range/algorithm/for_each.hpp>

namespace terminalpp { namespace detail {

//* =========================================================================
/// \brief A manipulator that converts ANSI protocol bytes into terminal
/// tokens.
//* =========================================================================
class read_tokens
{
public:
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    constexpr explicit read_tokens(terminalpp::bytes data)
      : data_(data)
    {
    }

    //* =====================================================================
    /// \brief Convert the text and write the result to the continuation
    //* =====================================================================
    template <class ReadContinuation>
    void operator()(
        terminalpp::behaviour const &/*beh*/,
        terminalpp::terminal_state &state,
        ReadContinuation &&cont) const
    {
        boost::for_each(
            data_, 
            [&](terminalpp::byte data)
            {
                auto const result = state.input_parser_(data);

                if (result)
                {
                    terminalpp::token const well_known_results[] = {
                        detail::get_well_known_virtual_key(*result)
                    };

                    cont(well_known_results);
                }
            });
    }

private:
    terminalpp::bytes data_;
};

//* =========================================================================
/// \brief A class that is used to stream manipulators together to a 
/// terminal.
//* =========================================================================
template <class ReadContinuation>
class terminal_reader
{
public:
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    terminal_reader(
        behaviour const &beh,
        terminal_state &state,
        ReadContinuation &&rc)
      : behaviour_(beh),
        state_(state),
        read_continuation_(std::forward<ReadContinuation>(rc))
    {
    }

    //* =====================================================================
    /// \brief Streams a manipulator to the reader, which executes it on the
    /// current state.
    //* =====================================================================
    template <
        typename Manip,
        typename = typename std::enable_if<
            !std::is_convertible<Manip, terminalpp::bytes>::value
        >::type
    >
    terminal_reader const &operator>>(Manip &&manip) const
    {
        manip(behaviour_, state_, read_continuation_);
        return *this;
    }

    //* =====================================================================
    /// \brief Parses ANSI protocol bytes and sends their tokenized 
    /// representation to the continuation.
    //* =====================================================================
    terminal_reader const &operator>>(terminalpp::bytes const &data) const
    {
        return *this >> detail::read_tokens(data);
    }

private:
    behaviour const &behaviour_;
    terminal_state &state_;
    ReadContinuation read_continuation_;
};

}}