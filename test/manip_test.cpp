#include <terminalpp/ansi_terminal.hpp>
#include <terminalpp/terminal_manip.hpp>
#include <gtest/gtest.h>

using namespace terminalpp::literals;

TEST(a_terminal, can_have_a_terminal_string_streamed_to_it)
{
    terminalpp::ansi_terminal terminal;

    std::string const expected_result = "test";
    std::string const result = terminal << "test"_ets;

    ASSERT_EQ(expected_result, result);
}

TEST(a_terminal, can_have_an_attributed_terminal_string_streamed_to_it)
{
    terminalpp::ansi_terminal terminal;
    std::string const expected_result = "\x1B[31mtest";
    std::string const result = terminal << "\\[1test"_ets;

    ASSERT_EQ(expected_result, result);
}

TEST(a_terminal, can_have_a_cursor_move_streamed_to_it)
{
    terminalpp::ansi_terminal reference_terminal;
    std::string const expected_result = reference_terminal.move_cursor({5, 10});

    terminalpp::ansi_terminal terminal;
    std::string const result = terminal << terminalpp::move_cursor({5, 10});

    ASSERT_EQ(expected_result, result);
}

TEST(a_terminal, can_have_a_cursor_move_and_text_streamed_to_it)
{
    terminalpp::ansi_terminal reference_terminal;
    std::string expected_result = reference_terminal.move_cursor({10, 5});
    expected_result += reference_terminal.write("test"_ets);

    terminalpp::ansi_terminal terminal;
    std::string result =
        terminal << terminalpp::move_cursor({10, 5})
                 << "test"_ets;

    ASSERT_EQ(expected_result, result);
}

TEST(a_terminal, can_have_multiple_cursor_moves_and_texts_streamed_to_it)
{
    terminalpp::ansi_terminal reference_terminal;
    std::string expected_result = reference_terminal.move_cursor({10, 5});
    expected_result += reference_terminal.write("test"_ets);
    expected_result += reference_terminal.move_cursor({17,5});
    expected_result += reference_terminal.write("more"_ets);

    terminalpp::ansi_terminal terminal;
    std::string result =
        terminal << terminalpp::move_cursor({10, 5})
                 << "test"_ets
                 << terminalpp::move_cursor({17,5})
                 << "more"_ets;

    ASSERT_EQ(expected_result, result);
}

TEST(a_terminal, can_have_an_enable_mouse_command_streamed_to_it)
{
    terminalpp::behaviour behaviour;
    behaviour.supports_basic_mouse_tracking = true;

    terminalpp::ansi_terminal reference_terminal{behaviour};
    std::string const expected_result = reference_terminal.enable_mouse();

    terminalpp::ansi_terminal terminal{behaviour};
    std::string result = terminal << terminalpp::enable_mouse();

    ASSERT_EQ(expected_result, result);
}

TEST(a_terminal, can_have_a_disable_mouse_command_streamed_to_it)
{
    terminalpp::behaviour behaviour;
    behaviour.supports_basic_mouse_tracking = true;

    terminalpp::ansi_terminal reference_terminal{behaviour};
    reference_terminal.enable_mouse();
    std::string const expected_result = reference_terminal.disable_mouse();

    terminalpp::ansi_terminal terminal{behaviour};
    terminal.enable_mouse();
    std::string result = terminal << terminalpp::disable_mouse();

    ASSERT_EQ(expected_result, result);
}

TEST(a_terminal, can_have_a_window_title_streamed_to_it)
{
    terminalpp::behaviour behaviour;
    behaviour.supports_window_title_bel = true;

    terminalpp::ansi_terminal reference_terminal{behaviour};
    std::string const expected_result = reference_terminal.set_window_title("title");

    terminalpp::ansi_terminal terminal{behaviour};
    std::string result = terminal << terminalpp::set_window_title("title");

    ASSERT_EQ(expected_result, result);
}

TEST(a_terminal, can_have_a_show_cursor_command_streamed_to_it)
{
    terminalpp::ansi_terminal reference_terminal;
    reference_terminal.hide_cursor();
    std::string const expected_result = reference_terminal.show_cursor();

    terminalpp::ansi_terminal terminal;
    terminal.hide_cursor();
    std::string result = terminal << terminalpp::show_cursor();

    ASSERT_EQ(expected_result, result);
}

TEST(a_terminal, can_have_a_hide_cursor_command_streamed_to_it)
{
    terminalpp::ansi_terminal reference_terminal;
    reference_terminal.show_cursor();
    std::string const expected_result = reference_terminal.hide_cursor();

    terminalpp::ansi_terminal terminal;
    terminal.show_cursor();
    std::string result = terminal << terminalpp::hide_cursor();

    ASSERT_EQ(expected_result, result);
}
