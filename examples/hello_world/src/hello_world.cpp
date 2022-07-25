#include <terminalpp/terminal.hpp>

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
    using namespace terminalpp::literals;
    terminalpp::string text = "Hello, world!\n"_ts;

    console_channel channel;
    terminalpp::terminal terminal{channel};
    terminal << text;
}
