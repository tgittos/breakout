#include <cassert>
#include "ComposableObject.hpp"

ComposableObject::ComposableObject() {
  std::list<ComponentFeature*> _componentFeatures;
}

ComposableObject::~ComposableObject() {
/*
  std::map<const char*, ComponentFeature*>::iterator itr;
  for (itr = _componentFeatures.begin(); itr != _componentFeatures.end(); ++itr) {
    delete itr->second;
  }
*/
}

void ComposableObject::AddFeature(ComponentFeature* feature) {
  _componentFeatures.push_back(feature);
}
