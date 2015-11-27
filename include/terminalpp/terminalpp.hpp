#ifndef TERMINALPP_TERMINALPP_HPP_
#define TERMINALPP_TERMINALPP_HPP_

// The basic layer of terminal reading and writing is defined in terminal.hpp,
// which includes everything you need to know about the terminal, including
// token types (virtual keys, control sequences, mouse reports), 
// manipulation of elements to form strings, and basic cursor and size 
// manipulation.
#include "terminalpp/terminal.hpp"

// More advanced knowledge of the terminal comes in the form of the screen,
// which embeds canvases to be drawn on.
#include "terminalpp/screen.hpp"

#endif
