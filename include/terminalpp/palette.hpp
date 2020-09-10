#include <terminalpp/attribute.hpp>
#include <terminalpp/ansi/graphics.hpp>

namespace terminalpp { namespace palette {

constexpr attribute black   { low_colour(ansi::graphics::colour::black) };
constexpr attribute maroon  { low_colour(ansi::graphics::colour::red) };
constexpr attribute green   { low_colour(ansi::graphics::colour::green) };
constexpr attribute olive   { low_colour(ansi::graphics::colour::yellow) };
constexpr attribute navy    { low_colour(ansi::graphics::colour::blue) };
constexpr attribute purple  { low_colour(ansi::graphics::colour::magenta) };
constexpr attribute teal    { low_colour(ansi::graphics::colour::cyan) };
constexpr attribute silver  { low_colour(ansi::graphics::colour::white) };

constexpr attribute grey    { low_colour(ansi::graphics::colour::black), {}, ansi::graphics::intensity::bold };
constexpr attribute red     { low_colour(ansi::graphics::colour::red), {}, ansi::graphics::intensity::bold };
constexpr attribute lime    { low_colour(ansi::graphics::colour::green), {}, ansi::graphics::intensity::bold };
constexpr attribute yellow  { low_colour(ansi::graphics::colour::yellow), {}, ansi::graphics::intensity::bold };
constexpr attribute blue    { low_colour(ansi::graphics::colour::blue), {}, ansi::graphics::intensity::bold };
constexpr attribute fuchsia { low_colour(ansi::graphics::colour::magenta), {}, ansi::graphics::intensity::bold };
constexpr attribute aqua    { low_colour(ansi::graphics::colour::cyan), {}, ansi::graphics::intensity::bold };
constexpr attribute white   { low_colour(ansi::graphics::colour::white), {}, ansi::graphics::intensity::bold };

}}