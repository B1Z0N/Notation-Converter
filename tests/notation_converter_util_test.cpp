#include "gmock/gmock.h"

#include "arithmetic_notation.h"
#include "notation_converter_util.h"

#include <string>

using namespace notation_conv::detail;

TEST(Utils, EmptyConvert) {
  EXPECT_THAT(from_infix_to_prefix(""), testing::Eq(""));
  EXPECT_THAT(from_postfix_to_prefix(""), testing::Eq(""));
  EXPECT_THAT(from_prefix_to_postfix(""), testing::Eq(""));
  EXPECT_THAT(from_prefix_to_infix(""), testing::Eq(""));
}
