#ifndef NOTATION_CONVERTER_H
#define NOTATION_CONVERTER_H

#include <string>
#include "arithmetic_notation.h"
#include "syntax_tree.h"

namespace notaconv {

class NotationConverter {
 public:
  NotationConverter() = default;
  NotationConverter(NotationConverter&&) = default;
  NotationConverter& operator=(NotationConverter&&) = default;
  NotationConverter(const NotationConverter&) = delete;
  NotationConverter& operator=(const NotationConverter*) = delete;

  NotationConverter(const std::string& expr, ArithmeticNotation notation);

  std::string convert(ArithmeticNotation notation) const;

 private:
  detail::SyntaxTree tree_;
};

};  // namespace notaconv

#endif  // NOTATION_CONVERTER_H
