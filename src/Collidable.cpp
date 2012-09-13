#include <assert.h>
#include "Collidable.hpp"
#include "Dimension.hpp"

Collidable::Collidable(ComposableObject* owner):
  _owner(owner) {
  if (!_owner->HasFeature<Dimension>()) {
    Dimension* dimension = new Dimension();
    _owner->AddFeature(dimension);
  }
}

bool Collidable::Intersects(float x, float y) {
  Dimension* d = _owner->GetFeature<Dimension>();
  assert(NULL != d);
  return d->GetX() - d->GetWidth() / 2 <= x &&
         d->GetX() + d->GetWidth() / 2 >= x &&
         d->GetY() - d->GetHeight() / 2 <= y &&
         d->GetY() + d->GetHeight() / 2 >= y;
}
