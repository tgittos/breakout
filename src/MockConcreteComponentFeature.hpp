#ifndef MOCK_CONCRETE_COMPONENT_FEATURE_H
#define MOCK_CONCRETE_COMPONENT_FEATURE_H

#include "gmock/gmock.h"
#include "ComponentFeature.hpp"

class MockConcreteComponentFeature : public ComponentFeature {
  public:
  MOCK_CONST_METHOD0(GetIdentifier, char*());
};

#endif
