#include "terminalpp/terminal.hpp"
#include "terminalpp/detail/well_known_virtual_key.hpp"

namespace terminalpp {

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
terminal::terminal(
    read_function read_fn,
    write_function write_fn,
    behaviour beh)
  : read_(std::move(read_fn)),
    write_(std::move(write_fn)),
    behaviour_(std::move(beh))
{
}

// ==========================================================================
// SET_SIZE
// ==========================================================================
void terminal::set_size(extent size)
{
    state_.terminal_size_ = size;

    // The cursor positions that terminals have after a size change is
    // inconsistent across implementations.  By resetting our own position
    // to an unknown one, it ensures that a precise move occurs the next
    // time the cursor is moved to a position.
    state_.cursor_position_ = {};
}

// ==========================================================================
// OPERATOR<<(element)
// ==========================================================================
terminal &terminal::operator<<(terminalpp::element const &elem)
{
    *this << write_optional_default_attribute();
    return *this << write_element(elem);
}

// ==========================================================================
// OPERATOR<<(string)
// ==========================================================================
terminal &terminal::operator<<(terminalpp::string const &text)
{
    *this << write_optional_default_attribute();
    
    boost::for_each(
        text,
        [this](terminalpp::element const &elem)
        {
            *this << write_element(elem);
        });

    return *this;
}

// ==========================================================================
// OPERATOR>>(bytes)
// ==========================================================================
terminal &terminal::operator>>(terminalpp::bytes data)
{
    boost::for_each(
        data, 
        [this](terminalpp::byte datum)
        {
            auto const result = state_.input_parser_(datum);

            if (result)
            {
                terminalpp::token const well_known_results[] = {
                    detail::get_well_known_virtual_key(*result)
                };

                read_(well_known_results);
            }
        });
    
    return *this;
}

}
