#ifndef SFML_BUTTON_VIEW_H
#define SFML_BUTTON_VIEW_H

#include "SFMLView.hpp"

namespace sf {
  class RenderWindow;
  class Font;
};
class Button;

class SFMLButtonView : public SFMLView {
  public:
  SFMLButtonView(sf::RenderWindow& window, Button& button);
  ~SFMLButtonView(){};

  void Draw();
  void Click();

  private:
  sf::RenderWindow& _window;
  Button& _button;
  sf::Font* _font;
};

#endif
