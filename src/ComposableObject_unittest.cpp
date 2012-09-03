#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ComposableObject.hpp"
#include "ComponentFeature.hpp"

class ConcreteComponentFeature : public ComponentFeature {
  public:
  virtual const char* GetIdentifier() {
    return "ConcreteComponentFeature";
  }
};

class ConcreteComposableObject : public ComposableObject {
  public:
  ConcreteComposableObject() {
    ConcreteComponentFeature* ccf = new ConcreteComponentFeature();
    AddFeature(ccf->GetIdentifier(), ccf);
  }
  ~ConcreteComposableObject() {
    // iterate over features and delete the memory for them
  }
};

TEST(ComposableObject, HasFeatureReturnsTrue) {
  ConcreteComposableObject co = ConcreteComposableObject();
  ASSERT_TRUE(co.HasFeature("ConcreteComponentFeature"));
}

TEST(ComposableObject, HasFeatureReturnsFalse) {
  ConcreteComposableObject co = ConcreteComposableObject();
  ASSERT_FALSE(co.HasFeature("FoobarComponentFeature"));
}
