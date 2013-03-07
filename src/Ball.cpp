#include <cstdlib>
#include <math.h>
#include <time.h>
#include "Ball.hpp"
#include "Dimension.hpp"

Ball::Ball():
  SPEED_INCREMENT(20.f), OSCILLATION_FUDGE(20.f), _heading(0.f), _speed(230.f) {
  AddFeature(new Dimension());
  AddFeature(new Collidable(this));
}

void Ball::SetHeading(float h) {
  _heading = h;
}

float Ball::GetHeading() {
  return _heading;
}

float Ball::GetSpeed() {
  return _speed;
}

void Ball::Reflect(Collidable::IntersectionSurface surfaceAngle) {
  float newHeading = fmodf(360 + 2.f * surfaceAngle - _heading, 360.f);
  if (abs(newHeading - _heading) == 180) {
    // fudge the newHeading to prevent oscillation
    srand(time(NULL)); // seed the random number
    if (rand() < 0.5) {
      newHeading += OSCILLATION_FUDGE;
    } else {
      newHeading -= OSCILLATION_FUDGE;
    }
  }
  _heading = newHeading;
}

void Ball::SpeedUp() {
  _speed += SPEED_INCREMENT;
}
