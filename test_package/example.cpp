#include <terminalpp/terminal.hpp>
#include <terminalpp/string.hpp>
#include <iostream>
#include <string>

int main()
{
    terminalpp::terminal terminal{
        [](terminalpp::tokens) {
        },
        [](terminalpp::bytes data) {
            std::cout << std::string(std::cbegin(data), std::cend(data));
        }
    }

    using namespace terminalpp::literals;
    terminal << "\\[1SUCCESS!\\x\n"_ets;
}
