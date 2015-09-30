[![Stories in Ready](https://badge.waffle.io/KazDragon/terminalpp.png?label=ready&title=Ready)](https://waffle.io/KazDragon/terminalpp)
# Terminal++
A C++ library for interacting with ANSI terminal windows.
[![Build Status](https://travis-ci.org/KazDragon/terminalpp.svg?branch=master)](https://travis-ci.org/KazDragon/terminalpp)

# Features / Roadmap

1. [x] A utility for creating strings with embedded ANSI attributes
  * terminalpp::string
  * This will be immediately useful in line-oriented programs to construct and
    output streams of attributed (coloured, emboldened, underlined, etc.) text.

2. [x] A utility for managing ANSI escape codes that are not bound to specific
   characters.  For example, commands for moving the cursor, changing the
   screen's title, clearing the screen, etc.

3. [ ] A utility for managing screens of attributed characters
  * terminalpp::screen
  * terminalpp::canvas
  * This will be useful for those who wish to develop a more graphical or
    "curses-style" user interface.

4. [ ] A set of classes that implement a windowing user interface
  * terminalpp::component
  * terminalpp::layout
  * This will enable developer to create fully featured console-based UIs
    that can be delivered over any channel to which you can write text, such
    as terminal windows or even TCP/IP socket connections.
