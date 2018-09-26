# CPPUT

A tiny cpp unit test framework for myself. It's for quick start, only 1 header and 1 cpp file. Coping to a repo finishs the setup.

See `src/example.cpp` to get a few examples.

## Quick Get Started

1. Put `src/cpput.hpp` and `src/cpput.cc` into your project

2. In the test code

``` c++
// include header:
#include "cpput.hpp"

// define a test case
TEST(TestGroup, TestCase) {
    // do your case
    // ...
    // check result
    EQ_(result,
}
```

## Supported Assertions

- `OK_(exp)` expect `exp` is true
- `NO_(exp)` expect `exp` is false
- `EQ_(exp1, exp2)` expect `exp1 == exp2`
- `NE_(exp1, exp2)` expect `exp1 != exp2`
- `LE_(exp1, exp2)` expect `exp1 <= exp2`
- `LT_(exp1, exp2)` expect `exp1 < exp2`
- `GE_(exp1, exp2)` expect `exp1 >= exp2`
- `GT_(exp1, exp2)` expect `exp1 > exp2`
