#include <terminalpp/terminal.hpp>
#include <terminalpp/canvas.hpp>
#include <terminalpp/screen.hpp>

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
    console_channel channel;
    terminalpp::terminal terminal{channel};
    terminalpp::screen screen{terminal};
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

    screen.draw(canvas);
    // screen is now actually shocking pink.

    canvas[10][15].glyph_ = 'y';
    canvas[10][15].attribute_.background_colour_ = terminalpp::graphics::colour::blue;

    screen.draw(canvas);
    // screen is still shocking pink, but there is now a letter 'y' with a
    // blue background at position (10, 15).
}
