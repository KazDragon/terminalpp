#include <terminalpp/string.hpp>
#include <gtest/gtest.h>

using namespace terminalpp::literals;

TEST(inserting_a_character_at_the_beginning_of_an_empty_string, gives_a_string_with_that_value)
{
    auto const inserted_character = 'a';
    auto const expected_data = "a"_ets;

    terminalpp::string str;
    str.insert(str.begin(), inserted_character);

    ASSERT_EQ(expected_data, str);
}

TEST(inserting_at_the_beginning_of_an_empty_string, gives_a_string_with_that_value)
{
    auto const test_data = "test data"_ets;
    
    terminalpp::string str;
    str.insert(str.begin(), test_data.begin(), test_data.end());
    
    ASSERT_EQ(test_data, str);
}

TEST(inserting_a_character_at_the_end_of_an_empty_string, gives_a_string_with_that_value)
{
    auto const inserted_character = 'a';
    auto const expected_data = "a"_ets;

    terminalpp::string str;
    str.insert(str.end(), inserted_character);

    ASSERT_EQ(expected_data, str);
}

TEST(inserting_at_the_end_of_an_empty_string, gives_a_string_with_that_value)
{
    auto const test_data = "test data"_ets;
    
    terminalpp::string str;
    str.insert(str.end(), test_data.begin(), test_data.end());
    
    ASSERT_EQ(test_data, str);
}

TEST(inserting_a_character_at_the_beginning_of_a_string_with_content, prepends_that_value_to_the_string)
{
    auto const test_data = "test_data"_ets;
    auto const prepend_data = 'c';
    auto const expected_data = "ctest_data"_ets;
    
    terminalpp::string str = test_data;
    str.insert(str.begin(), prepend_data);
    
    ASSERT_EQ(expected_data, str);
}

TEST(inserting_at_the_beginning_of_a_string_with_content, prepends_that_value_to_the_string)
{
    auto const test_data = "test_data"_ets;
    auto const prepend_data = "one "_ets;
    auto const expected_data = "one test_data"_ets;
    
    terminalpp::string str = test_data;
    str.insert(str.begin(), prepend_data.begin(), prepend_data.end());
    
    ASSERT_EQ(expected_data, str);
}

TEST(inserting_a_character_at_the_end_of_a_string_with_content, appends_that_value_to_the_string)
{
    auto const test_data = "test_data"_ets;
    auto const append_data = 'z';
    auto const expected_data = "test_dataz"_ets;
    
    auto str = test_data;
    str.insert(str.end(), append_data);
    
    ASSERT_EQ(expected_data, str);
}

TEST(inserting_at_the_end_of_a_string_with_content, appends_that_value_to_the_string)
{
    auto const test_data = "test_data"_ets;
    auto const append_data = " one"_ets;
    auto const expected_data = "test_data one"_ets;
    
    auto str = test_data;
    str.insert(str.end(), append_data.begin(), append_data.end());
    
    ASSERT_EQ(expected_data, str);
}

TEST(inserting_a_character_into_the_middle_of_a_string_with_content, inserts_text_at_that_location)
{
    auto const test_data = "test data"_ets;
    auto const insert_data = '0';
    auto const expected_data = "test 0data"_ets;
    
    auto str = test_data;
    str.insert(str.begin() + 5, insert_data);
    
    ASSERT_EQ(expected_data, str);
}

TEST(inserting_into_the_middle_of_a_string_with_content, inserts_text_at_that_location)
{
    auto const test_data = "test data"_ets;
    auto const insert_data = "this "_ets;
    auto const expected_data = "test this data"_ets;
    
    auto str = test_data;
    str.insert(str.begin() + 5, insert_data.begin(), insert_data.end());
    
    ASSERT_EQ(expected_data, str);
}
