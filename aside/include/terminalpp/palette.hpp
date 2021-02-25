#include <terminalpp/attribute.hpp>
#include <terminalpp/ansi/graphics.hpp>

namespace terminalpp { namespace palette {

// Low colour, normal intensity.  Note: console colours tend to be more
// variable than "pure" colours.  For example, on my terminal, maroon
// is really a little bit pink.
constexpr colour black   { low_colour(ansi::graphics::colour::black)   }; // #000000
constexpr colour maroon  { low_colour(ansi::graphics::colour::red)     }; // #800000
constexpr colour green   { low_colour(ansi::graphics::colour::green)   }; // #008000
constexpr colour olive   { low_colour(ansi::graphics::colour::yellow)  }; // #808000
constexpr colour navy    { low_colour(ansi::graphics::colour::blue)    }; // #000080
constexpr colour purple  { low_colour(ansi::graphics::colour::magenta) }; // #800080
constexpr colour teal    { low_colour(ansi::graphics::colour::cyan)    }; // #008080
constexpr colour silver  { low_colour(ansi::graphics::colour::white)   }; // #C0C0C0

// Low colour, bold intensity.  These must be attributes and separated into
// forground and background in order to be complete.  Note: lines also come
// out thicker due to boldness, so even if they match up with other colours,
// they behave differently.
constexpr attribute fg_grey    { low_colour(ansi::graphics::colour::black), {}, ansi::graphics::intensity::bold   }; // #808080
constexpr attribute fg_red     { low_colour(ansi::graphics::colour::red), {}, ansi::graphics::intensity::bold     }; // #FF0000
constexpr attribute fg_lime    { low_colour(ansi::graphics::colour::green), {}, ansi::graphics::intensity::bold   }; // #00FF00
constexpr attribute fg_yellow  { low_colour(ansi::graphics::colour::yellow), {}, ansi::graphics::intensity::bold  }; // #FFFF00
constexpr attribute fg_blue    { low_colour(ansi::graphics::colour::blue), {}, ansi::graphics::intensity::bold    }; // #0000FF
constexpr attribute fg_fuchsia { low_colour(ansi::graphics::colour::magenta), {}, ansi::graphics::intensity::bold }; // #FF00FF
constexpr attribute fg_aqua    { low_colour(ansi::graphics::colour::cyan), {}, ansi::graphics::intensity::bold    }; // #00FFFF
constexpr attribute fg_white   { low_colour(ansi::graphics::colour::white), {}, ansi::graphics::intensity::bold   }; // #FFFFFF

constexpr attribute bg_grey    { {}, low_colour(ansi::graphics::colour::black), ansi::graphics::intensity::bold   }; // #808080
constexpr attribute bg_red     { {}, low_colour(ansi::graphics::colour::red), ansi::graphics::intensity::bold     }; // #FF0000
constexpr attribute bg_lime    { {}, low_colour(ansi::graphics::colour::green), ansi::graphics::intensity::bold   }; // #00FF00
constexpr attribute bg_yellow  { {}, low_colour(ansi::graphics::colour::yellow), ansi::graphics::intensity::bold  }; // #FFFF00
constexpr attribute bg_blue    { {}, low_colour(ansi::graphics::colour::blue), ansi::graphics::intensity::bold    }; // #0000FF
constexpr attribute bg_fuchsia { {}, low_colour(ansi::graphics::colour::magenta), ansi::graphics::intensity::bold }; // #FF00FF
constexpr attribute bg_aqua    { {}, low_colour(ansi::graphics::colour::cyan), ansi::graphics::intensity::bold    }; // #00FFFF
constexpr attribute bg_white   { {}, low_colour(ansi::graphics::colour::white), ansi::graphics::intensity::bold   }; // #FFFFFF

// Pure greys
constexpr colour grey0   { high_colour(0, 0, 0) };  // #000000
constexpr colour grey3   { greyscale_colour(0)  };  // #080808
constexpr colour grey7   { greyscale_colour(1)  };  // #121212
constexpr colour grey11  { greyscale_colour(2)  };  // #1C1C1C
constexpr colour grey15  { greyscale_colour(3)  };  // #262626
constexpr colour grey19  { greyscale_colour(4)  };  // #303030
constexpr colour grey23  { greyscale_colour(5)  };  // #3A3A3A
constexpr colour grey27  { greyscale_colour(6)  };  // #444444
constexpr colour grey30  { greyscale_colour(7)  };  // #4E4E4E
constexpr colour grey35  { greyscale_colour(8)  };  // #585858
constexpr colour grey37  { high_colour(1, 1, 1) };  // #5F5F5F
constexpr colour grey39  { greyscale_colour(9)  };  // #626262
constexpr colour grey42  { greyscale_colour(10) };  // #6C6C6C
constexpr colour grey46  { greyscale_colour(11) };  // #767676
constexpr colour grey50  { greyscale_colour(12) };  // #808080
constexpr colour grey53  { high_colour(2, 2, 2) };  // #878787
constexpr colour grey54  { greyscale_colour(13) };  // #8A8A8A
constexpr colour grey58  { greyscale_colour(14) };  // #949494
constexpr colour grey62  { greyscale_colour(15) };  // #9E9E9E
constexpr colour grey66  { greyscale_colour(16) };  // #A8A8A8
constexpr colour grey69  { high_colour(3, 3, 3) };  // #AFAFAF
constexpr colour grey70  { greyscale_colour(17) };  // #B2B2B2
constexpr colour grey74  { greyscale_colour(18) };  // #BCBCBC
constexpr colour grey78  { greyscale_colour(19) };  // #C6C6C6
constexpr colour grey82  { greyscale_colour(20) };  // #D0D0D0
constexpr colour grey84  { high_colour(4, 4, 4) };  // #D7D7D7
constexpr colour grey85  { greyscale_colour(21) };  // #DADADA
constexpr colour grey89  { greyscale_colour(22) };  // #E4E4E4
constexpr colour grey93  { greyscale_colour(23) };  // #EEEEEE
constexpr colour grey100 { high_colour(5, 5, 5) };  // #FFFFFF

// Pure reds
constexpr colour red37      { high_colour(1, 0, 0) }; // #5F0000 // DarkRed
constexpr colour red53      { high_colour(2, 0, 0) }; // #870000 // DarkRed
constexpr colour red69      { high_colour(3, 0, 0) }; // #AF0000 // Red3
constexpr colour red84      { high_colour(4, 0, 0) }; // #D70000 // Red3
constexpr colour red100     { high_colour(5, 0, 0) }; // #FF0000 // Red1

// Pure greens
constexpr colour green37    { high_colour(0, 1, 0) }; // #005F00 // DarkGreen
constexpr colour green53    { high_colour(0, 2, 0) }; // #008700 // Green4
constexpr colour green69    { high_colour(0, 3, 0) }; // #00AF00 // Green3
constexpr colour green84    { high_colour(0, 4, 0) }; // #00D700 // Green3
constexpr colour green100   { high_colour(0, 5, 0) }; // #00FF00 // Green1

// Pure blues
constexpr colour blue37     { high_colour(0, 0, 1) };  // #00005F // NavyBlue
constexpr colour blue53     { high_colour(0, 0, 2) };  // #000087 // DarkBlue
constexpr colour blue69     { high_colour(0, 0, 3) };  // #0000AF // Blue3
constexpr colour blue84     { high_colour(0, 0, 4) };  // #0000D7 // Blue3
constexpr colour blue100    { high_colour(0, 0, 5) };  // #0000FF // Blue1

// Pure yellows
constexpr colour yellow37   { high_colour(1, 1, 0) };  // #5F5F00 // Orange4
constexpr colour yellow53   { high_colour(2, 2, 0) };  // #878700 // Yellow4
constexpr colour yellow69   { high_colour(3, 3, 0) };  // #AFAF00 // Gold3
constexpr colour yellow84   { high_colour(4, 4, 0) };  // #D7D700 // Yellow3
constexpr colour yellow100  { high_colour(5, 5, 0) };  // #FFFF00 // Yellow1

// Pure magentas
constexpr colour magenta37  { high_colour(1, 0, 1) };  // #5F005F // DeepPink4
constexpr colour magenta53  { high_colour(2, 0, 2) };  // #870087 // DarkMagenta
constexpr colour magenta69  { high_colour(3, 0, 3) };  // #AF00AF // Magenta3
constexpr colour magenta84  { high_colour(4, 0, 4) };  // #D700D7 // Magenta3
constexpr colour magenta100 { high_colour(5, 0, 5) };  // #FF00FF // Magenta1

// Pure cyans
constexpr colour cyan37     { high_colour(0, 1, 1) };  // #005F5F // DeepSkyBlue4
constexpr colour cyan53     { high_colour(0, 2, 2) };  // #008787 // Turquoise4
constexpr colour cyan69     { high_colour(0, 3, 3) };  // #00AFAF // LightSeaGreen
constexpr colour cyan84     { high_colour(0, 4, 4) };  // #00D7D7 // DarkTurquoise
constexpr colour cyan100    { high_colour(0, 5, 5) };  // #00FFFF // Cyan1

}}