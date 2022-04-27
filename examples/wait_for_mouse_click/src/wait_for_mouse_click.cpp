#include <consolepp/console.hpp>
#include <terminalpp/terminal.hpp>
#include <terminalpp/mouse.hpp>
#include <terminalpp/detail/lambda_visitor.hpp>
#include <boost/asio.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <fmt/format.h>

static void handle_token(terminalpp::token const &token);
static void schedule_async_read();

static boost::asio::io_context io_context;
static auto work_guard = boost::asio::make_work_guard(io_context);

static consolepp::console console{io_context};
static terminalpp::point mouse_position;

terminalpp::terminal terminal{
    [](terminalpp::tokens tokens) {
        boost::for_each(tokens, handle_token);
    },
    [](terminalpp::bytes data) {
        console.write(data);
    },
    [] {
        terminalpp::behaviour behaviour;
        behaviour.supports_basic_mouse_tracking = true;
        return behaviour;
    }()
};

static void wait_for_mouse_click()
{
    schedule_async_read();
    io_context.run();
}

int main()
{
    terminal << terminalpp::save_cursor_position()
             << terminalpp::use_alternate_screen_buffer()
             << terminalpp::enable_mouse()
             << terminalpp::erase_display()
             << terminalpp::move_cursor({0, 0})
             << "Click with a mouse button to exit!\n";
        
    wait_for_mouse_click();

    terminal << terminalpp::disable_mouse()
             << terminalpp::use_normal_screen_buffer()
             << terminalpp::restore_cursor_position()
             << fmt::format("mouse clicked at ({},{})\n", mouse_position.x_, mouse_position.y_);
}

static void handle_token(terminalpp::token const &token)
{
    boost::apply_visitor(terminalpp::detail::make_lambda_visitor(
        [](terminalpp::mouse::event const &mouse)
        {
            if (mouse.action_ == terminalpp::mouse::event_type::left_button_down)
            {
                mouse_position = mouse.position_;
                io_context.stop();
            }
        },
        [](auto &&)
        {
        }),
        token);
}

static void schedule_async_read()
{
    console.async_read(
        [](consolepp::bytes data)
        {
            terminal >> data;
            schedule_async_read();
        });
}
