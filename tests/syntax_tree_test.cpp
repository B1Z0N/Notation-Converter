#include "gmock/gmock.h"

#include "arithmetic_notation.h"
#include "syntax_tree.h"

#include <string>
#include <vector>

using namespace notation_conv;
using namespace detail;

////////////////////////////////////////////////////////////////////////////////
// Helper functions tests
////////////////////////////////////////////////////////////////////////////////

void __gen_vofstr(std::vector<std::string>& res) {}

template <typename T, typename... Ts>
void __gen_vofstr(std::vector<std::string>& res, T head, Ts... tail) {
  res.push_back(std::string{head});
  __gen_vofstr(res, tail...);
}

template <typename... Ts>
std::vector<std::string> gen_vofstr(Ts... tail) {
  std::vector<std::string> res;
  __gen_vofstr(res, tail...);
  return res;
}

TEST(split, SplitSingleSpaces) {
  using vofstr = std::vector<std::string>;

  vofstr v1 = gen_vofstr("1");
  ASSERT_EQ(split("1"), v1);
  ASSERT_EQ(split("1 "), v1);
  ASSERT_EQ(split(" 1"), v1);
  ASSERT_EQ(split(" 1 "), v1);

  vofstr v2 = gen_vofstr("1", "a", "3");
  ASSERT_EQ(split("1 a 3"), v2);
  ASSERT_EQ(split(" 1 a 3 "), v2);
  ASSERT_EQ(split(" 1 a 3 4"), gen_vofstr("1", "a", "3", "4"));
  ASSERT_EQ(split("4 1 a 3 "), gen_vofstr("4", "1", "a", "3"));
}

TEST(split, SplitMultipleSpaces) {
  using vofstr = std::vector<std::string>;

  vofstr v1 = gen_vofstr("1");
  ASSERT_EQ(split("1       "), v1);
  ASSERT_EQ(split("         1"), v1);
  ASSERT_EQ(split("    1     "), v1);

  vofstr v2 = gen_vofstr("1", "a", "3");
  ASSERT_EQ(split("1  a     3"), v2);
  ASSERT_EQ(split("   1  a 3   "), v2);
  ASSERT_EQ(split("   1 a  3 4"), gen_vofstr("1", "a", "3", "4"));
  ASSERT_EQ(split("4  1   a   3      "), gen_vofstr("4", "1", "a", "3"));
}

TEST(is_operator, Basic) {
  ASSERT_TRUE(is_operator("+"));
  ASSERT_TRUE(is_operator("-"));
  ASSERT_TRUE(is_operator("/"));
  ASSERT_TRUE(is_operator("*"));

  ASSERT_FALSE(is_operator("("));
  ASSERT_FALSE(is_operator(")"));
  ASSERT_FALSE(is_operator("2"));
  ASSERT_FALSE(is_operator("sasd"));
}

TEST(is_greater_precedence, Basic) {
  ASSERT_TRUE(is_greater_precedence("/", "+"));
  ASSERT_TRUE(is_greater_precedence("/", "-"));
  ASSERT_TRUE(is_greater_precedence("/", "("));
  ASSERT_TRUE(is_greater_precedence("/", ")"));
  ASSERT_TRUE(is_greater_precedence("/", "diksa"));

  ASSERT_TRUE(is_greater_precedence("*", "+"));
  ASSERT_TRUE(is_greater_precedence("*", "-"));
  ASSERT_TRUE(is_greater_precedence("*", "("));
  ASSERT_TRUE(is_greater_precedence("*", ")"));
  ASSERT_TRUE(is_greater_precedence("*", "asdf"));

  ASSERT_TRUE(is_greater_precedence("+", "("));
  ASSERT_TRUE(is_greater_precedence("+", ")"));
  ASSERT_TRUE(is_greater_precedence("+", "dkjiwo"));
  ASSERT_TRUE(is_greater_precedence("-", "("));
  ASSERT_TRUE(is_greater_precedence("-", ")"));
  ASSERT_TRUE(is_greater_precedence("-", "xckkw"));

  ASSERT_FALSE(is_greater_precedence("+", "*"));
  ASSERT_FALSE(is_greater_precedence("+", "/"));

  ASSERT_FALSE(is_greater_precedence("-", "*"));
  ASSERT_FALSE(is_greater_precedence("-", "/"));

  ASSERT_FALSE(is_greater_precedence("(", "*"));
  ASSERT_FALSE(is_greater_precedence("(", "/"));
  ASSERT_FALSE(is_greater_precedence("(", "+"));
  ASSERT_FALSE(is_greater_precedence("(", "-"));
  ASSERT_FALSE(is_greater_precedence("(", "klsd"));

  ASSERT_FALSE(is_greater_precedence(")", "*"));
  ASSERT_FALSE(is_greater_precedence(")", "/"));
  ASSERT_FALSE(is_greater_precedence(")", "+"));
  ASSERT_FALSE(is_greater_precedence(")", "-"));
  ASSERT_FALSE(is_greater_precedence(")", "klsd"));

  for (auto x : gen_vofstr("+", "-", "*", "/", "(", ")", "adiq")) {
    ASSERT_FALSE(is_greater_precedence(x, x));
  }
}

////////////////////////////////////////////////////////////////////////////////
// SyntaxTree tests
////////////////////////////////////////////////////////////////////////////////

TEST(SyntaxTree, ConstructionAndAssignment) {
  SyntaxTree st1;
  // SyntaxTree st2 {st1}; // not allowed
  SyntaxTree st3{std::move(st1)};
  // SyntaxTree st4 = st3; // not allowed
  SyntaxTree st5 = std::move(st3);

  SyntaxTree st{"1", ArithmeticNotation::PREFIX};
}


// TEST(SyntaxTree, BuildingTreeFromDifferentNotation) { SyntaxTree st{"1"}; }