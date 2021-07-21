#include <terminalpp/element.hpp>
#include <gtest/gtest.h>

using namespace terminalpp::literals;

TEST(an_empty_element_udl, returns_a_default_element)
{
    terminalpp::element const expected_element = {};
    terminalpp::element const elem = ""_ete;

    ASSERT_EQ(expected_element, elem);
}

TEST(an_element_udl_with_a_character, returns_the_character)
{
    terminalpp::element const expected_element = {'x'};
    terminalpp::element const elem = "x"_ete;

    ASSERT_EQ(expected_element, elem);
}

TEST(an_element_udl_with_multiple_characters, returns_the_first_character)
{
    terminalpp::element const expected_element = {'x'};
    terminalpp::element const elem = "xyz"_ete;

    ASSERT_EQ(expected_element, elem);
}

TEST(an_element_udl_with_an_escape_slash, returns_a_default_element)
{
    terminalpp::element const expected_element = {};
    terminalpp::element const elem = "\\"_ete;

    ASSERT_EQ(expected_element, elem);
}