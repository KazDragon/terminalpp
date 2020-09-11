#include <terminalpp/terminal.hpp>

int main()
{
    using namespace terminalpp::literals;
    terminalpp::terminal terminal;

    std::cout << terminal.save_cursor()
              << terminal.move_cursor({0,0})
              << terminal.write("\\U263A"_ets)
              << terminal.restore_cursor();
}
