#ifndef TERMINALPP_TEST_EXPECT_TOKENS_HPP_
#define TERMINALPP_TEST_EXPECT_TOKENS_HPP_

#include "terminalpp/token.hpp"
#include <vector>

// When a string is read in by a terminal, expect the one following token.
void expect_token(
    std::string const &input,
    terminalpp::token const &expected_token);

// When a string is read in by a terminal, expect the following tokens.
void expect_tokens(
    std::string const &input,
    std::vector<terminalpp::token> const &expected_tokens);

#endif
