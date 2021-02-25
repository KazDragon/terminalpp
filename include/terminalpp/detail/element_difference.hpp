#pragma once

#include "terminalpp/core.hpp"

namespace terminalpp { namespace detail {

//* =========================================================================
/// \brief Returns a string of ANSI codes that sets the attributes to the
/// default.
//* =========================================================================
byte_storage default_attribute();

}}