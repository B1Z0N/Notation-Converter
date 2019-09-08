#ifndef NOTATION_CONVERTER_H
#define NOTATION_CONVERTER_H

#include <string>

#include "notation_converter_util.h"

namespace notation_conv {

enum class ArithmeticNotation { PREFIX, INFIX, POSTFIX };

class NotationConverter {
 public:
  NotationConverter() = default;

  NotationConverter(const std::string& expr, ArithmeticNotation notation) {
    insert(expr, notation);
  }

  void insert(const std::string& expr, ArithmeticNotation notation) {
    expr_ = expr;
    notation_ = notation;
  }

  std::string convert(ArithmeticNotation notation) {
    if (notation_ == notation) {
      return expr_;
    }
    return expr_;
  };

 private:
  std::string expr_ {};
  ArithmeticNotation notation_ {};

  std::string prefix_expr_ {};
};
};  // namespace notation_conv

#endif  // NOTATION_CONVERTER_H
