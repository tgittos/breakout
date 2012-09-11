#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ComposableObject.hpp"
#include "MockComposableObject.hpp"
#include "Collidable.hpp"
#include "Dimension.hpp"

using ::testing::A;
using ::testing::Return;

class ConcreteComposableObject : public ComposableObject {
  public:
  ~ConcreteComposableObject(){}
  void Init(bool addDimension = true) {
    if (addDimension) {
      Dimension* d = new Dimension();
      AddFeature(d->GetIdentifier(), d);
    }
    Collidable* c = new Collidable(this);
    AddFeature(c->GetIdentifier(), c);
  }
};

TEST(CollidableTest, AddDimensionWhenNeeded) {
  ConcreteComposableObject o;
  ASSERT_FALSE(o.HasFeature("Dimension"));
  o.Init(false);
  ASSERT_TRUE(o.HasFeature("Dimension"));
}

TEST(CollidableTest, DontAddDimensionWhenNotNeeded) {
  ConcreteComposableObject o;
  ASSERT_FALSE(o.HasFeature("Dimension"));
  o.Init(true);
  ASSERT_TRUE(o.HasFeature("Dimension"));
}

TEST(CollidableTest, Intersection) {
  ConcreteComposableObject o;
  o.Init();
  static_cast<Dimension*>(o.GetFeature("Dimension"))->SetX(100.f);
  static_cast<Dimension*>(o.GetFeature("Dimension"))->SetY(100.f);
  ASSERT_TRUE(static_cast<Collidable*>(o.GetFeature("Collidable"))->Intersects(100.f, 100.f));
}

TEST(CollidableTest, NoIntersection) {
  ConcreteComposableObject o;
  o.Init();
  static_cast<Dimension*>(o.GetFeature("Dimension"))->SetX(0.f);
  static_cast<Dimension*>(o.GetFeature("Dimension"))->SetY(0.f);
  ASSERT_FALSE(static_cast<Collidable*>(o.GetFeature("Collidable"))->Intersects(100.f, 100.f));
}

TEST(CollidableTest, IntersectionWidth) {
  ConcreteComposableObject o;
  o.Init();
  static_cast<Dimension*>(o.GetFeature("Dimension"))->SetX(100.f);
  static_cast<Dimension*>(o.GetFeature("Dimension"))->SetY(100.f);
  static_cast<Dimension*>(o.GetFeature("Dimension"))->SetWidth(50.f);
  ASSERT_TRUE(static_cast<Collidable*>(o.GetFeature("Collidable"))->Intersects(120.f, 100.f));
}

TEST(CollidableTest, IntersectionHeight) {
  ConcreteComposableObject o;
  o.Init();
  static_cast<Dimension*>(o.GetFeature("Dimension"))->SetX(100.f);
  static_cast<Dimension*>(o.GetFeature("Dimension"))->SetY(100.f);
  static_cast<Dimension*>(o.GetFeature("Dimension"))->SetHeight(50.f);
  ASSERT_TRUE(static_cast<Collidable*>(o.GetFeature("Collidable"))->Intersects(100.f, 120.f));
}
