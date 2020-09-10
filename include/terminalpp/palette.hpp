#include <terminalpp/attribute.hpp>
#include <terminalpp/ansi/graphics.hpp>

namespace terminalpp { namespace palette {

// Low colour, normal intensity.  Note: console colours tend to be more
// variable than "pure" colours.  For example, on my terminal, maroon
// is really a little bit pink.
constexpr attribute black   { low_colour(ansi::graphics::colour::black)   }; // #000000
constexpr attribute maroon  { low_colour(ansi::graphics::colour::red)     }; // #800000
constexpr attribute green   { low_colour(ansi::graphics::colour::green)   }; // #008000
constexpr attribute olive   { low_colour(ansi::graphics::colour::yellow)  }; // #808000
constexpr attribute navy    { low_colour(ansi::graphics::colour::blue)    }; // #000080
constexpr attribute purple  { low_colour(ansi::graphics::colour::magenta) }; // #800080
constexpr attribute teal    { low_colour(ansi::graphics::colour::cyan)    }; // #008080
constexpr attribute silver  { low_colour(ansi::graphics::colour::white)   }; // #C0C0C0

// Low colour, bold intensity.  Note: lines come out thicker due to boldness, 
// so even if they match up with other colours, they behave differently.
constexpr attribute grey    { low_colour(ansi::graphics::colour::black), {}, ansi::graphics::intensity::bold   }; // #808080
constexpr attribute red     { low_colour(ansi::graphics::colour::red), {}, ansi::graphics::intensity::bold     }; // #FF0000
constexpr attribute lime    { low_colour(ansi::graphics::colour::green), {}, ansi::graphics::intensity::bold   }; // #00FF00
constexpr attribute yellow  { low_colour(ansi::graphics::colour::yellow), {}, ansi::graphics::intensity::bold  }; // #FFFF00
constexpr attribute blue    { low_colour(ansi::graphics::colour::blue), {}, ansi::graphics::intensity::bold    }; // #0000FF
constexpr attribute fuchsia { low_colour(ansi::graphics::colour::magenta), {}, ansi::graphics::intensity::bold }; // #FF00FF
constexpr attribute aqua    { low_colour(ansi::graphics::colour::cyan), {}, ansi::graphics::intensity::bold    }; // #00FFFF
constexpr attribute white   { low_colour(ansi::graphics::colour::white), {}, ansi::graphics::intensity::bold   }; // #FFFFFF

// Pure greys
constexpr attribute grey0   { high_colour(0, 0, 0) };  // #000000
constexpr attribute grey3   { greyscale_colour(0)  };  // #080808
constexpr attribute grey7   { greyscale_colour(1)  };  // #121212
constexpr attribute grey11  { greyscale_colour(2)  };  // #1C1C1C
constexpr attribute grey15  { greyscale_colour(3)  };  // #262626
constexpr attribute grey19  { greyscale_colour(4)  };  // #303030
constexpr attribute grey23  { greyscale_colour(5)  };  // #3A3A3A
constexpr attribute grey27  { greyscale_colour(6)  };  // #444444
constexpr attribute grey30  { greyscale_colour(7)  };  // #4E4E4E
constexpr attribute grey35  { greyscale_colour(8)  };  // #585858
constexpr attribute grey37  { high_colour(1, 1, 1) };  // #5F5F5F
constexpr attribute grey39  { greyscale_colour(9)  };  // #626262
constexpr attribute grey42  { greyscale_colour(10) };  // #6C6C6C
constexpr attribute grey46  { greyscale_colour(11) };  // #767676
constexpr attribute grey50  { greyscale_colour(12) };  // #808080
constexpr attribute grey53  { high_colour(2, 2, 2) };  // #878787
constexpr attribute grey54  { greyscale_colour(13) };  // #8A8A8A
constexpr attribute grey58  { greyscale_colour(14) };  // #949494
constexpr attribute grey62  { greyscale_colour(15) };  // #9E9E9E
constexpr attribute grey66  { greyscale_colour(16) };  // #A8A8A8
constexpr attribute grey69  { high_colour(3, 3, 3) };  // #AFAFAF
constexpr attribute grey70  { greyscale_colour(17) };  // #B2B2B2
constexpr attribute grey74  { greyscale_colour(18) };  // #BCBCBC
constexpr attribute grey78  { greyscale_colour(19) };  // #C6C6C6
constexpr attribute grey82  { greyscale_colour(20) };  // #D0D0D0
constexpr attribute grey84  { high_colour(4, 4, 4) };  // #D7D7D7
constexpr attribute grey85  { greyscale_colour(21) };  // #DADADA
constexpr attribute grey89  { greyscale_colour(22) };  // #E4E4E4
constexpr attribute grey93  { greyscale_colour(23) };  // #EEEEEE
constexpr attribute grey100 { high_colour(5, 5, 5) };  // #FFFFFF

// Pure reds
constexpr attribute red37      { high_colour(1, 0, 0) }; // #5F0000 // DarkRed
constexpr attribute red53      { high_colour(2, 0, 0) }; // #870000 // DarkRed
constexpr attribute red69      { high_colour(3, 0, 0) }; // #AF0000 // Red3
constexpr attribute red84      { high_colour(4, 0, 0) }; // #D70000 // Red3
constexpr attribute red100     { high_colour(5, 0, 0) }; // #FF0000 // Red1

// Pure greens
constexpr attribute green37    { high_colour(0, 1, 0) }; // #005F00 // DarkGreen
constexpr attribute green53    { high_colour(0, 2, 0) }; // #008700 // Green4
constexpr attribute green69    { high_colour(0, 3, 0) }; // #00AF00 // Green3
constexpr attribute green84    { high_colour(0, 4, 0) }; // #00D700 // Green3
constexpr attribute green100   { high_colour(0, 5, 0) }; // #00FF00 // Green1

// Pure blues
constexpr attribute blue37     { high_colour(0, 0, 1) };  // #00005F // NavyBlue
constexpr attribute blue53     { high_colour(0, 0, 2) };  // #000087 // DarkBlue
constexpr attribute blue69     { high_colour(0, 0, 3) };  // #0000AF // Blue3
constexpr attribute blue84     { high_colour(0, 0, 4) };  // #0000D7 // Blue3
constexpr attribute blue100    { high_colour(0, 0, 5) };  // #0000FF // Blue1

// Pure yellows
constexpr attribute yellow37   { high_colour(1, 1, 0) };  // #5F5F00 // Orange4
constexpr attribute yellow53   { high_colour(2, 2, 0) };  // #878700 // Yellow4
constexpr attribute yellow69   { high_colour(3, 3, 0) };  // #AFAF00 // Gold3
constexpr attribute yellow84   { high_colour(4, 4, 0) };  // #D7D700 // Yellow3
constexpr attribute yellow100  { high_colour(5, 5, 0) };  // #FFFF00 // Yellow1

// Pure magentas
constexpr attribute magenta37  { high_colour(1, 0, 1) };  // #5F005F // DeepPink4
constexpr attribute magenta53  { high_colour(2, 0, 2) };  // #870087 // DarkMagenta
constexpr attribute magenta69  { high_colour(3, 0, 3) };  // #AF00AF // Magenta3
constexpr attribute magenta84  { high_colour(4, 0, 4) };  // #D700D7 // Magenta3
constexpr attribute magenta100 { high_colour(5, 0, 5) };  // #FF00FF // Magenta1

// Pure cyans
constexpr attribute cyan37     { high_colour(0, 1, 1) };  // #005F5F // DeepSkyBlue4
constexpr attribute cyan53     { high_colour(0, 2, 2) };  // #008787 // Turquoise4
constexpr attribute cyan69     { high_colour(0, 3, 3) };  // #00AFAF // LightSeaGreen
constexpr attribute cyan84     { high_colour(0, 4, 4) };  // #00D7D7 // DarkTurquoise
constexpr attribute cyan100    { high_colour(0, 5, 5) };  // #00FFFF // Cyan1

}}