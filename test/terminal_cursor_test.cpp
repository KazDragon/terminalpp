#include "terminal_test.hpp"
#include "expect_sequence.hpp"
#include <terminalpp/terminal.hpp>
#include <gtest/gtest.h>

using namespace terminalpp::literals;
using testing::ValuesIn;

namespace {

using unknown_location_move_data = std::tuple<
    terminalpp::point,       // Position to move to
    terminalpp::byte_storage // Expected ANSI-encoded result
>;

class a_terminal_with_an_unknown_location
  : public testing::TestWithParam<unknown_location_move_data>,
    public terminal_test_base
{
public:
    a_terminal_with_an_unknown_location()
    {
        terminal_.set_size({10, 10});
    }
};

}

TEST_P(a_terminal_with_an_unknown_location, sends_bytes_when_moving_the_cursor)
{
    using std::get;

    auto const &param = GetParam();
    auto const &destination     = get<0>(param);
    auto const &expected_result = get<1>(param);

    terminal_.write(discard_result) << ""_ets;
    terminal_.write(append_to_result) << terminalpp::move_cursor(destination);

    expect_sequence(expected_result, result_);
}

static unknown_location_move_data const unknown_location_move_data_table[] = {
    unknown_location_move_data{ {0, 0}, "\x1B[H"_tb },
    unknown_location_move_data{ {0, 4}, "\x1B[5H"_tb },
    unknown_location_move_data{ {2, 0}, "\x1B[1;3H"_tb },
    unknown_location_move_data{ {2, 4}, "\x1B[5;3H"_tb },
};

INSTANTIATE_TEST_SUITE_P(
    moving_the_cursor_sends_ansi_bytes,
    a_terminal_with_an_unknown_location,
    ValuesIn(unknown_location_move_data_table)
);
