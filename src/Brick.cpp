#include "Brick.hpp"
#include "Dimension.hpp"
#include "Collidable.hpp"

Brick::Brick(BrickType type):
  _type(type) {
  AddFeature(new Dimension());
  AddFeature(new Collidable(this));
};

int Brick::GetPoints() {
  return (int)_type;
}

bool Brick::IsUnbreakable() {
  return _type == Brick::UNBREAKABLE;
}
