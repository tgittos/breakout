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
  ConcreteComposableObject(ConcreteComponentFeature* ccf) {
    AddFeature(ccf->GetIdentifier(), ccf);
  }
  ~ConcreteComposableObject() {
    // iterate over features and delete the memory for them
  }
};

TEST(ComposableObject, HasFeatureReturnsTrue) {
  ConcreteComponentFeature* ccf = new ConcreteComponentFeature();
  ConcreteComposableObject co = ConcreteComposableObject(ccf);
  ASSERT_TRUE(co.HasFeature(ccf->GetIdentifier()));
}

TEST(ComposableObject, HasFeatureReturnsFalse) {
  ConcreteComponentFeature* ccf = new ConcreteComponentFeature();
  ConcreteComposableObject co = ConcreteComposableObject(ccf);
  ASSERT_FALSE(co.HasFeature("FoobarComponentFeature"));
}

TEST(ComposableObject, GetValidFeature) {
  ConcreteComponentFeature* ccf = new ConcreteComponentFeature();
  ConcreteComposableObject co = ConcreteComposableObject(ccf);
  ASSERT_EQ(ccf, co.GetFeature("ConcreteComponentFeature"));
}

TEST(ComposableObject, GetInvalidFeature) {
  ConcreteComponentFeature* ccf = new ConcreteComponentFeature();
  ConcreteComposableObject co = ConcreteComposableObject(ccf);
  ASSERT_EQ(NULL, co.GetFeature("FoobarComponentFeature"));
}
