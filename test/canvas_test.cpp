// #include "terminalpp/canvas.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class canvas_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(canvas_test);
        CPPUNIT_TEST(dummy_test);
    CPPUNIT_TEST_SUITE_END();
    
private :
    void dummy_test();
};

CPPUNIT_TEST_SUITE_REGISTRATION(canvas_test);

void canvas_test::dummy_test()
{
    CPPUNIT_ASSERT(false);
}





