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
    mouse::event_type         mouse_event_type_;
    point                     mouse_coordinate_;
    byte_storage              argument_;
    std::vector<byte_storage> arguments_;
};

}}
