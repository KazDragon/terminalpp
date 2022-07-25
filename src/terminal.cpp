#include "terminalpp/terminal.hpp"
#include "terminalpp/detail/well_known_virtual_key.hpp"

namespace terminalpp {

// ==========================================================================
// DESTRUCTOR
// ==========================================================================
terminal::~terminal() = default;

// ==========================================================================
// ASYNC_READ
// ==========================================================================
void terminal::async_read(std::function<void (tokens)> const &callback)
{
    channel_->async_read(
        [=](terminalpp::bytes data)
        {
            std::vector<token> results;

            boost::for_each(
                data,
                [this, &results](terminalpp::byte datum)
                {
                    if (auto const result = state_.input_parser_(datum);
                        result.has_value())
                    {
                        results.push_back(
                            detail::get_well_known_virtual_key(*result));
                    }
                });

            callback(results);
        });
}

// ==========================================================================
// WRITE
// ==========================================================================
void terminal::write(bytes data)
{
    channel_->write(data);
}

// ==========================================================================
// IS_ALIVE
// ==========================================================================
bool terminal::is_alive() const
{
    return channel_->is_alive();
}

// ==========================================================================
// CLOSE
// ==========================================================================
void terminal::close()
{
    channel_->close();
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

}
