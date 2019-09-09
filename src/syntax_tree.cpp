#include "syntax_tree.h"
#include "arithmetic_notation.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace notation_conv {
namespace detail {

std::vector<std::string> split(const std::string& s) {
  std::vector<std::string> contatiner;
  std::istringstream iss(s);
  std::copy(std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{},
            std::back_inserter{contatiner});

  return contatiner;
}

SyntaxTree::SyntaxTree(const std::string& expr, ArithmeticNotation notation) {
  node_.nodify(expr, notation);
}

std::string SyntaxTree::to_notation(ArithmeticNotation notation) {
  return node_.stringify(notation);
}

void SyntaxTree::Node::nodify(const std::string& expr,
                              ArithmeticNotation notation) {
  std::vector<std::string> vec = split(expr);
  switch (notation) {
    case ArithmeticNotation::PREFIX: {
      nodify_from_prefix(vec);
      break;
    }
    case ArithmeticNotation::INFIX: {
      nodify_from_infix(vec);
      break;
    }
    case ArithmeticNotation::POSTFIX: {
      nodify_from_postfix(vec);
      break;
    }
  }
}

std::string SyntaxTree::Node::stringify(ArithmeticNotation notation) {
  switch (notation) {
    case ArithmeticNotation::PREFIX:
      return stringify_to_prefix();
    case ArithmeticNotation::INFIX:
      return stringify_to_infix();
    case ArithmeticNotation::POSTFIX:
      return stringify_to_postfix();
  }
}

bool is_operator(std::string str) {
  return (str[0] == '+' || str[0] == '-' || str == '*' || str == '/') &&
         str.size() == 1;
}

void SyntaxTree::Node::nodify_from_prefix(
    const std::vector<std::string> splited) {
  std::stack<Node*> st;
  st.push(this);

  for (std::size_t i = 0; i < splited.size() && !st.empty(); ++i) {
    Node* nd = st.top();
    st.pop();
    nd.data_ = splited[i];

    if (is_operator(nd.data_)) {
      nd.left_ = new Node{};
      nd.right_ = new Node{};

      st.push(nd->right_);
      st.push(nd->left_);
    }
  }
}

void SyntaxTree::Node::nodify_from_infix(
    const std::vector<std::string>& splited) {
  // TODO: ???
}

void SyntaxTree::Node::nodify_from_postfix(
    const std::vector<std::string> splited) {
  std::stack<Node*> st;
  st.push(this);

  for (int i = splited.size() - 1; i >= 0 && !st.empty(); --i) {
    Node* nd = st.top();
    st.pop();
    nd.data_ = splited[i];

    if (is_operator(nd.data_)) {
      nd.left_ = new Node{};
      nd.right_ = new Node{};

      st.push(nd->left_);
      st.push(nd->right_);
    }
  }
}

std::string SyntaxTree::Node::stringify_to_prefix() {
  static auto stringify{[](Node* nd, std::string& result_expr) {
    if (nd == nullptr) return;
    result_expr += nd.data_ + " "s;

    stringify(nd->left, result_expr);
    stringify(nd->right, result_expr);

    return result_expr;
  }};

  std::string result_expr;
  stringify(this, result_expr);
  return result_expr;
}

std::string SyntaxTree::Node::stringify_to_infix() {}

std::string SyntaxTree::Node::stringify_to_postfix() {
  static auto stringify{[](Node* nd, std::string& result_expr) {
    if (nd == nullptr) return;

    stringify(nd->left, result_expr);
    stringify(nd->right, result_expr);

    result_expr += nd.data_ + " "s;
  }};

  std::string result_expr;
  stringify(this, result_expr);
  return result_expr;
}

void SyntaxTree::Node::~Node() {
  if (left_) delete left_;
  if (right_) delete right_;
}
};  // namespace detail
};  // namespace notation_conv
