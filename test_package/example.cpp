#include <terminalpp/terminal.hpp>
#include <terminalpp/string.hpp>
#include <iostream>
#include <string>

struct console_channel
{
    void async_read(std::function<void (terminalpp::bytes)>) {}
    void write(terminalpp::bytes data) 
    {
        std::cout << std::string{data.begin(), data.end()};
    }
    void close(){}
    bool is_alive() const { return true; }
};

int main()
{
    console_channel channel;
    terminalpp::terminal terminal{channel};

    using namespace terminalpp::literals;
    terminal << "\\[1SUCCESS!\\x\n"_ets;
}
