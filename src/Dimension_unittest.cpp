#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MockDimension.hpp"

TEST(DimensionTest, SetXPos) {
  Dimension d;
  d.SetX(100.f);
}

TEST(DimensionTest, SetYPos) {
  Dimension d;
  d.SetY(100.f);
}

TEST(DimensionTest, GetXPos) {
  Dimension d;
  d.SetX(100.f);
  ASSERT_EQ(100.f, d.GetX());
}

TEST(DimensionTest, GetYPos) {
  Dimension d;
  d.SetY(100.f);
  ASSERT_EQ(100.f, d.GetY());
}

TEST(DimensionTest, SetWidth) {
  Dimension d;
  d.SetWidth(50.f);
}

TEST(DimensionTest, SetHeight) {
  Dimension d;
  d.SetHeight(50.f);
}

TEST(DimensionTest, GetWidth) {
  Dimension d;
  d.SetWidth(50.f);
  ASSERT_EQ(50.f, d.GetWidth());
}

TEST(DimensionTest, GetHeight) {
  Dimension d;
  d.SetHeight(50.f);
  ASSERT_EQ(50.f, d.GetHeight());
}
