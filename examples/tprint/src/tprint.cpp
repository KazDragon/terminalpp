#include <terminalpp/terminal.hpp>
#include <terminalpp/encoder.hpp>
#include <terminalpp/stdout_channel.hpp>
#include <cstdlib>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "USAGE: " << argv[0] << " <encoded string>\n";
    }
    else
    {
        terminalpp::stdout_channel channel;
        terminalpp::terminal terminal{channel};
        terminal
            << terminalpp::encode(argv[1])
            << "\n";
    }

    return EXIT_SUCCESS;
}