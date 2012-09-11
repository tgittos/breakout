#ifndef COMPOSABLE_OBJECT_H
#define COMPOSABLE_OBJECT_H

#include <map>

class ComponentFeature;

class ComposableObject {
  public:
  ComposableObject();
  virtual ~ComposableObject();

  bool HasFeature(const char* identifier);

  ComponentFeature* GetFeature(const char* identifier);

  void AddFeature(const char* identifier, ComponentFeature* feature);

  protected:
  std::map<const char*, ComponentFeature*> _componentFeatures;
};

#endif
