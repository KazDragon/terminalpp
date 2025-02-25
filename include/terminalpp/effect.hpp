#pragma once

#include "terminalpp/graphics.hpp"

#include <boost/container_hash/hash.hpp>

#include <iostream>
#include <type_traits>

namespace terminalpp {

//* =========================================================================
/// \brief A traits class for which value of an effect is the "default" one.
//* =========================================================================
template <class Type>
struct effect_default;

template <class Type>
constexpr Type effect_default_v = effect_default<Type>::value;

//* =========================================================================
/// \brief A structure representing an ANSI graphics effect (e.g.
/// intensity, underlining)
//* =========================================================================
template <class Type>
struct effect
{
    //* =====================================================================
    /// \brief Initialises the intensity to the default (normal) value
    //* =====================================================================
    constexpr effect() noexcept : effect(effect_default_v<Type>)
    {
    }

    //* =====================================================================
    /// \brief Initialises the effect to the given value
    //* =====================================================================
    constexpr effect(Type value) noexcept  // NOLINT
      : value_(value)
    {
    }

    //* =====================================================================
    /// \brief Hash function
    //* =====================================================================
    [[nodiscard]] friend std::size_t hash_value(effect const &eff) noexcept
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, eff.value_);
        return seed;
    }

    //* =====================================================================
    /// \brief Relational operators for effects
    //* =====================================================================
    [[nodiscard]] constexpr friend auto operator<=>(
        effect const &lhs, effect const &rhs) noexcept = default;

    Type value_;
};

//* =========================================================================
/// \brief Specialization for intensity default case (normal intensity)
//* =========================================================================
template <>
struct effect_default<terminalpp::graphics::intensity>
  : std::integral_constant<
        terminalpp::graphics::intensity,
        terminalpp::graphics::intensity::normal>
{
};

//* =========================================================================
/// \brief Specialization for underlining default case (not underlined)
//* =========================================================================
template <>
struct effect_default<terminalpp::graphics::underlining>
  : std::integral_constant<
        terminalpp::graphics::underlining,
        terminalpp::graphics::underlining::not_underlined>
{
};

//* =========================================================================
/// \brief Specialization for polarity default case (positive)
//* =========================================================================
template <>
struct effect_default<terminalpp::graphics::polarity>
  : std::integral_constant<
        terminalpp::graphics::polarity,
        terminalpp::graphics::polarity::positive>
{
};

//* =========================================================================
/// \brief Specialization for blinking default case (steady)
//* =========================================================================
template <>
struct effect_default<terminalpp::graphics::blinking>
  : std::integral_constant<
        terminalpp::graphics::blinking,
        terminalpp::graphics::blinking::steady>
{
};

using intensity = effect<terminalpp::graphics::intensity>;
using underlining = effect<terminalpp::graphics::underlining>;
using polarity = effect<terminalpp::graphics::polarity>;
using blinking = effect<terminalpp::graphics::blinking>;

template <typename EffectType>
struct effect_has_normal : std::bool_constant<false>
{
};

template <>
struct effect_has_normal<terminalpp::graphics::intensity>
  : std::bool_constant<true>
{
};

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

}  // namespace terminalpp

namespace std {

template <class Effect>
struct hash<terminalpp::effect<Effect>>
{
    using argument_type = terminalpp::effect<Effect>;
    using result_type = std::size_t;

    [[nodiscard]] result_type operator()(
        argument_type const &effect) const noexcept
    {
        return hash_value(effect);
    }
};

}  // namespace std
