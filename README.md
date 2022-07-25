# Terminal++

[![Documentation](https://img.shields.io/badge/code-documented-brightgreen.svg?style=flat)](https://kazdragon.github.io/terminalpp/) 
[![License](https://img.shields.io/github/license/KazDragon/terminalpp.svg)](https://en.wikipedia.org/wiki/MIT_License)
[![MSVC Build status](https://ci.appveyor.com/api/projects/status/ywpx7m37e902hdoy/branch/master?svg=true)](https://ci.appveyor.com/project/KazDragon/terminalpp/branch/master) 
[![Linux Build status](https://github.com/KazDragon/terminalpp/workflows/build/badge.svg)](https://github.com/KazDragon/terminalpp/actions?query=event%3Apush) 
[![Coverage Status](https://coveralls.io/repos/github/KazDragon/terminalpp/badge.svg?branch=master)](https://coveralls.io/github/KazDragon/terminalpp?branch=master) 
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/a2741e8f7abf49bc8b496fbf8b51b983)](https://www.codacy.com/gh/KazDragon/terminalpp/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=KazDragon/terminalpp&amp;utm_campaign=Badge_Grade)

# Terminal++
A C++ library for interacting with ANSI/VT100 terminal or terminal emulator displays.

# Requirements

Terminal++ requires a C++17 compiler and the following libraries:
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

Terminal++ is currently automatically tested using MSVC 2019 and GCC 9.4.  For further information about the working status of the library, to report any bugs, or to make any feature requests, visit the [Issues page](https://github.com/KazDragon/terminalpp/issues).  Feel free to discuss using Github Discussions!

# The Basics

The purpose of the library is to be able to allow the usage of ANSI escape codes to their fullest potential in order to create fully-featured text-based applications.  The use cases for such software include interactive forms of command-line software, and even GUI-style applications over the internet using terminal emulators such as Xterm, PuTTY, or even some MUD clients (e.g Tintin++).

At its most fundamental level, Terminal++ is in the business of manipulating character elements on the screen, where each element is encoded as a glyph, which describes the character that is presented to the user, and a series of non-character graphical attributes. These are encapsulated in the following classes:

* terminalpp::glyph - represents a character (which may be ASCII or any UTF-8 value up to U+FFFF) and its character set (by default, this is the US_ASCII character set).
* terminalpp::attribute - a collection of variables that describe the non-character graphical part of the output, such as the foreground and background colours, whether it is bold, underlined, and so on.

These are combined into Terminal++'s fundamental type, terminalpp::element.

The library's primary abstraction is the terminal class, which is a container for all the operations one might want to do on it.  Because the terminal is unaware whether you are sending data to the console or over a network connection, it uses a type-erased "channel" concept onto which these operations are mapped.  This concept aligns closely with telnetpp::session, serverpp::tcp_socket and consolepp::console in the Telnet++, Server++ and Console++ libraries for easy integration. Terminal++ also provides stdout_channel, which can serve for programs who do not require asynchronous input.  This is used in the examples below.

# Strings

terminalpp::elements can be collected together using the terminalpp::string class.  It has several constructors for different uses.  For example, one of the constructors takes a std::string and an attribute to apply to all those characters for when you want something like print out a single red error message.  In addition, there are the user-defined literal suffixes _ts (terminal string) and _ets (encoded terminal string) to help construct more complicated strings

[Hello, World! project](examples/hello_world)
```cpp
#include <terminalpp/terminal.hpp>
#include <terminalpp/stdout_channel.hpp>

int main()
{
    using namespace terminalpp::literals;
    terminalpp::string text = "Hello, world!\n"_ts;

    terminalpp::stdout_channel channel;
    terminalpp::terminal terminal{channel};
    terminal << text;
}

// Constructs a terminalpp::string, and then prints it to the terminal as, "Hello, world!"
```

By using _ets, you can also encode attributes within the text.  For example:

[Encoded Hello, World! project](examples/encoded_hello_world)
```cpp
#include <terminalpp/terminal.hpp>
#include <terminalpp/stdout_channel.hpp>

int main()
{
    using namespace terminalpp::literals;
    terminalpp::string text = "\\[1Hello, \\[2World! \\x\\U263A\n"_ets;

    terminalpp::stdout_channel channel;
    terminalpp::terminal terminal{channel};
    terminal << text;
}
```

This prints out "Hello, " in red text, then "World!" in green text, and then a smiley face in the default colour.  See the Wiki for more information about the attribute encoding used and its possibilities.  It is also possible to change the attributes for each element programatically.

```cpp
terminalpp::string text = ...;
text[0].attribute_.intensity_ = terminalpp::graphics::intensity::bold;
```

# Terminals

At this point, you have everything you need for a standard command-line application that uses colour or other properties, such as you might see in the output of a CMake script or Google Test results, or even standard unix functions such as ls.  But the terminal class allows for complete control over the terminal's appearance.

[Positioned smiley project](examples/positioned_smiley)
```cpp
#include <terminalpp/terminal.hpp>
#include <terminalpp/stdout_channel.hpp>

int main()
{
    using namespace terminalpp::literals;
    terminalpp::stdout_channel channel;
    terminalpp::terminal terminal{channel};

    terminal
        << terminalpp::save_cursor_position()
        << terminalpp::move_cursor({0, 0})
        << "\\U263A"_ets
        << terminalpp::restore_cursor_position();
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
#include <terminalpp/terminal.hpp>
#include <terminalpp/canvas.hpp>
#include <terminalpp/screen.hpp>
#include <terminalpp/stdout_channel.hpp>

int main()
{
    terminalpp::stdout_channel channel;
    terminalpp::terminal terminal{channel};
    terminalpp::screen screen{terminal};
    terminalpp::canvas canvas({80, 24});

    // Set the entire canvas to be the letter 'x' on a shocking pink
    // background.  Because, why not?
    terminalpp::element element('x');
    element.attribute_.background_colour_ = terminalpp::high_colour(5, 1, 2);

    for (terminalpp::coordinate_type y = 0; y < canvas.size().height_; ++y)
    {
        for (terminalpp::coordinate_type x = 0; x < canvas.size().width_; ++x)
        {
            canvas[x][y] = element;
        }
    }

    screen.draw(canvas);
    // screen is now actually shocking pink.

    canvas[10][15].glyph_ = 'y';
    canvas[10][15].attribute_.background_colour_ = terminalpp::graphics::colour::blue;

    screen.draw(canvas);
    // screen is still shocking pink, but there is now a letter 'y' with a
    // blue background at position (10, 15).
}
```

All of these examples so far have ignored the read function for terminals since they only output to the screen.  It is also possible to read from a terminal.  This operation converts a sequence of ANSI protocol bytes into a series of tokens that can be inspected for regular text, control sequences (including function keys, arrow keys, etc.) and even mouse operations.  The example project for this uses the [Console++ library](https://github.com/KazDragon/consolepp) to provide asynchronous key-by-key input from a console window.

[wait_for_mouse_click project](examples/wait_for_mouse_click)
```cpp
// ...

static void schedule_async_read();

static consolepp::console console{io_context};
static console_channel channel{console};

// ...

terminalpp::terminal terminal{
    channel,
    [] {
        terminalpp::behaviour behaviour;
        behaviour.supports_basic_mouse_tracking = true;
        return behaviour;
    }()
};

int main()
{
    terminal << terminalpp::save_cursor_position()
             << terminalpp::use_alternate_screen_buffer()
             << terminalpp::enable_mouse()
             << terminalpp::erase_display()
             << terminalpp::move_cursor({0, 0})
             << "Click with a mouse button to exit!\n";
        
    schedule_async_read();
    io_context.run();

    terminal << terminalpp::disable_mouse()
             << terminalpp::use_normal_screen_buffer()
             << terminalpp::restore_cursor_position()
             << fmt::format("mouse clicked at ({},{})\n", mouse_position.x_, mouse_position.y_);
}

static void handle_token(terminalpp::token const &token);
static void schedule_async_read()
{
    terminal.async_read(
        [](terminalpp::tokens tokens) {
            for (auto const &token : tokens) {
                handle_token(token);
            }

            schedule_async_read();
        });
}

// ...

```
