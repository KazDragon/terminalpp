#include <terminalpp/terminal.hpp>

int main()
{
    using namespace terminalpp::literals;
    terminalpp::string text = "\\[1Hello, \\[2World! \\x\\U263A\n"_ets;

    terminalpp::terminal terminal;
    std::cout << terminal.write(text);
}