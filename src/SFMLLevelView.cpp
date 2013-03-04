#include <iostream>
#include <math.h>
#include <list>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFMLLevelView.hpp"
#include "Level.hpp"
#include "SFMLBrickView.hpp"
#include "Dimension.hpp"

SFMLLevelView::SFMLLevelView(sf::RenderWindow& window, Level& level)
  :_window(window), _level(level) {
  Brick** grid = _level.GetGrid();
  int totalBricks = _level.GetTotalBricks();
  for(int i = 0; i < totalBricks; i++) {
    Brick* brick = grid[i];
    SFMLBrickView* view = new SFMLBrickView(_window, _level, *brick);
    _brickViews.push_back(view);
  }
}

void SFMLLevelView::Draw() {
  for(std::list<SFMLBrickView*>::iterator itr = _brickViews.begin(); itr != _brickViews.end(); ++itr) {
    (*itr)->Draw();
  }
}

int* SFMLLevelView::MapMouseToBrick(int mouseX, int mouseY) {
  Dimension* d =  _level.GetFeature<Dimension>();
  int x = d->GetX();
  int y = d->GetY();
  int width = d->GetWidth();
  int height = d->GetHeight();
  int row = floor(((mouseY - y) * 1.f / height) * Level::ROWS);
  int col = floor(((mouseX - x) * 1.f / width) * Level::BRICKS_PER_ROW);
  int* coords = new int[2];
  coords[0] = row;
  coords[1] = col;
  return coords;
}
