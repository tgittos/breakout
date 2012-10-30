#include "SFMLButtonView.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Button.hpp"
#include "Dimension.hpp"
#include "Clickable.hpp"

SFMLButtonView::SFMLButtonView(sf::RenderWindow& window, Button& button):
  _window(window), _button(button) {
  _font = new sf::Font();
  _font->LoadFromFile("assets/visitor.ttf");
}

void SFMLButtonView::Draw() {
  Dimension* d = _button.GetFeature<Dimension>();
  sf::Shape rect = sf::Shape::Rectangle(
    d->GetX(),
    d->GetY(),
    d->GetX() + d->GetWidth(),
    d->GetY() + d->GetHeight(),
    sf::Color::Black, true, sf::Color::Black
  );
  sf::String l(_button.GetLabel(), *_font);
  l.SetX(d->GetX() + 10);
  l.SetY(d->GetY() + 10);

  _window.Draw(rect);
  _window.Draw(l);
}

void SFMLButtonView::Click() {
  _button.GetFeature<Clickable>()->Click();
}
