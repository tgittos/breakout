#include <string>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Button.hpp"
#include "EventManager.hpp"
#include "EventHandler.hpp"
#include "Dimension.hpp"
#include "Clickable.hpp"

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

TEST(ButtonTest, FeatureTest) {
  Button b("foobar");
  ASSERT_TRUE(b.HasFeature<Dimension>());
  ASSERT_TRUE(b.HasFeature<Clickable>());
}

TEST(ButtonTest, ClickedDispatchesEvent) {
  Button b("foobar");
  MockEventSubscriber mes = MockEventSubscriber(b.GetEventString());
  ASSERT_EQ(0, mes.MyInteger);
  b.GetFeature<Clickable>()->Click();
  ASSERT_EQ(1, mes.MyInteger);
}

TEST(ButtonTest, GetEventString) {
  Button b("foobar");
  ASSERT_EQ(std::string("button::foobar::click"), b.GetEventString());
}

TEST(ButtonTest, GetLabel) {
  Button b("foobar");
  ASSERT_EQ(std::string("foobar"), b.GetLabel());
}

TEST(ButtonTest, Pointers) {
  Button* b = new Button("foobar");
  ASSERT_EQ(std::string("foobar"), b->GetLabel());
  ASSERT_EQ(std::string("button::foobar::click"), b->GetEventString());
}
