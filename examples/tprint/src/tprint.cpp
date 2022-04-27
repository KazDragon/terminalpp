#include <terminalpp/terminal.hpp>
#include <terminalpp/encoder.hpp>
#include <cstdlib>

void read_from_console(terminalpp::tokens)
{
    // Unused
}

void write_to_console(terminalpp::bytes data)
{
    std::cout << std::string{data.begin(), data.end()};
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "USAGE: " << argv[0] << " <encoded string>\n";
    }
    else
    {
        terminalpp::terminal terminal{read_from_console, write_to_console};
        terminal
            << terminalpp::encode(argv[1])
            << "\n";
    }

    return EXIT_SUCCESS;
}