#pragma once

#include "terminalpp/ansi/charset.hpp"
#include "terminalpp/core.hpp"

#include <boost/container_hash/hash.hpp>

#include <iosfwd>
#include <ranges>
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
{
    //* =====================================================================
    /// \brief Initialises the character set to its default value.
    //* =====================================================================
    constexpr character_set() noexcept : character_set(charset::us_ascii)
    {
    }

    //* =====================================================================
    /// \brief Initialises the character set the given value.
    //* =====================================================================
    constexpr character_set(charset const &set) noexcept  // NOLINT
      : value_(set)
    {
    }

    //* =====================================================================
    /// \brief Relational operators for character sets
    //* =====================================================================
    [[nodiscard]] constexpr friend auto operator<=>(
        character_set const &lhs, character_set const &rhs) noexcept = default;

    //* =====================================================================
    /// \brief Hash function
    //* =====================================================================
    [[nodiscard]] friend std::size_t hash_value(
        character_set const &cs) noexcept
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, cs.value_);

        return seed;
    }

    terminalpp::charset value_;
};

namespace detail {

using charset_map_small_entry = std::pair<character_set, byte const (&)[1]>;
inline constexpr charset_map_small_entry const charset_map[] = {
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

using charset_map_extended_entry = std::pair<character_set, byte const (&)[2]>;
inline constexpr charset_map_extended_entry const extended_charset_map[] = {
    {charset::dec_supplementary_graphics, ansi::charset_dec_supplementary_gr},
    {charset::portuguese,                 ansi::charset_portuguese          },
};

}  // namespace detail

//* =========================================================================
/// \brief Looks up a character set from a set of ANSI bytes.  Returns
/// nullptr if there is no matching set.
//* =========================================================================
TERMINALPP_EXPORT
[[nodiscard]] constexpr std::optional<character_set> lookup_character_set(
    bytes code) noexcept
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
[[nodiscard]] constexpr std::basic_string_view<byte> encode_character_set(
    character_set const &set) noexcept
{
    constexpr auto project_first = [](auto const &entry) {
        return entry.first;
    };

    if (auto const *entry =
            std::ranges::find(detail::charset_map, set, project_first);
        entry != std::cend(detail::charset_map))
    {
        return {entry->second, 1};
    }

    if (auto const *entry =
            std::ranges::find(detail::extended_charset_map, set, project_first);
        entry != std::cend(detail::extended_charset_map))
    {
        return {entry->second, 2};
    }

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

    [[nodiscard]] result_type operator()(argument_type const &cs) const noexcept
    {
        return hash_value(cs);
    }
};

}  // namespace std
