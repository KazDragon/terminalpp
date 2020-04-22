#include <terminalpp/ansi_terminal.hpp>

int main()
{
    using namespace terminalpp::literals;
    terminalpp::string text = "\\[1Hello, \\[2World! \\x\\U263A\n"_ets;

    terminalpp::ansi_terminal terminal;
    std::cout << terminal.write(text);
}