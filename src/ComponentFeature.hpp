#ifndef COMPONENT_FEATURE_H
#define COMPONENT_FEATURE_H

class ComponentFeature {
  public:
  ComponentFeature() {};
  virtual ~ComponentFeature() {};

  virtual const char* GetIdentifier() =0;
};

#endif
