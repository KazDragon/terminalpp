# Changelog

## Version 1.4 - Migrated away from Conan
1. [x] Conan packages are still built for Terminal++, but it is no longer required for building.
2. [x] Added some constants for a more accessible colour palette.

## Version 1.3 - Migrated to Conan
1. [x] Now uses the Conan package manager for managing its dependencies.

## Version 1.2 - Untitled Feature Release
1. [x] Migrated from CppUnit to GTest
2. [x] Pre-computed values of high_colour and greyscale_colour, which reduced the size of terminalpp::element from 16B to 12B.

## Version 1.0 - Terminal Management
1. [x] A utility for creating strings with embedded ANSI attributes
  * [x] terminalpp::string
  * This will be immediately useful in line-oriented programs to construct and output streams of attributed (coloured, emboldened, underlined, etc.) text.

2. [x] A utility for managing ANSI escape codes that are not bound to specific characters.  For example, commands for moving the cursor, changing the screen's title, clearing the screen, etc.
  * [x] terminalpp::terminal

3. [x] Utilities for managing screens of attributed characters
  * [x] terminalpp::canvas
  * [x] terminalpp::screen
  * This will be useful for those who wish to develop a more graphical or "curses-style" user interface.
