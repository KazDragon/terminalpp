#include "terminalpp/string.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class string_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(string_test);
        CPPUNIT_TEST(can_construct_from_string_and_attribute);
        CPPUNIT_TEST(can_aggregate_initialize_from_string_and_attribute);
    CPPUNIT_TEST_SUITE_END();
    
private :
    void can_construct_from_string_and_attribute();
    void can_aggregate_initialize_from_string_and_attribute();
};

CPPUNIT_TEST_SUITE_REGISTRATION(string_test);

void string_test::can_construct_from_string_and_attribute()
{
    terminalpp::attribute attr;
    attr.polarity_ = terminalpp::ansi::graphics::polarity::negative;
    
    auto str = [](terminalpp::string const &str)
    {
        return str;
    }(terminalpp::string(std::string("xy"), attr));
    
    CPPUNIT_ASSERT_EQUAL(size_t{2}, str.size());
    CPPUNIT_ASSERT_EQUAL(terminalpp::glyph('x'), str[0].glyph_);
    CPPUNIT_ASSERT_EQUAL(attr, str[0].attribute_);
    CPPUNIT_ASSERT_EQUAL(terminalpp::glyph('y'), str[1].glyph_);
    CPPUNIT_ASSERT_EQUAL(attr, str[1].attribute_);
}

void string_test::can_aggregate_initialize_from_string_and_attribute()
{
    terminalpp::attribute attr;
    attr.polarity_ = terminalpp::ansi::graphics::polarity::negative;
    
    auto str = [](terminalpp::string const &str)
    {
        return str;
    }({"xy", attr});
    
    CPPUNIT_ASSERT_EQUAL(size_t{2}, str.size());
    CPPUNIT_ASSERT_EQUAL(terminalpp::glyph('x'), str[0].glyph_);
    CPPUNIT_ASSERT_EQUAL(attr, str[0].attribute_);
    CPPUNIT_ASSERT_EQUAL(terminalpp::glyph('y'), str[1].glyph_);
    CPPUNIT_ASSERT_EQUAL(attr, str[1].attribute_);
}
