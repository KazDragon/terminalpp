#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class parser_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(parser_test);
        CPPUNIT_TEST(dummy_test);
        /*
        parser empty string yields nothing
        parse text yields text
        parse command yields command
        parse meta command yields meta command
        parse mouse command yield mouse command
        -- all above for both 7- and 8- bit.

        parse partial command yields nothing
        parse partial mouse command yields nothing
        */
    CPPUNIT_TEST_SUITE_END();

private :
    void dummy_test();
};

CPPUNIT_TEST_SUITE_REGISTRATION(parser_test);

void parser_test::dummy_test()
{
    CPPUNIT_ASSERT(false);
}
