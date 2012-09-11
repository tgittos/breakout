#include "gtest/gtest.h"
#include "Brick.hpp"

TEST(BrickTest, FeatureTest) {
  ASSERT_FALSE(true);
}

TEST(BrickTest, BrickHasScore) {
  Brick b = Brick(Brick::FIVE_POINTS);
  ASSERT_EQ(5, b.GetPoints());
}

TEST(BrickTest, UnbreakableBrickHasNoScore) {
  Brick b = Brick(Brick::UNBREAKABLE);
  ASSERT_EQ(0, b.GetPoints());
}

TEST(BrickTest, UnbreakableIsTrue) {
  Brick b = Brick(Brick::UNBREAKABLE);
  ASSERT_TRUE(b.IsUnbreakable());
}

TEST(BrickTest, UnbreakableIsFalse) {
  Brick b = Brick(Brick::FIVE_POINTS);
  ASSERT_FALSE(b.IsUnbreakable());
}
