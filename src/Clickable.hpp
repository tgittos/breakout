#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <string>
#include "ComponentFeature.hpp"

class Clickable : public ComponentFeature {
  public:
  Clickable(std::string ns);
  ~Clickable(){};

  void Click();

  std::string GetEventString();

  private:
  static const std::string CLICK;
  std::string _namespace;
};

#endif
