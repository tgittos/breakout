#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Clickable.hpp"
#include "EventManager.hpp"
#include "EventHandler.hpp"

class MockEventSubscriber : public EventHandler {
  public:
  int MyInteger;
  MockEventSubscriber(std::string event) {
    MyInteger = 0;
    EventManager::GetInstance().Subscribe(event, EventManager::Handler(this, static_cast<void (EventHandler::*)(void*)>(&MockEventSubscriber::OnClick)));
  };
  void OnClick(void* data) {
    MyInteger = 1;
  }
};

TEST(Clickable, GetEventString) {
  Clickable c("foobar");
  ASSERT_EQ(std::string("foobar::click"), c.GetEventString());
}

TEST(Clickable, DispatchEvent) {
  Clickable c("foobar");
  MockEventSubscriber mes = MockEventSubscriber(c.GetEventString());
  ASSERT_EQ(0, mes.MyInteger);
  c.Click();
  ASSERT_EQ(1, mes.MyInteger);
}
