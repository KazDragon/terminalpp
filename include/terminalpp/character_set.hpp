#pragma once

#include "terminalpp/ansi/charset.hpp"
#include "terminalpp/core.hpp"

#include <boost/container_hash/hash.hpp>
#include <boost/operators.hpp>

#include <iosfwd>
#include <string_view>

namespace terminalpp {

//* =========================================================================
/// \brief An enumeration for all supported character sets.
//* =========================================================================
enum class charset : char
{
    dec,
    dec_supplementary,
    dec_supplementary_graphics,
    dec_technical,
    uk,
    us_ascii,
    dutch,
    finnish,
    french,
    french_canadian,
    german,
    italian,
    danish,
    portuguese,
    spanish,
    swedish,
    swiss,
    sco,
    utf8,
};

//* =========================================================================
/// \brief A structure that represents a character set.
//* =========================================================================
struct TERMINALPP_EXPORT character_set
  : private boost::less_than_comparable<
        character_set,
        boost::equality_comparable<character_set>>
{
    //* =====================================================================
    /// \brief Initialises the character set to its default value.
    //* =====================================================================
    constexpr character_set() : character_set(charset::us_ascii)
    {
    }

    //* =====================================================================
    /// \brief Initialises the character set the given value.
    //* =====================================================================
    constexpr character_set(charset const &set)  // NOLINT
      : value_(set)
    {
    }

    //* =====================================================================
    /// \brief Equality operator for character sets
    //* =====================================================================
    constexpr friend bool operator==(
        character_set const &lhs, character_set const &rhs)
    {
        return lhs.value_ == rhs.value_;
    }

    //* =====================================================================
    /// \brief Less-than operator for character sets
    //* =====================================================================
    constexpr friend bool operator<(
        character_set const &lhs, character_set const &rhs)
    {
        return lhs.value_ < rhs.value_;
    }

    //* =====================================================================
    /// \brief Hash function
    //* =====================================================================
    friend std::size_t hash_value(character_set const &cs) noexcept
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, cs.value_);

        return seed;
    }

    terminalpp::charset value_;
};

namespace detail {

static constexpr std::pair<character_set, byte const (&)[1]> const
    charset_map[] = {
        {charset::us_ascii,          ansi::charset_us_ascii           },
        {charset::sco,               ansi::charset_sco                },
        {charset::dec,               ansi::charset_dec                },
        {charset::dec_supplementary, ansi::charset_dec_supplementary  },
        {charset::dec_technical,     ansi::charset_dec_technical      },
        {charset::uk,                ansi::charset_uk                 },
        {charset::dutch,             ansi::charset_dutch              },
        {charset::finnish,           ansi::charset_finnish            },
        {charset::finnish,           ansi::charset_finnish_alt        },
        {charset::french,            ansi::charset_french             },
        {charset::french,            ansi::charset_french_alt         },
        {charset::french_canadian,   ansi::charset_french_canadian    },
        {charset::french_canadian,   ansi::charset_french_canadian_alt},
        {charset::german,            ansi::charset_german             },
        {charset::italian,           ansi::charset_italian            },
        {charset::danish,            ansi::charset_danish             },
        {charset::danish,            ansi::charset_danish_alt_1       },
        {charset::danish,            ansi::charset_danish_alt_2       },
        {charset::spanish,           ansi::charset_spanish            },
        {charset::swedish,           ansi::charset_swedish            },
        {charset::swedish,           ansi::charset_swedish_alt        },
        {charset::swiss,             ansi::charset_swiss              },
};

static constexpr std::pair<character_set, byte const (&)[2]> const
    extended_charset_map[] = {
        {charset::dec_supplementary_graphics,
         ansi::charset_dec_supplementary_gr                           },
        {charset::portuguese,                 ansi::charset_portuguese},
};

}  // namespace detail

//* =========================================================================
/// \brief Looks up a character set from a set of ANSI bytes.  Returns
/// nullptr if there is no matching set.
//* =========================================================================
TERMINALPP_EXPORT
constexpr std::optional<character_set> lookup_character_set(bytes code)
{
    auto const len = code.size();

    if (len == 0)
    {
        return {};
    }

    if (code[0] == ansi::charset_extender)
    {
        if (len > 1)
        {
            for (auto &&mapping : detail::extended_charset_map)
            {
                if (code[1] == mapping.second[1])
                {
                    return mapping.first;
                }
            }
        }
    }
    else
    {
        for (auto &&mapping : detail::charset_map)
        {
            if (code[0] == mapping.second[0])
            {
                return mapping.first;
            }
        }
    }

    return std::nullopt;
}

//* =========================================================================
/// \brief Encodes a character set into a set of ANSI bytes.
//* =========================================================================
TERMINALPP_EXPORT
constexpr std::basic_string_view<byte> encode_character_set(
    character_set const &set)
{
    // std::find_if is not constexpr in C++17.
    auto const *charset_entry = std::cbegin(detail::charset_map);
    while (charset_entry != std::cend(detail::charset_map))
    {
        if (charset_entry->first == set)
        {
            break;
        }

        ++charset_entry;
    }

    if (charset_entry != std::cend(detail::charset_map))
    {
        return {charset_entry->second, 1};
    }

    auto const *extended_charset_entry =
        std::cbegin(detail::extended_charset_map);
    while (extended_charset_entry != std::cend(detail::extended_charset_map))
    {
        if (extended_charset_entry->first == set)
        {
            break;
        }

        ++extended_charset_entry;
    }

    if (extended_charset_entry != std::cend(detail::extended_charset_map))
    {
        return {extended_charset_entry->second, 2};
    }  // If the character set is an unknown, fall back to US ASCII.
    return encode_character_set(character_set(charset::us_ascii));
}

//* =========================================================================
/// \brief Streaming output operator for character sets.  Outputs the name
/// of the character set.
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, character_set const &set);

}  // namespace terminalpp

namespace std {

template <>
struct hash<terminalpp::character_set>
{
    using argument_type = terminalpp::character_set;
    using result_type = std::size_t;

    result_type operator()(argument_type const &cs) const noexcept
    {
        return hash_value(cs);
    }
};

}  // namespace std
