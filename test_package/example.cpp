#include <iostream>
#include <terminalpp/string.hpp>

int main() 
{
    using namespace terminalpp::literals;
    auto str = "\\U0000"_ets;
    return !(str.size() == 1);
}
