#include "terminalpp/string.hpp"
#include <gtest/gtest.h>

TEST(string_test, can_construct_from_string_and_attribute)
{
    terminalpp::attribute attr;
    attr.polarity_ = terminalpp::ansi::graphics::polarity::negative;
    
    auto str = [](terminalpp::string const &str)
    {
        return str;
    }(terminalpp::string(std::string("xy"), attr));
    
    ASSERT_EQ(size_t{2}, str.size());
    ASSERT_EQ(terminalpp::glyph('x'), str[0].glyph_);
    ASSERT_EQ(attr, str[0].attribute_);
    ASSERT_EQ(terminalpp::glyph('y'), str[1].glyph_);
    ASSERT_EQ(attr, str[1].attribute_);
}

TEST(string_test, can_aggregate_initialize_from_string_and_attribute)
{
    terminalpp::attribute attr;
    attr.polarity_ = terminalpp::ansi::graphics::polarity::negative;
    
    auto str = [](terminalpp::string const &str)
    {
        return str;
    }({"xy", attr});
    
    ASSERT_EQ(size_t{2}, str.size());
    ASSERT_EQ(terminalpp::glyph('x'), str[0].glyph_);
    ASSERT_EQ(attr, str[0].attribute_);
    ASSERT_EQ(terminalpp::glyph('y'), str[1].glyph_);
    ASSERT_EQ(attr, str[1].attribute_);
}

TEST(string_test, converting_empty_tstring_yields_plain_empty_string)
{
    terminalpp::string tstr;
    std::string str = terminalpp::to_string(tstr);
    std::string expected = "";
    
    ASSERT_EQ(expected, str);
}

TEST(string_test, converting_tstring_with_attributes_yields_plain_string)
{
    using namespace terminalpp::literals;
    
    auto tstr = "\\[1Test\\]2String"_ets;
    auto str  = terminalpp::to_string(tstr);
    
    std::string expected = "TestString";
    
    ASSERT_EQ(expected, str);
}

TEST(string_test, converting_tstring_with_unicode_values_yields_plain_string_with_unicode_values)
{
    using namespace terminalpp::literals;
    
    auto tstr = "Test\\U010EString"_ets;
    auto str = terminalpp::to_string(tstr);
    
    std::string expected = "Test\xC4\x8EString";
    
    ASSERT_EQ(expected, str);
}
