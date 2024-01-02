#include "terminal_test.hpp"

TEST_F(a_terminal, is_alive_if_its_underlying_channel_is_alive)
{
  ASSERT_TRUE(terminal_.is_alive());

  channel_.close();
  ASSERT_FALSE(terminal_.is_alive());
}

TEST_F(a_terminal, closes_its_underlying_channel_if_it_is_closed)
{
  ASSERT_TRUE(channel_.is_alive());
  terminal_.close();
  ASSERT_FALSE(channel_.is_alive());
}
