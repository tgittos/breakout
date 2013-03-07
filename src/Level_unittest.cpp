#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MockLevel.hpp"
#include "Brick.hpp"
#include "Collidable.hpp"
#include "Dimension.hpp"

TEST(LevelTest, NewLevelHasGrid) {
  Level l;
  ASSERT_EQ(Level::ROWS * Level::BRICKS_PER_ROW, l.GetTotalBricks());
  Brick** grid = l.GetGrid();
  int totalBricks = l.GetTotalBricks();
  for(int i = 0; i < totalBricks; i++) {
    ASSERT_EQ(NULL, grid[i]);
  }
}

TEST(LevelTest, IntersectReturnCorrectSide) {
  Level l;
  l.LoadFromFile("test/fixtures/level.txt");
  int x = l.GetFeature<Dimension>()->GetY() + Brick::BRICK_HEIGHT * (Level::ROWS - 1);
  int y = l.GetFeature<Dimension>()->GetX() + 200;
  ASSERT_EQ(Collidable::BOTTOM, l.Intersect(x, y));
}

TEST(LevelTest, IntersectionReturnsNoSide) {
  Level l;
  l.LoadFromFile("test/fixtures/level.txt");
  int x = l.GetFeature<Dimension>()->GetY() + Brick::BRICK_HEIGHT * (Level::ROWS - 1) + 600;
  int y = 0;
  ASSERT_EQ(Collidable::NONE, l.Intersect(x, y));
}

TEST(LevelTest, BrickRemovedWhenHit) {
    Level l;
  l.LoadFromFile("test/fixtures/level.txt");
  int x = Brick::BRICK_WIDTH / 2;
  int y = 0;
  l.Intersect(x, y);
  Brick** grid = l.GetGrid();
  ASSERT_TRUE(NULL == grid[0]);
}

TEST(LevelTest, BrickNotRemovedWhenNoHit) {
    Level l;
  l.LoadFromFile("test/fixtures/level.txt");
  int x = l.GetFeature<Dimension>()->GetY() + Brick::BRICK_HEIGHT * Level::ROWS + 100;
  int y = 0;
  l.Intersect(x, y);
  Brick** grid = l.GetGrid();
  ASSERT_TRUE(NULL != grid[0]);
}

TEST(LevelTest, LoadLevelHasBricks) {
  Level l;
  l.LoadFromFile("test/fixtures/level.txt");
  Brick** grid = l.GetGrid();
  for(int i = 0; i < l.GetTotalBricks(); i++) {
    //int y = (int)floor(i * 1.f / Level::BRICKS_PER_ROW);
    //int x = i % Level::BRICKS_PER_ROW;
    Brick* brick = grid[i];
    ASSERT_TRUE(NULL != brick);
    ASSERT_EQ(3, brick->GetPoints());
  }
}

TEST(LevelTest, LoadLevelGivesBricksCorrectXY) {
  Level l;
  l.LoadFromFile("test/fixtures/level.txt");
  Brick** grid = l.GetGrid();
  for(int i = 0; i < l.GetTotalBricks(); i++) {
    int row = (int)floor(i * 1.f / Level::BRICKS_PER_ROW);
    int col = i % Level::BRICKS_PER_ROW;
    int brickX = col * Brick::BRICK_WIDTH;
    int brickY = row * Brick::BRICK_HEIGHT;
    Brick* brick = grid[i];
    Dimension* d = brick->GetFeature<Dimension>();
    ASSERT_EQ(brickX, d->GetX());
    ASSERT_EQ(brickY, d->GetY());
  }
}

TEST(LevelTest, SaveLevelWritesFile) {
  Level l;
  Brick** grid = l.GetGrid();
  for(int i = 0; i < l.GetTotalBricks(); i++) {
    Brick b(Brick::FIVE_POINTS);
    grid[i] = &b;
  }
  l.SaveToFile("test/fixtures/unittestlevel.txt");
  std::ifstream fileStream("test/fixtures/unittestlevel.txt");
  ASSERT_TRUE(NULL != fileStream);
  fileStream.close();
  std::remove("test/fixtures/unittestlevel.txt");
}

TEST(LevelTest, LoadSavedFile) {
  Level l;
  Brick** grid = l.GetGrid();
  for(int i = 0; i < l.GetTotalBricks(); i++) {
    Brick b(Brick::FIVE_POINTS);
    grid[i] = &b;
  }
  l.SaveToFile("test/fixtures/unittestlevel.txt");

  l = Level();
  l.LoadFromFile("test/fixtures/unittestlevel.txt");
  grid = l.GetGrid();
  for(int i = 0; i < l.GetTotalBricks(); i++) {
    Brick* brick = grid[i];
    ASSERT_TRUE(NULL != brick);
    ASSERT_EQ(5, brick->GetPoints());
  }
  std::remove("test/fixtures/unittestlevel.txt");
}

TEST(LevelTest, CanAddBrickToGrid) {
  Level l;
  l.AddBrick(3, 10, new Brick(Brick::THREE_POINTS));
  Brick** grid = l.GetGrid();
  Brick* b = grid[3 * Level::BRICKS_PER_ROW + 10];
  ASSERT_TRUE(NULL != b);
  ASSERT_EQ(3, b->GetPoints());
}

TEST(LevelTest, CanDeleteBrickFromGrid) {
  Level l;
  l.LoadFromFile("test/fixtures/level.txt");
  Brick** grid = l.GetGrid();
  ASSERT_EQ(3, grid[0]->GetPoints());
  l.DeleteBrick(0, 0);
  ASSERT_EQ(NULL, grid[0]);
}

TEST(LevelTest, CanChangeBrickType) {
  Level l;
  l.LoadFromFile("test/fixtures/level.txt");
  Brick** grid = l.GetGrid();
  ASSERT_EQ(3, grid[0]->GetPoints());
  l.ChangeBrick(0, 0, Brick::SEVEN_POINTS);
  ASSERT_EQ(7, grid[0]->GetPoints());
}
