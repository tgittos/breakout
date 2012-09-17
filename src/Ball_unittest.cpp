#include "gtest/gtest.h"
#include "Ball.hpp"
#include "Dimension.hpp"
#include "Collidable.hpp"

TEST(BallTest, FeatureTest) {
  Ball b;
  ASSERT_TRUE(b.HasFeature<Collidable>());
  ASSERT_TRUE(b.HasFeature<Dimension>());
}

TEST(BallTest, WallReflection) {
  Ball b;

  // hit right wall going up - the right wall is a left
  // facing surface
  b.SetHeading(40.f);
  b.Reflect(Collidable::LEFT);
  ASSERT_EQ(320.f, b.GetHeading());

  // hit right wall going down
  b.SetHeading(150.f);
  b.Reflect(Collidable::LEFT);
  ASSERT_EQ(210.f, b.GetHeading());

  // hit left wall going down - the left wall is a right
  // facing surface
  b.SetHeading(210.f);
  b.Reflect(Collidable::RIGHT);
  ASSERT_EQ(150.f, b.GetHeading());

  // hit left wall going up
  b.SetHeading(300.f);
  b.Reflect(Collidable::RIGHT);
  ASSERT_EQ(60.f, b.GetHeading());
}

TEST(BallTest, PaddleReflection) {
  Ball b;

  // hit top of paddle going left - the baddle is a top
  // facing surface
  b.SetHeading(225.f);
  b.Reflect(Collidable::TOP);
  ASSERT_EQ(315.f, b.GetHeading());

  // hit top of padding going right
  b.SetHeading(130.f);
  b.Reflect(Collidable::TOP);
  ASSERT_EQ(50.f, b.GetHeading());
}

TEST(BallTest, BrickReflection){
  Ball b;

  // hit bottom
  b.SetHeading(40.f);
  b.Reflect(Collidable::BOTTOM);
  ASSERT_EQ(140.f, b.GetHeading());

  b.SetHeading(320.f);
  b.Reflect(Collidable::BOTTOM);
  ASSERT_EQ(220.f, b.GetHeading());

  // hit left side
  b.SetHeading(40.f);
  b.Reflect(Collidable::LEFT);
  ASSERT_EQ(320.f, b.GetHeading());

  b.SetHeading(135.f);
  b.Reflect(Collidable::LEFT);
  ASSERT_EQ(225.f, b.GetHeading());

  // hit right side
  b.SetHeading(315.0f);
  b.Reflect(Collidable::RIGHT);
  ASSERT_EQ(45.f, b.GetHeading());

  b.SetHeading(225.f);
  b.Reflect(Collidable::RIGHT);
  ASSERT_EQ(135.f, b.GetHeading());

  // hit top
  b.SetHeading(225.f);
  b.Reflect(Collidable::TOP);
  ASSERT_EQ(315.f, b.GetHeading());

  b.SetHeading(130.f);
  b.Reflect(Collidable::TOP);
  ASSERT_EQ(50.f, b.GetHeading());
}

TEST(BallTest, NoOscillation) {
  Ball b;
  b.SetHeading(90.f);
  b.Reflect(Collidable::LEFT);
  ASSERT_NE(270.f, b.GetHeading());
}

TEST(BallTest, IncreaseVelocity) {
  Ball b;
  ASSERT_EQ(230.f, b.GetSpeed());
  b.SpeedUp();
  ASSERT_EQ(250.f, b.GetSpeed());
}
