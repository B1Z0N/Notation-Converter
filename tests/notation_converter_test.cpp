#include "gmock/gmock.h"

#include "notation_converter.h"

#include <string>

TEST(NotationConverter, Intitialization) {
  NotationConverter nt{"1", ArithmeticNotation::PREFIX};
}

class NotationConverterInit : public testing::Test {
 public:
  NotationConverter nt;
  std::string converted;
};

TEST_F(NotationConverterInit, PostInitialization) {
  nt.insert("1", ArithmeticNotation::PREFIX);
}

TEST_F(NotationConverterInit, OneNumberFromXNotationToXNotation) {
  nt.insert("1", ArithmeticNotation::PREFIX);
  converted = nt.convert(ArithmeticNotation::PREFIX);
  EXPECT_THAT(converted, testing::Eq(std::string{"1"}));

  nt.insert("22", ArithmeticNotation::INFIX);
  converted = nt.convert(ArithmeticNotation::INFIX);
  EXPECT_THAT(converted, testing::Eq(std::string{"22"}));

  nt.insert("945", ArithmeticNotation::POSTFIX);
  converted = nt.convert(ArithmeticNotation::POSTFIX);
  EXPECT_THAT(converted, testing::Eq(std::string{"945"}));
}

TEST_F(NotationConverterInit, OneNumberFromXNotationToYNotation) {
  NotationConverter nt{"1", ArithmeticNotation::PREFIX};
  converted = nt.convert(ArithmeticNotation::INFIX);
  EXPECT_THAT(converted, testing::Eq(std::string{"1"}));

  //   NotationConverter nt{"1", ArithmeticNotation::PREFIX};
  //   converted = nt.convert(ArithmeticNotation::POSTFIX);
  //   EXPECT_THAT(converted, testing::Eq(std::string{"1"}));

  //   NotationConverter nt{"1", ArithmeticNotation::INFIX};
  //   converted = nt.convert(ArithmeticNotation::PREFIX);
  //   EXPECT_THAT(converted, testing::Eq(std::string{"1"}));

  //   NotationConverter nt{"1", ArithmeticNotation::INFIX};
  //   converted = nt.convert(ArithmeticNotation::POSTFIX);
  //   EXPECT_THAT(converted, testing::Eq(std::string{"1"}));

  //   NotationConverter nt{"1", ArithmeticNotation::POSTFIX};
  //   converted = nt.convert(ArithmeticNotation::PREFIX);
  //   EXPECT_THAT(converted, testing::Eq(std::string{"1"}));

  //   NotationConverter nt{"1", ArithmeticNotation::POSTFIX};
  //   converted = nt.convert(ArithmeticNotation::INFIX);
  //   EXPECT_THAT(converted, testing::Eq(std::string{"1"}));
}