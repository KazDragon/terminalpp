#include "terminalpp/attribute.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class colour_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(colour_test);
        CPPUNIT_TEST(can_construct_from_low_colour_enum);
    CPPUNIT_TEST_SUITE_END();
    
private :
    void can_construct_from_low_colour_enum();
};

CPPUNIT_TEST_SUITE_REGISTRATION(colour_test);

void colour_test::can_construct_from_low_colour_enum()
{
    terminalpp::ansi::graphics::colour col(
        terminalpp::ansi::graphics::colour::red);
    
    terminalpp::colour expected_colour = terminalpp::low_colour(col);
    
    auto result_colour = [](terminalpp::colour const &col)
    {
        return col;
    }(col);
    
    CPPUNIT_ASSERT_EQUAL(expected_colour, result_colour);
}
