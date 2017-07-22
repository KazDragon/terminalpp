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
    coordinate_type     y,
    control_mode const &mode);

//* =========================================================================
/// \brief Move the cursor down y spaces.
//* =========================================================================
std::string cursor_down(
    coordinate_type     y,
    control_mode const &mode);

//* =========================================================================
/// \brief Move the cursor forward x spaces.
//* =========================================================================
std::string cursor_forward(
    coordinate_type     x,
    control_mode const &mode);

//* =========================================================================
/// \brief Move the cursor backward x spaces.
//* =========================================================================
std::string cursor_backward(
    coordinate_type     x,
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
