#ifndef COMPOSABLE_OBJECT_H
#define COMPOSABLE_OBJECT_H

class ComponentFeature;

class ComposableObject {
  public:
  ComposableObject();
  virtual ~ComposableObject();

  bool HasFeature(const char* identifier);

  protected:
  void AddFeature(const char* identifier, ComponentFeature* feature);
};

#endif
