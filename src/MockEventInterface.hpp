#ifndef MOCK_EVENT_INTERFACE_H
#define MOCK_EVENT_INTERFACE_H

#include "gmock/gmock.h"
#include "EventInterface.hpp"

class MockEventInterface : public EventInterface {
  public:
  MOCK_CONST_METHOD0(GetIdentifier, char*());
};

#endif
