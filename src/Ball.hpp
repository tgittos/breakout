#ifndef BALL_H
#define BALL_H

#include "ComposableObject.hpp"
#include "Collidable.hpp"

class Ball : public ComposableObject {
  public:
  Ball();
  ~Ball(){};

  void SetHeading(float h);
  float GetHeading();
  float GetSpeed();

  void Reflect(Collidable::IntersectionSurface surfaceAngle);
  void SpeedUp();

  private:
  const float SPEED_INCREMENT;
  const float OSCILLATION_FUDGE;

  float _heading;
  float _speed;
};

#endif
