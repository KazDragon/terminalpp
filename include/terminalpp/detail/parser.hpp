#pragma once

#include "terminalpp/core.hpp"
#include "terminalpp/token.hpp"
#include <optional>
#include <vector>

namespace terminalpp::detail {

class TERMINALPP_EXPORT parser
{
 public:
  parser();

  std::optional<terminalpp::token> operator()(byte input);

 private:
  enum class state
  {
    idle,
    cr,
    lf,
    escape,
    arguments,
    mouse0,
    mouse1,
    mouse2,
  };

  std::optional<terminalpp::token> parse_idle(byte input);
  std::optional<terminalpp::token> parse_cr(byte input);
  std::optional<terminalpp::token> parse_lf(byte input);
  std::optional<terminalpp::token> parse_escape(byte input);
  std::optional<terminalpp::token> parse_arguments(byte input);
  std::optional<terminalpp::token> parse_mouse0(byte input);
  std::optional<terminalpp::token> parse_mouse1(byte input);
  std::optional<terminalpp::token> parse_mouse2(byte input);

  state state_;
  byte initializer_;
  byte extender_;
  bool meta_;
  mouse::event_type mouse_event_type_;
  point mouse_coordinate_;
  byte_storage argument_;
  std::vector<byte_storage> arguments_;
};

}  // namespace terminalpp::detail
