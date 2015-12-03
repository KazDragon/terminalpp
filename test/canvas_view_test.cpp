#include "terminalpp/canvas_view.hpp"
#include "terminalpp/canvas.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class canvas_view_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(canvas_view_test);
        CPPUNIT_TEST(default_canvas_view_views_same_basis_as_canvas);
        CPPUNIT_TEST(default_canvas_view_has_same_size_as_canvas);
        
        CPPUNIT_TEST(offset_canvas_view_has_offset_basis);
        CPPUNIT_TEST(offset_canvas_view_has_reduced_size);
        CPPUNIT_TEST(offset_is_cumulative);
    CPPUNIT_TEST_SUITE_END();
    
private :
    void default_canvas_view_views_same_basis_as_canvas();
    void default_canvas_view_has_same_size_as_canvas();
    
    void offset_canvas_view_has_offset_basis();
    void offset_canvas_view_has_reduced_size();
    
    void offset_is_cumulative();
};

CPPUNIT_TEST_SUITE_REGISTRATION(canvas_view_test);

void canvas_view_test::default_canvas_view_views_same_basis_as_canvas()
{
    terminalpp::canvas canvas({2, 2});
    terminalpp::canvas_view canvas_view(canvas);
    
    canvas_view[0][0] = 'a';
    canvas_view[0][1] = 'b';
    canvas_view[1][0] = 'c';
    canvas_view[1][1] = 'd';
    
    CPPUNIT_ASSERT(canvas[0][0] == 'a');
    CPPUNIT_ASSERT(canvas[0][1] == 'b');
    CPPUNIT_ASSERT(canvas[1][0] == 'c');
    CPPUNIT_ASSERT(canvas[1][1] == 'd');
}

void canvas_view_test::default_canvas_view_has_same_size_as_canvas()
{
    terminalpp::canvas canvas({2, 2});
    terminalpp::canvas_view canvas_view(canvas);
    
    CPPUNIT_ASSERT_EQUAL(canvas.size(), canvas_view.size());
}

void canvas_view_test::offset_canvas_view_has_offset_basis()
{
    terminalpp::canvas canvas({2, 2});
    terminalpp::canvas_view canvas_view(canvas);
    
    canvas_view.offset_by({1, 1});
    canvas_view[0][0] = 'x';
    CPPUNIT_ASSERT(canvas_view[0][0] == 'x');
    
    CPPUNIT_ASSERT(canvas[0][0] == ' ');
    CPPUNIT_ASSERT(canvas[0][1] == ' ');
    CPPUNIT_ASSERT(canvas[1][0] == ' ');
    CPPUNIT_ASSERT(canvas[1][1] == 'x');
}

void canvas_view_test::offset_canvas_view_has_reduced_size()
{
    terminalpp::canvas canvas({2, 2});
    terminalpp::canvas_view canvas_view(canvas);
    
    canvas_view.offset_by({1, 1});
    
    CPPUNIT_ASSERT_EQUAL(
        (canvas.size() - terminalpp::extent{1, 1}),
        canvas_view.size());
}

void canvas_view_test::offset_is_cumulative()
{
    terminalpp::canvas canvas({3, 3});
    terminalpp::canvas_view canvas_view(canvas);
    
    canvas_view.offset_by({1, 1});
    canvas_view.offset_by({1, 1});
    
    canvas_view[0][0] = 'x';
    CPPUNIT_ASSERT(canvas[2][2] == 'x');
}
