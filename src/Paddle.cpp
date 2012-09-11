#include "Paddle.hpp"

void Paddle::MoveLeft(const float timestep) {
  if (_velocity > 0.f) {
    _velocity = 0.f;
  }
  _velocity -= Paddle::ACCELERATION * timestep;
}

void Paddle::MoveRight(const float timestep) {
  if (_velocity < 0.f) {
    _velocity = 0.f;
  }
  _velocity += Paddle::ACCELERATION * timestep;
}

void Paddle::Idle(const float timestep) {
  if (_velocity == 0.f) {
    return;
  }
  // handle deceleration from movement left
  if (_velocity < 0.f) {
    _velocity += Paddle::DECELERATION * timestep;
    if (_velocity > 0.f) {
      _velocity = 0.f;
    }
  }
  // handle deceleration from movement right
  if (_velocity > 0.f) {
    _velocity -= Paddle::DECELERATION * timestep;
    if (_velocity < 0.f) {
      _velocity = 0.f;
    }
  }
}

const float Paddle::GetVelocity() {
  return _velocity;
}
