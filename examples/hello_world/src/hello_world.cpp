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
    terminalpp::string text = "Hello, world!\n"_ts;

    terminalpp::terminal terminal{read_from_console, write_to_console};
    terminal << text;
}
