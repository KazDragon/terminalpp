#include "terminal_test.hpp"
#include "terminalpp/screen.hpp"
#include "expect_sequence.hpp"
#include <gtest/gtest.h>

using namespace terminalpp::literals;

namespace {

class a_screen : public a_terminal
{
public:
    a_screen()
      : size_{5, 5},
        canvas_(size_),
        reference_terminal_{
            [](terminalpp::tokens) { 
                FAIL(); 
            },
            [this](terminalpp::bytes data)
            {
                reference_result_.append(data.begin(), data.end());
            }
        },
        screen_{terminal_}

    {
        terminal_.set_size(size_);
        reference_terminal_.set_size(size_);

        terminal_ << ""_ets;
        reference_terminal_ << ""_ets;

        result_.clear();
        reference_result_.clear();
    }

protected:
    void fill_canvas()
    {
        auto ch = 'a';
        for (terminalpp::coordinate_type y = 0; y < canvas_.size().height_; ++y)
        {
            for (terminalpp::coordinate_type x = 0; x < canvas_.size().width_; ++x)
            {
                canvas_[x][y] = ch++;
            }
        }
    }

    terminalpp::extent size_;
    terminalpp::canvas canvas_;
    terminalpp::terminal reference_terminal_;
    terminalpp::byte_storage reference_result_;
    terminalpp::screen screen_;
};

}

TEST_F(a_screen, first_draw_of_blank_screen_draws_clear_screen_only)
{
    // What is expected is that the screen will be cleared, and then since
    // each element is assumed to be a blank, and the canvas is also blank,
    // no further drawing is necessary.
    reference_terminal_ << terminalpp::erase_display();
    
    screen_.draw(canvas_);

    expect_sequence(reference_result_, result_);
}

TEST_F(a_screen, first_draw_of_screen_with_content_draws_clear_screen_then_content)
{
    fill_canvas();

    // What is expected here is that the screen will be cleared, and then
    // the content will be drawn starting by moving the cursor to the top
    // left and proceeding left-to-right, top-to-bottom, moving the cursor
    // on each new line.
    reference_terminal_ << terminalpp::erase_display();

    for (terminalpp::coordinate_type y = 0; y < canvas_.size().height_; ++y)
    {
        reference_terminal_ << terminalpp::move_cursor({0, y});

        for (terminalpp::coordinate_type x = 0; x < canvas_.size().width_; ++x)
        {
            reference_terminal_ << canvas_[x][y];
        }
    }

    screen_.draw(canvas_);

    expect_sequence(reference_result_, result_);
}

TEST_F(a_screen, drawing_after_drawing_draws_nothing)
{
    fill_canvas();

    screen_.draw(canvas_);
    result_.clear();

    // Since we have just drawn this screen, we expect that drawing it again
    // will yield no changes.
    screen_.draw(canvas_);
    expect_sequence(reference_result_, result_);
}

TEST_F(a_screen, drawing_after_modifying_one_element_writes_one_element)
{
    fill_canvas();
    screen_.draw(canvas_);
    result_.clear();

    canvas_[2][3] = 'x';
    
    reference_terminal_
        << terminalpp::move_cursor({2, 3})
        << terminalpp::element{'x'};

    screen_.draw(canvas_);
    expect_sequence(reference_result_, result_);
}

TEST_F(a_screen, drawing_after_modifying_two_elements_writes_two_elements)
{
    fill_canvas();
    screen_.draw(canvas_);
    result_.clear();

    canvas_[2][3] = 'x';
    canvas_[3][4] = 'y';
    
    reference_terminal_
        << terminalpp::move_cursor({2, 3})
        << terminalpp::element{'x'}
        << terminalpp::move_cursor({3, 4})
        << terminalpp::element{'y'};

    screen_.draw(canvas_);
    expect_sequence(reference_result_, result_);
}

TEST_F(a_screen, drawing_consecutive_elements_does_not_write_cursor_moves)
{
    fill_canvas();
    screen_.draw(canvas_);
    result_.clear();

    canvas_[2][3] = 'x';
    canvas_[3][3] = 'y';
    
    reference_terminal_
        << terminalpp::move_cursor({2, 3})
        << terminalpp::element{'x'}
        << terminalpp::element{'y'};

    screen_.draw(canvas_);
    expect_sequence(reference_result_, result_);
}
