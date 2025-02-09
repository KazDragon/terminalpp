#include <terminalpp/ansi/graphics.hpp>
#include <terminalpp/attribute.hpp>

namespace terminalpp::palette {

// Low colour, normal intensity.  Note: console colours tend to be more
// variable than "pure" colours.  For example, on my terminal, maroon
// is really a little bit pink.
// clang-format off
inline constexpr colour black   { low_colour(graphics::colour::black)   }; // #000000
inline constexpr colour maroon  { low_colour(graphics::colour::red)     }; // #800000
inline constexpr colour green   { low_colour(graphics::colour::green)   }; // #008000
inline constexpr colour olive   { low_colour(graphics::colour::yellow)  }; // #808000
inline constexpr colour navy    { low_colour(graphics::colour::blue)    }; // #000080
inline constexpr colour purple  { low_colour(graphics::colour::magenta) }; // #800080
inline constexpr colour teal    { low_colour(graphics::colour::cyan)    }; // #008080
inline constexpr colour silver  { low_colour(graphics::colour::white)   }; // #C0C0C0
// clang-format on

// Low colour, bold intensity.  These must be attributes and separated into
// foreground and background in order to be complete.  Note: lines also come
// out thicker due to boldness, so even if they match up with other colours,
// they behave differently.
// clang-format off
inline constexpr attribute fg_grey    { low_colour(graphics::colour::black), {}, graphics::intensity::bold   }; // #808080
inline constexpr attribute fg_red     { low_colour(graphics::colour::red), {}, graphics::intensity::bold     }; // #FF0000
inline constexpr attribute fg_lime    { low_colour(graphics::colour::green), {}, graphics::intensity::bold   }; // #00FF00
inline constexpr attribute fg_yellow  { low_colour(graphics::colour::yellow), {}, graphics::intensity::bold  }; // #FFFF00
inline constexpr attribute fg_blue    { low_colour(graphics::colour::blue), {}, graphics::intensity::bold    }; // #0000FF
inline constexpr attribute fg_fuchsia { low_colour(graphics::colour::magenta), {}, graphics::intensity::bold }; // #FF00FF
inline constexpr attribute fg_aqua    { low_colour(graphics::colour::cyan), {}, graphics::intensity::bold    }; // #00FFFF
inline constexpr attribute fg_white   { low_colour(graphics::colour::white), {}, graphics::intensity::bold   }; // #FFFFFF

inline constexpr attribute bg_grey    { {}, low_colour(graphics::colour::black), graphics::intensity::bold   }; // #808080
inline constexpr attribute bg_red     { {}, low_colour(graphics::colour::red), graphics::intensity::bold     }; // #FF0000
inline constexpr attribute bg_lime    { {}, low_colour(graphics::colour::green), graphics::intensity::bold   }; // #00FF00
inline constexpr attribute bg_yellow  { {}, low_colour(graphics::colour::yellow), graphics::intensity::bold  }; // #FFFF00
inline constexpr attribute bg_blue    { {}, low_colour(graphics::colour::blue), graphics::intensity::bold    }; // #0000FF
inline constexpr attribute bg_fuchsia { {}, low_colour(graphics::colour::magenta), graphics::intensity::bold }; // #FF00FF
inline constexpr attribute bg_aqua    { {}, low_colour(graphics::colour::cyan), graphics::intensity::bold    }; // #00FFFF
inline constexpr attribute bg_white   { {}, low_colour(graphics::colour::white), graphics::intensity::bold   }; // #FFFFFF

// Pure greys
inline constexpr colour grey0   { high_colour(0, 0, 0) };  // #000000
inline constexpr colour grey3   { greyscale_colour(0)  };  // #080808
inline constexpr colour grey7   { greyscale_colour(1)  };  // #121212
inline constexpr colour grey11  { greyscale_colour(2)  };  // #1C1C1C
inline constexpr colour grey15  { greyscale_colour(3)  };  // #262626
inline constexpr colour grey19  { greyscale_colour(4)  };  // #303030
inline constexpr colour grey23  { greyscale_colour(5)  };  // #3A3A3A
inline constexpr colour grey27  { greyscale_colour(6)  };  // #444444
inline constexpr colour grey30  { greyscale_colour(7)  };  // #4E4E4E
inline constexpr colour grey35  { greyscale_colour(8)  };  // #585858
inline constexpr colour grey37  { high_colour(1, 1, 1) };  // #5F5F5F
inline constexpr colour grey39  { greyscale_colour(9)  };  // #626262
inline constexpr colour grey42  { greyscale_colour(10) };  // #6C6C6C
inline constexpr colour grey46  { greyscale_colour(11) };  // #767676
inline constexpr colour grey50  { greyscale_colour(12) };  // #808080
inline constexpr colour grey53  { high_colour(2, 2, 2) };  // #878787
inline constexpr colour grey54  { greyscale_colour(13) };  // #8A8A8A
inline constexpr colour grey58  { greyscale_colour(14) };  // #949494
inline constexpr colour grey62  { greyscale_colour(15) };  // #9E9E9E
inline constexpr colour grey66  { greyscale_colour(16) };  // #A8A8A8
inline constexpr colour grey69  { high_colour(3, 3, 3) };  // #AFAFAF
inline constexpr colour grey70  { greyscale_colour(17) };  // #B2B2B2
inline constexpr colour grey74  { greyscale_colour(18) };  // #BCBCBC
inline constexpr colour grey78  { greyscale_colour(19) };  // #C6C6C6
inline constexpr colour grey82  { greyscale_colour(20) };  // #D0D0D0
inline constexpr colour grey84  { high_colour(4, 4, 4) };  // #D7D7D7
inline constexpr colour grey85  { greyscale_colour(21) };  // #DADADA
inline constexpr colour grey89  { greyscale_colour(22) };  // #E4E4E4
inline constexpr colour grey93  { greyscale_colour(23) };  // #EEEEEE
inline constexpr colour grey100 { high_colour(5, 5, 5) };  // #FFFFFF

// Pure reds
inline constexpr colour red37      { high_colour(1, 0, 0) }; // #5F0000 // DarkRed
inline constexpr colour red53      { high_colour(2, 0, 0) }; // #870000 // DarkRed
inline constexpr colour red69      { high_colour(3, 0, 0) }; // #AF0000 // Red3
inline constexpr colour red84      { high_colour(4, 0, 0) }; // #D70000 // Red3
inline constexpr colour red100     { high_colour(5, 0, 0) }; // #FF0000 // Red1

// Pure greens
inline constexpr colour green37    { high_colour(0, 1, 0) }; // #005F00 // DarkGreen
inline constexpr colour green53    { high_colour(0, 2, 0) }; // #008700 // Green4
inline constexpr colour green69    { high_colour(0, 3, 0) }; // #00AF00 // Green3
inline constexpr colour green84    { high_colour(0, 4, 0) }; // #00D700 // Green3
inline constexpr colour green100   { high_colour(0, 5, 0) }; // #00FF00 // Green1

// Pure blues
inline constexpr colour blue37     { high_colour(0, 0, 1) };  // #00005F // NavyBlue
inline constexpr colour blue53     { high_colour(0, 0, 2) };  // #000087 // DarkBlue
inline constexpr colour blue69     { high_colour(0, 0, 3) };  // #0000AF // Blue3
inline constexpr colour blue84     { high_colour(0, 0, 4) };  // #0000D7 // Blue3
inline constexpr colour blue100    { high_colour(0, 0, 5) };  // #0000FF // Blue1

// Pure yellows
inline constexpr colour yellow37   { high_colour(1, 1, 0) };  // #5F5F00 // Orange4
inline constexpr colour yellow53   { high_colour(2, 2, 0) };  // #878700 // Yellow4
inline constexpr colour yellow69   { high_colour(3, 3, 0) };  // #AFAF00 // Gold3
inline constexpr colour yellow84   { high_colour(4, 4, 0) };  // #D7D700 // Yellow3
inline constexpr colour yellow100  { high_colour(5, 5, 0) };  // #FFFF00 // Yellow1

// Pure magentas
inline constexpr colour magenta37  { high_colour(1, 0, 1) };  // #5F005F // DeepPink4
inline constexpr colour magenta53  { high_colour(2, 0, 2) };  // #870087 // DarkMagenta
inline constexpr colour magenta69  { high_colour(3, 0, 3) };  // #AF00AF // Magenta3
inline constexpr colour magenta84  { high_colour(4, 0, 4) };  // #D700D7 // Magenta3
inline constexpr colour magenta100 { high_colour(5, 0, 5) };  // #FF00FF // Magenta1

// Pure cyans
inline constexpr colour cyan37     { high_colour(0, 1, 1) };  // #005F5F // DeepSkyBlue4
inline constexpr colour cyan53     { high_colour(0, 2, 2) };  // #008787 // Turquoise4
inline constexpr colour cyan69     { high_colour(0, 3, 3) };  // #00AFAF // LightSeaGreen
inline constexpr colour cyan84     { high_colour(0, 4, 4) };  // #00D7D7 // DarkTurquoise
inline constexpr colour cyan100    { high_colour(0, 5, 5) };  // #00FFFF // Cyan1
// clang-format off

}  // namespace terminalpp::palette