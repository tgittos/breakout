#include <list>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFMLLevelView.hpp"
#include "Level.hpp"
#include "SFMLBrickView.hpp"

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
