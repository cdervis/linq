#include <catch2/catch_test_macros.hpp>
#include <linq.hpp>

TEST_CASE( "all" ) {
    REQUIRE( linq::from( { 4, 3, 4, 3, 3 } ).all( []( int i ) {
        return i > 2;
    } ) );

    REQUIRE( linq::from( std::initializer_list<int>() ).all( []( const int i ) {
        return i > 2;
    } ) );

    REQUIRE_FALSE( linq::from( { 4, 3, 4, 3, 3, 1 } ).all( []( int i ) {
        return i > 2;
    } ) );
}

TEST_CASE( "any" ) {
    constexpr auto numbers = std::array{ 3, 2, 5, 7, 9 };

    REQUIRE( linq::from( &numbers ).any( []( const int i ) {
        return i % 2 == 0;
    } ) );

    REQUIRE( linq::from( &numbers ).any( []( const int i ) {
        return i % 2 == 0;
    } ) );

    REQUIRE( linq::from( { 3, 2, 5, 7, 9, 1 } ).any( []( int i ) {
        return i % 2 == 0;
    } ) );
}
