#ifndef BRICK_H
#define BRICK_H

#include "ComposableObject.hpp"

class Brick : public ComposableObject {
  public:
    enum BrickType {
      UNBREAKABLE = 0,
      ONE_POINT = 1,
      THREE_POINTS = 3,
      FIVE_POINTS = 5,
      SEVEN_POINTS = 7
    };
    static const int BRICK_HEIGHT = 25;
    static const int BRICK_WIDTH = 50;

    Brick(BrickType type);

    int GetPoints();
    bool IsUnbreakable();

  private:
    BrickType _type;
};

#endif
