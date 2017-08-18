#pragma once
#include "terminalpp/terminal.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief Encapsulates writing a string to a terminal.
//* =========================================================================
struct write_string
{
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    write_string(string const &text)
      : text_(text)
    {
    }

    //* =====================================================================
    /// \brief Writes the string to the terminal.
    //* =====================================================================
    std::string operator()(terminal &term) const
    {
        return term.write(text_);
    }

    string const &text_;
};

}
