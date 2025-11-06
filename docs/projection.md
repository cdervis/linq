# Projection

## select

Applies a `transform` function to each element of the range, producing new
elements (of a potentially different type).

The resulting range will have the same number of elements as the range itself.

`transform` must be a function that takes the range's element as input, and produces
a new value, i.e. $f(x) \mapsto y$, where `y` will be the type of element contained
in the new range.

```cpp title="Signature"
template <typename TTransform>
constexpr auto select( TTransform&& transform ) const;
```

```cpp title="Example" linenums="1"
const auto words  = std::vector{ "some"s, "example"s, "words"s };

const auto first_letters = linq::from( &words )
                          .select( []( const std::string& word ) { return word[0]; } )
                          .to_vector();

assert( first_letters == std::vector{ 's', 'e', 'w' } );
```

## select_to_string

Maps the elements of a range to a string using `std::to_string()`.
The resulting string type is `std::string`, unless `LINQ_NO_STL_CONTAINERS` is enabled.
If so, then the string type has to be specified explicitly, as a template type argument.

- `int_base` specifies the decimal base for integral input values
- `float_format` specified the format for floating-point input values

```cpp title="Signature"
#ifdef LINQ_NO_STL_CONTAINERS
template <typename StringType>
#endif
constexpr auto select_to_string( int               int_base = 10,
                                 std::chars_format float_format = std::chars_format::general ) const;
```

```cpp title="Example" linenums="1"
constexpr auto numbers = std::array{ 1, 2, 3 };

const auto result = linq::from( &numbers ).select_to_string().to_vector();

assert( result.size() == 3 );
assert( result == std::vector{ "1"s, "2"s, "3"s } );
```

## select_many

Applies a `transform` function to the range's elements that extracts a subrange from each element, i.e. $f(x) \mapsto Range$.

Produces a flattened range that combines all extracted ranges sequentially.

```cpp title="Signature"
template <typename TTransform>
constexpr auto select_many( TTransform&& transform ) const;
```

```cpp title="Example" linenums="1"
struct value_type {
    std::vector<int> nums;
};

const auto values = std::vector<value_type>{
    { .nums = { 1, 2, 3, 4 } },
    { .nums = { 5, 6, 7, 8 } },
    { .nums = { 9, 10, 11, 12 } },
};

const auto result = linq::from( &values )
                   .select_many( []( const value_type& p ) {
                       return linq::from( &p.nums );
                    } )
                   .to_vector();

assert( result.size() == 12 );
assert( result == std::vector{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 } );
```
