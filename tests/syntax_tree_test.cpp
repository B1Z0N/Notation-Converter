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

TEST(SyntaxTree, BuildingTreeFromDifferentNotation) {
  
}