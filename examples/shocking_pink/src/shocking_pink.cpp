#include <terminalpp/terminal.hpp>
#include <terminalpp/canvas.hpp>
#include <terminalpp/screen.hpp>

int main()
{
    terminalpp::terminal terminal;
    terminalpp::screen screen;
    terminalpp::canvas canvas({80, 24});

    // Set the entire canvas to be the letter 'x' on a shocking pink
    // background.  Because, why not?
    terminalpp::element element('x');
    element.attribute_.background_colour_ = terminalpp::high_colour(5, 1, 2);

    for (terminalpp::coordinate_type y = 0; y < canvas.size().height; ++y)
    {
        for (terminalpp::coordinate_type x = 0; x < canvas.size().width; ++x)
        {
            canvas[x][y] = element;
        }
    }

    std::cout << screen.draw(terminal, canvas);
    // screen is now actually shocking pink.

    canvas[10][15].glyph_ = 'y';
    canvas[10][15].attribute_.background_colour_ =
        terminalpp::ansi::graphics::colour::blue;

    std::cout << screen.draw(terminal, canvas);
    // screen is still shocking pink, but there is now a letter 'y' with a
    // blue background at position (10, 15).
}
