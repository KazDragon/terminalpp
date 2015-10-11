#include "terminalpp/canvas.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class canvas_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(canvas_test);
        CPPUNIT_TEST(can_perform_loops_over_canvas);
    CPPUNIT_TEST_SUITE_END();
    
private :
    void can_perform_loops_over_canvas();
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
    
    for (terminalpp::s32 row = 0; row < size.height; ++row)
    {
        for (terminalpp::s32 column = 0; column < size.width; column++)
        {
            auto expected = terminalpp::element('x');
            auto result   = terminalpp::element(canvas[column][row]);
            CPPUNIT_ASSERT_EQUAL(expected, result);
        }
    }
}

/*
void canvas_test::can_perform_algorithms_on_rows()
{
    terminalpp::canvas canvas({5, 5});
}
*/