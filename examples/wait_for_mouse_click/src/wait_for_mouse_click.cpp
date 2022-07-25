#include <consolepp/console.hpp>
#include <terminalpp/terminal.hpp>
#include <terminalpp/mouse.hpp>
#include <boost/asio.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <fmt/format.h>
#include <variant>

struct console_channel
{
    console_channel(consolepp::console &console)
      : console_{console}
    {
    }

    void async_read(std::function<void (terminalpp::bytes)> const &callback) {
        console_.async_read(callback);
    }

    void write(terminalpp::bytes data) 
    {
        console_.write(data);
    }
    void close(){}
    bool is_alive() const { return true; }

    consolepp::console &console_;
};

static void schedule_async_read();

static boost::asio::io_context io_context;
static auto work_guard = boost::asio::make_work_guard(io_context);

static consolepp::console console{io_context};
static console_channel channel{console};

static terminalpp::terminal terminal{
    channel,
    [] {
        terminalpp::behaviour behaviour;
        behaviour.supports_basic_mouse_tracking = true;
        return behaviour;
    }()
};

static terminalpp::point mouse_position;

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

template <typename... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <typename... Ts> overloaded(Ts...) -> overloaded<Ts...>;

static void schedule_async_read()
{
    terminal.async_read(
        [](terminalpp::tokens tokens) {
            for (auto const &token : tokens) {
                std::visit(overloaded{
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
                    }},
                    token);
            }
            
            schedule_async_read();
        });
}
