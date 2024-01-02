#include "expect_sequence.hpp"
#include "terminal_test.hpp"
#include <gtest/gtest.h>
#include <terminalpp/terminal.hpp>

using namespace terminalpp::literals;  // NOLINT
using testing::ValuesIn;

namespace {

using unknown_location_move_data = std::tuple<
    terminalpp::point,        // Position to move to
    terminalpp::byte_storage  // Expected ANSI-encoded result
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

}  // namespace

TEST_P(a_terminal_with_an_unknown_location, sends_bytes_when_moving_the_cursor)
{
  using std::get;

  auto const &param = GetParam();
  auto const &destination = get<0>(param);
  auto const &expected_result = get<1>(param);

  terminal_ << terminalpp::move_cursor(destination);

  expect_sequence(expected_result, channel_.written_);
}

static unknown_location_move_data const unknown_location_move_data_table[] = {
    unknown_location_move_data{{0, 0}, "\x1B[H"_tb},
    unknown_location_move_data{{0, 4}, "\x1B[5H"_tb},
    unknown_location_move_data{{2, 0}, "\x1B[1;3H"_tb},
    unknown_location_move_data{{2, 4}, "\x1B[5;3H"_tb},
};

INSTANTIATE_TEST_SUITE_P(
    moving_the_cursor_sends_ansi_bytes,
    a_terminal_with_an_unknown_location,
    ValuesIn(unknown_location_move_data_table));

namespace {

using known_location_move_data = std::tuple<
    terminalpp::point,        // Position to move from
    terminalpp::point,        // Position to move to
    terminalpp::byte_storage  // Expected ANSI-encoded result
    >;

class a_terminal_with_a_known_location
  : public testing::TestWithParam<known_location_move_data>,
    public terminal_test_base
{
 public:
  a_terminal_with_a_known_location()
  {
    terminal_.set_size({30, 30});
  }
};

}  // namespace

TEST_P(a_terminal_with_a_known_location, sends_bytes_when_moving_the_cursor)
{
  using std::get;

  auto const &param = GetParam();
  auto const &source = get<0>(param);
  auto const &destination = get<1>(param);
  auto const &expected_result = get<2>(param);

  terminal_ << terminalpp::move_cursor(source);
  channel_.written_.clear();

  terminal_ << terminalpp::move_cursor(destination);

  expect_sequence(expected_result, channel_.written_);
}

static known_location_move_data const known_location_move_data_table[] = {
    // Moving to the current location sends nothing.
    known_location_move_data{{0, 0}, {0, 0}, ""_tb},
    known_location_move_data{{7, 6}, {7, 6}, ""_tb},

    // Moving to the home location sends cursor position = home
    known_location_move_data{{10, 10}, {0, 0}, "\x1B[H"_tb},

    // Moving in the current row sends cursor horizontal absolute
    known_location_move_data{{10, 10}, {0, 10}, "\x1B[G"_tb},
    known_location_move_data{{20, 10}, {8, 10}, "\x1B[9G"_tb},
    known_location_move_data{{8, 10}, {20, 10}, "\x1B[21G"_tb},

    // Moving up in rows sends cursor up
    known_location_move_data{{10, 10}, {10, 9}, "\x1B[A"_tb},
    known_location_move_data{{10, 10}, {10, 8}, "\x1B[2A"_tb},

    // Moving down in rows sends cursor down
    known_location_move_data{{10, 10}, {10, 11}, "\x1B[B"_tb},
    known_location_move_data{{10, 10}, {10, 12}, "\x1B[2B"_tb},

    // Moving in any kind of diagonal way reverts to using cursor position
    known_location_move_data{{10, 10}, {5, 6}, "\x1B[7;6H"_tb},
};

INSTANTIATE_TEST_SUITE_P(
    moving_the_cursor_sends_ansi_bytes,
    a_terminal_with_a_known_location,
    ValuesIn(known_location_move_data_table));

TEST_F(a_terminal, when_hiding_the_cursor_sends_ansi_codes)
{
  terminal_ << terminalpp::hide_cursor();
  expect_sequence("\x1B[?25l"_tb, channel_.written_);
}

TEST_F(a_terminal, when_showing_the_cursor_sends_ansi_codes)
{
  terminal_ << terminalpp::show_cursor();
  expect_sequence("\x1B[?25h"_tb, channel_.written_);
}

namespace {

class a_terminal_with_a_shown_cursor : public a_terminal
{
 public:
  a_terminal_with_a_shown_cursor()
  {
    terminal_ << terminalpp::show_cursor();
    channel_.written_.clear();
  }
};

}  // namespace

TEST_F(a_terminal_with_a_shown_cursor, when_hiding_the_cursor_sends_ansi_codes)
{
  terminal_ << terminalpp::hide_cursor();
  expect_sequence("\x1B[?25l"_tb, channel_.written_);
}

TEST_F(a_terminal_with_a_shown_cursor, when_showing_the_cursor_sends_nothing)
{
  terminal_ << terminalpp::show_cursor();
  expect_sequence(""_tb, channel_.written_);
}

namespace {

class a_terminal_with_a_hidden_cursor : public a_terminal
{
 public:
  a_terminal_with_a_hidden_cursor()
  {
    terminal_ << terminalpp::hide_cursor();
    channel_.written_.clear();
  }
};

}  // namespace

TEST_F(a_terminal_with_a_hidden_cursor, when_hiding_the_cursor_sends_nothing)
{
  terminal_ << terminalpp::hide_cursor();
  expect_sequence(""_tb, channel_.written_);
}

TEST_F(
    a_terminal_with_a_hidden_cursor, when_showing_the_cursor_sends_ansi_codes)
{
  terminal_ << terminalpp::show_cursor();
  expect_sequence("\x1B[?25h"_tb, channel_.written_);
}

TEST_F(a_terminal, when_saving_the_cursor_sends_ansi_codes)
{
  terminal_ << terminalpp::save_cursor_position();
  expect_sequence("\x1B[s"_tb, channel_.written_);
}

TEST_F(a_terminal, when_restoring_the_cursor_sends_ansi_codes)
{
  terminal_ << terminalpp::restore_cursor_position();
  expect_sequence("\x1B[u"_tb, channel_.written_);
}

TEST_F(
    a_terminal,
    when_restoring_the_cursor_to_a_known_location_remembers_that_location)
{
  terminal_.set_size({30, 30});
  terminal_ << terminalpp::move_cursor({10, 10})
            << terminalpp::save_cursor_position()
            << terminalpp::move_cursor({0, 0}) << "?"
            << terminalpp::restore_cursor_position();
  channel_.written_.clear();

  terminal_ << terminalpp::move_cursor({10, 10}) << "x";

  expect_sequence("x"_tb, channel_.written_);
}

TEST_F(a_terminal, has_an_unknown_cursor_location_when_the_size_is_changed)
{
  terminal_.set_size({10, 10});
  terminal_ << terminalpp::move_cursor({8, 8}) << "a";
  channel_.written_.clear();

  terminal_.set_size({11, 11});
  terminal_ << terminalpp::move_cursor({9, 8}) << "b";

  expect_sequence("\x1B[9;10Hb"_tb, channel_.written_);
}

TEST_F(
    a_terminal,
    has_an_unknown_cursor_location_when_writing_the_last_character_in_a_line)
{
  terminal_.set_size({10, 10});
  terminal_ << terminalpp::move_cursor({9, 0}) << "a";
  channel_.written_.clear();

  terminal_ << terminalpp::move_cursor({0, 1}) << "b";

  expect_sequence("\x1B[2Hb"_tb, channel_.written_);
}
