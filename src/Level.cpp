#include <iostream>
#include <sstream>
#include <fstream>
#include "Level.hpp"
#include "Dimension.hpp"
#include "Collidable.hpp"

Level::Level():
  _totalBricks(0) {
  for(int i = 0; i < ROWS * BRICKS_PER_ROW; i++) {
    _grid[i] = NULL;
    _totalBricks++;
  }
  Dimension * d = new Dimension();
  d->SetWidth(BRICKS_PER_ROW * Brick::BRICK_WIDTH);
  d->SetHeight(_totalBricks / BRICKS_PER_ROW * Brick::BRICK_HEIGHT);
  AddFeature(d);
}

Level::~Level() {

}

Collidable::IntersectionSurface Level::Intersect(int x, int y) {
  Dimension* d = GetFeature<Dimension>();
  int realX = x - d->GetX();
  int realY = y - d->GetY();
  for(int i = 0; i < _totalBricks; i++) {
    Brick* b = _grid[i];
    Collidable::IntersectionSurface s = b->GetFeature<Collidable>()->Intersects(realX, realY);
    if (Collidable::NONE != s) {
      delete b;
      _grid[i] = NULL;
      return s;
    }
  }
  return Collidable::NONE;
}

void Level::LoadFromFile(const char* path) {
  std::vector<std::string> level = ReadFile(path);
  for (size_t i = 0; i < level.size(); i++) {
    std::vector<std::string> bricks;
    std::string lineDelimiter(",");
    Split(bricks, level[i], lineDelimiter);
    for (size_t j = 0; j < bricks.size(); j++) {
      int brickValue;
      std::stringstream conversionStream(bricks[j]);
      conversionStream >> brickValue;
      Brick* b = new Brick((Brick::BrickType)brickValue);
      b->GetFeature<Dimension>()->SetX(j * Brick::BRICK_WIDTH);
      b->GetFeature<Dimension>()->SetY(i * Brick::BRICK_HEIGHT);
      _grid[i * BRICKS_PER_ROW + j] = b;
    }
  }
}

void Level::SaveToFile(const char* path) {
  std::string levelString;
  std::stringstream ss;
  for (int i = 1; i <= _totalBricks; i++) {
    ss.str("");
    ss << _grid[i-1]->GetPoints();
    levelString += ss.str();
    if (i != _totalBricks) {
      if (0 == i % BRICKS_PER_ROW) {
        levelString += "\n";
      } else {
        levelString += ",";
      }
    }
  }
  WriteFile(path, levelString);
}

void Level::AddBrick(int row, int col, Brick* newBrick) {
  _grid[row * BRICKS_PER_ROW + col] = newBrick;
}

void Level::ChangeBrick(int row, int col, Brick::BrickType newType) {
  _grid[row * BRICKS_PER_ROW + col]->ChangeType(newType);
}

Brick** Level::GetGrid() {
  return _grid;
}

int Level::GetTotalBricks() {
  return _totalBricks;
}

std::vector<std::string> Level::ReadFile(const char* path) {
  std::vector<std::string> strings;
  std::ifstream fileStream(path);
  if (fileStream.is_open()){
    while (fileStream.good()) {
      std::string theString;
      std::getline(fileStream, theString);
      strings.push_back(theString);
    }
    fileStream.close();
  }
  return strings;
}

void Level::WriteFile(const char* path, std::string content) {
  std::ofstream fileStream(path);
  if (fileStream.is_open()) {
    fileStream << content;
    fileStream.close();
  }
}

void Level::Split(std::vector<std::string>& returnVector, const std::string& theString, std::string& delimiter) {
  size_t start = 0, end = 0;
  while(end != std::string::npos) {
    end = theString.find(delimiter, start);
    returnVector.push_back(theString.substr(start, (end == std::string::npos) ? std::string::npos : end - start));
    start = ((end > (std::string::npos - delimiter.size())) ? std::string::npos : end + delimiter.size());
  }
}
