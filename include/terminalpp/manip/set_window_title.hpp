#pragma once
#include "terminalpp/terminal.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief A structure that encapsulates a set window title operation
//* =========================================================================
struct set_window_title
{
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    explicit set_window_title(std::string const &title)
      : title_(title)
    {
    }

    //* =====================================================================
    /// \brief Sets the window title in the terminal.
    //* =====================================================================
    std::string operator()(terminal &term)
    {
        return term.set_window_title(title_);
    }

    std::string const &title_;
};

}
