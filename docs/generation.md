# Generation

## from_to

Produces a range that starts at `start` and stops at `stop` (inclusive) using a value of `step` with each step.

```cpp title="Signature"
template <typename T>
constexpr auto from_to( T&& start, T&& end, T&& step = T( 1 ) );
```

```cpp title="Example" linenums="1"
constexpr auto range1 = linq::from_to( 1, 5 );           // 1, 2, 3, 4, 5
constexpr auto range2 = linq::from_to( 1.0, 2.0, 0.5 );  // 1.0, 1.5, 2.0

static_assert( range1.sum() == 15 );
static_assert( range2.sum() == 4.5 );
```

!!! note
    `T` must represent a default-constructible type that supports `operator+=`, `operator<` and construction from `int`.

    This is illustrated by the following concept:

    ```cpp
    template <typename T>
    concept addable = requires( T a, T b ) {
        requires std::is_convertible_v<int, T>;
        { a += b } -> std::convertible_to<T>;
        { a < b } -> std::same_as<bool>;
    } || number<T>;
    ```

## repeat

Repeats the range `count` times.

```cpp title="Signature"
constexpr auto repeat( size_t count ) const;
```

```cpp title="Example" linenums="1"
constexpr auto range = linq::from_to( 0, 5 );

// never repeat
{
    const auto numbers = range.repeat( 0 ).to_vector();

    assert( numbers.size() == 6 );
    assert( numbers == std::vector{ 0, 1, 2, 3, 4, 5 } );
}

// repeat once
{
    const auto numbers = range.repeat( 1 ).to_vector();

    assert( numbers.size() == 12 );
    assert( numbers == std::vector{ 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5 } );
}
```

## generate

Produces a range using a `generator` function.

`generator` must be a function that either:

- A value to generate (`linq::generate_return()`) or
- A sentinel value to indicate the end of the generator (`linq::generate_finish()`)

```cpp title="Signature"
template <typename TGenerator>
constexpr auto generate( TGenerator&& generator );
```

```cpp title="Example" linenums="1"
constexpr auto range = linq::generate( []( const size_t iteration ) {
    if ( iteration < 10 ) {
        return linq::generate_return( iteration * 2 );
    }

    return linq::generate_finish<size_t>();
} );

static_assert( range.count() == 10 );

const auto list = range.to_vector();

assert( list == std::vector<size_t>{ 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 } );
```
