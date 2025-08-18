# Quantifiers

## all

Computes whether all elements of the range satisfy a `predicate`.

`predicate` must be a function that takes the range's element as input, and
returns a `bool` indicating whether that element satisfied it, i.e. $f(x) \mapsto bool$.

The operator has a complexity of $O(N)$, where `N` is the number of elements searched.

The search finishes as soon as an element does **not** satisfy the predicate.

```cpp title="Signature"
template <typename TPredicate>
constexpr auto all( const TPredicate& predicate ) const -> bool;
```

```cpp title="Example" linenums="1"
static_assert(
    linq::from( { 4, 3, 4, 3, 3 } )
    .all( []( int i ) { return i > 2; } )
);

static_assert(
    linq::from( std::initializer_list<int>() )
    .all( []( const int i ) { return i > 2; } )
);

static_assert(
    !linq::from( { 4, 3, 4, 3, 3, 1 } )
    .all( []( int i ) { return i > 2; } )
);
```

## any

Computes whether any element of the range satisfies a `predicate`.

`predicate` must be a function that takes the range's element as input, and
returns a `bool` indicating whether that element satisfied it, i.e. $f(x) \mapsto bool$.

The operator has a complexity of $O(N)$, where `N` is the number of elements searched.

The search finishes as soon as an element satisfies the predicate.

```cpp title="Signature"
template <typename TPredicate>
constexpr auto any( const TPredicate& predicate ) const -> bool;
```

```cpp title="Example" linenums="1"
constexpr auto numbers = std::array{ 3, 2, 5, 7, 9 };

static_assert(
    linq::from( &numbers )
    .any( []( const int i ) { return i % 2 == 0; } )
);

static_assert(
    linq::from( &numbers )
    .any( []( const int i ) { return i % 2 == 0; } )
);

static_assert(
    linq::from( { 3, 2, 5, 7, 9, 1 } )
    .any( []( int i ) { return i % 2 == 0; } )
);
```

## none

Computes whether none of the range's elements satisfy a `predicate`.

`predicate` must be a function that takes the range's element as input, and
returns a `bool` indicating whether that element satisfied it, i.e. $f(x) \mapsto bool$.

The operator has a complexity of $O(N)$, where `N` is the number of elements searched.

The search finishes as soon as an element satisfies the predicate.

```cpp title="Signature"
template <typename TPredicate>
constexpr auto none( const TPredicate& predicate ) const -> bool;
```
