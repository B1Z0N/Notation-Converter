#include "gmock/gmock.h"

#include "notation_converter.h"

#include <string>

using namespace notation_conv;

TEST(NotationConverter, Intitialization) {
  NotationConverter nt{"1", ArithmeticNotation::PREFIX};
}

TEST(NotationConverter, PostInitialization) {
  NotationConverter nt;
  nt.insert("1", ArithmeticNotation::PREFIX);
}

TEST(NotationConverter, CopyMoveConstructionAndAssignment) {
  NotationConverter nt1 {"3", ArithmeticNotation::POSTFIX};
  NotationConverter nt2 {nt1};
  NotationConverter nt3 {std::move(nt1)};
  NotationConverter nt4 = nt2;
  NotationConverter nt5 = std::move(nt2);
}

class NotationConverterInit : public testing::Test {
  NotationConverter nt {};

 public:

  bool from_x_to_y_notation(ArithmeticNotation from, ArithmeticNotation to,
                            std::string start_expr, std::string end_expr) {
    nt.insert(start_expr, from);
    return nt.convert(to) == end_expr;
  }
};

TEST_F(NotationConverterInit, OneNumberFromXNotationToXNotation) {
  auto from_x_to_x_notation{
      [this](ArithmeticNotation notation, std::string expr) {
        return from_x_to_y_notation(notation, notation, expr, expr);
      }};

  EXPECT_TRUE(from_x_to_x_notation(ArithmeticNotation::PREFIX, "1"));
  EXPECT_TRUE(from_x_to_x_notation(ArithmeticNotation::INFIX, "12"));
  EXPECT_TRUE(from_x_to_x_notation(ArithmeticNotation::POSTFIX, "945"));
}

TEST_F(NotationConverterInit, OneNumberFromXNotationToYNotation) {
  EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::PREFIX, ArithmeticNotation::INFIX, "1", "1"));
  EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::PREFIX, ArithmeticNotation::POSTFIX, "12", "12"));

  EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::INFIX, ArithmeticNotation::PREFIX, "123", "123"));
  EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::INFIX, ArithmeticNotation::POSTFIX, "1234", "1234"));

  EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::POSTFIX, ArithmeticNotation::INFIX, "12345", "12345"));
  EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::POSTFIX, ArithmeticNotation::PREFIX, "91231", "91231"));
}


// TEST_F(NotationConverterInit, PlusFromXNotationToYNotation) {
  // EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::PREFIX, ArithmeticNotation::INFIX, "+ 1 1", "1 + 1"));
  // EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::PREFIX, ArithmeticNotation::POSTFIX, "+ 1 2", "1 2 +"));

//   EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::INFIX, ArithmeticNotation::PREFIX, "+ 123", "123"));
//   EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::INFIX, ArithmeticNotation::POSTFIX, "1234", "1234"));

//   EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::POSTFIX, ArithmeticNotation::INFIX, "12345", "12345"));
//   EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::POSTFIX, ArithmeticNotation::PREFIX, "91231", "91231"));
// }