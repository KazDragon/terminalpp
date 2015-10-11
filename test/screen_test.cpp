#include "terminalpp/screen.hpp"
#include "terminalpp/terminal.hpp"
#include "expect_sequence.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace terminalpp::literals;

class screen_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(screen_test);
        CPPUNIT_TEST(first_draw_always_draws_entire_screen);
        CPPUNIT_TEST(drawing_after_drawing_draws_nothing);
        CPPUNIT_TEST(drawing_after_modifying_one_element_writes_one_element);
        CPPUNIT_TEST(drawing_after_modifying_two_elements_writes_two_elements);
        CPPUNIT_TEST(drawing_consecutive_elements_does_not_write_cursor_moves);
    CPPUNIT_TEST_SUITE_END();
    
private :
    void first_draw_always_draws_entire_screen();
    void drawing_after_drawing_draws_nothing();
    void drawing_after_modifying_one_element_writes_one_element();
    void drawing_after_modifying_two_elements_writes_two_elements();
    void drawing_consecutive_elements_does_not_write_cursor_moves();
};

CPPUNIT_TEST_SUITE_REGISTRATION(screen_test);

void screen_test::first_draw_always_draws_entire_screen()
{
    auto const size = terminalpp::extent{5, 5};
    auto reference_terminal = terminalpp::terminal();
    auto terminal = terminalpp::terminal();
    
    reference_terminal.set_size(size);
    terminal.set_size(size);
    
    terminalpp::screen screen(size);
    
    // What we expect is that the cursor will be moved to each row
    // and then spaces will be output.  In essence, a blank screen.
    
    std::string expected;
    for (terminalpp::s32 row = 0; row < size.height; ++row)
    {
        expected += reference_terminal.move_cursor({0, row})
                  + reference_terminal.write("     "_ets);
    }
    
    auto result = screen.draw(terminal);
    
    expect_sequence(expected, result);
}

void screen_test::drawing_after_drawing_draws_nothing()
{
    auto const size = terminalpp::extent{5, 5};
    auto terminal = terminalpp::terminal();
    terminal.set_size(size);
    
    terminalpp::screen screen(size);
    screen.draw(terminal);
    
    // Because the screen has just been drawn, there are no changes left to
    // draw.  Therefore, the result should be an empty string.
    auto expected = std::string("");
    auto result   = screen.draw(terminal);
    
    expect_sequence(expected, result);
}

void screen_test::drawing_after_modifying_one_element_writes_one_element()
{
    auto const size = terminalpp::extent{5, 5};
    auto reference_terminal = terminalpp::terminal();
    auto terminal = terminalpp::terminal();
    
    reference_terminal.set_size(size);
    terminal.set_size(size);
    
    terminalpp::screen screen(size);
    screen.draw(terminal);

    screen[2][3] = terminalpp::element{'x'};
    
    auto expected = reference_terminal.move_cursor({2, 3})
                  + reference_terminal.write("x"_ets);
                  
    auto result = screen.draw(terminal);
    
    expect_sequence(expected, result);
}

void screen_test::drawing_after_modifying_two_elements_writes_two_elements()
{
    auto const size = terminalpp::extent{5, 5};
    auto reference_terminal = terminalpp::terminal();
    auto terminal = terminalpp::terminal();
    
    reference_terminal.set_size(size);
    terminal.set_size(size);
    
    terminalpp::screen screen(size);
    screen.draw(terminal);

    screen[2][3] = terminalpp::element{'x'};
    screen[3][4] = terminalpp::element{'y'};
    
    auto expected = reference_terminal.move_cursor({2, 3})
                  + reference_terminal.write("x"_ets)
                  + reference_terminal.move_cursor({3, 4})
                  + reference_terminal.write("y"_ets);
                  
    auto result = screen.draw(terminal);
    
    expect_sequence(expected, result);
}

void screen_test::drawing_consecutive_elements_does_not_write_cursor_moves()
{
    auto const size = terminalpp::extent{5, 5};
    auto reference_terminal = terminalpp::terminal();
    auto terminal = terminalpp::terminal();
    
    reference_terminal.set_size(size);
    terminal.set_size(size);
    
    terminalpp::screen screen(size);
    screen.draw(terminal);

    screen[2][3] = terminalpp::element{'x'};
    screen[3][3] = terminalpp::element{'y'};
    
    auto expected = reference_terminal.move_cursor({2, 3})
                  + reference_terminal.write("xy"_ets);
                  
    auto result = screen.draw(terminal);
    
    expect_sequence(expected, result);
}
