#include "Brick.hpp"
#include "Dimension.hpp"
#include "Collidable.hpp"

const int Brick::BRICK_WIDTH;
const int Brick::BRICK_HEIGHT;

Brick::Brick(BrickType type):
  _type(type) {
  Dimension* d = new Dimension();
  d->SetWidth(Brick::BRICK_WIDTH);
  d->SetHeight(Brick::BRICK_HEIGHT);

  AddFeature(d);
  AddFeature(new Collidable(this));
};

int Brick::GetPoints() {
  return (int)_type;
}

bool Brick::IsUnbreakable() {
  return _type == Brick::UNBREAKABLE;
}
