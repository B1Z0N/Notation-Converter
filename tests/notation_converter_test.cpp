#include "gmock/gmock.h"

#include "arithmetic_notation.h"
#include "notation_converter.h"

#include <string>

using namespace notaconv;

TEST(NotationConverter, CopyMoveConstructionAndAssignment) {
  NotationConverter nt1{"3", ArithmeticNotation::POSTFIX};
  // NotationConverter nt2{nt1}; // not allowed
  NotationConverter nt3{std::move(nt1)};
  // NotationConverter nt4 = nt2; // not allowed
  NotationConverter nt5 = std::move(nt3);
}

class NotationConverterInit : public testing::Test {
  NotationConverter nt{};

 public:
  bool from_x_to_y_notation(ArithmeticNotation from, ArithmeticNotation to,
                            const std::string& start_expr, const std::string& end_expr) {
    nt = NotationConverter{start_expr, from};
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
  EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::PREFIX,
                                   ArithmeticNotation::INFIX, "1", "1"));
  EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::PREFIX,
                                   ArithmeticNotation::POSTFIX, "12", "12"));

  EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::INFIX,
                                   ArithmeticNotation::PREFIX, "123", "123"));
  EXPECT_TRUE(from_x_to_y_notation(
      ArithmeticNotation::INFIX, ArithmeticNotation::POSTFIX, "1234", "1234"));

  EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::POSTFIX,
                                   ArithmeticNotation::INFIX, "12345",
                                   "12345"));
  EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::POSTFIX,
                                   ArithmeticNotation::PREFIX, "91231",
                                   "91231"));
}

TEST_F(NotationConverterInit, PlusFromXNotationToYNotation) {

  EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::PREFIX,
                                   ArithmeticNotation::INFIX, "+ 1 1",
                                   "1 + 1"));

  EXPECT_TRUE(from_x_to_y_notation(
      ArithmeticNotation::INFIX, ArithmeticNotation::POSTFIX, "1234", "1234"));

  EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::POSTFIX,
                                   ArithmeticNotation::INFIX, "12345",
                                   "12345"));
  EXPECT_TRUE(from_x_to_y_notation(ArithmeticNotation::POSTFIX,
                                   ArithmeticNotation::PREFIX, "91231",
                                   "91231"));
}

TEST(NotationConverter, ConversionOfSingleNumber) {
  NotationConverter prefix {" 1  ", ArithmeticNotation::PREFIX};
  ASSERT_EQ(prefix.convert(ArithmeticNotation::PREFIX), "1");
  ASSERT_EQ(prefix.convert(ArithmeticNotation::INFIX), "1");
  ASSERT_EQ(prefix.convert(ArithmeticNotation::POSTFIX), "1");

  NotationConverter infix {" 1  ", ArithmeticNotation::INFIX};
  ASSERT_EQ(infix.convert(ArithmeticNotation::PREFIX), "1");
  ASSERT_EQ(infix.convert(ArithmeticNotation::INFIX), "1");
  ASSERT_EQ(infix.convert(ArithmeticNotation::POSTFIX), "1");

  NotationConverter postfix {" 1  ", ArithmeticNotation::POSTFIX};
  ASSERT_EQ(postfix.convert(ArithmeticNotation::PREFIX), "1");
  ASSERT_EQ(postfix.convert(ArithmeticNotation::INFIX), "1");
  ASSERT_EQ(postfix.convert(ArithmeticNotation::POSTFIX), "1");
}

TEST(NotationConverter, ConversionOfSingleOperatorExpression) {
  NotationConverter prefix {" +  1  1 ", ArithmeticNotation::PREFIX};
  ASSERT_EQ(prefix.convert(ArithmeticNotation::PREFIX), "+ 1 1");
  ASSERT_EQ(prefix.convert(ArithmeticNotation::INFIX), "1 + 1");
  ASSERT_EQ(prefix.convert(ArithmeticNotation::POSTFIX), "1 1 +");

  NotationConverter infix {" 1   + 2 ", ArithmeticNotation::INFIX};
  ASSERT_EQ(infix.convert(ArithmeticNotation::PREFIX), "+ 1 2");
  ASSERT_EQ(infix.convert(ArithmeticNotation::INFIX), "1 + 2");
  ASSERT_EQ(infix.convert(ArithmeticNotation::POSTFIX), "1 2 +");

  NotationConverter postfix {" 1   2  + ", ArithmeticNotation::POSTFIX};
  ASSERT_EQ(postfix.convert(ArithmeticNotation::PREFIX), "+ 1 2");
  ASSERT_EQ(postfix.convert(ArithmeticNotation::INFIX), "1 + 2");
  ASSERT_EQ(postfix.convert(ArithmeticNotation::POSTFIX), "1 2 +");
}

