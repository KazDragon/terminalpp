#include <terminalpp/terminal.hpp>

void read_from_console(terminalpp::tokens)
{
    // See later.
}

void write_to_console(terminalpp::bytes data)
{
    std::cout << std::string{data.begin(), data.end()};
}

int main()
{
    using namespace terminalpp::literals;
    terminalpp::terminal terminal{read_from_console, write_to_console};

    terminal
        << terminalpp::save_cursor_position()
        << terminalpp::move_cursor({0, 0})
        << "\\U263A"_ets
        << terminalpp::restore_cursor_position();
}
