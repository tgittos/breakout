#ifndef SCORE_H
#define SCORE_H

#include "Brick.hpp"

class Score {
  public:
  Score();
  ~Score(){};

  int GetScore();

  void Increment(Brick::BrickType type);

  private:
  int _score;
};

#endif
