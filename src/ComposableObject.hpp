#ifndef COMPOSABLE_OBJECT_H
#define COMPOSABLE_OBJECT_H

#include <cstddef>
#include <list>

class ComponentFeature;

class ComposableObject {
  public:
  ComposableObject();
  virtual ~ComposableObject();

  template<class T>
  bool HasFeature() {
    return NULL != GetFeature<T>();
  }

  template<class T>
  T* GetFeature() {
    T* ptr = NULL;
    for(std::list<ComponentFeature*>::iterator itr = _componentFeatures.begin(); itr != _componentFeatures.end(); ++itr) {
      ptr = dynamic_cast<T*>(*itr);
      if (NULL != ptr) {
        break;
      }
    }
    return ptr;
  }

  void AddFeature(ComponentFeature* feature);

  protected:
  std::list<ComponentFeature*> _componentFeatures;
};

#endif
