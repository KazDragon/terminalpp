#include "expect_sequence.hpp"
#include <cppunit/TestAssert.h>
#include <boost/format.hpp>
#include <cctype>

static std::string escape(std::string const &str)
{
    std::string result;

    for (auto ch : str)
    {
        if (!isprint(ch))
        {
            result += boost::str(boost::format("0x%02X") % int(ch));
        }
        else
        {
            result += ch;
        }
    }

    return result;
}

void expect_sequence(std::string const &expected, std::string const &result)
{

    if (expected != result)
    {
        std::cout << "\n"
                  << "Expected: \"" << escape(expected) << "\"\n"
                  << "Result:   \"" << escape(result) << "\"\n";
    }

    CPPUNIT_ASSERT_EQUAL(expected, result);
}
