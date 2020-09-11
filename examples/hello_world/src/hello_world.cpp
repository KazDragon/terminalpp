#include <terminalpp/terminal.hpp>

int main()
{
    using namespace terminalpp::literals;
    terminalpp::string text = "Hello, world!\n"_ts;

    terminalpp::terminal terminal;
    std::cout << terminal.write(text);
}
