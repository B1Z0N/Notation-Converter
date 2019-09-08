#ifndef NOTATION_CONVERTER_H
#define NOTATION_CONVERTER_H

#include "arithmetic_notation.h"
#include <string>

namespace notation_conv {

class NotationConverter {
 public:
  NotationConverter() = default;

  NotationConverter(const std::string& expr, ArithmeticNotation notation);

  void insert(const std::string& expr, ArithmeticNotation notation);

  std::string convert(ArithmeticNotation notation);

 private:
  std::string expr_{};
  ArithmeticNotation notation_{};

  std::string prefix_expr_{};
};
};  // namespace notation_conv

#endif  // NOTATION_CONVERTER_H
