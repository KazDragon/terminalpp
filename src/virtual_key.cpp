#include "terminalpp/virtual_key.hpp"
#include <iostream>

namespace terminalpp {

// ==========================================================================
// OPERATOR<<(VK_MODIFIER)
// ==========================================================================
static std::ostream &operator<<(std::ostream &out, vk_modifier const &vkm)
{
    bool pipe = false;

    if ((vkm & vk_modifier::shift) == vk_modifier::shift)
    {
        out << "shift";
        pipe = true;
    }

    if ((vkm & vk_modifier::ctrl) == vk_modifier::ctrl)
    {
        if (pipe)
        {
            out << "|";
        }

        out << "ctrl";
        pipe = true;
    }

    if ((vkm & vk_modifier::alt) == vk_modifier::alt)
    {
        if (pipe)
        {
            out << "|";
        }

        out << "alt";
        pipe = true;
    }

    if ((vkm & vk_modifier::meta) == vk_modifier::meta)
    {
        if (pipe)
        {
            out << "|";
        }

        out << "meta";
    }

    return out;
}

// ==========================================================================
// OPERATOR<<(VK)
// ==========================================================================
static std::ostream &operator<<(std::ostream &out, vk const &key)
{
    static constexpr vk abstract_key_start = vk::cursor_up;

    if (key < abstract_key_start)
    {
        out << "'" << static_cast<char>(key) << "'";
    }
    else
    {
        switch (key)
        {
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
            default :           out << "unk"; break;
        }
    }

    return out;
}

// ==========================================================================
// OPERATOR==
// ==========================================================================
bool operator==(virtual_key const &lhs, virtual_key const &rhs)
{
    return lhs.key == rhs.key
        && lhs.modifiers == rhs.modifiers
        && lhs.repeat_count == rhs.repeat_count;
}


// ==========================================================================
// OPERATOR<<
// ==========================================================================
std::ostream &operator<<(std::ostream &out, virtual_key const &vk)
{
    static virtual_key const default_vk = {};
    bool comma = false;

    out << "virtual_key[";

    if (vk.key != default_vk.key)
    {
        out << "vk:" << vk.key;
        comma = true;
    }

    if (vk.modifiers != default_vk.modifiers)
    {
        if (comma)
        {
            out << ", ";
        }

        out << vk.modifiers;
        comma = true;
    }

    if (vk.repeat_count != default_vk.repeat_count)
    {
        if (comma)
        {
            out << ", ";
        }

        out << "repeat:" << vk.repeat_count;
        comma = true;
    }

    if (vk.sequence != default_vk.sequence)
    {
        if (comma)
        {
            out << ", ";
        }

        out << "seq:" << vk.sequence;
    }

    return out << "]";
}

}
