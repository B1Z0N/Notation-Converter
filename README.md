# Notation Converter

Class for converting from one arithmetical notation to another. 

# Notation types

- [Prefix](https://en.wikipedia.org/wiki/Polish_notation)
- [Infix](https://en.wikipedia.org/wiki/Infix_notation)
- [Postifx](https://en.wikipedia.org/wiki/Reverse_Polish_notation)

# Installation and testing

It is one header class, so just include appropriate file named `notation_converter.h` in `inculde/` directory.

To run the tests(assuming you are in root repo directory):
```bash
mkdir build  # or mybuild
cd build
cmake ..
make
./run_tests
```

# How to

For user there are to main classes in this project:
1. `NotationConverter`
1. `ArithmeticNotation`

Second one is just `enum class` denoting one of [types of notation](#notation-types). And the second is a converter. 
Use it like this:
```c++
#include <iostream>
#include <string>

#include "notation_converter.h"

std::string expr {"1 + 2 * ( 3 - 2 )"};
NotationConverter nc {expr, ArithemticNotation::INFIX};

std::cout << nc.convert(ArithemticNotation::PREFIX) << '\n';    // "+ 1 * 2 - 3 2"
std::cout << nc.convert(ArithemticNotation::INFIX) << '\n';     // "1 + 2 * ( 3 - 2 )"
std::cout << nc.convert(ArithemticNotation::POSTFIX) << '\n';   // "1 2 3 2 - * +"

```

# Note

This repository is a pet-pet project to learn TDD.
