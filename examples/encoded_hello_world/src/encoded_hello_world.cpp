#include <terminalpp/terminal.hpp>

void read_from_console(terminalpp::tokens)
{
    // See later.
}

void write_to_console(terminalpp::bytes data)
{
    std::cout << std::string(data.begin(), data.end());
}

int main()
{
    using namespace terminalpp::literals;
    terminalpp::string text = "\\[1Hello, \\[2World! \\x\\U263A\n"_ets;

    terminalpp::terminal terminal{read_from_console, write_to_console};
    terminal << text;
}
