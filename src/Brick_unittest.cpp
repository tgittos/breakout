#include "gtest/gtest.h"
#include "Brick.hpp"
#include "Dimension.hpp"
#include "Collidable.hpp"

TEST(BrickTest, FeatureTest) {
  Brick b = Brick(Brick::UNBREAKABLE);
  ASSERT_TRUE(b.HasFeature<Dimension>());
  ASSERT_TRUE(b.HasFeature<Collidable>());
}

TEST(BrickTest, WidthHeightSet) {
  Brick b = Brick(Brick::UNBREAKABLE);
  ASSERT_EQ(Brick::BRICK_WIDTH, b.GetFeature<Dimension>()->GetWidth());
  ASSERT_EQ(Brick::BRICK_HEIGHT, b.GetFeature<Dimension>()->GetHeight());
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