TEST(NotationConverter, ConversionOfTwoOperatorsWithEqualPrecedence) {
  NotationConverter prefix {" +  1  + 2 3 ", ArithmeticNotation::PREFIX};
  ASSERT_EQ(prefix.convert(ArithmeticNotation::PREFIX), "+ 1 + 2 3");
  ASSERT_EQ(prefix.convert(ArithmeticNotation::INFIX), "1 + 2 + 3");
  ASSERT_EQ(prefix.convert(ArithmeticNotation::POSTFIX), "1 2 3 + +");

  NotationConverter infix {" 1  +   2  + 3 ", ArithmeticNotation::INFIX};
  ASSERT_EQ(infix.convert(ArithmeticNotation::PREFIX), "+ + 1 2 3");
  ASSERT_EQ(infix.convert(ArithmeticNotation::INFIX), "1 + 2 + 3");
  ASSERT_EQ(infix.convert(ArithmeticNotation::POSTFIX), "1 2 + 3 +");

  NotationConverter postfix {"  1  2     3  +   +    ", ArithmeticNotation::POSTFIX};
  ASSERT_EQ(postfix.convert(ArithmeticNotation::PREFIX), "+ 1 + 2 3");
  ASSERT_EQ(postfix.convert(ArithmeticNotation::INFIX), "1 + 2 + 3");
  ASSERT_EQ(postfix.convert(ArithmeticNotation::POSTFIX), "1 2 3 + +");
}

TEST(NotationConverter, ConversionOfTwoOperatorsWithDifferentPrecedence) {
  NotationConverter prefix {" +  1  * 2 3 ", ArithmeticNotation::PREFIX};
  ASSERT_EQ(prefix.convert(ArithmeticNotation::PREFIX), "+ 1 * 2 3");
  ASSERT_EQ(prefix.convert(ArithmeticNotation::INFIX), "1 + 2 * 3");
  ASSERT_EQ(prefix.convert(ArithmeticNotation::POSTFIX), "1 2 3 * +");

  NotationConverter infix {" 1   +   2 *   3               ", ArithmeticNotation::INFIX};
  ASSERT_EQ(infix.convert(ArithmeticNotation::PREFIX), "+ 1 * 2 3");
  ASSERT_EQ(infix.convert(ArithmeticNotation::INFIX), "1 + 2 * 3");
  ASSERT_EQ(infix.convert(ArithmeticNotation::POSTFIX), "1 2 3 * +");

  NotationConverter postfix {"   1   2 3   *          + ", ArithmeticNotation::POSTFIX};
  ASSERT_EQ(postfix.convert(ArithmeticNotation::PREFIX), "+ 1 * 2 3");
  ASSERT_EQ(postfix.convert(ArithmeticNotation::INFIX), "1 + 2 * 3");
  ASSERT_EQ(postfix.convert(ArithmeticNotation::POSTFIX), "1 2 3 * +");
}

TEST(NotationConverter, ConversionOfTwoOperatorsWithEqualPrecedenceInParentheses) {
  NotationConverter prefix {" +  1  + 2 3 ", ArithmeticNotation::PREFIX};
  ASSERT_EQ(prefix.convert(ArithmeticNotation::PREFIX), "+ 1 + 2 3");
  ASSERT_EQ(prefix.convert(ArithmeticNotation::INFIX), "1 + 2 + 3");
  ASSERT_EQ(prefix.convert(ArithmeticNotation::POSTFIX), "1 2 3 + +");

  NotationConverter infix {" 1  +  ( 2  + 3   ) ", ArithmeticNotation::INFIX};
  ASSERT_EQ(infix.convert(ArithmeticNotation::PREFIX), "+ 1 + 2 3");
  ASSERT_EQ(infix.convert(ArithmeticNotation::INFIX), "1 + 2 + 3");
  ASSERT_EQ(infix.convert(ArithmeticNotation::POSTFIX), "1 2 3 + +");

  NotationConverter postfix {"  1  2     3  +   +    ", ArithmeticNotation::POSTFIX};
  ASSERT_EQ(postfix.convert(ArithmeticNotation::PREFIX), "+ 1 + 2 3");
  ASSERT_EQ(postfix.convert(ArithmeticNotation::INFIX), "1 + 2 + 3");
  ASSERT_EQ(postfix.convert(ArithmeticNotation::POSTFIX), "1 2 3 + +");
}

