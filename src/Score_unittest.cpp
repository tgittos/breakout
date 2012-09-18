#include "gtest/gtest.h"
#include "Score.hpp"


TEST(ScoreTest, ValidInitialization) {
  Score s;
  ASSERT_EQ(0, s.GetScore());
}

TEST(ScoreTest, ListensForBrickHitEvents) {
  Score s;
  s.Increment(Brick::FIVE_POINTS);
  ASSERT_EQ(5, s.GetScore());
}
