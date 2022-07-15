#include "terminalpp/virtual_key.hpp"
#include <boost/io/ios_state.hpp>
#include <iomanip>
#include <iostream>
#include <tuple>

namespace terminalpp {

static virtual_key const default_vk = {};

// ==========================================================================
// OPERATOR==
// ==========================================================================
bool operator==(virtual_key const &lhs, virtual_key const &rhs)
{
    return 
        std::tie(
            lhs.key,
            lhs.modifiers,
            lhs.repeat_count,
            lhs.sequence)
     == std::tie(
            rhs.key,
            rhs.modifiers,
            rhs.repeat_count,
            rhs.sequence);
}

namespace {

// ==========================================================================
// OUTPUT_PIPE
// ==========================================================================
void output_pipe(std::ostream &out, bool &pipe)
{
    if (std::exchange(pipe, true))
    {
        out << "|";
    }
}

// ==========================================================================
// OPERATOR<<(INPUT_SEQUENCE)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, virtual_key::input_sequence const &is)
{
    std::visit([&out](auto const &seq) { out << seq; }, is);
    return out;
}

// ==========================================================================
// OPERATOR<<(VK_MODIFIER)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, vk_modifier const &vkm)
{
    bool pipe = false;

    if ((vkm & vk_modifier::shift) == vk_modifier::shift)
    {
        output_pipe(out, pipe);
        out << "shift";
    }

    if ((vkm & vk_modifier::ctrl) == vk_modifier::ctrl)
    {
        output_pipe(out, pipe);
        out << "ctrl";
    }

    if ((vkm & vk_modifier::alt) == vk_modifier::alt)
    {
        output_pipe(out, pipe);
        out << "alt";
    }

    if ((vkm & vk_modifier::meta) == vk_modifier::meta)
    {
        output_pipe(out, pipe);
        out << "meta";
    }

    return out;
}

// ==========================================================================
// OUTPUT_COMMA
// ==========================================================================
void output_comma(std::ostream &out, bool &comma)
{
    if (std::exchange(comma, true))
    {
        out << ", ";
    }
}

// ==========================================================================
// OUTPUT_VK
// ==========================================================================
void output_vk(std::ostream &out, vk const &key, bool &comma)
{
    if (key != default_vk.key)
    {
        output_comma(out, comma);
        out << "vk:" << key;
    }
}

// ==========================================================================
// OUTPUT_MODIFIERS
// ==========================================================================
void output_modifiers(
    std::ostream &out,
    vk_modifier const &vkm,
    bool &comma)
{
    if (vkm != default_vk.modifiers)
    {
        output_comma(out, comma);
        out << vkm;
    }
}

// ==========================================================================
// OUTPUT_REPEAT_COUNT
// ==========================================================================
void output_repeat_count(
    std::ostream &out,
    int repeat_count,
    bool &comma)
{
    if (repeat_count != default_vk.repeat_count)
    {
        output_comma(out, comma);
        out << "repeat:" << repeat_count;
    }
}

// ==========================================================================
// OUTPUT_INPUT_SEQUENCE
// ==========================================================================
void output_input_sequence(
    std::ostream &out,
    virtual_key::input_sequence const &sequence,
    bool &comma)
{
    if (!(sequence == default_vk.sequence))
    {
        output_comma(out, comma);
        out << "seq:" << sequence;
    }
}

}

// ==========================================================================
// OPERATOR<<
// ==========================================================================
std::ostream &operator<<(std::ostream &out, virtual_key const &vk)
{
    bool comma = false;

    out << "virtual_key[";
    output_vk(out, vk.key, comma);
    output_modifiers(out, vk.modifiers, comma);
    output_repeat_count(out, vk.repeat_count, comma);
    output_input_sequence(out, vk.sequence, comma);
    return out << "]";
}

// ==========================================================================
// OPERATOR<<(VK)
// ==========================================================================
std::ostream &operator<<(std::ostream &out, vk const &key)
{
    if (is_control_key(key))
    {
        switch (key)
        {
            case vk::cr :           out << "'\\r'"; break;
            case vk::lf :           out << "'\\n'"; break;
            case vk::ht :           out << "'\\t'"; break;

            case vk::cursor_up :    out << "cursor_up"; break;
            case vk::cursor_down :  out << "cursor_down"; break;
            case vk::cursor_left :  out << "cursor_left"; break;
            case vk::cursor_right : out << "cursor_right"; break;

            case vk::home :         out << "home"; break;
            case vk::ins :          out << "ins"; break;
            case vk::end :          out << "end"; break;
            case vk::pgup :         out << "pgup"; break;
            case vk::pgdn :         out << "pgdn"; break;

            case vk::bt :           out << "bt"; break;
            case vk::enter :        out << "enter"; break;

            case vk::f1 :           out << "f1"; break;
            case vk::f2 :           out << "f2"; break;
            case vk::f3 :           out << "f3"; break;
            case vk::f4 :           out << "f4"; break;
            case vk::f5 :           out << "f5"; break;
            case vk::f6 :           out << "f6"; break;
            case vk::f7 :           out << "f7"; break;
            case vk::f8 :           out << "f8"; break;
            case vk::f9 :           out << "f9"; break;
            case vk::f10 :          out << "f10"; break;
            case vk::f11 :          out << "f11"; break;
            case vk::f12 :          out << "f12"; break;
            default :
                boost::io::ios_all_saver ias(out);
                out << "'\\x" 
                    << std::hex << std::setfill('0') << std::setw(2) << std::uppercase 
                    << int(static_cast<unsigned char>(key))
                    << "'";
        }
    }
    else
    {
        out << "'" << static_cast<char>(key) << "'";
    }

    return out;
}

}
