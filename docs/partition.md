# Partition

## skip

Skips a specified number of elements in the range.

```cpp title="Signature"
constexpr auto skip( size_t count ) const;
```

```cpp title="Example" linenums="1"
constexpr auto numbers = std::array{ 1, 2, 3, 4, 5, 6 };

const auto result  = linq::from( &numbers )
                    .skip( 3 )
                    .to_vector();

static_assert( result.size() == 3 );
static_assert( result == std::vector{ 4, 5, 6 } );
```

## skip_while

Skips elements in the range while a specific `predicate` is satisfied.

The predicate is invoked per element, for which a `bool` is returned that indicates
whether the element satisfies it, i.e. $f(x) \mapsto bool$.

```cpp title="Signature"
template <typename TPredicate>
constexpr auto skip_while( TPredicate&& predicate ) const;
```

```cpp title="Example" linenums="1"
const auto numbers = std::vector{ 1, 2, 3, 4, 5, 6 };

const auto result  = linq::from( &numbers )
                    .skip_while( []( const int i ) { return i < 5; } );

static_assert( result.size() == 2 );
static_assert( result == std::vector{ 5, 6 } );
```

## take

Takes a specific number of elements of the range and discards the rest.

```cpp title="Signature"
constexpr auto take( size_t count ) const;
```

```cpp title="Example" linenums="1"
const auto numbers = std::vector{ 1, 2, 3, 4, 5, 6 };

const auto result  = linq::from( &numbers )
                    .take( 3 )
                    .to_vector();

static_assert( result.size() == 3 );
static_assert( result == std::vector{ 1, 2, 3 } );
```

## take_while

Takes elements of the range while a specific `predicate` is satisfied.

The predicate is invoked per element, for which a `bool` is returned that indicates
whether the element satisfies it, i.e. $f(x) \mapsto bool$.

```cpp title="Signature"
template <typename TPredicate>
constexpr auto take_while( TPredicate&& predicate ) const;
```

```cpp title="Example" linenums="1"
constexpr auto numbers = std::array{ 1, 2, 3, 4, 5, 6 };

constexpr auto result  = linq::from( &numbers )
                    .take_while( []( const int i ) { return i < 5; } );

static_assert( result.size() == 4 );
static_assert( result == std::vector{ 1, 2, 3, 4 } );
```




