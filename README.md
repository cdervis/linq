# linq - LINQ for C++

![logo](docs/img/logo.png)

linq is a header-only LINQ library for C++ 17 and newer.

It has no dependencies and neatly integrates into the STL by taking advantage of modern C++ features.

- offers a simpler alternative to C++20 `<ranges>`
- resolves all type related functionality at compile-time; no virtual dispatch is used
- uses lazy evaluation, so your queries still work even after you modify the container they're based on
- focuses on immutability, so your queries stay predictable by minimizing surprising side-effects
- is efficient in the way it works with your data; it avoids copies and instead moves data wherever it can
- generates an operation chain at compile-time (supports `constexpr`)
- works with all generic container types, not just the STL

---

## Documentation

The documentation is available on the [home page](https://dervis.de/linq).

## Example

```cpp linenums="1"
#include <linq.hpp>
#include <print>
#include <string>
#include <vector>

struct Person {
  std::string name;
  int age;
};
  
int main() {
    auto people = std::vector<Person> {
        { "Person 1", 20 },
        { "Person 2", 21 },
        { "Person 3", 22 }
    };
  
    auto query = linq::from( &people )
                .where( []( const Person& p ) { return p.age > 20; } )
                .select( []( const Person& p ) { return p.name; } );
  
    for ( const auto& name : query )
        std::println( "{}", name );
  
    return 0;
}
```

Output:

```
Person 2
Person 3
```
