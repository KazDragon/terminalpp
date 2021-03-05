#ifndef TERMINALPP_TEST_EXPECT_TOKENS_HPP_
#define TERMINALPP_TEST_EXPECT_TOKENS_HPP_

#include "terminalpp/token.hpp"

void expect_tokens(
    terminalpp::tokens const &expected_tokens,
    terminalpp::tokens const &result_tokens);

#endif
