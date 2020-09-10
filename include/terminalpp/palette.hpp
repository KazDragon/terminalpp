#include <terminalpp/attribute.hpp>
#include <terminalpp/ansi/graphics.hpp>

namespace terminalpp { namespace palette {

// Low colour, normal intensity
constexpr attribute black   { low_colour(ansi::graphics::colour::black) };
constexpr attribute maroon  { low_colour(ansi::graphics::colour::red) };
constexpr attribute green   { low_colour(ansi::graphics::colour::green) };
constexpr attribute olive   { low_colour(ansi::graphics::colour::yellow) };
constexpr attribute navy    { low_colour(ansi::graphics::colour::blue) };
constexpr attribute purple  { low_colour(ansi::graphics::colour::magenta) };
constexpr attribute teal    { low_colour(ansi::graphics::colour::cyan) };
constexpr attribute silver  { low_colour(ansi::graphics::colour::white) };

// Low colour, bold intensity
constexpr attribute grey    { low_colour(ansi::graphics::colour::black), {}, ansi::graphics::intensity::bold };
constexpr attribute red     { low_colour(ansi::graphics::colour::red), {}, ansi::graphics::intensity::bold };
constexpr attribute lime    { low_colour(ansi::graphics::colour::green), {}, ansi::graphics::intensity::bold };
constexpr attribute yellow  { low_colour(ansi::graphics::colour::yellow), {}, ansi::graphics::intensity::bold };
constexpr attribute blue    { low_colour(ansi::graphics::colour::blue), {}, ansi::graphics::intensity::bold };
constexpr attribute fuchsia { low_colour(ansi::graphics::colour::magenta), {}, ansi::graphics::intensity::bold };
constexpr attribute aqua    { low_colour(ansi::graphics::colour::cyan), {}, ansi::graphics::intensity::bold };
constexpr attribute white   { low_colour(ansi::graphics::colour::white), {}, ansi::graphics::intensity::bold };

constexpr attribute grey3   { greyscale_colour(0) };
constexpr attribute grey7   { greyscale_colour(1) };
constexpr attribute grey11  { greyscale_colour(2) };
constexpr attribute grey15  { greyscale_colour(3) };
constexpr attribute grey19  { greyscale_colour(4) };
constexpr attribute grey23  { greyscale_colour(5) };
constexpr attribute grey27  { greyscale_colour(6) };
constexpr attribute grey30  { greyscale_colour(7) };
constexpr attribute grey35  { greyscale_colour(8) };
constexpr attribute grey39  { greyscale_colour(9) };
constexpr attribute grey42  { greyscale_colour(10) };
constexpr attribute grey46  { greyscale_colour(11) };
constexpr attribute grey50  { greyscale_colour(12) };
constexpr attribute grey54  { greyscale_colour(13) };
constexpr attribute grey58  { greyscale_colour(14) };
constexpr attribute grey62  { greyscale_colour(15) };
constexpr attribute grey66  { greyscale_colour(16) };
constexpr attribute grey70  { greyscale_colour(17) };
constexpr attribute grey74  { greyscale_colour(18) };
constexpr attribute grey78  { greyscale_colour(19) };
constexpr attribute grey82  { greyscale_colour(20) };
constexpr attribute grey85  { greyscale_colour(21) };
constexpr attribute grey89  { greyscale_colour(22) };
constexpr attribute grey93  { greyscale_colour(23) };

}}