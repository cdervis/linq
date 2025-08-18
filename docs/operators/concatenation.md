# Concatenation

## append

Appends another range to the range.

`other_range` is appended in such a way that it is linked to the range.

This means that the sum range is lazily updated.

```cpp title="Signature"
template <typename TOtherRange>
constexpr auto append( const TOtherRange& other_range ) const;
```

```cpp title="Example" linenums="1"
auto nums1 = std::vector{ 1, 2, 3, 4 };
auto nums2 = std::vector{ 5, 6, 7, 8 };

const auto query1 = linq::from( &nums1 );     // 1, 2, 3, 4
const auto query2 = linq::from( &nums2 );     // 5, 6, 7, 8
const auto query3 = query1.append( query2 );  // 1, 2, 3, 4, 5, 6, 7, 8

nums1.push_back( -1 );
nums2.insert( nums2.begin(), 10 );

// query1 == 1, 2, 3, 4, -1
// query2 == 10, 5, 6, 7, 8
// query3 == 1, 2, 3, 4, -1, 10, 5, 6, 7, 8
```