#include <terminalpp/terminal.hpp>

void write_to_console(terminalpp::bytes data)
{
    std::cout << std::string{data.begin(), data.end()};
}

int main()
{
    using namespace terminalpp::literals;
    terminalpp::terminal terminal{write_to_console};

    terminal.write(write_to_console)
        << terminalpp::save_cursor_position()
        << terminalpp::move_cursor({0, 0})
        << "\\U263A"_ets
        << terminalpp::restore_cursor_position();
}
