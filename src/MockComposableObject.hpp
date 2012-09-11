#ifndef MOCK_COMPOSABLE_OBJECT_H
#define MOCK_COMPOSABLE_OBJECT_H

#include "gmock/gmock.h"
#include "ComposableObject.hpp"

class MockComposableObject : public ComposableObject {
  MOCK_METHOD1(HasFeature, bool(const char* identifier));
  MOCK_METHOD2(AddFeature, void(const char* identifier, ComponentFeature* feature));
};

#endif
