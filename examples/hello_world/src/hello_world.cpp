#include <terminalpp/terminal.hpp>
#include <terminalpp/stdout_channel.hpp>

int main()
{
    using namespace terminalpp::literals;
    terminalpp::string text = "Hello, world!\n"_ts;

    terminalpp::stdout_channel channel;
    terminalpp::terminal terminal{channel};
    terminal << text;
}
