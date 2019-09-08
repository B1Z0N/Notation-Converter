#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <string>

#include "arithmetic_notation.h"

namespace notation_conv {
namespace detail {

class SyntaxTree {
 public:
  SyntaxTree() = default;

  SyntaxTree(const std::string& expr, ArithmeticNotation notation);

  std::string to_notation(ArithmeticNotation notation);

 private:
  struct Node {
    void nodify(const std::string& expr, ArithmeticNotation notation);
    void stringify(ArithmeticNotation notation);

   private:
    Node* left_;
    Node* right_;
    std::string data_;

    void nodify_from_prefix(const std::string& expr);
    void nodify_from_infix(const std::string& expr);
    void nodify_from_postfix(const std::string& expr);

    std::string stringify_to_prefix(ArithmeticNotation notation);
    std::string stringify_to_infix(ArithmeticNotation notation);
    std::string stringify_to_postfix(ArithmeticNotation notation);
  };
};

};  // namespace detail
};  // namespace notation_conv

#endif  // SYNTAX_TREE_H
