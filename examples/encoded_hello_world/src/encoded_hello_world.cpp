#include <terminalpp/terminal.hpp>

void write_to_console(terminalpp::bytes data)
{
    std::cout << std::string(data.begin(), data.end());
}

int main()
{
    using namespace terminalpp::literals;
    terminalpp::string text = "\\[1Hello, \\[2World! \\x\\U263A\n"_ets;

    terminalpp::terminal terminal{write_to_console};
    terminal.write(write_to_console) << text;
}
