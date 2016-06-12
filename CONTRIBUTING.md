# How to Contribute to Terminal++

## General

Contributions are welcome!

## Scope

Terminal++ is a C++-14 library aimed at providing an easy-to-use API for managing communication to and from terminal emulators, such as Xterm, PuTTY, Tinyfugue, and so on.  It provides both core knowledge about how to communicate with all kinds of terminals, as well as as set of abstractions (e.g. "screen" and "terminal") that can be used to communicate in more general ways.  Finally, Terminal++ aims to build a database of terminal capabilities so that output can be tailored to the terminal being used.

## Contributing

Contributions can be in several forms:
* Opening issues - the simplest way of contributing can be to say how you would like to use the library.  Or, alternatively, what you couldn't work out from the documentation.  Every ticket closed ends up improving the library!
* Providing fixes - any size welcome.  Spotted a typo?  You can edit this online and submit a pull request.  Have a complete new feature you want to develop and integrate?  Awesome!  You can fork the repo, develop on a branch, and then submit that as a pull request.

## Guidelines

This is a C++-14 codebase, with a Standard Library/Boost look-and-feel.  Please let your tests drive your development, and keep it to around 80 characters per line to make it easier to read.  The rest is negotiable during integration.
