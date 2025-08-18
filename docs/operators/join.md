# Join

## join

```cpp title="Signature"
template <
    typename TOtherRange,
    typename TKeySelectorA,
    typename TKeySelectorB,
    typename TTransform
>
constexpr auto join(
    const TOtherRange& other_range,
    TKeySelectorA&&    key_selector_a,
    TKeySelectorB&&    key_selector_b,
    TTransform&&       transform ) const;
```

```cpp title="Example" linenums="1"
const auto people1 = std::vector {
    Person{ .name = "Person 1", .age = 20 },
    Person{ .name = "Person 2", .age = 21 },
    Person{ .name = "Person 3", .age = 22 },
};

const auto people2 = std::vector {
    Person{ .name = "Person 1", .age = 22 },
    Person{ .name = "Person 3", .age = 23 },
    Person{ .name = "Person 1", .age = 26 },
};

const auto query = linq::from( &people1 )
                   .join(
                   linq::from( &people2 ),
                   []( const Person& p ) { return p.name; },
                   []( const Person& p ) { return p.name; },
                   []( const Person& a, const Person& b ) {
                       return Person {
                           .name = a.name + b.name,
                           .age  = a.age + b.age,
                       };
                   } );

// query =
//   [0] = { "Person 1Person 1"; 42 }
//   [1] = { "Person 1Person 1"; 46 }
//   [2] = { "Person 3Person 3"; 45 }
```
