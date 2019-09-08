#include "notation_converter.h"
#include "arithmetic_notation.h"
#include "syntax_tree.h"

#include <string>

namespace notation_conv {

NotationConverter::NotationConverter(const std::string& expr,
                                     ArithmeticNotation notation) {
  insert(expr, notation);
}

void NotationConverter::insert(const std::string& expr,
                               ArithmeticNotation notation) {
  expr_ = expr;
  notation_ = notation;
  prefix_expr_ = "";
}

std::string NotationConverter::convert(ArithmeticNotation notation) {
  if (notation == notation_) {
    return expr_;
  }

  if (prefix_expr_.empty()) {
    // prefix_expr_ = detail::to_prefix(expr_, notation_);
  }

  // return detail::from_prefix(prefix_expr_, notation);
  return "";
};

};  // namespace notation_conv
