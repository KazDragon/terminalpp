#include <terminalpp/ansi_terminal.hpp>
#include <terminalpp/encoder.hpp>
#include <cstdlib>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "USAGE: " << argv[0] << " <encoded string>\n";
    }
    else
    {
        terminalpp::ansi_terminal terminal;
        std::cout << terminal.write(terminalpp::encode(argv[1])) << "\n";
    }

    return EXIT_SUCCESS;
}