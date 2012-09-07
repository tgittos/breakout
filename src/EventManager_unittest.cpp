#include "gtest/gtest.h"
#include "EventManager.hpp"
#include "ComposableObject.hpp"

class MockEventSubscriber : public ComposableObject {
  public:
  int MyInteger;
  MockEventSubscriber() {
    MyInteger = 0;
    EventManager::GetInstance().Subscribe("MockEvent", EventManager::Handler(this, static_cast<void (ComposableObject::*)(void*)>(&MockEventSubscriber::MockEventHandler)));
    EventManager::GetInstance().Subscribe("MockEvent2", EventManager::Handler(this, static_cast<void (ComposableObject::*)(void*)>(&MockEventSubscriber::MockEvent2Handler)));
  };
  void MockEventHandler(void* data) {
    MyInteger = 1;
  }
  void MockEvent2Handler(void* data) {
    MyInteger++;
  }
};

TEST(EventManager, InitializeList) {
  ASSERT_EQ(0, EventManager::GetInstance().SubscriberCount("MockEvent"));
}

TEST(EventManager, EventDispatch) {
  MockEventSubscriber mes = MockEventSubscriber();
  ASSERT_EQ(0, mes.MyInteger);
  EventManager::GetInstance().Dispatch("MockEvent", NULL);
  ASSERT_EQ(1, mes.MyInteger);
}

TEST(EventManager, NoLeakySubscriptions) {
  MockEventSubscriber mes = MockEventSubscriber();
  ASSERT_EQ(0, mes.MyInteger);
  EventManager::GetInstance().Dispatch("MockEvent", NULL);
  ASSERT_EQ(1, mes.MyInteger);
  EventManager::GetInstance().Dispatch("MockEvent2", NULL);
  ASSERT_EQ(2, mes.MyInteger);
}
