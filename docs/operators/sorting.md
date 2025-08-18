# Sorting

## order_by

Sorts the range using a key selector function (`key_selector`) according to a direction
(`sort_dir`).

`key_selector` must be a function that takes the range's elements as input and returns a
value of an arbitrary type, i.e. $f(x) \mapsto y$. The result value (of type `y`) is then
used as the sorting key in the subsequent sorting algorithm.

`sort_dir` specifies whether the elements are sorted in ascending or descending order.

Comparison is done using `operator<` between elements of type `y`.

```cpp title="Signature"
template <typename TKeySelector>
constexpr auto order_by( TKeySelector&& key_selector, sort_direction sort_dir ) const;
```

```cpp title="Example" linenums="1"
const auto words = std::vector{ "hello"s, "world"s, "here"s,
                                "are"s, "some"s, "sorted"s, "words"s };
                                
const auto result = linq::from( &words )
                   .order_by( linq::size, linq::sort_direction::ascending )
                   .to_vector();

assert( result == std::vector{ "are"s, "here"s, "some"s,
                               "hello"s, "world"s, "words"s, "sorted"s } );
```

## then_by

Sorts a range that was produced by `order_by` and serves to apply subsequent sorting criteria.

A `then_by` operation can **only** be applied to a `order_by` range.

Applying this operator to another kind of range will result in a compile-time error.

```cpp title="Signature"
template <typename TKeySelector>
constexpr auto then_by( TKeySelector&& key_selector, sort_direction sort_dir ) const;
```

```cpp title="Example" linenums="1"
const auto words = std::vector{ "hello"s, "world"s, "here"s,
                                "are"s, "some"s, "sorted"s, "words"s };
                                
const auto result = linq::from( &words )
                   .order_by_ascending( linq::size )  // convenience function ..._by_ascending
                   .then_by_ascending( linq::self )   // same here, but with then_by
                   .to_vector();

assert( result == std::vector{ "are"s, "here"s, "some"s,
                               "hello"s, "words"s, "world"s, "sorted"s } );
```

## reverse

Reverses the order of the range.

```cpp title="Signature"
constexpr auto reverse() const;
```

```cpp title="Example" linenums="1"
const auto numbers = std::vector{ 1, 2, 3, 4 };

const auto result = linq::from( &numbers )
                   .reverse()
                   .to_vector();

assert( result.size() == 4 );
assert( result == std::vector{ 4, 3, 2, 1 } );
```
