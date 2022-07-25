#include <terminalpp/terminal.hpp>
#include <terminalpp/string.hpp>
#include <terminalpp/stdout_channel.hpp>
#include <iostream>
#include <string>

int main()
{
    terminalpp::stdout_channel channel;
    terminalpp::terminal terminal{channel};

    using namespace terminalpp::literals;
    terminal << "\\[1SUCCESS!\\x\n"_ets;
}
