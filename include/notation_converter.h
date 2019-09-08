#ifndef NOTATION_CONVERTER_H
#define NOTATION_CONVERTER_H

#include <string>

enum class ArithmeticNotation { PREFIX, INFIX, POSTFIX };

class NotationConverter {
 public:
  NotationConverter() = default;

  NotationConverter(const std::string& expr, ArithmeticNotation notation) 
  {
    insert(expr, notation);
  }

  void insert(const std::string& expr, ArithmeticNotation notation) 
  {
    expr_ = expr;
    notation_ = notation; 
  }

  std::string convert(ArithmeticNotation notation) {
    if (notation_ == notation) {
      return expr_;
    } 

    return "";
  };
private:
  std::string expr_;
  ArithmeticNotation notation_;
};

#endif  // NOTATION_CONVERTER_H
