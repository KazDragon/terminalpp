#include "terminalpp/screen.hpp"
#include "terminalpp/terminal.hpp"
#include "expect_sequence.hpp"
#include <gtest/gtest.h>

using namespace terminalpp::literals;

TEST(screen_test, first_draw_of_blank_screen_draws_clear_screen_only)
{
    auto const size = terminalpp::extent{5, 5};
    auto const canvas = terminalpp::canvas(size);
    auto terminal = terminalpp::terminal();
    auto reference_terminal = terminalpp::terminal();

    terminal.set_size(size);
    reference_terminal.set_size(size);

    auto screen = terminalpp::screen();

    // What is expected is that the screen will be cleared, and then since
    // each element is assumed to be a blank, and the canvas is also blank,
    // no further drawing is necessary.
    auto expected =
        reference_terminal.erase_in_display(
            terminalpp::terminal::erase_display::all);

    auto result = screen.draw(terminal, canvas);

    expect_sequence(expected, result);
}

TEST(screen_test, first_draw_of_screen_with_content_draws_clear_screen_then_content)
{
    using namespace terminalpp::literals;

    auto const size = terminalpp::extent{5, 5};
    auto canvas = terminalpp::canvas(size);
    auto terminal = terminalpp::terminal();
    auto reference_terminal = terminalpp::terminal();

    terminal.set_size(size);
    reference_terminal.set_size(size);

    auto screen = terminalpp::screen();

    char ch = 'a';
    for (terminalpp::s32 y = 0; y < canvas.size().height; ++y)
    {
        for (terminalpp::s32 x = 0; x < canvas.size().width; ++x)
        {
            canvas[x][y] = ch++;
        }
    }

    // What is expected here is that the screen will be cleared, and then
    // the content will be drawn starting by moving the cursor to the top
    // left and proceeding left-to-right, top-to-bottom, moving the cursor
    // on each new line.
    auto expected =
        reference_terminal.erase_in_display(
                terminalpp::terminal::erase_display::all);

    for (terminalpp::s32 y = 0; y < canvas.size().height; ++y)
    {
        expected += reference_terminal.move_cursor({0, y});

        for (terminalpp::s32 x = 0; x < canvas.size().width; ++x)
        {
            expected += reference_terminal.write(canvas[x][y]);
        }
    }

    auto result = screen.draw(terminal, canvas);

    expect_sequence(expected, result);
}

TEST(screen_test, drawing_after_drawing_draws_nothing)
{
    auto const size = terminalpp::extent{5, 5};
    auto canvas = terminalpp::canvas(size);
    auto terminal = terminalpp::terminal();
    auto reference_terminal = terminalpp::terminal();

    terminal.set_size(size);
    reference_terminal.set_size(size);

    auto screen = terminalpp::screen();

    auto ch = 'a';
    for (terminalpp::s32 y = 0; y < canvas.size().height; ++y)
    {
        for (terminalpp::s32 x = 0; x < canvas.size().width; ++x)
        {
            canvas[x][y] = ch++;
        }
    }

    screen.draw(terminal, canvas);

    // Since we have just drawn this screen, we expect that drawing it again
    // will yield no changes.
    auto expected = std::string("");
    auto result = screen.draw(terminal, canvas);

    expect_sequence(expected, result);
}

TEST(screen_test, drawing_after_modifying_one_element_writes_one_element)
{
    auto const size = terminalpp::extent{5, 5};
    auto canvas = terminalpp::canvas(size);
    auto terminal = terminalpp::terminal();
    auto reference_terminal = terminalpp::terminal();

    terminal.set_size(size);
    reference_terminal.set_size(size);

    auto screen = terminalpp::screen();

    auto ch = 'a';
    for (terminalpp::s32 y = 0; y < canvas.size().height; ++y)
    {
        for (terminalpp::s32 x = 0; x < canvas.size().width; ++x)
        {
            canvas[x][y] = ch++;
        }
    }

    screen.draw(terminal, canvas);

    canvas[2][3] = 'x';

    auto expected = reference_terminal.move_cursor({2, 3})
                  + reference_terminal.write("x"_ts);

    auto result = screen.draw(terminal, canvas);

    expect_sequence(expected, result);
}

TEST(screen_test, drawing_after_modifying_two_elements_writes_two_elements)
{
    auto const size = terminalpp::extent{5, 5};
    auto canvas = terminalpp::canvas(size);
    auto terminal = terminalpp::terminal();
    auto reference_terminal = terminalpp::terminal();

    terminal.set_size(size);
    reference_terminal.set_size(size);

    auto screen = terminalpp::screen();

    auto ch = 'a';
    for (terminalpp::s32 y = 0; y < canvas.size().height; ++y)
    {
        for (terminalpp::s32 x = 0; x < canvas.size().width; ++x)
        {
            canvas[x][y] = ch++;
        }
    }

    screen.draw(terminal, canvas);

    canvas[2][3] = 'x';
    canvas[3][4] = 'y';

    auto expected = reference_terminal.move_cursor({2, 3});
    expected += reference_terminal.write("x"_ts);
    expected += reference_terminal.move_cursor({3, 4});
    expected += reference_terminal.write("y"_ts);

    auto result = screen.draw(terminal, canvas);

    expect_sequence(expected, result);
}

TEST(screen_test, drawing_consecutive_elements_does_not_write_cursor_moves)
{
    auto const size = terminalpp::extent{5, 5};
    auto canvas = terminalpp::canvas(size);
    auto terminal = terminalpp::terminal();
    auto reference_terminal = terminalpp::terminal();

    terminal.set_size(size);
    reference_terminal.set_size(size);

    auto screen = terminalpp::screen();

    auto ch = 'a';
    for (terminalpp::s32 y = 0; y < canvas.size().height; ++y)
    {
        for (terminalpp::s32 x = 0; x < canvas.size().width; ++x)
        {
            canvas[x][y] = ch++;
        }
    }

    screen.draw(terminal, canvas);

    canvas[2][3] = 'x';
    canvas[3][3] = 'y';

    auto expected = reference_terminal.move_cursor({2, 3})
                  + reference_terminal.write("xy"_ts);

    auto result = screen.draw(terminal, canvas);

    expect_sequence(expected, result);
}
