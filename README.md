# Notation Converter

Class for converting from one arithmetical notation to another. 

# Notation types

- [Prefix](https://en.wikipedia.org/wiki/Polish_notation)
- [Infix](https://en.wikipedia.org/wiki/Infix_notation)
- [Postifx](https://en.wikipedia.org/wiki/Reverse_Polish_notation)

# Installation and testing

It is one header class, so just include appropriate file named `notation_converter.h` in `inculde/` directory.

To run the tests(assuming you are in the root repository directory):
```bash
mkdir build  # or mybuild
cd build
cmake ..
make
./run_tests
```

# Using in your project

From previous step you can find static library generated in `build` directory. File named `libnotaconv.a` is a static library. So you should link this to your cpp-program and also add an include path which is `include` folder in the project's root. 

## Manually

```c++
// use.cpp

#include "notation_converter.h"

#include <iostream>

using namespace notaconv;

int main() {
    NotationConverter nc {"+ 1 1", ArithmeticNotation::PREFIX};
    std::cout << nc.convert(ArithmeticNotation::INFIX) << '\n';
}
```

And compile-link-run it like this(gcc example):

```bash
> g++ use.cpp -I"${PROJECT_DIR}/inculde" ${PROJECT_DIR}/build/libnotaconv.a -o use
> ./use
> 1 + 1
```

Where `${PROJECT_DIR}` is a path to this project's directory.

## CMake

Add this lines to your `CMakeLists.txt`:

```cmake
include_directories(${NOTACONV_PROJECT_DIR}/include)
link_directories(${NOTACONV_PROJECT_DIR}/build)
...
...
...
target_link_libraries(executable notaconv)
```

Where `${NOTACONV_PROJECT_DIR}` is a path to this project's directory, and `executable` is your target specified in `add_executable(executable ${SOURCES})` function call.

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

using namespace notaconv;

std::string expr {"1 + 2 * ( 3 - 2 )"}; // necessary to have a space between two items
NotationConverter nc {expr, ArithemticNotation::INFIX};

std::cout << nc.convert(ArithemticNotation::PREFIX) << '\n';    // "+ 1 * 2 - 3 2"
std::cout << nc.convert(ArithemticNotation::INFIX) << '\n';     // "1 + 2 * ( 3 - 2 )"
std::cout << nc.convert(ArithemticNotation::POSTFIX) << '\n';   // "1 2 3 2 - * +"

```

# Note

This repository is a pet-pet project to learn TDD.
