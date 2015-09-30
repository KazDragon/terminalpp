#include "expect_sequence.hpp"
#include <cppunit/TestAssert.h>

void expect_sequence(std::string const &expected, std::string const &result)
{
    if (expected != result)
    {
        std::cout << "\n"
                  << "Expected: \"" << expected << "\"\n"
                  << "Result:   \"" << result << "\"\n";
    }
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}
