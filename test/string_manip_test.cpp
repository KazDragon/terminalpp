#include <gtest/gtest.h>
#include <terminalpp/string.hpp>

using namespace terminalpp::literals;  // NOLINT

TEST(
    inserting_a_character_at_the_beginning_of_an_empty_string,
    gives_a_string_with_that_value)
{
    auto const inserted_character = 'a';
    auto const expected_data = "a"_ets;

    terminalpp::string str;
    str.insert(str.begin(), inserted_character);

    ASSERT_EQ(expected_data, str);
}

TEST(
    inserting_an_element_at_the_beginning_of_an_empty_string,
    gives_a_string_with_that_value)
{
    auto const inserted_element = R"(\[1a)"_ete;
    auto const expected_data = R"(\[1a)"_ets;

    terminalpp::string str;
    str.insert(str.begin(), inserted_element);

    ASSERT_EQ(expected_data, str);
}

TEST(
    inserting_at_the_beginning_of_an_empty_string,
    gives_a_string_with_that_value)
{
    auto const test_data = "test data"_ets;

    terminalpp::string str;
    str.insert(str.begin(), test_data.begin(), test_data.end());

    ASSERT_EQ(test_data, str);
}

TEST(
    inserting_a_character_at_the_end_of_an_empty_string,
    gives_a_string_with_that_value)
{
    auto const inserted_character = 'a';
    auto const expected_data = "a"_ets;

    terminalpp::string str;
    str.insert(str.end(), inserted_character);

    ASSERT_EQ(expected_data, str);
}

TEST(
    inserting_an_element_at_the_end_of_an_empty_string,
    gives_a_string_with_that_value)
{
    auto const inserted_element = R"(\}09a)"_ete;
    auto const expected_data = R"(\}09a)"_ets;

    terminalpp::string str;
    str.insert(str.end(), inserted_element);

    ASSERT_EQ(expected_data, str);
}

TEST(inserting_at_the_end_of_an_empty_string, gives_a_string_with_that_value)
{
    auto const test_data = "test data"_ets;

    terminalpp::string str;
    str.insert(str.end(), test_data.begin(), test_data.end());

    ASSERT_EQ(test_data, str);
}

TEST(
    inserting_a_character_at_the_beginning_of_a_string_with_content,
    prepends_that_value_to_the_string)
{
    auto const test_data = "test_data"_ets;
    auto const prepend_data = 'c';
    auto const expected_data = "ctest_data"_ets;

    terminalpp::string str = test_data;
    str.insert(str.begin(), prepend_data);

    ASSERT_EQ(expected_data, str);
}

TEST(
    inserting_an_element_at_the_beginning_of_a_string_with_content,
    prepends_that_value_to_the_string)
{
    auto const test_data = "test_data"_ets;
    auto const prepend_data = R"(\i>x)"_ete;
    auto const expected_data = R"(\i>x\xtest_data)"_ets;

    terminalpp::string str = test_data;
    str.insert(str.begin(), prepend_data);

    ASSERT_EQ(expected_data, str);
}

TEST(
    inserting_at_the_beginning_of_a_string_with_content,
    prepends_that_value_to_the_string)
{
    auto const test_data = "test_data"_ets;
    auto const prepend_data = "one "_ets;
    auto const expected_data = "one test_data"_ets;

    terminalpp::string str = test_data;
    str.insert(str.begin(), prepend_data.begin(), prepend_data.end());

    ASSERT_EQ(expected_data, str);
}

TEST(
    inserting_a_character_at_the_end_of_a_string_with_content,
    appends_that_value_to_the_string)
{
    auto const test_data = "test_data"_ets;
    auto const append_data = 'z';
    auto const expected_data = "test_dataz"_ets;

    auto str = test_data;
    str.insert(str.end(), append_data);

    ASSERT_EQ(expected_data, str);
}

