#pragma once
#include "terminalpp/ansi/protocol.hpp"
#include <boost/operators.hpp>
#include <iostream>

namespace terminalpp {

//* =========================================================================
/// \brief A traits class for which value of an effect is the "default" one.
//* =========================================================================
template <class Type>
struct effect_default;

//* =========================================================================
/// \brief A structure representing an ANSI graphics effect (e.g.
/// intensity, underlining)
//* =========================================================================
template <class Type>
struct effect
  : private boost::less_than_comparable<effect<Type>,
            boost::equality_comparable<effect<Type>>>
{
    //* =====================================================================
    /// \brief Initialises the intensity to the default (normal) value
    //* =====================================================================
    constexpr effect()
      : effect(effect_default<Type>::value)
    {
    }

    //* =====================================================================
    /// \brief Initialises the effect to the given value
    //* =====================================================================
    constexpr effect(Type value)
      : value_(value)
    {
    }

    Type value_;
};

//* =========================================================================
/// \brief Less than for effects.
//* =========================================================================
template <class Type>
constexpr bool operator<(effect<Type> const &lhs, effect<Type> const &rhs)
{
  return lhs.value_ < rhs.value_;
}

//* =========================================================================
/// \brief Equality for effects.
//* =========================================================================
template <class Type>
constexpr bool operator==(effect<Type> const &lhs, effect<Type> const &rhs)
{
    return lhs.value_ == rhs.value_;
}

//* =========================================================================
/// \brief Specialization for intensity default case (normal intensity)
//* =========================================================================
template <>
struct effect_default<terminalpp::ansi::graphics::intensity>
  : std::integral_constant<
        terminalpp::ansi::graphics::intensity,
        terminalpp::ansi::graphics::intensity::normal
    >
{
};

//* =========================================================================
/// \brief Specialization for underlining default case (not underlined)
//* =========================================================================
template <>
struct effect_default<terminalpp::ansi::graphics::underlining>
  : std::integral_constant<
        terminalpp::ansi::graphics::underlining,
        terminalpp::ansi::graphics::underlining::not_underlined
    >
{
};

//* =========================================================================
/// \brief Specialization for polarity default case (positive)
//* =========================================================================
template <>
struct effect_default<terminalpp::ansi::graphics::polarity>
  : std::integral_constant<
        terminalpp::ansi::graphics::polarity,
        terminalpp::ansi::graphics::polarity::positive
    >
{
};

//* =========================================================================
/// \brief Specialization for blinking default case (steady)
//* =========================================================================
template <>
struct effect_default<terminalpp::ansi::graphics::blinking>
  : std::integral_constant<
        terminalpp::ansi::graphics::blinking,
        terminalpp::ansi::graphics::blinking::steady
    >
{
};

using intensity   = effect<terminalpp::ansi::graphics::intensity>;
using underlining = effect<terminalpp::ansi::graphics::underlining>;
using polarity    = effect<terminalpp::ansi::graphics::polarity>;
using blinking    = effect<terminalpp::ansi::graphics::blinking>;

//* =========================================================================
/// \brief Streaming output operator for intensities.  Prints the text
/// equivalent of the intensity (e.g. "normal", "bold", "faint").
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, intensity const &eff);

//* =========================================================================
/// \brief Streaming output operator for underlining.  Prints the text
/// equivalent of the underlining (e.g. "underlined", "not underlined").
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, underlining const &eff);

//* =========================================================================
/// \brief Streaming output operator for polarities.  Prints the text
/// equivalent of the polarity (e.g. "positive", "negative").
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, polarity const &eff);

//* =========================================================================
/// \brief Streaming output operator for blinking.  Prints the text
/// equivalent of the blink effect (e.g. "blinking", "steady").
//* =========================================================================
TERMINALPP_EXPORT
std::ostream &operator<<(std::ostream &out, blinking const &eff);

}
