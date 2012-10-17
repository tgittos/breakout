#ifndef LEVEL_VIEW_H
#define LEVEL_VIEW_H


class Level;

class LevelView {
  public:
  virtual ~LevelView() {};

  virtual void Draw(Level* level) = 0;
};

#endif
