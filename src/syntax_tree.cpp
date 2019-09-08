#include "syntax_tree.h"
#include "arithmetic_notation.h"

#include <string>

namespace notation_conv {
namespace detail {

SyntaxTree::SyntaxTree(const std::string& expr, ArithmeticNotation notation) {
  nodify(expr, notation);
}

std::string SyntaxTree::to_notation(ArithmeticNotation notation) {
  return node.stringify(notation);
}

void SyntaxTree::Node::nodify_from_prefix(const std::string& expr) {

}
void SyntaxTree::Node::nodify_from_infix(const std::string& expr) {

}
void SyntaxTree::Node::nodify_from_postfix(const std::string& expr) {

}

std::string SyntaxTree::Node::stringify_to_prefix() {

}
std::string SyntaxTree::Node::stringify_to_infix() {

}
std::string SyntaxTree::Node::stringify_to_postfix() {

}

};  // namespace detail
};  // namespace notation_conv
