#include "gtest/gtest.h"
#include "EventManager.hpp"

class MockEventSubscriber : public EventHandler {
  public:
  int MyInteger;
  static int MyStaticInteger;
  MockEventSubscriber() {
    MyInteger = 0;
    EventManager::GetInstance().Subscribe("MockEvent", EventManager::Handler(this, static_cast<void (EventHandler::*)(void*)>(&MockEventSubscriber::MockEventHandler)));

    EventManager::GetInstance().Subscribe("MockEvent2", EventManager::Handler(this, static_cast<void (EventHandler::*)(void*)>(&MockEventSubscriber::MockEvent2Handler)));

    EventManager::GetInstance().Subscribe("MockEvent3", EventManager::Handler(&MockEvent3Handler));
  };
  ~MockEventSubscriber(){};
  void MockEventHandler(void* data) {
    MyInteger = 1;
  };
  void MockEvent2Handler(void* data) {
    MyInteger++;
  };
  static void MockEvent3Handler(void* data) {
    MyStaticInteger = -1;
  };
};
int MockEventSubscriber::MyStaticInteger = 0;

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

TEST(EventManager, StaticMethodHandler) {
  ASSERT_EQ(0, MockEventSubscriber::MyStaticInteger);
  EventManager::GetInstance().Dispatch("MockEvent3", NULL);
  ASSERT_EQ(-1, MockEventSubscriber::MyStaticInteger);
}
