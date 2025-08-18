#include <catch2/catch_test_macros.hpp>
#include <linq.hpp>

TEST_CASE( "element_at" ) {
    const auto numbers = std::vector{ 1, 2, 3, 4 };

    const auto num1 = linq::from( &numbers ).element_at( 2 );
    const auto num2 = linq::from( &numbers ).element_at( 6 );

    REQUIRE( num1.value() == 3 );
    REQUIRE( num2.has_value() == false );
}

TEST_CASE( "first" ) {
    constexpr auto numbers = std::array{ 1, 2, 3, 4 };

    constexpr auto num1 = linq::from( &numbers ).first();

    constexpr auto num2 = linq::from( &numbers ).first( []( const int i ) {
        return i > 2;
    } );

    STATIC_REQUIRE( num1.value() == 1 );
    STATIC_REQUIRE( num2.value() == 3 );
}

TEST_CASE( "last" ) {
    constexpr auto numbers = std::array{ 1, 2, 3, 4 };

    constexpr auto num1 = linq::from( &numbers ).last();
    constexpr auto num2 = linq::from( &numbers ).last( []( int i ) {
        return i < 3;
    } );

    STATIC_REQUIRE( num1.value() == 4 );
    STATIC_REQUIRE( num2.value() == 2 );
}
