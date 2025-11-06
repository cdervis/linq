# Aggregation

## aggregate

Applies an accumulator function `func` over the range and produces a single, accumulated result,
i.e. $f(a, b) \mapsto R$.

The initial value is specified by the `seed` parameter.

```cpp title="Signature"
template <typename TSeed, typename TAccumFunc>
constexpr auto aggregate( TSeed seed, TAccumFunc&& func ) const;
```

```cpp title="Example" linenums="1"
constexpr auto numbers = std::array{ 1, 2, 3, 4 };

constexpr auto result1 = linq::from( &numbers )
                        .aggregate( 0, []( int a, int b ) { return a + b; } );
                      
constexpr auto result2 = linq::from( &numbers )
                        .aggregate( 2, std::plus() );

constexpr auto result3 = linq::from( &numbers )
                        .aggregate( 2, std::multiplies() );

static_assert( result1 == 10 ); // 1 + 2 + 3 + 4
static_assert( result2 == 12 ); // 2 + (1 + 2 + 3 + 4)
static_assert( result3 == 48 ); // 2 * (1 * 2 * 3 * 4)
```

---

## reduce

Applies an accumulator function `func` over the range and produces a single, accumulated result,
i.e. $f(a, b) \mapsto R$.

The starting value is a default-constructed object of the range's output type.

```cpp title="Signature"
template <typename TAccumFunc>
constexpr auto reduce( const TAccumFunc& func ) const;
```

```cpp title="Example" linenums="1"
constexpr auto nums = std::array{ 1, 2, 3, 4 };

constexpr auto sum1 = linq::from( &nums )
                     .reduce( std::plus() );

constexpr auto sum2 = linq::from( &nums )
                     .reduce( [](int a, int b) { return a + b; } );
                     
constexpr auto product = linq::from( &nums )
                        .reduce( std::multiplies() );

static_assert( sum1 == 10 );
static_assert( sum2 == 10 );
static_assert( product == 24 );
```

---

## average

Computes the average value of the range.

```cpp title="Signature"
constexpr auto average() const;
```

```cpp title="Example" linenums="1"
constexpr auto nums = std::array{ 1, 2, 3, 4 };

constexpr auto avg = linq::from( &nums ).average();

static_assert( avg == 2.5 ); // avg is of type double

const auto average_age = linq::from( &people )
                        .select( []( const Person& p ) { return p.age; } )
                        .average();
```

!!! note
    The range's input element type must be averageable, which can be expressed by the following concept:

    ```cpp
    template <typename T>
    concept averageable = requires( T a, T b, size_t c ) {
        requires std::is_default_constructible_v<T>;
        { a / c } -> std::same_as<T>;
        a += b;
    } || number<T>;
    ```

---

## count

1. Counts the number of elements in the range.
2. Counts the number of elements in the range that satisfy a predicate. The `predicate` is a
   function $f(x) \mapsto bool$.

```cpp title="Signatures"
// 1.
constexpr auto count() const -> size_t;

// 2.
template <typename TPredicate>
constexpr auto count( const TPredicate& predicate ) const -> size_t;
```

```cpp title="Example" linenums="1"
size_t number_of_people = linq::from( &people )
                         .count();

size_t number_of_people_over_20 = linq::from( &people )
                                 .count( []( const Person& p ) { return p.age > 20; } );
```

---

## max

Computes the maximum value of the range.

Comparison is done using the element type's `operator<`.

```cpp title="Signature"
constexpr auto max() const;
```

```cpp title="Example" linenums="1"
constexpr auto nums   = std::array{ 1, 2, 3, 4 };
constexpr auto result = linq::from( &nums ).max();
static_assert( result == 4 );
```

---

## min

Computes the minimum value of the range.

Comparison is done using the element type's `operator<`.

```cpp title="Signature"
constexpr auto min() const;
```

```cpp title="Example" linenums="1"
constexpr auto nums   = std::array{ 1, 2, 3, 4 };
constexpr auto result = linq::from( &nums ).min();
static_assert( result == 1 );
```

---

## sum

Computes the value sum of the range.

```cpp title="Signature"
constexpr auto sum() const;
```

```cpp title="Example" linenums="1"
constexpr auto nums = std::array{ 1, 2, 3, 4 };

constexpr auto sum = linq::from( &nums )
                    .where( []( int value ) { return value > 1; } )
                    .sum();
                    
static_assert( sum == 9 ); // 2 + 3 + 4

constexpr auto letters = std::array{ 'h', 'e', 'l', 'l', 'o', ' ',
                                     'w', 'o', 'r', 'l', 'd' };

const auto words = linq::from( &letters )
.select_to_string()
.reduce( std::plus() );

assert( words == "hello world" );
```

---

## sum_and_count

Computes the value sum of the range, and additionally returns the number of elements in the range.

The result is of type `std::optional<std::pair<T, U>>`, where `T` is the value sum, and `U` is the
number of elements.

```cpp title="Signature"
constexpr auto sum_and_count() const -> std::optional<std::pair<...>>;
```
