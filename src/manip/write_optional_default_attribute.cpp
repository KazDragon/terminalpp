#include "terminalpp/detail/element_difference.hpp"
#include "terminalpp/terminal.hpp"

namespace terminalpp {

// ==========================================================================
// WRITE_OPTIONAL_DEFAULT_ATTRIBUTE::OPERATOR()
// ==========================================================================
void write_optional_default_attribute::operator()(
    terminalpp::behaviour const &beh,
    terminalpp::terminal_state &state,
    terminal::write_function const &write_fn) const
{
  if (!state.last_element_)
  {
    detail::default_attribute(beh, write_fn);
    state.last_element_ = terminalpp::element{};
  }
}

}  // namespace terminalpp