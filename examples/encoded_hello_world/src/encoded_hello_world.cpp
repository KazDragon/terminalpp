#include <terminalpp/terminal.hpp>
#include <terminalpp/stdout_channel.hpp>

int main()
{
    using namespace terminalpp::literals;
    terminalpp::string text = "\\[1Hello, \\[2World! \\x\\U263A\n"_ets;

    terminalpp::stdout_channel channel;
    terminalpp::terminal terminal{channel};
    terminal << text;
}
