#include "gtest/gtest.h"
#include "EventManager.hpp"
#include "MockEvent.hpp"
#include "MockEventInterface.hpp"

TEST(EventManager, InitializeList) {
  EventManager em = EventManager();
  ASSERT_EQ(0, em.Subscribers("MockEvent"));
}

TEST(EventManager, EventSubscription) {
  EventManager em = EventManager();
  em.Subscribe("MockEvent", SomeHandler);
  ASSERT_EQ(1, em.Subscribers("MockEvent"));
}

TEST(EventManager, EventDispatch) {
  ASSERT_FALSE(true);
}

TEST(EventManager, ListenerReceive) {
  ASSERT_FALSE(true);
}
