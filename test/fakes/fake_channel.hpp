#pragma once

#include <terminalpp/core.hpp>
#include <functional>
#include <vector>

struct fake_channel
{
    //* =================================================================
    /// \brief Asynchronously read from the channel and call the function
    /// back when it's available.
    //* =================================================================
    void async_read(std::function<void (terminalpp::bytes)> const &callback)
    {
        read_callback_ = callback;
    }

    //* =================================================================
    /// \brief Write the given data to the channel.
    //* =================================================================
    void write(terminalpp::bytes data)
    {
        written_.append(data.begin(), data.end());
    }

    //* =================================================================
    /// \brief Returns whether the channel is alive.
    //* =================================================================
    bool is_alive() const
    {
        return alive_;
    }

    //* =================================================================
    /// \brief Closes the channel.
    //* =================================================================
    void close()
    {
        alive_ = false;

        if (read_callback_)
        {
            read_callback_({});
        }
    }

    //* =================================================================
    /// \brief Fakes receiving the passed data.
    //* =================================================================
    void receive(terminalpp::bytes data)
    {
        std::function<void (terminalpp::bytes)> callback;
        std::swap(read_callback_, callback);

        if (callback)
        {
            callback(data);
        }
    }

    std::function<void (terminalpp::bytes)> read_callback_;
    terminalpp::byte_storage written_;
    bool alive_{true};
};