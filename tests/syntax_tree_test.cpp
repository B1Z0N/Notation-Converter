#include "gmock/gmock.h"

#include "arithmetic_notation.h"
#include "syntax_tree.h"

#include <string>

using namespace notation_conv;
using namespace detail;

TEST(SyntaxTree, ConstructionAndAssignment) {
  SyntaxTree st1;
  // SyntaxTree st2 {st1}; // not allowed
  SyntaxTree st3{std::move(st1)};
  // SyntaxTree st4 = st3; // not allowed
  SyntaxTree st5 = std::move(st3);

  SyntaxTree st{"1", ArithmeticNotation::PREFIX};
}

auto check_same_notation{
    [](const std::string& expr, ArithmeticNotation notation) {
      SyntaxTree st{expr, notation};
      return st.to_notation(notation) == expr;
    }};

TEST(SyntaxTree, ConversionToTheSameNotation) {
  ASSERT_TRUE(check_same_notation("+ 1 1", ArithmeticNotation::PREFIX));
  ASSERT_TRUE(check_same_notation("+ 1 1", ArithmeticNotation::INFIX));
  ASSERT_TRUE(check_same_notation("+ 1 1", ArithmeticNotation::POSTFIX));
}