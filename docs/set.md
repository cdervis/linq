# Set

## distinct

Computes the unique values of the range.

Elements are compared using `operator==` in a nested linear search.

```cpp title="Signature"
constexpr auto distinct() const;
```

```cpp title="Example" linenums="1"
constexpr auto nums = std::array{ 1, 2, 3, 3, 5, 4, 5, 6, 7 };

const auto unique_nums = linq::from( &nums )
                        .distinct()
                        .to_vector();

assert( unique_nums.size() == 7 );
assert( unique_nums == std::vector{ 1, 2, 3, 5, 4, 6, 7 } );
```

!!! note
    This operator may dynamically allocate heap memory.
