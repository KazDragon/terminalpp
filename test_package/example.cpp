#include <terminalpp/terminal.hpp>
#include <terminalpp/string.hpp>
#include <iostream>
#include <string>

int main()
{
    using namespace terminalpp::literals;
    terminalpp::terminal terminal;

    terminal.write(
        [](terminalpp::bytes data) 
        { 
            std::cout << std::string(std::cbegin(data), std::cend(data));
        })
        << "\\[1SUCCESS!\\x\n"_ets;
}
