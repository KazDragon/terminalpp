#pragma once

#include "terminalpp/token.hpp"
#include <boost/optional.hpp>
#include <vector>

namespace terminalpp { namespace detail {

class parser
{
public :
    parser();

    boost::optional<terminalpp::token> operator()(char input);

private :
    enum class state
    {
        idle,
        cr,
        lf,
        escape,
        arguments,
        mouse0,
        mouse1,
        mouse2,
    };

    boost::optional<terminalpp::token> parse_idle(char input);
    boost::optional<terminalpp::token> parse_cr(char input);
    boost::optional<terminalpp::token> parse_lf(char input);
    boost::optional<terminalpp::token> parse_escape(char input);
    boost::optional<terminalpp::token> parse_arguments(char input);
    boost::optional<terminalpp::token> parse_mouse0(char input);
    boost::optional<terminalpp::token> parse_mouse1(char input);
    boost::optional<terminalpp::token> parse_mouse2(char input);

    state                    state_;
    char                     initialiser_;
    char                     extender_;
    bool                     meta_;
    terminalpp::u8           mouse_button_;
    terminalpp::u32          mouse_x_;
    terminalpp::u32          mouse_y_;
    std::string              argument_;
    std::vector<std::string> arguments_;
};

}}
