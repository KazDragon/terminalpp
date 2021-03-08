#include <terminalpp/terminal.hpp>

void write_to_console(terminalpp::bytes data)
{
    std::cout << std::string{data.begin(), data.end()};
}

int main()
{
    using namespace terminalpp::literals;
    terminalpp::string text = "Hello, world!\n"_ts;

    terminalpp::terminal terminal;
    terminal.write(write_to_console) << text;
}
