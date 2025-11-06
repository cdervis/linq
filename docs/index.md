---
title: linq
---

# linq - LINQ for C++

![logo](assets/logo.png){width=80}

linq is a minimalistic, header-only LINQ library for C++ 17 and newer.

It has no dependencies and neatly integrates into the STL by taking advantage of modern C++ features.

- Offers a simpler alternative to C++20 `#!cpp <ranges>`
- Resolves all type related functionality at compile-time; no virtual dispatch is used
- Uses lazy evaluation, so your queries still work even after you modify the container they're based on
- Focuses on immutability, so your queries stay predictable by minimizing surprising side-effects
- Is efficient in the way it works with your data, avoiding copies and instead moves data when possible
- Generates an operation chain at compile-time (supports `#!cpp constexpr`)
- Works with all generic container types, not just the STL

---

- [Download](https://github.com/cdervis/linq/archive/refs/tags/v0.9.0.zip) :octicons-download-16:
- [Try it on Compiler Explorer](https://godbolt.org/z/193YjTebf) :octicons-link-external-16:
- [License](license.md) :material-copyright:

---

## Examples

=== "Intro"

    ```cpp linenums="1"
    #include <linq.hpp>
    #include <print>
    
    struct Person {
      std::string name;
      int age;
    };
      
    int main() {
        const auto people = std::vector<Person> {
            { "Person 1", 20 },
            { "Person 2", 21 },
            { "Person 3", 22 }
        };
      
        // Create a query into the 'people' vector.
        const auto query = linq::from( &people )
                          .where( []( const Person& p ) { return p.age > 20; } )
                          .select( []( const Person& p ) { return p.name; } );
      
        // Iterating through a query will execute it.
        for ( const auto& name : query )
            std::println( "{}", name );
      
        return 0;
    }
    ```
  
    Output:
 
    ```
    Person 2
    Person 3
    ```

=== "Aggregation"

    ```cpp linenums="1"
    const auto people = std::vector<Person> {
        { "Person 1", 20 },
        { "Person 2", 21 },
        { "Person 3", 22 }
    };
    
    const double average_age = linq::from( &people )
                              .select( []( const Person& p ) { return p.age; } )
                              .average();
   
    const int people_over_20 = linq::from( &people )
                              .where( []( const Person& p ) { return p.age > 20; } )
                              .count();
    ```

=== "Element access"

    ```cpp linenums="1"
    const auto people = std::vector<Person> {
        { "Person 1", 20 },
        { "Person 2", 21 },
        { "Person 3", 22 }
    };
    
    const auto over_20  = []( const Person& p ) { return p.age > 20; };
    const auto under_20 = []( const Person& p ) { return p.age < 20; };
        
    const auto first_over_20 = linq::from( &people ).first( over_20 );
    //                       = Person 2
    
    const auto last_over_20 = linq::from( &people ).last( over_20 );
    //                      = Person 3
    
    const auto last_under_20 = linq::from( &people ).last( under_20 );
    //                       = empty optional
    ```

=== "Partitioning"

    ```cpp linenums="1"
    const auto numbers = linq::from( { 1, 2, 3, 4, 5, 6 } );
    
    const auto smaller_than_4 = []( int i ) { return i < 4; };
    
    const auto query1 = numbers.skip( 3 );                      // 4, 5, 6
    const auto query2 = numbers.skip_while( smaller_than_4 );   // 4, 5, 6
    const auto query3 = numbers.take( 4 );                      // 1, 2, 3, 4
    const auto query4 = numbers.take_while( smaller_than_4 );   // 1, 2, 3
    ```

=== "Sorting"

    ```cpp linenums="1"
    const auto words = std::vector {
        "hello"s, "world"s, "here"s,
        "are"s,   "some"s,  "sorted"s, "words"s
    };

    const auto word_length = []( const auto& word ) { return word.size(); };
    const auto self        = []( const auto& obj )  { return obj; };
    
    const auto query = linq::from( &words )
                      .order_by_ascending( word_length )
                      .then_by_ascending( self );

    //               = are, here, some, hello, words, world, sorted
    
    const auto rev = query.reverse();

    //             = sorted, world, words, hello, some, here, are
    ```

=== "Concatenation"

    ```cpp linenums="1"
    const auto numbers1 = std::vector{ 1, 2, 3 };
    const auto numbers2 = std::vector{ 4, 5, 6 };

    const auto range = linq::from( &numbers1 )
                      .append( linq::from( &numbers2 ) );
    
    //               = 1, 2, 3, 4, 5, 6
    ```

=== "Removing duplicates"

    ```cpp linenums="1"
    const auto numbers = std::vector{ 1, 2, 3, 3, 5, 4, 5, 6, 7 };

    const auto query = linq::from( &numbers ).distinct();

    //               = 1, 2, 3, 5, 4, 6, 7
    ```

=== "Composition"
    ```cpp linenums="1"
    const auto people = std::vector<Person> {
        { "Person 1", 20 },
        { "Person 2", 21 },
        { "Person 3", 22 }
    };

    const auto age_is_over_20 = []( const Person& p ) { return p.age > 20; };
    const auto age            = []( const Person& p ) { return p.age; };
    
    const double average_age = linq::from( &people )
                              .where( age_is_over_20 )
                              .select( age )
                              .average();

    //                       = 21
    ```

=== "Generation"

    ```cpp linenums="1"
    const auto range1 = linq::from_to( 0, 5 ); // 0, 1, 2, 3, 4, 5
    const auto range2 = linq::from_to( 0.0, 1.5, 0.5 ); // 0, 0.5, 1, 1.5
    const auto range3 = linq::from_to( 0, 3 ).repeat( 1 ); // 0, 1, 2, 3, 0, 1, 2, 3
    
    const auto range4 = linq::generate( []( size_t i ) {
        if ( i < 5 )
            return linq::generate_return( i * 2 );
    
        return linq::generate_finish();
    } );
    
    //          = 0, 2, 4, 6, 8
    ```

## How to use

### Option 1 (Direct, recommended)

You can simply copy `linq.hpp` into your source tree and then `#!cpp #include <linq.hpp>` to use linq directly.

### Option 2 (CMake)

[Download a release package](https://github.com/cdervis/linq/releases) and then add to your CMake script:

```cmake
project(MyProject)
add_executable(MyApp main.cpp)
add_subdirectory(linq)                    # Include
target_link_libraries(MyApp PRIVATE linq) # Link
```

## Compiler Support

linq has been tested with the following compilers:

| Compiler   | Version |
|------------|---------|
| MSVC       | 2019+   |
| Clang      | 16+     |
| GCC        | 10+     |
| AppleClang | 13+     |
