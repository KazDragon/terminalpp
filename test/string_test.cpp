#include "terminalpp/string.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class string_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(string_test);
        CPPUNIT_TEST(can_construct_from_string_and_attribute);
        CPPUNIT_TEST(can_aggregate_initialize_from_string_and_attribute);
        CPPUNIT_TEST(converting_empty_tstring_yields_plain_empty_string);
        CPPUNIT_TEST(converting_tstring_with_attributes_yields_plain_string);
        CPPUNIT_TEST(converting_tstring_with_unicode_values_yields_plain_string_with_unicode_values);
    CPPUNIT_TEST_SUITE_END();
    
private :
    void can_construct_from_string_and_attribute();
    void can_aggregate_initialize_from_string_and_attribute();
    void converting_empty_tstring_yields_plain_empty_string();
    void converting_tstring_with_attributes_yields_plain_string();
    void converting_tstring_with_unicode_values_yields_plain_string_with_unicode_values();
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

void string_test::converting_empty_tstring_yields_plain_empty_string()
{
    terminalpp::string tstr;
    std::string str = terminalpp::to_string(tstr);
    std::string expected = "";
    
    CPPUNIT_ASSERT_EQUAL(expected, str);
}

void string_test::converting_tstring_with_attributes_yields_plain_string()
{
    using namespace terminalpp::literals;
    
    auto tstr = "\\[1Test\\]2String"_ets;
    auto str  = terminalpp::to_string(tstr);
    
    std::string expected = "TestString";
    
    CPPUNIT_ASSERT_EQUAL(expected, str);
}

void string_test::converting_tstring_with_unicode_values_yields_plain_string_with_unicode_values()
{
    using namespace terminalpp::literals;
    
    auto tstr = "Test\\U010EString"_ets;
    auto str = terminalpp::to_string(tstr);
    
    std::string expected = "Test\xC4\x8EString";
    
    CPPUNIT_ASSERT_EQUAL(expected, str);
}
