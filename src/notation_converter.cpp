#include "notation_converter.h"
#include "arithmetic_notation.h"
#include "syntax_tree.h"

#include <string>

namespace notaconv {

NotationConverter::NotationConverter(const std::string& expr,
                                     ArithmeticNotation notation)
    : tree_{expr, notation} {}

std::string NotationConverter::convert(ArithmeticNotation notation) const {
  return tree_.to_notation(notation);
};

};  // namespace notaconv
