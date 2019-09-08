#include "notation_converter_util.h"
#include "arithmetic_notation.h"
#include <string>

namespace notation_conv {
namespace detail {

std::string from_infix_to_prefix(const std::string& infix_expr) { return ""; }
std::string from_postfix_to_prefix(const std::string& prefix_expr) {
  return "";
}
std::string from_prefix_to_infix(const std::string& prefix_expr) { return ""; }
std::string from_prefix_to_postfix(const std::string& prefix_expr) {
  return "";
}

std::string to_prefix(const std::string& expr,
                      ArithmeticNotation from_notation) {
  switch (from_notation) {
    case ArithmeticNotation::PREFIX:
      return expr;
    case ArithmeticNotation::INFIX:
      return from_infix_to_prefix(expr);
    case ArithmeticNotation::POSTFIX:
      return from_postfix_to_prefix(expr);
  }
}

std::string from_prefix(const std::string& prefix_expr,
                        ArithmeticNotation to_notation) {
  switch (to_notation) {
    case ArithmeticNotation::PREFIX:
      return prefix_expr;
    case ArithmeticNotation::INFIX:
      return from_prefix_to_infix(prefix_expr);
    case ArithmeticNotation::POSTFIX:
      return from_prefix_to_postfix(prefix_expr);
  }
}

};  // namespace detail
};  // namespace notation_conv
