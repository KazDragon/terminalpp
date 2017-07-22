#pragma once

#include "terminalpp/detail/terminal_control.hpp"

namespace terminalpp {

class behaviour;
class point;
class terminal;

namespace detail {

//* =========================================================================
/// \brief Move the cursor up y spaces.
//* =========================================================================
std::string cursor_up(
    dimension_type      y,
    control_mode const &mode);

//* =========================================================================
/// \brief Move the cursor down y spaces.
//* =========================================================================
std::string cursor_down(
    dimension_type      y,
    control_mode const &mode);

//* =========================================================================
/// \brief Move the cursor forward x spaces.
//* =========================================================================
std::string cursor_forward(
    dimension_type      x,
    control_mode const &mode);

//* =========================================================================
/// \brief Move the cursor backward x spaces.
//* =========================================================================
std::string cursor_backward(
    dimension_type      x,
    control_mode const &mode);

//* =========================================================================
/// \brief Move the cursor to column x.
//* =========================================================================
std::string cursor_horizontal_absolute(
    coordinate_type              x,
    terminalpp::behaviour const &behaviour,
    control_mode          const &mode);

//* =========================================================================
/// \brief Move the cursor to the specified position.
//* =========================================================================
std::string cursor_position(
  terminalpp::point     const &pt,
  terminalpp::behaviour const &behaviour,
  control_mode          const &mode);

}}
