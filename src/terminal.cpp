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

    // The cursor positions that terminals have after a size change is
    // inconsistent across implementations.  By resetting our own position
    // to an unknown one, it ensures that a precise move occurs the next
    // time the cursor is moved to a position.
    state_.cursor_position_ = {};
}

}
