#include "Score.hpp"

Score::Score():
  _score(0) {
}

int Score::GetScore() {
  return _score;
}

void Score::Increment(Brick::BrickType type) {
  _score += (int)type;
}
