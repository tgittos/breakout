#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "ComposableObject.hpp"

class Button : public ComposableObject {
  public:

  Button(std::string label);
  ~Button(){};

  std::string GetEventString();

  std::string GetLabel();

  private:
  static std::string NAMESPACE;
  std::string _label;
};

#endif
