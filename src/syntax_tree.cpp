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

std::vector<std::string> split(const std::string& str) {
  std::vector<std::string> contatiner;
  std::istringstream iss{str};
  std::copy(std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{},
            std::back_inserter(contatiner));

  return contatiner;
}

void trim(std::string& str) {
  // trim from start (in place)
  static auto ltrim{[](std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    [](int ch) { return !std::isspace(ch); }));
  }};

  // trim from end (in place)
  static auto rtrim{[](std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](int ch) { return !std::isspace(ch); })
                .base(),
            s.end());
  }};

  // trim from both ends (in place)
  ltrim(str);
  rtrim(str);
}

bool is_operator(const std::string& str) {
  return (((str[0] == '+') || (str[0] == '-') || (str[0] == '*') ||
           (str[0] == '/')) &&
          (str.size() == 1));
}

bool is_greater_precedence(const std::string& op1, const std::string& op2) {
  static auto precedence{[](const std::string& op) -> int {
    if (op == "+" || op == "-") {
      return 2;
    } else if (op == "/" || op == "*") {
      return 1;
    } else if (op == "(" || op == ")") {
      return 3;
    }
    return 0;
  }};

  // lowest comes first
  return precedence(op1) < precedence(op2);
}

SyntaxTree::SyntaxTree(const std::string& expr, ArithmeticNotation notation) {
  tree_.nodify(expr, notation);
}

std::string SyntaxTree::to_notation(ArithmeticNotation notation) const {
  return tree_.stringify(notation);
}

void SyntaxTree::Node::nodify(const std::string& expr,
                              ArithmeticNotation notation) {
  std::vector<std::string> vec{split(expr)};
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

std::string SyntaxTree::Node::stringify(ArithmeticNotation notation) const {
  std::string res;
  switch (notation) {
    case ArithmeticNotation::PREFIX: {
      res = stringify_to_prefix();
      break;
    }
    case ArithmeticNotation::INFIX: {
      res = stringify_to_infix();
      break;
    }
    case ArithmeticNotation::POSTFIX: {
      res = stringify_to_postfix();
      break;
    }
  }

  trim(res);
  return res;
}

void SyntaxTree::Node::nodify_from_prefix(
    const std::vector<std::string>& splited) {
  std::stack<Node*> st;
  st.push(this);

  for (std::size_t i = 0; i < splited.size() && !st.empty(); ++i) {
    Node* nd = st.top();
    st.pop();
    nd->data_ = splited[i];

    if (is_operator(nd->data_)) {
      nd->left_ = new Node{};
      nd->right_ = new Node{};

      st.push(nd->right_);
      st.push(nd->left_);
    }
  }
}

void SyntaxTree::Node::nodify_from_infix(
    const std::vector<std::string>& splited) {
  // shunting yard algo
  static auto from_infix_to_postfix{
      [](const std::vector<std::string>& splited) {
        std::stack<std::string> st;
        std::vector<std::string> postfix;

        for (std::size_t i = 0; i < splited.size(); ++i) {
          std::string token = splited[i];

          if (is_operator(token)) {
            while (!st.empty() && (is_greater_precedence(st.top(), token) ||
                                   token == st.top())) {
              postfix.push_back(st.top());
              st.pop();
            }
            st.push(token);
          } else if (token == "(") {
            st.push(token);
          } else if (token == ")") {
            while (st.top() != "(" && !st.empty()) {
              postfix.push_back(st.top());
              st.pop();
            }

            if (st.empty())
              throw std::underflow_error{"Left paren is missing!"};
            st.pop();
          } else {  // just a number
            postfix.push_back(token);
          }
        }

        while (!st.empty()) {
          postfix.push_back(st.top());
          st.pop();
        }

        return postfix;
      }};

  nodify_from_postfix(from_infix_to_postfix(splited));
}

void SyntaxTree::Node::nodify_from_postfix(
    const std::vector<std::string>& splited) {
  std::stack<Node*> st;
  st.push(this);

  for (int i = splited.size() - 1; i >= 0 && !st.empty(); --i) {
    Node* nd = st.top();
    st.pop();
    nd->data_ = splited[i];

    if (is_operator(nd->data_)) {
      nd->left_ = new Node{};
      nd->right_ = new Node{};

      st.push(nd->left_);
      st.push(nd->right_);
    }
  }
}

std::string SyntaxTree::Node::stringify_to_prefix() const {
  // trick with passing itself as a parameter is to
  // workaround compiler error:
  // "use of 'stringify' before deduction of auto"
  static auto stringify{[](const auto stringify, const Node* nd,
                           std::string& result_expr) -> void {
    if (nd == nullptr) return;
    result_expr += nd->data_ + " ";

    stringify(stringify, nd->left_, result_expr);
    stringify(stringify, nd->right_, result_expr);
  }};

  std::string result_expr;
  stringify(stringify, this, result_expr);
  return result_expr;
}

std::string SyntaxTree::Node::stringify_to_infix() const {
  // read more about the trick in "stringify_to_prefix"
  static auto stringify{[](const auto stringify, const Node* nd,
                           std::string& result_expr) -> void {
    if (nd == nullptr) return;

    if (nd->left_ != nullptr &&
        is_greater_precedence(nd->data_, nd->left_->data_)) {
      result_expr += "( ";
      stringify(stringify, nd->left_, result_expr);
      result_expr += ") ";
    } else {
      stringify(stringify, nd->left_, result_expr);
    }

    result_expr += nd->data_ + " ";

    if (nd->right_ != nullptr &&
        is_greater_precedence(nd->data_, nd->right_->data_)) {
      result_expr += "( ";
      stringify(stringify, nd->right_, result_expr);
      result_expr += ") ";
    } else {
      stringify(stringify, nd->right_, result_expr);
    }
  }};

  std::string result_expr;
  stringify(stringify, this, result_expr);
  return result_expr;
}

std::string SyntaxTree::Node::stringify_to_postfix() const {
  // read more about the trick in "stringify_to_prefix"
  static auto stringify{[](const auto stringify, const Node* nd,
                           std::string& result_expr) -> void {
    if (nd == nullptr) return;

    stringify(stringify, nd->left_, result_expr);
    stringify(stringify, nd->right_, result_expr);

    result_expr += nd->data_ + " ";
  }};

  std::string result_expr;
  stringify(stringify, this, result_expr);
  return result_expr;
}


SyntaxTree::Node::Node(Node&& nd) {
  *this = std::move(nd);
}

SyntaxTree::Node& SyntaxTree::Node::operator=(Node&& nd) {
  left_ = nd.left_;
  right_ = nd.right_;
  data_ = nd.data_;

  nd.left_ = nullptr;
  nd.right_ = nullptr;
  nd.data_ = "";

  return *this;
}

SyntaxTree::Node::~Node() {
  if (left_) delete left_;
  if (right_) delete right_;
}
};  // namespace detail
};  // namespace notation_conv
