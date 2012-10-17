#ifndef SFML_BRICK_VIEW_H
#define SFML_BRICK_VIEW_H

#include "SFMLView.hpp"

namespace sf {
  class RenderWindow;
};
class Brick;
class Level;

class SFMLBrickView : public SFMLView {
  public:
  SFMLBrickView(sf::RenderWindow& window, Level& level, Brick& brick);
  ~SFMLBrickView(){};

  void Draw();

  private:
  sf::RenderWindow& _window;
  Brick& _brick;
  Level& _level;

  sf::Color GetColor();
};

#endif
