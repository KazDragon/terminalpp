#include "terminalpp/terminal.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

class terminal_test_fixture : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(terminal_test_fixture);
        // TODO:
    CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(terminal_test_fixture);
