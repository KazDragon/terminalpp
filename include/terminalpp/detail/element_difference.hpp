#pragma once

#include "terminalpp/ansi/charset.hpp"
#include "terminalpp/ansi/control_characters.hpp"
#include "terminalpp/ansi/csi.hpp"
#include "terminalpp/ansi/dec_private_mode.hpp"
#include "terminalpp/ansi/graphics.hpp"
#include "terminalpp/ansi/protocol.hpp"
#include "terminalpp/attribute.hpp"
#include "terminalpp/behaviour.hpp"
#include "terminalpp/character_set.hpp"
#include "terminalpp/colour.hpp"
#include "terminalpp/core.hpp"
#include "terminalpp/detail/overloaded.hpp"
#include "terminalpp/effect.hpp"
#include "terminalpp/element.hpp"

#include <format>

#include <optional>
#include <utility>

namespace terminalpp::detail {

//* =========================================================================
/// \brief Returns the CSI code for the given behaviour
//* =========================================================================
template <class WriteContinuation>
constexpr void csi(
    behaviour const & /*terminal_behaviour*/, WriteContinuation &&wc)
{
    wc({std::cbegin(ansi::control7::csi), std::cend(ansi::control7::csi)});
}

//* =========================================================================
/// \brief Returns the OSC code for the given behaviour
//* =========================================================================
template <class WriteContinuation>
constexpr void osc(
    behaviour const & /*terminal_behaviour*/, WriteContinuation &&wc)
{
    wc({std::cbegin(ansi::control7::osc), std::cend(ansi::control7::osc)});
}

//* =========================================================================
/// \brief Returns the ST code for the given behaviour
//* =========================================================================
template <class WriteContinuation>
constexpr void st(
    behaviour const & /*terminal_behaviour*/, WriteContinuation &&wc)
{
    wc({std::cbegin(ansi::control7::st), std::cend(ansi::control7::st)});
}

//* =========================================================================
/// \brief Returns the DEC_PM code
//* =========================================================================
template <class WriteContinuation>
constexpr void dec_pm(
    behaviour const &terminal_behaviour, WriteContinuation &&wc)
{
    csi(terminal_behaviour, wc);

    std::initializer_list<byte> const dec_pm{
        terminalpp::ansi::dec_private_mode[0]};

    wc(dec_pm);
}

//* =========================================================================
/// \brief Returns a string of ANSI codes that sets the attributes to the
/// default.
//* =========================================================================
template <class WriteContinuation>
constexpr void default_attribute(
    behaviour const &terminal_behaviour, WriteContinuation &&wc)
{
    std::initializer_list<byte> const default_attribute_string = {
        '0'_tb, terminalpp::ansi::csi::select_graphics_rendition};

    csi(terminal_behaviour, wc);
    wc(default_attribute_string);
}

//* =========================================================================
/// \brief Designates the G0 charset as the given character set.
//* =========================================================================
template <class WriteContinuation>
constexpr void designate_g0_charset(
    character_set const &set,
    behaviour const & /*terminal_behaviour*/,
    WriteContinuation &&wc)
{
    bytes const select_g0_charset = {
        std::cbegin(ansi::set_charset_g0), std::cend(ansi::set_charset_g0)};

    wc(select_g0_charset);
    wc(encode_character_set(set));
}

//* =========================================================================
/// \brief Enables the utf8 charset
//* =========================================================================
template <class WriteContinuation>
constexpr void select_utf8_charset(WriteContinuation &&wc)
{
    bytes const select_utf8_charset_command = {
        std::cbegin(ansi::select_utf8_character_set),
        std::cend(ansi::select_utf8_character_set)};

    wc(select_utf8_charset_command);
}

//* =========================================================================
/// \brief Disables the utf8 charset
//* =========================================================================
template <class WriteContinuation>
constexpr void select_default_charset(WriteContinuation &&wc)
{
    bytes const select_default_charset_command = {
        std::cbegin(ansi::select_default_character_set),
        std::cend(ansi::select_default_character_set)};

    wc(select_default_charset_command);
}

//* =========================================================================
/// \brief Changes charset from the source to destination, skipping over the
/// operation if they are already compatible.
//* =========================================================================
template <class WriteContinuation>
constexpr void change_charset(
    character_set const &source,
    character_set const &dest,
    behaviour const &terminal_behaviour,
    WriteContinuation &&wc)
{
    if (source != dest)
    {
        if (dest == charset::utf8)
        {
            if (!terminal_behaviour.unicode_in_all_charsets)
            {
                change_charset(
                    source, charset::us_ascii, terminal_behaviour, wc);
            }

            select_utf8_charset(wc);
        }
        else
        {
            if (source == charset::utf8)
            {
                select_default_charset(wc);
            }

            designate_g0_charset(dest, terminal_behaviour, wc);
        }
    }
}

//* =========================================================================
/// \brief Changes an effect from the source to destination.
//* =========================================================================
template <class EffectType, class WriteContinuation>
constexpr void change_effect(
    effect<EffectType> const &source,
    effect<EffectType> const &dest,
    bool &change_appended,
    WriteContinuation &&wc)
{
    std::initializer_list<byte> const separator = {ansi::ps};

    if (source != dest)
    {
        if constexpr (effect_has_normal<EffectType>::value)
        {
            if (source.value_ != EffectType::normal
                && dest.value_ != EffectType::normal)
            {
                if (std::exchange(change_appended, true))
                {
                    wc(separator);
                }

                wc(to_bytes(std::format("{}", int(EffectType::normal))));
            }
        }

        if (std::exchange(change_appended, true))
        {
            wc(separator);
        }

        wc(to_bytes(std::format("{}", int(dest.value_))));
    }
}

//* =========================================================================
/// \brief Changes the foreground colour from source to destination.
//* =========================================================================
template <class WriteContinuation>
constexpr void change_foreground_colour(
    colour const &source,
    colour const &dest,
    bool &change_appended,
    WriteContinuation &&wc)
{
    if (source != dest)
    {
        if (std::exchange(change_appended, true))
        {
            std::initializer_list<byte> const separator = {ansi::ps};
            wc(separator);
        }

        std::visit(
            overloaded{
                [&wc](low_colour const &col) {
                    wc(to_bytes(std::format(
                        "{}",
                        static_cast<int>(col.value_)
                            + ansi::graphics::foreground_colour_base)));
                },
                [&wc](high_colour const &col) {
                    wc(to_bytes(
                        std::format("38;5;{}", static_cast<int>(col.value_))));
                },
                [&wc](greyscale_colour const &col) {
                    wc(to_bytes(
                        std::format("38;5;{}", static_cast<int>(col.shade_))));
                },
                [&wc](true_colour const &col) {
                    wc(to_bytes(std::format(
                        "38;2;{};{};{}",
                        static_cast<int>(col.red_),
                        static_cast<int>(col.green_),
                        static_cast<int>(col.blue_))));
                }},
            dest.value_);
    }
}

//* =========================================================================
/// \brief Changes the foreground colour from source to destination.
//* =========================================================================
template <class WriteContinuation>
constexpr void change_background_colour(
    colour const &source,
    colour const &dest,
    bool &change_appended,
    WriteContinuation &&wc)
{
    if (source != dest)
    {
        if (std::exchange(change_appended, true))
        {
            std::initializer_list<byte> const separator = {ansi::ps};
            wc(separator);
        }

        std::visit(
            overloaded{
                [&wc](low_colour const &col) {
                    wc(to_bytes(std::format(
                        "{}",
                        static_cast<int>(col.value_)
                            + ansi::graphics::background_colour_base)));
                },
                [&wc](high_colour const &col) {
                    wc(to_bytes(
                        std::format("48;5;{}", static_cast<int>(col.value_))));
                },
                [&wc](greyscale_colour const &col) {
                    wc(to_bytes(
                        std::format("48;5;{}", static_cast<int>(col.shade_))));
                },
                [&wc](true_colour const &col) {
                    wc(to_bytes(std::format(
                        "48;2;{};{};{}",
                        static_cast<int>(col.red_),
                        static_cast<int>(col.green_),
                        static_cast<int>(col.blue_))));
                }},
            dest.value_);
    }
}

//* =========================================================================
/// \brief Changes attribute from the source to destination.
//* =========================================================================
template <class WriteContinuation>
constexpr void change_attribute(
    attribute const &source,
    attribute const &dest,
    behaviour const &terminal_behaviour,
    WriteContinuation &&wc)
{
    if (source == dest)
    {
        return;
    }

    if (dest == terminalpp::attribute{})
    {
        default_attribute(terminal_behaviour, wc);
        return;
    }

    csi(terminal_behaviour, wc);

    bool change_appended = false;
    change_effect(source.intensity_, dest.intensity_, change_appended, wc);
    change_effect(source.polarity_, dest.polarity_, change_appended, wc);
    change_effect(source.underlining_, dest.underlining_, change_appended, wc);
    change_foreground_colour(
        source.foreground_colour_,
        dest.foreground_colour_,
        change_appended,
        wc);
    change_background_colour(
        source.background_colour_,
        dest.background_colour_,
        change_appended,
        wc);

    std::initializer_list<byte> const sgr_trailer = {
        ansi::csi::select_graphics_rendition};

    wc(sgr_trailer);
}

//* =========================================================================
/// \brief Resets the current attribute if necessary.
//* =========================================================================
template <class WriteContinuation>
constexpr void change_to_default_attribute(
    std::optional<element> &last_element,
    behaviour const &beh,
    WriteContinuation &&wc)
{
    if (last_element)
    {
        detail::change_attribute(last_element->attribute_, {}, beh, wc);
        last_element->attribute_ = {};
    }
}

}  // namespace terminalpp::detail
