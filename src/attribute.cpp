#include "terminalpp/attribute.hpp"
#include <algorithm>
#include <ostream>

namespace terminalpp {

// ==========================================================================
// OUTPUT_NON_DEFAULT_ATTRIBUTE
// ==========================================================================
template <class T>
void output_non_default_attribute(
    std::ostream &out,
    T const &value,
    bool &with_comma,
    char const *prefix = "",
    char const *suffix = "")
{
  if (value != T())
  {
    if (std::exchange(with_comma, true))
    {
      out << ",";
    }

    out << prefix << value << suffix;
  }
}

// ==========================================================================
// OPERATOR<<(STREAM, ATTRIBUTE)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, attribute const &attr)
{
  bool with_comma = false;

  output_non_default_attribute(
      out, attr.foreground_colour_, with_comma, "foreground[", "]");
  output_non_default_attribute(
      out, attr.background_colour_, with_comma, "background[", "]");
  output_non_default_attribute(out, attr.intensity_, with_comma);
  output_non_default_attribute(out, attr.underlining_, with_comma);
  output_non_default_attribute(out, attr.polarity_, with_comma);
  output_non_default_attribute(out, attr.blinking_, with_comma);

  return out;
}

}  // namespace terminalpp
