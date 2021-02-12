#pragma once

#include "terminalpp/token.hpp"
#include <boost/optional.hpp>
#include <vector>

namespace terminalpp { namespace detail {

class parser
{
public :
    parser();

    boost::optional<terminalpp::token> operator()(byte input);

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

    boost::optional<terminalpp::token> parse_idle(byte input);
    boost::optional<terminalpp::token> parse_cr(byte input);
    boost::optional<terminalpp::token> parse_lf(byte input);
    boost::optional<terminalpp::token> parse_escape(byte input);
    boost::optional<terminalpp::token> parse_arguments(byte input);
    boost::optional<terminalpp::token> parse_mouse0(byte input);
    boost::optional<terminalpp::token> parse_mouse1(byte input);
    boost::optional<terminalpp::token> parse_mouse2(byte input);

    state                     state_;
    byte                      initialiser_;
    byte                      extender_;
    bool                      meta_;
    byte                      mouse_button_;
    coordinate_type           mouse_x_;
    coordinate_type           mouse_y_;
    byte_storage              argument_;
    std::vector<byte_storage> arguments_;
};

}}
