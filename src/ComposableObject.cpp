#include "ComposableObject.hpp"

ComposableObject::ComposableObject() {
  std::map<const char*, ComponentFeature*> _componentFeatures = std::map<const char*, ComponentFeature*>();
}

ComposableObject::~ComposableObject() {
/*
  std::map<const char*, ComponentFeature*>::iterator itr;
  for (itr = _componentFeatures.begin(); itr != _componentFeatures.end(); ++itr) {
    delete itr->second;
  }
*/
}

void ComposableObject::AddFeature(const char* identifier, ComponentFeature* feature) {
  _componentFeatures.insert(std::pair<const char*, ComponentFeature*>(identifier, feature));
}

bool ComposableObject::HasFeature(const char* identifier) {
  std::map<const char*, ComponentFeature*>::iterator itr = _componentFeatures.find(identifier);
  return _componentFeatures.end() != itr;
}

ComponentFeature* ComposableObject::GetFeature(const char* identifier) {
  std::map<const char*, ComponentFeature*>::iterator itr = _componentFeatures.find(identifier);
  if(_componentFeatures.end() == itr)
  {
    return NULL;
  } else {
    return itr->second;
  }
}
