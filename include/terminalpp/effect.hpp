#pragma once

#include "terminalpp/graphics.hpp"
#include <boost/container_hash/hash.hpp>
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
struct effect : private boost::less_than_comparable<
                    effect<Type>,
                    boost::equality_comparable<effect<Type>>>
{
  //* =====================================================================
  /// \brief Initialises the intensity to the default (normal) value
  //* =====================================================================
  constexpr effect() : effect(effect_default<Type>::value)
  {
  }

  //* =====================================================================
  /// \brief Initialises the effect to the given value
  //* =====================================================================
  constexpr effect(Type value)  // NOLINT
    : value_(value)
  {
  }

  //* =====================================================================
  /// \brief Hash function
  //* =====================================================================
  friend std::size_t hash_value(effect const &eff) noexcept
  {
    std::size_t seed = 0;
    boost::hash_combine(seed, eff.value_);
    return seed;
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

  result_type operator()(argument_type const &effect) const noexcept
  {
    return hash_value(effect);
  }
};

}  // namespace std
