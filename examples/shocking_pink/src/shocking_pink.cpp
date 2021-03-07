#include <terminalpp/terminal.hpp>
#include <terminalpp/canvas.hpp>
#include <terminalpp/palette.hpp>
#include <terminalpp/screen.hpp>

void write_to_console(terminalpp::bytes data)
{
    std::cout << std::string{data.begin(), data.end()};
}

int main()
{
    terminalpp::terminal terminal{write_to_console};
    terminalpp::screen screen;
    terminalpp::canvas canvas({80, 24});

    // Set the entire canvas to be the letter 'x' on a shocking pink
    // background.  Because, why not?
    terminalpp::element element('x');
    element.attribute_.background_colour_ = terminalpp::high_colour(5, 1, 2);

    for (terminalpp::coordinate_type y = 0; y < canvas.size().height_; ++y)
    {
        for (terminalpp::coordinate_type x = 0; x < canvas.size().width_; ++x)
        {
            canvas[x][y] = element;
        }
    }

    screen.draw(terminal, canvas, write_to_console);
    // screen is now actually shocking pink.

    canvas[10][15].glyph_ = 'y';
    canvas[10][15].attribute_ = terminalpp::palette::bg_blue;

    screen.draw(terminal, canvas, write_to_console);
    // screen is still shocking pink, but there is now a letter 'y' with a
    // blue background at position (10, 15).
}
