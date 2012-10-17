#ifndef SFML_LEVEL_VIEW_H
#define SFML_LEVEL_VIEW_H

#include "SFMLView.hpp"

namespace sf {
  class RenderWindow;
};
class Level;
class SFMLBrickView;

class SFMLLevelView : public SFMLView {
  public:
  SFMLLevelView(sf::RenderWindow& window, Level& level);
  ~SFMLLevelView(){};

  virtual void Draw();

  private:
  sf::RenderWindow& _window;
  Level& _level;
  std::list<SFMLBrickView*> _brickViews;
};

#endif
