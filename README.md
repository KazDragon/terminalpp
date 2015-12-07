
[![Stories on the Backlog](https://badge.waffle.io/KazDragon/terminalpp.png?label=backlog&title=Stories%20On%20The%20Backlog)](https://waffle.io/KazDragon/terminalpp)

[![Stories in Ready](https://badge.waffle.io/KazDragon/terminalpp.png?label=ready&title=Stories%20In%20Ready)](https://waffle.io/KazDragon/terminalpp)

[![Stories in Progress](https://badge.waffle.io/KazDragon/terminalpp.png?label=in%20progress&title=Stories%20In%20Progress)](https://waffle.io/KazDragon/terminalpp)

# Terminal++
A C++ library for interacting with ANSI terminal windows.

# Requirements

Terminal++ requires a C++14 library and the Boost Libraries.  It also uses CppUnit for its testing suite, which is compiled optionally.

# Features / Roadmap

1. [x] A utility for creating strings with embedded ANSI attributes
  * [x] terminalpp::string
  * This will be immediately useful in line-oriented programs to construct and output streams of attributed (coloured, emboldened, underlined, etc.) text.

2. [x] A utility for managing ANSI escape codes that are not bound to specific characters.  For example, commands for moving the cursor, changing the screen's title, clearing the screen, etc.
  * [x] terminalpp::terminal

3. [x] Utilities for managing screens of attributed characters
  * [x] terminalpp::canvas
  * [x] terminalpp::canvas_view
  * [x] terminalpp::screen
  * This will be useful for those who wish to develop a more graphical or "curses-style" user interface.

YOU ARE HERE! What follows is for future implementation.

4. [ ] A set of classes that implement a windowing user interface
  * [ ] terminalpp::component
  * [ ] terminalpp::layout
  * This will enable developer to create fully featured console-based UIs that can be delivered over any channel to which you can write text, such as terminal windows or even TCP/IP socket connections.

# Status

Terminal++ is currently automatically tested using:

* Clang 3.4: [![Build Status](https://travis-ci.org/KazDragon/terminalpp.svg?branch=master)](https://travis-ci.org/KazDragon/terminalpp)

# The Basics

The purpose of the library is to be able to allow the usage of ANSI escape codes to their fullest potential so that fully-featured text-based applications can be created.  The use cases for such software include interactive forms of command-line software, and even GUI-style applications over the internet using terminal emulators such as Xterm, PuTTY, or even some MUD clients (e.g Tintin++).

At its most fundamental level, Terminal++ is in the business of manipulating character elements on the screen, where each element is encoded as a glyph, which describes the character that is presented to the user, and a series of non-character graphical properties. These are encapsulated in the following classes:

* terminalpp::glyph - represents a character (which may be ASCII or any UTF-8 value up to U+FFFF) and its character set (by default, this is the US_ASCII character set).
* terminalpp::attribute - a collection of variables that describe the non-character graphical part of the output, such as the foreground and background colours, whether it is bold, underlined, and so on.

These are combined into Terminal++'s fundamental structure, terminalpp::element.

# Strings

terminalpp::elements can be collected together as strings.  The terminalpp::string class is used for that, but there are user-defined literals that can help: _ts (terminal string) and _ets (encoded terminal string)

```
int main()
{
    using namespace terminalpp::literals;
    std::cout << "Hello, world!\n"_ts; 
}

// Constructs a terminalpp::string, and then prints it as simply, "Hello, world!"
```

By using _ets, you can also encode attributes within the text.  For example:

```
int main()
{
    using namespace terminalpp::literals;
    std::cout << "\\[1Hello, \\[2World! \\U263A\n"_ets;
}
