#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "ComponentFeature.hpp"
#include "ComposableObject.hpp"

class Collidable : public ComponentFeature {
  public:
  Collidable(ComposableObject* owner);
  ~Collidable() {}

  bool Intersects(float x, float y);

  private:
  ComposableObject* _owner;
};

#endif
