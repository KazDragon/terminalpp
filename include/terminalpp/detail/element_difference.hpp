#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/ansi/charset.hpp"
#include "terminalpp/ansi/control_characters.hpp"
#include "terminalpp/ansi/graphics.hpp"
#include "terminalpp/ansi/csi.hpp"
#include "terminalpp/ansi/protocol.hpp"
#include <fmt/format.h>

namespace terminalpp { namespace detail {

//* =========================================================================
/// \brief Returns the CSI code for the given behaviour
//* =========================================================================
template <class WriteContinuation>
void csi(behaviour const &terminal_behaviour, WriteContinuation &&wc)
{
    static byte_storage const csi7 = {
        terminalpp::ansi::control7::csi[0],
        terminalpp::ansi::control7::csi[1],
    };

    static byte_storage const csi8 = {
        terminalpp::ansi::control8::csi
    };

    wc(terminal_behaviour.can_use_eight_bit_control_codes ? csi8 : csi7);
}

//* =========================================================================
/// \brief Returns a string of ANSI codes that sets the attributes to the
/// default.
//* =========================================================================
template <class WriteContinuation>
void default_attribute(
    behaviour const &terminal_behaviour, WriteContinuation &&wc)
{
    static byte_storage const default_attribute_string = {
        '0'_tb,
        terminalpp::ansi::csi::select_graphics_rendition
    };

    csi(terminal_behaviour, wc);
    wc(default_attribute_string);
}

//* =========================================================================
/// \brief
//* =========================================================================
template <class WriteContinuation>
void designate_g0_charset(
    character_set const &set, 
    behaviour const &terminal_behaviour,
    WriteContinuation &&wc)
{
    static constexpr bytes select_g0_charset = {
        std::cbegin(ansi::set_charset_g0),
        std::cend(ansi::set_charset_g0)
    };

    wc(select_g0_charset);
    wc(encode_character_set(set));
}

//* =========================================================================
/// \brief Changes charset from the source to destination, skipping over the
/// operation if they are already compatible.
//* =========================================================================
template <class WriteContinuation>
void change_charset(
    character_set const &source,
    character_set const &dest,
    behaviour const &terminal_behaviour,
    WriteContinuation &&wc)
{
    if (source != dest)
    {
        designate_g0_charset(dest, terminal_behaviour, wc);
    }
}

//* =========================================================================
/// \brief Changes an effect from the source to destination.
//* =========================================================================
template <class EffectType, class WriteContinuation>
void change_effect(
    effect<EffectType> const &source,
    effect<EffectType> const &dest,
    bool &change_appended,
    WriteContinuation &&wc)
{
    using namespace fmt::literals;

    if (source != dest)
    {
        if (std::exchange(change_appended, true))
        {
            static byte_storage const separator = { ansi::ps };
            wc(separator);
        }

        wc(to_bytes("{}"_format(int(dest.value_))));
    }
}

//* =========================================================================
/// \brief Changes attribute from the source to destination.
//* =========================================================================
template <class WriteContinuation>
void change_attribute(
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
    change_effect(source.polarity_,  dest.polarity_,  change_appended, wc);

    static byte_storage const sgr_trailer = {
        ansi::csi::select_graphics_rendition
    };

    wc(sgr_trailer);
}

}}
