#ifndef PADDLE_H
#define PADDLE_H

#include "ComposableObject.hpp"

class Paddle : public ComposableObject {

  public:
  Paddle();
  ~Paddle(){};

  const float GetVelocity();

  void MoveLeft(const float timestep);

  void MoveRight(const float timestep);

  void Idle(const float timestep);

  private:
  static float const ACCELERATION = 4.f;
  static float const DECELERATION = 2.f;

  float _velocity;

};

#endif
