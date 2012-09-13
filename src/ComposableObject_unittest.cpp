#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ComposableObject.hpp"
#include "ComponentFeature.hpp"

class ConcreteComponentFeature : public ComponentFeature {
};

class ConcreteComposableObject : public ComposableObject {
  public:
  ConcreteComposableObject(ConcreteComponentFeature* ccf = NULL) {
    if(NULL != ccf) {
      AddFeature(ccf);
    }
  }
  void AddConcreteComponentFeature() {
    return AddFeature(new ConcreteComponentFeature());
  }
  ~ConcreteComposableObject() {
    // iterate over features and delete the memory for them
  }
};

TEST(ComposableObject, HasFeatureReturnsTrue) {
  ConcreteComponentFeature* ccf = new ConcreteComponentFeature();
  ConcreteComposableObject co = ConcreteComposableObject(ccf);
  ASSERT_TRUE(co.HasFeature<ConcreteComponentFeature>());
}

TEST(ComposableObject, HasFeatureReturnsFalse) {
  ConcreteComposableObject co = ConcreteComposableObject();
  ASSERT_FALSE(co.HasFeature<ConcreteComponentFeature>());
}

TEST(ComposableObject, GetValidFeature) {
  ConcreteComponentFeature* ccf = new ConcreteComponentFeature();
  ConcreteComposableObject co = ConcreteComposableObject(ccf);
  ASSERT_EQ(ccf, co.GetFeature<ConcreteComponentFeature>());
}

TEST(ComposableObject, GetInvalidFeature) {
  ConcreteComposableObject co = ConcreteComposableObject();
  ASSERT_EQ(NULL, co.GetFeature<ConcreteComponentFeature>());
}
