#include <terminalpp/terminal.hpp>

void read_from_console(terminalpp::tokens)
{
    // Unused
}

void write_to_console(terminalpp::bytes data)
{
    std::cout << std::string{data.begin(), data.end()};
}

int main()
{
    terminalpp::terminal terminal{read_from_console, write_to_console};

    using namespace terminalpp::literals;
    terminalpp::string text = "Low colours:\n"_ts;
    terminal << text;

    for (auto col = terminalpp::graphics::colour::black; 
         col <= terminalpp::graphics::colour::default_; 
         col = static_cast<terminalpp::graphics::colour>(int(col) + 1))
    {
        terminalpp::element elem = ' ';
        elem.attribute_.intensity_ = terminalpp::graphics::intensity::faint;
        elem.attribute_.background_colour_ = terminalpp::low_colour(col);
        terminal << elem;
    }

    for (auto col = terminalpp::graphics::colour::black; 
         col <= terminalpp::graphics::colour::default_; 
         col = static_cast<terminalpp::graphics::colour>(int(col) + 1))
    {
        terminalpp::element elem = ' ';
        elem.attribute_.background_colour_ = terminalpp::low_colour(col);
        terminal << elem;
    }

    for (auto col = terminalpp::graphics::colour::black; 
         col <= terminalpp::graphics::colour::default_; 
         col = static_cast<terminalpp::graphics::colour>(int(col) + 1))
    {
        terminalpp::element elem = ' ';
        elem.attribute_.intensity_ = terminalpp::graphics::intensity::bold;
        elem.attribute_.background_colour_ = terminalpp::low_colour(col);
        terminal << elem;
    }

    terminal << "\nHigh colours:\n";

    for (auto r = 0; r < 6; ++r)
    {
        for (auto g = 0; g < 6; ++g)
        {
            for (auto b = 0; b < 6; ++b)
            {
                terminalpp::element elem = ' ';
                elem.attribute_.background_colour_ = terminalpp::high_colour(r, g, b);
                terminal << elem;
            }
        }

        terminal << "\n";
    }

    terminal << "Greyscale colours:\n";

    for (auto shade = 0; shade <= 23; ++shade)
    {
        terminalpp::element elem = ' ';
        elem.attribute_.background_colour_ = terminalpp::greyscale_colour(shade);
        terminal << elem;
    }

    terminal << "\n";
}