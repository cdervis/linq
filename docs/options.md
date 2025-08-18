# Options

linq can be configured via preprocessor `#define`s.

These options must be defined prior to including `linq.hpp`, or as a global compiler define.

Example:

=== "In C++"

    ```cpp
    #define LINQ_NO_ASSERTIONS
    #include <linq.hpp>

    // ...
    ```

=== "In CMake"

    ```cmake
    target_link_libraries( MyApp PRIVATE linq )

    target_compile_definitions( MyApp PRIVATE
        -DLINQ_NO_ASSERTIONS
        -DLINQ_NO_STL_CONTAINERS
    )
    ```

---

## `LINQ_NO_STL_CONTAINERS` 

If defined, linq will not include and use any STL containers,
such as `std::array`, `std::vector` and `std::unordered_map`.

If you're not using STL containers in your codebase anyway, you may specify enable this
option to reduce compilation times.

---

## `LINQ_NO_ASSERTIONS`

If defined, linq will not perform any assertions. The default assertion mechanism in linq is the `assert()` macro
from `<cassert>`.

You may specify a custom assertion macro by using `#define LINQ_ASSERT`.

Example:

=== "Disabling assertions"
    ```cpp
    #define LINQ_NO_ASSERTIONS
    #include <linq.hpp>
    ```

=== "Custom assertions"
    ```cpp
    #define LINQ_ASSERT(...) myOwnAssert( __VA_ARGS__ )
    #include <linq.hpp>
    ```

!!! note

    If you specify your own `LINQ_ASSERT` macro, then `LINQ_NO_ASSERTIONS` is overwritten, and linq
    will always perform assertions using your `LINQ_ASSERT` macro.


