#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <string>
#include <unordered_set>
#include <vector>

#include "arithmetic_notation.h"

namespace notation_conv {
namespace detail {

std::vector<std::string> split(const std::string& s);
void trim(std::string& s);

bool is_operator(const std::string& s);
bool is_greater_precedence(const std::string& op1, const std::string& op2);

class SyntaxTree {
 public:
  SyntaxTree() = default;
  SyntaxTree(SyntaxTree&&) = default;
  SyntaxTree& operator=(SyntaxTree&&) = default;
  SyntaxTree(const SyntaxTree&) = delete;
  SyntaxTree& operator=(const SyntaxTree&) = delete;

  SyntaxTree(const std::string& expr, ArithmeticNotation notation);

  std::string to_notation(ArithmeticNotation notation) const;

 private:
  struct Node {
    Node() = default;
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;

    Node(Node&&);
    Node& operator=(Node&&);
    ~Node();

    void nodify(const std::string& expr, ArithmeticNotation notation);
    std::string stringify(ArithmeticNotation notation) const;

   private:
    Node* left_{};
    Node* right_{};
    std::string data_{};

    void nodify_from_prefix(const std::vector<std::string>& splited);
    void nodify_from_infix(const std::vector<std::string>& splited);
    void nodify_from_postfix(const std::vector<std::string>& splited);

    std::string stringify_to_prefix() const;
    std::string stringify_to_infix() const;
    std::string stringify_to_postfix() const;

    static Node* exception_aware_alloc(); 
  };
  Node tree_;
};

};  // namespace detail
};  // namespace notation_conv

#endif  // SYNTAX_TREE_H
