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
