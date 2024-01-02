#pragma once

namespace terminalpp::detail {

template <typename... Ts>
struct overloaded : Ts...
{
  using Ts::operator()...;
};

template <typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

}  // namespace terminalpp::detail