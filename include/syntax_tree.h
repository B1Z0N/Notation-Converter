#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "arithmetic_notation.h"

namespace notation_conv {
namespace detail {

template <typename C>
C split(const std::string& s) {
  C contatiner;
  std::istringstream iss(s);
  std::copy(std::istream_iterator<std::string>{iss},
            std::istream_iterator < std::string{},
            std::back_inserter{contatiner});

  return contatiner;
}

class SyntaxTree {
 public:
  SyntaxTree() = default;

  SyntaxTree(const std::string& expr, ArithmeticNotation notation);

  std::string to_notation(ArithmeticNotation notation);

 private:
  struct Node {
    void nodify(const std::string& expr, ArithmeticNotation notation) {
      switch (notation) {
        case ArithmeticNotation::PREFIX: {
          nodify_from_prefix(expr);
          break;
        }
        case ArithmeticNotation::INFIX: {
          nodify_from_infix(expr);
          break;
        }
        case ArithmeticNotation::POSTFIX: {
          nodify_from_postfix(expr);
          break;
        }
      }
    }

    std::string stringify(ArithmeticNotation notation) {
      switch (notation) {
        case ArithmeticNotation::PREFIX: return stringify_to_prefix();
        case ArithmeticNotation::INFIX: return stringify_to_infix();
        case ArithmeticNotation::POSTFIX: return stringify_to_postfix();
      }
    }

   private:
    Node* left_;
    Node* right_;
    std::string data_;

    void nodify_from_prefix(const std::string& expr);
    void nodify_from_infix(const std::string& expr);
    void nodify_from_postfix(const std::string& expr);

    std::string stringify_to_prefix();
    std::string stringify_to_infix();
    std::string stringify_to_postfix();
  };
  Node* node;
};

};  // namespace detail
};  // namespace notation_conv

#endif  // SYNTAX_TREE_H