TEST(NotationConverter, ConversionOfTwoOperatorsWithDifferentPrecedenceInParentheses) {
  NotationConverter prefix {" /   1   - 2  3     ", ArithmeticNotation::PREFIX};
  ASSERT_EQ(prefix.convert(ArithmeticNotation::PREFIX), "/ 1 - 2 3");
  ASSERT_EQ(prefix.convert(ArithmeticNotation::INFIX), "1 / ( 2 - 3 )");
  ASSERT_EQ(prefix.convert(ArithmeticNotation::POSTFIX), "1 2 3 - /");

  NotationConverter infix {" 1   /   ( 2  -   3   )    ", ArithmeticNotation::INFIX};
  ASSERT_EQ(infix.convert(ArithmeticNotation::PREFIX), "/ 1 - 2 3");
  ASSERT_EQ(infix.convert(ArithmeticNotation::INFIX), "1 / ( 2 - 3 )");
  ASSERT_EQ(infix.convert(ArithmeticNotation::POSTFIX), "1 2 3 - /");

  NotationConverter postfix {" 1   2   3 -  /     ", ArithmeticNotation::POSTFIX};
  ASSERT_EQ(postfix.convert(ArithmeticNotation::PREFIX), "/ 1 - 2 3");
  ASSERT_EQ(postfix.convert(ArithmeticNotation::INFIX), "1 / ( 2 - 3 )");
  ASSERT_EQ(postfix.convert(ArithmeticNotation::POSTFIX), "1 2 3 - /");
}

TEST(NotationConverter, ConversionWithAdditionalParentheses) {
  NotationConverter infix {"( ( 5 ) * ( ( 3 ) + ( 2 ) ) )", ArithmeticNotation::INFIX};
  ASSERT_EQ(infix.convert(ArithmeticNotation::PREFIX), "* 5 + 3 2");
  ASSERT_EQ(infix.convert(ArithmeticNotation::INFIX), "5 * ( 3 + 2 )");
  ASSERT_EQ(infix.convert(ArithmeticNotation::POSTFIX), "5 3 2 + *");
}

TEST(NotationConverter, ComplexConversion) {
  NotationConverter prefix {"- * 5 - 3 + 2 * 6 / - 2 3 + 7 8 11", ArithmeticNotation::PREFIX};
  ASSERT_EQ(prefix.convert(ArithmeticNotation::PREFIX), "- * 5 - 3 + 2 * 6 / - 2 3 + 7 8 11");
  ASSERT_EQ(prefix.convert(ArithmeticNotation::INFIX), "5 * ( 3 - 2 + 6 * ( 2 - 3 ) / ( 7 + 8 ) ) - 11");
  ASSERT_EQ(prefix.convert(ArithmeticNotation::POSTFIX), "5 3 2 6 2 3 - 7 8 + / * + - * 11 -");

  NotationConverter infix {"5 * ( 3 - 2 + 6 * ( 2 - 3 ) / ( 7 + 8 ) ) - 11", ArithmeticNotation::INFIX};
  ASSERT_EQ(infix.convert(ArithmeticNotation::PREFIX), "- * 5 - 3 + 2 * 6 / - 2 3 + 7 8 11");
  ASSERT_EQ(infix.convert(ArithmeticNotation::INFIX), "5 * ( 3 - 2 + 6 * ( 2 - 3 ) / ( 7 + 8 ) ) - 11");
  ASSERT_EQ(infix.convert(ArithmeticNotation::POSTFIX), "5 3 2 6 2 3 - 7 8 + / * + - * 11 -");

  NotationConverter postfix {"5 3 2 6 2 3 - 7 8 + / * + - * 11 -", ArithmeticNotation::POSTFIX};
  ASSERT_EQ(postfix.convert(ArithmeticNotation::PREFIX), "- * 5 - 3 + 2 * 6 / - 2 3 + 7 8 11");
  ASSERT_EQ(postfix.convert(ArithmeticNotation::INFIX), "5 * ( 3 - 2 + 6 * ( 2 - 3 ) / ( 7 + 8 ) ) - 11");
  ASSERT_EQ(postfix.convert(ArithmeticNotation::POSTFIX), "5 3 2 6 2 3 - 7 8 + / * + - * 11 -");
}