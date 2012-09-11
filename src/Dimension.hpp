#ifndef DIMENSION_H
#define DIMENSION_H

#include "ComponentFeature.hpp"

class Dimension : public ComponentFeature {
  public:
  Dimension():
    _x(0.f), _y(0.f), _width(0.f), _height(0.f){};
  virtual ~Dimension(){};

  const char* GetIdentifier() { return "Dimension"; }

  float GetX();
  void SetX(float x);

  float GetY();
  void SetY(float y);

  float GetWidth();
  void SetWidth(float width);

  float GetHeight();
  void SetHeight(float height);

  private:
  float _x;
  float _y;
  float _width;
  float _height;
};

#endif
