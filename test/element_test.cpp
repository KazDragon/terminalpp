#include "terminalpp/element.hpp"
#include <gtest/gtest.h>

TEST(element_test, can_implicitly_construct_element_from_glyph)
{
    auto elem = [](terminalpp::element const &elem)
    {
        return elem;
    }(terminalpp::glyph('x'));
    
    ASSERT_EQ('x', elem.glyph_.character_);
}

TEST(element_test, can_implicitly_construct_element_from_char)
{
    auto elem = [](terminalpp::element const &elem)
    {
        return elem;
    }('x');
    
    ASSERT_EQ('x', elem.glyph_.character_);
}

TEST(element_test, can_aggregate_initialize_from_glyph)
{
    auto elem = [](terminalpp::element const &elem)
    {
        return elem;
    }({terminalpp::glyph('x')});
    
    ASSERT_EQ('x', elem.glyph_.character_);
}

TEST(element_test, can_aggregate_initialize_from_char)
{
    auto elem = [](terminalpp::element const &elem)
    {
        return elem;
    }({'x'});
    
    ASSERT_EQ('x', elem.glyph_.character_);
}
