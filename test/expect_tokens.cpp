#include "expect_tokens.hpp"
#include "terminalpp/terminal.hpp"
#include <gtest/gtest.h>
#include <iostream>

namespace {

template <class Token>
struct token_compare_visitor_impl : boost::static_visitor<>
{
    explicit token_compare_visitor_impl(Token const &token)
        : token_(token)
    {
    }

    template <class ExpectedToken>
    void operator()(ExpectedToken const &expected_token)
    {
        std::cerr << "\nExpected was: " << expected_token;
        std::cerr << "\nResult was: " << token_;

        FAIL();
    }

    void operator()(Token const &expected_token)
    {
        if (!(token_ == expected_token))
        {
            std::cerr << "\nExpected was: " << expected_token;
            std::cerr << "\nResult was: " << token_;
        }

        ASSERT_EQ(expected_token, token_);
    }

    Token const &token_;
};

struct token_compare_visitor : boost::static_visitor<>
{
    explicit token_compare_visitor(terminalpp::token const &expected_token)
        : expected_token_(expected_token)
    {
    }

    template <class ResultToken>
    void operator()(ResultToken const &token)
    {
        token_compare_visitor_impl<ResultToken> visitor(token);
        boost::apply_visitor(visitor, expected_token_);
    }

    terminalpp::token const &expected_token_;
};

}

void expect_tokens(
    terminalpp::tokens const &expected_tokens,
    terminalpp::tokens const &result_tokens)
{
    ASSERT_EQ(expected_tokens.size(), result_tokens.size());

    for (auto &&lhs = expected_tokens.cbegin(),
              &&rhs = result_tokens.cbegin();
         lhs != expected_tokens.cend();
         ++lhs, ++rhs)
    {
        token_compare_visitor visitor(*lhs);
        boost::apply_visitor(visitor, *rhs);
    }
}
