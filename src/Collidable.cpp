#include <assert.h>
#include <algorithm>
#include "Collidable.hpp"
#include "Dimension.hpp"

Collidable::Collidable(ComposableObject* owner):
  _owner(owner) {
  if (!_owner->HasFeature<Dimension>()) {
    Dimension* dimension = new Dimension();
    _owner->AddFeature(dimension);
  }
}

Collidable::IntersectionSurface Collidable::Intersects(float x, float y) {
  IntersectionSurface surface = Collidable::NONE;
  Dimension* d = _owner->GetFeature<Dimension>();
  assert(NULL != d);
  bool intersected = (x >= d->GetX() && x <= d->GetX() + d->GetWidth()) &&
                     (y >= d->GetY() && y <= d->GetY() + d->GetHeight());
  if (intersected) {
    // assumes x, y position is top left
    float deltaTop = abs(d->GetY() - y);
    float deltaBottom = abs(d->GetY() + d->GetHeight() - y);
    float deltaLeft = abs(d->GetX() - x);
    float deltaRight = abs(d->GetX() + d->GetWidth() - x);
    float min = std::min(std::min(deltaTop, deltaBottom),std::min(deltaLeft, deltaRight));
    if (min == deltaTop) {
      surface = Collidable::TOP;
    } else if (min == deltaBottom) {
      surface = Collidable::BOTTOM;
    } else if (min == deltaLeft) {
      surface = Collidable::LEFT;
    } else if (min == deltaRight) {
      surface = Collidable::RIGHT;
    }
  }
  return surface;
}
