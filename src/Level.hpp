#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "Brick.hpp"
#include "ComposableObject.hpp"
#include "Collidable.hpp"


class Level : public ComposableObject{
  public:
  static const int BRICKS_PER_ROW = 15;
  static const int ROWS = 8;

  Level();
  ~Level();

  int GetTotalBricks();

  Brick** GetGrid();

  Collidable::IntersectionSurface Intersect(int x, int y);

  void LoadFromFile(const char* path);
  void SaveToFile(const char* path);

  void AddBrick(int row, int col, Brick* newBrick);
  void DeleteBrick(int row, int col);
  void ChangeBrick(int row, int col, Brick::BrickType newType);

  private:
  Brick* _grid[ROWS * BRICKS_PER_ROW];
  int _totalBricks;

  std::vector<std::string> ReadFile(const char* path);
  void WriteFile(const char* path, std::string content);
  void Split(std::vector<std::string>& returnVector, const std::string& string, std::string& delimiter);
};

#endif
