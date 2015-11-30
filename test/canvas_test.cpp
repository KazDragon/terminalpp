#include "terminalpp/canvas.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class canvas_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(canvas_test);
        CPPUNIT_TEST(can_perform_loops_over_canvas);
        CPPUNIT_TEST(can_assign_from_canvas_to_canvas);
        CPPUNIT_TEST(resizing_canvas_larger_keeps_content);
        CPPUNIT_TEST(resizing_canvas_smaller_truncates_content);
    CPPUNIT_TEST_SUITE_END();
    
private :
    void can_perform_loops_over_canvas();
    void can_assign_from_canvas_to_canvas();
    void resizing_canvas_larger_keeps_content();
    void resizing_canvas_smaller_truncates_content();
};

CPPUNIT_TEST_SUITE_REGISTRATION(canvas_test);

void canvas_test::can_perform_loops_over_canvas()
{
    terminalpp::canvas canvas({5, 5});
    auto size = canvas.size();

    CPPUNIT_ASSERT_EQUAL(terminalpp::extent(5, 5), size);
    
    for (auto &&elem : canvas)
    {
        elem = {'x'};
    }
    
    for (terminalpp::u32 row = 0; row < size.height; ++row)
    {
        for (terminalpp::u32 column = 0; column < size.width; column++)
        {
            auto expected = terminalpp::element('x');
            auto result   = terminalpp::element(canvas[column][row]);
            CPPUNIT_ASSERT_EQUAL(expected, result);
        }
    }
}

void canvas_test::can_assign_from_canvas_to_canvas()
{
    terminalpp::canvas canvas_source({1, 1});
    terminalpp::canvas canvas_dest({1, 1});
    
    canvas_dest[0][0] = canvas_source[0][0];
}

void canvas_test::resizing_canvas_larger_keeps_content()
{
    auto small_size = terminalpp::extent{5, 6};
    auto large_size = terminalpp::extent{10, 9};
    
    terminalpp::canvas canvas(small_size);
    
    for (auto &&elem : canvas)
    {
        elem = {'x'};
    }
    
    canvas.resize(large_size);
    CPPUNIT_ASSERT_EQUAL(large_size, canvas.size());
    
    for (terminalpp::u32 row = 0; row < large_size.height; ++row)
    {
        for (terminalpp::u32 column = 0; column < large_size.width; ++column)
        {
            auto expected = 
                row < small_size.height && column < small_size.width 
              ? terminalpp::element{'x'}
              : terminalpp::element{' '};
              
            auto result   = terminalpp::element(canvas[column][row]);
            CPPUNIT_ASSERT_EQUAL(expected, result);
        }
    }
}

void canvas_test::resizing_canvas_smaller_truncates_content()
{
    auto small_size = terminalpp::extent{5, 6};
    auto large_size = terminalpp::extent{10, 9};
    
    terminalpp::canvas canvas(large_size);

    for (terminalpp::u32 row = 0; row < large_size.height; ++row)
    {
        for (terminalpp::u32 column = 0; column < large_size.width; ++column)
        {
            canvas[column][row] = {char(column * row)};
        }
    }
    
    canvas.resize(small_size);

    for (terminalpp::u32 row = 0; row < small_size.height; ++row)
    {
        for (terminalpp::u32 column = 0; column < small_size.width; ++column)
        {
            auto expected = terminalpp::element(char(column * row));
            auto result   = terminalpp::element(canvas[column][row]);
            
            CPPUNIT_ASSERT_EQUAL(expected, result);
        }
    }
}
