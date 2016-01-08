#include <terminalpp/events/default_event_context.hpp>
#include <terminalpp/event_context.hpp>
#include <gtest/gtest.h>

TEST(default_event_context_test, default_event_context_is_an_event_context)
{
    terminalpp::event_context ec{
        terminalpp::events::default_event_context{}};
}