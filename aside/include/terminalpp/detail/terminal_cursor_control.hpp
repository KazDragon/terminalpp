#pragma once

#include "terminalpp/detail/terminal_control.hpp"
#include "terminalpp/core.hpp"

namespace terminalpp {

struct behaviour;
struct point;
class terminal;

namespace detail {

//* =========================================================================
/// \brief Move the cursor up y spaces.
//* =========================================================================
byte_storage cursor_up(
    coordinate_type     y,
    control_mode const &mode);

//* =========================================================================
/// \brief Move the cursor down y spaces.
//* =========================================================================
byte_storage cursor_down(
    coordinate_type     y,
    control_mode const &mode);

//* =========================================================================
/// \brief Move the cursor forward x spaces.
//* =========================================================================
byte_storage cursor_forward(
    coordinate_type     x,
    control_mode const &mode);

//* =========================================================================
/// \brief Move the cursor backward x spaces.
//* =========================================================================
byte_storage cursor_backward(
    coordinate_type     x,
    control_mode const &mode);

//* =========================================================================
/// \brief Move the cursor to column x.
//* =========================================================================
byte_storage cursor_horizontal_absolute(
    coordinate_type              x,
    terminalpp::behaviour const &behaviour,
    control_mode          const &mode);

//* =========================================================================
/// \brief Move the cursor to the specified position.
//* =========================================================================
byte_storage cursor_position(
  terminalpp::point     const &pt,
  terminalpp::behaviour const &behaviour,
  control_mode          const &mode);

//* =========================================================================
/// \brief Move the cursor to row y.
//* =========================================================================
byte_storage line_position_absolute(
    coordinate_type              y,
    terminalpp::behaviour const &behaviour,
    control_mode          const &mode);

}}
