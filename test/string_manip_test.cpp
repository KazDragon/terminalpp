#include <terminalpp/string.hpp>
#include <gtest/gtest.h>

using namespace terminalpp::literals;

TEST(inserting_at_the_beginning_of_an_empty_string, gives_a_string_with_that_value)
{
    const terminalpp::string test_data = "test data"_ets;
    
    terminalpp::string str;
    str.insert(str.begin(), test_data.begin(), test_data.end());
    
    ASSERT_EQ(test_data, str);
}

TEST(inserting_at_the_end_of_an_empty_string, gives_a_string_with_that_value)
{
    const terminalpp::string test_data = "test data"_ets;
    
    terminalpp::string str;
    str.insert(str.end(), test_data.begin(), test_data.end());
    
    ASSERT_EQ(test_data, str);
}

TEST(inserting_at_the_beginning_of_a_string_with_content, prepends_that_value_to_the_string)
{
    const terminalpp::string test_data = "test_data"_ets;
    const terminalpp::string append_data = "one "_ets;
    const terminalpp::string expected_data = "one test_data"_ets;
    
    terminalpp::string str = test_data;
    str.insert(str.begin(), append_data.begin(), append_data.end());
    
    ASSERT_EQ(expected_data, str);
}

TEST(inserting_at_the_end_of_a_string_with_content, appends_that_value_to_the_string)
{
    const auto test_data = "test_data"_ets;
    const auto append_data = " one"_ets;
    const auto expected_data = "test_data one"_ets;
    
    auto str = test_data;
    str.insert(str.end(), append_data.begin(), append_data.end());
    
    ASSERT_EQ(expected_data, str);
}

TEST(inserting_into_the_middle_of_a_string_with_content, inserts_text_at_that_location)
{
    const auto test_data = "test data"_ets;
    const auto insert_data = "this "_ets;
    const auto expected_data = "test this data"_ets;
    
    auto str = test_data;
    str.insert(str.begin() + 5, insert_data.begin(), insert_data.end());
    
    ASSERT_EQ(expected_data, str);
}