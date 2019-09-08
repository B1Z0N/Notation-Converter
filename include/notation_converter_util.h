#ifndef NOTATION_CONVERTER_UTIL_H
#define NOTATION_CONVERTER_UTIL_H

#include <string>

#include "arithmetic_notation.h"

namespace notation_conv {
namespace detail {

std::string from_infix_to_prefix(const std::string& infix_expr);
std::string from_postfix_to_prefix(const std::string& prefix_expr);
std::string from_prefix_to_infix(const std::string& prefix_expr);
std::string from_prefix_to_postfix(const std::string& prefix_expr);

std::string to_prefix(const std::string& expr,
                      ArithmeticNotation from_notation);

std::string from_prefix(const std::string& prefix_expr,
                        ArithmeticNotation to_notation);

};  // namespace detail
};  // namespace notation_conv

#endif  // NOTATION_CONVERTER_UTIL_H
