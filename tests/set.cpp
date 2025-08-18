#include <catch2/catch_test_macros.hpp>
#include <linq.hpp>

TEST_CASE( "distinct" ) {
    const auto numbers          = std::vector{ 1, 2, 3, 3, 5, 4, 5, 6, 7 };
    const auto distinct_numbers = linq::from( &numbers ).distinct().to_vector();

    REQUIRE( distinct_numbers.size() == 7 );
    REQUIRE( distinct_numbers == std::vector{ 1, 2, 3, 5, 4, 6, 7 } );
}