TEST(
    inserting_an_element_at_the_end_of_a_string_with_content,
    appends_that_value_to_the_string)
{
    auto const test_data = "test_data"_ets;
    auto const append_data = R"(\>234z)"_ete;
    auto const expected_data = R"(test_data\>234z)"_ets;

    auto str = test_data;
    str.insert(str.end(), append_data);

    ASSERT_EQ(expected_data, str);
}

TEST(
    inserting_at_the_end_of_a_string_with_content,
    appends_that_value_to_the_string)
{
    auto const test_data = "test_data"_ets;
    auto const append_data = " one"_ets;
    auto const expected_data = "test_data one"_ets;

    auto str = test_data;
    str.insert(str.end(), append_data.begin(), append_data.end());

    ASSERT_EQ(expected_data, str);
}

TEST(
    inserting_an_element_into_the_middle_of_a_string_with_content,
    inserts_text_at_that_location)
{
    auto const test_data = "test data"_ets;
    auto const insert_data = R"(\[2\U2691)"_ete;
    auto const expected_data = R"(test \[2\U2691\xdata)"_ets;

    auto str = test_data;
    str.insert(str.begin() + 5, insert_data);

    ASSERT_EQ(expected_data, str);
}

TEST(
    inserting_a_character_into_the_middle_of_a_string_with_content,
    inserts_text_at_that_location)
{
    auto const test_data = "test data"_ets;
    auto const insert_data = '0';
    auto const expected_data = "test 0data"_ets;

    auto str = test_data;
    str.insert(str.begin() + 5, insert_data);

    ASSERT_EQ(expected_data, str);
}

TEST(
    inserting_into_the_middle_of_a_string_with_content,
    inserts_text_at_that_location)
{
    auto const test_data = "test data"_ets;
    auto const insert_data = "this "_ets;
    auto const expected_data = "test this data"_ets;

    auto str = test_data;
    str.insert(str.begin() + 5, insert_data.begin(), insert_data.end());

    ASSERT_EQ(expected_data, str);
}

TEST(erasing_an_empty_string, gives_an_empty_string)
{
    auto const expected_data = ""_ets;

    terminalpp::string str;
    str.erase();

    ASSERT_EQ(expected_data, str);
}

TEST(erasing_the_end_of_an_empty_string, gives_an_empty_string)
{
    auto const expected_data = ""_ets;

    terminalpp::string str;
    str.erase(str.end());

    ASSERT_EQ(expected_data, str);
}

TEST(erasing_a_string_with_content, gives_an_empty_string)
{
    auto const test_data = "test_data"_ets;
    auto const expected_data = ""_ets;

    auto str = test_data;
    str.erase();

    ASSERT_EQ(expected_data, str);
}

TEST(erasing_the_beginning_of_a_string_with_content, gives_an_empty_string)
{
    auto const test_data = "test_data"_ets;
    auto const expected_data = ""_ets;

    auto str = test_data;
    str.erase(str.begin());

    ASSERT_EQ(expected_data, str);
}

TEST(erasing_the_end_of_a_string_with_content, gives_the_content)
{
    auto const test_data = "test_data"_ets;
    auto const expected_data = "test_data"_ets;

    auto str = test_data;
    str.erase(str.end());

    ASSERT_EQ(expected_data, str);
}

TEST(
    erasing_from_the_middle_of_a_string_with_content,
    truncates_the_string_at_that_point)
{
    auto const test_data = "test_data"_ets;
    auto const expected_data = "test"_ets;

    auto str = test_data;
    str.erase(str.begin() + 4);

    ASSERT_EQ(expected_data, str);
}

TEST(
    erasing_a_substring_from_a_string_with_content,
    removes_that_substring_from_the_string)
{
    auto const test_data = "test data"_ets;
    auto const expected_data = "teta"_ets;

    auto str = test_data;
    str.erase(str.begin() + 2, str.begin() + 7);

    ASSERT_EQ(expected_data, str);
}