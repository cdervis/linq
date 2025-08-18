#include <catch2/catch_test_macros.hpp>
#include <linq.hpp>

TEST_CASE( "to_vector" ) {
    const auto nums = std::array{ 1, 2, 3, 4 };
    const auto vec  = linq::from( &nums ).to_vector();

    REQUIRE( vec.size() == 4 );
    REQUIRE( vec.at( 0 ) == 1 );
    REQUIRE( vec.at( 1 ) == 2 );
    REQUIRE( vec.at( 2 ) == 3 );
    REQUIRE( vec.at( 3 ) == 4 );
}

TEST_CASE( "to_map" ) {
    constexpr auto pairs = std::array{ std::pair{ "c"s, 1 }, std::pair{ "b"s, 2 }, std::pair{ "a"s, 3 } };
    const auto     map   = linq::from( &pairs ).to_map();

    REQUIRE( map.size() == 3 );
    REQUIRE( map.at( "a" ) == 3 );
    REQUIRE( map.at( "b" ) == 2 );
    REQUIRE( map.at( "c" ) == 1 );
}

TEST_CASE( "to_unordered_map" ) {
    const auto pairs = std::array{ std::pair{ "c"s, 1 }, std::pair{ "b"s, 2 }, std::pair{ "a"s, 3 } };
    const auto map   = linq::from( &pairs ).to_unordered_map();

    REQUIRE( map.size() == 3 );
    REQUIRE( map.at( "a" ) == 3 );
    REQUIRE( map.at( "b" ) == 2 );
    REQUIRE( map.at( "c" ) == 1 );
}
