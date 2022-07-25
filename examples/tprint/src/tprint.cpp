#include <terminalpp/terminal.hpp>
#include <terminalpp/encoder.hpp>
#include <cstdlib>

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

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "USAGE: " << argv[0] << " <encoded string>\n";
    }
    else
    {
        console_channel channel;
        terminalpp::terminal terminal{channel};
        terminal
            << terminalpp::encode(argv[1])
            << "\n";
    }

    return EXIT_SUCCESS;
}