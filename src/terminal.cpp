#include "terminalpp/terminal.hpp"

namespace terminalpp {

terminal_state::terminal_state() = default;

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
terminal::terminal(behaviour const &beh)
  : behaviour_(beh)
{
}

// ==========================================================================
// SET_SIZE
// ==========================================================================
void terminal::set_size(extent size)
{
    state_.terminal_size_ = size;
}

}
