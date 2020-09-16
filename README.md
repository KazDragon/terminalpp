# Terminal++

[![Documentation](https://codedocs.xyz/KazDragon/terminalpp.svg)](https://codedocs.xyz/KazDragon/terminalpp/)
[![License](https://img.shields.io/github/license/KazDragon/terminalpp.svg)](https://en.wikipedia.org/wiki/MIT_License)
[![Coverage Status](https://coveralls.io/repos/github/KazDragon/terminalpp/badge.svg?branch=master)](https://coveralls.io/github/KazDragon/terminalpp?branch=master)
[![Build Status](https://travis-ci.org/KazDragon/terminalpp.svg?branch=master)](https://travis-ci.org/KazDragon/terminalpp)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/a2741e8f7abf49bc8b496fbf8b51b983)](https://www.codacy.com/app/KazDragon/terminalpp?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=KazDragon/terminalpp&amp;utm_campaign=Badge_Grade)
[![Download](https://api.bintray.com/packages/kazdragon/conan-public/terminalpp%3Akazdragon/images/download.svg)](https://bintray.com/kazdragon/conan-public/terminalpp%3Akazdragon/_latestVersion)

[![Github Issues](https://img.shields.io/github/issues/KazDragon/terminalpp.svg)](https://github.com/KazDragon/terminalpp/issues)

[![Gitter](https://badges.gitter.im/KazDragon/terminalpp.svg)](https://gitter.im/KazDragon/terminalpp?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

# Terminal++
A C++ library for interacting with ANSI/VT100 terminal or terminal emulator displays.

# Requirements

Terminal++ requires a C++14 library and the following libraries:
  * Boost (At least version 1.69.0)
  * libfmt (At least version 5.3)
  * (For testing only) Google Test

# Installation - CMake

Terminal++ can be installed from source using CMake.  This requires Boost, libfmt and any other dependencies to have been installed beforehand, using their own instructions, or for the call to `cmake --configure` to be adjusted appropriately (e.g. `-DBOOST_ROOT=...` or `-Dfmt_DIR=...`).  If you do not wish to install into a system directory, and thus avoid the use of sudo, you can also pass `-DCMAKE_INSTALL_PREFIX=...` into the `cmake --configure` call.

    git clone https://github.com/KazDragon/terminalpp.git && cd terminalpp
    mkdir build && cd build
    cmake --configure -DCMAKE_BUILD_TYPE=Release ..
    cmake --build .
    sudo cmake --install .

# Installation - Conan

You can also use [the Conan Package Manager](https://conan.io/) to install Terminal++ and its dependencies.

See [the tprint example](examples/tprint) for a minimalistic project that describes this setup.

# Features / Roadmap

1. [x] A utility for creating strings with embedded ANSI attributes
  * [x] terminalpp::string
  * This will be immediately useful in line-oriented programs to construct and output streams of attributed (coloured, emboldened, underlined, etc.) text.

2. [x] A utility for managing ANSI escape codes that are not bound to specific characters.  For example, commands for moving the cursor, changing the screen's title, clearing the screen, etc.
  * [x] terminalpp::terminal

3. [x] Utilities for managing screens of attributed characters
  * [x] terminalpp::canvas
  * [x] terminalpp::screen
  * This will be useful for those who wish to develop a more graphical or "curses-style" user interface.

4. [ ] A database of terminal types and their associated behaviours
  * With some kind of application-specific terminal type detection, this would make it possible to write apps that automatically adjust to the most appropriate protocols supported by the client.

A set of classes that implement a windowing user interface are currently being implemented in the [Munin project](https://github.com/KazDragon/munin).

# Status

Terminal++ is currently automatically tested using Clang 4.0 and GCC 5.5.  For further information about the working status of the library, to report any bugs, or to make any feature requests, visit the [Issues page](https://github.com/KazDragon/terminalpp/issues).

# The Basics

The purpose of the library is to be able to allow the usage of ANSI escape codes to their fullest potential in order to create fully-featured text-based applications.  The use cases for such software include interactive forms of command-line software, and even GUI-style applications over the internet using terminal emulators such as Xterm, PuTTY, or even some MUD clients (e.g Tintin++).

At its most fundamental level, Terminal++ is in the business of manipulating character elements on the screen, where each element is encoded as a glyph, which describes the character that is presented to the user, and a series of non-character graphical attributes. These are encapsulated in the following classes:

* terminalpp::glyph - represents a character (which may be ASCII or any UTF-8 value up to U+FFFF) and its character set (by default, this is the US_ASCII character set).
* terminalpp::attribute - a collection of variables that describe the non-character graphical part of the output, such as the foreground and background colours, whether it is bold, underlined, and so on.

These are combined into Terminal++'s fundamental type, terminalpp::element.

# Strings

terminalpp::elements can be collected together using the terminalpp::string class.  It has several constructors for different uses.  For example, one of the constructors takes a std::string and an attribute to apply to all those characters for when you want something like print out a single red error message.  In addition, there are the user-defined literal suffixes _ts (terminal string) and _ets (encoded terminal string) to help construct more complicated strings

[Hello, World! project](examples/hello_world)
```cpp
#include <terminalpp/ansi_terminal.hpp>

int main()
{
    using namespace terminalpp::literals;
    terminalpp::string text = "Hello, world!\n"_ts;

    terminalpp::ansi_terminal terminal;
    std::cout << terminal.write(text);
}

// Constructs a terminalpp::string, and then prints it to the terminal as, "Hello, world!"
```

By using _ets, you can also encode attributes within the text.  For example:

[Encoded Hello, World! project](examples/encoded_hello_world)
```cpp
#include <terminalpp/ansi_terminal.hpp>

int main()
{
    using namespace terminalpp::literals;
    terminalpp::string text = "\\[1Hello, \\[2World! \\x\\U263A\n"_ets;

    terminalpp::ansi_terminal terminal;
    std::cout << terminal.write(text);
}
```

This prints out "Hello, " in red text, then "World!" in green text, and then a smiley face in the default colour.  See the Wiki for more information about the attribute encoding used and its possibilities.  It is also possible to change the attributes for each element programatically.

```cpp
terminalpp::string text = ...;
text[0].attribute_.intensity_ = terminalpp::ansi::graphics::intensity::bold;
```

# Terminals

At this point, you have everything you need for a standard command-line application that uses colour or other properties, such as you might see in the output of a CMake script or Google Test results, or even standard unix functions such as ls.  But the ansi_terminal class allows for complete control over the terminal's appearance.

[Positioned smiley project](examples/positioned_smiley)
```cpp
#include <terminalpp/ansi_terminal.hpp>

int main()
{
    using namespace terminalpp::literals;
    terminalpp::ansi_terminal terminal;

    std::cout << terminal.save_cursor()
              << terminal.move_cursor({0,0})
              << terminal.write("\\U263A"_ets)
              << terminal.restore_cursor();
}
```

This writes a smiley face in the (0, 0) position on the terminal -- the top-left corner. The cursor position is unchanged. The terminal uses a 0-based co-ordinate system where point (0, 0) is the top-left corner, and the co-ordinates are in (x, y) order.

Note that it is necessary to output the results of the terminal operations.  This is because terminalpp is datastream-agnostic: it doesn't know where the terminal you're writing to actually is.  It could be standard out, it could be some named pipe, or it could be a network socket.  This gives you the flexibility to use Terminal++ in any situation where there is some kind of terminal emulator on the other side of a stream, without imposing any kind of restrictions.

# Canvas and Screen

For even finer control of the terminal, the terminalpp::canvas class presents a grid of elements upon which you can "paint" the desired appearance of the terminal on a frame-by-frame by simply assigning to the appropriate co-ordinates:

```cpp
int main()
{
    terminalpp::canvas canvas({80, 24});

    // Set the entire canvas to be the letter 'x' on a shocking pink
    // background.  Because, why not?
    terminalpp::element element('x');
    element.attribute_.background_colour_ = terminalpp::high_colour(5, 1, 2);

    for (terminalpp::coordinate_type y = 0; y < canvas.size().height; ++y)
    {
        for (terminalpp::coordinate_type x = 0; x < canvas.size().width; ++x)
        {
            canvas[x][y] = element;
        }
    }
}
```

Now, assigning elements to the canvas wont actually cause any immediate effect.  For that, you would need to index over the entire canvas and output it, element-by-element, to a terminal.  But it's very wasteful to output the entire screen each time that a small part of it changes.

To control this, we present the terminalpp::screen class, which represents a double-buffered approach to drawing the contents of a canvas.  Its draw() member function will cause only the differences between the previously drawn canvas and the current canvas to be output, with efforts made to keep the output as small as possible.  Note: it is assumed for the first canvas drawn, and for any canvas drawn after a change in output size, that everything has changed.

[Shocking pink project](examples/shocking_pink)
```cpp
#include <terminalpp/ansi_terminal.hpp>
#include <terminalpp/canvas.hpp>
#include <terminalpp/screen.hpp>

int main()
{
    terminalpp::ansi_terminal terminal;
    terminalpp::screen screen;
    terminalpp::canvas canvas({80, 24});

    // ... Shocking pink screen as before ...
    std::cout << screen.draw(terminal, canvas);
    // screen is now actually shocking pink.

    canvas[10][15].glyph_ = 'y';
    canvas[10][15].attribute_.background_colour_ =
        terminalpp::ansi::graphics::colour::blue;

    std::cout << screen.draw(terminal, canvas);
    // screen is still shocking pink, but there is now a letter 'y' with a
    // blue background at position (10, 15).
}
```
