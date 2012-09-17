#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "ComponentFeature.hpp"
#include "ComposableObject.hpp"

class Collidable : public ComponentFeature {
  public:
  enum IntersectionSurface {
    NONE = -1,
    LEFT = 0,
    TOP = 90,
    RIGHT = 180,
    BOTTOM = 270
  };

  Collidable(ComposableObject* owner);
  ~Collidable() {}

  IntersectionSurface Intersects(float x, float y);

  private:
  ComposableObject* _owner;
};

#endif
