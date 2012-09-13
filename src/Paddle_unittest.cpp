#include "gtest/gtest.h"
#include "Paddle.hpp"
#include "Dimension.hpp"
#include "Collidable.hpp"

TEST(PaddleTest, MoveLeftNegativeAcceleration) {
  Paddle p = Paddle();
  ASSERT_EQ(0.f, p.GetVelocity());
  p.MoveLeft(1);
  ASSERT_TRUE(p.GetVelocity() < 0);
}

TEST(PaddleTest, MoveRightPositiveAcceleration) {
  Paddle p = Paddle();
  ASSERT_EQ(0.f, p.GetVelocity());
  p.MoveRight(1.f);
  ASSERT_TRUE(p.GetVelocity() > 0);
}

TEST(PaddleTest, AccelerationOfPaddle) {
  float desiredAcceleration = 4.f;
  float timestep = 0.01f;
  Paddle p = Paddle();
  p.MoveRight(timestep);
  ASSERT_EQ(timestep * desiredAcceleration, p.GetVelocity());
}

TEST(PaddleTest, DecelerationOfPaddle) {
  float desiredDeceleration = 2.f;
  float timestep = 0.01f;
  Paddle p = Paddle();
  p.MoveRight(1.f);
  float acceleration = p.GetVelocity();
  p.Idle(timestep);
  ASSERT_EQ(acceleration - (timestep * desiredDeceleration), p.GetVelocity());
}

TEST(PaddleTest, InstantaneousDirectionChange) {
  float acceleration = 4.f;
  Paddle p = Paddle();
  p.MoveRight(1.f);
  ASSERT_EQ(acceleration, p.GetVelocity());
  p.MoveLeft(1.f);
  ASSERT_EQ(-acceleration, p.GetVelocity());
}

TEST(PaddleTest, FeatureTest) {
  Paddle p;
  ASSERT_TRUE(p.HasFeature<Dimension>());
  ASSERT_TRUE(p.HasFeature<Collidable>());
}
