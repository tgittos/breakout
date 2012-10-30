#include "Button.hpp"
#include "Dimension.hpp"
#include "Clickable.hpp"

Button::Button(std::string label):
  _label(label) {
  Dimension* d = new Dimension();
  d->SetWidth(100);
  d->SetHeight(50);
  AddFeature(d);
  AddFeature(new Clickable(NAMESPACE + "::" + _label));
}

std::string Button::GetEventString() {
  return GetFeature<Clickable>()->GetEventString();
}

std::string Button::GetLabel() {
  return _label;
}

std::string Button::NAMESPACE = "button";
