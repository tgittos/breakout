#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFMLBrickView.hpp"
#include "Brick.hpp"
#include "Level.hpp"
#include "Dimension.hpp"

SFMLBrickView::SFMLBrickView(sf::RenderWindow& window, Level& level, Brick& brick):
  _window(window), _level(level), _brick(brick) {
}

void SFMLBrickView::Draw(){
  sf::Color c = GetColor();
  Dimension* bd = _brick.GetFeature<Dimension>();
  Dimension* ld = _level.GetFeature<Dimension>();
  sf::Shape rect = sf::Shape::Rectangle(
    bd->GetX() + ld->GetX(),
    bd->GetY() + ld->GetY(),
    bd->GetX() + bd->GetWidth() + ld->GetX(),
    bd->GetY() + bd->GetHeight() + ld->GetY(),
    c, true, sf::Color::Black
  );
  _window.Draw(rect);
}

sf::Color SFMLBrickView::GetColor(){
  int points = _brick.GetPoints();
  sf::Color c;
  switch(points) {
    case Brick::UNBREAKABLE:
      c = sf::Color::White;
      break;
    case Brick::ONE_POINT:
      c = sf::Color::Yellow;
      break;
    case Brick::THREE_POINTS:
      // orange
      c = sf::Color(255, 127, 0);
      break;
    case Brick::FIVE_POINTS:
      c = sf::Color::Green;
      break;
    case Brick::SEVEN_POINTS:
      c = sf::Color::Red;
      break;
  }
  return c;
}
