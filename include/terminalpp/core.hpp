#pragma once

#include "terminalpp/detail/export.hpp"
#include <gsl/gsl-lite.hpp>
#include <cstdint>

namespace terminalpp {

// A byte in Terminal++ is represented consistently as an unsigned 
// 8-bit integer.
using byte = std::uint8_t;

// A stream of bytes in Terminal++ is exposed as a non-owning span.  It is
// expected that the data will live for no longer than any function in which
// it is found.  For that reason, these spans should never be stored directly.
// If storage is necessary, it must be converted into a longer-term data
// structure.
using bytes = gsl::span<byte const>;

// Where necessary, bytes are stored in this type, which has the small string
// optimization, meaning that most cases will not cause an allocation.
using byte_storage = std::basic_string<byte>;

// A co-ordinate in a terminal is represented consistently as a signed 
// 32-bit integer.
using coordinate_type = std::int32_t;

namespace literals {

// A helper function to convert from a character literal to a byte.
inline byte operator ""_tb(char const text)
{
    return static_cast<byte>(text);
}

// A helper function to convert from string literals to stored bytes.
inline byte_storage operator ""_tb(char const *text, size_t length)
{
    byte_storage result;
    result.reserve(length);

    for (auto ch : gsl::span<char const>{text, length})
    {
        result.push_back(byte(ch));
    }

    return result;
}

}

/*
// A helper function to convert from strings to stored bytes.
inline byte_storage to_bytes(std::string const &str)
{
    byte_storage result;
    result.reserve(str.size());

    for (auto const ch : str)
    {
        result.push_back(byte(ch));
    }

    return result;
}

// A helper function to convert from stores bytes to strings.
inline std::string to_string(byte_storage const &text)
{
    std::string result;
    result.reserve(text.size());

    for (auto const by : text)
    {
        result.push_back(char(by));
    }

    return result;
}
*/

}
