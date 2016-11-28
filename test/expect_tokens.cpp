#include "expect_tokens.hpp"
#include "terminalpp/terminal.hpp"
#include "io/ansi/control_sequence.hpp"
#include "io/ansi/mouse.hpp"
#include "io/virtual_key.hpp"
#include <gtest/gtest.h>
#include <iostream>

namespace {

template <class Token>
struct token_compare_visitor_impl : boost::static_visitor<>
{
    token_compare_visitor_impl(Token const &token)
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
    token_compare_visitor(terminalpp::token const &expected_token)
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

void expect_token(
    std::string const &input,
    terminalpp::token const &expected_token)
{
    expect_tokens(input, {expected_token});
}

void expect_tokens(
    std::string const &input,
    std::vector<terminalpp::token> const &expected_tokens)
{
    terminalpp::terminal terminal;

    auto result = terminal.read(input);

    ASSERT_EQ(expected_tokens.size(), result.size());

    for (std::vector<terminalpp::token>::const_iterator
             lhs = expected_tokens.begin(),
             rhs = result.begin();
         lhs != expected_tokens.end();
         ++lhs, ++rhs)
    {
        token_compare_visitor visitor(*lhs);
        boost::apply_visitor(visitor, *rhs);
    }

}

template <class Expected> void expect_token(
    std::string const &input,
    Expected const &expected)
{
    terminalpp::terminal terminal;

    auto result = terminal.read(input);

    ASSERT_EQ(false, result.empty());

    ASSERT_EQ(
        boost::get<Expected>(expected),
        boost::get<Expected>(result[0]));
}
