#pragma once

#include "terminalpp/core.hpp"

#include <functional>

namespace terminalpp {

//* =========================================================================
/// \brief A class that models the terminal's channel concept, providing
/// output to stdout.
//* =========================================================================
class stdout_channel
{
public:
    //* =====================================================================
    /// \brief Request data from the channel.
    ///
    /// A stdout channel does no inputting, so this is silently discarded.
    //* =====================================================================
    void async_read(std::function<void(terminalpp::bytes)> const &);

    //* =====================================================================
    /// \brief Writes the data to stdout.
    //* =====================================================================
    void write(terminalpp::bytes data);

    //* =====================================================================
    /// \brief Returns whether the output stream is alive.
    ///
    /// For simplicity, a stdout channel is always alive.
    //* =====================================================================
    [[nodiscard]] bool is_alive() const;

    //* =====================================================================
    /// \brief Requests that the channel be closed.
    ///
    /// For simplicity, a stdout channel cannot be closed, so this is a no-op.
    //* =====================================================================
    void close();
};

}  // namespace terminalpp
