#include "datatypes.hpp"
#include <catch2/catch_test_macros.hpp>
#include <linq.hpp>

TEST_CASE( "join" ) {
    const auto people1 = std::vector<person>{
        { .name = "P1", .age = 20 },
        { .name = "P2", .age = 21 },
        { .name = "P3", .age = 22 },
    };

    const auto people2 = std::vector<person>{
        { .name = "P1", .age = 22 },
        { .name = "P3", .age = 23 },
        { .name = "P1", .age = 26 },
    };

    const auto result = linq::from( &people1 )
                            .join(
                                linq::from( &people2 ),
                                []( const person& p ) {
                                    return p.name;
                                },
                                []( const person& p ) {
                                    return p.name;
                                },
                                []( const person& a, const person& b ) {
                                    return person{
                                        .name = a.name + b.name,
                                        .age  = a.age + b.age,
                                    };
                                } )
                            .to_vector();
}
