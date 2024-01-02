#include "terminalpp/stdout_channel.hpp"
#include <iostream>

namespace terminalpp {

// ==========================================================================
// ASYNC_READ
// ==========================================================================
void stdout_channel::async_read(std::function<void(terminalpp::bytes)> const &)
{
}

// ==========================================================================
// WRITE
// ==========================================================================
void stdout_channel::write(terminalpp::bytes data)
{
  std::cout.write(reinterpret_cast<char const *>(data.begin()), data.ssize());
}

// ==========================================================================
// IS_ALIVE
// ==========================================================================
bool stdout_channel::is_alive() const
{
  return true;
}

// ==========================================================================
// CLOSE
// ==========================================================================
void stdout_channel::close()
{
}

}  // namespace terminalpp
