#include <terminalpp/ansi_terminal.hpp>

int main()
{
    using namespace terminalpp::literals;
    terminalpp::string text = "Hello, world!\n"_ts;

    terminalpp::ansi_terminal terminal;
    std::cout << terminal.write(text);
}
