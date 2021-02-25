#include "terminalpp/detail/element_difference.hpp"
#include "terminalpp/ansi/control_characters.hpp"
#include "terminalpp/ansi/graphics.hpp"
#include "terminalpp/ansi/csi.hpp"
#include <fmt/format.h>

using namespace fmt::literals;

namespace terminalpp { namespace detail {

// ==========================================================================
// DEFAULT_ATTRIBUTE
// ==========================================================================
byte_storage default_attribute()
{
    static auto const default_attribute_string = to_bytes("{}{}{}"_format(
        terminalpp::ansi::control7::csi,
        int(terminalpp::ansi::graphics::no_attributes),
        char(terminalpp::ansi::csi::select_graphics_rendition)));

    return default_attribute_string;
}

}}
