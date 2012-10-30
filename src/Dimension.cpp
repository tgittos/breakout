#include "Dimension.hpp"

float Dimension::GetX() {
  return _x;
}

void Dimension::SetX(float x) {
  _x = x;
}

float Dimension::GetY() {
  return _y;
}

void Dimension::SetY(float y) {
  _y = y;
}

float Dimension::GetWidth() {
  return _width;
}

void Dimension::SetWidth(float width) {
  _width = width;
}

float Dimension::GetHeight() {
  return _height;
}

void Dimension::SetHeight(float height) {
  _height = height;
}

bool Dimension::Inside(int x, int y) {
  return x > _x && x < (_x + _width) &&
         y > _y && y < (_y + _height);
}
