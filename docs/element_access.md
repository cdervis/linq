# Element Access

## element_at

Gets the element of the range at position `index` (zero-based).

```cpp title="Signature"
constexpr auto element_at( size_t index ) const -> std::optional<output_t>;
```

```cpp title="Example" linenums="1"
constexpr auto nums = std::array{ 1, 2, 3, 4 };

constexpr auto two = linq::from( &nums ).element_at( 1 );
constexpr auto sixth = linq::from( &nums ).element_at( 5 );

static_assert( two == 2 );
static_assert( !sixth );
```

## first

1. Gets the first element of the range. If the range is empty, an empty optional is produced.
2. Gets the first element of the range that satisfies a `predicate`. If the range is empty, or no element satisfied the predicate, an empty optional is produced.

```cpp title="Signature"
// 1.
constexpr auto first() const -> std::optional<output_t>;

// 2.
template <typename TPredicate>
constexpr auto first( const TPredicate& predicate ) const -> std::optional<output_t>;
```

```cpp title="Example" linenums="1"
constexpr auto nums = std::array{ 1, 2, 3, 4 };

constexpr auto one = linq::from( &nums ).first();

constexpr auto first_above_2 = linq::from( &nums )
                              .first( []( int value ) { return value > 2; } );
                              
constexpr auto first_above_4 = linq::from( &nums )
                              .first( []( int value ) { return value > 4; } );

static_assert( one == 1 );
static_assert( first_above_2 == 3 );
static_assert( !first_above_4 );
```

## last

1. Gets the last element of the range. If the range is empty, an empty optional is produced.
2. Gets the last element of the range that satisfies a `predicate`. If the range is empty, or no element satisfied the predicate, an empty optional is produced.

```cpp title="Signature"
// 1.
constexpr auto last() const -> std::optional<output_t>;

// 2.
template <typename TPredicate>
constexpr auto last( const TPredicate& predicate ) const -> std::optional<output_t>;
```

```cpp title="Example" linenums="1"
constexpr auto nums = std::array{ 1, 2, 3, 4 };

constexpr auto four = linq::from( &nums ).last();

constexpr auto last_above_2 = linq::from( &nums )
                             .last( []( int value ) { return value > 2; } );
                              
constexpr auto last_under_1 = linq::from( &nums )
                             .last( []( int value ) { return value < 1; } );

static_assert( four == 4 );
static_assert( last_above_2 == 4 );
static_assert( !last_under_1 );
```
