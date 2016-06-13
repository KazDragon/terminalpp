#pragma once

#include "terminalpp/point.hpp"
#include "terminalpp/terminal.hpp"

namespace terminalpp { namespace detail {

//* =========================================================================
/// \brief Move the cursor up y spaces.
//* =========================================================================
std::string cursor_up(
    terminalpp::s32 y,
    terminalpp::terminal::control_mode const &control_mode);

//* =========================================================================
/// \brief Move the cursor down y spaces.
//* =========================================================================
std::string cursor_down(
    terminalpp::s32 y,
    terminalpp::terminal::control_mode const &control_mode);

//* =========================================================================
/// \brief Move the cursor forward x spaces.
//* =========================================================================
std::string cursor_forward(
    terminalpp::s32 x,
    terminalpp::terminal::control_mode const &control_mode);

//* =========================================================================
/// \brief Move the cursor backward x spaces.
//* =========================================================================
std::string cursor_backward(
    terminalpp::s32 x,
    terminalpp::terminal::control_mode const &control_mode);

//* =========================================================================
/// \brief Move the cursor to column x.
//* =========================================================================
std::string cursor_horizontal_absolute(
    terminalpp::s32                           x,
    terminalpp::terminal::behaviour    const &behaviour,
    terminalpp::terminal::control_mode const &control_mode);

//* =========================================================================
/// \brief Move the cursor to the specified position.
//* =========================================================================
std::string cursor_position(
  terminalpp::point                  const &pt,
  terminalpp::terminal::behaviour    const &behaviour,
  terminalpp::terminal::control_mode const &control_mode);

}}
