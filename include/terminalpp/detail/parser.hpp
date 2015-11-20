#ifndef TERMINALPP_DETAIL_PARSER_HPP_
#define TERMINALPP_DETAIL_PARSER_HPP_

#include "terminalpp/token.hpp"
#include "terminalpp/detail/parse_helper.hpp"
#include <boost/optional.hpp>
#include <vector>

namespace terminalpp { namespace detail {

template <class InputIterator1, class InputIterator2>
std::vector<token> parse(InputIterator1 &begin, InputIterator2 end)
{
    auto result = std::vector<token>{};
    auto temps = parse_temps();

    auto current = begin;

    while (current != end)
    {
        auto parse_result = parse_helper(*current++, temps);

        if (parse_result)
        {
            result.push_back(parse_result.get());
            begin = current;
        }
    }

    return result;
}


}}

#endif
