# Filters

## where

Appends a filter to the range, dropping elements that don't satisfy a specific predicate.

`predicate` must be a function `f` that takes the range's element `x` and returns a value indicating
whether the condition is satisfied, i.e. $f(x) \mapsto bool$.

```cpp title="Signature"
template <typename TPredicate>
constexpr auto where( TPredicate&& predicate ) const;
```

```cpp title="Example" linenums="1"
const auto people = std::vector{
    Person{ .name = "Person 1", .age = 20 },
    Person{ .name = "Person 2", .age = 21 },
    Person{ .name = "Person 3", .age = 22 },
};

const auto query = linq::from( &people )
                  .where( []( const Person& p ) { return p.age > 20; } );
                  
//               = Person 2, Person 3
```
