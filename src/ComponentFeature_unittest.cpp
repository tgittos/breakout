#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MockConcreteComponentFeature.hpp"

using ::testing::Return;

TEST(ComponentFeature, CanGetIdentifier) {
  MockConcreteComponentFeature ccf;

  EXPECT_CALL(ccf, GetIdentifier())
      .WillRepeatedly(Return("MockComponentFeature"));

  ASSERT_EQ("MockComponentFeature", ccf.GetIdentifier());
}
