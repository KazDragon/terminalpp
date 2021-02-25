#pragma once
#include "terminalpp/manip/disable_mouse.hpp"
#include "terminalpp/manip/enable_mouse.hpp"
#include "terminalpp/manip/erase_in_display.hpp"
#include "terminalpp/manip/erase_in_line.hpp"
#include "terminalpp/manip/hide_cursor.hpp"
#include "terminalpp/manip/move_cursor.hpp"
#include "terminalpp/manip/write_string.hpp"
#include "terminalpp/manip/restore_cursor.hpp"
#include "terminalpp/manip/save_cursor.hpp"
#include "terminalpp/manip/set_window_title.hpp"
#include "terminalpp/manip/show_cursor.hpp"
#include "terminalpp/manip/terminal_streamer.hpp"
#include "terminalpp/manip/use_normal_screen_buffer.hpp"
#include "terminalpp/manip/use_alternate_screen_buffer.hpp"

namespace terminalpp {

//* =========================================================================
/// \brief Streams an operation into a terminal, yielding a terminal_streamer
/// that allows further streaming operations in the expression.
//* =========================================================================
template <class Op>
terminal_streamer operator<<(terminal &term, Op &&op)
{
    terminal_streamer streamer(term);
    streamer << std::forward<Op>(op);
    return streamer;
}

}
